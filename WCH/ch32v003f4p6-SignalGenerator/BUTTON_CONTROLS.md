# Si5351 VFO/RF Generator - Button Controls

## Overview
This project implements a VFO (Variable Frequency Oscillator) / RF Generator using the Si5351 clock generator chip with an OLED display and button controls.

## Hardware Setup
- **MCU**: CH32V003F4P6
- **Display**: SSD1306 128x64 OLED (I2C)
- **Generator**: Si5351 Clock Generator (I2C)
- **Buttons**: 5 buttons (UP, DOWN, LEFT, RIGHT, ENTER)

## Button Controls

### UP Button
- **Function**: Increase frequency
- **Behavior**: 
  - Single press: Increase by current step size
  - Hold: After 300ms, starts repeating at increasing speed
  - Fast repeat: After 10 repeats, accelerates to 2x speed

### DOWN Button
- **Function**: Decrease frequency
- **Behavior**: 
  - Single press: Decrease by current step size
  - Hold: After 300ms, starts repeating at increasing speed
  - Fast repeat: After 10 repeats, accelerates to 2x speed

### LEFT Button
- **Function**: Decrease step size
- **Step Sizes**: 1Hz → 10Hz → 100Hz → 1kHz → 10kHz → 100kHz → 1MHz → (cycles back to 1Hz)

### RIGHT Button
- **Function**: Increase step size
- **Step Sizes**: 1Hz → 10Hz → 100Hz → 1kHz → 10kHz → 100kHz → 1MHz → (cycles back to 1Hz)

### ENTER Button
- **Function**: Toggle RX/TX mode
- **RX Mode**: 
  - Shows "RX" indicator
  - IF frequency is added (configured in code)
  - Displays "LO" for Local Oscillator
- **TX Mode**:
  - Shows "TX" indicator
  - No IF offset (VFO mode)
  - Displays "VFO"

## Display Layout

```
┌─────────────────────────────────────────┐
│ RX  40m  VFO        [STEP:1k]           │ ← Status bar
├─────────────────────────────────────────┤
│                                         │
│   07.100.000                            │ ← Large frequency display
│                    MHz                  │
│                                         │
│                                         │
│ IF: 455kHz                              │
│ S: [████████░░]                         │ ← S-meter
└─────────────────────────────────────────┘
```

### Status Bar (Top)
- **RX/TX**: Current mode (RX = filled box, TX = outlined box)
- **Band**: Current amateur radio band (160m, 80m, 40m, etc.)
- **VFO/LO**: Frequency mode
- **STEP**: Current frequency step size

### Main Display
- **Large Frequency**: Shows frequency in format `XX.XXX.XXX`
- **Unit**: MHz or kHz depending on frequency range
- **IF Display**: Shows IF frequency when in RX mode
- **S-Meter**: Signal strength indicator (0-9, +20dB)

## Frequency Range
- **Minimum**: 10 kHz
- **Maximum**: 225 MHz (Si5351 limit)
- **Default**: 7.1 MHz (40m band)

## Amateur Radio Bands Supported
- 160m: 1.8 - 2.0 MHz
- 80m: 3.5 - 4.0 MHz
- 40m: 7.0 - 7.3 MHz
- 30m: 10.1 - 10.15 MHz
- 20m: 14.0 - 14.35 MHz
- 17m: 18.068 - 18.168 MHz
- 15m: 21.0 - 21.45 MHz
- 12m: 24.89 - 24.99 MHz
- 10m: 28.0 - 29.7 MHz

## Configuration

### IF Frequency
Edit line 11 in `main.c`:
```c
#define IF 455  // Enter your IF frequency in kHz
```

Common IF frequencies:
- **455 kHz**: Standard AM radio
- **10.7 MHz**: FM radio
- **9 MHz**: Common HF receiver

### Initial Frequency
Edit line 13 in `main.c`:
```c
static uint32_t freq = 7100000;  // 7.1 MHz default
```

## Usage Tips

1. **Quick Tuning**: Use UP/DOWN buttons for rapid frequency changes
2. **Fine Tuning**: Set step to 1Hz or 10Hz for precise adjustments
3. **Band Hopping**: Use large steps (10kHz, 100kHz) to quickly move between bands
4. **RX/TX Switching**: Press ENTER to toggle between receive and transmit modes
5. **Button Repeat**: Hold UP/DOWN for continuous frequency changes

## Technical Details

### Button Debouncing
- Hardware debouncing: 10ms polling rate
- Software debouncing: State change detection
- Repeat delay: 300ms initial, then accelerating

### Display Update
- Full redraw on button press
- S-meter updates every 500ms
- Optimized for 128x64 OLED

### I2C Communication
- **SSD1306**: 0x3C (7-bit address)
- **Si5351**: 0x60 (7-bit address)
- **Speed**: 400 kHz (Fast Mode)

## Troubleshooting

### Display Not Working
1. Check I2C connections (SDA, SCL)
2. Verify I2C address (0x3C for SSD1306)
3. Check power supply (3.3V or 5V)

### Si5351 Not Working
1. Check I2C connections
2. Verify Si5351 address (0x60)
3. Check crystal frequency (25 MHz)
4. Verify power supply (3.3V)

### Buttons Not Responding
1. Check button connections to GPIO
2. Verify button pull-up resistors
3. Check button definitions in code

## Future Enhancements
- [ ] Memory channels (save/recall frequencies)
- [ ] RIT/XIT offset
- [ ] Split frequency operation
- [ ] CTCSS/DCS tone generation
- [ ] Frequency scanning
- [ ] Real S-meter from ADC

## License
This project is open source and available for educational and amateur radio use.

## Credits
Based on the Arduino Si5351 Clock Generator project by TeknoTrek
Adapted for CH32V003F4P6 with button controls

