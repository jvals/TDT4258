#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "efm32gg.h"

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */ 
  
  int x = 0;

  (*GPIO_PA_DOUT) = 0x0fff;

  sleep(3);



  (*GPIO_PA_DOUT) = 0xf0ff;
  x = 0;
  while(x<100000) {
    x++;
  }


  //Clear handler
  *TIMER1_IFC = 1; 
  
	
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    
    *GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
    *GPIO_IFC = 0xff;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    *GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
    *GPIO_IFC = 0xff;
}


