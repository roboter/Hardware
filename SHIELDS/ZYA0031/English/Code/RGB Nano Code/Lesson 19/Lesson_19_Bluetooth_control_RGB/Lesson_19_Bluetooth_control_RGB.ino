
//2021.9.30

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Number of 2812 lamps
#define  RGB_PIN 13  // 2812 pin definition
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);//Creating light objects
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin(); // Initialize 2812 library functions
  pixels.show();
  pixels.clear(); // Lighting function

}


void loop() {
  // put your main code here, to run repeatedly:
  HC_06(); //Run Bluetooth processing function
  

	
}


void HC_06()
{
	int serialData;
	if(Serial.available() > 0)      //Determine whether the received data is greater than 0
    {
		//Serial.println(Serial.read());
		serialData = Serial.read(); //Receive order function
		if('R' == serialData )  //R
		{
			Serial.println("ok");
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(255,0, 0)); //The bluetooth receives the "R" character RGB from the mobile phone APP and displays red
				pixels.show();
			}
		}
		else if('G' == serialData )  //G
		{
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(0,255, 0));//The bluetooth receives the "G" character RGB from the mobile phone APP and displays green
				pixels.show();
			}
		}
		else if('B' == serialData )  //B
		{
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(0,0, 255));//Bluetooth receives the "B" character RGB from the mobile phone APP and displays blue
				pixels.show();
			}
		}
		else if('Y' == serialData )  //Y
		{
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(255,255, 0)); //The bluetooth receives the "Y" character RGB from the mobile phone APP and displays yellow
				pixels.show();
			}
		}
		else if('W' == serialData )  //W
		{
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(255,255, 255));//Bluetooth receives the "W" character RGB from the mobile phone APP and displays white
				pixels.show();
			}
		}
		else if('O' == serialData )  //O
		{
			for(int i=0;i<12;i++)
			{
				pixels.setPixelColor(i, pixels.Color(0,0, 0));//Bluetooth receives the "O" character RGB from the mobile phone APP is turned off
				pixels.show();
			}
		}
	}
	
}










