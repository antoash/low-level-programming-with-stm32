#include "main.h"
#include "gpioInit.h"

void gpioInit() {

	RCC->AHBENR |= GPIOA_CLK_ENABLE;  									// Enable peripheral clock for I/O port A.
	GPIOA->MODER |= PA2_AF | PA3_AF;  									// Set Alternate Function Mode.
	GPIOA->AFR[0] |= AF1_SEL_PA2 | AF1_SEL_PA3; 						// Enable Alternate Function 1 for PA2 & PA3.

}
