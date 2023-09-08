/*-------------------------------------------------------------------------
// Function: Joystick control the movement of the matrix spot.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/
#include <OS_SingleJoystick.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_NeoPixel.h>

#define PIN A3
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
#define SW_PIN 0xff //there is no button in the Joystick.
#define JOYSTCK_X A0
#define JOYSTCK_Y A1

SingleJoystick joystick(JOYSTCK_X, JOYSTCK_Y);

uint8_t coordinate_x = 7;
uint8_t coordinate_y = 3;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  //-------------
  rgb.begin();
  rgb.clear();
  rgb.show();
  //-------------
  Serial.println("begin");
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1);
  matrix.clear();      // clear display
  matrix.drawPixel(coordinate_x, coordinate_y, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  
}

// the loop function runs over and over again forever
void loop() {
  joystickControlLED();
  delay(100); // optionally, only to delay the output of information in the example
}

void joystickControlLED()
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
        Serial.println("UP");
		if(coordinate_y>0) coordinate_y -= 1; 
		break;
      case MOVE_DOWN:
        Serial.println("DOWN");
		if(coordinate_y<7) coordinate_y += 1; 
		break;
      case MOVE_RIGHT:
        Serial.println("RIGHT");
		if(coordinate_x<15) coordinate_x += 1;
		break;
      case MOVE_LEFT:
       Serial.println("LEFT");
	   if(coordinate_x>0) coordinate_x -= 1; 
	   break;
      default:
	   Serial.println("NOT");break;
       break;
    }
	Serial.print(coordinate_x);
    Serial.print(" , ");
    Serial.println(coordinate_y);
	matrix.clear();      // clear display
    matrix.drawPixel(coordinate_x, coordinate_y, LED_ON);  
    matrix.writeDisplay();  // write the changes we just made to the display
  }
}
