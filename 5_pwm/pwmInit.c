/*
 * Time period is 1s.
 * Ton = 0.5s, Toff = 0.5s
 */


#include "main.h"
#include "pwmInit.h"

void pwmInit() {

	RCC->APB1ENR |= TIM3_CLK_EN;		   // Enable peripheral clock for Timer 3

	TIM3->PSC = PRESCALAR_VAL;		       // Set prescalar
	TIM3->ARR = ARR_VAL;	               // Set Auto Reload Value
	TIM3->CCR1 = (TIM3->ARR)/2;		       // 50% duty cycle

	TIM3->CCMR1 |= OC1M_PWM_2;             // Set PWM MODE 2
	TIM3->CCER |= CC1E_EN;                 // Output signal enabled
	TIM3->CR1 |= CNT_EN;                   // Enable counter

}