# TTGO ESP32 with 18650 Battery & OLED Wiring

## Power Supply
- **18650 Battery**: Features an integrated holder on the back.
- **Micro-USB**: Power and charging (0.5A charging current).
- **Power Switch**: Controls the power to the board.
- **Charging LED**: Green (Full), Red (Charging).
- **Battery Measurement**: Connected to **GPIO33** (Analog).

## OLED Display (SSD1306)
The OLED is connected via I2C.
- **SDA**: GPIO5
- **SCL**: GPIO4
- **Address**: 0x3c

## Programming and Debugging
- **USB-to-Serial**: CP210X.
- **Buttons**:
    - **BOOT**: GPIO0
    - **RESET**: Reset button
- **Upload Sequence**: 
    1. Turn OFF power switch.
    2. Hold **BOOT** button.
    3. Start upload from IDE.
    4. Turn ON power switch.
    5. Release **BOOT** button.

## On-board Peripherals
- **User LED**: GPIO16 (Active High).
- **User Button**: GPIO0 (Shared with BOOT).

## Pinout
Refer to [pinout.png](pinout.png) and [esp32_ttgo_oled_battery_thing_pinout-1024x724.png](esp32_ttgo_oled_battery_thing_pinout-1024x724.png).
