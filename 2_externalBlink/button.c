#include <stm32f0xx.h>
#include "button.h"

void button() {

    if (GPIOC->IDR & (1<<7)) { // If button pressed

        GPIOA->BSRR = (1<<25); // Reset ODRA bit 9, LED off

    } else {

        GPIOA->BSRR = (1<<9); // Set ODRA bit 9, LED on
    }
}
