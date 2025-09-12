// ===================================================================================
// SSD1306 128x64 Pixels OLED Terminal Functions                              * v1.0 *
// ===================================================================================
//
// Collection of the most necessary functions for controlling an SSD1306 128x64 pixels
// I2C OLED for the display of text in the context of emulating a terminal output.
//
// References:
// -----------
// - Neven Boyanov: https://github.com/tinusaur/ssd1306xled
// - Stephen Denne: https://github.com/datacute/Tiny4kOLED
// - David Johnson-Davies: http://www.technoblogy.com/show?TV4
// - TinyOLEDdemo: https://github.com/wagiminator/attiny13-tinyoleddemo
// - TinyTerminal: https://github.com/wagiminator/ATtiny85-TinyTerminal
// - USB2OLED: https://github.com/wagiminator/CH552-USB-OLED
//
// 2022 by Stefan Wagner: https://github.com/wagiminator

#include "ssd1306.h"
#include "ch32v00x_i2c.h"

// Standard ASCII 5x8 font (adapted from Neven Boyanov and Stephen Denne)
const uint8_t OLED_FONT[] __attribute__((section(".rodata"))) = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00,
  0x14, 0x7F, 0x14, 0x7F, 0x14, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x23, 0x13, 0x08, 0x64, 0x62,
  0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x41, 0x00,
  0x00, 0x41, 0x22, 0x1C, 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, 0x08, 0x08, 0x3E, 0x08, 0x08,
  0x00, 0x00, 0xA0, 0x60, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x60, 0x60, 0x00, 0x00,
  0x20, 0x10, 0x08, 0x04, 0x02, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x42, 0x7F, 0x40, 0x00,
  0x42, 0x61, 0x51, 0x49, 0x46, 0x21, 0x41, 0x45, 0x4B, 0x31, 0x18, 0x14, 0x12, 0x7F, 0x10,
  0x27, 0x45, 0x45, 0x45, 0x39, 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x01, 0x71, 0x09, 0x05, 0x03,
  0x36, 0x49, 0x49, 0x49, 0x36, 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x36, 0x36, 0x00, 0x00,
  0x00, 0x56, 0x36, 0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14,
  0x00, 0x41, 0x22, 0x14, 0x08, 0x02, 0x01, 0x51, 0x09, 0x06, 0x32, 0x49, 0x59, 0x51, 0x3E,
  0x7C, 0x12, 0x11, 0x12, 0x7C, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x3E, 0x41, 0x41, 0x41, 0x22,
  0x7F, 0x41, 0x41, 0x22, 0x1C, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x7F, 0x09, 0x09, 0x09, 0x01,
  0x3E, 0x41, 0x49, 0x49, 0x7A, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x41, 0x7F, 0x41, 0x00,
  0x20, 0x40, 0x41, 0x3F, 0x01, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x7F, 0x40, 0x40, 0x40, 0x40,
  0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x3E, 0x41, 0x41, 0x41, 0x3E,
  0x7F, 0x09, 0x09, 0x09, 0x06, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x7F, 0x09, 0x19, 0x29, 0x46,
  0x46, 0x49, 0x49, 0x49, 0x31, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x3F, 0x40, 0x40, 0x40, 0x3F,
  0x1F, 0x20, 0x40, 0x20, 0x1F, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x63, 0x14, 0x08, 0x14, 0x63,
  0x07, 0x08, 0x70, 0x08, 0x07, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x7F, 0x41, 0x41, 0x00,
  0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x41, 0x41, 0x7F, 0x00, 0x04, 0x02, 0x01, 0x02, 0x04,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x01, 0x02, 0x04, 0x00, 0x20, 0x54, 0x54, 0x54, 0x78,
  0x7F, 0x48, 0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x20, 0x38, 0x44, 0x44, 0x48, 0x7F,
  0x38, 0x54, 0x54, 0x54, 0x18, 0x08, 0x7E, 0x09, 0x01, 0x02, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,
  0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x44, 0x7D, 0x40, 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,
  0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,
  0x7C, 0x08, 0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 0xFC, 0x24, 0x24, 0x24, 0x18,
  0x18, 0x24, 0x24, 0x18, 0xFC, 0x7C, 0x08, 0x04, 0x04, 0x08, 0x48, 0x54, 0x54, 0x54, 0x20,
  0x04, 0x3F, 0x44, 0x40, 0x20, 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x1C, 0x20, 0x40, 0x20, 0x1C,
  0x3C, 0x40, 0x30, 0x40, 0x3C, 0x44, 0x28, 0x10, 0x28, 0x44, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,
  0x44, 0x64, 0x54, 0x4C, 0x44, 0x08, 0x36, 0x41, 0x41, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00,
  0x00, 0x41, 0x41, 0x36, 0x08, 0x08, 0x04, 0x08, 0x10, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE];

// OLED initialisation sequence
const uint8_t OLED_INIT_CMD[] = {
  OLED_MULTIPLEX,   0x3F,                 // set multiplex ratio  
  OLED_CHARGEPUMP,  0x14,                 // set DC-DC enable  
  OLED_MEMORYMODE,  0x02,                 // set page addressing mode
  OLED_COMPINS,     0x12,                 // set com pins
  OLED_XFLIP, OLED_YFLIP,                 // flip screen
  OLED_DISPLAY_ON                         // display on
};

const uint8_t ssd1306_init_sequence [] = {	// Initialization Sequence
	0xAE,			// Set Display ON/OFF - AE=OFF, AF=ON
	0xD5, 0xF0,		// Set display clock divide ratio/oscillator frequency, set divide ratio
	0xA8, 0x3F,		// Set multiplex ratio (1 to 64) ... (height - 1)
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0x40 | 0x00,	// Set start line address, at 0.
	0x8D, 0x14,		// Charge Pump Setting, 14h = Enable Charge Pump
	0x20, 0x00,		// Set Memory Addressing Mode - 00=Horizontal, 01=Vertical, 10=Page, 11=Invalid
	0xA0 | 0x01,	// Set Segment Re-map
	0xC8,			// Set COM Output Scan Direction
	0xDA, 0x12,		// Set COM Pins Hardware Configuration - 128x32:0x02, 128x64:0x12
	0x81, 0x3F,		// Set contrast control register
	0xD9, 0x22,		// Set pre-charge period (0x22 or 0xF1)
	0xDB, 0x20,		// Set Vcomh Deselect Level - 0x00: 0.65 x VCC, 0x20: 0.77 x VCC (RESET), 0x30: 0.83 x VCC
	0xA4,			// Entire Display ON (resume) - output RAM to display
	0xA6,			// Set Normal/Inverse Display mode. A6=Normal; A7=Inverse
	0x2E,			// Deactivate Scroll command
	0xAF,			// Set Display ON/OFF - AE=OFF, AF=ON
	0x22, 0x00, 0x3f,	// Set Page Address (start,end)
	0x21, 0x00,	0x7f,	// Set Column Address (start,end)
};

// OLED global variables
uint8_t line, column, scroll;

// OLED set cursor to line start
void OLED_setline(uint8_t line) {
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_PAGE + line);            // set line
  I2C_write(0x00); I2C_write(0x10);       // set column to "0"
  I2C_stop();                             // stop transmission
}

// OLED clear line
void OLED_clearline(uint8_t line) {
  uint8_t i;
  OLED_setline(line);                     // set cursor to line start
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(i=128; i; i--) I2C_write(0x00);     // clear the line
  I2C_stop();                             // stop transmission
}

// OLED clear screen
void OLED_clear2(void) {
  uint16_t i;
		OLED_setpos(0, 0);
//  OLED_setCursor(0);                              // set cursor to first digit
  I2C_start(OLED_ADDR);                           // start transmission to OLED
  I2C_write(OLED_DAT_MODE);                       // set data mode
  for(i=128*8; i; i--) I2C_write(0xFF);           // clear screen
  I2C_stop();                                     // stop transmission
}

// OLED clear screen
void OLED_clear(void) {
  uint8_t i;
  for(i=0; i<8; i++) OLED_clearline(i);
  line = scroll;
  column = 0;
  OLED_setline((line + scroll) & 0x07);
}

// OLED clear the top line, then scroll the display up by one line
void OLED_scrollDisplay(void) {
  OLED_clearline(scroll);                 // clear line
  scroll = (scroll + 1) & 0x07;           // set next line
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_OFFSET);                 // set display offset:
  I2C_write(scroll << 3);                 // scroll up
  I2C_stop();                             // stop transmission
}

// OLED init function
void OLED_init(void) {
  uint8_t i;
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  for(i = 0; i < sizeof(ssd1306_init_sequence); i++)
    I2C_write(ssd1306_init_sequence[i]);          // send the command bytes
  I2C_stop();                             // stop transmission
  scroll = 0;                             // start with zero scroll
  OLED_clear();                           // clear screen
}

// OLED plot a single character
void OLED_plotChar(char c) {
  uint8_t i;
  uint16_t ptr = c - 32;                  // character pointer
  ptr += ptr << 2;                        // -> ptr = (ch - 32) * 5;
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(i=5 ; i; i--) I2C_write(OLED_FONT[ptr++]);
  I2C_write(0x00);                        // write space between characters
  I2C_stop();                             // stop transmission
}

// OLED write a character or handle control characters
void OLED_write(char c) {
  c = c & 0x7F;                           // ignore top bit
  // normal character
  if(c >= 32) {
    OLED_plotChar(c);
    if(++column > 20) {
      column = 0;
      if(line == 7) OLED_scrollDisplay();
      else line++;
      OLED_setline((line + scroll) & 0x07);
    }
  }
  // new line
  else if(c == '\n') {
    column = 0;
    if(line == 7) OLED_scrollDisplay();
    else line++;
    OLED_setline((line + scroll) & 0x07);
  }
  // carriage return
  else if(c == '\r') {
    column = 0;
    OLED_setline((line + scroll) & 0x07);
  }
}

// OLED print string
void OLED_print(char* str) {
  while(*str) OLED_write(*str++);
}

// OLED print string with newline
void OLED_println(char* str) {
  OLED_print(str);
  OLED_write('\n');
}

// For BCD conversion
const uint32_t DIVIDER[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

// Print decimal value (BCD conversion by substraction method)
void OLED_printD(uint32_t value) {
  uint8_t digits   = 10;                          // print 10 digits
  uint8_t leadflag = 0;                           // flag for leading spaces
  while(digits--) {                               // for all digits
    uint8_t digitval = 0;                         // start with digit value 0
    uint32_t divider = DIVIDER[digits];           // read current divider
    while(value >= divider) {                     // if current divider fits into the value
      leadflag = 1;                               // end of leading spaces
      digitval++;                                 // increase digit value
      value -= divider;                           // decrease value by divider
    }
    if(!digits)  leadflag++;                      // least digit has to be printed
    if(leadflag) OLED_write(digitval + '0');      // print the digit
  }
}

// Convert byte nibble into hex character and print it
void OLED_printN(uint8_t nibble) {
  OLED_write((nibble <= 9) ? ('0' + nibble) : ('A' - 10 + nibble));
}

// Convert byte into hex characters and print it
void OLED_printB(uint8_t value) {
  OLED_printN(value >> 4);
  OLED_printN(value & 0x0f);
}

// Convert word into hex characters and print it
void OLED_printW(uint16_t value) {
  OLED_printB(value >> 8);
  OLED_printB(value);
}

// Convert long into hex characters and print it
void OLED_printL(uint32_t value) {
  OLED_printW(value >> 16);
  OLED_printW(value);
}

// OLED set cursor position
void OLED_setpos(uint8_t x, uint8_t y) {
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_PAGE | y);	              // set page start address
  I2C_write(x & 0x0F);			              // set lower nibble of start column
  I2C_write(OLED_COLUMN_HIGH | (x >> 4)); // set higher nibble of start column
  I2C_stop();                             // stop transmission
}

void ssd1306_start_data(void) {
I2C_start(OLED_ADDR);   
	//I2C_write(OLED_ADDR);	// Slave address, R/W(SA0)=0 - write
	I2C_write(0x40);			// Control byte: D/C=1 - write data
}

// OLED fill screen
void OLED_fill(uint8_t p) {
  OLED_setpos(0, 0);                      // set cursor to display start
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(uint16_t i=128*8; i; i--) I2C_write(p); // send pattern
  I2C_stop();                             // stop transmission
}

void OLED_fill2(uint8_t p) {	
	OLED_setpos(0, 0);
//	I2C_start(OLED_ADDR);  // Initiate transmission of data
//	I2C_write(OLED_DAT_MODE);
	ssd1306_start_data();
	for (uint16_t i = 128 * 8 *32; i > 0; i--) {
		I2C_write(p);
	}
		I2C_stop(); // Finish transmission of data	
}

// OLED draw bitmap
void OLED_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t* bmp) {
	
	int z=0;
  for(uint8_t y = y0; y < y1; y++) {
    OLED_setpos(x0, y);
    I2C_start(OLED_ADDR);
    I2C_write(OLED_DAT_MODE);
    for(uint8_t x = x0; x < x1; x++)
		{
			printf("%d\r\n",bmp[z]);
      I2C_write(bmp[z]);
			z++;
		}
    I2C_stop();
  }
}

/*
 * Draw a bitmap from x0 & y0 with the w & h sizes
 * x0 => X origin coordinate
 * y0 => Y origin coordinate
 * w  => Width in pixels of the bitmap
 * h  => Heiht in pixels of the bitmap
 * bmp  => Bitmap array
 */
void OLED_draw_bmp_by_size(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, const uint8_t* bmp) {
	int z=0;
  for(uint8_t y = y0; y < y0+(h/8); y++) {
    OLED_setpos(x0, y);
    I2C_start(OLED_ADDR);
    I2C_write(OLED_DAT_MODE);
    for(uint8_t x = x0; x < x0+w; x++)
		{
			I2C_write(bmp[z]);
			z++;
		}
    I2C_stop();
  }
}

/*
 * Draw one pixel in the screenbuffer
 * X => X Coordinate
 * Y => Y Coordinate
 * color => Pixel color
 */
void OLED_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }
   
    // Draw in the right color
    if(color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else { 
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}




// Set system clock frequency
#ifndef F_CPU
  #define F_CPU           24000000  // 24Mhz if not otherwise defined
#endif

// I2C event flag definitions
#define I2C_START_GENERATED     0x00010003    // BUSY, MSL, SB
#define I2C_ADDR_TRANSMITTED    0x00820003    // BUSY, MSL, ADDR, TXE
#define I2C_BYTE_TRANSMITTED    0x00840003    // BUSY, MSL, BTF, TXE
#define I2C_checkEvent(n)       (((((uint32_t)I2C1->STAR1<<16) | I2C1->STAR2) & n) == n)



// Start I2C transmission (addr must contain R/W bit)
void I2C_start(uint8_t addr) {
    // Wait until bus ready
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    
    // Generate START condition
    I2C_GenerateSTART(I2C1, ENABLE);
    
    // Wait for START condition generated
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    // Send slave address + R/W bit
    I2C_SendData(I2C1, addr);
    
    // Wait for address transmitted
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

// Send data byte via I2C bus
void I2C_write(uint8_t data) {
    // Wait for data register empty
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    
    // Send data byte
    I2C_SendData(I2C1, data);
}

// Stop I2C transmission
void I2C_stop(void) {
    // Wait for byte transfer finished
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // Generate STOP condition
    I2C_GenerateSTOP(I2C1, ENABLE);
    
    // Wait for STOP condition completed
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

// Test connection to all addresses and display results in a table
void OLED_test_all_addresses(void) {
    uint8_t found_addresses[128] = {0};
    uint8_t found_count = 0;
    
    OLED_clear();
    OLED_println("I2C Address Scan");
    OLED_println("----------------");
    
    // Scan all 128 possible addresses
    for(uint8_t i = 0; i < 128; i++) {
        I2C_GenerateSTART(I2C1, ENABLE);
        uint32_t timeout = 1000;
        
        // Wait for START condition
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
            if(timeout-- == 0) {
                I2C_GenerateSTOP(I2C1, ENABLE);
                break;
            }
        }
        
        if(timeout > 0) { // START was successful
            I2C_Send7bitAddress(I2C1, i, I2C_Direction_Transmitter);
            Delay_Ms(1);
            
            if(!I2C_GetFlagStatus(I2C1, I2C_FLAG_AF)) {
                found_addresses[found_count++] = i;
            } else {
                I2C_ClearFlag(I2C1, I2C_FLAG_AF);
            }
        }
        
        I2C_GenerateSTOP(I2C1, ENABLE);
        timeout = 1000;
        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF)) {
            if(timeout-- == 0) break;
        }
    }
    
    // Display results in a table format
    OLED_clear();
    OLED_println("I2C Devices Found:");
    OLED_println("7-bit  8-bit(W)");
    OLED_println("-----  ---------");
    
    uint8_t line = 3; // Start from line 3
    for(uint8_t i = 0; i < found_count; i++) {
       
        
        OLED_setpos(0, line);
        
        // Display 7-bit address
        OLED_print("0x");
        if(found_addresses[i] < 0x10) OLED_print("0");
        OLED_printB(found_addresses[i]);
        
        // Display 8-bit write address
        OLED_setpos(7 * 6, line);
        OLED_print("0x");
        OLED_printB(found_addresses[i] << 1);
        
        line++;
    }
    
    // Display summary at the bottom
//    OLED_setpos(0, 7);
//    OLED_print("Total: ");
//    OLED_printD(found_count);
//    OLED_print(" devices");
    
//    Delay_Ms(5000); // Display for 5 seconds
//    
//    // Return to top and show detailed info
//    if(found_count > 0) {
//        OLED_clear();
//        OLED_println("Device Details:");
//        OLED_println("---------------");
//        
//        for(uint8_t i = 0; i < found_count ; i++) {
//            OLED_setpos(0, 2 + i);
//            OLED_print("0x");
//            OLED_printB(found_addresses[i] << 1);
//            OLED_print(" (7-bit: 0x");
//            OLED_printB(found_addresses[i]);
//            OLED_print(")");
//        }
//        
//      
//        
//        Delay_Ms(3000);
//    }
}