#include "ssd1306.h"
#include "ssd1306_font.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ch32v00x_i2c.h>

// SSD1306 Commands
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COLUMNADDR          0x21
#define SSD1306_PAGEADDR            0x22
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_CHARGEPUMP          0x8D
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON        0xA5
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_DEACTIVATE_SCROLL   0x2E
#define SSD1306_ACTIVATE_SCROLL     0x2F
#define SSD1306_RIGHT_HORIZ_SCROLL  0x26
#define SSD1306_LEFT_HORIZ_SCROLL   0x27
#define SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL 0x29
#define SSD1306_VERT_AND_LEFT_HORIZ_SCROLL  0x2A
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3

#define MY_STRLEN(s) ({           \
    const char *p = (s);          \
    size_t n = 0;                 \
    while (*p++) n++;             \
    n; })


// Display buffer
static uint8_t ssd1306_buffer[SSD1306_BUFFER_SIZE];

// Text cursor
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t text_size = 1;
static SSD1306_COLOR text_color = White;
static uint8_t text_wrap = 1;

// I2C communication helpers
static void i2c_write_byte(uint8_t data) {
    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

static void i2c_start_transmission(uint8_t addr) {
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, addr << 1, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

static void i2c_stop_transmission(void) {
    I2C_GenerateSTOP(I2C1, ENABLE);
}

// Send command to SSD1306
void OLED_sendCommand(uint8_t cmd) {
    i2c_start_transmission(SSD1306_I2C_ADDR);
    i2c_write_byte(0x00); // Command mode
    i2c_write_byte(cmd);
    i2c_stop_transmission();
}

// Send data to SSD1306
void OLED_sendData(uint8_t data) {
    i2c_start_transmission(SSD1306_I2C_ADDR);
    i2c_write_byte(0x40); // Data mode
    i2c_write_byte(data);
    i2c_stop_transmission();
}

// Initialize display
void OLED_init(void) {
    // Initialization sequence
    OLED_sendCommand(SSD1306_DISPLAYOFF);
    OLED_sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
    OLED_sendCommand(0x80);
    OLED_sendCommand(SSD1306_SETMULTIPLEX);
    OLED_sendCommand(SSD1306_HEIGHT - 1);
    OLED_sendCommand(SSD1306_SETDISPLAYOFFSET);
    OLED_sendCommand(0x00);
    OLED_sendCommand(SSD1306_SETSTARTLINE | 0x00);
    OLED_sendCommand(SSD1306_CHARGEPUMP);
    OLED_sendCommand(0x14);
    OLED_sendCommand(SSD1306_MEMORYMODE);
    OLED_sendCommand(0x00);
    OLED_sendCommand(SSD1306_SEGREMAP | 0x01);
    OLED_sendCommand(SSD1306_COMSCANDEC);
    OLED_sendCommand(SSD1306_SETCOMPINS);
    OLED_sendCommand(0x12);
    OLED_sendCommand(SSD1306_SETCONTRAST);
    OLED_sendCommand(0xCF);
    OLED_sendCommand(SSD1306_SETPRECHARGE);
    OLED_sendCommand(0xF1);
    OLED_sendCommand(SSD1306_SETVCOMDETECT);
    OLED_sendCommand(0x40);
    OLED_sendCommand(SSD1306_DISPLAYALLON_RESUME);
    OLED_sendCommand(SSD1306_NORMALDISPLAY);
    OLED_sendCommand(SSD1306_DEACTIVATE_SCROLL);
    OLED_sendCommand(SSD1306_DISPLAYON);
    
    OLED_clear();
    OLED_update();
}

// Clear buffer
void OLED_clear(void) {
    memset(ssd1306_buffer, 0, SSD1306_BUFFER_SIZE);
    cursor_x = 0;
    cursor_y = 0;
}

void OLED_clearBuffer(void) {
    memset(ssd1306_buffer, 0, SSD1306_BUFFER_SIZE);
}

// Update display from buffer
void OLED_update(void) {
    OLED_sendCommand(SSD1306_COLUMNADDR);
    OLED_sendCommand(0);
    OLED_sendCommand(SSD1306_WIDTH - 1);
    OLED_sendCommand(SSD1306_PAGEADDR);
    OLED_sendCommand(0);
    OLED_sendCommand(7);
    
    i2c_start_transmission(SSD1306_I2C_ADDR);
    i2c_write_byte(0x40); // Data mode
    
    for(uint16_t i = 0; i < SSD1306_BUFFER_SIZE; i++) {
        i2c_write_byte(ssd1306_buffer[i]);
    }
    
    i2c_stop_transmission();
}

void OLED_display(void) {
    OLED_update();
}

// Set contrast
void OLED_setContrast(uint8_t contrast) {
    OLED_sendCommand(SSD1306_SETCONTRAST);
    OLED_sendCommand(contrast);
}

// Invert display
void OLED_invertDisplay(uint8_t invert) {
    OLED_sendCommand(invert ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY);
}

// Dim display
void OLED_dim(uint8_t dim) {
    OLED_setContrast(dim ? 0x00 : 0xCF);
}

// Draw pixel
void OLED_drawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    
    switch(color) {
        case White:
            ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y & 7));
            break;
        case Black:
            ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y & 7));
            break;
        case Inverse:
            ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] ^= (1 << (y & 7));
            break;
    }
}

// Helper for abs
static inline int16_t abs16(int16_t x) {
    return x < 0 ? -x : x;
}

// Swap two values
static inline void swap(uint8_t *a, uint8_t *b) {
    uint8_t t = *a;
    *a = *b;
    *b = t;
}

// Draw line (Bresenham's algorithm)
void OLED_drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SSD1306_COLOR color) {
    int16_t steep = abs16(y1 - y0) > abs16(x1 - x0);
    
    if(steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    
    if(x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int16_t dx = x1 - x0;
    int16_t dy = abs16(y1 - y0);
    int16_t err = dx / 2;
    int16_t ystep = (y0 < y1) ? 1 : -1;
    
    for(; x0 <= x1; x0++) {
        if(steep) {
            OLED_drawPixel(y0, x0, color);
        } else {
            OLED_drawPixel(x0, y0, color);
        }
        err -= dy;
        if(err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void OLED_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SSD1306_COLOR color) {
    OLED_drawLine(x0, y0, x1, y1, color);
}

// Fast horizontal line
void OLED_drawFastHLine(uint8_t x, uint8_t y, uint8_t w, SSD1306_COLOR color) {
    for(uint8_t i = x; i < x + w && i < SSD1306_WIDTH; i++) {
        OLED_drawPixel(i, y, color);
    }
}

// Fast vertical line
void OLED_drawFastVLine(uint8_t x, uint8_t y, uint8_t h, SSD1306_COLOR color) {
    for(uint8_t i = y; i < y + h && i < SSD1306_HEIGHT; i++) {
        OLED_drawPixel(x, i, color);
    }
}

// Draw rectangle
void OLED_drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, SSD1306_COLOR color) {
    OLED_drawFastHLine(x, y, w, color);
    OLED_drawFastHLine(x, y + h - 1, w, color);
    OLED_drawFastVLine(x, y, h, color);
    OLED_drawFastVLine(x + w - 1, y, h, color);
}

// Fill rectangle
void OLED_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, SSD1306_COLOR color) {
    for(uint8_t i = x; i < x + w && i < SSD1306_WIDTH; i++) {
        OLED_drawFastVLine(i, y, h, color);
    }
}

// Draw rounded rectangle
void OLED_drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, SSD1306_COLOR color) {
    // Draw main rectangle
    OLED_drawFastHLine(x + r, y, w - 2 * r, color);
    OLED_drawFastHLine(x + r, y + h - 1, w - 2 * r, color);
    OLED_drawFastVLine(x, y + r, h - 2 * r, color);
    OLED_drawFastVLine(x + w - 1, y + r, h - 2 * r, color);
    
    // Draw corners
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t px = 0;
    int16_t py = r;
    
    while(px < py) {
        if(f >= 0) {
            py--;
            ddF_y += 2;
            f += ddF_y;
        }
        px++;
        ddF_x += 2;
        f += ddF_x;
        
        // Draw corner pixels
        OLED_drawPixel(x + r + px, y + r - py, color);
        OLED_drawPixel(x + r + py, y + r - px, color);
        OLED_drawPixel(x + w - r - px - 1, y + r - py, color);
        OLED_drawPixel(x + w - r - py - 1, y + r - px, color);
        OLED_drawPixel(x + r + px, y + h - r + py - 1, color);
        OLED_drawPixel(x + r + py, y + h - r + px - 1, color);
        OLED_drawPixel(x + w - r - px - 1, y + h - r + py - 1, color);
        OLED_drawPixel(x + w - r - py - 1, y + h - r + px - 1, color);
    }
}

// Fill rounded rectangle
void OLED_fillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, SSD1306_COLOR color) {
    // Fill center rectangle
    OLED_fillRect(x + r, y, w - 2 * r, h, color);
    
    // Fill side rectangles
    OLED_fillRect(x, y + r, r, h - 2 * r, color);
    OLED_fillRect(x + w - r, y + r, r, h - 2 * r, color);
    
    // Fill corners
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t px = 0;
    int16_t py = r;
    
    while(px < py) {
        if(f >= 0) {
            py--;
            ddF_y += 2;
            f += ddF_y;
        }
        px++;
        ddF_x += 2;
        f += ddF_x;
        
        OLED_drawFastVLine(x + r + px, y + r - py, 2 * py + 1 + h - 2 * r - 1, color);
        OLED_drawFastVLine(x + w - r - px - 1, y + r - py, 2 * py + 1 + h - 2 * r - 1, color);
        OLED_drawFastVLine(x + r + py, y + r - px, 2 * px + 1 + h - 2 * r - 1, color);
        OLED_drawFastVLine(x + w - r - py - 1, y + r - px, 2 * px + 1 + h - 2 * r - 1, color);
    }
}

// Draw circle (Midpoint algorithm)
void OLED_drawCircle(uint8_t x0, uint8_t y0, uint8_t r, SSD1306_COLOR color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    
    OLED_drawPixel(x0, y0 + r, color);
    OLED_drawPixel(x0, y0 - r, color);
    OLED_drawPixel(x0 + r, y0, color);
    OLED_drawPixel(x0 - r, y0, color);
    
    while(x < y) {
        if(f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        OLED_drawPixel(x0 + x, y0 + y, color);
        OLED_drawPixel(x0 - x, y0 + y, color);
        OLED_drawPixel(x0 + x, y0 - y, color);
        OLED_drawPixel(x0 - x, y0 - y, color);
        OLED_drawPixel(x0 + y, y0 + x, color);
        OLED_drawPixel(x0 - y, y0 + x, color);
        OLED_drawPixel(x0 + y, y0 - x, color);
        OLED_drawPixel(x0 - y, y0 - x, color);
    }
}

// Fill circle
void OLED_fillCircle(uint8_t x0, uint8_t y0, uint8_t r, SSD1306_COLOR color) {
    OLED_drawFastVLine(x0, y0 - r, 2 * r + 1, color);
    
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    
    while(x < y) {
        if(f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        OLED_drawFastVLine(x0 + x, y0 - y, 2 * y + 1, color);
        OLED_drawFastVLine(x0 + y, y0 - x, 2 * x + 1, color);
        OLED_drawFastVLine(x0 - x, y0 - y, 2 * y + 1, color);
        OLED_drawFastVLine(x0 - y, y0 - x, 2 * x + 1, color);
    }
}

// Draw triangle
void OLED_drawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, 
                       uint8_t x2, uint8_t y2, SSD1306_COLOR color) {
    OLED_drawLine(x0, y0, x1, y1, color);
    OLED_drawLine(x1, y1, x2, y2, color);
    OLED_drawLine(x2, y2, x0, y0, color);
}

// Fill triangle
void OLED_fillTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                       uint8_t x2, uint8_t y2, SSD1306_COLOR color) {
    int16_t a, b, y, last;
    
    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if(y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    if(y1 > y2) {
        swap(&y2, &y1);
        swap(&x2, &x1);
    }
    if(y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    
    if(y0 == y2) { // All on same line
        a = b = x0;
        if(x1 < a) a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a) a = x2;
        else if(x2 > b) b = x2;
        OLED_drawFastHLine(a, y0, b - a + 1, color);
        return;
    }
    
    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;
    int32_t sa = 0;
    int32_t sb = 0;
    
    if(y1 == y2) last = y1;
    else last = y1 - 1;
    
    for(y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        
        if(a > b) swap((uint8_t*)&a, (uint8_t*)&b);
        OLED_drawFastHLine(a, y, b - a + 1, color);
    }
    
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        
        if(a > b) swap((uint8_t*)&a, (uint8_t*)&b);
        OLED_drawFastHLine(a, y, b - a + 1, color);
    }
}

// Text functions
void OLED_setCursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
}

void OLED_setTextSize(uint8_t size) {
    text_size = (size > 0) ? size : 1;
}

void OLED_setTextColor(SSD1306_COLOR color) {
    text_color = color;
}

void OLED_setTextWrap(uint8_t wrap) {
    text_wrap = wrap;
}

void OLED_setpos(uint8_t x, uint8_t page) {
    cursor_x = x;
    cursor_y = page * 8;
}

void OLED_drawSymbol(uint8_t x, uint8_t y, uint8_t s, SSD1306_COLOR color) {
    for(uint8_t i=0;i<5;i++) {
        uint8_t line = font_symbols[s][i];
        for(uint8_t j=0;j<8;j++,line>>=1){
            if(line & 1) {
                if(text_size==1) OLED_drawPixel(x+i, y+j, color);
                else OLED_fillRect(x+i*text_size, y+j*text_size, text_size, text_size, color);
            }
        }
    }
}

// Draw character
void OLED_drawChar(uint8_t x, uint8_t y, char c, SSD1306_COLOR color, uint8_t size) {
    if((x >= SSD1306_WIDTH) || (y >= SSD1306_HEIGHT)) return;
   // if(c < ' ' || c > '~') c = ' ';
    
    for(uint8_t i = 0; i < 5; i++) {
        uint8_t line = font[c - ' '][i];
        for(uint8_t j = 0; j < 8; j++, line >>= 1) {
            if(line & 1) {
                if(size == 1) {
                    OLED_drawPixel(x + i, y + j, color);
                } else {
                    OLED_fillRect(x + i * size, y + j * size, size, size, color);
                }
            } else if(color == Black) {
                if(size == 1) {
                    OLED_drawPixel(x + i, y + j, Black);
                } else {
                    OLED_fillRect(x + i * size, y + j * size, size, size, Black);
                }
            }
        }
    }
}

void OLED_write(uint8_t c) {
    if(c == '\n') {
        cursor_y += text_size * 8;
        cursor_x = 0;
    } else if(c == '\r') {
        // Skip
    } else {
        OLED_drawChar(cursor_x, cursor_y, c, text_color, text_size);
        cursor_x += text_size * 6;
        if(text_wrap && (cursor_x > (SSD1306_WIDTH - text_size * 6))) {
            cursor_y += text_size * 8;
            cursor_x = 0;
        }
    }
}

void OLED_print(const char *str) {
    while(*str) {
        OLED_write(*str++);
    }
}

void OLED_printS(const char *str) {
    OLED_print(str);
}

void OLED_println(const char *str) {
    OLED_print(str);
    OLED_write('\n');
}

void OLED_printB(uint8_t value) {
    char buf[3];
    sprintf(buf, "%02X", value);
    OLED_print(buf);
}

void OLED_printD(int32_t value) {
    char buf[12];
    sprintf(buf, "%ld", value);
    OLED_print(buf);
}

void OLED_printU(uint32_t value) {
    char buf[12];
    sprintf(buf, "%lu", value);
    OLED_print(buf);
}

void OLED_printf(const char *fmt, ...) {
    char buf[64];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OLED_print(buf);
}

// Get text bounds
void OLED_getTextBounds(const char *str, uint8_t x, uint8_t y, 
                        uint8_t *x1, uint8_t *y1, uint8_t *w, uint8_t *h) {
    uint8_t len = MY_STRLEN(str);
    *x1 = x;
    *y1 = y;
    *w = len * 6 * text_size;
    *h = 8 * text_size;
}

// Print with alignment
void OLED_printAlign(const char *str, TEXT_ALIGN align) {
    uint8_t len = MY_STRLEN(str);
    uint8_t width = len * 6 * text_size;
    
    switch(align) {
        case ALIGN_LEFT:
            cursor_x = 0;
            break;
        case ALIGN_CENTER:
            cursor_x = (SSD1306_WIDTH - width) / 2;
            break;
        case ALIGN_RIGHT:
            cursor_x = SSD1306_WIDTH - width;
            break;
    }
    
    OLED_print(str);
}

// Progress bar
void OLED_drawProgressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t percent) {
    if(percent > 100) percent = 100;
    OLED_drawRect(x, y, w, h, White);
    uint8_t fill_width = (w - 2) * percent / 100;
    if(fill_width > 0) {
        OLED_fillRect(x + 1, y + 1, fill_width, h - 2, White);
    }
}

// Bar graph
void OLED_drawBargraph(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bars, uint8_t filled) {
    if(filled > bars) filled = bars;
    if(bars == 0) return;
    
    uint8_t bar_width = w / bars;
    if(bar_width < 3) bar_width = 3;
    
    for(uint8_t i = 0; i < bars; i++) {
        uint8_t bx = x + i * bar_width;
        if(bx + bar_width > x + w) break;
        
        if(i < filled) {
            OLED_fillRect(bx, y, bar_width - 2, h, White);
        } else {
            OLED_drawRect(bx, y, bar_width - 2, h, White);
        }
    }
}

// Get buffer pointer
uint8_t* OLED_getBuffer(void) {
    return ssd1306_buffer;
}

// Scrolling functions
void OLED_startScrollRight(uint8_t start, uint8_t stop) {
    OLED_sendCommand(SSD1306_RIGHT_HORIZ_SCROLL);
    OLED_sendCommand(0x00);
    OLED_sendCommand(start);
    OLED_sendCommand(0x00);
    OLED_sendCommand(stop);
    OLED_sendCommand(0x00);
    OLED_sendCommand(0xFF);
    OLED_sendCommand(SSD1306_ACTIVATE_SCROLL);
}

void OLED_startScrollLeft(uint8_t start, uint8_t stop) {
    OLED_sendCommand(SSD1306_LEFT_HORIZ_SCROLL);
    OLED_sendCommand(0x00);
    OLED_sendCommand(start);
    OLED_sendCommand(0x00);
    OLED_sendCommand(stop);
    OLED_sendCommand(0x00);
    OLED_sendCommand(0xFF);
    OLED_sendCommand(SSD1306_ACTIVATE_SCROLL);
}

void OLED_startScrollDiagRight(uint8_t start, uint8_t stop) {
    OLED_sendCommand(SSD1306_SET_VERTICAL_SCROLL_AREA);
    OLED_sendCommand(0x00);
    OLED_sendCommand(SSD1306_HEIGHT);
    OLED_sendCommand(SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL);
    OLED_sendCommand(0x00);
    OLED_sendCommand(start);
    OLED_sendCommand(0x00);
    OLED_sendCommand(stop);
    OLED_sendCommand(0x01);
    OLED_sendCommand(SSD1306_ACTIVATE_SCROLL);
}

void OLED_startScrollDiagLeft(uint8_t start, uint8_t stop) {
    OLED_sendCommand(SSD1306_SET_VERTICAL_SCROLL_AREA);
    OLED_sendCommand(0x00);
    OLED_sendCommand(SSD1306_HEIGHT);
    OLED_sendCommand(SSD1306_VERT_AND_LEFT_HORIZ_SCROLL);
    OLED_sendCommand(0x00);
    OLED_sendCommand(start);
    OLED_sendCommand(0x00);
    OLED_sendCommand(stop);
    OLED_sendCommand(0x01);
    OLED_sendCommand(SSD1306_ACTIVATE_SCROLL);
}

void OLED_stopScroll(void) {
    OLED_sendCommand(SSD1306_DEACTIVATE_SCROLL);
}

// Draw bitmap (vertical byte orientation)
void OLED_drawBitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, 
                     uint8_t w, uint8_t h, SSD1306_COLOR color) {
    uint16_t byte_width = (w + 7) / 8;
    uint8_t byte = 0;
    
    for(uint8_t j = 0; j < h; j++) {
        for(uint8_t i = 0; i < w; i++) {
            if(i & 7) {
                byte <<= 1;
            } else {
                byte = bitmap[j * byte_width + i / 8];
            }
            
            if(byte & 0x80) {
                OLED_drawPixel(x + i, y + j, color);
            }
        }
    }
}

// Draw XBitmap (LSB first format)
void OLED_drawXBitmap(uint8_t x, uint8_t y, const uint8_t *bitmap,
                      uint8_t w, uint8_t h, SSD1306_COLOR color) {
    uint16_t byte_width = (w + 7) / 8;
    uint8_t byte = 0;
    
    for(uint8_t j = 0; j < h; j++) {
        for(uint8_t i = 0; i < w; i++) {
            if(i & 7) {
                byte >>= 1;
            } else {
                byte = bitmap[j * byte_width + i / 8];
            }
            
            if(byte & 0x01) {
                OLED_drawPixel(x + i, y + j, color);
            }
        }
    }
}