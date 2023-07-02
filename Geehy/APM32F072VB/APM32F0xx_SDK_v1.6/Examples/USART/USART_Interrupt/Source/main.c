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

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

/** USART Write Data */
void USART_Write(USART_T* usart,uint8_t *dat);

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
    USART_Config_T usartConfigStruct;
    APM_MINI_COMInit(COM1);
    /** Enable GPIO clock */
    RCM_EnableAHBPeriphClock(MINI_COM1_TX_GPIO_CLK  | MINI_COM2_TX_GPIO_CLK);

    /** Enable COM1 or COM2 clock */
    RCM_EnableAPB2PeriphClock(MINI_COM1_CLK);
    RCM_EnableAPB2PeriphClock(MINI_COM2_CLK);

    /** Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(MINI_COM1_TX_GPIO_PORT,MINI_COM1_TX_SOURCE,MINI_COM1_TX_AF);

    /** Connect PXx to USARRX_Rx */
    GPIO_ConfigPinAF(MINI_COM1_RX_GPIO_PORT,MINI_COM1_RX_SOURCE,MINI_COM1_RX_AF);

    /** Configure USART Tx as alternate function push-pull */
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pin = MINI_COM1_TX_PIN;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(MINI_COM1_TX_GPIO_PORT, &gpioConfig);

    /** Configure USART Rx as input floating */
    gpioConfig.pin  = MINI_COM1_RX_PIN;
    GPIO_Config(MINI_COM1_RX_GPIO_PORT, &gpioConfig);


    /** MINI_USARTs configured as follow:  */
    /** BaudRate = 115200 baud   */
    usartConfigStruct.baudRate = 115200;
    /** Receive and transmit enabled  */
    usartConfigStruct.mode     = USART_MODE_TX_RX;
    /** Hardware flow control disabled (RTS and CTS signals)   */
    usartConfigStruct.hardwareFlowCtrl = USART_FLOW_CTRL_NONE;
    /** No parity  */
    usartConfigStruct.parity   = USART_PARITY_NONE;
    /** One Stop Bit  */
    usartConfigStruct.stopBits =  USART_STOP_BIT_1;
    /** Word Length = 8 Bits  */
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    /** USART_Config  */
    USART_Config(MINI_COM1, &usartConfigStruct);

    /** Enable USART_Interrupt_RXBNEIE*/
    USART_EnableInterrupt(MINI_COM1,USART_INT_RXBNEIE);

    NVIC_EnableIRQRequest(MINI_COM1_IRQn,2);

    /** Enable USART */
    USART_Enable(MINI_COM1);

    /** MINI_COM1 Send data to PC, and you need to open serial assistant to observe*/
    USART_Write(MINI_COM1,"HELLO APM MINI BOARD\r\n");
    while(1)
    {

    }

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

/*!
 * @brief        serial port tramsimt data
 *
 * @param        pointer to date that need to be sent
 *
 * @retval       None
 *
 * @note
 */
void USART_Write(USART_T* usart,uint8_t *dat)
{
     /** Enable USART_INT_TXCIE*/
    USART_EnableInterrupt(MINI_COM1,USART_INT_TXCIE);

    while(*dat)
    {
        while(USART_ReadStatusFlag(usart, USART_FLAG_TXBE) == RESET);

        USART_TxData(usart, *dat++);
    }

     USART_DisableInterrupt(MINI_COM1,USART_INT_TXCIE);
}

/*!
 * @brief        This function handles USART1 RX interrupt Handler
 *
 * @param        None
 *
 * @retval       None
 *
 * @note        This function need to put into  void USART1_IRQHandler(void)
 */
 void  USART_Receive_Isr(void)
 {
    uint8_t dat;

    if(USART_ReadStatusFlag(MINI_COM1, USART_FLAG_RXBNE) == SET)
    {
        dat = (uint8_t)USART_RxData(MINI_COM1);

        printf("%c",dat);
    }
 }


/*!
 * @brief        This function handles USART1 TXCIE interrupt Handler
 *
 * @param        None
 *
 * @retval       None
 *
 * @note        This function need to put into  void USART1_IRQHandler(void)
 */
 void USART_Send_Isr(void)
 {
     while(USART_ReadStatusFlag(MINI_COM1,USART_FLAG_TXBE)==RESET);

     if(USART_ReadStatusFlag(MINI_COM1,USART_FLAG_TXC))
     {
        /** USART1 output this information*/
        printf("APM MINI BOARD SEND FINISHED\r\n\r\n");

        USART_ClearStatusFlag(MINI_COM1,USART_FLAG_TXC);
     }
 }
