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
#include "apm32f0xx_can.h"
#include "stdio.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

typedef enum {FAILED = 0, SUCCEED = !FAILED} Status;
__IO uint32_t flag = 0;
__IO Status reSta;
uint32_t i = 0;

/** Delay */
void Delay(uint32_t count);
/** CAN interrupt */
Status CAN_Interrupt(void);

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

    /** Enable CAN clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN);

    /** NVIC configuration */
    NVIC_EnableIRQRequest(CEC_CAN_IRQn,0);

    reSta = CAN_Interrupt();

    if(reSta == SUCCEED)
    {
        APM_MINI_LEDOn(LED2);
        printf("\r\n RxMessage Status: SUCCEED\r\n");
    }
    else
    {
        APM_MINI_LEDOn(LED3);
        printf("\r\n RxMessage Status: FAILED\r\n");
    }

    while(1)
    {

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
 * @brief       DAC Interrupt
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
Status CAN_Interrupt()
{
    CAN_Config_T          canConfig;
    CAN_FilterConfig_T    filterConfig;
    CAN_Tx_Message        TxMessage;

    CAN_Reset();

    /** Enable FIF0 message pending interrupt */
    CAN_EnableInterrupt(CAN_INT_F0MP);

    /** CAN configuration */
    CAN_ConfigStructInit(&canConfig);
    canConfig.autoBusOffManage = DISABLE;
    canConfig.autoWakeUpMode   = DISABLE;
    canConfig.nonAutoRetran    = DISABLE;
    canConfig.timeTrigComMode  = DISABLE;
    canConfig.txFIFOPriority   = DISABLE;
    canConfig.rxFIFOLockMode   = DISABLE;
    canConfig.mode             = CAN_MODE_LOOPBACK;
    canConfig.syncJumpWidth    = CAN_SJW_1;
    canConfig.timeSegment1     = CAN_TIME_SEGMENT1_9;
    canConfig.timeSegment2     = CAN_TIME_SEGMENT2_8;
    canConfig.prescaler        = 4;
    CAN_Config(&canConfig);

    /** CAN filter configuration */
    filterConfig.filterIdHigh     = 0x0000;
    filterConfig.filterIdLow      = 0x0000;
    filterConfig.filterMaskIdHigh = 0x0000;
    filterConfig.filterMaskIdLow  = 0x0000;
    filterConfig.filterFIFO       = CAN_FIFO_0;
    filterConfig.filterNumber     = CAN_FILTER_NUMBER_1;
    filterConfig.filterMode       = CAN_FILTER_MODE_IDMASK;
    filterConfig.filterScale      = CAN_FILTER_SCALE_32BIT;
    filterConfig.filterActivation = ENABLE;
    CAN_ConfigFilter(&filterConfig);

    /** CAN Tx Message configuration */
    TxMessage.stanID         = 0x0000;
    TxMessage.extenID        = 0x1111;
    TxMessage.typeID         = CAN_TYPEID_EXT;
    TxMessage.remoteTxReq    = CAN_RTXR_DATA;
    TxMessage.dataLengthCode = 2;
    TxMessage.data[0]        = 0x55;
    TxMessage.data[1]        = 0xAA;
    CAN_TxMessage(&TxMessage);

    flag = 0xFF;
    i = 0;
    while((i<0xFFF) && (flag == 0xFF))
    {
        i++;
    }

    if(i == 0xFFF)
    {
        flag = 0;
    }

    CAN_DisableInterrupt(CAN_INT_F0MP);

    return(Status)flag;
}

/*!
 * @brief       CAN IRQHandler
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
 void CAN_Isr(void)
 {
     CAN_Rx_Message RxMessage;

     if(CAN_ReadIntFlag(CAN_INT_F0MP) == SET)
     {
         RxMessage.stanID           = 0x0000;
         RxMessage.extenID          = 0x0000;
         RxMessage.typeID           = CAN_TYPEID_STD;
         RxMessage.dataLengthCode   = 0;
         RxMessage.filterMatchIndex = 0;
         RxMessage.data[0]          = 0x00;
         RxMessage.data[1]          = 0x00;

         CAN_RxMessage(CAN_FIFO_0,&RxMessage);

         if((RxMessage.extenID == 0x1111) && (RxMessage.typeID == CAN_TYPEID_EXT)
             && (RxMessage.dataLengthCode == 2) && (RxMessage.data[1] | (RxMessage.data[0]<<8)) == 0x55AA)
         {
            flag = 1;
         }
         else
         {
            flag = 0;
         }
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
