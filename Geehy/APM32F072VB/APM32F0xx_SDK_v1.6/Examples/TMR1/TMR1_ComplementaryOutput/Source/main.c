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

/** TMR1 Init*/
void APM_MINI_TMR1_Init(void);
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
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_TMR1_Init();

    /** Turn LED2 on */
    GPIO_ClearBit(LED2_GPIO_PORT, LED2_PIN);
    /** Turn LED3 off */
    GPIO_SetBit(LED3_GPIO_PORT, LED3_PIN);

    for(;;)
    {
        Delay();
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
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
void APM_MINI_TMR1_Init()
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  occonfig;
    TMR_BDTInit_T   bdtconfig;
    GPIO_Config_T   gpioconfig;

    /** Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
    /** Connect TMR1 to CH1N */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_PIN2);
    /**  Connect TMR1 to CH1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN2);

    gpioconfig.mode = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin  =  GPIO_PIN_7;
    gpioconfig.pupd = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA,&gpioconfig);

    gpioconfig.pin  =  GPIO_PIN_8;
    GPIO_Config(GPIOA,&gpioconfig);

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
    TMR_ConfigTimeBase(TMR1,&timeBaseConfig);

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
    /** Set compare value = 0xef */
    occonfig.Pulse = 0xEF;
    TMR_OC1Config(TMR1,&occonfig);

    /** bdt automatic Output  */
    bdtconfig.automaticOutput = TMR_AUTOMATIC_OUTPUT_ENABLE;
    /** Enable BRK */
    bdtconfig.breakState = TMR_BREAK_STATE_ENABLE;
    /** BRKPolarity is high */
    bdtconfig.breakPolarity = TMR_BREAK_POLARITY_HIGH;
    /** Set dead time */
    bdtconfig.deadTime = 100;
    /** Disable output when CHx output closed */
    bdtconfig.IMOS_State = TMR_IMOS_STATE_DISABLE;
    /** Protect Off */
    bdtconfig.lockLevel = TMR_LOCK_LEVEL_OFF;
    /** Disable output when CHxN output closed */
    bdtconfig.RMOS_State = TMR_RMOS_STATE_DISABLE;
    TMR_ConfigBDT(TMR1,&bdtconfig);

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
    volatile uint32_t delay = 0xffff5;

    while(delay--);
}
