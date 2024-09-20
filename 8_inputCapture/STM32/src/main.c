/******************************************************************************
 * This is register-level code for input capture using EXTI (commented out)
 * OR TIMER based interrupts.
 *
 * @File     main.c
 * @Author   antoash
 *
 *****************************************************************************/


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


