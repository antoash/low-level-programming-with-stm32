#include "main.h"
#include "usartInit.h"

/*
 * USART2: STM32 - PC communication
 * USART3: ESP8266 - STM32 communication
 */

void usart2Init() {

	RCC->APB1ENR |= USART2_CLK_ENABLE;											// Enable peripheral clock for USART 2.
	USART2->CR2 &= ~(1<<12);													// 1 stop bit.
	USART2->BRR = BAUD_RATE_VAL;												// Set baud rate 115200.
	USART2->CR1 |= OVERSAMPLE_8 | TX_ENABLE | RX_ENABLE | USART_ENABLE;   		// Set oversampling by 8, Transmitter Enable, Receiver Enable, USART Enable.

}

void usart3Init() {
	RCC->APB1ENR |= (1<<18);													// Enable peripheral clock for USART 3.
	USART3->CR2 &= ~(1<<12);													// 1 stop bit.
	USART3->BRR = BAUD_RATE_VAL;												// Set baud rate 115200.
	USART3->CR1 |= OVERSAMPLE_8 | TX_ENABLE | RX_ENABLE | USART_ENABLE;   		// Set oversampling by 8, Transmitter Enable, Receiver Enable, USART Enable.

}
