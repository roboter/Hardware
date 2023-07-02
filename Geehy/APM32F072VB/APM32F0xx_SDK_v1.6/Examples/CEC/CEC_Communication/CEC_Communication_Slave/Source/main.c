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
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_cec.h"
#include "stdio.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

uint8_t rxDataBuffer[3] = {0x00, 0x00, 0x00};
static uint32_t interruptSrc;
uint8_t header,txheader;

#define false_return(val)        if(!(val)){return;}
#define true_return(val)         if((val)){return;}

/** Delay */
void Delay(uint32_t count);
/** Rx init */
void CEC_RxInit(void);
/** receive data */
void CEC_ReceiveData(void);
/** Write data */
void CEC_Write(uint8_t header, uint8_t *dat, uint8_t size);
/** Read data */
void CEC_Read(uint8_t *header, uint8_t *dat, uint8_t size);

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
    APM_MINI_COMInit(COM1);
    APM_MINI_LEDOn(LED3);

    interruptSrc = 0;
    header = (0x00 << 4 | 0x01);

    CEC_RxInit();

    while(1)
    {
        CEC_ReceiveData();

        Delay(100000);
        APM_MINI_LEDOff(LED3);
        APM_MINI_LEDToggle(LED2);

        printf(" Slave receive data£º  0x%02X, 0x%02X, 0x%02X\r\n", rxDataBuffer[0], rxDataBuffer[1],rxDataBuffer[2]);
    }
}

/*!
 * @brief       Receive Data
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void CEC_ReceiveData(void)
{
    CEC_Read(&header, rxDataBuffer, sizeof(rxDataBuffer));
    CEC_Write(txheader, rxDataBuffer, sizeof(rxDataBuffer));
}

/*!
 * @brief       CEC Transmit Data
 *
 * @param       header   data header
 *
 * @param       *dat:    data pointer
 *
 * @param       size:    data size
 *
 * @note
 */
void CEC_Write(uint8_t header, uint8_t *dat, uint8_t size)
{
    uint8_t i;

    if(!size)
    {
        CEC_CompleteMessage();
        CEC_TxData(header);
        CEC_StartNewMessage();
        return;
    }

    false_return(dat);

    CEC_TxData(header);
    CEC_StartNewMessage();

    for(i = 0; i < size; i++)
    {
        while((CEC_ReadStatusFlag(CEC_FLAG_TXBR) == RESET) && (!(interruptSrc & CEC_INT_TXBR)));

        if(interruptSrc & CEC_INT_TXBR)
        {
            interruptSrc &= ~CEC_INT_TXBR;
        }

        if(CEC_ReadStatusFlag(CEC_FLAG_TXBR) == SET)
        {
            CEC_ClearStatusFlag(CEC_FLAG_TXBR);
        }

        if(i == (size - 1))
        {
            CEC_CompleteMessage();
        }
        CEC_TxData(dat[i]);
        CEC_StartNewMessage();
    }
}

/*!
 * @brief       CEC Read Data
 *
 * @param       header   data header
 *
 * @param       *dat:    data pointer
 *
 * @param       size:    data size
 *
 * @note
 */
void CEC_Read(uint8_t *header, uint8_t *dat, uint8_t size)
{
    uint8_t i;

    true_return((!header) || (size && (!dat)));

    while((CEC_ReadStatusFlag(CEC_FLAG_RXBR) == RESET) && (!(interruptSrc & CEC_INT_RXBR)));
    CEC_ClearStatusFlag(CEC_FLAG_RXBR);
    interruptSrc &= ~CEC_INT_RXBR;
    *header = CEC_RxData();

    for(i = 0; i < size; i++)
    {
        while((CEC_ReadStatusFlag(CEC_FLAG_RXBR) == RESET) && (!(interruptSrc & CEC_INT_RXBR)));
        CEC_ClearStatusFlag(CEC_FLAG_RXBR);
        interruptSrc &= ~CEC_INT_RXBR;
        dat[i] = CEC_RxData();
    }

    while(CEC_ReadStatusFlag(CEC_FLAG_RXEND) == RESET && (!(interruptSrc & CEC_INT_RXEND)) && CEC_ReadStatusFlag(CEC_FLAG_RXOVR) == RESET);
    interruptSrc &= ~CEC_INT_RXEND;
    CEC_ClearStatusFlag(CEC_FLAG_RXEND);
}

/*!
 * @brief       CEC_Rx Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void CEC_RxInit(void)
{
    CEC_Config_T cecConfig;
    GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CEC);

    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_OD;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    gpioConfig.pin = GPIO_PIN_10;
    GPIO_Config(GPIOB, &gpioConfig);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_10, GPIO_AF_PIN0);

    CEC_ConfigStructInit(&cecConfig);
    CEC_Config(&cecConfig);

    CEC_ConfigOwnAddress(0x01);
    CEC_Enable();
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
