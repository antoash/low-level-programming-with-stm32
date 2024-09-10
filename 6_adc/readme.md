### Varying the duty cycle of a PWM signal using a potentiometer.

PWM + ADC functionality. [demo](https://youtu.be/LosYJq7Qyh0)

1) Useful Concepts    
   - **Digital Signal:** A digital signal is discrete and discontinuous, represented by 0 and 1 which are the only two states available. 0 indicating logic low and 1 indicating max voltage.     
   - **Analog Signal:** An analog signal is smooth and continuous. They are bound to a range of values like (+5V to -5V) but there is an infinite possilities values within the range.  Unfortunately these signals are more susceptible to noise which are variations of voltage.     
   - **Sampling:** A technique used in conversion of analog signals to digital signals.  The analog signal will regularly captured over intervals of time in order to discretize the continuous signal.                                 
   The sampling frequency determines the rate of reads/samples per second. For accurate conversion, an adequate frequency must be selected to avoid loss of signal data.       
   - **Nyquist Theorem:** According to this, the minimum sampling rate required to accurately capture an analog signal is twice the highest frequency component of the signal. This rate is known as Nyquist rate. If sampling rate is lower that Nyquist rate, aliasing can occur.   
   - **Aliasing:** This is a phenomenon caused by under sampling of a signal. When fewer samples of the signal are captured, the shape of the signal is lost.                    
   - **Resolution:** It is a range of discrete values expressed in bits used to map each captured sample of the signal.                     
   A 12 bit resolution indicates a range of values from 0 to 4095, which can be mapped to the samples. 
   On the other hand, 8 bit resolution will be less accurate because there are only 256 values to match with the captured sample. Higher the range, the closer the mapping which means accuracy is better.                 
   - **Quantization:** During the conversion process, each captured value is matched with the closest discrete digital equivalent. This process is called quantization. The range of values is determined by the resolution of the ADC.                

2) Conversion Modes:                                                            
   There are various conversion modes available for different applications:                              
   - **Single Conversion:** The ADC performs one conversion on a single channel, then stops.                                                                           
   - **Continuous Conversion Mode:** The ADC continuously converts a single channel without stopping. After each conversion, the ADC immediately starts the next one.                
   - **Discontinuous Mode:** A subset of channels from the regular scan sequence is converted at a time, with a pause between groups.                 

3) Relevant Registers                     
Details on setting up registers for PWM/GPIO can be found in the previous exercises. These registers are only relevant for ADC configuration.     

   **_RCC_APB2ENR_** - APB 2 Enable Register                          
	   &emsp;Set bit 9 to enable ADC peripheral clock.                  
   **_RCC_AHBENR_** - AHB Enable Register                   
	   &emsp;Set bit 17 for port A.           
   
   **_GPIOA_MODER_** - Pin Mode                                              
	   &emsp;Enable Analog mode for PA 1 by setting bits \[3:2] to 11                
 
   **_ADC_CR_** - Control Register      
	   &emsp;Bit 31 - ADCAL (Calibration)         
		   &emsp;&emsp;1 - Set to calibrate only when ADC is disabled.              
		   &emsp;&emsp;Obtain calibration factor from bits \[6:0] in _ADC_DR_.                                                      
	   &emsp;Bit 2 - ADSTART (this can only be set once bits ADEN=1 and ADIS=0 -  ADC enabled, no pending request to disable)                                         
		   &emsp;&emsp;Set 1 to start ADC operation                                 
	   &emsp;Bit 1 -  ADDIS (disable command)                                                 
		   &emsp;&emsp;Set by software by writing to 1 in order to disable the ADC                                      
		   &emsp;&emsp;0 indicates no ADDIS command in progress.    
	   &emsp;Bit 0 - ADEN (enable)        
		   &emsp;&emsp;Write 1 to enable the ADC.       
		   &emsp;&emsp;Cleared by hardware once disabled.           

   **_ADC_ISR_** - Status Register                                              
	   &emsp;Bit 2 - EOC (end of conversion)                                                                              
		   &emsp;&emsp;Set by hardware after conversion of a channel is completed and data is available to read.                            
		   &emsp;&emsp;It can be cleared by reading the _ADC_DR_ register                               
	   &emsp;Bit 0 - ADRDY ADC Ready Flag                                                                 
		   &emsp;&emsp;1 - Set by hardware when ADC is enabled and ready to start conversion.                                           
		   &emsp;&emsp;0 - ADC not ready to start conversion/flag event was already acknowledged and cleared by software.                               

   **_ADC_CFGR1_** - Configuration Register 1                               
	   &emsp;Bit 2 - SCANDIR (scan direction)                         
		   &emsp;&emsp;0 - scan from channel 0 to 18.                               
		   &emsp;&emsp;1 - scan from channel 18 to 0.                                                   

   **_ADC_CFGR2_** - Configuration Register 2                                                                   
	   &emsp;Bits \[31:30] - CKMODE (clock mode)                                                                  
		   &emsp;&emsp;Set to 00 for asynchronous clock mode to use RCC clock. To be set when ADC is disabled.                                      

   **_ADC_SMPR_** - Sampling Register                                                       
	   &emsp;Bits \[2:0] - Sampling time selection                                                        
		   &emsp;&emsp;Select sampling time of 7.5 ADC cycles by setting 001.                                           

   **_ADC_DR_** - Data Register                                                                                     
	   &emsp;Bits \[15:0] - DATA Read only. Converted data from the last converted channel.                                                   
	   &emsp;&emsp;Immediately after calibration is complete, bits \[6:0] contain calibration factor.                                                   

   **_ADC_CHSELR_** - Channel Select Register                                                   
	   &emsp;Bit \[18:0] - each bit represents a channel                                          
		   &emsp;&emsp;Set bit 1 to select input channel 1                                          

4) Code Overview                                                

	adcInit Function                                                    
	&emsp;Reset ISR register                                              
	&emsp;Enable Calibration                              
	&emsp;Wait till ADCAL is 0                        
	&emsp;Select channel 1                        
	&emsp;Select asynchronous clock mode              
	&emsp;Enable ADC                                              
	&emsp;Wait till ADC ready (ADRDY) flag is set                                             

	adcRead Function                                                                                            
	&emsp;Start conversion                    
	&emsp;Wait till End of Conversion is set to read the data.                    
	&emsp;Return data                 

	setDutyCycle Function                   
	&emsp;Divide ADC value by 4095 and multiply with ARR register value to get duty cycle                 
	&emsp;Set CCR register to this new duty cycle                 

5. References
   - [Datasheet - STM32F078CB STM32F078RB STM32F078VB](https://www.st.com/resource/en/datasheet/stm32f072c8.pdf)                                                                                                                                                        
   - [STM32F0x1/STM32F0x2/STM32F0x8  Reference manual](https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)          
   - [STM32's ADC modes and their applications](https://www.st.com/resource/en/application_note/an3116-stm32s-adc-modes-and-their-applications-stmicroelectronics.pdf)          
   - [STM32 Potentiometer Reading Examples (Single & Multiple)](https://deepbluembedded.com/stm32-potentiometer-read-examples-single-multiple-potentiometers/)            

