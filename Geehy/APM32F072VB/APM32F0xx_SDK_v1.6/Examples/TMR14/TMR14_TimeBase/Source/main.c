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
#include "apm32f0xx_eint.h"

/** Timer tick */
volatile uint32_t tick = 0;
/** TMR14 Init */
void APM_MINI_TMR14_Init(void);


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
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_EINT);
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_TMR14_Init();

    /** Turn LED2 on */
    GPIO_ClearBit(LED2_GPIO_PORT, LED2_PIN);
    /** Turn LED3 off */
    GPIO_SetBit(LED3_GPIO_PORT, LED3_PIN);

    for(;;)
    {
        if(tick >= 100)
        {
            tick = 0;
            APM_MINI_LEDToggle(LED2);
            APM_MINI_LEDToggle(LED3);
        }
    }
}


void APM_MINI_TMR14_Init()
{
    TMR_TimeBase_T  timeBaseConfig;

    /** Enable Clock*/
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR14);

    /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /** Set divider = 47.So TMR1 clock freq ~= 48/(47 + 1) = 1MHZ */
    timeBaseConfig.div = 47 ;
    /** Set counter = 0xffff */
    timeBaseConfig.period = 0xFF;
    /** Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;

    TMR_ConfigTimeBase(TMR14,&timeBaseConfig);

    /** Enable update interrupt*/
    TMR_EnableInterrupt(TMR14,TMR_INT_UPDATE);
    NVIC_EnableIRQRequest(TMR14_IRQn,2);

    /**  Enable TMR14  */
    TMR_Enable(TMR14);
}

/*!
 * @brief       TMR4 interrupt service runtine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into TMR14_IRQHandler() in apm32f0xx_int.c
 */
void TMR14Isr(void)
{
    if(TMR_ReadIntFlag(TMR14,TMR_INT_FLAG_UPDATE) == SET)
    {
        TMR_ClearIntFlag(TMR14,TMR_INT_FLAG_UPDATE);

        tick++;
    }
}
