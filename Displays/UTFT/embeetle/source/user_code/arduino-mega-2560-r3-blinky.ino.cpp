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
#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Uncomment the next line for Arduino Mega
UTFT myGLCD(ITDB32WC, 38, 39, 40, 41); // Remember to change the model parameter to suit your display module!

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board

void setup();

void loop();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

// the loop function runs over and over again forever
void loop() {
    int buf[398];
  int x, x2;
  int y, y2;
  int r;
  
   myGLCD.show_color_bar();
  delay(2000);
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  
   myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 399, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, 399, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("*** Universal Color TFT Display Library ***", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255, 255, 0);
  myGLCD.print("< http://electronics.henningkarlsen.com >", CENTER, 227);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 399, 225);

  // Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(199, 15, 199, 224);
  myGLCD.drawLine(1, 119, 398, 119);
  for (int i = 9; i < 390; i += 10)
    myGLCD.drawLine(i, 117, i, 121);
  for (int i = 19; i < 220; i += 10)
    myGLCD.drawLine(197, i, 201, i);

  // Draw sin-, cos- and tan-lines
  myGLCD.setColor(0, 255, 255);
  myGLCD.print("Sin", 5, 15);
  for (int i = 1; i < 398; i++)
  {
    myGLCD.drawPixel(i, 119 + (sin(((i * 0.9) * 3.14) / 180) * 95));
  }

  myGLCD.setColor(255, 0, 0);
  myGLCD.print("Cos", 5, 27);
  for (int i = 1; i < 398; i++)
  {
    myGLCD.drawPixel(i, 119 + (cos(((i * 0.9) * 3.14) / 180) * 95));
  }

  myGLCD.setColor(255, 255, 0);
  myGLCD.print("Tan", 5, 39);
  for (int i = 1; i < 398; i++)
  {
    y = 119 + (tan(((i * 0.9) * 3.14) / 180));
    if ((y > 15) && (y < 224))
      myGLCD.drawPixel(i, y);
  }

  delay(2000);

  // Clear the screen and draw the frame
  myGLCD.clrScr();
}

