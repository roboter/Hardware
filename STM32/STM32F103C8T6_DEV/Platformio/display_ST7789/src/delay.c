/**********************************************************************************
 * System Timer (SysTick) Delay Functions
 * Compatible with STM32 Cortex-M series
 * Version: ST_v3.5
 **********************************************************************************/

#include "delay.h"

static u8 fac_us = 0;  // us delay factor
static u16 fac_ms = 0; // ms delay factor

void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // Select external clock HCLK/8
    fac_us = SystemCoreClock / 8000000;                   // System clock divided by 8
    fac_ms = (u16)fac_us * 1000;                          // Calculate ticks needed for 1ms
}

/**
 * Delay in microseconds
 * @param nus Microseconds to delay
 */
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;             // Set reload value
    SysTick->VAL = 0x00;                      // Clear current value
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Start counting

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); // Wait until timeout

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable counter
    SysTick->VAL = 0X00;                       // Clear current value
}

/**
 * Delay in milliseconds
 * Note: Maximum delay limited by 24-bit register
 * For 72MHz clock: nms <= 1864
 * @param nms Milliseconds to delay
 */
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;        // Set reload value (24-bit)
    SysTick->VAL = 0x00;                      // Clear current value
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // Start counting

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); // Wait until timeout

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable counter
    SysTick->VAL = 0X00;                       // Clear current value
}