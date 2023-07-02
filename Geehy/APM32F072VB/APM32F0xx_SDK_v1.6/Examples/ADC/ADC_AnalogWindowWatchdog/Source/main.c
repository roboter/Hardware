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

#include "stdio.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_adc.h"
#include "Board.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

/** The analog watchdog High threshold : (awhtVoltage*3300)/4096 */
#define awhtVoltage  0xA00

/** The analog watchdog low threshold : (awltVoltage*3300)/4096 */
#define awltVoltage  0x800

/** Delay */
void Delay(void);
/** ADC Init */
void ADCInit(void);

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
    APM_MINI_LEDOff(LED2);

    APM_MINI_LEDInit(LED3);
    APM_MINI_LEDOff(LED3);

    APM_MINI_COMInit(COM1);
    ADCInit();

    printf("The analog watchdog High threshold : %d mV\r\n", (awhtVoltage*3300)/4096);
    printf("The analog watchdog low threshold  : %d mV\r\n", (awltVoltage*3300)/4096);

    /** Wait until ADC is ready */
    while (!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));

    ADC_StartConversion();

    for (;;)
    {

    }
}

/*!
 * @brief       ADC AnalogWatchdog Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADCAnalogWatchdogInit(void)
{
    /**  Enables the analog watchdog */
    ADC_EnableAnalogWatchdog();

    /** set analog watchdog low threshold*/
    ADC_AnalogWatchdogLowThreshold(awltVoltage);

    /** set analog watchdog High threshold*/
    ADC_AnalogWatchdogHighThreshold(awhtVoltage);

    /** Enables the Analog Watchdog Single Channel */
    ADC_EnableAnalogWatchdogSingleChannel();

    /** ADC analog watchdog channel selection : AWD Channel 0*/
    ADC_AnalogWatchdogSingleChannel(ADC_ANALG_WDT_CHANNEL_0);
}

/*!
 * @brief       ADC_Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ADCInit(void)
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
    adcConfig.dataAlign  = ADC_DATA_ALIGN_RIGHT;
    /** Set scanDir*/
    adcConfig.scanDir    = ADC_SCAN_DIR_UPWARD;
    /** Set convMode continous*/
    adcConfig.convMode   = ADC_CONVERSION_CONTINUOUS;
    /** Set extTrigConv*/
    adcConfig.extTrigConv  = ADC_EXT_TRIG_CONV_TRG0;
    /** Set TrigEdge*/
    adcConfig.extTrigEdge    = ADC_EXT_TRIG_EDGE_NONE;

    ADC_Config(&adcConfig);
    ADC_ConfigChannel(ADC_CHANNEL_0, ADC_SAMPLE_TIME_239_5);

    /** ADC AnalogWatchdog Init */
    ADCAnalogWatchdogInit();

    /** Enable Interrupt*/
    ADC_EnableInterrupt(ADC_INT_CS);
    ADC_EnableInterrupt(ADC_INT_AWD);

    #if defined (APM32F030)
    NVIC_EnableIRQRequest(ADC1_IRQn, 2);
    #elif defined (APM32F072)
    NVIC_EnableIRQRequest(ADC1_COMP_IRQn, 2);
    #endif

    /** Calibration*/
    ADC_ReadCalibrationFactor();
    /** Enable ADC*/
    ADC_Enable();

}

/*!
 * @brief       ADC_Isr
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into ADC1_IRQHandler in apm32f0xx_int.c
 */
void ADC_Isr()
{
    uint32_t adcData = 0;
    uint32_t voltage = 0;

    APM_MINI_LEDOff(LED2);
    APM_MINI_LEDOff(LED3);

    if (ADC_ReadIntFlag(ADC_INT_FLAG_CS) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_CS);
        /** Read ADC Conversion value*/
        adcData = ADC_ReadConversionValue();
        /**  voltage(mV) =  adcData * (3300mV / 4095) */
        voltage = (adcData*3300)/4095;
        /** output to serial port*/
        printf("\r\n volatage : %d  mV\r\n", voltage);
    }

    if (ADC_ReadIntFlag(ADC_INT_FLAG_AWD) == SET)
    {
        ADC_ClearIntFlag(ADC_INT_FLAG_AWD);

        if (adcData < awltVoltage)
        {
            APM_MINI_LEDOn(LED2);
            APM_MINI_LEDOff(LED3);
        }
        else if (adcData > awhtVoltage)
        {
            APM_MINI_LEDOff(LED2);
            APM_MINI_LEDOn(LED3);
        }

        printf("\r\n Analog watchdog interrupt !\r\n");
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
    volatile uint32_t delay = 0xff5;

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
