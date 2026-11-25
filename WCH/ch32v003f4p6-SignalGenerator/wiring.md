# Wiring — CH32V003F4P6 Signal Generator (Si5351A + SSD1306)

Complete hardware connection guide matching [`source/User/main.h`](source/User/main.h) and [`source/User/main.c`](source/User/main.c).

---

## 1. Power & Programming (WCH-Link / SWIO)

- **Supply Voltage**: `3.3V` regulated DC for the **CH32V003F4P6**, **SSD1306**, and **Si5351A**.
  - Some Si5351A (CJMCU-5351) modules include an onboard `3.3V` LDO and `5V`-tolerant I2C level shifters (`VIN` = `3.3V–5V`). If yours is a bare `3.3V` module, power it from `3.3V` only.
- **Safety**: Use a current-limited bench supply when powering up a new build.

| WCH-Link Pin | CH32V003F4P6 Pin | Purpose |
|---|---|---|
| `3V3` | `VDD` | `3.3V` power |
| `GND` | `VSS` | Ground |
| `SWDIO` | `PD1` (SWIO) | Single-wire debug & flash programming |

---

## 2. I2C Bus (SSD1306 OLED + Si5351A)

Both devices share **I2C1** on Port C at `400 kHz` (`I2C_AFIO_REG = 0x00000000`):

| CH32V003 Pin | Signal | SSD1306 (`0x3C`) | Si5351A (`0x60`) |
|---|---|---|---|
| **`PC1`** | `I2C1_SDA` | `SDA` | `SDA` |
| **`PC2`** | `I2C1_SCL` | `SCL` | `SCL` |
| `3.3V` | `VCC` | `VCC` | `VIN` / `VCC` |
| `GND` | `GND` | `GND` | `GND` |

- **Pull-up Resistors**: Ensure `4.7 kΩ` pull-up resistors from `SDA` and `SCL` to `3.3V` are present (many SSD1306/CJMCU-5351 breakout boards already include `4.7 kΩ`–`10 kΩ` pull-ups).

---

## 3. 5-Way Navigation Buttons

Buttons are configured with internal pull-downs (**`GPIO_Mode_IPD`**) on `GPIOC` (active-high when pressed, so external `10 kΩ` pull-down resistors are not required):

| CH32V003 Pin | Button | Recommended Wiring |
|---|---|---|
| **`PC3`** | `ENTER` | Tactile switch between `3.3V` and `PC3` |
| **`PC4`** | `DOWN` | Tactile switch between `3.3V` and `PC4` |
| **`PC5`** | `LEFT` | Tactile switch between `3.3V` and `PC5` |
| **`PC6`** | `RIGHT` | Tactile switch between `3.3V` and `PC6` |
| **`PC7`** | `UP` | Tactile switch between `3.3V` and `PC7` |

> **Tip:** Add a `100 nF` capacitor across each button or to `GND` for hardware debouncing if needed.

---

## 4. Si5351A RF Outputs (`CLK0`, `CLK1`, `CLK2`)

- **Outputs**: `CLK0`, `CLK1`, and `CLK2` are `3.3V` peak-to-peak CMOS square waves (`~50 Ω` source impedance).
- **DC Blocking**: Place a `100 nF` series capacitor on each `CLK` output before connecting to RF test equipment, mixers, or receivers.
- **Harmonics**: Square waves contain odd harmonics (`3f`, `5f`, `7f`...); add a low-pass filter when a clean sine wave is required.
