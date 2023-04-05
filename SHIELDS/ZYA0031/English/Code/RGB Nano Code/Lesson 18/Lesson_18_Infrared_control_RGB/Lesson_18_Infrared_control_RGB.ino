//2021.9.30

#include "IRremote.h"
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Number of 2812 lamps
#define  RGB_PIN 13  // 2812 pin definition
#define  HW    2
IRrecv irrecv(HW); 
decode_results results;  

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);//Creating light objects
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  Serial.begin(9600);
  pixels.begin(); // Initialize 2812 library functions
  pixels.show();
  pixels.clear(); // Lighting function

}

void loop() {
  // put your main code here, to run repeatedly:
    if (irrecv.decode(&results)) // have we received an IR signal?
    { 
      translateIR();
      Serial.println( results.value,HEX );
      irrecv.resume(); // receive the next value
    }


}


void translateIR()
{
	if(results.value==0XFF30CF)  //1
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(255,0, 0)); //Received digital 1RGB display red
			pixels.show();
		}
	}
	else if(results.value==0XFF18E7)  //2
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(0,255, 0));//Received digital 2RGB display green
			pixels.show();
		}
	}
	else if(results.value==0XFF7A85)  //3
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(0,0, 255));//Received digital 3RGB display blue
			pixels.show();
		}
	}
	else if(results.value==0XFF10EF)  //4
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(255,255, 0)); //Received digital 4RGB display yellow
			pixels.show();
		}
	}
	else if(results.value==0XFF38C7)  //5
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(255,255, 255));//Received digital 5RGB display white
			pixels.show();
		}
	}
	else if(results.value==0XFF5AA5)  //6
	{
		for(int i=0;i<12;i++)
		{
			pixels.setPixelColor(i, pixels.Color(0,0, 0));//Receive digital 6RGB light off
			pixels.show();
		}
	}
	
}
