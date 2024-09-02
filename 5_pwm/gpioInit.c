#include "main.h"
#include "gpioInit.h"

void gpioInit() {

	RCC->AHBENR |= PORTB_CLK_EN;	    // Enable peripheral clock for I/O port B
	GPIOB->MODER |= MODER4_AF;		    // Alternate Function Mode for PB4
	GPIOB->AFR[0] |= AFSEL4_AF1;        // Enable Alternate Function 1 - TIM3_CH1

}