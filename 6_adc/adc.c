#include "main.h"
#include "adc.h"

void adcInit() {

	ADC1_ISR &= ~(ADC1_ISR);
	ADC1_CR |= ADCAL_EN;
	while(ADC1_CR & ADCAL_EN);  

	ADC1_CHSELR |= CHSEL_CH1;
	ADC1_CFGR2 &= ~CLKMODE_ADC;
	ADC1_SMPR |= SMPLRATE_1;

	ADC1_CR |= ADC_EN;
	while(!(ADC1_ISR & ADC_EN));

}

uint16_t adcRead() {

	ADC1_CR |= ADC_START;
	while (!(ADC1_ISR & ADC_START));  
	return (ADC1_DR);

}