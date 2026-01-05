#include <unity.h>
#include "stm32f1xx_hal.h"

// Setup function called before each test
void setUp(void) {
    // Initialize HAL if not already done
    // HAL_Init();
    // SystemClock_Config(); // Define or include your clock config
}

// Teardown function called after each test
void tearDown(void) {
    // Cleanup if needed
}

// Example test using STM32 HAL GPIO
void test_hal_gpio(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure GPIO pin (e.g., PC13 as output)
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Test setting pin high
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));

    // Test setting pin low
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));

    // Test toggling
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
}

// Main function for running tests
int main(void) {
    // Initialize HAL and system clock
    HAL_Init();
    // SystemClock_Config(); // Uncomment and define if needed

    // Start Unity test framework
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_hal_gpio);

    // End tests
    return UNITY_END();
}