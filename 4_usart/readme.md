A program to demonstrate serial communication between the Nucleo board and computer.

### Important Concepts
- **Duplex:** Data can be either transmitted or received.
- **Simplex:** Data can only be transmitted or only received.
- **Full Duplex:** Data can be transmitted and received simultaneously in both directions.
- **Half Duplex:** Data can either be transmitted or received, but not at the same time.
- **CR/LF:**
    - **Carriage Return (CR):** Moves the cursor to the beginning of the current line (`\r`).
    - **Line Feed (LF):** Moves the cursor down to the next line (`\n`).
    - **CRLF:** Combination of the above — moves the cursor down to the next line and then to the beginning of that line.
- **Baud Rate**: The baud rate is the speed of data transmission over the USART interface. It is specified in bits per second (bps). This is an essential parameter for Asynchronous transmission and both receiver and transmitter must be configured with the same baud rate to prevent data errors during transmission and reception.
- **Idle Line**: The USART line remains in a high state (logic 1) before the start of data transmission or reception. 
- **Sampling**: The process of measuring the voltage level of a signal at discrete intervals. It involves capturing the state of the incoming data line at specific times to determine whether a bit is high or low.
	- **Undersampling:** When sampling rate is too low compared to signal frequency, it might now be able to capture the transitions between the time period which leads to data errors. synchronization issues. Accuracy is affected.
	- **Oversampling:** Data is sampled multiple times within the bit period (8/16 times), the receiver can more accurately identify the bit values and reduce  noise or signal distortion. This helps in achieving better synchronization and error detection.
### Composition of Data Packets
A data packet is the unit of data transmitted from the sender to the receiver. It consists of the following component.

- **Start Bit**: This is a signal that marks the beginning of a data frame. It is typically a single bit of logic 0 that enables the transition from the idle state (logic 1) to indicate that data transmission is about to begin. This allows the receiver to synchronize with the incoming data stream.

- **Data Frame**: The data frame consists of information to be transmitted in the packet and can consist of 7, 8, or 9 bits (based on configuration). Data is transmitted with the least significant bit (LSB) first by default.

- **Parity Bits**: Parity bits are added to a data packet during transmission for error detection. They are used to detect errors by adding an extra bit to the data, which can be set to either make the total number of 1's in the packet even (even parity) or odd (odd parity). Parity checking helps identify errors in the transmitted data. The choice of odd/even parity can be configured.

- **Stop Bits**: Stop bits signal the end of a data frame. They provide a way to separate data words and ensure that the receiver has sufficient time to process each data word. The number of stop bits can be 0.5, 1, 1.5, or 2, and their length is generally equal to one or more bit times. The stop bits are transmitted as logic 1 and allow the line to return to the idle state.

**Data Transmission/Reception**
- Transmission begins by pulling the idle line from a HIGH to a LOW state for one bit period.
- Data is transmitted character by character in packets.
- The USART can receive data words of either 7, 8 or 9 bits with stop bits and parity bit depending on the configuration.
- During an USART reception, data shifts in least significant bit first (default configuration) through the RX pin. 

### Determining the Baud Rate value 
For this case, I require a baud rate of 115200 with a clock frequency of 8MHz and oversampling set at 8 times the frequency.

Oversampling by 8, the formula is: $Baud = {2 \times f_{ck}\over USARTDIV}$
- USARTDIV:  ${{2 \times 8M}\over 115200}$
- USARTDIV = 139 = 0x8B = 0b10001011 
- _USART_BRR_ \[15:4] = 1000
- _USART_BRR_ \[3] = 0 (Must always be cleared when oversampling by 8)
- _USART_BRR_ \[2:0] = (1011>>1) = 0101 = 101 
- Putting this together, 10000101
- _USART_BRR_ = 0b10000101 = 0x85

In case of oversampling by 16, the formula is: $Baud = {f_{ck}\over USARTDIV}$
- USARTDIV:  ${{8M}\over 115200}$
- USARTDIV = 70 = 0x46 = 0b1000110
- _USART_BRR_ = 0x46
### Relevant Registers & Bits . 

**GPIO Pin Configuration** - PA2 (TX) & PA3 (RX)
- _RCC_AHBENR_ - AHB clock enable register 2
	- Bit 17 - IOPAEN
		- Set bit to enable Port A
- _GPIOA_MODER_ - GPIO Mode
	- Bits \[5:4] - MODER2
		- Set 10 to enable Alternate Function.
	- Bits \[7:6] - MODER3
		- Set 10 to enable Alternate Function.
- _GPIOA_AFRL_ - Alternate function selection for pins 0 to 7
	- Bits \[11:8] - AFSEL2
		- Set 0001 to enable Alternate Function 1.
	- Bits \[15:12] - AFSEL3
		- Set 0001 to enable Alternate Function 1.

**USART Configuration**
- _RCC_APB1ENR_ - AHB clock enable register 1
	- Bit 17 - USART2EN
		- Set 1 to enable.

- _USART_BRR_ - Baud Rate Register
	- This register can only be written when the USART is disabled (UE=0).
	- Bits \[15:4] = USARTDIV \[15:4].
	- BRR \[2:0] = USARTDIV \[3:0] shifted 1 bit to the right. BRR \[3] must be kept cleared.
	- BRR \[3] must be kept cleared.

- _USART_CR1_ - Control Register 1
	- Bit 28 & 12 - M1 & M0 to set word length - 8bit. 
		- Set 00 for 1 start bit, 8 data bits and n stop bits.
	- Bit 15 - OVER8
		- Set 0 - oversampling by 16.
		- Set 1 - oversampling by 8.
	- Bit 3 - TE Transmitter enable.
	- Bit 2 - RE Receiver enable.
	- Bit 0 - USART Enable
		- Set after basic configuration like word length, baud rate etc is completed.

- _USART_CR2_ - Control Register 2
	- Bits \[13:12] - Stop bits
		- Set 00 for 1 stop bit.
		- Set when UE=0.

- _USART_ISR_ -
	- Bit 7 - TXE Transmit data register empty. Set by hardware. read only.
		- 0: data is not transferred to the shift register
		- 1: data is transferred to the shift register
	- Bit 6 - TC: Transmission complete. Set by hardware. read only.
		- Set when transmission of a frame containing data is complete AND if TXE is set.
		- 0: Transmission is not complete 
		- 1: Transmission is complete
	- Bit 5 - RXNE: Read data register not empty. Set by hardware. read only.
		- 0: Data not received
		- 1: Received data has been transferred from the shift register to the Receiver Data Register.

- _USART_TDR_ - Transmit Data Register
	- Bits \[8:0] - TDR, rest of the bits are reserved.
	- Contains the data character to be transmitted.
- _USART_RDR_ - Receive Data Register
	- Bits \[8:0] - RDR, rest of the bits are reserved.
	- Contains the data character received.

### Code Overview

&emsp;gpioInit Function           
&emsp;&emsp;Set up the PA2 & PA3 pins as Alternate function pins - transmit and receive.               
           
&emsp;usartInit Function                
&emsp;&emsp;Define word length. (Default - 8 bit)                  
&emsp;&emsp;Select the desired baud rate.            
&emsp;&emsp;Set the number of stop bits.                  
&emsp;&emsp;Set oversampling rate.             
&emsp;&emsp;Enable transmitter, receiver and USART.                       

&emsp;transmitChar Function                              
&emsp;&emsp;Wait for the Transmission Complete flag to be set. Indicates that transmission has completed.                    
&emsp;&emsp;Transmit next character.                        
                                  
&emsp;transmitString Function         
&emsp;&emsp;Use string literals to identify whether termination character is reached. Else transmit current character and increment to the next character.                
   
&emsp;receiveChar Function                     
&emsp;&emsp;Wait till data has been received and transferred into the Data Register from the shift register.                     
&emsp;&emsp;Store this character in a variable and return.               

