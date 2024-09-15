
#include "stm32f0xx.h"

void GPIO_Config(void);
void EXTI_Config(void);

int main(void) {
    // Initialize GPIO and EXTI
    GPIO_Config();
    EXTI_Config();

    while (1) {
        // Main loop does nothing, just waiting for the interrupt
    }
}

// Function to configure GPIO for the LED (PA5) and Button (PC13)
void GPIO_Config(void) {
    // Enable GPIOA and GPIOC clocks
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // Enable GPIOA clock for LED
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;  // Enable GPIOC clock for Button

    // Configure PA5 as output (for LED)
    GPIOA->MODER &= ~(GPIO_MODER_MODER5);    // Clear PA5
    GPIOA->MODER |= (GPIO_MODER_MODER5_0);   // Set PA5 as output

    // Configure PC13 as input (for Button)
    GPIOC->MODER &= ~(GPIO_MODER_MODER13);   // Set PC13 as input (reset state)
}

// Function to configure EXTI for the button on PC13
void EXTI_Config(void) {
    // Enable the SYSCFG clock (needed to route the EXTI line)
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Configure EXTI line 13 to be triggered by PC13
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;   // Map PC13 to EXTI13

    // Configure EXTI line 13 for falling edge trigger (button press)
    EXTI->FTSR |= EXTI_FTSR_TR13;   // Falling trigger selection for line 13
    EXTI->IMR |= EXTI_IMR_MR13;     // Unmask EXTI line 13

    // Enable the EXTI interrupt in the NVIC
    NVIC_EnableIRQ(EXTI4_15_IRQn);  // Enable interrupt for EXTI lines 4 to 15
}

// Interrupt Service Routine for EXTI lines 4 to 15 (including EXTI13)
void EXTI4_15_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR13) {  // Check if EXTI13 triggered the interrupt
        // Toggle the LED
        GPIOA->ODR ^= GPIO_ODR_5;   // Toggle PA5 (LD2)

        // Clear the EXTI pending flag
        EXTI->PR |= EXTI_PR_PR13;   // Clear pending bit for EXTI13
    }
}
