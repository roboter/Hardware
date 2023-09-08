/*-------------------------------------------------------------------------
// Function: The battery display will show the level of the sound loundness.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/

#include "TM1651.h"
#include <Adafruit_NeoPixel.h>

#define PIN A3
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

#define CLK 10//pins definitions for TM1651 and can be changed to other ports       
#define DIO 11
TM1651 batteryDisplay(CLK,DIO);


#define SOUND_PIN A2
#define MAX_SENSORVALUE 1000
#define MIN_SENSORVALUE 8

void setup() {
    //-------------
  rgb.begin();
  rgb.clear();
  rgb.show();
  //-------------
    batteryDisplay.init();
    batteryDisplay.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop() {
	sound();
}

//-----------------------
void sound()
{
	int sensorValue = analogRead(SOUND_PIN); 
	int level = map(sensorValue, 0, MAX_SENSORVALUE, 0, MIN_SENSORVALUE); //convert the sensor value to the light level
	batteryDisplay.displayLevel(level);
}
