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
#include "apm32f0xx_tmr.h"
#include "apm32f0xx_misc.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** TMR1 Input capture Init */
void APM_MINI_TMR1_Input_Capture_Init(void);
/** COC Init */
void ClockOutputInit(void);
/** Delay */
void Delay(void);

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
    /** input capture Value*/
    uint16_t icValue[2];
    /** TMR1 clock Frequent*/
    uint32_t clockFreqTMR1;
    /** LSI frequent*/
    uint32_t freqLSI;

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_COMInit(COM2);

    APM_MINI_TMR1_Input_Capture_Init();
    ClockOutputInit();
    /**  TMR1 clock = Master clock  */
    clockFreqTMR1 = RCM_ReadSYSCLKFreq();

    /** Turn LED2 on */
    APM_MINI_LEDOn(LED2);
    /** Turn LED3 off */
    APM_MINI_LEDOff(LED3);

    /**  Clear Channel3 Input Capture flag  */
    TMR_ClearStatusFlag(TMR1, TMR_FLAG_CH3);
    /**  Wait end of capture */
    while(TMR_ReadStatusFlag(TMR1,TMR_FLAG_CH3) == RESET);
    /**  Read capture value */
    icValue[0] = TMR_ReadCaputer3(TMR1);

    TMR_ClearStatusFlag(TMR1, TMR_FLAG_CH3);
    while(TMR_ReadStatusFlag(TMR1,TMR_FLAG_CH3) == RESET);
    icValue[1] = TMR_ReadCaputer3(TMR1);

    /**  calculate the LSI clock frequency  */
    freqLSI = (clockFreqTMR1) / (icValue[1]- icValue[0]);

    printf("freq : %d\r\n\r\n",freqLSI);
    /**  if LSI clock frequency in [39~41]Khz  */
    if((freqLSI < 45000) && (freqLSI > 39000))
    {
         APM_MINI_LEDOff(LED2);
    }

    for(;;)
    {
        Delay();

        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       TMR1 Input_Capture Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR1_Input_Capture_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_ICConfig_T  ICconfigstruct;
    GPIO_Config_T   gpioconfig;
    /** Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    /**  Connect TMR1 to CH3 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_PIN2);
    gpioconfig.mode = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin  =  GPIO_PIN_10;
    gpioconfig.pupd = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA,&gpioconfig);

    /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /** Set divider = 0 .So TMR1 clock freq ~= 48/( 95 + 1) = 0.5MHZ */
    timeBaseConfig.div = 7 ;
    /** Set counter = 0xffff */
    timeBaseConfig.period = 0xFFFF;
    /** Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR1,&timeBaseConfig);

    /** Connect InputCapture channel to TMR1_CHANNEL_3*/
    ICconfigstruct.channel  = TMR_CHANNEL_3;
    /**  Set Input Capture filter  */
    ICconfigstruct.ICfilter = 0x00;
    /**  Set Input Capture polarity  */
    ICconfigstruct.ICpolarity  = TMR_IC_POLARITY_RISING;
    /**  Set Input Capture divider  */
    ICconfigstruct.ICprescaler = TMR_ICPSC_DIV8;
    /**  Set Input Capture selection  */
    ICconfigstruct.ICselection = TMR_IC_SELECTION_DIRECT_TI;
    TMR_ICConfig(TMR1,&ICconfigstruct);

    /**  Enable TMR1  */
    TMR_Enable(TMR1);
}

/*!
 * @brief       COC Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void ClockOutputInit()
{
    GPIO_Config_T gpioconfig;

    /**  Connect RCM Clock output */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN0);
    gpioconfig.mode    =  GPIO_MODE_AF;
    gpioconfig.outtype =  GPIO_OUT_TYPE_PP;
    gpioconfig.pin     =  GPIO_PIN_8;
    gpioconfig.pupd    =  GPIO_PUPD_NO;
    gpioconfig.speed   =  GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioconfig);

    /**  LSI clock as clock output  */
#if defined (APM32F030) || defined (APM32F051)
    RCM_ConfigCOC(RCM_COC_LSI);
#else
    RCM_ConfigCOC(RCM_COC_LSI,RCM_COC_DIV_1);
#endif

    /**  Enable LSI clock*/
    RCM_EnableLSI();
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
    volatile uint32_t delay = 0xffff5;

    while(delay--);
}

/*!
 * @brief       fpuc
 *
 * @param       None
 *
 * @retval      None
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
