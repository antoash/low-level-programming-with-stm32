#ifndef MAIN_H
#define MAIN_H

#include <stm32f0xx.h>

#define PRESCALAR_VAL       (245-1)
#define ARR_VAL             (32768-1)
#define PORTB_CLK_EN        (1<<18)
#define TIM3_CLK_EN         (1<<1)
#define MODER4_AF           (1<<9)
#define AFSEL4_AF1          (1<<16)
#define OC1M_PWM_2          (7<<4)
#define CC1E_EN             (1<<0)
#define CNT_EN              (1<<0)

#endif