#include "stm32f1xx.h"

void SystemClock_Config(void)
{
    // Enable HSE (8MHz external crystal)
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;

    // Configure PLL (8MHz * 9 = 72MHz)
    RCC->CFGR |= RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC;
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;

    // Set flash latency
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // Switch to PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ;
}

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 5000; i++)
    {
        __asm__ volatile("nop");
    }
}

void LED_Init(void)
{
    // 1. Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // 2. Configure PA1 as push-pull output (50MHz)
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOA->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1; // Output, 50MHz
}

int main(void)
{
    SystemClock_Config();
    LED_Init();

    while (1)
    {
        GPIOA->ODR ^= GPIO_ODR_ODR1; // Toggle PA1
        delay_ms(500);
    }
}