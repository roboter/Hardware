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
#include "apm32f0xx_dma.h"
#include "apm32f0xx_syscfg.h"

/** Set Buff Size */
#define BufSize 0xFF
/** USART TX Buf*/
uint8_t DMA_USART_TxBuf[BufSize];
/** USART RX Buf*/
uint8_t DMA_USART_RxBuf[BufSize];

/** Delay */
void Delay(void);
/** USART Init */
void USART1_Init(void);
/** DMA_USART_Rx Init */
void DMA_Rx_Init(uint32_t* RxBuf);
/** compare Buffer */
BOOL BufferCompare(uint8_t* buf1, uint8_t* buf2, uint8_t size);

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
    APM_MINI_LEDOn(LED2);
    APM_MINI_LEDOn(LED3);

    APM_MINI_COMInit(COM2);
    USART1_Init();

    /** Init TxBuf*/
    for (int i = 0; i<BufSize; i++)
    {
        DMA_USART_TxBuf[i] = i;
    }

    /** Config channel5 of DMA */
    DMA_Disable(DMA1_CHANNEL_5);

    DMA_Rx_Init((uint32_t *)DMA_USART_RxBuf);

    USART_EnableDMA(USART1, USART_DMA_REQUEST_RX);

    /** data from usart2 send to usart1 */
    for (int i = 0; i<BufSize; i++)
    {
        /** USART send data*/
        while (USART_ReadStatusFlag(USART2, USART_FLAG_TXBE)==RESET);

        USART_TxData(USART2, DMA_USART_TxBuf[i]);
    }

    /** Data is ok then turn off LED2 */
    if (BufferCompare(DMA_USART_TxBuf, DMA_USART_RxBuf, BufSize) != FALSE)
    {
        APM_MINI_LEDOff(LED2);
    }

    for (;;)
    {
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
        Delay();
    }
}

/*!
 * @brief       USART Configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void USART1_Init()
{
    APM_MINI_COMInit(COM1);

    /** Enable SYSCFG Clock for Remaping DMA Channel*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    /** Remap USART1_RX Channel to DMA channel 5*/
    SYSCFG_EnableDMAChannelRemap(SYSCFG_DAM_REMAP_USART1RX);
}

/*!
 * @brief       DMA usart receive Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void DMA_Rx_Init(uint32_t* RxBuf)
{
    /** Enable DMA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA1);
    /** DMA Configure */
    DMA_Config_T dmaConfig;
    /** size of buffer*/
    dmaConfig.bufferSize = BufSize;
    /** set memory Data Size*/
    dmaConfig.memoryDataSize = DMA_MEMORY_DATASIZE_BYTE;
    /** Set peripheral Data Size*/
    dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_BYTE;
    /** Enable Memory Address increase*/
    dmaConfig.memoryInc = DMA_MEMORY_INC_ENABLE;
    /** Disable Peripheral Address increase*/
    dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    /** Reset Circular Mode*/
    dmaConfig.circular = DMA_CIRCULAR_DISABLE;
    /** Disable M2M*/
    dmaConfig.memoryTomemory = DMA_M2M_DISABLE;
    /** set priority*/
    dmaConfig.priority = DMA_PRIORITY_LEVEL_HIGHT;
    /** read from memory*/
    dmaConfig.direction = DMA_DIR_PERIPHERAL;
    /** Set memory Address*/
    dmaConfig.memoryAddress = (uint32_t)RxBuf;
    /** Set Peripheral Address*/
    dmaConfig.peripheralAddress = (uint32_t)&USART1->RXDATA;

    DMA_Config(DMA1_CHANNEL_5, &dmaConfig);
    /** Clear DMA TF flag*/
    DMA_ClearIntFlag(DMA1_INT_FLAG_TF5);
    /** Enable DMA Interrupt*/
    DMA_EnableInterrupt(DMA1_CHANNEL_5, DMA_INT_TFIE);

#if defined (APM32F030)
    NVIC_EnableIRQRequest(DMA1_CH4_5_IRQn, 2);
#elif defined (APM32F072)
    NVIC_EnableIRQRequest(DMA1_CH1_IRQn, 2);
#endif

    USART_ClearStatusFlag(USART1, USART_FLAG_TXC);

    DMA_Enable(DMA1_CHANNEL_5);

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
BOOL BufferCompare(uint8_t* buf1, uint8_t* buf2, uint8_t size)
{
    uint8_t i;

    for (i = 0; i < size; i++)
    {
        if (buf1[i] != buf2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*!
 * @brief       DMA_Interrupt
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void DMA_Isr(void)
{
    if (DMA_ReadStatusFlag(DMA1_FLAG_TF5))
    {
        /** do something*/
        DMA_ClearStatusFlag(DMA1_FLAG_TF5);
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
    volatile uint32_t delay = 0x3ffff;

    while (delay--);
}
