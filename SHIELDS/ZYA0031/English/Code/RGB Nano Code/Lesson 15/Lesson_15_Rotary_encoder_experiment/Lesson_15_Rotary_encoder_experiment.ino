//2021.9.28

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 12 // Number of 2812 lamps
#define  RGB_PIN 13  // 2812 pin definition
//Define the pin connection
int CLK = 2;//CLK->D2
int DT = 3;//DT->D3
int SW = 4;//SW->D4
const int interrupt0 = 0;//Interrupt 0 on pin 2
int count = 0;//Define the count
int lastCLK = 0;//CLK initial value
 
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);//Creating light objects

void setup()
{
	pinMode(SW, INPUT_PULLUP);
	pinMode(CLK, INPUT_PULLUP);
	pinMode(DT, INPUT_PULLUP);
	
  	pixels.begin(); // Initialize 2812 library functions
	pixels.show();
	pixels.clear(); // Lighting function
    attachInterrupt(interrupt0, ClockChanged, CHANGE);//Set the interrupt 0 handler, trigger level change

    Serial.begin(9600);
}
 
void loop()
{
	if(count<=0)count=0;
	if(count>=12)count=12;
	if (!digitalRead(SW)) //Read the button press and the count value to 0 when the counter reset
	{
		count = 0;
	}
	//Light up the corresponding RGB light
	//Change the "count" variable to change the corresponding light
	pixels.setPixelColor(count, pixels.Color(0, 255, 0));
	pixels.show();
	pixels.clear(); // Lighting function
	attachInterrupt(interrupt0, ClockChanged, CHANGE);

}
 
//Interrupt handler
void ClockChanged()
{

	if(digitalRead(SW))  //Judgment is not pressed
	{
	  int clkValue = digitalRead(CLK);//Read the CLK pin level
	  int dtValue = digitalRead(DT);//Read the DT pin level
	  if (lastCLK != clkValue)
	  {
		lastCLK = clkValue;
		count += (clkValue != dtValue ? 1 : -1);//CLK and inconsistent DT + 1, otherwise - 1
		Serial.print("count:");
	    Serial.println(count);  //Serial print rotation value
	  }
	}
}