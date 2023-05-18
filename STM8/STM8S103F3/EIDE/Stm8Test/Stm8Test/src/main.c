/**************************************
 * 
 *       stm8s sdcc blink demo
 * 
 * MCU: STM8S103/003
 * FREQ: 16MHz
 * PIN: PB5
 * 
 **************************************
*/

#include "stm8s.h"

#define LED_GPIO_PORT (GPIOB)
#define LED_GPIO_PINS (GPIO_PIN_5)

void DelayInit(void);
void DelayMs(uint16_t ms);

void main(void)
{
    // set system clock to 16Mhz
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    // init delay timer
    DelayInit();

    // init LED pin
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    while (1)
    {
        GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
        DelayMs(500);
    }
}

void DelayInit(void)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249); // 1ms
    TIM4_SelectOnePulseMode(TIM4_OPMODE_SINGLE);
}

void DelayMs(uint16_t ms)
{
    while (ms--)
    {
        TIM4->SR1 = (uint8_t)(~TIM4_FLAG_UPDATE);
        TIM4->CR1 |= TIM4_CR1_CEN;
        while ((TIM4->SR1 & (uint8_t)TIM4_FLAG_UPDATE) == 0)
            ;
    }
}

/**
 * =========================================================
 *                     interrupt functions
 * =========================================================
*/

/**
  * @brief  TRAP interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    while (1)
    {
        nop();
    }
}

/**
  * @brief  this is a example for interrupt function define
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(_this_is_a_example, EXTI_PORTA_IRQn)
{
    // TODO
}
