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
#include "apm32f0xx_dac.h"
#include "apm32f0xx_adc.h"
#include "apm32f0xx_misc.h"
#include "stdio.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

/** Delay */
void Delay(uint32_t count);
/** DAC init */
void DAC_Init(void);
/** ADC init */
void ADC_Init(void);

/** use to generate analog signal for DAC*/
uint16_t dacData = 0;

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

    DAC_Init();
    ADC_Init();

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
 * @brief       DAC Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void DAC_Init()
{
    GPIO_Config_T   gpioConfig;
    DAC_Config_T    dacConfig;

    /** Enable GPIOA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);

    /** DAC out PA4 pin configuration */
    GPIO_ConfigStructInit(&gpioConfig);
    gpioConfig.mode    = GPIO_MODE_AN;
    gpioConfig.pupd    = GPIO_PUPD_NO;
    gpioConfig.pin     = GPIO_PIN_4;
    GPIO_Config(GPIOA,&gpioConfig);

    /** Enable DAC clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_DAC);

    /** DAC channel 1 configuration */
    DAC_ConfigStructInit(&dacConfig);
    dacConfig.trigger           = DAC_TRIGGER_NONE;
    dacConfig.waveGeneration    = DAC_WAVE_GENERATION_NONE;
    dacConfig.maskAmplitudeSelect = DAC_LFSRUNAMASK_BIT0;
    dacConfig.outputBuff        = DAC_OUTPUTBUFF_ENABLE;
    DAC_Config(DAC_CHANNEL_1,&dacConfig);

    /** Enable DAC channel 1 */
    DAC_Enable(DAC_CHANNEL_1);
}

/*!
 * @brief       ADC Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_Init(void)
{
    GPIO_Config_T   gpioConfig;
    ADC_Config_T    adcConfig;

    /** Enable GPIOA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOC);

    /** ADC channel 0 configuration */
    GPIO_ConfigStructInit(&gpioConfig);
    gpioConfig.mode    = GPIO_MODE_AN;
    gpioConfig.pupd    = GPIO_PUPD_NO;
    gpioConfig.pin     = GPIO_PIN_0;
    GPIO_Config(GPIOC,&gpioConfig);

    /** Enable ADC clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC1);

    /** ADC configuration */
    ADC_Reset();
    ADC_ConfigStructInit(&adcConfig);
    adcConfig.resolution  = ADC_RESOLUTION_12B;
    adcConfig.convMode    = ADC_CONVERSION_CONTINUOUS;
    adcConfig.dataAlign   = ADC_DATA_ALIGN_RIGHT;
    adcConfig.extTrigEdge = ADC_EXT_TRIG_EDGE_NONE;
    adcConfig.scanDir     = ADC_SCAN_DIR_UPWARD;
    ADC_Config(&adcConfig);

    /** ADC channel 10 Convert configuration */
    ADC_ConfigChannel(ADC_CHANNEL_10,ADC_SAMPLE_TIME_239_5);

    /** Enable complete conversion interupt */
    ADC_EnableInterrupt(ADC_INT_CC);

    /** NVIC configuration */
    NVIC_EnableIRQRequest(ADC1_COMP_IRQn,0);

    /** Enable ADC */
    ADC_Enable();

    /** Wait the ADC ready flag */
    while(!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));

    /** ADC start conversion */
    ADC_StartConversion();
}

/*!
 * @brief       ADC interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADC_Isr(void)
{
    uint16_t adcData = 0;
    uint16_t voltage = 0;

    /** generate analog signal*/
    DAC_ConfigChannel1Data(DAC_ALIGN_12B_R,dacData);

    if (dacData >= 0x0FFF )
    {
        dacData = 0;
    }
    dacData += 0x7F;

    if(ADC_ReadIntFlag(ADC_INT_FLAG_CC))
    {
        adcData = ADC_ReadConversionValue();

        voltage = (adcData*3300)/4095;
        printf("\r\n voltage : %d mV\r\n", voltage);

        /**  voltage greater than 3100mv */
        if(voltage > 3100)
        {
            APM_MINI_LEDOn(LED2);
            APM_MINI_LEDOff(LED3);
        }
        /**  voltage less than 800mv */
        else if(voltage < 800)
        {
            APM_MINI_LEDOn(LED3);
            APM_MINI_LEDOff(LED2);
        }
        /**  800mv <= voltage <= 3100 */
        else
        {
            APM_MINI_LEDOn(LED2);
            APM_MINI_LEDOn(LED3);
        }

        Delay(0x3FFFF);

        ADC_ClearIntFlag(ADC_INT_FLAG_CC);
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
