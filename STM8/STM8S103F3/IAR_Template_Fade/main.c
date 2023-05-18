#include "stm8s.h"

#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_5

int main(void) {
    
    // Reset ("de-initialise") GPIO port D.
    GPIO_DeInit(LED_PORT);    
    // Initialise pin 0 of port D.
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    
    // Reset ("de-initialise") TIM3.
    TIM2_DeInit();
    // Set TIM1 to use a prescaler of 2048 and have a period of 999.
    TIM2_TimeBaseInit(TIM2_PRESCALER_2048, 999);
    // Enable TIM3.
    TIM2_Cmd(ENABLE);

    // Infinite loop.
    for(;;) {        
        if (TIM2_GetCounter() < 500) {        
            // Output a low on the LED pin to illuminate it.
            GPIO_WriteLow(LED_PORT, LED_PIN);
        } else {
            // Output a high on the LED pin to switch it off.
            GPIO_WriteHigh(LED_PORT, LED_PIN);
        }
    }
}


#ifdef USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif