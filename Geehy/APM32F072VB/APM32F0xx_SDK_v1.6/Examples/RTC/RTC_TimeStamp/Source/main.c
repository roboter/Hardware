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
#include "apm32f0xx_rtc.h"
#include "apm32f0xx_pmu.h"
#include "Board.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** Delay */
void Delay(void);
/** RTC Init */
void RTC_Init(void);
/** RTC Eint */
void RTC_EintConfig(void);

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
    uint8_t Presec;
    RTC_DATE_T DateStruct;
    RTC_TIME_T TimeStruct;

    APM_MINI_LEDInit(LED2);
    APM_MINI_COMInit(COM2);

    RTC_Init();
    RTC_Reset();
    RTC_Init();
    RTC_EnableInit();

    /** Init Date 20/8/22/6*/
    DateStruct.year =  20;
    DateStruct.month = 8;
    DateStruct.date =  22;
    DateStruct.weekday = 6;
    RTC_ConfigDate(RTC_FORMAT_BIN,&DateStruct);
    Delay();

    /** Init Time 23:59:50*/
    TimeStruct.H12 = 12;
    TimeStruct.hours = 23;
    TimeStruct.minutes = 59;
    TimeStruct.seconds = 50;
    RTC_ConfigTime(RTC_FORMAT_BIN,&TimeStruct);
    Delay();

    /** RTC TimeStamp*/
    printf("\r\nConnect PC13 in the air to require a time stamp\r\n");

    /** RTC Eint Line Init*/
    RTC_EintConfig();

    /** Set Time Stamp */
    RTC_EnableTimeStamp(RTC_TIME_STAMPEDGE_RISING);

    /** Enable TimeStamp Interrupt*/
    RTC_EnableInterrupt(RTC_INT_FLAG_TS);
    NVIC_EnableIRQRequest(RTC_IRQn,2);

    RTC_DisableInit();


    for(;;)
    {
        Presec = TimeStruct.seconds;

        RTC_ReadTime(RTC_FORMAT_BIN,&TimeStruct);

        /** Read Date and Time per second*/
        if(Presec!=TimeStruct.seconds)
        {
            APM_MINI_LEDToggle(LED2);
            RTC_ReadDate(RTC_FORMAT_BIN,&DateStruct);
            printf(" \r\n date = 20%d / %d / %d / %d \r\n",
                    DateStruct.year,DateStruct.month,DateStruct.date,DateStruct.weekday);

            printf(" \r\n time : %d - %d - %d \r\n",
                    (TimeStruct.hours),(TimeStruct.minutes),(TimeStruct.seconds));
        }

    }
}

/*!
 * @brief       RTC Isr
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into RTC_IRQHandler in apm32f0xx_int.h
 */

void RTC_Isr(void)
{
    RTC_DATE_T dateStruct;
    RTC_TIME_T timeStruct;

    if(RTC_ReadIntFlag(RTC_INT_FLAG_TS)==SET)
    {
        RTC_ReadTimeDate(RTC_FORMAT_BIN,&timeStruct,&dateStruct);
        printf("\r\nRTC_time_Stamp : %d/%d/%d , %d-%d-%d\r\n",
            dateStruct.year,dateStruct.month,dateStruct.date,
            timeStruct.hours,timeStruct.minutes,timeStruct.seconds);
        /** Clear RTC TS flag*/
        RTC_ClearIntFlag(RTC_INT_FLAG_TS);
        /** Clear EINT RTC flag*/
        EINT_ClearIntFlag(EINT_LINE19);
    }
}

/*!
 * @brief       RTC_Eint Line configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RTC_EintConfig(void)
{
    EINT_Config_T   eintConfig;
    GPIO_Config_T   gpioConfig;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOC);

    gpioConfig.pin  = GPIO_PIN_0;
    gpioConfig.mode = GPIO_MODE_IN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &gpioConfig);

    gpioConfig.pin  = GPIO_PIN_13;
    gpioConfig.mode = GPIO_MODE_IN;
    gpioConfig.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOC, &gpioConfig);

    eintConfig.line = EINT_LINE19 | EINT_LINE17;
    eintConfig.mode = EINT_MODE_INTERRUPT;
    eintConfig.trigger = EINT_TRIGGER_RISING;
    eintConfig.lineCmd = ENABLE;
    EINT_Config(&eintConfig);

    NVIC_EnableIRQRequest(RTC_IRQn,0);
}

/*!
 * @brief       RTC Configuration
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void RTC_Init(void)
{
    RTC_Config_T Struct;

    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);

    PMU_EnableBackupAccess();

    RCM_EnableLSI();

    while(RCM_ReadStatusFlag(RCM_FLAG_LSIRDY) == RESET)
    {
    }

    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);

    RCM_EnableRTCCLK();

    RTC_DisableWriteProtection();

    RTC_WaitForSynchro();

    /** LSI */
    RTC_ConfigStructInit(&Struct);
    Struct.AsynchPrediv = 0X63;
    Struct.SynchPrediv  = 0X18F;

    RTC_Config(&Struct);

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
    volatile uint32_t delay = 0x1Fff5;

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



