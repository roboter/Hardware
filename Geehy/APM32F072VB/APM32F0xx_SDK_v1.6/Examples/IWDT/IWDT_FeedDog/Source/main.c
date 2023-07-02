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
#include "apm32f0xx_iwdt.h"
#include "stdio.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** delay */
void Delay(uint32_t count);
/** IWDT init */
void IWDTInit(void);
/** IWDT Feed */
void IWDT_Feed(void);

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

    IWDTInit();
    printf("System Reset\r\n");
    while(1)
    {
          /** delay about 1 second  */
          Delay(1000000);
          APM_MINI_LEDToggle(LED2);
          IWDT_Feed();
          printf("runming\r\n");
    }
}


/*!
 * @brief       Delay
 *
 * @param       count:  delay count
 *
 * @retval      None
 *
 * @note
 */
void Delay(uint32_t count)
{
    volatile uint32_t delay = count;

    while(delay--);
}

/*!
 * @brief       IWDT Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDTInit()
{

    /** clear IWDTRST Flag*/
    if(RCM_ReadStatusFlag(RCM_FLAG_IWDTRST) != RESET)
    {
        RCM_ClearStatusFlag();
    }
    /** set IWDT Write Access */
    IWDT_EnableWriteAccess();

    /** set IWDT Divider*/
    IWDT_ConfigDivider(IWDT_DIV_64);

    /** set IWDT Reloader*/
    IWDT_ConfigReload(40000/32);

    /** Refresh*/
    IWDT_Refresh();

    /** Enable IWDT*/
    IWDT_Enable();
}

/*!
 * @brief       IWDT Feed Dog
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void IWDT_Feed(void)
{
    IWDT_Refresh();
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
int fputc(int ch, FILE *f)
{
        /** send a byte of data to the serial port */
        USART_TxData(DEBUG_USART,(uint8_t)ch);

        /** wait for the data to be send  */
        while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

        return (ch);
}
