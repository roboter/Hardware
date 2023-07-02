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
#include "apm32f0xx_usart.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** USART Write data */
void USART_Write(USART_T* usart,uint8_t *dat);
/** Delay */
void Delay(uint32_t count);
/** Buffer compare*/
BOOL BufferCompare(uint8_t *buf1, uint8_t *buf2, uint8_t size);

#define DATA_BUF_SIZE       (32)
/** USART1 receive buffer*/
uint8_t rxDataBufUSART1[DATA_BUF_SIZE] = {0};
/** USART2 transmit buffer*/
uint8_t txDataBufUSART2[DATA_BUF_SIZE] = {0};
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
    BOOL state = TRUE;
    /** Init txDataBufUSART2 */
    for(int i = 0; i < DATA_BUF_SIZE; i++)
    {
        txDataBufUSART2[i] = i;
    }

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);
    APM_MINI_COMInit(COM2);
    USART_DisableInterrupt(MINI_COM1,USART_INT_RXBNEIE);
    USART_DisableInterrupt(MINI_COM2,USART_INT_RXBNEIE);

    for(int i = 0; i < DATA_BUF_SIZE; i++)
    {
        /** Wait until end of transmission */
        while(USART_ReadStatusFlag(USART2, USART_FLAG_TXBE) == RESET);
        USART_TxData(USART2, txDataBufUSART2[i]);

        /** Wait until end of reception */
        while(USART_ReadStatusFlag(USART1, USART_FLAG_RXBNE) == RESET);
        rxDataBufUSART1[i] = USART_RxData(USART1);
    }

     /** Verify data */
    state = BufferCompare(rxDataBufUSART1, txDataBufUSART2, DATA_BUF_SIZE);

    /** Data is ok then turn off LED2 */
    if(state == TRUE)
    {
        APM_MINI_LEDOn(LED2);
        printf("The DATA IS PASS, LED2 ON\r\n");
    }
    while(1)
    {
        APM_MINI_LEDToggle(LED3);
        Delay(0x7ffff);
    }
}

/*!
 * @brief       Compares two buffers
 *
 * @param       buf1:    First buffer to be compared
 *
 * @param       buf1:    Second buffer to be compared
 *
 * @param       size:    Buffer size
 *
 * @retval      Return TRUE if buf1 = buf2. If not then return FALSE
 *
 * @note
 */
BOOL BufferCompare(uint8_t *buf1, uint8_t *buf2, uint8_t size)
{
    uint8_t i;

    for(i = 0; i < size; i++)
    {
        if(buf1[i] != buf2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}
/*!
 * @brief       Delay
 *
 * @param       count:  delay count
 *
.
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
