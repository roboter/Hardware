

## Introduction

`nanoESP32-C6` is a `ESP32-C6` minimum system board designed and made by Muse Lab based on `ESP32-C6-WROOM-1` module of Expressif. It features `RGB` `LED`, a `BOOT` button and a `RST` button. The dual TYPE-C USB ports including `USB` to `TTL` and native `USB` are more convenient for developers to develop and test.
<img alt="nanoESP32-C6" src="Sfbee5e59702d4e92b3ee03f7a2549696B.avif">

## Specification

<img alt="specification" src="S8bc9a5534f704ff0b51a418b6b320441o.avif">


## Features
● On-board USB to TTL
● On-board Boot button and RST button
● On-board TYPE-C and RGB LED

### Diagram
<img alt="diagram" src="S22b1382851dd447fb99d6769ea8fa4edC.avif">

## Documentation

● nanoESP32-C6 https://github.com/wuxx/nanoESP32-C6
● esp-idf https://github.com/espressif/esp-idf
● esp32-C6 get-started https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/get-started/
● esp32-C6 https://www.espressif.com/zh-hans/products/socs/esp32-C6

## Platformio

```ini
[env:esp32-c6-devkitc-1]
platform = espressif32
board = esp32-c6-devkitc-1
framework = espidf
```

## Remarks
 Seems therere no `arduino` framework in p;atformio

 ## Pins
 ```c
 #define RGBLED 8
 ```

 ## esptool
```bash
> python -m esptool flash_id

esptool.py v4.8.1
Found 1 serial ports
Serial port COM8
Connecting...
Detecting chip type... ESP32-C6
Chip is ESP32-C6 (QFN40) (revision v0.0)
Features: WiFi 6, BT 5, IEEE802.15.4
Crystal is 40MHz
MAC: 40:4c:ca:ff:fe:41:58:e4
BASE MAC: 40:4c:ca:41:58:e4
MAC_EXT: ff:fe
Uploading stub...
Running stub...
Stub running...
Manufacturer: c8
Device: 4016
Detected flash size: 4MB
Hard resetting via RTS pin...
```