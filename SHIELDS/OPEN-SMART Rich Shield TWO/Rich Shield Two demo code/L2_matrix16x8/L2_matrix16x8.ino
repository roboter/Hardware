/*-------------------------------------------------------------------------
// Function: Show how to control the on board led matrix and display words, grafics.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_NeoPixel.h>

#define PIN A3
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("16x8 LED Matrix Test");
  rgb.begin();
  rgb.clear();
  rgb.show();
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {
  
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  
  matrix.clear();
  matrix.drawBitmap(0, 8, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();      // clear display
  matrix.drawPixel(0, 0, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0,0, 7,15, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0,0, 8,16, LED_ON);
  matrix.fillRect(2,2, 4,12, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3,8, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);


  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x=7; x>=-69; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hello world!");
    matrix.writeDisplay();
    delay(100);
  }
  delay(2000);
  matrix.setRotation(0);
}
