/*!
 * @file        delay.h
 *
 * @brief       This file contains external declarations of the led.c file.
 *
 * @version     V1.0.0
 *
 * @date        2022-02-21
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

#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup LED_Driver LED Driver
  @{
*/

/** @addtogroup LED_Macros Macros
  @{
*/

typedef enum
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2,
    LED4 = 3
} Led_TypeDef;

#define LEDn            4

#define LED_PORT        GPIOC
#define LED1_PIN        GPIO_PIN_0
#define LED2_PIN        GPIO_PIN_1
#define LED3_PIN        GPIO_PIN_2
#define LED4_PIN        GPIO_PIN_3
#define LED_ALLPIN      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3

/**@} end of group LED_Macros*/

/** @addtogroup LED_Fuctions Fuctions
  @{
*/
void LED_Config(void);
void LED_On(Led_TypeDef Led);
void LED_Off(Led_TypeDef Led);
void LED_Toggle(Led_TypeDef Led);

void LED_Action(uint8_t index);

/**@} end of group LED_Fuctions */
/**@} end of group LED_Driver */
/**@} end of group Peripherals_Library */

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
