## Description
* processor 328p
* This board is available in two versions i.e. one runs at 5V with 16MHz clock frequency while the other runs at 3.3V with a clock frequency of 8MHz.

## Arduino Pro Mini Pin Description:

Now you’ve got a little intro about Arduino Pro Mini. In this section, we’ll discuss the pin description of each pin available on the board.

* **Digital I/O Pins:** you’ll find `14` digital `I/O` pins on board that is used for the connection with external components.

* **Analog Pins:** `8` analogue pins are available on the board which can measure the voltage from `0` to `5V`.

* **PWM Pins:** `6 PWM` pins are incorporated on the board which can control the speed of the motor of the brightness of the LED.

* **Reset Pins:** 2 reset pins are available on this unit. These pins are useful to reset the board if your code hangs up in the middle of a running program. Providing `LOW` value to these pins will reset the board.

* **Vcc:** 2 `Vcc` pins are incorporated on the board which provides regulated voltage i.e. `5V` or `3.3V` based on the board you’re using.

* **GND:** 3 ground pins are available on this device.

* **Programming Header:** `FTDI` six-pin programmer is incorporated on board which is used to upload the code into the controller.

* **External Interrupts:** Two external interrupts (also known as hardware interrupts) are available on the board. There are marked as `T0` at pin `4` and `T1` at pin `5`.

* **USART:** The board comes with `USART` serial communication protocol that carries two pins `RX` and `TX`. The `RX` pin is used to receive serial data while the `TX` pin is the transmission pin used to transmit serial data.

* **SPI Communication:** The unit supports `SPI` communication protocol in which four pins `10(SS)`, `11(MOSI)`, `12(MISO)`, and `13(SCK)` are used to carry out this communication.

* **I2C Communication:** The boards also support `I2C` communication that comes with two pins `SDA` and `SCL`. The `SDA` is a serial data pin used to carry data while SCL is a serial clock line used for data synchronization clock.

## Arduino output

```sh
avrdude: Device signature = 0x1e950f (probably m328p)
```