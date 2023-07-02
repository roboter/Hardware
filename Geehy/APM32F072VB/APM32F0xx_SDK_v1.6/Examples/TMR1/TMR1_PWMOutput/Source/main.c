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

/** TMR1 PWM Output Init*/
void APM_MINI_TMR1_PWMOutPut_Init(void);
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
    uint16_t i = 0;

    APM_MINI_LEDInit(LED2);
    APM_MINI_TMR1_PWMOutPut_Init();

    for(;;)
    {
        Delay();
        TMR_SetCompare1(TMR1,i++);

        if(i == 0xFFFF)
        {
            i = 0;

            APM_MINI_LEDToggle(LED2);
        }
    }
}

/*!
 * @brief       TMR1 PWM Output Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR1_PWMOutPut_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  occonfig;
    GPIO_Config_T   gpioconfig;
    /** Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);

    /**  Connect TMR1 to CH1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_PIN2);
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_8;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA,&gpioconfig);

      /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
      /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
      /** Set divider = 47 .So TMR1 clock freq ~= 48/(47+1) = 1MHZ */
    timeBaseConfig.div = 47 ;
      /** Set counter = 0xffff */
    timeBaseConfig.period = 0xFFFF;
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
    occonfig.OC_OutputNState =  TMR_OUTPUT_NSTATE_DISABLE;
     /** Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
     /** CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
     /** CH1N polarity is high */
    occonfig.OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
     /** Set compare value */
    occonfig.Pulse = 0xFEFF;
    TMR_OC1Config(TMR1,&occonfig);

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
    volatile uint32_t delay = 0xFF;

    while(delay--);
}
