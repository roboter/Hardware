//2021.10.8
#define BLINKER_WIFI
#define BLINKER_MIOT_SENSOR   //Xiao Ai defined it as sensor equipment
 
#include <Blinker.h>
#include <DHT.h>
 
char auth[] = "2c2f8bf29d07";//Lamp APP to obtain the device
char ssid[] = "zhiyi1";//WiFi name
char pswd[] = "wuqian198910";//WiFi password
 
BlinkerNumber HUMI("humi");    //Define the humidity data key name
BlinkerNumber TEMP("temp");    //Define the temperature data key name
  
#define DHTPIN 2      //Define pin GPIO2(D4) for DHT11 module connection
 
#define DHTTYPE DHT11   // Use the DHT 11 temperature and humidity module
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
 
DHT dht(DHTPIN, DHTTYPE);    // dht
 
float humi_read = 0, temp_read = 0;
 
void heartbeat()
{
    HUMI.print(humi_read);        //Return humidity data to blinkerapp
    TEMP.print(temp_read);        //Return temperature data to blinkerapp
}

void miotQuery(int32_t queryCode)      //Xiao Ai classmates voice command feedback
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);

            int humi_read_int=humi_read;     //Remove humidity floating point
            BlinkerMIOT.humi(humi_read_int);     //Little love receives humidity
            BlinkerMIOT.temp(temp_read);      //Little love receives the temperature
            BlinkerMIOT.print();

}


void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
 
    Blinker.begin(auth, ssid, pswd);   
    Blinker.attachHeartbeat(heartbeat);
    dht.begin();
    BlinkerMIOT.attachQuery(miotQuery);
}
 
void loop()
{
    Blinker.run();
 
    float h = dht.readHumidity();
    float t = dht.readTemperature();
 
    if (isnan(h) || isnan(t))
    {
        BLINKER_LOG("Failed to read from DHT sensor!");
    }
    else
    {
        BLINKER_LOG("Humidity: ", h, " %");
        BLINKER_LOG("Temperature: ", t, " *C");
        humi_read = h;
        temp_read = t;
    }

 
    Blinker.delay(2000);
}
