/*
Function: Get the temperature from a single DS18B20 on the one wire bus.
*/
#include <OneWire.h>
#define DS18B20 5
OneWire  ds(DS18B20);  

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  byte data[12];
  float celsius, fahrenheit;
  ds.reset();
  ds.skip();
  ds.write(0x44, 0);        // start conversion
  delay(1000);     // maybe 750ms is enough, maybe not
  ds.reset();
  ds.skip();
  ds.write(0xBE);         // Read Scratchpad
  Serial.print("  Data = ");
  for (unsigned char i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();
   // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  // at lower res, the low bits are undefined, so let's zero them
  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  //// default is 12 bit resolution, 750 ms conversion time
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  Serial.println(" ");
}
