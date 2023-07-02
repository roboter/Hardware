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

/** TMR3 Init */
void APM_MINI_TMR3_Init(void);
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
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_EINT);
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_TMR3_Init();

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
 * @brief       TMR3 Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR3_Init()
{
    TMR_TimeBase_T  timeBaseConfig;
    GPIO_Config_T   gpioconfig;
    TMR_OCConfig_T  occonfig;
    /** Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

    /**  Connect TMR3 to CH1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN1);
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_6;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA,&gpioconfig);

    /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /** Set divider = 47.So TMR1 clock freq ~= 48/(47 + 1) = 1MHZ */
    timeBaseConfig.div = 47 ;
    /** Set counter = 0xffff */
    timeBaseConfig.period = 0xFFFF;
    /** Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR3,&timeBaseConfig);

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
    /** Set compare value = 0x5ef */
    occonfig.Pulse = 0x5EF;
    TMR_OC1Config(TMR3,&occonfig);
    /** Set One Pulse Mode*/
    TMR_SelectOnePulseMode(TMR3,TMR_OPMODE_SINGLE);

     /**  Enable TMR3  */
    TMR_Enable(TMR3);

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
 * @brief       The interrupt will happen when the button is press ,
 *              and TMR3 will generate one pulse.
 * @param
 *
 * @retval
 *
 * @note        This function should put into EINT0_1_IRQHandler() in apm32f0xx_int.c
 */
void  BUTTON_KEY_OnePluse_Isr(void)
{
    if(EINT_ReadStatusFlag(EINT_LINE1)==SET)
    {
        TMR_Enable(TMR3);
        EINT_ClearStatusFlag(EINT_LINE1);
    }
}



