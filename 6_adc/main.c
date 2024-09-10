#include "main.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"

int main(){
    gpioInit();
	adcInit();
	pwmInit();

	uint16_t adc_value = 0;

    while (1) {

    	adc_value = adcRead();
    	setDutyCycle(adc_value);

    }


}
