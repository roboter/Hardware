//Demo for PS2 Joystick module 
//by Open-Smart Team
//open_smart@163.com
//Arduino IDE: Arduino 1.6.5
//Store: http://www.aliexpress.com/store/1199788


//---------------------------
//module --- Arduino
//GND ---- GND
//VCC ---- 5V
#define JoyStick_X  A0 //X pin 
#define JoyStick_Y  A1// Y pin 

void setup()
{
  pinMode(JoyStick_X, INPUT); 
  pinMode(JoyStick_Y, INPUT); 
  
  Serial.begin(9600); // 9600 bps
}

void loop()

{
  int x,y; 
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);

  Serial.print(x ,DEC);
  Serial.print(","); 
  Serial.println(y ,DEC);

  delay(100);
}
