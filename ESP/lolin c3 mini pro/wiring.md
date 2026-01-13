# Lolin S3 Mini Pro Wiring and Programming

> [!NOTE]
> Although the folder is named `lolin c3 mini pro`, the hardware is based on the **ESP32-S3FH4R2**.

## Features
- **MCU**: ESP32-S3FH4R2 (Dual-core, 2.4GHz Wi-Fi & Bluetooth LE)
- **Display**: 0.85” TFT (128x128, GC9107/GC9A01)
- **IMU**: QMI8658C (6-axis)
- **RGB LED**: IO8 (Data), IO7 (Power)

## Pinout
Refer to the following images in this folder:
- [Front Pinout](s3_mini_pro_v1_pinout.webp)
- [Back Pinout](s3_mini_pro_v1_pinout_back.webp)

## Programming
- **USB**: Connect via the USB-C port for programming (native USB-CDC).
- **Buttons**:
    - **BOOT**: IO0
    - **RESET**: Reset pin/button
- To enter bootloader mode: Hold **IO0**, press **RESET**, then release **IO0**.

## On-board Peripheral Pins
- **Display**: 
    - MOSI: IO11
    - SCK: IO12
    - CS: IO10
    - DC: IO13
    - RES: IO14
    - BLK: IO15
- **RGB LED**: IO8
- **IMU (I2C)**: 
    - SDA: IO5
    - SCL: IO6
- **Buttons**: IO0, IO47, IO48
- **IR**: IO9
