#include "main.h"
#include "gpio.h"

void gpioInit() {

	RCC_APB2ENR |= ADC_CLK_EN;			// Enable peripheral clock for ADC1
	RCC_AHBENR |= PORTA_CLK_EN;			// Enable peripheral clock for I/O port A
	GPIOA_MODER |= MODER1_ANALOG;		// Enable Analog Mode

	RCC_AHBENR |= PORTB_CLK_EN;	    	// Enable peripheral clock for I/O port B
	GPIOB_MODER |= MODER4_AF;		    // Alternate Function Mode for PB4
	GPIOB_AFRL |= AFSEL4_AF1;        	// Enable Alternate Function 1 - TIM3_CH1

}

void setDutyCycle(uint16_t data){

	uint16_t dutyCycle = (data * TIM3_ARR) / 4095;		// Calculating the new duty cycle as a ratio of adc reading by 4095 (max resolution of this ADC channel) 
	TIM3_CCR1 = dutyCycle;								// Setting the new duty cycle
	
}