/*!
 * @file        main.c
 *
 * @brief       Main program body
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

#include "Board.h"
#include "stdio.h"

/** Delay */
void Delay(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
int main(void)
{
    GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(LED2_GPIO_CLK|LED3_GPIO_CLK);
    /** LED2 GPIO configuration */
    gpioConfig.pin = LED2_PIN;
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    GPIO_Config(LED2_GPIO_PORT, &gpioConfig);

    /** LED3 GPIO configuration */
    gpioConfig.pin = LED3_PIN;
    GPIO_Config(LED3_GPIO_PORT, &gpioConfig);

    /** Turn LED2 on */
    GPIO_ClearBit(LED2_GPIO_PORT, LED2_PIN);
    /** Turn LED3 off */
    GPIO_SetBit(LED3_GPIO_PORT, LED3_PIN);

    for(;;)
    {
        Delay();
        /** LED Toggle*/
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       Delay
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Delay(void)
{
    volatile uint32_t delay = 0xffff5;

    while(delay--);
}
