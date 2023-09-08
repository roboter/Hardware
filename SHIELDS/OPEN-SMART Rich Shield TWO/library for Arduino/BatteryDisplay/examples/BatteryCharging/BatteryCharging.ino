/***********************************************************/
//Demo for the the Battery Display by OPEN-SMART Team
//Board:  Arduino UNO R3
//IDE:	  Arduino-1.6.5
//Function:  Simulate charging display of a battery.
//Store: http://www.aliexpress.com/store/1199788
/***************************************************************/

#include "TM1651.h"
#define CLK 10//pins definitions for TM1651 and can be changed to other ports       
#define DIO 11
TM1651 batteryDisplay(CLK,DIO);
void setup()
{
  batteryDisplay.init();
  batteryDisplay.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  batteryDisplay.frame(FRAME_ON);//light the frame of the battery display
}
void loop()
{
  charging();
}

void charging()
{
  for(uint8_t level = 0; level < 8; level ++)
  {
    batteryDisplay.displayLevel(level);
	delay(500);
  }
}
