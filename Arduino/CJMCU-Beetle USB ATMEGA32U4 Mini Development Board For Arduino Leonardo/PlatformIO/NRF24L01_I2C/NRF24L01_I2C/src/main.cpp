#include <Arduino.h>
#include <Wire.h>

#define I2C_ADDR 0x23 // 35

#define SW 9
#define VRX A0
#define VRY A1

int x = 0;
int y = 0;

unsigned char judge = 0;
char scan;

void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
    pinMode(SW, INPUT_PULLUP);
    Serial.begin(9600);           //  setup serial
    for(int i=0;i!=10; i++)
    {
        Serial.print(i);
        Serial.println(" setup");
        delay(1000);
    }
}

void loop()
{
    Serial.println("loop");
    if(judge == 0)
    {
        Serial.println("judge 0");
        Wire.beginTransmission(35); // transmit to device #35
        //Wire.write(7);        // sends five bytes
        Wire.write(scan);
        Wire.endTransmission();    // stop transmitting
        judge = 1;
    }
    delay(100);

    if(judge == 1)
    {
        Serial.println("judge 1");
        Wire.requestFrom(35, 1);    // request 1 bytes from slave device #35
        if(Wire.available())
        {
            Serial.println("available");
            unsigned char c = Wire.read(); // receive a byte as character
            Serial.println(c);
            if(c !=0x47)
            {
                Serial.println(c);
                ++scan;
                if(scan == 8) scan = 0;
                judge = 0;
            }
        }
    }
}


void loop_1() {
    bool sw = digitalRead(SW);
    x = analogRead(VRX); // 0 - 1023
    y = analogRead(VRY); // 0 - 1023

    // if(sw)
    //     Serial.println("H");//not pressed
    // else
    //     Serial.println("L");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    delay(100);
}
