        .syntax unified
	
	      .include "efm32gg.s"
		.include "vectors.s"


	.section .text
 
	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset:
 	// Enable GPIO clock in cmu
	ldr R0, cmu_base_addr
	ldr R1, [R0, #CMU_HFPERCLKEN0]
	mov R2, #1
	lsl R2, R2, #CMU_HFPERCLKEN0_GPIO
	orr R1, R1, R2
	str R1, [R0, #CMU_HFPERCLKEN0]

	// Set high drive strength
	ldr R0, =GPIO_PA_BASE
	mov R1, #2
	str R1, [R0,#GPIO_CTRL]

	// Set pins 8-15 to output by writing 0x55555555
	ldr R1, =0x55555555
	STR R1, [R0,#GPIO_MODEH]

	// Test LEDs
	ldr R1, =0b0111000011110000
	str R1, [R0,#GPIO_DOUT]

cmu_base_addr:
			.long CMU_BASE
	
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////

        .thumb_func
gpio_handler:  

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

