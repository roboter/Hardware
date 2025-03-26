#include <iostm8s103f3.h>


/*
#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_5
*/

//
// Delay loop
//
// Actual delay depends on clock settings
// and compiler optimization settings.
//
void delay(unsigned int n)
{
  while (n-- > 0);
}

int main( void )
{
  //
  // Data Direction Register
  //
  // 0: Input
  // 1: Output
  //
  PB_DDR_bit.DDR5 = 1;
  
  //
  // Control Register 1
  //
  // Input mode:
  //   0: Floating input
  //   1: Input with pull-up
  //
  // Output mode:
  //   0: Pseudo open drain
  //   1: Push-pull
  //
  PB_CR1_bit.C15 = 1;
  
  //
  // Control Register 2
  //
  // Input mode:
  //   0: External interrupt disabled
  //   1: External interrupt enabled
  //
  // Output mode:
  //   0: Output speed up to  2 MHz
  //   1: Output speed up to 10 MHz
  //
  PB_CR2_bit.C25 = 1;
  
  //
  // Output Data Register
  //
  // Output value
  //
  PB_ODR_bit.ODR5 = 0;
  
  //
  // Main loop
  //
  while (1)
  {
    PB_ODR_bit.ODR5 = !PB_ODR_bit.ODR5;
    delay(60000);
  }
}
