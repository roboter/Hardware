# Wiring — Heltec WiFi Kit 8 (ESP8266 + OLED + LiPo)

- Power:
  - USB supplies 5V that is regulated to 3.3V on-board. The board includes a LiPo charging circuit and LiPo connector.
  - When using external LiPo, ensure correct polarity and do not exceed the recommended battery voltage (single-cell LiPo).
- Pins:
  - ESP8266 uses 3.3V logic. Do not apply 5V to GPIOs.
- OLED & Peripherals:
  - The OLED is wired to the board and uses SPI/I2C depending on board variant; usually pre-wired and usable without additional wiring.
- Programming:
  - Uses common USB-serial workflow with CP2104/CP2014 driver — use appropriate drivers on host.
- Safety:
  - Verify battery charge circuit and do not short battery terminals. Use a current-limited supply when experimenting with modified boards.

> Note: Consult the Heltec GitHub for board-specific BSP and examples.