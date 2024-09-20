#include "main.h"
#include "timer.h"

void timerIC(void) {

	TIM14->PSC = 0x111;								// Prescaler = 7
	TIM14->ARR = 0xFFFF;							// ARR = 65536
	TIM14->CNT = 0;									// Set initial counter value

	TIM14->CCMR1  = (1<<0);							// Set input capture mode
	TIM14->CCER  = (1<<3) | (1<<1) | (1<<0);			// Enable input capture at falling & rising edge
	TIM14->DIER |= (1<<1); 							// Enable interrupt for input capture

	TIM14->CR1 |= (1<<0);						// Enable input capture

	NVIC_EnableIRQ(TIM14_IRQn);

}

void TIM14_IRQHandler(void) {
							
	if (TIM14->SR & (1<<1)) {  		// Check flag for input capture rising/fallign edge

		GPIOA->ODR ^= (1<<5);		// Toggle LED
		TIM14->SR &= ~(1<<1);		// Reset flag 
	
	}
}
