### Blink 101

1) File structure                     
   - There are 5 files in this directory.           
   - I split up the program into separate header and source files. 
   - Each function is defined in its source file while the corresponding header file contains the declarations.                               
   - The _main.c_ file contains program logic where these functions are utilized.              
   
2) What is `#ifndef`?
   - A directive that prevents multiple compilations of the same header file in a project. 
   - It stands for 'If not defined' and is used with `#define` to create "#include guards".                              
   - In case of a large codebase, if a header file is included multiple times, the compiler will process it that many times which can lead to errors and increase the complexity of the code.                      
   - In other compilers, `#pragma once` is used which has the same functionality but is less verbose.                                      
               
   An example:            
   ```c         
    #ifndef GPIO_H         
    #define GPIO_H                

    #include <stdio.h>                   
    #include <stm32f0xx.h>                 

    void gpioInit();               

    #endif             
	```             
   - First, `#ifndef` checks whether the identifier (e.g., GPIO_H) has been previously defined by the preprocessor.         
   - If it hasn't been defined yet, the code inside the `#ifndef` block will be processed. The `#define` directive is then used to define the identifier, which effectively marks that the header has been included. The code inside the header file is then included and processed.                              
   - The `#endif` statement marks the end of the `#ifndef` block.                            
   - When the same header file is included again later in another part of code, the `#ifndef` checks for the identifier, which now exists due to the previous `#define`.                                                
   - Since the identifier is already defined, the code inside the `#ifndef` block is skipped which prevents the header from being included and processed again.                                        
              
3) General overview of Registers                             
   _x - A, B, C, D, E_                            
   - _RCC_AHBENR_ (AHB peripheral clock enable)                     
	   - Enable the corresponding peripheral clock to turn on power and clock signal to the port. Without enabling the clock, the registers of the peripheral cannot be access or modified.                       
   
   **Configuration Registers (32-bit)**                 
   - _GPIOx_MODER_ (GPIO Mode)               
	   - Select input modes                      
	   - Input mode, GPIO, alternate function, analog mode               
   - _GPIOx_OTYPER_              
	   - Set push-pull/open drain                     
   - _GPIOx_OSPEEDR_                
	   - Set speed: low/medium/high                                  
   - _GPIOx_PUPDR_                                     
	   - no pull up, pull down/pull up/pull down/reserved                                 
                 
   **Data Registers (32-bit)**              
   - _GPIOx_IDR_ (Input Data Register)                  
	   - When GPIO port is configured as input, data is stored in this register. Read only.
	   - Bits 16:31 are reserved.                                              
   - _GPIOx_ODR_ (Output Data Register)                   
	   - When GPIO port is used as OUTPUT, data can be stored/accessed using this register. Read/Write enabled.               
	   - Bits 16:31 are reserved.             
	     
   **Bitwise Data Handling Register (32-bit)**            
   - _GPIOx_BSRR_ (Bit Set/Reset Register)                 
	   - Write only register.                                             
	   - Set or Reset any individual bit in the _GPIOx_ODR_ .          
	   - 0 to 15 set corresponding ODRx bit              
	   - 16 to 31 reset corresponding ODRx bit                     
	     
   - **Alternate Function Registers**                            
	   - _GPIOx_AFRH_                         
	   - _GPIOx_AFRL_        

4) Make it blink! - Code overview           

   GPIO Init Function:                                     
   &emsp;Set IOPA EN bit. Enable the peripheral clock for port A.                    
   &emsp;Set MODER5 as 01 to enable general purpose output mode on port A pin 5.                              
   &emsp;Reset OT5 bit to set output type as Output Push Pull for port A pin 5.                                 
   &emsp;Set port A pin 5 to HIGH for the LED to glow.                
                    
   Delay Function:                 
   &emsp;Use for loops to generate a delay.                   
   
   Main Function:              
   &emsp;Loop infinitely.                                  
   &emsp;Set and Reset the BSRR register to toggle ODR register value with a delay in between to blink the LED.                   


### References            
- [Short introduction to header files in C (youtube.com)](https://www.youtube.com/watch?v=u1e0gLoz1SU)                 
- [HackMD - Collaborative Markdown Knowledge Base](https://hackmd.io/@hrbenitez/158_2s2223_GPIO)                                                 
- [STM32F0x1/STM32F0x2/STM32F0x8 advanced Arm-based 32-bit MCUs - Reference manual](https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)                
