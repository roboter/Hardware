//2021.8.27

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);// green light
  pinMode(3,OUTPUT);// Yellow light
  pinMode(4,OUTPUT);//red light
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);// Open the green light
  digitalWrite(3,LOW);// Close the yellow light
  digitalWrite(4,LOW);//Close th red light
  delay(5000);//Let the green light go on for five seconds
  
  //The green light flashes every 500 milliseconds
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);
  delay(500);
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);
  delay(500);
  digitalWrite(2,HIGH);
  delay(500);
  
  //Yellow light for one second
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  delay(1200);
  
  //The red light is on for five seconds
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(5000);
  
  //The red light blinks every 500 milliseconds
  digitalWrite(4,HIGH);
  delay(500);
  digitalWrite(4,LOW);
  delay(500);
  digitalWrite(4,HIGH);
  delay(500);
  digitalWrite(4,LOW);
  delay(500);
  digitalWrite(4,HIGH);
  delay(500);
  
}
