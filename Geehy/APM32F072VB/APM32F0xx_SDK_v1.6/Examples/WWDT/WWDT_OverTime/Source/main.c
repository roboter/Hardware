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
#include "apm32f0xx_wwdt.h"
#include "stdio.h"
#include "apm32f0xx_eint.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** The OverTime is used to change the test way*/
uint8_t is_OverTime = 0;

/** Delay */
void Delay(uint32_t Time);
/** WWDT_Init */
void WWDT_Init(void);

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
    APM_MINI_COMInit(COM2);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);

    /** Clear WWDTRST flag */
    if (RCM_ReadStatusFlag(RCM_FLAG_WWDTRST)!=RESET)
    {
        APM_MINI_LEDOn(LED3);
        RCM_ClearStatusFlag();
    }

    WWDT_Init();

    printf("\r\n System reset \r\n");

    while (1)
    {
        if (is_OverTime == RESET)
        {
            APM_MINI_LEDToggle(LED2);
            /**Delay about 250ms  , 192.23<250<261.76 ,Refresh allowed, system still running */
            Delay(400000);
            WWDT_ConfigCounter(127);
            printf("running\r\n");
        }

        if (is_OverTime == SET)
        {
            APM_MINI_LEDOn(LED3);
            /**Delay about 320ms  ,261.76<320 ,Refresh not allowed, system reset */
            Delay(500000);
            WWDT_ConfigCounter(127);
        }
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
void Delay(uint32_t Time)
{
    while (Time--);
}

/*!
 * @brief       WWDT configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void WWDT_Init(void)
{
    /** Enable WWDT clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_WWDT);

    /** WWDT TimeBase =  PCLK1 (8MHz)/4096)/8 = 244Hz (~4.09 ms)  */
    WWDT_SetTimebase(WWDT_DIV_8);

    /** Set Window value to 80; WWDT counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated  */
    WWDT_ConfigWindowValue(80);

    /** Enable WWDG and set counter value to 127, WWDT timeout = ~683 us * 64 = 43.7 ms
     In this case the refresh window is: ~5.46 * (127-80)= 192.23ms < refresh window < ~5.46 * 64 = 261.76ms*/
    WWDT_Enable(127);
}

/*!
 * @brief       Redirect C Library function printf to serial port.
 *              After Redirection, you can use printf function.
 *
 * @param       ch:  The characters that need to be send.
 *
 * @param       *f:  pointer to a FILE that can recording all information
 *              needed to control a stream
 *
 * @retval      The characters that need to be send.
 *
 * @note
 */
int fputc(int ch, FILE* f)
{
    /** send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /** wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}
