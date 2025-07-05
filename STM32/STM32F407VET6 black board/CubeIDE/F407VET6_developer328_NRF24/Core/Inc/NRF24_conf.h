/*
 * 25-JUL-2024
 * STM32 HAL NRF24 LIBRARY
 */

#ifndef _NRF_24_CONF_H_
#define _NRF_24_CONF_H_

#define hspiX hspi1
#define spi_w_timeout 1000
#define spi_r_timeout 1000
#define spi_rw_timeout 1000

#define csn_gpio_port GPIOB
#define csn_gpio_pin GPIO_PIN_7

#define ce_gpio_port GPIOB
#define ce_gpio_pin GPIO_PIN_6

#endif

