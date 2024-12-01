#include "font.h"
#include <Adafruit_NeoPixel.h>

#define PIN 3
#define MATRIX_WIDTH 8                          // Width of the 8x8 matrix
#define MATRIX_HEIGHT 8                         // Height of the 8x8 matrix
#define NUM_PIXELS MATRIX_WIDTH * MATRIX_HEIGHT  // Total number of pixels in one matrix
#define MAXNUM 50

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


// Function to initialize a NeoPixel matrix
void initializeMatrix( int brightness) {
  matrix.begin();                    // Initialize the NeoPixel library
  matrix.show();                     // Turn off all pixels
  matrix.setBrightness(brightness);  // Set brightness (0-255)
}

void setup() {
  // Initialize all matrices with a brightness of 50
  initializeMatrix(50);
}

// Function to display a single digit on a given matrix
void displayDigit( int digit) {
  // Ensure the digit is valid (0-9)
  if (digit < 0 || digit > 9) {
    return;  // Invalid digit, do nothing
  }

  // Get the font for the digit
  const uint8_t* font = basic_font[digit];

  // Loop through each row of the 8x8 matrix
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    for (int col = 0; col < MATRIX_WIDTH; col++) {
      // Check if the pixel should be ON (1) or OFF (0)
      if (font[row] & (1 << (7 - col))) {
        // Calculate the pixel index in the linear array (row-major order)
        int pixelIndex = row * MATRIX_WIDTH + col;
        matrix.setPixelColor(pixelIndex, matrix.Color(MAXNUM, MAXNUM, MAXNUM));  // Set color to white
      } else {
        // Turn off the pixel
        int pixelIndex = row * MATRIX_WIDTH + col;
        matrix.setPixelColor(pixelIndex, matrix.Color(0, 0, 0));  // Set color to black
      }
    }
  }

  matrix.show();  // Update the LED matrix
}

// Function to display a 3-digit number on the NeoPixel matrices
void displayNumber(int number) {
  // Ensure the number is between 0 and 999
  if (number < 0 || number > 999) {
    return;  // Invalid number, do nothing
  }

  // Extract the digits of the number
  int digits[3];
  digits[0] = number / 100;          // Hundreds place
  digits[1] = (number / 10) % 10;    // Tens place
  digits[2] = number % 10;           // Ones place

  displayDigit(digits[2]);  // Display the current digit
}

void loop() {
  // Display digits 0-9 in sequence
  // for (int i = 0; i < 10; i++) {
  //   displayDigit(matrix1, i);  // Display the current digit
  //   displayDigit(matrix2, i);  // Display the current digit
  //   delay(1000);               // Wait 1 second
  // }

  // Example: Display numbers 0-999 in sequence
  for (int i = 0; i <= 999; i++) {
    displayNumber(i);
    delay(1000);  // Wait 1 second
  }
}