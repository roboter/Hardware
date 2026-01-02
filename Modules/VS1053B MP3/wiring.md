# Wiring — VS1053B MP3 Codec

Typical SPI wiring:
- SCLK (SCK)
- MOSI (SDI)
- MISO (SDO)
- CS (XCS)
- DCS (XDCS)
- DREQ (data request)
- RESET

Audio outputs: connect to headphone amp or line out; ensure proper decoupling.

Notes:
- Use 3.3 V logic levels.
- Check `vs1053.pdf` for detailed register and wiring notes.