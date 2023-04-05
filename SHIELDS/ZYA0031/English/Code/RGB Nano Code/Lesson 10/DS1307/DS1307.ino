

#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define ADDRESS_DS1307 0x68

byte timeBcd[] = {0, 0, 0, 0, 0, 0, 0};
//time = {year, month, date, day, hours, minutes, seconds};

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    lcd.begin(16,2);
    lcd.clear();
}

void loop()
{
    DS1307();
}

void DS1307()
{
    //read the time
    Wire.beginTransmission(ADDRESS_DS1307);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(ADDRESS_DS1307, 7);
    if (Wire.available() >= 7)
    {
        for (int i = 0; i < 7; i++)
        {
            timeBcd[6-i] = Wire.read();
        }
    }
    
    //print
    Serial.print("20"); Serial.print(timeBcd[0], HEX); Serial.print("/");
    Serial.print(timeBcd[1], HEX); Serial.print("/"); Serial.print(timeBcd[2], HEX);
    Serial.print(" "); Serial.print(BcdToDay(timeBcd[3])); Serial.print(" ");
    Serial.print(timeBcd[4], HEX); Serial.print(":");
    Serial.print(timeBcd[5], HEX); Serial.print(":");
    Serial.print(timeBcd[6], HEX); Serial.println();

    lcd.setCursor(0, 0);
    lcd.print("20");
    lcd.setCursor(2, 0);
    lcd.print(timeBcd[0], HEX);
    lcd.setCursor(4, 0);
    lcd.print("/");
    lcd.setCursor(5, 0);
    lcd.print(timeBcd[1], HEX);
    lcd.setCursor(7, 0);
    lcd.print("/");
    lcd.setCursor(8, 0);
    lcd.print(timeBcd[2], HEX);
    lcd.setCursor(10, 0);
    lcd.print("week:");
    lcd.setCursor(15, 0);
    lcd.print(timeBcd[3], HEX);

    lcd.setCursor(0, 1);
    lcd.print(timeBcd[4], HEX);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(timeBcd[5], HEX);
    lcd.setCursor(5, 1);
    lcd.print(":");
    lcd.setCursor(6, 1);
    lcd.print(timeBcd[6], HEX);
}
// Convert binary coded decimal to day
String BcdToDay(byte val)
{
    String res;
    switch(val)
    {
        case 1: res = "Sunday"; break;
        case 2: res = "Monday"; break;
        case 3: res = "Tuesday"; break;
        case 4: res = "Wednesday"; break;
        case 5: res = "Thursday"; break;
        case 6: res = "Friday"; break;
        case 7: res = "Saturday"; break;
        default: res = "Error!";
    }
    return res;
}
