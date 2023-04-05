//2021.8.25
#define  LED     13
#define  button  2 

int key_ok=0;   //Define the data variables required by the project
int LED_en=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT);  //Define pin port work type
  pinMode(LED,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //Determine whether there is a button pressed, read the button level
  if(digitalRead(button))   
  {
    if(key_ok)  //Determine whether the button is pressed
    {
      key_ok = 0;
      if(LED_en)LED_en=0;  //Determine whether the last flag bit is established
      else LED_en = 1;     
    }
  }
  else
  {
    delay(20);  //Delayed debounce
    if(!digitalRead(button)) key_ok = 1;
  }
  
  //When a button is pressed, the pin port status is reversed
  if(LED_en) digitalWrite(LED,HIGH);  
  else digitalWrite (LED,LOW);

}
