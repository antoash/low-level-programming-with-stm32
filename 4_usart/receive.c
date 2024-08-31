#include "main.h"
#include "receive.h"

uint8_t receiveChar() {
	uint8_t *ch;

	while(!(USART2->ISR & ISR_RXNE_BIT));
	ch = USART2->RDR;

	return ch;
}
