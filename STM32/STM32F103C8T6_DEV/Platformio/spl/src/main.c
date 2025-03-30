/**
 ******************************************************************************
 * @file    GPIO/IOToggle/main.c
 * @author  MCD Application Team
 * @version V3.6.0
 * @date    20-September-2021
 * @brief   Main program body.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2011 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
 * @{
 */

/** @addtogroup GPIO_IOToggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */

#define SYSCLK_FREQ_72MHz 72000000
#define DELAY DELAY_MS_MAX // Delay value for visible blink rate

void SetSysClockTo72(void)
{
    /* Enable HSI oscillator (internal 8 MHz clock) */
    RCC_HSICmd(ENABLE);

    /* Wait until the HSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
        ;

    /* Configure PLL to multiply HSI by 9 (8 MHz * 9 = 72 MHz) */
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9); // Use HSI and multiply by 9

    /* Enable the PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait until the PLL is locked */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        ;

    /* Select PLL as the system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait until the PLL is used as the system clock */
    while (RCC_GetSYSCLKSource() != RCC_SYSCLKSource_PLLCLK)
        ;
}

int main(void)
{
    /* Configure the system clock to 72 MHz */
    // SetSysClockTo72();
    delay_init();

    LED_Init();
    while (1)
    {
        LED_Toggle();
        delay_ms(DELAY);
    }
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */
