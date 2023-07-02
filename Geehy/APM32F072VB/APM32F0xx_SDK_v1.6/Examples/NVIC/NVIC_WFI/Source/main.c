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
#include "apm32f0xx_eint.h"
#include "apm32f0xx_misc.h"

/** define KEY1,KEY2 EXTI LINE*/
#define KEY1_BUTTON_EXTI_LINE  EINT_LINE1
/** printf function configs to USART1*/
#define DEBUG_USART  USART1

/** used to indicate interrupt status*/
uint8_t intStatus;

/** Delay */
void Delay(uint32_t count);

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
    APM_MINI_LEDOff(LED3);

    APM_MINI_COMInit(COM1);

    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);

    /** Configure NVIC_IRQRequest */
    NVIC_EnableIRQRequest(EINT0_1_IRQn, 1);

    printf("push KEY1 to executing WFI£¬and device will enter sleep mode.\r\n\r\n");

    while(1)
    {
        if (intStatus == 1)
        {
            APM_MINI_LEDOff(LED2);
            APM_MINI_LEDOff(LED3);

            printf("enter sleep mode successfully, push KEY1 to wake up device.\r\n\r\n");
            /** Wait fot interrupt*/
            __WFI();

            printf("exit sleep mode successfully!\r\n\r\n");
            intStatus = 0;

            printf("running...\r\n");
        }

        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);

        Delay(100000);
    }
}

/**
 * @brief       The interrupt will happen when the button 1 is press
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function should put into EINT0_1_IRQHandler() in apm32f0xx_int.c
 */
void APM_MINI_PB_Isr(void)
{
    if(EINT_ReadStatusFlag(KEY1_BUTTON_EXTI_LINE) == SET)
    {
        intStatus = 1;

        EINT_ClearStatusFlag(KEY1_BUTTON_EXTI_LINE);
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
