#include "gpio.h"

void gpioInit(void) {
	RCC->AHBENR |= (1<<17);  		// Enable clock peripheral for Port A
	RCC->AHBENR |= (1<<19); 		// Enable clock peripheral for Port C

	GPIOA->MODER &= ~(3<<10); 		// Reset bits
	GPIOA->MODER |= (1<<10);  		// Set GPIO Output Mode for PA5

	GPIOC->MODER &= ~(3<<26);  		// Set GPIO Input Mode for PA13
}