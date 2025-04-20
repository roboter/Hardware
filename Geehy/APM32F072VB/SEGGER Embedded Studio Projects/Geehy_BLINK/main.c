/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include <stdio.h>
/* Includes */
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"
#include "Board.H"



/* Delay */
void Delay(void);


/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
int main(void) {
 GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(LED2_GPIO_CLK | LED3_GPIO_CLK);
    /* LED2 GPIO configuration */
    gpioConfig.pin = LED2_PIN;
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    GPIO_Config(LED2_GPIO_PORT, &gpioConfig);

    /* LED3 GPIO configuration */
    gpioConfig.pin = LED3_PIN;
    GPIO_Config(LED3_GPIO_PORT, &gpioConfig);

    /* Turn LED2 on */
    GPIO_ClearBit(LED2_GPIO_PORT, LED2_PIN);
    /* Turn LED3 off */
    GPIO_SetBit(LED3_GPIO_PORT, LED3_PIN);

    for (;;)
    {
        Delay();
        /* LED Toggle*/
        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
  int i;

  for (i = 0; i < 100; i++) {
    printf("Hello World %d!\n", i);
  }
  do {
    i++;
  } while (1);
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

/*************************** End of file ****************************/
