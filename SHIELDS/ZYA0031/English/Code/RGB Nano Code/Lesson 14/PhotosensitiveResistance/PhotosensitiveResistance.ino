
//2021.9.28
int inputValue = 0;

//Define the pins
#define RES_Pin A0 //A0 Connect the photoresistor
#define LED_Pin 4  //D4 Connect the LED pins


void setup()
{
    Serial.begin(9600);
    pinMode(LED_Pin, OUTPUT);
}

void loop() 
{
    //Read the photosensitive resistance value
    inputValue = analogRead(RES_Pin);

    Serial.print("Value=");
    Serial.println(inputValue);
    
    //When the light is low, turn on the light
    if (inputValue < 500) 
    {
        digitalWrite(LED_Pin, HIGH);
    }  
    else //When the light is bright, turn off the light
    {
       digitalWrite(LED_Pin, LOW);
    }
}
