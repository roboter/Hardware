#ifndef _CONFIG_H_
#define _CONFIG_H_

//screen
#define TFT_LED_PIN 32
#define TFT_DC_PIN 17
#define TFT_CS_PIN 16
#define TFT_MOSI_PIN 23
#define TFT_CLK_PIN 5
#define TFT_RST_PIN 9
#define TFT_MISO_PIN 19

//SD card
#define TFCARD_CS_PIN 4

//number of buttons
#define NUM_BTN 3

//buttons ID
#define BTN_A 0
#define BTN_B 1
#define BTN_C 2
#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_C 2
#define BUTTON_A_PIN 35//39
#define BUTTON_B_PIN 34//35
#define BUTTON_C_PIN 39//34

// BEEP PIN
#define SPEAKER_PIN 25
#define TONE_PIN_CHANNEL 0

#define USE_SERIAL Serial

#endif /* SETTINGS_C */
