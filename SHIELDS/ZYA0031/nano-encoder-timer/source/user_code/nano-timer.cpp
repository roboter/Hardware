
#include <Arduino.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define CLK 2
#define DT 9
#define SW 8

const int interrupt0 = 0;
int count = 0;//Define the count
int  lastCLK = 0;//CLK initial value

void setup();

void loop();

//void ClockChanged()
//{
//	if(digitalRead(SW))
//	{
//		int clkValue = digitalRead(CLK);
//		int dtValue = digitalRead(DT);
//		if (lastCLK != clkValue)
//		{
//			lastCLK = clkValue;
//			count += (clkValue != dtValue ? 1 : -1);
//			lcd.print(count);
//		}
//	}
//}

//The interrupt handlers
void ClockChanged()
{
  int clkValue = digitalRead(CLK);//Read the CLK pin level
  int dtValue = digitalRead(DT);//Read  the DT pin level
  if (lastCLK != clkValue)
  {
    lastCLK = clkValue;
    count += (clkValue != dtValue ? 1 : -1);//CLK and inconsistent DT + 1, otherwise  - 1

    Serial.print("count:");
    Serial.println(count);
   // LedOutput(count);
  }
}

void setup() {
	// initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(CLK, INPUT_PULLUP);
	pinMode(DT, INPUT_PULLUP);
	pinMode(SW, INPUT_PULLUP);
	
	attachInterrupt(interrupt0, ClockChanged, CHANGE);
	
	lcd.begin(16,2);
	lcd.clear();
	Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
	
	if (!digitalRead(SW) && count != 0) //Read the button  press and the count value to 0 when the counter reset
  {
    count = 0;
    Serial.print("count:");
    Serial.println(count);
  }
	lcd.clear();
	lcd.print(count);
//	int BTN = digitalRead(SW);
//	if(BTN == HIGH){
//		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//	}
//  //delay(1000);                       // wait for a second
//	else{
//		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//	}
//]


  delay(100);                       // wait for a second
}

