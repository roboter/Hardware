//2021.9.28

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Wiring instructions
/**********************
CSN  -> D9
CE   -> D10
MOSI -> D11
SCK  -> D13
MISO -> D12

**********************/

//Initial RF24(cePin, csnPi)
RF24 radio(9,10);

//This is the transmission channel code we are about to establish
//!!To be consistent with another module
const uint64_t pipe = 0xE8E8F0F0E1LL;

//Data to be transferred
int data = 0;

void setup(void){
  Serial.begin(57600);
  //Boot chip
  radio.begin();
  //Open write channel
  radio.openWritingPipe(pipe);
}
 
void loop(void)
{
      Serial.print("Sending:");
      Serial.print(data);
      //Call radio.write(const void *buf, uint8_t len) to transfer information
      //The first parameter is the variable pointer we want to pass, and the second parameter is the size of the information to be transmitted.
      //If the transmission is successful, it will return true, otherwise it will return false.
	  
      bool ok = radio.write(&data,sizeof(int));
      if(ok)
        Serial.println(".....successed");
      else
        Serial.println(".....failed");

      data++;    //Add 1 every 200ms
      delay(200);
}