#include "main.h"
#include "adc.h"

void adcInit() {

	ADC1_ISR &= ~(ADC1_ISR);		// Clear ISR register
	ADC1_CR |= ADCAL_EN;			// Enable Calibration
	while(ADC1_CR & ADCAL_EN);  	// Wait till calibration to complete

	ADC1_CHSELR |= CHSEL_CH1;		// Select ADC Channel 1
	ADC1_CFGR2 &= ~CLKMODE_ADC;		// Clear bits to select Async clock mode
	ADC1_SMPR |= SMPLRATE_1;		// Select sampling raet of 7.5 cycles

	ADC1_CR |= ADC_EN;				// Enable ADC 
	while(!(ADC1_ISR & ADC_EN));	// Wait for ready flag to be set

}

uint16_t adcRead() {

	ADC1_CR |= ADC_START;					// Start conversion
	while (!(ADC1_ISR & ADC_START));  		// Wait till End of Conversion flag is set 
	return (ADC1_DR);						// Return the value

}