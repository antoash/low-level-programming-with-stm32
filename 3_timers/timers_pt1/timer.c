#include <stm32f0xx.h>
#include "timer.h"

void timer_config() {

	RCC->APB1ENR |= (1<<8);             // Enable clock for TIMER 14
	TIM14->PSC = 251 - 1;               // Set Prescalar value
	TIM14->ARR = 25000;                 // Set Auto Reload Register value
	TIM14->CR1 |= (1<<7) | (1<<0);      // Auto Reload Preload Enable + Enable Timer

}