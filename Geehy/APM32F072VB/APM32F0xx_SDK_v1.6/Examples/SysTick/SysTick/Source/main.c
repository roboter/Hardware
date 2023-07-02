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
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_rcm.h"

/** System tick */
uint32_t sysTick = 0;

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
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOn(LED3);

    /** Configure the SysTick to generate a time base equal to 1 ms*/
    if (SysTick_Config(SystemCoreClock/1000))
    {
        while (1);
    }

    while (1)
    {
        if (sysTick >= 1000)
        {
            sysTick = 0;

            APM_MINI_LEDToggle(LED2);
            APM_MINI_LEDToggle(LED3);
        }
    }
}
