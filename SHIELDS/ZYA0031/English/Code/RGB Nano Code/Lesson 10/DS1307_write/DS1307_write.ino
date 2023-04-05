/*
real time clock using DS1307
function: set the time
*/

#include <Wire.h>

#define ADDRESS_DS1307 0x68

byte timeDec[] = {21, 9, 30, 4, 14,58, 10};
byte timeBcd[] = {0, 0, 0, 0, 0, 0, 0};
//time = {year, month, date, day, hours, minutes, seconds};

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    //convert decimal to BCD code
    int i;
    for (i = 0; i < 7; i++)
    {
        timeBcd[i] = DecToBcd(timeDec[i]);
    }

    //set the time
    Wire.beginTransmission(ADDRESS_DS1307);
    Wire.write(0x00);
    for (i = 0; i < 7; i++)
    {
        Wire.write(timeBcd[6-i]);
    }
    Wire.endTransmission();

    Serial.println("Time has been set.");

}

void loop()
{
    delay(4000);
}

// Convert normal decimal numbers to binary coded decimal
byte DecToBcd(byte val)
{
    byte res;
    if ((val <= 99) && (val >= 0))
    {
        res = ((val/10)<<4) | (val%10);
    }
    else
    {
        res = 0;
        Serial.println("Error");
    }
    return res;
}
// Convert binary coded decimal to normal decimal numbers
byte BcdToDec(byte val)
{
    byte res;
    if (val <= 0x99)
    {
        res = (val >> 4)*10 + (val & 0x0F);
    }
    else
    {
        res = 0;
        Serial.println("Error");
    }
    return res;
}
