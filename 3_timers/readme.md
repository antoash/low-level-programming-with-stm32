Using a Timer to toggle an LED every 500ms.

### Timers Available 
On the STM32 F072RB, these are the timers available:
- Advanced Timer (TIM1)
- General Purpose Timer 1 (TIM2/3)
- General Purpose Timer 2 (TIM14)
- General Purpose Timer 3 (TIM15/16/17)
- Basic Timer (TIM6/7)

### Important Concepts
- Tick - counter increment                   
- Frequency F: the number of pulses produced in a single second. F = 1/T = pulse/second        
- Time period T: duration of a single pulse in seconds. Inverse of frequency.                        
- System clock: a continuous signal oscillating between HIGH and LOW state at a constant interval. 
	- The clock frequency is the 8MHz quartz crystal by default. It produces 8 million clock pulses per second OR a pulse every 0.125us.        
- Prescalar: divides the clock frequency by a constant factor. A prescalar of 8 reduces the 8MHz clock into 1MHz. 
	- Frequency decreases as prescalar increases. The number of pulses produced per second decreases.             
- Time period for each pulse increases. The duration of a single pulse becomes larger.

### Calculations Required  
- System clock frequency = 8MHz (8 million cycles per second).    
- Time period of a single cycle = 1/F = 0.125us (time taken for a clock cycle).     
- The timer is 16bits so the max resolution is 0 to 65535.                                                         
- Max time duration before counter resets: $0.125us \times 65536 = 8.192ms < 500ms$                

Only possible variable is the time period, so we utilize the prescalar.

- Prescalar = 250                            
- Frequency = ${8M\over250} = 32KHz$             
- Time period =  31.25us                      
- Max time duration before counter resets: ${31.25us \times 65536} = 2.048s > 500ms$           
- This configuration allows the counter to go from 0 to 65536 in 2.048 seconds.                         
   
&emsp;	Finding the number of counter ticks to reach 500ms:               
&emsp;	2.048s -----> 65536                                         
&emsp;	0.5s     ----->    x   
&emsp;	$x = {{0.5 \times 65536} \over 2.048} = 16000 ticks$
### Relevant Registers 
- _RCC_APB1ENR_ (APB peripheral clock enable register 1)
	- Enable timer 14 by setting bit 8 - TIM14EN
- _TIM14_CR1_ (TIM14 control register 1)
	- Bit 7 - ARPE (Auto reload preload enable). Set 1 
		- Ensures any updates to ARR doesn't take place immediately. Instead, ARR will be updated at the next update event. Till then it will be stored in a shadow register. Without this, ARR will be updated immediately when written to (not good esp in middle of counting). 
	- Bit 2 - URS (update request source).
		- Set 1 - only counter overflow generates a UEV 
	- Bit 1 - UDIS (update disable). 
		- Set 0 - enable update event generation for for counter overflow OR setting UG bit in _TIM_EGR_. 
		- Set 1 - no update event (UEV) generated.
	- Bit 0 - CEN (counter enable) - Set to enable counter.

- _TIMx_ARR_ (ARR - Auto Reload Register) 
	- On matching the value stored in this register, the counter will be RESET back to zero.
	- An update event is generated which is used along with DMA/Interrupt to perform a task on completion of the timer.
- _TIMx_PSC_ (Prescalar Register) 
	- Stores the prescalar factor which is a 16bit value from 1 to 65536.
- _TIMx_CNT_ (Counter Register)
	- Keeps track of the count and is incremented each clock cycle.
	- It will count from 0 to the value stored in TIMx_ARR after which is.

- _TIM14_DIER_ (TIM14 interrupt enable register)
	- Bit 0 - UIE (update interrupt enable). set 1 to enable
		- When set to 1, the update interrupt is enabled. The timer will generate an interrupt request whenever an update event occurs
		- Set to 0, no interrupt request will be generated when an update event occurs.
- _TIM14_SR_ (Status register)
	- Bit 0 - UIF update interrupt flag. 0 indicates no update occurred. 
		- 1 indicates update interrupt pending. This is set by the hardware when: 
			- Overflow & UDIS = 0 in TIM14_CR1 register
			- rc_w0 - Software can read as well as clear this bit by writing 0. Writing 1 has no effect on the bit value.
- _TIM14_EGR_  (Event Generation Register)    
	- Automatically cleared by hardware.
	- Bit 0 - UG (update generation) 
		- At 1, reinitialize the counter and generate updates of registers. Prescalar Counter (keeps track of ticks doesn't store the psc value) is cleared and counter is also cleared.
		- At 0, no action.

**What are shadow registers?**
- Shadow registers are internal registers in a microcontroller that temporarily store data before transferring to the main register, ensuring smooth operation without disrupting ongoing processes. 
- They are not directly accessible by the user. 
- For example, on updating the Auto-Reload Register (ARR) during counting with auto-reload preload enabled, the new value is intially stored in the shadow register. It is then transferred to the _TIMx_ARR_ register during the next update event, ensuring that the ARR update doesn't affect the current counting process.

### Code Overview
&emsp;timerConfig function:                                 
&emsp;&emsp;Enable the clock for timer 14 peripheral.              
&emsp;&emsp;Set prescaler value.                         
&emsp;&emsp;Set the auto reload value.           
&emsp;&emsp;Enable auto reload preload and enable counter. _TIM14_CR1_              

&emsp;gpioInit function:                             
&emsp;&emsp;Enable clock.           
&emsp;&emsp;Set GPIO output mode.              
&emsp;&emsp;Set output configuration to Push-Pull.             
&emsp;&emsp;Switch on LED.                       
                            
&emsp;main function:                     
&emsp;&emsp;If timer has reached overflow condition.                
&emsp;&emsp;Reset the overflow flag and toggle LED.             
