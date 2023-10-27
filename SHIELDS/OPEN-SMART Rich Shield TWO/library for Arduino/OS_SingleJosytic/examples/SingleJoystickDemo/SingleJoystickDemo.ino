//Store: http://www.aliexpress.com/store/1199788
 // 	 http://dx.com
 // board: OPEN-SMART UNO R3
 //IDE version: 1.6.5
 //Function: use the serial monitor to tell the movement of Joystick Control 
/***************************************/


#include <OS_SingleJoystick.h>

#define JOYSTCK_X A0
#define JOYSTCK_Y A1

SingleJoystick joystick(JOYSTCK_X, JOYSTCK_Y);

void setup()
{
  joystick.init();
  Serial.begin(9600); // 9600 bps
  Serial.println("start");
}

void loop()
{  
  if(joystick.isChange())
  {
	int x,y; 
    x=joystick.nowX;
    y=joystick.nowY;
    Serial.print("x = ");
    Serial.print(x ,DEC);
    Serial.print(" y = ");
    Serial.println(y ,DEC);
	
	uint8_t operation;
    operation = joystick.multipleRead();

    switch (operation) {
      case MOVE_UP:
        Serial.println("UP");break;
      case MOVE_DOWN:
        Serial.println("DOWN");break;
      case MOVE_RIGHT:
        Serial.println("RIGHT");break;
      case MOVE_LEFT:
       Serial.println("LEFT");break;
      default:
	   Serial.println("NOT");break;
       break;
    }
  }
  delay(100);
}


