#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Library for the ST7735 TFT screen
#include <SPI.h>
#include "Adafruit_HX711.h"

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 14;   // Can use any pins!
const uint8_t CLOCK_PIN = 13;  // Can use any pins!

Adafruit_HX711 hx711(DATA_PIN, CLOCK_PIN);

// Define the pins for your display (adjust these to your setup)
#define TFT_CS 35   // Chip select pin
#define TFT_RST 34  // Reset pin
#define TFT_DC 36   // Data/Command pin
#define TFT_BL 33   // Backlight pin (TFT_BL/IO33)

// Define button pins (correct according to schematic)
#define BUTTON_LEFT 0     // IO0 for the left button
#define BUTTON_CENTER 47  // IO47 for the center button
#define BUTTON_RIGHT 48   // IO48 for the right button

// Define display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  // Initialize the backlight pin
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);  // Turn on the backlight

  // Initialize the display
  tft.initR(INITR_BLACKTAB);     // Specific initialization for the ST7735 screen
  tft.fillScreen(ST77XX_BLACK);  // Clear the screen with a black background

  // Draw the bitmap at position (0, 0)
  // tft.drawBitmap(0, 0, myBitmap, 128, 128, ST77XX_WHITE); // Change color as needed

  // Set up buttons as inputs
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_CENTER, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  tft.print("Adafruit HX711 Test!");

  // Initialize the HX711
  hx711.begin();

  tft.setTextSize(3);
  // read and toss 3 values each
  Serial.println("Tareing....");
  for (uint8_t t = 0; t < 3; t++) {
    hx711.tareA(hx711.readChannelRaw(CHAN_A_GAIN_128));
    hx711.tareA(hx711.readChannelRaw(CHAN_A_GAIN_128));
    // hx711.tareB(hx711.readChannelRaw(CHAN_B_GAIN_32));
    // hx711.tareB(hx711.readChannelRaw(CHAN_B_GAIN_32));
  }
}

void loop() {
  Serial.println("Adafruit HX711 Test!");
  // delay(10000);
  if (digitalRead(BUTTON_LEFT) == LOW) {
  }
  // Read from Channel A with Gain 128, can also try CHAN_A_GAIN_64 or CHAN_B_GAIN_32
  // since the read is blocking this will not be more than 10 or 80 SPS (L or H switch)
  int32_t weightA128 = hx711.readChannelBlocking(CHAN_A_GAIN_128);
  Serial.print("Channel A (Gain 128): ");
  tft.fillScreen(0);
  tft.setCursor(0, 0);
  tft.print(weightA128);
  Serial.println(weightA128);

  // // Read from Channel A with Gain 128, can also try CHAN_A_GAIN_64 or CHAN_B_GAIN_32
  int32_t weightB32 = hx711.readChannelBlocking(CHAN_B_GAIN_32);
  Serial.print("Channel B (Gain 32): ");
  Serial.println(weightB32);
}
