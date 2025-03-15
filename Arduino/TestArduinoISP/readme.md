## Arduino board with chip replaced to `m168pb`

## Uploading is done with USBASP clone

```ini
[env:ATmega168PB]
platform = atmelavr
board = ATmega168PB
framework = arduino
upload_protocol = usbasp-clone
```

## USB-ASP with metal case gives error
```
*  Executing task in folder m168pb: C:\Users\x\.platformio\penv\Scripts\platformio.exe run --target upload --environment ATmega168PB

Processing ATmega168PB (platform: atmelavr; board: ATmega168PB; framework: arduino)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/atmelavr/ATmega168PB.html
PLATFORM: Atmel AVR (5.1.0) > ATmega168PB
HARDWARE: ATMEGA168PB 16MHz, 1KB RAM, 16KB Flash
PACKAGES:
 - framework-arduino-avr-minicore @ 3.0.2
 - tool-avrdude @ 1.70200.0 (7.2.0)
 - toolchain-atmelavr @ 1.70300.191015 (7.3.0)
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 8 compatible libraries
Scanning dependencies...
No dependencies
Building in release mode
Checking size .pio\build\ATmega168PB\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   0.9% (used 9 bytes from 1024 bytes)
Flash: [=         ]   5.5% (used 900 bytes from 16384 bytes)
Configuring upload protocol...
AVAILABLE: usbasp-clone
CURRENT: upload_protocol = usbasp-clone
Looking for upload port...
Uploading .pio\build\ATmega168PB\firmware.hex
avrdude error: cannot find USB device with vid=0x16c0 pid=0x5dc
avrdude error: unable to open programmer usbasp-clone on port usb
```

## USBASP metall case

screenshot
```
USBHID
USBID 03EB C8B4
```

it is not compatible with avrusb but can be done
Converting Cheap Chinese USBHID Fake USBasps Into Real USBasps:
https://blog.lincomatic.com/converting-cheap-chinese-usbhid-fake-usbasps-into-real-usbasps/


##

```
avrdude: device signature = 0x1e9415 (probably m168pb)

```

## AVRISP Error
```
avrdude warning: verification mismatch
        device 0x63 != input 0x6b at addr 0x0002 (error)
```

this command fixes it:
```
 C:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -F -v -patmega328p -cusbasp -Pusb -e -Ulock:w:0x3F:m -Uefuse:w:0xFD:m -Uhfuse:w:0xDE:m -Ulfuse:w:0xFF:m
 ```


  C:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -cusbasp -p m168pb -B 5 -V -e -U lock:w:0x3F:m -U hfuse:w:0xDF:m -U lfuse:w:0xFF:m -U efuse:w:0xF8:m
C:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -cusbasp -p m168pb -B 1 -V -D -U flash:w:C:\Users\robby\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\bootloaders\atmega\ATmegaBOOT_168_pro_8MHz.hex:i
C:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\robby\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -c usbasp -p m168pb -B 5 -V -U lock:w:0xCF:m


avrdude error: cannot set sck period; please check for usbasp firmware update
avrdude error: program enable: target does not answer (0x01)
avrdude error: initialization failed, rc=-1