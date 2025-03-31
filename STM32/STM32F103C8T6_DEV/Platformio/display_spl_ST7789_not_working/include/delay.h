
#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
#define DELAY_US_MAX  1864135  // ~1.864 seconds
#define DELAY_MS_MAX  1864     // ~1.864 seconds
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
