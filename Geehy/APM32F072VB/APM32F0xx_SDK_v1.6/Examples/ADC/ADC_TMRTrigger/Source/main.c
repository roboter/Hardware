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

#include "stdio.h"
#include "Board.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_adc.h"
#include "apm32f0xx_tmr.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

/** Delay */
void Delay(void);
/** ADC Init */
void ADCInit(void);
/** TMR1 Init*/
void TMR1Init(void);

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
    uint32_t adcData = 0;
    uint32_t voltage = 0;

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM1);

    /** TMR1 Configuration */
    TMR1Init();

    /** ADC Configuration */
    ADCInit();

    /** Wait until ADC is ready */
    while (!ADC_ReadStatusFlag(ADC_FLAG_ADRDY));

    ADC_StartConversion();

    for (;;)
    {
        while (ADC_ReadStatusFlag(ADC_FLAG_CC) == RESET);

        /** Read ADC Conversion value*/
        adcData = ADC_ReadConversionValue();
        /**  voltage(mV) =  adcData * (3300mV / 4095) */
        voltage = (adcData*3300)/4095;
        /** output to serial port*/
        printf("\r\n volatage : %d\r\n", voltage);
    }
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
    adcConfig.dataAlign = ADC_DATA_ALIGN_RIGHT;
    /** Set scanDir*/
    adcConfig.scanDir = ADC_SCAN_DIR_UPWARD;
    /** Set convMode continous*/
    adcConfig.convMode   = ADC_CONVERSION_SINGLE;
    /** Set extTrigConv*/
    adcConfig.extTrigConv  = ADC_EXT_TRIG_CONV_TRG1;
    /** Set TrigEdge*/
    adcConfig.extTrigEdge = ADC_EXT_TRIG_EDGE_RISING;

    ADC_Config(&adcConfig);
    ADC_ConfigChannel(ADC_CHANNEL_0, ADC_SAMPLE_TIME_239_5);

    /** Calibration*/
    ADC_ReadCalibrationFactor();
    /** Enable ADC*/
    ADC_Enable();
}

/*!
 * @brief       TMR1 Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void TMR1Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  occonfig;

    /** Enable Clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /** Set divider = 47.So TMR1 clock freq ~= 48/(47 + 1) = 1MHZ */
    timeBaseConfig.div = 47 ;
    /** Set counter = 0xff */
    timeBaseConfig.period = 0xFF;
    /** Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /** PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /** Idle State is reset */
    occonfig.OC_Idlestate  = TMR_OCIDLESTATE_RESET;
    /** NIdle State is reset */
    occonfig.OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
    /** Enable CH1N ouput */
    occonfig.OC_OutputNState =  TMR_OUTPUT_NSTATE_ENABLE;
    /** Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /** CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /** CH1N polarity is high */
    occonfig.OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
    /** Set compare value = 0x01 */
    occonfig.Pulse = 0x1;
    TMR_OC4Config(TMR1, &occonfig);

    /** Enable PWM output */
    TMR_EnablePWMOutputs(TMR1);
    /**  Enable TMR1  */
    TMR_Enable(TMR1);
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
