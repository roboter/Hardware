# Wiring & programming — ESP32-CAM

- Power:
  - Many modules have no USB — supply 5V to the 5V pin (the regulator provides 3.3V for ESP32).
  - Ensure sufficient current (camera + Wi-Fi may draw ~200-400mA peaks).
- Programming:
  - To enter flash mode: pull GPIO0 to GND while resetting/powering the board.
  - Connect TX/RX from USB-TTL adapter to U0R/U0T lines (verify which pins are TX/RX on the board). Use 3.3V TTL levels if connecting to pins directly.
- Camera:
  - OV2640 camera module connector is pre-attached — handle the flex cable gently.
- Safety:
  - Use a stable 5V power supply with sufficient current capability; avoid powering from weak USB ports or poor cables.

> Note: See included datasheets for exact connector pinouts and timing requirements.