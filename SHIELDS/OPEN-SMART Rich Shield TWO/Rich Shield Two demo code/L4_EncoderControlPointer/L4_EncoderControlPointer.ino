/*-------------------------------------------------------------------------
// Function: Function: use the rotary encoder to rotate the pointer on the led matrix.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <RotaryEncoder.h>
#include <Adafruit_NeoPixel.h>

#define PIN A3
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
#define encoder_button 4//the SIG pin on the Rocker Switch module is connected with D2 of Arduino/Catduino
// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(3, 2);


#define CLOCKWISE 1
#define ANTI_CLOCKWISE -0

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
void rotatePointer(uint8_t,uint8_t);

void setup() {
  Serial.begin(9600);
  //-------------
  rgb.begin();
  rgb.clear();
  rgb.show();
  //-------------
  Serial.println("16x8 LED Matrix Test");
  pinMode(encoder_button,INPUT);
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1);
  matrix.drawLine(0,3, 15,4, LED_ON);// init
  matrix.writeDisplay(); 
}



void loop() {
  static int pos = 0;
  if(digitalRead(encoder_button)==1)
  {
    delay(10);
    if(digitalRead(encoder_button)==1)
    {
       matrix.clear();
       matrix.writeDisplay(); 
     }
   }
  encoder.tick();
  int newPos = encoder.getPosition();
  uint8_t pointerDirection;
  if (pos != newPos) {
    // compute linear acceleration
    RotaryEncoder::Direction currentDirection = encoder.getDirection();
	if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
          pointerDirection = ANTI_CLOCKWISE;
        }
		else pointerDirection = CLOCKWISE;
    rotatePointer(pointerDirection,1);
	rotatePointer(pointerDirection,1);
    Serial.print(newPos);
    Serial.println();
    pos = newPos;
  } // if
}

int8_t x1=0;
int8_t x2=15;
int8_t y1=3;
int8_t y2=4;
void rotatePointer(uint8_t direction, uint8_t steps)
{
    if(direction==CLOCKWISE){
	  if(x1==0 && y1>0)y1 -= steps;
	  else if(y1==0 && x1<15) x1 += steps;
	  else if(x1==15 && y1<7) y1 += steps;
	  else if(y1==7 && x1>0) x1 -= steps;
	
	  if(x2==0 && y2>0)y2 -= steps;
	  else if(y2==0 && x2<15) x2 += steps;
	  else if(x2==15 && y2<7) y2 += steps;
	  else if(y2==7 && x2>0) x2 -= steps;
	}
	else{
		if(x1==0 && y1<7)y1 += steps;
	  else if(y1==7 && x1<15) x1 += steps;
	  else if(x1==15 && y1>0) y1 -= steps;
	  else if(y1==0 && x1>0) x1 -= steps;
	
	  if(x2==0 && y2<7)y2 += steps;
	  else if(y2==7 && x2<15) x2 += steps;
	  else if(x2==15 && y2>0) y2 -= steps;
	  else if(y2==0 && x2>0) x2 -= steps;
	}
  matrix.clear();
  matrix.drawLine(x1,y1, x2,y2, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  //delay(500);
}
