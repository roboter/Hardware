#include "main.h"
// Only declarations of constants is used, but there no functions like GPIO_Init
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

extern bool isPower;
extern uint8_t tim4_counter;
extern uint8_t uart_ready;
extern uint8_t uart_index;
extern char uart_buf[UART_BUFFER_LEN]; // UART_BUFFER_LEN=10
void clear_uart_buf();
void print_encoder(char *str, int value);
void delay(uint32_t ms)
{
    ms *= 1000; // Convert milliseconds to microseconds
    for (uint32_t i = 0; i < ms; i++)
    {
        __NOP(); // Perform a no-operation to introduce a small delay
    }
}

// In this updated code, the delay_us() function uses the DWT(Data Watchpoint and Trace)
// cycle counter register to introduce microsecond delays.
// The DWT cycle counter provides accurate timing based on the system clock frequency.
void delay_us(uint32_t us)
{
    // Enable DWT cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    uint32_t start = DWT->CYCCNT;                               // Get the current cycle count
    uint32_t target = start + us * (SystemCoreClock / 1000000); // Calculate the target cycle count

    // Wait until the target cycle count is reached
    while (DWT->CYCCNT < target)
        ;
}

int main(void)
{
    // Enable HSE (external high-speed oscillator)
    RCC->CR |= (1 << 16); // HSEON
    while (!(RCC->CR & (1 << 17)))
        ; // Wait for HSE to stabilize

    // Configure PLL
    RCC->CFGR &= ~((1 << 16) | (0xF << 18)); // Clear PLL source and multiplier bits
    RCC->CFGR |= (1 << 16) | (9 << 18);      // Set PLL source as HSE, PLL multiplier as 9

    // Enable PLL
    RCC->CR |= (1 << 24); // PLLON
    while (!(RCC->CR & (1 << 25)))
        ; // Wait for PLL to stabilize

    // Configure flash latency
    FLASH->ACR &= ~0x7; // Clear flash latency bits
    FLASH->ACR |= 0x2;  // Set flash latency to 2 wait states for 72MHz

    // Switch system clock to PLL
    RCC->CFGR &= ~(0x3 << 0); // Clear system clock bits
    RCC->CFGR |= (0x2 << 0);  // Set PLL as system clock
    while ((RCC->CFGR & (0x3 << 2)) != (0x2 << 2))
        ; // Wait for PLL to become the system clock

    // Enable clock for GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB1 as output (push-pull, 10 MHz)
    GPIOB->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOB->CRL |= GPIO_CRL_MODE1_0;

    while (1)
    {

        // Delay for 1 second
        // delay(1000);
        delay_us(0xFFFFFF);

        // Toggle PB1 (LED)
        GPIOB->ODR ^= GPIO_ODR_ODR1;
    }
}

// In this updated example, the clock system is configured using the High - Speed External(HSE)
// oscillator and the PLL to provide the system clock.The delay function and GPIO configuration remain the same as in the previous example.

//     Please note that the code assumes you are using an STM32F103 microcontroller.Ensure that you include the appropriate CMSIS
//     headers(stm32f10x.h) and
//     modify the code according to your specific microcontroller series.Additionally,
//     adjust the clock settings to match your desired frequency and oscillator configuration.

int main2()
{
    // enable GPIOC port
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;  // enable PORT_C
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;  // enable PORT_A
    RCC->APB2ENR |= RCC_APB2Periph_GPIOB;  // enable PORT_B
    RCC->APB2ENR |= RCC_APB2Periph_USART1; // enable UART1
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;   // enable TIM2
    RCC->APB1ENR |= RCC_APB1Periph_TIM4;   // enable TIM4
#ifdef HW_SPI
    RCC->APB2ENR |= RCC_APB2Periph_SPI1; // enable SPI1
#endif
#ifdef USE_DMA
    RCC->AHBENR |= RCC_AHBENR_DMA1EN; // enable DMA1
#endif
    // --- GPIO setup ----
    // GPIOC->CRH &= ~(uint32_t)(0xf << 20); // Reset for PC13 (LED)
    // GPIOC->CRH |= (uint32_t)(0x2 << 20);  // Push-Pull 2-MHz fo PC13 (LED

    // Mapple MINI

    // Set PB1 as output
    // Enable clock for GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB1 as output (push-pull)
    GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    GPIOB->CRL |= GPIO_CRL_MODE1_0;

    gpio_set(GPIOC, LED);
    GPIOA->CRH &= ~(uint32_t)(0xf << 4); // enable Alterentive mode
    GPIOA->CRH |= (uint32_t)(0xa << 4);  // for PA9 = USART1_TX
    GPIOA->CRH &= ~(uint32_t)(0xf << 8); // enable Alterentive mode
    GPIOA->CRH |= (uint32_t)(0xa << 8);  // for PA10 = USART1_RX
    // encoder PA0, PA1
    GPIOA->CRL &= ~(uint32_t)(0xff); // clear
    GPIOA->CRL |= (uint32_t)(0x88);  // pull-down input mode for PA0, PA1
    GPIOA->ODR |= (uint16_t)(0x3);   // switch to pull-up mode for PA0,PA1
    // Configure Port B. PB6_DC, PB4_RST, PB5_BackLight
    GPIOB->CRL &= ~(uint32_t)(0xf << 24); // clear mode for PB6   (DC)
    GPIOB->CRL &= ~(uint32_t)(0xf << 16); // clear mode for PB4   (RST)
    GPIOB->CRL &= ~(uint32_t)(0xf << 20); // clear mode for PB5   (BackLight)
    GPIOB->CRL |= (uint32_t)(0x3 << 24);  // for PB6 set  PushPull mode 50MHz (DC)
    GPIOB->CRL |= (uint32_t)(0x3 << 16);  // for PB4 set  PushPull mode 50MHz (RST)
    GPIOB->CRL |= (uint32_t)(0x7 << 20);  // for PB5 set  OpenDrain mode 50MHz (BL)
    // SOFT SPI Setup (PA4_SE, PA5_CLK,  PA7_DIO)
    GPIOA->CRL &= ~(uint32_t)(0xf << 16); // clear mode for PA4   (SE)
    GPIOA->CRL &= ~(uint32_t)(0xf << 20); // clear mode for PA5   (SPI_Clock)
    GPIOA->CRL &= ~(uint32_t)(0xf << 28); // clear mode for PA7   (SPI_DIO)
    GPIOA->CRL |= (uint32_t)(0x3 << 16);  // for PA4 set  PushPull mode 50MHz (SE)
#ifdef HW_SPI
    GPIOA->CRL |= (uint32_t)(0xb << 20); // for PA5 set  Alternative mode, 50MHz
    GPIOA->CRL |= (uint32_t)(0xb << 28); // for PA7 set  Alternative mode, 50MHz
#else
    GPIOA->CRL |= (uint32_t)(0x3 << 20); // for PA5 set  PushPull mode 50MHz (SPI_Clock)
    GPIOA->CRL |= (uint32_t)(0x3 << 28); // for PA7 set  PushPull mode 50MHz (SPI_DIO)
#endif
    // ------- SysTick CONFIG --------------
    if (SysTick_Config(72000)) // set 1ms
    {
        while (1)
            ; // error
    }
    // ------ TIM2 Setup -------------------
    TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
    TIM2->CCER = TIM_CCER_CC1P | TIM_CCER_CC2P;
    TIM2->SMCR = TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
    TIM2->ARR = 1000;
    TIM2->CR1 = TIM_CR1_CEN;

#ifdef HW_SPI
    // --- SPI1 setup ----
    SPI1->CR1 = (SPI_Mode_Master | SPI_DataSize_8b | SPI_NSS_Soft | SPI_BaudRatePrescaler_4);
#ifdef USE_DMA
    SPI1->CR2 |= SPI_CR2_TXDMAEN; // enable DMA request
#endif
    SPI1->CR1 |= SPI_CR1_SPE;
#endif

    pcd8544_init();

    pcd8544_clear();
    lcd_print("Hello, World", 0, 1);
    lcd_print("++++++++++++", 0, 0);
    lcd_print("!!!!!!!!!!!!", 0, 2);
    lcd_print_invert("testtesttest", 0, 3);
    lcd_print("------------", 0, 4);
    lcd_print("Privet, MiR!", 0, 5);

    pcd8544_display_fb();

    delay_ms(50);

    // Toggle PB1 (LED)
    GPIOB->ODR ^= GPIO_ODR_ODR1;

    // Delay
    // delay(1000000);
}
