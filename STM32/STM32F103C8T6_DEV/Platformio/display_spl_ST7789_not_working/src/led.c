#include "led.h"
#include "delay.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    LED_Reset(); // Start with LED off
}

void LED_Set(void)
{
    GPIOA->BSRR = GPIO_Pin_1; // Set pin (turn on)
}

void LED_Reset(void)
{
    GPIOA->BRR = GPIO_Pin_1; // Reset pin (turn off)
}

void LED_Toggle(void)
{
    GPIOA->ODR ^= GPIO_Pin_1; // Toggle pin state
}