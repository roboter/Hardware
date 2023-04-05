//2021.9.28

#include "IRremote.h"
#define  HW    2
#define  LED   13
int BIT_LED=0;
IRrecv irrecv(HW); 
decode_results results;  
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  Serial.begin(9600);
  pinMode(LED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    if (irrecv.decode(&results)) // have we received an IR signal?
    { 
      translateIR();
      Serial.println( results.value,HEX );
      irrecv.resume(); // receive the next value
    }
	

}


void translateIR() // takes action based on IR code received
{
  if(results.value==0xFFA857)  //Determine the received key value as an intermediate value
  {
    if(BIT_LED)BIT_LED=0;
    else BIT_LED=1;
    if(BIT_LED)digitalWrite(LED, HIGH);  //Invert the state of the LED
    else digitalWrite(LED, LOW);
    //delay(50);
  }

} 
