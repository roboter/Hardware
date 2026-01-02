# Wiring — Arduino Pro Mini

- Voltage variants:
  - This board commonly ships in 5V/16MHz and 3.3V/8MHz variants — confirm before powering.
- Power:
  - Supply via VCC (regulated) or RAW (unregulated) pins depending on the board variant.
  - FTDI or USB-to-serial adapter should match board voltage (3.3V/5V) when programming.
- Pins:
  - SPI: 10(SS), 11(MOSI), 12(MISO), 13(SCK)
  - UART: RX/TX header (use FTDI adapter for programming)
  - I2C: SDA/SCL (confirm mapping on silkscreen)
- Safety:
  - Avoid powering the board with mismatched voltages (do not feed 5V into a 3.3V board's VCC).

> Note: When in doubt, measure Vcc with a multimeter and consult the silkscreen/board markings before connecting peripherals.