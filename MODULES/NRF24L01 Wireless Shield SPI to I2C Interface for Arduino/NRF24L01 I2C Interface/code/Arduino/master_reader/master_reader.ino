

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device

unsigned char ppt =0;

#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}
unsigned char judge = 0,good;

void loop()
{

// Wire Master Reader 
if(judge == 0)
{
      Wire.requestFrom(35, 1);    // request 6 bytes from slave device #2
      if(Wire.available())
      { 
          good = Wire.read(); // receive a byte as character
         
         
          if(good !=0x47){
              //Serial.println(good) ;
              //Serial.println("Recieve code") ;

              
              judge = 1;
              }
    
     }
}


// Wire Master Write
if(judge == 1)
{
 Wire.beginTransmission(35); // transmit to device #35
  //Wire.write(7);        // sends five bytes
  Wire.write(good);              // transfer character 1 then salve will be display "hello ,homepage!"
  
  Wire.endTransmission();    // stop transmitting
  Serial.println(good) ;
  judge = 0;
}



 delay(100);

}
