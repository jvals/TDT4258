#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include "efm32gg.h"
#include "music_theory.h"
#include "timer.h"
#include "dac.h"
#include "LETimer.h"

#define PI 3.14159
#define PERIOD 318

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880


/* Declarations */
void GPIO_Buttons();
void playSound(int change);
void sawtoothWave(int note, int time);
int mapInputToButton();

volatile int lastButtonActive = -1;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) LETIMER0_IRQHandler() {  


  if (counter >= current_note_length) {
    counter = 0;
    note_counter++;
  } else {
    counter++;
  }

  if(note_counter >= (*current_song).length) {
    stopLETimer();
    disableDAC();
    return;
  }

  Note* n = (*current_song).notes[note_counter];
  int offset = (i % (*n).number);
  setDACDATA(n, offset);
  i++;
}


/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
  GPIO_Buttons();
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
  GPIO_Buttons();
}


void GPIO_Buttons() {
  *GPIO_IFC = 0xff;
  *GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
  lastButtonActive = mapInputToButton();

  switch(lastButtonActive) {
  case(0) : break;
  case(1) : playSong(&TEST, 0x7fff); break;
  case(2) : playSong(&TEST1,0x2fff); break;
  case(3) : playSong(&TEST2,0x2fff); break;
  //case(4) : playSong(&TEST4,0xffff); break;
  case(5) : playSound(/*128*5*/ g   ); break;
  case(6) : playSound(/*128*6*/ gS  ); break;
  case(7) : playSound(/*128*7*/ a   ); break;
  case(8) : playSound(/*128*8*/ -1   ); break;
  default : break;
  }  
}



void playSound(int change) {
  if(change == -1) {
    stopLETimer();
    disableDAC();
    *DAC0_CH0DATA = 0;
    *DAC0_CH1DATA = 0;
    return;
  }
}

int mapInputToButton() {
  switch((*GPIO_PC_DIN)) {
    case(0xfe) : return 1;
    case(0xfd) : return 2;
    case(0xfb) : return 3;
    case(0xf7) : return 4;
    case(0xef) : return 5;
    case(0xdf) : return 6;
    case(0xbf) : return 7;
    case(0x7f) : return 8;

    default : break;
  }
  return 0;

}