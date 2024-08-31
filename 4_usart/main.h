#ifndef MAIN_H
#define MAIN_H

#include <stm32f0xx.h>

#define GPIOA_CLK_ENABLE    (1<<17)
#define PA2_AF              (2<<4)
#define PA3_AF              (2<<6)
#define AF1_SEL_PA2         (1<<8)
#define AF1_SEL_PA3         (1<<12)
#define ISR_RXNE_BIT        (1<<5)
#define ISR_TXE_BIT         (1<<7)
#define USART2_CLK_ENABLE   (1<<17)
#define BAUD_RATE_VAL       (0x85)
#define OVERSAMPLE_8        (1<<15)
#define TX_ENABLE           (1<<3)
#define RX_ENABLE           (1<<2)
#define USART_ENABLE        (1<<0)

#endif
