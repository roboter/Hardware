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
#include "apm32f0xx_spi.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** Buffsize*/
#define BuffSize 56
/** SPI TX Buffer*/
uint8_t SPI_Buffer_TX[BuffSize] =
{
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
    0x01,0x02,0x03,0x04,0x05,0x06,0X07,
};

/** Delay */
void Delay(uint16_t count);
/** SPI Init */
void APM_MINI_SPIInit(void);
/** Buffer Compare*/
BOOL BufferCompare(uint8_t *buf1, uint8_t *buf2, uint8_t size);


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
    /** index of TxData*/
    volatile uint8_t TxIdx = 0;
    /** index of RxData*/
    volatile uint8_t RxIdx = 0;
    /** SPI Receive Buffer*/
    uint8_t SPI_Buffer_RX[BuffSize] = {0x00};

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM2);
    APM_MINI_SPIInit();

    printf("I am Master\r\n");

    /** Low Down NSS for communication*/
    GPIO_ClearBit(GPIOA, GPIO_PIN_4);

    while(TxIdx < BuffSize)
    {
        while(SPI_ReadStatusFlag(SPI1,SPI_FLAG_TXBE)==RESET);
        SPI_I2S_TxData16(SPI1,SPI_Buffer_TX[TxIdx++]);

        while(SPI_ReadStatusFlag(SPI1,SPI_FLAG_RXBNE)==RESET);
        SPI_Buffer_RX[RxIdx++] = SPI_I2S_RxData16(SPI1);

    }
     for(int i =0;i<BuffSize;i++)
    {
        if(i%7 == 0)
        {
            printf("\r\n");
        }
        printf(" %02x ,",SPI_Buffer_RX[i]);

    }
    /** Set NSS high for close communication*/
    GPIO_SetBit(GPIOA, GPIO_PIN_4);

    /** Compare Buffer*/
    if(BufferCompare(SPI_Buffer_TX,SPI_Buffer_RX,BuffSize)==TRUE)
    {
        APM_MINI_LEDOn(LED2);
    }

    for(;;)
    {
       Delay(0x5f5f);
       APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       SPI Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_SPIInit(void)
{

    GPIO_Config_T gpioConfig;
    SPI_Config_T spiConfig;

    /** Enable related clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

     /** Config alter function*/
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);

    /** config PIN_5->SCK , PIN_7->MOSI*/
    gpioConfig.pin =  GPIO_PIN_5 | GPIO_PIN_7;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &gpioConfig);

     /** config PIN_4->NSS*/
    gpioConfig.pin =  GPIO_PIN_4;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.mode = GPIO_MODE_OUT;
    GPIO_Config(GPIOA, &gpioConfig);
    GPIO_SetBit(GPIOA, GPIO_PIN_4);

    /** config PIN_6  MISO*/
    gpioConfig.pin = GPIO_PIN_6;
    gpioConfig.mode = GPIO_MODE_AF;
    gpioConfig.pupd = GPIO_PUPD_PU;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioConfig);

    /** SPI RESET*/
    SPI_Reset(SPI1);
    SPI_ConfigStructInit(&spiConfig);

    /** SPI configuration*/
    /** Set Clock polarity is Low, but Slave is High*/
    spiConfig.polarity = SPI_CLKPOL_LOW;

    /** select master mode*/
    spiConfig.mode = SPI_MODE_MASTER;

    /** SPI Clock Phase is 1EDGE, but Slave is 1EDGE*/
    spiConfig.phase = SPI_CLKPHA_1EDGE;

    /** Enable Software slave control */
    spiConfig.slaveSelect = SPI_SSC_ENABLE;

    /** Set SPI BaudRate divider*/
    spiConfig.baudrateDiv = SPI_BAUDRATE_DIV_256;

    /** SPI data length*/
    spiConfig.length = SPI_DATA_LENGTH_16B;

    /** Set internal slave*/
    SPI_EnableInternalSlave(SPI1);
    SPI_Config(SPI1, &spiConfig);
    SPI_ConfigFIFOThreshold(SPI1, SPI_RXFIFO_QUARTER);

    SPI_Enable(SPI1);
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








