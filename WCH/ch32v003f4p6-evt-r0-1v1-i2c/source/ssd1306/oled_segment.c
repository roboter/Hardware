// ===================================================================================
// SSD1306 128x32 Pixels OLED Segment Functions                               * v1.0 *
// ===================================================================================
//
// Collection of the most necessary functions for controlling an SSD1306 128x32 pixels
// I2C OLED as a simulated 8-digit 7-segment display.
//
// References:
// -----------
// - Neven Boyanov:       https://github.com/tinusaur/ssd1306xled
// - Stephen Denne:       https://github.com/datacute/Tiny4kOLED
// - TinyOLEDdemo:        https://github.com/wagiminator/attiny13-tinyoleddemo
// - OLED Font Editor:    http://sourpuss.net/projects/fontedit/
//
// 2022 by Stefan Wagner: https://github.com/wagiminator
#include <string.h> // for memset
#include "oled_segment.h"
#include "led5x7.h"
#include "oled_font.h"
#include "font5x8.h"
unsigned char ssd1306_buffer[512]; // 128x32/8. Every bit is a pixel

// BCD conversion divider array
const uint16_t DIVIDER[] = {1, 10, 100, 1000, 10000};

// OLED initialisation sequence
const uint8_t OLED_INIT_CMD[] = {
  OLED_MULTIPLEX,   0x1F,                         		// set multiplex ratio  
  OLED_CHARGEPUMP,  0x14,                         		// set DC-DC enable  
  OLED_MEMORYMODE,  OLED_EXP_MEM_VERTICAL_ADDR_MODE,	// set memory addressing mode
  OLED_COMPINS,     0x02,                         		// set com pins
  OLED_PAGES, 0x00, 0x03,                         		// set min and max page
  OLED_XFLIP, OLED_YFLIP,                         		// flip screen
  OLED_DISPLAY_ON                                 		// display on
};

// OLED init function
void OLED_init(void) {
  uint8_t i;
  I2C_start(OLED_ADDR);                           // start transmission to OLED
  I2C_write(OLED_CMD_MODE);                       // set command mode
  for(i = 0; i < sizeof(OLED_INIT_CMD); i++)
    I2C_write(OLED_INIT_CMD[i]);                  // send the command bytes
  I2C_stop();                                     // stop transmission
}

// OLED set cursor to digit position
void OLED_setCursor(uint8_t digit) {
  I2C_start(OLED_ADDR);                           // start transmission to OLED
  I2C_write(OLED_CMD_MODE);                       // set command mode
  I2C_write(OLED_COLUMN_LOW | 0);                 // set xpos low nibble (always zero)
  I2C_write(OLED_COLUMN_HIGH | digit);            // set xpos high nibble
  I2C_write(OLED_PAGE | 0);                       // set ypos (always zero)
  I2C_stop();                                     // stop transmission
}

// OLED clear screen
void OLED_clear(void) {
  uint16_t i;
  OLED_setCursor(0);                              // set cursor to first digit
  I2C_start(OLED_ADDR);                           // start transmission to OLED
  I2C_write(OLED_DAT_MODE);                       // set data mode
  for(i=128*4; i; i--) I2C_write(0x00);           // clear screen
  I2C_stop();                                     // stop transmission
}

void OLED_print(char *msg)
{
	uint16_t ptr = 0;                     // character pointer
	
	for (char idx = 0; idx < strlen(msg)-1; idx++) { 
		char c = msg[idx];
		for(uint8_t i=0; i!= 5; i++) 
		{
			ssd1306_buffer[ptr++] = font5x8[c - 0x20][i];
			ptr +=(OLED_HEIGHT - 8) / 8;
		}
		ptr += (OLED_HEIGHT) / 8;
	}
}

// OLED plot a single character
void OLED_printc(uint8_t c) {
	uint16_t ptr = 0;                     // character pointer

  for(uint8_t i=0; i!= 6; i++) 
	{
		ssd1306_buffer[ptr++] = font5x8[c-0x20][i];
		ptr +=(OLED_HEIGHT -8) / 8;
	}
}

// OLED plot a single character
void OLED_plotChar(uint8_t c) {
  uint8_t i;
  uint16_t ptr = (uint16_t)c;                     // character pointer
  if(c == OLED_SPACE) {                           // SPACE?
    for(i=64; i; i--) I2C_write(0x00);            // plot space
    return;                                       // done
  }
  ptr = (ptr << 5) + (ptr << 4) + (ptr << 2);     // -> ptr = c * 13 * 4;
  for(i=52; i; i--) I2C_write(OLED_FONT[ptr++]);  // plot character
  for(i=12; i; i--) I2C_write(0x00);              // plot space between characters
}

// OLED write a single character
void OLED_write(uint8_t c) {
  I2C_start(OLED_ADDR);                           // start transmission to OLED
  I2C_write(OLED_DAT_MODE);                       // set data mode
  OLED_plotChar(c);                               // plot character
  I2C_stop();                                     // stop transmission
}

// update every pixel on the screen
void OLED_update() {
    unsigned short count = 512; // WIDTH * ((HEIGHT + 7) / 8)
    unsigned char * ptr = ssd1306_buffer; // first address of the pixel buffer
		I2C_start(OLED_ADDR);                           // start transmission to OLED
		I2C_write(OLED_DAT_MODE);                       // set data mode
    // send every pixel
    while (count--) {
        I2C_write(*ptr++);
    }
    I2C_stop();
}

// set a pixel value. Call update() to push to the display)
void OLED_drawPixel(unsigned char x, unsigned char y, unsigned char color) {
    if ((x < 0) || (x >= OLED_WIDTH) || (y < 0) || (y >= OLED_HEIGHT)) {
        return;
    }

    if (color == 1) {
        ssd1306_buffer[x + (y / 8)*OLED_WIDTH] |= (1 << (y & 7));
    } else {
        ssd1306_buffer[x + (y / 8)*OLED_WIDTH] &= ~(1 << (y & 7));
    }
}

// zero every pixel value
void OLED_clear_buffer() {
    memset(ssd1306_buffer, 0, 512); // make every bit a 0, memset in string.h
}