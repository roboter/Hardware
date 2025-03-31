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
#include "flash.h"
#include "ST7789.h"

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

void SystemClock_Config(void)
{
    // 1. Keep debugger active during clock changes
    DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;

    // 2. Enable PWR and BKP clocks for stability
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    // 3. Reset and enable HSE with timeout
    RCC_DeInit();
    uint32_t timeout = 0xFFFF;
    RCC_HSEConfig(RCC_HSE_ON);
    while ((RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET) && (timeout--))
        ;
    if (timeout == 0)
    {
        // Fallback to HSI if HSE fails
        RCC_HSEConfig(RCC_HSE_OFF);
        RCC_HSICmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
            ;
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16); // 64MHz
    }
    else
    {
        // Proceed with HSE
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 72MHz
    }

    // 4. Continue with PLL and clock configuration...
    // [Rest of your existing clock config]
}

int main(void)
{
    /* Configure the system clock to 72 MHz */
    SystemClock_Config();
    delay_init();

    LED_Init();

    // Initialize LCD
    LCD_Init();

    // Fill screen with red color
    LCD_FillScreen(0xF800); // RGB565 red

    // Draw a green pixel
    LCD_DrawPixel(100, 100, 0x07E0); // RGB565 green

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
