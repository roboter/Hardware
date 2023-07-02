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
#include "apm32f0xx_rtc.h"
#include "apm32f0xx_pmu.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/** Delay */
void Delay(void);
/** RTC Init */
void RTC_Init(void);

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
    uint32_t data;
    RTC_DATE_T DateStruct;
    RTC_TIME_T TimeStruct;

    APM_MINI_LEDInit(LED2);
    APM_MINI_COMInit(COM2);

    /** RTC Reset */
    RTC_Init();
    RTC_Reset();
    RTC_Init();

    /** RTC Enable Init*/
    RTC_EnableInit();

    RTC_ConfigDateStructInit(&DateStruct);

    /** First time Init*/
    if((RTC_ReadBackup(RTC_BAKP_DATA4)&&0X01)==RESET)
    {

        /** Init Date 20/8/22/6*/
        DateStruct.year =  20;
        DateStruct.month = 8;
        DateStruct.date =  22;
        DateStruct.weekday = 6;
        RTC_ConfigDate(RTC_FORMAT_BIN,&DateStruct);
        Delay();

        RTC_WriteBackup(RTC_BAKP_DATA1,RTC->DATE);
        Delay();

        RTC_WriteBackup(RTC_BAKP_DATA4,0X01);
    }
    /** Read Date information from Backup*/
   else
    {
        data = RTC_ReadBackup(RTC_BAKP_DATA1);
        DateStruct.year =  data>>16;
        DateStruct.month = (data>>8)&0x0f;
        DateStruct.date =  data&0xff;
        DateStruct.weekday = (data>>13)&0x07;
        RTC_ConfigDate(RTC_FORMAT_BCD,&DateStruct);
        Delay();
    }

    /** First time Init*/
    if((RTC_ReadBackup(RTC_BAKP_DATA3)&&0X01)==RESET)
    {
        TimeStruct.H12 = 12;
        TimeStruct.hours = 23;
        TimeStruct.minutes = 59;
        TimeStruct.seconds = 50;
        RTC_ConfigTime(RTC_FORMAT_BIN,&TimeStruct);
        Delay();
        RTC_WriteBackup(RTC_BAKP_DATA0,RTC->TIME);
        Delay();
        RTC_WriteBackup(RTC_BAKP_DATA3,0X01);
    }
    /** Read Time information from Backup */
   else
   {
        data = RTC_ReadBackup(RTC_BAKP_DATA0);
        TimeStruct.hours = data>>16;
        TimeStruct.minutes = (data>>8)&0xff;
        TimeStruct.seconds = (data)&0xff;
        RTC_ConfigTime(RTC_FORMAT_BCD,&TimeStruct);
        Delay();
   }

    /** Wait is neccessary*/
    Delay();

   /** RTC Disable Init */
    RTC_DisableInit();

    for(;;)
    {
        /** Read last Time*/
        Presec = TimeStruct.seconds;

        /** Read time*/
        RTC_ReadTime(RTC_FORMAT_BIN,&TimeStruct);

        /** If pass 1 second */
        if(Presec!=TimeStruct.seconds)
        {
            APM_MINI_LEDToggle(LED2);

            /** Read Date */
            RTC_ReadDate(RTC_FORMAT_BIN,&DateStruct);

            /** Write DATE information to Backup*/
            RTC_WriteBackup(RTC_BAKP_DATA1,RTC->DATE);

            printf(" \r\n date = 20%d / %d / %d / %d \r\n",
                    DateStruct.year,DateStruct.month,DateStruct.date,DateStruct.weekday);

            /** Write TIME information to Backup*/
            RTC_WriteBackup(RTC_BAKP_DATA0,RTC->TIME);
            printf(" \r\n time : %d - %d - %d \r\n",
                    (TimeStruct.hours),(TimeStruct.minutes),(TimeStruct.seconds));
        }

    }
}


/*!
 * @brief       RTC Init
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

    /** Enable PMU Periph Clock*/
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);

    /** Backup Access*/
    PMU_EnableBackupAccess();

    /** Enable LSI */
    RCM_EnableLSI();

    /** Wait until LSI is ready*/
    while(RCM_ReadStatusFlag(RCM_FLAG_LSIRDY) == RESET)
    {
    }
    /** Select LICT as RCM clock*/
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);

    /** Enable RTC clock*/
    RCM_EnableRTCCLK();

    /** Disable RTC write Protection*/
    RTC_DisableWriteProtection();

    /** Wait Synchro*/
    RTC_WaitForSynchro();

    /** set LSI Prediv */
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




