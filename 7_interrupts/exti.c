#include "exti.h"


void extiInit(){

	RCC->APB2ENR |= (1<<0);

	// mapping pc13 to exti13 line
	SYSCFG->EXTICR[3] |= (1<<5);

	// unmask exti 13
	EXTI->IMR |= (1<<13);

	// select falling edge trigger for line 13
	EXTI->FTSR |= (1<<13);

	// enable lines 4  to 13 in nvic
	NVIC_EnableIRQ(EXTI4_15_IRQn);

//	NVIC_SetPriority(EXTI4_15_IRQn, 0x03);

}


void EXTI4_15_IRQHandler(void) {

	if (EXTI->PR & (1<<13) ){
		// clear PR flag
		EXTI->PR |= (1<<13);
		GPIOA->ODR ^= (1<<5);


	}
}