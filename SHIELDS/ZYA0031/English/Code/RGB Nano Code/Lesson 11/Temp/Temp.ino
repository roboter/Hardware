
//2021.9.28

#include <LiquidCrystal.h>
#include <Wire.h>

int NTCPin = A0;
#define SERIESRESISTOR 10000
#define NOMINAL_RESISTANCE 10000
#define NOMINAL_TEMPERATURE 25
#define BCOEFFICIENT 3950

//Do the initial setup
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);//LCD pin

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    lcd.begin(16,2); // Initialize LCD1602
    lcd.clear();// Clear the LCD screen
}

void loop() 
{
    float ADCvalue;
    float Resistance;
    ADCvalue = analogRead(NTCPin);
    Resistance = (1023 / ADCvalue) - 1;
    Resistance = SERIESRESISTOR / Resistance;

    float steinhart;
    float temp1;
    steinhart = Resistance / NOMINAL_RESISTANCE; // (R/Ro)
    steinhart = log(steinhart); // ln(R/Ro)
    steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
    steinhart -= 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart; // Invert
    steinhart += 273.15; // convert to C
    temp1 = steinhart-(steinhart*2);//Turn negative numbers into positive numbers
    
    Serial.print("Temperature: ");// temperature
    Serial.print(temp1);
    Serial.println(" ℃ ");

     //Set LCD start display pointer position, 0 column 0 row
    lcd.setCursor(0, 0);
    lcd.print("temp:");
    lcd.setCursor(5, 0);
    lcd.print(temp1); //Display temperature data
    delay(1000);
}
