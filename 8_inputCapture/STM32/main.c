#include "main.h"
#include "timer.h"
#include "exti.h"
#include "gpio.h"

int main(){

	gpioInit();
	timerIC();
	extiInit();

	while(1);

}


