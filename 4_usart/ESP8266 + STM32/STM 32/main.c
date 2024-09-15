#include "main.h"
#include "gpioInit.h"
#include "usartInit.h"
#include "transmit.h"
#include "receive.h"

/*
 * USART2: STM32 - PC communication
 * USART3: ESP8266 - STM32 communication
 */

int main() {

	gpioInit();
	usartInit();

	uint8_t rx_buffer;

	while(1){

		while (rx_buffer != '\r'){
			rx_buffer = receiveChar3();				// Receive data from ESP8266 using USART3
			transmitChar2(rx_buffer);				// Send this data to Serial Monitor on PC using USART2
		}
		GPIOA->ODR ^= (1<<5);  		// Toggle LED
		rx_buffer = 0; 				// Reset the buffer
	}

}
