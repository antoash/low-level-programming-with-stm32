#include "main.h"
#include "receive.h"

uint8_t receiveChar2() {
	uint8_t *ch;

	while(!(USART2->ISR & ISR_RXNE_BIT));
	ch = USART2->RDR;

	return ch;
}
uint8_t receiveChar3() {
	uint8_t *ch;

	while(!(USART3->ISR & ISR_RXNE_BIT));
	ch = USART3->RDR;

	return ch;
}
