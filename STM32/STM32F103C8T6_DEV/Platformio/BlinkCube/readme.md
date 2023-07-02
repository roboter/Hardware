## Led
```
PA1
```

## Button
```
PA8
```

# BOOT JUMPERS
```
BOOT0 = 0
BOOT1 = 1
```

### Programmed with black ST-Link clone (Geehy)

```ini
[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = stm32cube
```

# EEPROM 24c02 NOT Hardware I2C

PB4 SCL
PB6 SDA

# Links 
https://lupyuen.github.io/articles/super-blue-pill-like-stm32-blue-pill-but-better

# Display ST7789 SPI

...
DISPLAY | PCB

GND   GND
VCC   VCC_3.3V
SCL   PB1
SDA   PB3
RES   PB5
DC    PB7
BLK   PB9



This module has total of 7 pins:

1) BLK = Backlight

2) D/C = Data/Command

3) RES = Reset

4) SDA = Serial Data or SPI MOSI

5) SCL = Serial Clock or SPI SCK

(Do not get confused with the I2C pins SDA and SCK, this screen is not I2C.)

6) VCC (3.3V)

7) Ground



HARDWARE SPI IS SUPPORTED ON DIFFERENT PINS?
CS      PA4
MOSI    PA7
SCK     PA5
MISO    PA6
...


DC = DC Data / Command