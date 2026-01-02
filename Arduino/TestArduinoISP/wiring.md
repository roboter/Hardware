# Wiring & programming — TestArduinoISP

- Programming:
  - Uses USBasp (or USBasp clone) to program replaced/modified ATmega chips.
  - If using a cheap USBasp clone that behaves as USBHID, you may need to flash corrected firmware or use the "usbasp-clone" upload_protocol as shown in `platformio.ini`.
- Connections:
  - Typical ISP pins: MISO, MOSI, SCK, RESET, VCC, GND.
  - Ensure the programmer and target share a common ground and the target VCC matches the programmer voltage.
- Debugging tips:
  - If avrdude reports device signature or SCK period errors, try updating programmer firmware or adding a small delay (e.g., `-B` parameter) to slow programming.
- Safety:
  - When testing modified boards, power up with a current-limited supply to prevent damage from wiring mistakes.