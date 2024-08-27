#include <stm32f0xx.h>
#include "gpioInit.h"

void gpioInit() {

	RCC->AHBENR |= (1<<19) | (1<<17); // Enable ports A & C

	GPIOA->MODER |= (1<<18); // Set GPIO Output Mode for PA9
	GPIOC->MODER &= ~(3<<14);  // Set Input Mode for PC 7

	GPIOA->OTYPER &= ~(1<<9); // Set output push-pull

	GPIOA->PUPDR |= (1<<18); // Pull Up enabled for PA 9
	GPIOC->PUPDR |= (1<<15); // Pull Down enabled for PC 7

	GPIOA->ODR &= ~(1<<9); // LED off initially

}