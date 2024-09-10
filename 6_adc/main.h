#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

/*
ADDRESS MAPPING
*/

#define Peripheral_Base 	(0x40000000UL)
#define APB_OFFSET 			(0x00000000UL)
#define APB_BASE	 		(Peripheral_Base + APB_OFFSET)

// RCC
#define RCC_OFFSET			(0x00021000UL)
#define RCC_BASE 			(Peripheral_Base + RCC_OFFSET)
#define RCC_AHBENR			(*(volatile uint32_t *)	(RCC_BASE + 0x14))
#define RCC_APB1ENR			(*(volatile uint32_t *)	(RCC_BASE + 0x1C))
#define RCC_APB2ENR         (*(volatile uint32_t *) (RCC_BASE + 0x18))

// Timer 3
#define TIM3_OFFSET  		(0x00000400UL)
#define TIM3_ADDR			(Peripheral_Base + TIM3_OFFSET)
#define TIM3_CR1			(*(volatile uint32_t *)(TIM3_ADDR + 0x00))
#define TIM3_CCMR1			(*(volatile uint32_t *)(TIM3_ADDR + 0x18))
#define TIM3_CCER			(*(volatile uint32_t *)(TIM3_ADDR + 0x20))
#define TIM3_CCR1			(*(volatile uint32_t *)(TIM3_ADDR + 0x34))
#define TIM3_CNT			(*(volatile uint32_t *)(TIM3_ADDR + 0x24))
#define TIM3_PSC			(*(volatile uint32_t *)(TIM3_ADDR + 0x28))
#define TIM3_ARR			(*(volatile uint32_t *)(TIM3_ADDR + 0x2C))

// GPIO A
#define GPIOA_OFFSET        (0x08000000UL)
#define GPIOA_BASE          (Peripheral_Base + GPIOA_OFFSET)
#define GPIOA_MODER         (*(volatile uint32_t *)(GPIOA_BASE + 0x00))

// GPIO B
#define GPIOB_OFFSET		(0x08000400UL)
#define GPIOB_BASE			(Peripheral_Base + GPIOB_OFFSET)
#define GPIOB_MODER 		(*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_AFRL 			(*(volatile uint32_t *)(GPIOB_BASE + 0x20))

// ADC
#define ADC1_OFFSET         (0x00012400UL)
#define ADC1_BASE           (Peripheral_Base + ADC1_OFFSET)
#define ADC1_ISR            (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR             (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_CFGR2          (*(volatile uint32_t *)(ADC1_BASE + 0x10))
#define ADC1_SMPR           (*(volatile uint32_t *)(ADC1_BASE + 0x14))
#define ADC1_CHSELR         (*(volatile uint32_t *)(ADC1_BASE + 0x28))
#define ADC1_DR             (*(volatile uint32_t *)(ADC1_BASE + 0x40))


#define PRESCALAR_VAL       (245-1)
#define ARR_VAL             (32768-1)

/*
REGISTER SET
*/

// RCC
#define PORTA_CLK_EN        (1<<17)
#define PORTB_CLK_EN        (1<<18)
#define TIM3_CLK_EN         (1<<1)
#define ADC_CLK_EN          (1<<9)

// GPIO
#define MODER1_ANALOG       (3<<2)
#define MODER4_AF           (1<<9)
#define AFSEL4_AF1          (1<<16)

// Timer 
#define OC1M_PWM_2          (7<<4)
#define CC1E_EN             (1<<0)
#define CNT_EN              (1<<0)
#define ARR_EN              (1<<7)

// ADC
#define ADCAL_EN            (1<<31)
#define CHSEL_CH1           (1<<1)
#define CLKMODE_ADC         (2<<30)
#define SMPLRATE_1          (1<<0)  
#define ADC_START           (1<<2)  
#define ADC_EN              (1<<0)  



#endif