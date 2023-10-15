/*
  IMPORTANT NOTE FOR ARDUINO USERS
  ================================

  The language used in Arduino sketches is a subset of C/C++.
  However, in Embeetle you should use plain C/C++, which means
  that:

    - Functions should have a function prototype, usually
      declared at the top of the file.

    - Include statements are important to use functions,
      variables and classes from other files.

*/

#include <Arduino.h>

#define CLK 10 // pins definitions for TM1651 and can be changed to other ports       
#define DIO 11
#define SDA_PIN 11
#define SCL_PIN 10

//I2C device found at address 0x70  !
	//************definitions for TM1651*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
	
#define STARTADDR  0xC0 
	/**** definitions for the frame of the battery display *******/
#define FRAME_ON   1
#define FRAME_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

/*
  Test Serial Connection
  
  Start a serial connection and send "Hello World"
  immediately when established. Then, send the string
  "embeetle" repeatedly, while blinking an LED.

  Most Arduinos have an on-board LED you can control. On
  the UNO, MEGA and ZERO it is attached to digital pin 13,
  on MKR1000 on pin 6. LED_BUILTIN is set to the correct
  LED pin independent of which board is used. If you want
  to know what pin the on-board LED is connected to on your
  Arduino model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.
*/

void bitWriteByte(int sda, int scl, uint8_t value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(sda, (value & 0x80) != 0);
    value <<= 1;
    digitalWrite(scl, HIGH);
    digitalWrite(scl, LOW);
  }
  // Wait for ACK (not shown here, as it depends on the TM1651 module's response)
}

void TM1651_init() {
  bitWriteByte(SDA_PIN, SCL_PIN, 0x40); // Control byte for data setting
}


void TM1651_display(uint8_t* data) {
  bitWriteByte(SDA_PIN, SCL_PIN, STARTADDR); // Start at address 0xC0
  for (int i = 0; i < 2; i++) {
    bitWriteByte(SDA_PIN, SCL_PIN, data[i]);
  }
}

// the setup function runs once
// when you press reset or power the board

void setup();

void loop();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // set up Serial library at 9600 bps
  Serial.begin(9600);
  Serial.println("Hello World");
  Serial.println("This is an Arduino Uno r3 board");
  TM1651_init();
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("embeetle");
  
  uint8_t data[] = {0x3F, 0x06}; // 0x3F is the pattern for '1', 0x06 is the pattern for '2'
  for(uint8_t i=0;i!=256;i++)
  {
    TM1651_display(i);
    delay(1000);
  }
}
