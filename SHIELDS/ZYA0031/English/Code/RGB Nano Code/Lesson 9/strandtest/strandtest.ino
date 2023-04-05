//2021.8.27

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    13

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
   
    rainbow(2);             // Flowing rainbow cycle along the whole strip
    RGB(1,50);
    RGB(2,100);
    RGB(3,100);
}

void RGB(int num,int time)
{
    // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
   strip.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<LED_COUNT; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    strip.setPixelColor(i-1, strip.Color(0, 0, 0));
    for (int j = 0; j < 255; j++)
    {
        if(num == 1)
        {
            strip.setPixelColor(i, strip.Color(j, 0, 0));
        }
        else if(num == 2)
        {
            strip.setPixelColor(i, strip.Color(0, j, 0));
        }
        else if(num == 3)
        {
            strip.setPixelColor(i, strip.Color(0, 0, j));
        }
    }
    strip.show();   // Send the updated pixel colors to the hardware.
    delay(time); // Pause before next pass through loop
  }

}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:

  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {    
     
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
  
  
       // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue))); 
      
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
     
  }
}
