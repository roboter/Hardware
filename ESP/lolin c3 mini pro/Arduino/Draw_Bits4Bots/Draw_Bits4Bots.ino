#include <Adafruit_GFX.h>        // Core graphics library
#include <Adafruit_ST7735.h>     // Library for the ST7735 TFT screen
#include <SPI.h>

// Define the pins for your display (adjust these to your setup)
#define TFT_CS     35  // Chip select pin
#define TFT_RST    34  // Reset pin
#define TFT_DC     36  // Data/Command pin
#define TFT_BL     33  // Backlight pin (TFT_BL/IO33)

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize the backlight pin
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);  // Turn on the backlight

  // Initialize the display
  tft.initR(INITR_BLACKTAB);  // Specific initialization for the ST7735 screen
  tft.fillScreen(ST77XX_BLACK); // Clear the screen with a black background
  
  // Draw the bitmap at position (0, 0)
 // tft.drawBitmap(0, 0, myBitmap, 128, 128, ST77XX_WHITE); // Change color as needed
}

void loop() {
  // The loop remains empty for this demo
}
