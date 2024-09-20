#include "main.h"
#include "exti.h"

void extiInit(void) {

//	RCC->APB2ENR |= (1<<0);				    // Enable the clock peripheral for SYSCFG
//	SYSCFG->EXTICR[0] |= (1<<4);			// Map PB1 line to EXTI1
//	EXTI->IMR |= (1<<1);					// Unmask EXTI1
//	EXTI->RTSR |= (1<<1);					// Set rising edge trigger
//	EXTI->FTSR |= (1<<1);					// Set fising edge trigger
//	NVIC_EnableIRQ(EXTI0_1_IRQn); 			// Enable NVIC Controller for TIM14

}

void EXTI0_1_IRQHandler(void) {
//
//	if ((EXTI->PR & (1<<1)) ) {	// Checks for pending trigger request
//		GPIOA->ODR ^= (1<<5);
//		EXTI->PR |= (1<<1);		// Reset the pending bit
//	}
}
