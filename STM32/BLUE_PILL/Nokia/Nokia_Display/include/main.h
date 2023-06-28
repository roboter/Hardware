#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f1xx.h"
#include "stdbool.h"
#define TIM4_INIT_VALUE 30
#define LED     GPIO_Pin_13
#define UART_BUFFER_LEN 10
#define gpio_set(PORT,pin)  PORT->BSRR=pin
#define gpio_reset(PORT,pin)  PORT->BRR=pin
//#define get_abs(n) ((n) < 0 ? -(n) : (n))

extern void delay_ms(uint32_t val);
void systick_delay(uint32_t count);
uint32_t get_abs(int j);


#endif //__MAIN_H
