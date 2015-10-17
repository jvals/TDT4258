#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "music_theory.h"
#include "LETimer.h"

/* The low energy timer will make use of the low frequency oscillator (LFX0) */

void setupLETimer(uint16_t period) {

	/* Start low freq oscillator */
	*CMU_OSCENCMD |= (1<<8);

	/* LF0 will drive the low frequency clock */
	*CMU_LFCLKSEL |= 2<<0;

	/* Configure the start-up delay for LFXO 
	Timeout period of 32768 cycles.
	Reset is 0x3 for some reason, so we need to 
	invert */
	*CMU_CTRL &= ~(3<<18);

	/* Enable clock for low energy peripheral interface */
	*CMU_HFCORECLKEN0 |= 1<<4;

	/* Enable clock for LETIMER */
	*CMU_LFACLKEN0 |= 1<<2;

	// Enable LETIMER0_COMP0 as top register for LETIMER
	*LETIMER0_CTRL |= (1 << 9);

	*LETIMER0_COMP0 = period;

	// Start the LETIMER
	*LETIMER0_CMD |= (1<<0);

	// Enable interrupt generation
	*LETIMER0_IEN |= (1 <<2);

}

void startLETimer() {
	*LETIMER0_CMD |= (1<<0);
	*CMU_OSCENCMD |= (1<<8);
}

void stopLETimer() {
	i = 0;
    counter = 0;
    note_counter = 0;
	*LETIMER0_CMD |= (1<<1);
	*CMU_OSCENCMD |= (1<<9);
	*LETIMER0_IFC |= (1 << 2);

}