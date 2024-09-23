[Demo](https://youtu.be/ms8SkEN7ErA)

- An ESP8266 is used to generate a signal with a rising and falling edge.                       
- A Blue LED is used to display the transition of the signal.                    
- Input Capture mode for Timer 14 is used to generate an interrupt when a rising edge and falling edge is detected.                 
- The interrupt handler toggles the Green LED each time an edge is detected.                                   
- The EXTI line configuration and interrupt handler is commented out. The EXTI interrupt handler performs the same task as the timer handler.        
