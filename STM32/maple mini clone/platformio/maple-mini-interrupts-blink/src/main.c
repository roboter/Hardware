#include "stm32f1xx_hal.h"

#define LED_PIN GPIO_PIN_1
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

TIM_HandleTypeDef htim3;

void LED_Init();

int main(void)
{
    HAL_Init();
    LED_Init();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 72000 - 1; // 72 MHz / 72000  = 1000 Hz
    htim3.Init.Period = 499;          // 1000 Hz / 500 = 2 Hz = 0.5s

    __HAL_RCC_TIM3_CLK_ENABLE(); // Enable clock

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    HAL_TIM_Base_Init(&htim3); // Configuring timer
    HAL_TIM_Base_Start_IT(&htim3); // Run timer

    while (1)
        ;
}

void LED_Init()
{
    LED_GPIO_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    }
}