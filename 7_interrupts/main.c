#include "main.h"
#include "gpio.h"
#include "exti.h"


int main() {

	// disable global interrupts - for uninterrupted & smooth initialization
	__disable_irq();

	gpioInit();
	extiInit();

	// enable global interrupts
	__enable_irq();

	while (1);
}



