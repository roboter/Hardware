# TTGO TS V1.0 (T10) Wiring and Programming

This folder contains resources for the TTGO TS V1.0 and V1.2 series boards.

## Board Features
- **MCU**: ESP32
- **Display**: 1.44" TFT LCD (ST7735)
- **Audio**: NS4148 amplifier with speaker.
- **MicroSD Card Slot**: SPI based.
- **User Buttons**: IO34, IO35, IO39.
- **User LED**: GPIO22.

## Programming
- **Interface**: Micro-USB (CP210X).
- **IDE**: Arduino IDE.
- **Board Selection**: `ESP32 Dev Module`.

## Pinout Definitions (Arduino)
```c
// Display (ST7735)
#define TFT_CS   16
#define TFT_RST  9
#define TFT_DC   17
#define TFT_SCLK 5
#define TFT_MOSI 23
#define TFT_BL   27

// Buttons
#define BUTTON_1 35
#define BUTTON_2 34
#define BUTTON_3 39

// Audio
#define SPEAKER_PIN 25

// LED
#define LED_BUILTIN 22
```

## Links
- [TTGO-TS-V1.0 GitHub](https://github.com/LilyGO/TTGO-TS-V1.0)
- [TTGO-TS-V1.2 GitHub](https://github.com/LilyGO/TTGO-TS-V1.2)
- [TTGO-T4-T10 Test Code](https://github.com/Xinyuan-LilyGO/TTGO-T4-T10-TestCode)
