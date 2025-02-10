#include "HX711.h"
#include <Wire.h>
#include <LCD-I2C.h>

// HX711 connections
#define LOADCELL_DOUT_PIN 6
#define LOADCELL_SCK_PIN 5
float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;
float ounces;
// Initialize HX711
HX711 scale(LOADCELL_SCK_PIN, LOADCELL_DOUT_PIN);

// Initialize the I2C LCD (make sure the address is correct)
LCD_I2C lcd(0x27, 16, 2);  // Change address if necessary

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  Wire.begin();
  // Initialize the LCD
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  lcd.print("Taring...");  // Display tare message
  delay(2000);             // Wait for a moment
  lcd.clear();             // Clear the LCD
}

void loop() {

    scale.set_scale(calibration_factor); //Adjust to this calibration factor

  // Read weight from the scale
   units = scale.get_units(), 10;  // Average of 10 readings

  // Print weight to serial monitor
  Serial.print("Weight: ");
  Serial.print(units);
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  // Display the weight on the LCD
  lcd.setCursor(0, 0);  // Set cursor to first row
  lcd.print("Weight: ");
  lcd.setCursor(0, 1);  // Set cursor to second row
  lcd.print(units);    // Print weight
  lcd.print(" g");      // Add unit (grams)

  //delay(100);  // Update every second
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
}