/*
  IMPORTANT NOTE FOR ARDUINO USERS
  ================================

  The language used in Arduino sketches is a subset of C/C++.
  However, in Embeetle you should use plain C/C++, which means
  that:

    - Functions should have a function prototype, usually
      declared at the top of the file.

    - Include statements are important to use functions,
      variables and classes from other files.

*/

#include <Arduino.h>



#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <RotaryEncoder.h>


#define SA 2
#define SB 3
#define SW 4
RotaryEncoder encoder(SB, SA);

#define RGB_PIN A3
#define NUM 4
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM, RGB_PIN, NEO_GRB + NEO_KHZ800);

int index_LED;
int PixelColor =255;
static int8_t oldbutton, newbutton;
    
uint8_t  flag_direct;

void setup();

void loop();

void SenttoNeoPixel(int index, int PixelColor);

void setup()
{
  strip.begin();
  strip.setBrightness(10);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(SW, INPUT);
}
void loop()
{

  newbutton = digitalRead(SW);
  if(newbutton != oldbutton){
	  oldbutton = newbutton;
	if(newbutton == HIGH){
		Serial.println("Button pressed");
    PixelColor--;
    if(PixelColor > 255) PixelColor = 255;
  }
}
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos) {

	if(newPos > pos) flag_direct = 1;
	else flag_direct = 0;
    pos = newPos;

	if(flag_direct){
		index_LED++;
		if (index_LED>16) index_LED=16;
		SenttoNeoPixel(index_LED, PixelColor);
	}
	else
     {
      index_LED--;
      if(index_LED<0)
      index_LED=0;
      SenttoNeoPixel(index_LED, PixelColor);
     }
  } 
  
}



void SenttoNeoPixel(int index, int PixelColor)
{
  for(uint16_t i=0; i< index; i++) {
      strip.setPixelColor(i, strip.Color(PixelColor, 0, 0));//red
      
  }
  for(uint16_t i=index; i< 16; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));//black
  }
  strip.show();
}

