#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x.h"
#include "stdbool.h"
#define TIM4_INIT_VALUE 30
#define LED GPIO_Pin_13
#define UART_BUFFER_LEN 10
#define gpio_set(PORT, pin) PORT->BSRR = pin
#define gpio_reset(PORT, pin) PORT->BRR = pin

extern void delay_ms(uint32_t val);
void systick_delay(uint32_t count);

#endif //__MAIN_H
