/* 
Links to documentation used:
https://www.fsl.cs.sunysb.edu/kernel-api/re940.html
http://www.makelinux.net/ldd3/chp-9-sect-4
http://os.inf.tu-dresden.de/l4env/doc/html/dde_linux/group__mod__res.html#ga5d18868f68bb57bcdb7551f70a21202
http://www.fsl.cs.sunysb.edu/kernel-api/re946.html
https://www.kernel.org/doc/htmldocs/device-drivers/API-device-create.html
*/

#include "efm32gg.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/signal.h>
#include <asm/siginfo.h>
#include <linux/interrupt.h>

/* Constants */
#define DRIVER_NAME "gamepad"
#define DEVICE_N_COUNT 1
#define GPIO_EVEN_IRQ_LINE 17
#define GPIO_ODD_IRQ_LINE 18
#define size 0x4

/* Variables */
static dev_t DEVICE_N;
struct cdev gamepad_cdev;
struct class* class;

/* Functions */
static int __init gamepad_init(void);
static void __exit gamepad_exit(void);
static ssize_t gamepad_read(struct file*, char* __user, size_t, loff_t*);
static int gamepad_open(struct inode*, struct file*);
static int gamepad_release(struct inode*, struct file*);
static ssize_t gamepad_write(struct file*, char* __user, size_t, loff_t*);
static irqreturn_t gpio_interrupt_handler(int, void*, struct pt_regs*);


static struct file_operations gamepad_fops = {
    .owner = THIS_MODULE,
    .open = gamepad_open,
    .release = gamepad_release,
    .read = gamepad_read,
    .write = gamepad_write,
};

/* Configure module */
module_init(gamepad_init);
module_exit(gamepad_exit);
MODULE_DESCRIPTION("Gamepad Driver");
MODULE_LICENSE("GPL");

static int __init gamepad_init(void) {
  printk(KERN_ALERT "Loading gamepad driver module \n");
  
  /*
  Allocates a range of char device numbers. The major number will be chosen 
  dynamically, and returned (along with the first minor number) in dev. 
  Returns zero or a negative error code. 
  */
  int result = alloc_chrdev_region(DEVICE_N, 0, DEVICE_N_COUNT, DRIVER_NAME);

  /* If we have an error */
  if (result < 0) {
    printk(KERN_ALERT "Driver allocation failed\n");
    return -1;
  }

  /*
  request_mem_region allocates a memory region of len bytes, starting at start. 
  If all goes well, a non-NULL pointer is returned; 
  otherwise the return value is NULL. 
   */
  
  if(request_mem_region(GPIO_PC_MODEL, 1, DRIVER_NAME) == NULL) {
    printk(KERN_ALERT "Error in GPIO_PC_MODEL memory region\n");
    return -1;
  }
  if(request_mem_region(GPIO_PC_DOUT, 1, DRIVER_NAME) == NULL) {
    printk(KERN_ALERT "Error in GPIO_PC_DOUT memory region\n");
    return -1;
  }  
  if(request_mem_region(GPIO_PC_DIN, 1, DRIVER_NAME) == NULL) {
    printk(KERN_ALERT "Error in GPIO_PC_DIN memory region\n");
    return -1;
  }

  /*
  Remap I/O memory into kernel address space (no cache). 
  These should be refactored to helper funtions

 Set pins 0-7 to input by writing 0x33333333 */
  iowrite32(
    0x33333333,
    ioremap_nocache(GPIO_PC_MODEL, size)
    );
  /* Enable internal pull-up by writing 0xff */
  iowrite32(
    0xff,
    ioremap_nocache(GPIO_PC_DOUT, size)
    );

  /* Enable GPIO EXTIPSELL */
  iowrite32(
    0x22222222,
    ioremap_nocache(GPIO_EXTIPSELL, size)
    );

  /* Setup interrupts */
  request_irq(
    GPIO_EVEN_IRQ_LINE, 
    (irq_handler_t)gpio_interrupt_handler, 
    0, 
    DRIVER_NAME, 
    &gamepad_cdev
    );
  request_irq(
    GPIO_ODD_IRQ_LINE, 
    (irq_handler_t)gpio_interrupt_handler, 
    0, 
    DRIVER_NAME, 
    &gamepad_cdev
    );

  /* Enable interrupts */
  iowrite32(
    0xff, 
    ioremap_nocache(GPIO_EXTIFALL, size)
    );
  iowrite32(
    0xff,
    ioremap_nocache(GPIO_IEN, size)
    );
  iowrite32(
    0xff,
    ioremap_nocache(GPIO_IFC, size)
    );

  /*
  Initializes cdev, remembering fops, making it ready to add to
  the system with cdev_add. 
   */
  cdev_init(&gamepad_cdev, &gamepad_fops);
  gamepad_cdev.owner = THIS_MODULE;
  /*
  cdev_add adds the device represented by p to the system, 
  making it live immediately. A negative error code is returned on failure. 
   */
  cdev_add(&gamepad_cdev, DEVICE_N, DEVICE_N_COUNT);
  class = class_create(THIS_MODULE, DRIVER_NAME);
  /*
  This function can be used by char device classes. 
  A struct device will be created in sysfs, registered to the specified class. 
   */
  device_create(class, NULL, DEVICE_N, NULL, DRIVER_NAME);

  printk(KERN_INFO "Gamepad driver successfully loaded.\n");
  return 0;

  }

static void __exit gamepad_exit(void) {
  printk(KERN_ALERT "Exit from gamepad module\n");

  /*
  Free allocated memory and disable stuff
   */
  
  iowrite32(0, GPIO_IEN);

  /* Remove interrupt handlers. */
  free_irq(GPIO_EVEN_IRQ_LINE, &gamepad_cdev);
  free_irq(GPIO_ODD_IRQ_LINE, &gamepad_cdev);

  /* Memory regions should be freed when no longer needed: */
  release_mem_region(GPIO_PC_MODEL, 1);
  release_mem_region(GPIO_PC_DIN, 1);
  release_mem_region(GPIO_PC_DOUT, 1);

  /*
   This call unregisters and cleans up a device that was
   created with a call to device_create. 
   */
  device_destroy(class, DEVICE_N);
  class_destroy(class);
  cdev_del(&gamepad_cdev);
  unregister_chrdev_region(DEVICE_N, DEVICE_N_COUNT);
}

/* Gamepad reader */
static ssize_t gamepad_read(struct file* filp, char* __user buff,
        size_t count, loff_t* offp){
    /* Read gpio button status and write to buff */
    uint32_t data = ioread32(GPIO_PC_DIN);
    /*
    copy data from the device to user space
     */
    copy_to_user(buff, &data, 1);
    return 0;
}

/* Gamepad open */
static int gamepad_open(struct inode* inode, struct file* filp){
    printk(KERN_INFO "Gamepad driver opened\n");
    return 0;
}
/* Gamepad writer */
static ssize_t gamepad_write(struct file* filp, char* __user buff,
        size_t count, loff_t* offp) {
    printk(KERN_INFO "Write to gamepad");
    return 1;
}
/* Gamepad release */
static int gamepad_release(struct inode* inode, struct file* filp){
    printk(KERN_INFO "Gamepad driver released\n");
    return 0;
}


/* Interrupt handler */
irqreturn_t gpio_interrupt_handler(int irq, void* dev_id, struct pt_regs* regs) {
    printk(KERN_ALERT "Handling GPIO interrupt\n");
    iowrite32(ioread32(GPIO_IF), GPIO_IFC);
    /*
    If the handler found that its device did need attention it 
    should return IRQ_HANDLED
     */
    return IRQ_HANDLED;
}