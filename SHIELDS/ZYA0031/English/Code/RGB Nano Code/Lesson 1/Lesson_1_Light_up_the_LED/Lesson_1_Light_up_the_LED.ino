//2021818
#define LED 13  //Define output pin

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  digitalWrite(LED , LOW); //Initialization, at the beginning, the pin level is low
  

}

void loop() {
  // put your main code here, to run repeatedly:
  /*Since the negative pole of our LED pin has been
  connected, we only need to use the control pin of 
  Arduino to output the high level, which is the positive
  pole, and the LED will be lit */
  digitalWrite(LED ,HIGH);
}
