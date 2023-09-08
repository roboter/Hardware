/*-------------------------------------------------------------------------
// Function: Show how to control the 4-bit RGB led.
// Hardware: OPEN-SMART ONE R3(ATmega328P board), Rich Shield Two
// Software: Arduino-1.8.7 IDE
// Product link: https://www.aliexpress.com/item/1005004421900420.html
// Doc link: https://drive.google.com/drive/folders/1V8sBBzX3-gRwBTCwtvl8yc5dPd1mSby7?usp=sharing
-------------------------------------------------------------------------*/
#include <Adafruit_NeoPixel.h>

#define PIN A3
// Parameter 1 = number of pixels in rgb
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
#define NUM 4
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
#define LEFT_TO_RIGHT 0
#define RIGHT_TO_LEFT 1

void setup() {
  rgb.begin();
  rgb.clear();
  rgb.show();
}

void loop() {
 rgb.setBrightness(40);
  // Some example procedures showing how to display to the pixels:
  colorWipe(rgb.Color(100, 100, 100), 0); // white
  delay(600);
  colorWipe(rgb.Color(50, 0, 0), 0); // Red
  delay(600);
  colorWipe(rgb.Color(0, 50, 0), 0); // Green
  delay(600);
  colorWipe(rgb.Color(0, 0, 50), 0); // Blue
  delay(600);
  colorWipe(rgb.Color(0, 0, 0), 0); // black
  delay(600);
  runLED(0xffff00, LEFT_TO_RIGHT); // yellow
  delay(600);
  colorWipe(rgb.Color(0, 0, 0), 0); // black
  delay(600);
  runLED(0xffff00, RIGHT_TO_LEFT);// yellow
  delay(600);

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<NUM; i++) {
      rgb.setPixelColor(i, c);
      
      //delay(wait);
  }
  rgb.show();
}
void runLED(uint32_t c,  uint8_t direction) {
  if(direction==LEFT_TO_RIGHT) 
    for(uint8_t i=0; i<NUM; i++) {
      rgb.setPixelColor(i, c);
	  rgb.show();
      delay(150);
    }
  else 
    for(uint8_t i=NUM; i>0; i--) {
      rgb.setPixelColor(i-1, c);
	  rgb.show();
      delay(150);
    }
}



//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < rgb.numPixels(); i=i+3) {
        rgb.setPixelColor(i+q, c);    //turn every third pixel on
      }
      rgb.show();
     
      delay(wait);
     
      for (int i=0; i < rgb.numPixels(); i=i+3) {
        rgb.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


