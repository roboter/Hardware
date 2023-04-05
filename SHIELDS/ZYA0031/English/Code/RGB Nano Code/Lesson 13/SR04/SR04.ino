//2021.9.28

#include <LiquidCrystal.h>
#include <Wire.h>

//ehco:D3 trig:D2
#define  Trig 2 
#define  Echo 3

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //LCD pin


void setup()
{
    Serial.begin(9600);
    Wire.begin();
    lcd.begin(16,2);  // Initialize LCD1602
    lcd.clear();      // Clear the LCD screen
    pinMode(Trig,OUTPUT); //Set Tring pin to output   
    pinMode(Echo,INPUT);  //Set the Echo pin as input
}

void loop() 
{ 
    int dis = GetDistance();//Assign ultrasonic data to dis
    Serial.print(dis);
    Serial.print("cm");
    Serial.println(); 
    //Set LCD start display pointer position, 0 column 0 row
    lcd.setCursor(0, 0);
    lcd.print(dis);//Display range data
    if(dis<10){
      lcd.setCursor(1, 0);
      lcd.print("  "); 
    }else if( (dis>9) && (dis<100) ){
      lcd.setCursor(2, 0);
      lcd.print(" "); 
    }
    lcd.setCursor(5, 0);
    lcd.print("cm:");  
    delay(200);
}

float GetDistance() //Read ultrasonic sensor data
{
  float distance;
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  distance = pulseIn(Echo, HIGH) / 58.00;
  return distance;
}
