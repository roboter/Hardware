// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}
unsigned char judge = 0;
char scan;

void loop()
{
  if(judge == 0)
  {
    Wire.beginTransmission(35); // transmit to device #35
    //Wire.write(7);        // sends five bytes
    Wire.write(scan); 
    Wire.endTransmission();    // stop transmitting
    judge = 1;
  }
  delay(100); 


  if(judge == 1)
  {
      Wire.requestFrom(35, 1);    // request 1 bytes from slave device #35
      if(Wire.available())
      { 
          unsigned char c = Wire.read(); // receive a byte as character
          if(c !=0x47){
            
            Serial.println(c);
  
           ++scan; 
           if(scan == 8) scan = 0; 
            judge = 0; 
           }        
     }  
  }
}
