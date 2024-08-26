#include "gpio.h"
#include "delay.h"

int main(void){
    GPIO_init();

    while(1){
        GPIOA->BSRR = GPIOA->BSRR | (1<<5);
        delay(100);
        GPIOA->BSRR = GPIOA->BSRR | (1<<21);
        delay(100);
    }
}
