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

/** TMR Synchronization Init*/
void APM_MINI_TMR_Synchronization_Init(void);

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

    APM_MINI_TMR_Synchronization_Init();

    /** Turn LED2 on */
    GPIO_ClearBit(LED2_GPIO_PORT, LED2_PIN);
    /** Turn LED3 off */
    GPIO_SetBit(LED3_GPIO_PORT, LED3_PIN);

    for (;;)
    {
        Delay();
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief       TMR synchronization Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_MINI_TMR_Synchronization_Init(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    GPIO_Config_T   gpioconfig;
    TMR_OCConfig_T  occonfig;

    /** Enable Clock*/
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

    /**  Connect TMR3 to CH1 */
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_6;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;

    GPIO_Config(GPIOA, &gpioconfig);

    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_PIN1);

    /** Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /** Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /** Set divider = 0 .So TMR1 clock freq ~= 48/(0+1) = 48MHZ */
    timeBaseConfig.div = 0x00;
    /** Set counter = 0xff */
    timeBaseConfig.period = 0xff;
    /** Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter = 0x00;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /** Set counter = 0x0A */
    timeBaseConfig.period = 0x0A;
    TMR_ConfigTimeBase(TMR3, &timeBaseConfig);

    /** PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /** Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /** CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /** Set compare value = 0x40 */
    occonfig.Pulse = 0x40;
    TMR_OC1Config(TMR1, &occonfig);

    TMR_EnableMasterSlaveMode(TMR1);

    TMR_SelectOutputTrigger(TMR1, TMR_TRGOSOURCE_UPDATE);

    /** PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /** Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /** CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /** Set compare value = 0x5ef */
    occonfig.Pulse = 0x04;

    TMR_OC1Config(TMR3, &occonfig);

    /** Set Slave Mode*/
    TMR_SelectSlaveMode(TMR3, TMR_SLAVEMODE_GATED);
    /** Set Input Trigger*/
    TMR_SelectInputTrigger(TMR3, TMR_TS_ITR0);

    /**  Enable TMR3  */
    TMR_Enable(TMR3);
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

    while (delay--);
}
