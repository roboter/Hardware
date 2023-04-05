//20218.27
/*Running water light*/
int time1=0,time2=0; //Define two time summations

void setup() 
{
   // Initialize the LED lamp pins, pin 2 to pin 13
    for (int i = 2; i <= 13; i++)
    {
        pinMode(i,OUTPUT);// Set to output mode
        digitalWrite(i, LOW); // Set the default level to low
    } 
}
    
void loop() 
{ 
    for (int i = 2; i <= 13; i++)
    {
        time1++;//It keeps adding up
        digitalWrite(12, HIGH);
        digitalWrite(i, HIGH);
        delay(time1); //The duration of a high level
        
        digitalWrite(i, LOW);
        delay(time1); //The duration of a low level
        
        if(time1 == 100) time1 = 0;//Clear when the count reaches 100
        Serial.print("LED");
        Serial.println(i);
    }
    for (int i = 13; i >= 2; i--)
    {
        time2++;
        digitalWrite(2, HIGH);
        digitalWrite(i, HIGH);
        delay(time1);  //The duration of a high level
        
        digitalWrite(i, LOW);
        delay(time1); //The duration of a low level
        
        if(time2 == 100) time2 = 0;
        Serial.print("LED");
        Serial.println(i);
    }            
}
