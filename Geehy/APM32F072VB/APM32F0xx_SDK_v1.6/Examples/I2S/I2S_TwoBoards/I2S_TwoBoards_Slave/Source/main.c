/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.0
 *
 * @date        2021-10-13
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
#include "apm32f0xx_spi.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** Buffsize*/
#define BuffSize 32

/** I2S TX Buffer */
uint16_t I2S_Buffer_TX[BuffSize] =
{
    0x0102, 0x0304, 0x0506, 0x0707,
    0x1112, 0x1314, 0x1516, 0x1717,
    0x2122, 0x2324, 0x2526, 0x2727,
    0x3132, 0x3334, 0x3536, 0x3737,
    0x4142, 0x4344, 0x4546, 0x4747,
    0x5152, 0x5354, 0x5556, 0x5757,
    0x6162, 0x6364, 0x6566, 0x6767,
    0x7172, 0x7374, 0x7576, 0x7777,
};

/** index of RxData*/
volatile uint8_t RxIdx = 0;
/** SPI Receive Buffer*/
uint16_t I2S_Buffer_RX[BuffSize] = {0x00};

/** Delay */
void Delay(uint16_t count);
/** I2S Slave Init */
void APM_MINI_I2S_Slave_Init(void);
/** Buffer Compare*/
BOOL BufferCompare(uint16_t* buf1, uint16_t* buf2, uint8_t size);

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

    printf("\r\n I am Slave\r\n");

    /** I2S Slave Receiver configuration */
    APM_MINI_I2S_Slave_Init();

    for (;;)
    {

        if (RxIdx == BuffSize)
        {
            RxIdx = 0;
            SPI_EnableInterrupt(SPI1, SPI_INT_RXBNEIE);

            printf(" I2S Slave Receiver Buffer:");

            for (int i =0; i<BuffSize; i++)
            {
                if (i%8 == 0)
                {
                    printf("\r\n");
                }

                printf(" 0x%04X,", I2S_Buffer_RX[i]);
            }

            /** Compare Buffer*/
            if (BufferCompare(I2S_Buffer_TX, I2S_Buffer_RX, BuffSize)==TRUE)
            {
                APM_MINI_LEDOn(LED2);
            }
            else
            {
                APM_MINI_LEDOff(LED2);
            }
        }

        Delay(0xFFFF);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       I2S Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_I2S_Slave_Init(void)
{
    GPIO_Config_T gpioConfig;
    I2S_Config_T i2sConfig;

    /** Enable related clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /** config PIN_4->WS, PIN_5->CK, PIN_7->SD*/
    gpioConfig.pin =  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    GPIO_Config(GPIOA, &gpioConfig);

    /** Config alter function*/
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_4, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);

    /** I2S configuration*/
    i2sConfig.mode       =  I2S_MODE_SLAVER_RX;
    i2sConfig.standard   =  I2S_STANDARD_PHILIPS;
    i2sConfig.length     =  I2S_DATA_LENGTH_16B;
    i2sConfig.MCLKOutput =  I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig.audioDiv   =  I2S_AUDIO_DIV_8K;
    i2sConfig.polarity   =  I2S_CLKPOL_LOW;

    SPI_Reset(SPI1);
    I2S_Config(SPI1, &i2sConfig);

    SPI_EnableInterrupt(SPI1, SPI_INT_RXBNEIE);

    NVIC_EnableIRQRequest(SPI1_IRQn, 2);

    I2S_Enable(SPI1);
}

/*!
 * @brief       I2S Isr
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into SPI1_IRQHandler in apm32f0xx_int.c
 */
void I2S_Isr(void)
{
    if (SPI_ReadStatusFlag(SPI1, SPI_FLAG_RXBNE) == SET)
    {
        I2S_Buffer_RX[RxIdx++] = SPI_I2S_RxData16(SPI1);
    }

    if (RxIdx == BuffSize)
    {
        SPI_DisableInterrupt(SPI1, SPI_INT_RXBNEIE);
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
void Delay(uint16_t count)
{
    volatile uint32_t delay = count;

    while (delay--);
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
BOOL BufferCompare(uint16_t* buf1, uint16_t* buf2, uint8_t size)
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
