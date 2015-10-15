#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  

  //Clear handler
  *TIMER1_IFC = 1; 

  if((*GPIO_PA_DOUT)!=0x0fff){
    (*GPIO_PA_DOUT) = 0x0fff;
  }
  else if((*GPIO_PA_DOUT)==0x0fff){
    (*GPIO_PA_DOUT) = 0xf0ff;
  }

	
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    //*GPIO_IFC = GPIO_IF;
    //*GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    //*GPIO_IFC = GPIO_IF;

    //*GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
}


