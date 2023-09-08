//Demo for Sound Sensor module 
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Arduino IDE: Arduino 1.6.5
//Store: http://www.aliexpress.com/store/1199788

int val;
int Threshold = 200;
void setup()
{
	Serial.begin(9600);
	pinMode(13,OUTPUT);
	digitalWrite(13,LOW);
}

void loop()
{
	val = analogRead(A2);
	Serial.println(val);
	if(val>Threshold) digitalWrite(13,HIGH);
	else digitalWrite(13,LOW);
	delay(100);
}
