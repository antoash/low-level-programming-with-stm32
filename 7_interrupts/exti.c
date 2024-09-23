#include "exti.h"


void extiInit(){

	RCC->APB2ENR |= (1<<0);				// Enable the clock peripheral for SYSCFG

	SYSCFG->EXTICR[3] |= (1<<5); 		// Map PB1 line to EXTI1

	EXTI->IMR |= (1<<13);				// Unmask EXTI13 line

	EXTI->FTSR |= (1<<13);				// Set falling edge trigger

	NVIC_EnableIRQ(EXTI4_15_IRQn);			// Enable NVIC Controller for EXTI13

//	NVIC_SetPriority(EXTI4_15_IRQn, 0x03);

}


void EXTI4_15_IRQHandler(void) {

	if (EXTI->PR & (1<<13) ){
		EXTI->PR |= (1<<13);		// Clear pending register flag 
		GPIOA->ODR ^= (1<<5);		// Toggle LED
	}
}