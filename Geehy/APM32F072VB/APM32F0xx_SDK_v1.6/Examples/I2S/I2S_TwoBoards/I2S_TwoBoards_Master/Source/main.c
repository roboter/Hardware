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

/** printf function configs to USART2 */
#define DEBUG_USART  USART2

/** define KEY1,KEY2 EXTI LINE */
#define KEY1_BUTTON_EXTI_LINE  EINT_LINE1

/** Buffsize */
#define BuffSize 32

/** KeyState */
uint8_t KeyState = RESET;

/** index of TxData*/
volatile uint8_t TxIdx = 0;

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

/** Delay */
void Delay(uint16_t count);
/** I2S Master Init */
void APM_MINI_I2S_Master_Init(void);

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

    printf("\r\n I am Master\r\n");

    /** I2S Master Transmitter configuration */
    APM_MINI_I2S_Master_Init();

    for (;;)
    {
        if (KeyState == SET)
        {
            printf(" I2S Master Transmitter Buffer:");

            while (TxIdx < BuffSize)
            {
                while (SPI_ReadStatusFlag(SPI1, SPI_FLAG_TXBE)==RESET);

                SPI_I2S_TxData16(SPI1, I2S_Buffer_TX[TxIdx++]);

                if (TxIdx%8 == 0)
                {
                    printf("\r\n");
                }

                printf(" 0x%04X,", I2S_Buffer_TX[TxIdx]);
            }

            TxIdx = 0;
            KeyState = RESET;
        }

        Delay(0xFFFF);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       I2S Master Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_I2S_Master_Init(void)
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
    i2sConfig.mode       =  I2S_MODE_MASTER_TX;
    i2sConfig.standard   =  I2S_STANDARD_PHILIPS;
    i2sConfig.length     =  I2S_DATA_LENGTH_16B;
    i2sConfig.MCLKOutput =  I2S_MCLK_OUTPUT_DISABLE;
    i2sConfig.audioDiv   =  I2S_AUDIO_DIV_8K;
    i2sConfig.polarity   =  I2S_CLKPOL_LOW;

    SPI_Reset(SPI1);
    I2S_Config(SPI1, &i2sConfig);
    I2S_Enable(SPI1);
}

/**
 * @brief       The interrupt will happen when the button is press.
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function should put into EINT0_1_IRQHandler() in apm32f0xx_int.c
 */
void APM_MINI_KEY0_Isr(void)
{
    if (EINT_ReadStatusFlag(KEY1_BUTTON_EXTI_LINE)==SET)
    {
        KeyState = SET;
        EINT_ClearStatusFlag(KEY1_BUTTON_EXTI_LINE);
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
