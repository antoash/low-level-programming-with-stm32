#include "main.h"
#include "gpioInit.h"

void gpioInit() {

	// UART2
	RCC->AHBENR |= GPIOA_CLK_ENABLE;  									// Enable peripheral clock for I/O port A.
	GPIOA->MODER |= PA2_AF | PA3_AF;  									// Set Alternate Function Mode.
	GPIOA->AFR[0] |= AF1_SEL_PA2 | AF1_SEL_PA3; 						// Enable Alternate Function 1 for PA2 & PA3.

	GPIOA->MODER |= (1<<10);  											// Set PA5 as output. (Built-in LED)

	// UART3 - PC4 TX & PC5 RX
	RCC->AHBENR |= (1<<19); 											// Enable peripheral clock for I/O port C.
	GPIOC->MODER |= (2<<8) | (2<<10);  									// Set Alternate Function Mode.
	GPIOC->AFR[0] |= (1<<16) | (1<<20); 								// Enable Alternate Function 1 for PC4 & PA5.



}
