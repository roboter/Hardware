# C5000 Audio BoosterPack UART Protocol Specification

## 📡 Overview

This document describes the **UART Interface (UIF)** protocol used for communication between the **MSP430G2553** host microcontroller and the **C55x DSP** running the Audio Player Recorder Framework (APRF / "Raga") on the Audio Capacitive Touch BoosterPack.

The protocol implements a **virtual register interface** where the host sends commands to read/write virtual registers on the DSP, which in turn controls audio playback, recording, file system navigation, and OLED display operations.

---

## 🔌 Physical Layer

### UART Configuration

| Parameter | Initial Value | Runtime Value |
|-----------|--------------|---------------|
| **Baud Rate** | 9600 bps | 19200 bps (after init) |
| **Data Bits** | 8 | 8 |
| **Parity** | None | None |
| **Stop Bits** | 1 | 1 |
| **Flow Control** | None | None |
| **Clock Source** | SMCLK (1 MHz) | SMCLK (1 MHz) |

### Pin Assignment

| Signal | MSP430 Pin | Direction |
|--------|-----------|-----------|
| **TXD** | P1.2 (UCA0TXD) | MSP430 → DSP |
| **RXD** | P1.1 (UCA0RXD) | DSP → MSP430 |
| **GND** | GND | Common ground |

### Initialization Sequence

1. **Power-on**: MSP430 enables DSP power via P2.7
2. **Initial UART**: 9600 bps, 8N1
3. **DSP boot delay**: ~4 seconds (APRF initialization)
4. **Baud rate change**: Host sends `UIF_CMD_BAUDRATE` = 19200
5. **UART reconfiguration**: Both sides switch to 19200 bps
6. **Protocol active**: All subsequent communication at 19200 bps

---

## 📦 Packet Structure

### Packet Types

The protocol defines **6 packet types** identified by the first byte:

| Type ID | Name | Direction | Purpose |
|---------|------|-----------|---------|
| `0x00` | `UIF_WRITE_SCALAR_DATA` | Host → DSP | Write a 32-bit value to a virtual register |
| `0x01` | `UIF_WRITE_ARRAY_DATA` | Host → DSP | Write an array (string/buffer) to a virtual register |
| `0x02` | `UIF_READ_SCALAR_DATA` | Host → DSP | Request to read a 32-bit value from a virtual register |
| `0x03` | `UIF_READ_ARRAY_DATA` | Host → DSP | Request to read an array from a virtual register |
| `0x04` | `UIF_WRITE_COMPLETION_ACK` | DSP → Host | Acknowledgment of write operation |
| `0x05` | `UIF_READ_COMPLETION_ACK` | Host → DSP | Acknowledgment that read data was received |

---

## 📝 Command Packet Formats

### 1. Write Scalar Command

**Purpose**: Write a 32-bit value to a virtual register (e.g., set volume, send operation command)

**Packet Format** (6 bytes):

```
Byte 0: 0x00 (UIF_WRITE_SCALAR_DATA)
Byte 1: Virtual Register Address (0x00 - 0xFF)
Byte 2: Value[31:24] (MSB)
Byte 3: Value[23:16]
Byte 4: Value[15:8]
Byte 5: Value[7:0] (LSB)
```

**Example**: Set volume to 50

```
0x00 0x03 0x00 0x00 0x00 0x32
 │    │    └────────┬────────┘
 │    │          Value = 50
 │    └─ UIF_CMD_VOLUME (0x03)
 └─ Write Scalar
```

**Response** (if ACK expected): 6-byte ACK packet

```
Byte 0: 0x04 (UIF_WRITE_COMPLETION_ACK)
Byte 1: Virtual Register Address (echo)
Byte 2: 0x00 (reserved)
Byte 3: 0x00 (reserved)
Byte 4: Status[15:8]
Byte 5: Status[7:0]
```

**Status Codes**:
- `0x0000` = SUCCESS
- `0x0001` = FAILURE
- `0x0002` = UIF_CMD_NOT_SUPPORTED
- `0x0003` = UIF_CMD_INVALID
- `0x0004` = UIF_CMD_INVALID_OPERATION
- `0x0005` = UIF_BUFFER_OVERFLOW
- `0x0006` = UIF_CMD_INVALID_FOR_SYSTEM_STATE
- `0x0007` = MAX_FC_ERR (max file count reached)

---

### 2. Write Array Command

**Purpose**: Write a variable-length array (string, filename, directory name) to a virtual register

**Packet Format** (6 bytes header + N bytes data):

**Header Packet**:
```
Byte 0: 0x01 (UIF_WRITE_ARRAY_DATA)
Byte 1: Virtual Register Address
Byte 2: 0x00 (reserved)
Byte 3: 0x00 (reserved)
Byte 4: Length[15:8] (MSB)
Byte 5: Length[7:0] (LSB)
```

**Response to Header**: 6-byte ACK packet (same format as Write Scalar ACK)

**Data Packet** (sent after ACK):
```
Byte 0..N-1: Array data (N bytes, where N = length from header)
```

**Response to Data**: 6-byte ACK packet

**Example**: Write filename "song.mp3" (8 bytes)

```
Header:
0x01 0x01 0x00 0x00 0x00 0x08
 │    │                   └─ Length = 8
 │    └─ UIF_CMD_PLAY_FILE (0x01)
 └─ Write Array

<Wait for ACK>

Data:
0x73 0x6F 0x6E 0x67 0x2E 0x6D 0x70 0x33
 s    o    n    g    .    m    p    3

<Wait for ACK>
```

---

### 3. Read Scalar Command

**Purpose**: Read a 32-bit value from a virtual register (e.g., get volume, play status, file count)

**Request Packet** (6 bytes):

```
Byte 0: 0x02 (UIF_READ_SCALAR_DATA)
Byte 1: Virtual Register Address
Byte 2: 0x00 (reserved)
Byte 3: 0x00 (reserved)
Byte 4: 0x00 (reserved)
Byte 5: 0x00 (reserved)
```

**Response 1** (ACK, 6 bytes):

```
Byte 0: 0x04 (UIF_WRITE_COMPLETION_ACK)
Byte 1: Virtual Register Address (echo)
Byte 2-3: 0x00 (reserved)
Byte 4-5: Status (0x0000 = SUCCESS)
```

**Response 2** (Data, 4 bytes):

```
Byte 0: Value[31:24] (MSB)
Byte 1: Value[23:16]
Byte 2: Value[15:8]
Byte 3: Value[7:0] (LSB)
```

**Host Acknowledgment** (6 bytes):

```
Byte 0: 0x05 (UIF_READ_COMPLETION_ACK)
Byte 1: Virtual Register Address
Byte 2-5: 0x00 (reserved)
```

**Example**: Read current volume

```
Request:
0x02 0x03 0x00 0x00 0x00 0x00
 │    └─ UIF_CMD_VOLUME (0x03)
 └─ Read Scalar

<Receive ACK>

<Receive Data>
0x00 0x00 0x00 0x32
 └────────┬────────┘
       Value = 50

<Send Read Completion ACK>
0x05 0x03 0x00 0x00 0x00 0x00
```

---

## 🗂️ Virtual Register Map

### Control Registers

| Address | Name | Type | Description |
|---------|------|------|-------------|
| `0x00` | `UIF_CMD_OPERATION` | R/W | Operation command (play, pause, stop, etc.) |
| `0x01` | `UIF_CMD_PLAY_FILE` | W | Filename to play (array) |
| `0x02` | `UIF_CMD_RECORD_FILE` | W | Filename for recording (array) |
| `0x03` | `UIF_CMD_VOLUME` | R/W | Volume level (0-100) |
| `0x04` | `UIF_CMD_BALANCE` | R/W | Stereo balance |
| `0x05` | `UIF_CMD_STEREO` | R/W | Stereo mode |
| `0x06` | `UIF_CMD_CONTROL_EQ` | R/W | Equalizer control |
| `0x07` | `UIF_CMD_CONTROL_KS` | R/W | Key shift control |
| `0x08` | `UIF_CMD_RECORD_BIT_RATE` | R/W | Recording bit rate |
| `0x09` | `UIF_CMD_RECORD_SAMPLE_RATE` | R/W | Recording sample rate |
| `0x0A` | `UIF_CMD_RECORD_FORMAT` | R/W | Recording format |
| `0x0B` | `UIF_CMD_PLAY_FORMAT` | R | Playback format |
| `0x0C` | `UIF_CMD_PLAY_BIT_RATE` | R | Playback bit rate |
| `0x0D` | `UIF_CMD_PLAY_SAMPLE_RATE` | R | Playback sample rate |
| `0x0E` | `UIF_CMD_AUDIO_OUTPUT` | R/W | Audio output selection |
| `0x0F` | `UIF_CMD_AUDIO_INPUT` | R/W | Audio input selection |

### File System Registers

| Address | Name | Type | Description |
|---------|------|------|-------------|
| `0x10` | `UIF_CMD_DIR_INFO` | R | Directory information (array) |
| `0x11` | `UIF_CMD_SYS_FILE` | R/W | System file buffer (array) |
| `0x15` | `UIF_CMD_PLAY_NUMBER` | R/W | Current file number in playlist |
| `0x16` | `UIF_CMD_CURRENT_PLAY_FILE` | R | Currently playing filename (array) |
| `0x17` | `UIF_CMD_RECORD_STATUS` | R | Recording status |
| `0x18` | `UIF_CMD_CURRENT_RECORD_FILE` | R | Currently recording filename (array) |
| `0x1C` | `UIF_CMD_FILE_COUNT` | R | Number of files in current directory |
| `0x1D` | `UIF_CMD_DIR_COUNT` | R | Number of subdirectories in current directory |
| `0x1E` | `UIF_CMD_PLAY_STATUS` | R | Playback status (stopped, playing, paused, FF, RWD) |
| `0x1F` | `UIF_CMD_PLAY_MODE` | R/W | Playback mode |
| `0x20` | `UIF_CMD_SHUFFLE_STATUS` | R | Shuffle on/off status |

### System Registers

| Address | Name | Type | Description |
|---------|------|------|-------------|
| `0x12` | `UIF_CMD_POWER_IO` | R/W | I/O power control |
| `0x13` | `UIF_CMD_POWER_CORE` | R/W | Core power control |
| `0x14` | `UIF_CMD_BAUDRATE` | W | UART baud rate (9600, 19200, etc.) |
| `0x19` | `UIF_CMD_TIME_OUT` | R/W | Timeout value |
| `0x1A` | `UIF_CMD_POWER_MODE` | R/W | Power mode |
| `0x1B` | `UIF_CMD_SYS_STATUS` | R | System status |
| `0x21` | `UIF_CMD_USB_CTRL` | W | USB control (enable/disable MSC) |
| `0x22` | `UIF_CMD_USB_STATUS` | R | USB status (cable inserted, MSC enabled) |
| `0x23` | `UIF_CMD_EVENT_CTRL` | R/W | Event control |
| `0x24` | `UIF_CMD_VERSION` | R | Firmware version (array) |

### Display Registers

| Address | Name | Type | Description |
|---------|------|------|-------------|
| `0x25` | `UIF_CMD_PARAM` | W | Parameter register for display commands |
| `0x26` | `UIF_CMD_STR` | W | String buffer for display (array) |

---

## 🎮 Operation Commands

The `UIF_CMD_OPERATION` register (0x00) accepts the following command values:

### Playback Control

| Value | Command | Description |
|-------|---------|-------------|
| `0x00` | `UIF_CMD_NOP` | No operation |
| `0x01` | `UIF_CMD_PLAY_LIST` | Start playing from playlist |
| `0x02` | `UIF_CMD_PAUSE_PLAY` | Pause playback |
| `0x03` | `UIF_CMD_RESUME_PLAY` | Resume playback |
| `0x04` | `UIF_CMD_PLAY_NEXT` | Skip to next file |
| `0x05` | `UIF_CMD_PLAY_PREV` | Skip to previous file |
| `0x06` | `UIF_CMD_FF_NORMAL` | Fast forward |
| `0x07` | `UIF_CMD_REWIND_NORMAL` | Rewind |
| `0x08` | `UIF_CMD_CYCLE` | Toggle cycle mode |
| `0x09` | `UIF_CMD_SHUFFLE` | Toggle shuffle mode |
| `0x0A` | `UIF_CMD_STOP_PLAY` | Stop playback |

### Recording Control

| Value | Command | Description |
|-------|---------|-------------|
| `0x0B` | `UIF_CMD_RECORD` | Start recording |
| `0x0C` | `UIF_CMD_STOP_RECORD` | Stop recording |
| `0x0D` | `UIF_CMD_PAUSE_RECORD` | Pause recording |
| `0x0E` | `UIF_CMD_RESUME_RECORD` | Resume recording |

### Volume Control

| Value | Command | Description |
|-------|---------|-------------|
| `0x0F` | `UIF_CMD_MUTE_UNMUTE` | Toggle mute |
| `0x10-0x1F` | `UIF_CMD_VOLUME_UP_01` to `_16` | Increase volume by 1-16 steps |
| `0x20-0x2F` | `UIF_CMD_VOLUME_DOWN_01` to `_16` | Decrease volume by 1-16 steps |
| `0x59` | `UIF_CMD_VOLUME_RESET` | Reset volume to default (81) |

### Balance Control

| Value | Command | Description |
|-------|---------|-------------|
| `0x30-0x3F` | `UIF_CMD_BALANCE_LEFT_01` to `_16` | Shift balance left by 1-16 steps |
| `0x40-0x4F` | `UIF_CMD_BALANCE_RIGHT_01` to `_16` | Shift balance right by 1-16 steps |
| `0x5A` | `UIF_CMD_BALANCE_RESET` | Reset balance to center |

### File System Commands

| Value | Command | Description |
|-------|---------|-------------|
| `0x50` | `UIF_CMD_FORMAT` | Format storage |
| `0x51` | `UIF_CMD_CD` | Change directory (use with `UIF_CMD_SYS_FILE`) |
| `0x52` | `UIF_CMD_DIR` | List directory (updates `UIF_CMD_SYS_FILE`) |
| `0x53` | `UIF_CMD_DEL` | Delete file |
| `0x54` | `UIF_CMD_MKDIR` | Make directory |
| `0x55` | `UIF_CMD_NEXTF` | Next file (updates `UIF_CMD_SYS_FILE`) |
| `0x56` | `UIF_CMD_PREVF` | Previous file (updates `UIF_CMD_SYS_FILE`) |
| `0x57` | `UIF_CMD_NEXTD` | Next directory (updates `UIF_CMD_SYS_FILE`) |
| `0x58` | `UIF_CMD_PREVD` | Previous directory (updates `UIF_CMD_SYS_FILE`) |
| `0x59` | `UIF_CMD_FSTF` | First file (updates `UIF_CMD_SYS_FILE`) |
| `0x5A` | `UIF_CMD_FSTD` | First directory (updates `UIF_CMD_SYS_FILE`) |

### OLED Display Commands

| Value | Command | Description |
|-------|---------|-------------|
| `0x5B-0x7A` | `UIF_CMD_SIDSL_00` to `_31` | Store string with long ID (0-31) |
| `0x7B-0x9A` | `UIF_CMD_SID_00` to `_31` | Store string with short ID (0-31) |
| `0x9B-0xBA` | `UIF_CMD_PRTS_00` to `_31` | Print string ID (0-31) at cursor |
| `0xBB-0xDA` | `UIF_CMD_PRTSLN_00` to `_31` | Print string ID (0-31) with newline |
| `0xDB` | `UIF_CMD_SETCUR` | Set cursor position (from `UIF_CMD_PARAM`) |
| `0xDC` | `UIF_CMD_SETVP` | Set virtual plane (from `UIF_CMD_PARAM`) |
| `0xDD` | `UIF_CMD_SETSPD` | Set scroll speed (from `UIF_CMD_PARAM`) |
| `0xDE` | `UIF_CMD_SCPY` | Screen copy |
| `0xDF` | `UIF_CMD_SETFB` | Set framebuffer |
| `0xE0` | `UIF_CMD_GETFB` | Get framebuffer |
| `0xE1` | `UIF_CMD_SETWIN` | Set window (from `UIF_CMD_PARAM`) |
| `0xE2` | `UIF_CMD_SETSC` | Set scroll parameters (from `UIF_CMD_PARAM`) |
| `0xE3` | `UIF_CMD_SCON` | Scroll on |
| `0xE4` | `UIF_CMD_SCOFF` | Scroll off |
| `0xF5` | `UIF_CMD_DPON` | Display on |
| `0xF6` | `UIF_CMD_DPOFF` | Display off |

### Power Management

| Value | Command | Description |
|-------|---------|-------------|
| `0xE5` | `UIF_CMD_SLEEP` | Enter sleep mode |

---

## 🖥️ OLED Display Protocol

The OLED display is a **128×64 pixel** monochrome screen with **8 lines** of text (8 pixels per line). The display supports:

- **Virtual planes**: 64 vertical pixels can be scrolled to show different content
- **String IDs**: Pre-store strings (0-31) and print them by ID
- **Cursor positioning**: Set cursor to any line/pixel location
- **Horizontal scrolling**: Scroll text left/right at configurable speeds

### Display Workflow

1. **Store a string**:
   ```
   Write Array: UIF_CMD_STR = "Hello World"
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_SID_00 (assign to ID 0)
   ```

2. **Set cursor position**:
   ```
   Write Scalar: UIF_CMD_PARAM = 0x0000 (line 0, pixel 0)
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_SETCUR
   ```

3. **Print the string**:
   ```
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_PRTS_00 (print ID 0)
   ```

4. **Set virtual plane** (scroll to show different lines):
   ```
   Write Scalar: UIF_CMD_PARAM = 0x1000 (show line 2-3)
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_SETVP
   ```

5. **Enable horizontal scroll**:
   ```
   Write Scalar: UIF_CMD_PARAM = 0x0801 (left, rate 1, lines 0-1)
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_SETSC
   Write Scalar: UIF_CMD_OPERATION = UIF_CMD_SCON
   ```

### Cursor Position Encoding

```
Cursor = (Line << 11) | (Pixel << 8)
```

Example:
- Line 0, Pixel 0: `0x0000`
- Line 2, Pixel 4: `0x1004`
- Line 5, Pixel 0: `0x2800`

### Virtual Plane Encoding

```
VP = (Line << 11)
```

Example:
- Show lines 0-1: `0x0000`
- Show lines 2-3: `0x1000`
- Show lines 4-5: `0x2000`

### Scroll Parameter Encoding

```
Scroll = (Direction << 11) | (Rate << 8) | (FirstLine << 4) | LastLine
```

- **Direction**: 0 = left, 1 = right
- **Rate**: 1-4 (scroll speed)
- **FirstLine**: 0-7
- **LastLine**: 0-7

---

## ⏱️ Timing & Timeout

### Timeout Mechanism

Each UART transaction has a **23-second timeout** implemented using Timer A0:

```c
TA0CCR0 = 34500;  // 23s @ 1.5kHz timer clock
TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR;  // ACLK/8, Up Mode
```

If a timeout occurs:
1. LEDs flash in an error pattern (30 cycles)
2. DSP power is disabled (P2.7 = 0)
3. MSP430 resets via watchdog

### Transaction Timing

| Operation | Typical Duration | Timeout |
|-----------|-----------------|---------|
| Write Scalar | ~5 ms | 23 s |
| Write Array (header) | ~5 ms | 23 s |
| Write Array (data) | ~N ms (N = length) | 23 s |
| Read Scalar | ~10 ms | 23 s |
| Display command | ~10-50 ms | 23 s |
| File system command | ~50-500 ms | 23 s |

---

## 🔄 Protocol Sequences

### Example 1: Play a File

```
1. Host → DSP: Write Array (UIF_CMD_PLAY_FILE, "song.mp3")
2. DSP → Host: ACK (header)
3. Host → DSP: Array data ("song.mp3")
4. DSP → Host: ACK (data)
5. Host → DSP: Write Scalar (UIF_CMD_PLAY_NUMBER, 1)
6. DSP → Host: ACK
7. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_PLAY_LIST)
8. DSP → Host: ACK
```

### Example 2: Navigate to Next Directory

```
1. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_NEXTD)
2. DSP → Host: ACK (UIF_CMD_SYS_FILE now contains next dir name)
3. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_DIR)
4. DSP → Host: ACK (directory info updated)
5. Host → DSP: Read Scalar (UIF_CMD_FILE_COUNT)
6. DSP → Host: ACK
7. DSP → Host: Data (file count)
8. Host → DSP: Read Completion ACK
```

### Example 3: Display Text on OLED

```
1. Host → DSP: Write Array (UIF_CMD_STR, "Now Playing")
2. DSP → Host: ACK (header)
3. Host → DSP: Array data
4. DSP → Host: ACK (data)
5. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_SID_02)
6. DSP → Host: ACK (string stored as ID 2)
7. Host → DSP: Write Scalar (UIF_CMD_PARAM, 0x0000)
8. DSP → Host: ACK
9. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_SETCUR)
10. DSP → Host: ACK
11. Host → DSP: Write Scalar (UIF_CMD_OPERATION, UIF_CMD_PRTS_02)
12. DSP → Host: ACK (string printed)
```

---

## 🛡️ Error Handling

### Error Detection

- **Timeout**: 23-second watchdog on all UART transactions
- **ACK validation**: Check ACK packet type and status code
- **Status codes**: Non-zero status indicates error

### Error Recovery

1. **Timeout**: System reset (DSP power cycle + MSP430 watchdog reset)
2. **NACK or error status**: Retry operation or report error to user
3. **Communication hang**: Timeout triggers full system reset

### Error Codes

| Code | Name | Description |
|------|------|-------------|
| `0x00` | SUCCESS | Operation completed successfully |
| `0x01` | FAILURE | General failure |
| `0x02` | UIF_CMD_NOT_SUPPORTED | Command not supported by DSP |
| `0x03` | UIF_CMD_INVALID | Invalid command |
| `0x04` | UIF_CMD_INVALID_OPERATION | Operation not allowed in current state |
| `0x05` | UIF_BUFFER_OVERFLOW | Buffer overflow on DSP side |
| `0x06` | UIF_CMD_INVALID_FOR_SYSTEM_STATE | Command invalid for current system state |
| `0x07` | MAX_FC_ERR | Maximum file count reached (recording) |

---

## 📊 Protocol State Machine

```
┌─────────────┐
│   IDLE      │
└──────┬──────┘
       │
       ├─ Write Scalar ──► Send 6 bytes ──► Wait ACK ──► IDLE
       │
       ├─ Write Array ───► Send header ──► Wait ACK ──► Send data ──► Wait ACK ──► IDLE
       │
       └─ Read Scalar ───► Send request ──► Wait ACK ──► Wait data ──► Send ACK ──► IDLE
```

---

## 🔍 Implementation Notes

### ACK Handling

The host can optionally **ignore ACKs** for certain commands by passing `ACK_IGNORE` (1) instead of `ACK_EXPECT` (0) to `uif_writeScalar()`. This is used for:

- `UIF_CMD_SLEEP` (DSP may not respond before sleeping)
- Non-critical display updates

### Interrupt-Driven UART

The MSP430 implementation uses **interrupt-driven UART** with:

- **TX ISR**: Sends bytes from buffer until complete
- **RX ISR**: Receives bytes into buffer until expected count reached
- **LPM0**: CPU sleeps during UART transactions to save power

### Buffer Management

- **ScalarBuff[21]**: Shared buffer for TX/RX (max 21 bytes for display strings)
- **WriteCount**: Number of bytes to transmit
- **ReadCount**: Number of bytes to receive
- **write_flag / read_flag**: Transaction in progress flags

---

## 📚 Reference Implementation

See the following source files for complete implementation:

- **Protocol core**: `ACTBP_uart.c`, `ACTBP_uart.h`
- **Virtual register definitions**: `C55_APRF_UIF.h`
- **Display commands**: `ACTBP_display.c`, `ACTBP_display.h`
- **File system commands**: `ACTBP_filesys.c`, `ACTBP_filesys.h`
- **Timeout handling**: `ACTBP_timer.c`, `ACTBP_timer.h`

---

## 📄 License

Copyright © 2011–2012 Texas Instruments Incorporated

Licensed under the BSD 3-Clause License. See source files for full license text.
