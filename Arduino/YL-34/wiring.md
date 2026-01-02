# Wiring — YL-34 ATmega development board

- Power options:
  - DC-005 jack (5.5×2.1 mm) — supply 5V regulated.
  - ISP programming port can also provide VCC during programming.
  - Board also has VCC/GND pairs for direct power wiring.
- Programming:
  - Standard 6-pin ISP header for SPI/ISP programming (MISO/MOSI/SCK/RESET/VCC/GND).
- Pins:
  - All ATmega I/O pins routed to headers — refer to silkscreen for exact mapping.
- Safety:
  - When using external power through VIN or DC jack, ensure correct polarity and voltage (5V regulated).
  - Verify ISP programmer voltage before connecting to avoid damaging the MCU or programmer.