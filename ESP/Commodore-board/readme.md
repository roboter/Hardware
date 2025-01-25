## ESP32-WROOM-32UE

## Arduino
`ESP32 Dev Module`

## Connections
```c
#define LED1 x
#define LED2 2
#define LED3 4

#define LED 35 -- did not work as output
#define LED 34 -- did not work as output

const int buttonPin = 0;  -- EN botton on ESP module -- same as RESET
```

```c
/* Commodore IEC Pins */
#define IEC_HAS_RESET // Reset line is available
                                                //       WIRING
                                                //      C64    DIN6
#define PIN_IEC_ATN             GPIO_NUM_32     //      ATN    3
#define PIN_IEC_CLK_IN          GPIO_NUM_33     //      CLK    4
#define PIN_IEC_CLK_OUT         GPIO_NUM_33     //
#define PIN_IEC_DATA_IN         GPIO_NUM_25     //      DATA   5
#define PIN_IEC_DATA_OUT        GPIO_NUM_25     //
#define PIN_IEC_SRQ             GPIO_NUM_26     //      SRQ    1
#define PIN_IEC_RESET           GPIO_NUM_34     //      RESET  6
                                                //      GND    2
```

## Power consumptions

`0.052` A

## Links
* https://www.aliexpress.com/item/1005001438925793.html?spm=a2g0o.order_list.order_list_main.41.1e0c1802UG4LyN


## Esptool

```sh
> python -m esptool flash_id
esptool.py v4.8.1
Found 1 serial ports
Serial port COM7
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting......
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 40:22:d8:03:a8:00
Uploading stub...
Running stub...
Stub running...
Manufacturer: 5e
Device: 4016
Detected flash size: 4MB
Flash voltage set by a strapping pin to 3.3V
Hard resetting via RTS pin...
```