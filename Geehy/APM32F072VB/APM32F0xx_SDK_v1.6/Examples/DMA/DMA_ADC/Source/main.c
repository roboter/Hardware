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
#include "apm32f0xx_dma.h"
#include "apm32f0xx_adc.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** define Tramismit Buf Size*/
#define BufSize 0x100

/** Delay */
void Delay(void);
/** ADC Init */
void APM_MINI_ADC_Init(void);
/** DMA Init */
void APM_MINI_DMA_Init(uint32_t* Buf);

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
     /** DMA value from ADC*/
    uint32_t DMA_ConvertedValue = 0;
     /** ADC convert to volatage*/
    float    ADC_ConvertedValue = 0;

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM2);

    APM_MINI_ADC_Init();
    APM_MINI_DMA_Init(&DMA_ConvertedValue);

    /** start conversion*/
    while(!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));
    ADC_StartConversion();

    for(;;)
    {
         /** convert value*/
        ADC_ConvertedValue = (float)DMA_ConvertedValue/4096*3.3;
        printf("\r\n  AD value = 0x%04X \r\n", DMA_ConvertedValue);
        printf("\r\n  AD value = %f V \r\n"  ,ADC_ConvertedValue);
        Delay();
    }
}

/*!
 * @brief       DMA_ADC Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_ADC_Init()
{
    GPIO_Config_T gpioConfig;
    ADC_Config_T  adcConfig;

    /** RCM Enable*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC1);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    /** GPIO Configuration */
    gpioConfig.pin = GPIO_PIN_0;
    gpioConfig.mode = GPIO_MODE_AN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &gpioConfig);
    /** ADC Configuration */
    ADC_Reset();
    ADC_ConfigStructInit(&adcConfig);
    /** Set resolution*/
    adcConfig.resolution = ADC_RESOLUTION_12B;
    /** Set dataAlign*/
    adcConfig.dataAlign = ADC_DATA_ALIGN_RIGHT;
    /** Set scanDir*/
    adcConfig.scanDir = ADC_SCAN_DIR_UPWARD;
    /** Set convMode continous*/
    adcConfig.convMode = ADC_CONVERSION_CONTINUOUS;
    /** Set extTrigConv*/
    adcConfig.extTrigConv = ADC_EXT_TRIG_CONV_TRG0;
    /** Set TrigEdge*/
    adcConfig.extTrigEdge = ADC_EXT_TRIG_EDGE_NONE;

    ADC_Config(&adcConfig);

    ADC_ConfigChannel(ADC_CHANNEL_0, ADC_SAMPLE_TIME_239_5);

    /** Calibration*/
    ADC_ReadCalibrationFactor();

    ADC_EnableDMA();
    /** Enable ADC*/
    ADC_Enable();
 }

 /*!
 * @brief       DMA Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_DMA_Init(uint32_t* Buf)
{
    /** Enable DMA clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_DMA1);
    /** DMA Configure */
    DMA_Config_T dmaConfig;
    /** size of buffer*/
    dmaConfig.bufferSize = 1;
    /** set memory Data Size*/
    dmaConfig.memoryDataSize = DMA_MEMORY_DATASIZE_HALFWORD;
    /** Set peripheral Data Size*/
    dmaConfig.peripheralDataSize = DMA_PERIPHERAL_DATASIZE_HALFWORD;
    /** Enable Memory Address increase*/
    dmaConfig.memoryInc = DMA_MEMORY_INC_DISABLE;
    /** Disable Peripheral Address increase*/
    dmaConfig.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    /** Reset Circular Mode*/
    dmaConfig.circular = DMA_CIRCULAR_ENABLE;
    /** Disable M2M*/
    dmaConfig.memoryTomemory = DMA_M2M_DISABLE;
    /** set priority*/
    dmaConfig.priority = DMA_PRIORITY_LEVEL_HIGHT;
    /** read from peripheral*/
    dmaConfig.direction = DMA_DIR_PERIPHERAL;
    /** Set memory Address*/
    dmaConfig.memoryAddress = (uint32_t)Buf;
    /** Set Peripheral Address*/
    dmaConfig.peripheralAddress = (uint32_t)&ADC->DATA;

    DMA_Config(DMA1_CHANNEL_1,&dmaConfig);
    /** Clear DMA TF flag*/
    DMA_ClearIntFlag(DMA1_INT_FLAG_TF1);
    /** Enable DMA Interrupt*/
    DMA_EnableInterrupt(DMA1_CHANNEL_1,DMA_INT_TFIE);

    NVIC_EnableIRQRequest(DMA1_CH1_IRQn,2);

    DMA_Enable(DMA1_CHANNEL_1);
}

/*!
 * @brief       DMA_Interrupt
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into DMA1_CH1_IRQHandler in apm32f0xx_int.c
 */
void DMA_Isr(void)
{
    if(DMA_ReadStatusFlag(DMA1_FLAG_TF1))
    {
        /** do something*/
        DMA_ClearStatusFlag(DMA1_FLAG_TF1);
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
    volatile uint32_t delay = 0xFFFFF;

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
