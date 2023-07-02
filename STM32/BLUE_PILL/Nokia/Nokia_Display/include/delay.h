#ifndef DELAY_H
#define DELAY_H
#include "stm32f1xx.h"
//#include "stm32f10x_conf.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void delay_config();

    void delay_ms(uint32_t aMilliseconds);

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H */