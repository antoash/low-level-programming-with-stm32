#include "main.h"
#include "gpioInit.h"
#include "usartInit.h"
#include "transmit.h"
#include "receive.h"

int main() {

	gpioInit();
	usartInit();

	uint8_t ch = 'Y';

	transmitChar(ch);
	transmitChar('\r');
	transmitChar('\n');

	uint8_t *tx_buffer = "Sending a string thru USART. Check it out! \r\n";

	transmitString(tx_buffer);
	transmitString("Enter your name (Hit enter when done): \r\n");

	uint8_t rx_buffer;

	while (rx_buffer != '\r'){
		rx_buffer = receiveChar();
		transmitChar(rx_buffer);
	}

}
