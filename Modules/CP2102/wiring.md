# Wiring — CP2102 / FT232RL USB‑to‑TTL

Typical pins:
- VCC: 3.3 V or 5 V (check jumper or silkscreen)
- GND: common ground
- TXD: transmit (to RX of target)
- RXD: receive (to TX of target)
- DTR/RTS: optional for auto‑reset / bootloader

Notes:
- Use correct voltage level for your UART device (3.3 V recommended for many microcontrollers).