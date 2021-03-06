#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
  /* TODO set input and output pins for the joystick */


  //set pins 0-7 to input by writing 0xff
  *GPIO_PC_MODEL = 0x33333333;

  //enable internal pull-up by writing 0xff
  *GPIO_PC_DOUT = 0xff;

  //Enable GPIO EXTIPSELL
  *GPIO_EXTIPSELL = 0x22222222;

  //Enable EXTIRISE, EXTIFALL and IEN
  *GPIO_EXTIRISE = 0xff;
  *GPIO_EXTIFALL = 0xff;
  *GPIO_IEN = 0xff;

  //Turn off SRAM
  //*EMU_CTRL = 0x7;

    
  /* Example of HW access from C code: turn on joystick LEDs D4-D8
     check efm32gg.h for other useful register definitions
  */
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
  *GPIO_PA_CTRL = 2;  /* set high drive strength */
  *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
  *GPIO_PA_DOUT = 0xffff; /* turn on LEDs D4-D8 (LEDs are active low) */


}



