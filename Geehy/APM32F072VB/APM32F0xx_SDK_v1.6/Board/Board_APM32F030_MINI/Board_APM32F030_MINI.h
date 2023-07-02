/*!
 * @file        Board_APM32F030_MINI.h
 *
 * @brief       This file contains definitions for APM32F030_MINIBOARD's Leds, push-buttons hardware resources
 *
 * @version     V1.0.1
 *
 * @date        2021-07-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __BOARD_APM32F030_MINI_H
#define __BOARD_APM32F030_MINI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "apm32f0xx.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_usart.h"
#include "apm32f0xx_rcm.h"

typedef enum
{
  LED2 = 0,
  LED3 = 1
} Led_TypeDef;

typedef enum
{
  BUTTON_KEY1 = 0,
  BUTTON_KEY2 = 1
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EINT = 1
} ButtonMode_TypeDef;

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;


#define LEDn                             2
#define LED2_PIN                         GPIO_PIN_6
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCM_AHB_PERIPH_GPIOB

#define LED3_PIN                         GPIO_PIN_7
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCM_AHB_PERIPH_GPIOB

#define BUTTONn                          2

/**
 * @brief Key1 push-button
 */
#define KEY1_BUTTON_PIN                   GPIO_PIN_1
#define KEY1_BUTTON_GPIO_PORT             GPIOA
#define KEY1_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOA
/**
 * @brief Key2 push-button
 */
#define KEY2_BUTTON_PIN                   GPIO_PIN_0
#define KEY2_BUTTON_GPIO_PORT             GPIOA
#define KEY2_BUTTON_GPIO_CLK              RCM_AHB_PERIPH_GPIOA

#define COMn                             2

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define MINI_COM1                        USART1
#define MINI_COM1_CLK                    RCM_APB2_PERIPH_USART1

#define MINI_COM1_TX_PIN                 GPIO_PIN_9
#define MINI_COM1_TX_GPIO_PORT           GPIOA
#define MINI_COM1_TX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define MINI_COM1_TX_SOURCE              GPIO_PIN_SOURCE_9
#define MINI_COM1_TX_AF                  GPIO_AF_PIN1

#define MINI_COM1_RX_PIN                 GPIO_PIN_10
#define MINI_COM1_RX_GPIO_PORT           GPIOA
#define MINI_COM1_RX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define MINI_COM1_RX_SOURCE              GPIO_PIN_SOURCE_10
#define MINI_COM1_RX_AF                  GPIO_AF_PIN1

#define MINI_COM1_IRQn                   USART1_IRQn
/**
 * @brief Definition for COM port2, connected to USART2 (USART2 pins remapped on GPIOD)
 */
#define MINI_COM2                        USART2
#define MINI_COM2_CLK                    RCM_APB1_PERIPH_USART2

#define MINI_COM2_TX_PIN                 GPIO_PIN_2
#define MINI_COM2_TX_GPIO_PORT           GPIOA
#define MINI_COM2_TX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define MINI_COM2_TX_SOURCE              GPIO_PIN_SOURCE_2
#define MINI_COM2_TX_AF                  GPIO_AF_PIN1

#define MINI_COM2_RX_PIN                 GPIO_PIN_3
#define MINI_COM2_RX_GPIO_PORT           GPIOA
#define MINI_COM2_RX_GPIO_CLK            RCM_AHB_PERIPH_GPIOA
#define MINI_COM2_RX_SOURCE              GPIO_PIN_SOURCE_3
#define MINI_COM2_RX_AF                  GPIO_AF_PIN1

#define MINI_COM2_IRQn                   USART2_IRQn


/** LED */
void APM_MINI_LEDInit(Led_TypeDef Led);
void APM_MINI_LEDOn(Led_TypeDef Led);
void APM_MINI_LEDOff(Led_TypeDef Led);
void APM_MINI_LEDToggle(Led_TypeDef Led);

/** Key button */
void APM_MINI_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t APM_MINI_PBGetState(Button_TypeDef Button);
void APM_MINI_PB_Led_Isr(void);
/** COM */
void APM_MINI_COMInit(COM_TypeDef COM);

#ifdef __cplusplus
}
#endif

#endif
