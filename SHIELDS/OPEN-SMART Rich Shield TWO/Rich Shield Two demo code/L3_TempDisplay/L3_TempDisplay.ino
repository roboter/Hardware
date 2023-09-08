/*-------------------------------------------------------------------------
// Function: Get the temperature from a single DS18B20 and display on the led matrix.
//          Every time the temperature rises one degree, the digital tube lights up one more level.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/
#include <OneWire.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "TM1651.h"
#include <Adafruit_NeoPixel.h>

#define PIN A3
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

#define CLK 10//pins definitions for TM1651 and can be changed to other ports       
#define DIO 11
TM1651 batteryDisplay(CLK,DIO);
OneWire  ds(5);  // on pin 2 (a 4.7K resistor is necessary)
Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
uint8_t level = 2;
int8_t temp0;
void setup()
{
  Serial.begin(9600);
  //-------------
  rgb.begin();
  rgb.clear();
  rgb.show();
  //-------------
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1);
  batteryDisplay.init();
  batteryDisplay.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  temp0 = readTemp();
  batteryDisplay.displayLevel(level);
}
void loop()
{
  int8_t celsius;
  celsius = readTemp();
  displayTemp(celsius);
  batteryDisplay.displayLevel(level+celsius-temp0);
}
int8_t readTemp()
{
	byte data[12];
  float celsius;
  ds.reset();
  ds.skip();
  ds.write(0x44, 0);        // start conversion
  delay(750);     // maybe 750ms is enough, maybe not
  ds.reset();
  ds.skip();
  ds.write(0xBE);         // Read Scratchpad
  Serial.print("  Data = ");
  for (unsigned char i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
   // Serial.print(data[i], HEX);
  //  Serial.print(" ");
  }

    int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  // at lower res, the low bits are undefined, so let's zero them
  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  //// default is 12 bit resolution, 750 ms conversion time
  celsius = (float)raw / 16.0;
  return celsius;
}
void displayTemp(int8_t temp)
{
	matrix.clear();
    matrix.setCursor(0,0);
    matrix.print(temp);
	matrix.print('c');
    matrix.writeDisplay();
}
