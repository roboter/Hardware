
//2021.8.25
#define Buzzer  3
void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
	digitalWrite(Buzzer,HIGH);
	delay(500);
	digitalWrite(Buzzer,LOW);
	delay(500);
	
}
