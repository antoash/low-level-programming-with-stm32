A program to generate a PWM signal with 50% duty cycle and time period of 1 second.
### What is a Pulse Width Modulation?
Pulse Width Modulation (PWM) is a technique used to generate analog signals from digital outputs by varying the duty cycle of a digital pulse.             
In an STM32 microcontroller, PWM is typically generated using the timer peripherals. 
The timer counts up to a specified value, and the output toggles between high and low states based on the duty cycle, which is set by adjusting the timer's compare register.          
By varying the duty cycle, you can control the effective voltage applied to a load, enabling tasks like motor speed control, LED dimming, and more.         
         
Some useful terminology related to PWM:                      
- **Duty Cycle**: The proportion of time during which the PWM signal is high (on) within a single period.                                   
- **Frequency**: The number of times the PWM signal completes a full cycle (high and low states) per second. It is measured in Hertz (Hz) and impacts how smoothly the PWM signal controls the load.                            
- **Period**: The duration of one complete PWM cycle, which is the inverse of the frequency. The period consists of both the high (on) and low (off) times.                 
- **Resolution**: The granularity with which you can adjust the duty cycle of the PWM signal. It is determined by the bit-width of the timer/counter used for generating the PWM, with higher resolution allowing finer control.
            
### Understanding PWM mode                         
- Pulse Width Modulation (PWM) mode allows the generation of a signal with a frequency determined by the value in the _TIMx_ARR_ (Auto-Reload Register) and a duty cycle defined by the value in the _TIMx_CCRx_ (Capture/Compare Register).                                                    
- The PWM mode can be independently selected on each channel by setting the _OCxM_ bits in the _TIMx_CCMRx_ (Capture/Compare Mode Register) to 110 (PWM mode 1) or 111 (PWM mode 2).                                         
    - To enable the corresponding preload register, you must set the _OCxPE_ bit in the _TIMx_CCMRx_ register. Additionally, if using upcounting or center-aligned modes, you should enable the auto-reload preload register by setting the _ARPE_ bit in the _TIMx_CR1_ (Control Register 1).                                 
- Since the preload registers are only transferred to the shadow registers upon an update event, all registers must be initialized before starting the counter by setting the _UG_ bit in the _TIMx_EGR_ (Event Generation Register).
 
### Calculations
A time period of 1 second at 50% duty cycle will be at 0.5s.          
                             
2 seconds ---> 65536 ticks                            
x seconds ---> 1 tick                        
                       
$T = 30.51us$                                         
 $F = {1\over T}$                  
$F = 32.768 KHz$                      
The frequency required is around 32.768KHz.                  
              
$Fclk = 8MHz$              
${Fclk \over PSC} = 32.768K$            
${8M \over PSC} = 32.768K$                  
$PSC = 244$                
                      
Counter will count to 65536 ticks in 2 seconds.                   
A time period of 1 second is required which means ARR is 32768 (65536/2) ticks.             
The LED will blink at 50% duty cycle which is every 0.5 second - ARR/2.                     
             
### Relevant Registers                                      
          
**GPIO Pin Configuration**             
- _RCC_AHBENR_ - AHB Peripheral Clock Enable Register              
	- Bit 18 - Enable clock peripheral for Port B.               
- _GPIOB_MODER_ - Mode Register             
	- Bits \[9:8] - MODER4              
		- Set 10 for Alternate Function mode.              
- _GPIOB_AFRL_ - alternate function low register             
	- Bits \[19:16] - AFSEL4              
		- Set 0001 for Alternate Function 1 (TIM3_CH1).                
                                   
**TIMER 3 Configuration**                                                                         
- _RCC_APB1ENR_ - AHB Peripheral Clock Enable Register 1                            
	- Bit 1 - Set to enable TIM3                       
                        
- _TIM3_CR1_ - Control Register 1              
	- Bit 7 - Set 1 for ARPE Auto-reload preload enable.              
	- Bit 4 -  Set 0 for up counter.         
	- Bit 0 - CEN (counter enable) - Set to enable counter.                             
                       
- _TIM3_CCMR1_ - Capture/Compare Mode Register 1                                                      
	- The bits in this register has a different configuration when the channel is in input capture mode (IC) vs output compare mode (OC). Since this program deals with output compare mode, all bits are configured in terms of OC.              
	- Bits \[6:4] - OC1M (Output compare 1 mode)                                                     
		- 111: PWM mode 2.                                        
		  Channel 1 in up counting mode, outputs logic LOW when _TIM3_CNT_<TIM3_CCR1 otherwise output is logic HIGH. (vice versa for down counting mode)                             
	- Bit 3 - OC1PE (Output Compare 1 Preload Enable)                                               
		- 1: Preload register on is enabled, _TIMx_CCR1_ will be loaded only at the next update event.                         
		- 0: If _TIMx_CCR1_ is updated, it will be loaded instantly into the register.                                 
                   
- _TIM3_CCER_ - Capture/Compare Enable Register                                     
	- The bits in this register has a different configuration when the channel is in input capture mode (IC) vs output compare mode (OC). Since this program deals with output compare mode, all bits are configured in terms of OC.               
	- Bit 0 - When channel 1 is configured as Output.            
		- Set 1 to enable OC signal on Channel 1 pin.         
		- Set 0 to disable OC signal.                 
                 
- _TIM3_ARR_ - Auto Reload Register                       
	- On matching the value stored in this register, the counter will be RESET back to zero.              
	- An update event is generated which is used along with DMA/Interrupt to perform a task on completion of the timer.                 
- _TIM3_PSC_ - Prescalar Register              
	- Stores the prescalar factor which is a 16bit value from 1 to 65536.               
- _TIM3_CNT_ - Counter Register              
	- Keeps track of the count and is incremented each clock cycle.                     
	- It will count from 0 to the value stored in TIMx_ARR after which is.               
- _TIM3_CCR1_ - Capture/Compare Register                                     
	- Bits \[15:0] - CCR1                         
		- The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OC1 output.                
             
- _TIM3_EGR_ - Event Generation Register          
	- Bit 0 - UG (Update generation)                                    
		- 1: Updates the registers. Clears prescalar and counter. Useful for when updates are required for particular registers that can't be updated instantly while counting is on going.                              
             
### Code Overview              
gpioInit Function                       
Enable peripheral clock for port B.                       
Set Alternate Fucntion mode for PB4 and enable Alternate Function 1 - TIM3 channel 1.              
                     
pwmInit Function                    
Enable peripheral clock for Timer 3.               
Set prescalar and ARR values.                 
Set the duty cycle which is based on the ARR value using CCR1 register.               
Enable PWM mode 2 which outputs logic LOW when _TIM3_CNT_<TIM3_CCR1 otherwise out put is logic HIGH.            
Enable output signal and start counter.              
        
### Result & Demonstration   
![12](https://github.com/user-attachments/assets/fd76e6df-dc90-49a8-acf3-8f6bce9c8fef)
[View Demo](https://youtu.be/p4pt5MOWSSw)

