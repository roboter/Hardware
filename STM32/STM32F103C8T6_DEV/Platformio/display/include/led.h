#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" // STM32F10x Standard Peripheral Library
#include "stm32f10x_gpio.h"

/**
 * @brief Initialize LED GPIO configuration
 *
 * Configures the LED pin (PA1) as a push-pull output
 * with 50MHz speed and initializes it to OFF state.
 */

void LED_Init(void);
void LED_Set(void);    // Set LED (turn on)
void LED_Reset(void);  // Reset LED (turn off)
void LED_Toggle(void); // Toggle LED state

#endif /* __LED_H */