#include "stm32f1xx_hal.h"

#define LED_PIN GPIO_PIN_1
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define MCO_PIN GPIO_PIN_8
#define MCO_PORT GPIOA

TIM_HandleTypeDef htim3;

void LED_Init();

void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct;
    RCC_OscInitTypeDef oscinitstruct;

    oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState = RCC_HSE_ON;
    oscinitstruct.HSIState = RCC_HSI_OFF;
    oscinitstruct.PLL.PLLState = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
    {
        while (1)
            ;
    }

    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK |
                               RCC_CLOCKTYPE_HCLK |
                               RCC_CLOCKTYPE_PCLK1 |
                               RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
    {
        while (1)
            ;
    }
}

void Init_MCO(void)
{
    // • RCC_MCOx: specifies the output direction for the clock source. This parameter can be one of the following
    // values:
    // – RCC_MCO1 Clock source to output on MCO1 pin(PA8).
    // • RCC_MCOSource: specifies the clock source to output. This parameter can be one of the following
    // values:
    // – RCC_MCO1SOURCE_NOCLOCK No clock selected as MCO clock
    // – RCC_MCO1SOURCE_SYSCLK System clock selected as MCO clock
    // – RCC_MCO1SOURCE_HSI HSI selected as MCO clock
    // – RCC_MCO1SOURCE_HSE HSE selected as MCO clock
    // – RCC_MCO1SOURCE_PLLCLK PLL clock divided by 2 selected as MCO source
    // – RCC_MCO1SOURCE_PLL2CLK PLL2 clock selected as MCO source
    // – RCC_MCO1SOURCE_PLL3CLK_DIV2 PLL3 clock divided by 2 selected as MCO source
    // – RCC_MCO1SOURCE_EXT_HSE XT1 external 3-25 MHz oscillator clock selected as MCO source
    // – RCC_MCO1SOURCE_PLL3CLK PLL3 clock selected as MCO source
    // • RCC_MCODiv: specifies the MCO DIV. This parameter can be one of the following values:
    // – RCC_MCODIV_1 no division applied to MCO clock
    // HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);

    /* Output clock on MCO1 pin(PA8) for debugging purpose */
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1); // 72 MHz or 64 MHz * CubeIDE says it can be only up to 50MHz

    //  MCO pin should be configured in alternate function mode
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MCO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(MCO_PORT, &GPIO_InitStruct);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    Init_MCO();
    LED_Init();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 72000 - 1; // 72 MHz / 72000  = 1000 Hz
    htim3.Init.Period = 10000 - 1;    // 1000 Hz / 500 = 2 Hz = 0.5s

    __HAL_RCC_TIM3_CLK_ENABLE(); // Enable clock

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    HAL_TIM_Base_Init(&htim3);     // Configuring timer
    HAL_TIM_Base_Start_IT(&htim3); // Run timer

    int cycle = 0;
    while (1)
    {
        cycle++;
        if (cycle > 1000)
            cycle = 0;

        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, cycle);
        HAL_Delay(10);
    }
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