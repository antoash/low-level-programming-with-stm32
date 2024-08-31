#include "main.h"
#include "transmit.h"

void transmitChar (uint8_t ch) {
	while (!(USART2->ISR & ISR_TXE_BIT));  						// Wait till data is transferred to shift register for transmission.
	USART2->TDR = ch;
}

void transmitString (uint8_t *str) {							// Transmit each character of a string literal.
	while(*str!='\0') {
		transmitChar(*str);
		str++;
	}
}
