/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/22
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
/*
 *@Note
 *GPIO routine:
 *PD0 push-pull output.
 *
*/

#include "debug.h"
#include "ch32v00x_gpio.h"
#include "ch32v00x_rcc.h"

/* Global define */
#define LED_PIN GPIO_Pin_1
#define LED_PORT GPIOC


void GPIO_Blink_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable the clock for GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configure PA1 as push-pull output
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

int main(void)
{
    // Initialize system and GPIO
    SystemInit();
    Delay_Init();
    GPIO_Blink_INIT();

    while (1)
    {
        // Toggle PC1

        GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
        Delay_Ms(50);  // Delay for 500 ms

        GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
        Delay_Ms(50);  // Delay for 500 ms
    }
}
