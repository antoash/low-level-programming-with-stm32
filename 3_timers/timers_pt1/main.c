#include "main.h"
#include "timer.h"
#include "gpio.h"


int main() {

	gpioInit();
	timer_config();

	while(1){

		if (TIM14->SR & (1<<0)) {		// Check if timer counter has exceed ARR value
			TIM14->SR &= ~(1<<0);		// Reset the UIF flag
			GPIOA->ODR ^= (1<<5);		// Toggle LED
		}

	}


}
