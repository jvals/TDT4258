#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include "efm32gg.h"

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

void GPIO_Buttons();
void playSound(int change);
int mapInputToButton();
void sawtoothWave(int note, int time);

volatile int lastButtonActive = -1;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
  //Clear handler
  *TIMER1_IFC = 1;
  switch(lastButtonActive) {
  case(0) : break;
  case(1) : playSound(/*128*1*/ c   ); break;
  case(2) : playSound(/*128*2*/ d   ); break;
  case(3) : playSound(/*128*3*/ e   ); break;
  case(4) : playSound(/*128*4*/ f   ); break;
  case(5) : playSound(/*128*5*/ g   ); break;
  case(6) : playSound(/*128*6*/ gS  ); break;
  case(7) : playSound(/*128*7*/ a   ); break;
  case(8) : playSound(/*128*8*/ -1   ); break;
  default : break;
  }
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
    
}



void playSound(int change) {

  if(change == -1) {
    *DAC0_CH0DATA = 0;
    *DAC0_CH1DATA = 0;
    return;
  }

  *DAC0_CH0DATA += change;
  *DAC0_CH1DATA += change;

  if(*DAC0_CH0DATA >= change*3) {
    *DAC0_CH0DATA = 0;
    *DAC0_CH1DATA = 0;
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
  return lastButtonActive;

}

/*void sawtoothWave(int note, int time){

    int sampling=PERIOD/note;
    
    int slope = (1024)/sampling;
    
    int y = (slope*duration);
    
    *DAC0_CH0DATA=y;
    *DAC0_CH1DATA=y;
    
    duration++;

    if(duration>=sampling){
      duration=0;
    }
    counter++;
    
    if(counter==time){
       iterate=true;
       counter=0;
    }
}*/