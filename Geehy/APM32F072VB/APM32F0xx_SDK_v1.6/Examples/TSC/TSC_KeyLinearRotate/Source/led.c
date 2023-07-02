/*!
 * @file        led.c
 *
 * @brief       This file contains the Delay Driver main functions.
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

#include "led.h"
#include "oled.h"
#include "delay.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup LED_Driver LED Driver
  @{
*/

/** @addtogroup LED_Fuctions Fuctions
  @{
*/

const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

/*!
 * @brief       Configures LED GPIO.
 *
 * @param       None
 *
 * @retval      None
 */
void LED_Config(void)
{
    GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOC);

    gpioConfig.pin     = LED_ALLPIN;
    gpioConfig.speed   = GPIO_SPEED_50MHz;
    gpioConfig.mode    = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    GPIO_Config(LED_PORT, &gpioConfig);
    GPIO_ClearBit(LED_PORT, LED_ALLPIN);
}

/*!
 * @brief       Selected LED On.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *              @arg LED4
 *
 * @retval      None
 */
void LED_On(Led_TypeDef Led)
{
    LED_PORT->BSC = GPIO_PIN[Led];
}

/*!
 * @brief       Selected LED Off.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *              @arg LED4
 *
 * @retval      None
 */
void LED_Off(Led_TypeDef Led)
{
    LED_PORT->BSC = (uint32_t)(GPIO_PIN[Led] << 16);
}

/*!
 * @brief       elected LED Toggles.
 *
 * @param       Led: Specifies the Led to be configured.
 *              This parameter can be one of following parameters:
 *              @arg LED1
 *              @arg LED2
 *              @arg LED3
 *              @arg LED4
 *
 * @retval      None
 */
void LED_Toggle(Led_TypeDef Led)
{
    LED_PORT->ODATA ^= GPIO_PIN[Led];
}

/*!
 * @brief       LED Action for Touch Key
 *
 * @param       index: Select LED
 *
 * @retval      None
 */
void LED_Action(uint8_t index)
{
    switch (index)
    {
        case 0:
            LED_Toggle(LED1);
            if(GPIO_ReadOutputBit(LED_PORT, LED1_PIN) == SET)
            {
                OLED_ShowChinese(96, 0, 5, 16);
                OLED_Refresh();
            }
            else
            {
                OLED_ClearChar(96,112);
            }
        break;
        case 1:
            LED_Toggle(LED2);
            if(GPIO_ReadOutputBit(LED_PORT, LED2_PIN) == SET)
            {
                OLED_ShowChinese(80, 0, 5, 16);
                OLED_Refresh();
            }
            else
            {
                OLED_ClearChar(80,96);
            }
        break;
        case 2:
            LED_Toggle(LED3);
            if(GPIO_ReadOutputBit(LED_PORT, LED3_PIN) == SET)
            {
                OLED_ShowChinese(64, 0, 5, 16);
                OLED_Refresh();
            }
            else
            {
                OLED_ClearChar(64,80);
            }
        break;
        case 3:
            if(GPIO_ReadOutputBit(LED_PORT, LED_ALLPIN) == SET)
            {
                GPIO_ClearBit(LED_PORT, LED_ALLPIN);
                OLED_ClearChar(48, 128);
            }
            else
            {
                GPIO_SetBit(LED_PORT, LED_ALLPIN);
                OLED_ShowChinese(96, 0, 5, 16);
                OLED_ShowChinese(80, 0, 5, 16);
                OLED_ShowChinese(64, 0, 5, 16);
                OLED_ShowChinese(48, 0, 5, 16);
                OLED_Refresh();
            }
        break;
        case 4:
            LED_Toggle(LED4);
            if(GPIO_ReadOutputBit(LED_PORT, LED4_PIN) == SET)
            {
                OLED_ShowChinese(48, 0, 5, 16);
                OLED_Refresh();
            }
            else
            {
                OLED_ClearChar(48,64);
            }
        break;
    }
}

/**@} end of group LED_Fuctions*/
/**@} end of group LED_Driver*/
/**@} end of group Peripherals_Library*/
