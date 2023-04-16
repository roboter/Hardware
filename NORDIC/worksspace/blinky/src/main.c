/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led_2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led_3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

void main(void)
{
	if (!device_is_ready(led_0.port))
	{
		return;
	}

	if (!device_is_ready(led_1.port))
	{
		return;
	}

	if (!device_is_ready(led_2.port))
	{
		return;
	}

	if (!device_is_ready(led_3.port))
	{
		return;
	}

	if (gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_ACTIVE) < 0)
	{
		return;
	}

	if (gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_ACTIVE) < 0)
	{
		return;
	}

	if (gpio_pin_configure_dt(&led_2, GPIO_OUTPUT_ACTIVE) < 0)
	{
		return;
	}

	if (gpio_pin_configure_dt(&led_3, GPIO_OUTPUT_ACTIVE) < 0)
	{
		return;
	}

	while (1)
	{
		if (gpio_pin_toggle_dt(&led_0) < 0)
		{
			return;
		}
		k_msleep(SLEEP_TIME_MS);
		if (gpio_pin_toggle_dt(&led_1) < 0)
		{
			return;
		}
		k_msleep(SLEEP_TIME_MS);
		if (gpio_pin_toggle_dt(&led_2) < 0)
		{
			return;
		}
		k_msleep(SLEEP_TIME_MS);
		if (gpio_pin_toggle_dt(&led_3) < 0)
		{
			return;
		}
		k_msleep(SLEEP_TIME_MS);
	}
}
