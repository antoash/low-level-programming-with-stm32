#include "main.h"
#include "gpio.h"

void gpioInit(void){

	RCC->AHBENR |= (1U<<17) | (1U<<18);		// Enable clock peripherals for GPIOA & GPIOB
	RCC->APB1ENR |= (1<<8);					// Enable clock peripheral for TIM14

	GPIOA->MODER |= (1<<10);				// Set PA5 in output mode
	GPIOB->MODER |= (1<<3);					// Set Alternate Function mode
	
	GPIOB->AFR[0] &= ~(0xF<<4); 			// Set Alternate Function 0 - TIM14 Channel 1

}
