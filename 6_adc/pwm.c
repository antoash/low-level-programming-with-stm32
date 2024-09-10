#include "main.h"
#include "pwm.h"

void pwmInit() {

	RCC_APB1ENR |= TIM3_CLK_EN;		      // Enable peripheral clock for Timer 3

	TIM3_PSC = PRESCALAR_VAL;		      // Set prescalar
	TIM3_ARR = ARR_VAL;	               	  // Set Auto Reload Value
	TIM3_CCR1 = (TIM3_ARR)/2;		      // 50% duty cycle

	TIM3_CCMR1 |= OC1M_PWM_2;             // Set PWM MODE 2
	TIM3_CCER |= CC1E_EN;                 // Output signal enabled
	TIM3_CR1 |= CNT_EN | ARR_EN;          // Enable counter & auto reload preload

}