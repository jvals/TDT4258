#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "efm32gg.h"

int i = 1;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */ 
  i +=  3;
  int x = 0;
  //while(x < 10000){
  *DAC0_CH0DATA = i;
  *DAC0_CH1DATA = i;
  //i+=44000;
  //x++;
  //}
    // Calculate the next LEDs that display time
  int time = *GPIO_PA_DOUT >> 8;
  time = ~time;
  time = (time + 1) & 0xffff;
  time = ~time;
  *GPIO_PA_DOUT = time << 8;

	
	
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


