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
	ldr R1, =0b0000000011111111 
	str R1, [R0,#GPIO_DOUT]

	// Set pins 0-7 to input by writing 0x33333333
	ldr R0, =GPIO_PC_BASE
	ldr R1, =0x33333333
	STR R1, [R0, #GPIO_MODEL]

	// Enable internal pull-up by writing 0xff
	ldr R3, =0xff
	STR R3, [R0, #GPIO_DOUT]

	//read status of pins 0-7 from GPIO_PC_DIN
	ldr R0, =GPIO_PA_BASE
	ldr R4, =GPIO_PC_BASE
	ldr R5, [R4, #GPIO_DIN]
	lsl R5, R5, #8
	STR R5, [R0, #GPIO_DOUT]


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

