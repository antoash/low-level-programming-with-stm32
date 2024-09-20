#include "main.h"
#include "gpio.h"

void extiInit(void) {

	RCC->APB2ENR |= (1<<0);				    // Enable the clock peripheral for SYSCFG
	SYSCFG->EXTICR[0] |= (1<<4);			// Map PB1 line to EXTI1
	EXTI->IMR |= (1<<1);					// Unmask EXTI1
	EXTI->RTSR |= (1<<1);					// Set rising edge trigger

	NVIC_EnableIRQ(TIM14_IRQn); 			// Enable NVIC Controller for TIM14 

}