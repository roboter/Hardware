/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.0
 *
 * @date        2022-02-21
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

#include "main.h"

#define TEST_TOUCHKEY(Num) ((MyTouchKeys[(Num)].p_Data->StateId == TSC_STATEID_DETECT))

#define TEST_LINROT(Num) ((MyLinRots[(Num)].p_Data->StateId == TSC_STATEID_DETECT) ||\
                         (MyLinRots[(Num)].p_Data->StateId == TSC_STATEID_DEB_RELEASE_DETECT))

void GPIO_Init(void);
void Process_Sensors(void);
void Systick_Delay(__IO uint32_t ms);

__IO uint32_t Global_SystickCounter;

/*!
 * @brief       Main
 *
 * @param       None
 *
 * @retval      None
 */
int main(void)
{
    SystemInit();
    GPIO_Init();

    Delay_Config();
    LED_Config();
    OLED_Config();

    TSC_User_Config();

    OLED_ShowString(0, 0, "Geehy", 16);
    OLED_ShowString(0, 22, "LTS Pos:", 16);
    OLED_ShowString(0, 48, "RTS Pos:", 16);
    OLED_Refresh();

    while(1)
    {
        /** Execute Touch Driver */
        if (TSC_User_Action() == TSC_STATUS_OK)
        {
            Process_Sensors();
        }
        else
        {
            /** Execute other tasks... */
        }
    }
}

/*!
 * @brief       Configure GPIO to Touch-Sensing
 *
 * @param       None
 *
 * @retval      None
 */
void GPIO_Init(void)
{
    /** Enable GPIO clocks */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA|RCM_AHB_PERIPH_GPIOB|RCM_AHB_PERIPH_GPIOC|
                             RCM_AHB_PERIPH_GPIOD|RCM_AHB_PERIPH_GPIOF);

    /** Configure all unused IOs in Analog to reduce current consumption.
     *  Excepted PA13 (SWDAT) and PA14 (SWCLK) used for debug.
     */
    GPIOA->MODE |= 0xC3FFFFFF;
    GPIOA->PUPD = 0;
    GPIOB->MODE = 0xFFFFFFFF;
    GPIOB->PUPD = 0;
    GPIOC->MODE = 0xFFFFFFFF;
    GPIOC->PUPD = 0;
    GPIOD->MODE = 0xFFFFFFFF;
    GPIOD->PUPD = 0;
    GPIOF->MODE = 0xFFFFFFFF;
    GPIOF->PUPD = 0;
}

/*!
 * @brief       Manage the activity on sensors
 *
 * @param       None
 *
 * @retval      None
 */
void Process_Sensors(void)
{
    uint8_t idx_key, idx_linrot;

    for (idx_key=0; idx_key<5; idx_key++)
    {
        if (TEST_TOUCHKEY(idx_key))
        {
            LED_Action(idx_key);
            Delay_ms(1000);
        }
    }

    for (idx_linrot=0; idx_linrot<2; idx_linrot++)
    {
        if (TEST_LINROT(0))
        {
            OLED_ShowNum(70, 14, MyLinRots[0].p_Data->Position, 3, 24);
            OLED_Refresh();
        }
        if (TEST_LINROT(1))
        {
            OLED_ShowNum(70, 40, MyLinRots[1].p_Data->Position, 3, 24);
            OLED_Refresh();
        }
    }
}

/*!
 * @brief       Executed when a sensor is in Error state
 *
 * @param       None
 *
 * @retval      None
 */
void MyKeys_ProcessErrorState(void)
{
    TSC_TouchKey_ConfigOffState();
    while(1)
    {
        LED_Toggle(LED1);
        LED_Toggle(LED2);
        Systick_Delay(100);
    }
}

/*!
 * @brief       Executed when a sensor is in Error state
 *
 * @param       None
 *
 * @retval      None
 */
void MyLinRots_ProcessErrorState(void)
{
    TSC_Linrot_ConfigOffState();
    while(1)
    {
        LED_Toggle(LED3);
        LED_Toggle(LED4);
        Systick_Delay(100);
    }
}

/*!
 * @brief       Executed when a sensor is in Off state
 *
 * @param       None
 *
 * @retval      None
 */
void MyKeys_ProcessOffState(void)
{
    //!< Add here your own processing
}

/*!
 * @brief       Executed when a sensor is in Off state
 *
 * @param       None
 *
 * @retval      None
 */
void MyLinRots_ProcessOffState(void)
{
    //!< Add here your own processing
}

/*!
 * @brief       Executed at each timer interrupt
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_CallBack_TimerTick(void)
{
    //!< Add here your own processing
}

/*!
 * @brief       Systick delay
 *
 * @param       ms: milliseconds
 *
 * @retval      None
 */
void Systick_Delay(__IO uint32_t ms)
{
    Global_SystickCounter = ms;

    while (Global_SystickCounter != 0)
    {
    }
}
