#include "delay.h"
#include "stm32f1xx.h"

static volatile uint32_t systick_10ms_ticks = 0xfffffff0;

/*
 * Функция задержки
 */
void delay_ms(uint32_t msec)
{
    uint32_t tenms = msec / 10;
    uint32_t dest_time = systick_10ms_ticks + tenms;

    if (dest_time < tenms)
    {
        systick_10ms_ticks = 0;
        dest_time = tenms;
    }

    while (systick_10ms_ticks < dest_time)
    {
        __WFI();
    }
}

void delay_config()
{
    SysTick_Config(SystemCoreClock / 80);
}

void SysTick_Handler2(void)
{
    systick_10ms_ticks++;
}