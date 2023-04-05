//2021.9.26

#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>

//Define the pins
#define DHTPIN 2 
//Define the type, DHT11 or whatever
#define DHTTYPE DHT11
//Do the initial setup
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
    Serial.begin(9600);
    dht.begin(); //DHT Start to work}
    Wire.begin();
    lcd.begin(16,2);
    lcd.clear();
}

void loop() 
{
    // It takes a few seconds between tests,
    //and this sensor is a little slow.
    delay(500);
    // It takes 250 milliseconds to read temperature or humidity
    float h = dht.readHumidity();//Read the humidity
    float t = dht.readTemperature();//Read temperature, default is Celsius
    Serial.print("Humidity: ");//humidity
    Serial.println(h);
    Serial.print("Temperature: ");// temperature
    Serial.print(t);
    Serial.println(" ℃ ");

     //Set LCD start display pointer position, 0 column 0 row
    lcd.setCursor(0, 0);
    lcd.print("temp:");
    lcd.setCursor(5, 0);
    lcd.print(t);//Display temperature data

    //Set LCD start display pointer position, 0 column 1 row
    lcd.setCursor(0, 1);
    lcd.print("humi:");
    lcd.setCursor(5, 1);
    lcd.print(h);
}
