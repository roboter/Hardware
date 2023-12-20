#include <Arduino.h>


///dots on display

//Arduino
// #define RST  12
// #define CE  11
// #define DC  10
// #define DIN 9
// #define CLK 8

//BluePill
// #define RST PC14
// #define CE PC15
// #define DC PA0
// #define DIN PA1
// #define CLK PA2
#define LED PB5

//maple
#define RST PB4
#define CE PA4
#define DC PB6
#define DIN PA7
#define CLK PA5


//#define LED PB1

// #define RST PC14           //6.1.12 RES: LOW followed by HIGH = reset
// #define ChipEnable PC15    //6.1.10 SCE: chip enable active LOW //could just connect this to ground if you have dedicated wires
// #define DCmodeSelect PA0  //6.1.9 D/C: mode select // If D/C LOW, the current byte is interpreted as command byte  If D/C = HIGH, the following bytes are stored in the display data RAM.
// #define DataIN PA1         //6.1.7 SDIN: serial data line
// #define SerialCLK PA2      //6.1.8 SCLK: serial clock line  0.0 to 4.0 Mbits/s max, -line rests low, so could be used for light control
#include "font.h"

void LcdWriteData(byte dat) {
  digitalWrite(DC, HIGH);  //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat);  //transmit serial data
  digitalWrite(CE, HIGH);
}

void LcdWriteCmd(byte cmd) {
  digitalWrite(DC, LOW);  //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd);  //transmit serial data
  digitalWrite(CE, HIGH);
}

void LcdXY(int x, int y) {
  LcdWriteCmd(0x80 | x);  // Column.
  LcdWriteCmd(0x40 | y);  // Row.
}

void LcdWriteCharacter(char character) {
  for (int i = 0; i < 5; i++) LcdWriteData(ASCII[character - 0x20][i]);
  LcdWriteData(0x00);
}

void LcdWriteString(char *characters) {
  while (*characters) LcdWriteCharacter(*characters++);
}

void setup();

void loop();

void setup() {

  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  LcdWriteCmd(0x21);  // LCD extended commands
  LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
  LcdWriteCmd(0x04);  // set temp coefficent
  LcdWriteCmd(0x14);  // LCD bias mode 1:40
  LcdWriteCmd(0x20);  // LCD basic commands
  // LcdWriteCmd(0x09); -- BLACK SCREEN
  LcdWriteCmd(0x0C);  // LCD normal video

  //for (int i = 0; i < 504; i++) LcdWriteData(0xFF);  // clear LCD

  LcdXY(20, 2);
  LcdWriteString("THE END");

  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
