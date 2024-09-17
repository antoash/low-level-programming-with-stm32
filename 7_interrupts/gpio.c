#include "gpio.h"

void gpioInit(void) {
	RCC->AHBENR |= (1<<17);  // clock for led pin
	RCC->AHBENR |= (1<<19); // enable clock for gpioc

	GPIOA->MODER &= ~(3<<10); // clear pa 5
	GPIOA->MODER |= (1<<10);  // output pa 5

	GPIOC->MODER &= ~(3<<26);  // input pa 13
}