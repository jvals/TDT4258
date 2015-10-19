#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "efm32gg.h"
#include "music_theory.c"
#include "LETimer.h"

/* 
  TODO calculate the appropriate sample period for the sound wave(s) 
  you want to generate. The core clock (which the timer clock is derived
  from) runs at 14 MHz by default. Also remember that the timer counter
  registers are 16 bits.
*/




/* Declaration of peripheral setup functions */
//void setupTimer(uint32_t period);

void setupDAC();
void setupNVIC();
void setupGPIO();

/* Your code will start executing here */
int main(void) 
{  
  /* Call the peripheral setup functions */
  setupGPIO();
  setupDAC();
  setupLETimer(SAMPLE_PERIOD);

  /* Enable interrupt handling */
  setupNVIC();

  
  /* TODO for higher energy efficiency, sleep while waiting for interrupts
     instead of infinite loop for busy-waiting
  */
/*
  *CMU_CMD = 4<<0; //Select LFXO as clock source for the high frequency clock

  *CMU_OSCENCMD |= 0<<0; // Disables the high frequency oscillator
  *CMU_OSCENCMD |= 1<<1; // Disables the high frequency oscillator
*/
  

  *SCR = 0x06;
  

  while(1) {
    __asm("WFI");
  }

  return 0;
}

void setupNVIC()
{
  /* TODO use the NVIC ISERx registers to enable handling of interrupt(s)
     remember two things are necessary for interrupt handling:
      - the peripheral must generate an interrupt signal
      - the NVIC must be configured to make the CPU handle the signal
     You will need TIMER1, GPIO odd and GPIO even interrupt handling for this
     assignment.
  */
     // GPIO EVEN
     *ISER0 |= 1 << 1;

     // GPIO ODD
     *ISER0 |= 1 << 11;

     // LETIMER0
     *ISER0 |= 1 << 26;
}
