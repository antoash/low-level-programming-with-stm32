#include "main.h"
#include "gpio.h"
#include "exti.h"


int main() {

	__disable_irq(); 		// Disable global interrupts - Prevent unexpected interruptions during initialization

	gpioInit();
	extiInit();

	__enable_irq();				// Enable global interrupts

	while (1);
}



