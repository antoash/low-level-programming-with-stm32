#include "main.h"
#include "transmit.h"

// USART2
void transmitChar2 (uint8_t ch) {
	while (!(USART2->ISR & ISR_TXE_BIT));  						// Wait till data is transferred to shift register for transmission.
	USART2->TDR = ch;
}

void transmitString2 (uint8_t *str) {							// Transmit each character of a string literal.
	while(*str!='\0') {
		transmitChar2(*str);
		str++;
	}
}

// USART3
void transmitChar3 (uint8_t ch) {
	while (!(USART3->ISR & ISR_TXE_BIT));
	USART3->TDR = ch;
}

void transmitString3 (uint8_t *str) {
	while(*str!='\0') {
		transmitChar3(*str);
		str++;
	}
}
