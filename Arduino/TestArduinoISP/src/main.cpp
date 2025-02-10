#include <Arduino.h>

#include <SoftwareSerial.h>

#define rxPin PD0

#define txPin PD1

// Set up a new SoftwareSerial object

// SoftwareSerial mySerial(rxPin, txPin);

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // pinMode(rxPin, OUTPUT);
  // pinMode(txPin, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //  mySerial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  // delay(250);
  // digitalWrite(rxPin, HIGH); // turn the LED on (HIGH is the voltage level)

  // delay(250);
  // digitalWrite(txPin, HIGH); // turn the LED on (HIGH is the voltage level)

  delay(250);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(250);                     // wait for a second

  // digitalWrite(rxPin, LOW); // turn the LED off by making the voltage LOW
  // delay(250);                     // wait for a second

  // digitalWrite(txPin, LOW); // turn the LED off by making the voltage LOW
  // delay(250);                     // wait for a second

  Serial.println("Hello!");
  // mySerial.println("World!");
}