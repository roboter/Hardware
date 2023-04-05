/*Note that after the download is successful,
you need to check whether the passive buzzer 
switch has been turned on. The switch is on
the back of the passive buzzer. If there is
no sound, try sliding the switch.*/
//2021.8.26
#define Buzzer  8
int beep_bit=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
	if(beep_bit == 0)
	{
		for(int i=0;i<=3000;i++) //Let the pin send high and low levels at a frequency
		{
			digitalWrite(Buzzer,HIGH);
			delayMicroseconds(100);
			digitalWrite(Buzzer,LOW);
			delayMicroseconds(100);
		}
	}
	delay(500);  //Let the sound last for a while, then turn it off
	if(beep_bit)beep_bit=0;
	else beep_bit=1;
	
}
