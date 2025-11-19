#ifndef __SSD1306_H
#define __SSD1306_H

#include <stdint.h>
#include <stdbool.h>

// SSD1306 I2C Address
#define SSD1306_I2C_ADDR    0x3C

// Screen dimensions
#define SSD1306_WIDTH       128
#define SSD1306_HEIGHT      64
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / 8)

#define CHAR_UP    0
#define CHAR_DOWN  1
#define CHAR_HEART 2
#define CHAR_CURSOR 3
#define CHAR_UP_S 4
#define CHAR_DOWN_S 5

// Colors
typedef enum {
    Black = 0,
    White = 1,
    Inverse = 2
} SSD1306_COLOR;

// Text alignment
typedef enum {
    ALIGN_LEFT = 0,
    ALIGN_CENTER = 1,
    ALIGN_RIGHT = 2
} TEXT_ALIGN;

// Basic functions
void OLED_init(void);
void OLED_clear(void);
void OLED_update(void);
void OLED_display(void);
void OLED_setContrast(uint8_t contrast);
void OLED_invertDisplay(uint8_t invert);
void OLED_dim(uint8_t dim);

// Cursor and text functions
void OLED_setCursor(uint8_t x, uint8_t y);
void OLED_setTextSize(uint8_t size);
void OLED_setTextColor(SSD1306_COLOR color);
void OLED_setTextWrap(uint8_t wrap);

// Print functions
void OLED_print(const char *str);
void OLED_printS(const char *str);
void OLED_println(const char *str);
void OLED_printB(uint8_t value);      // Print byte in hex
void OLED_printD(int32_t value);      // Print decimal
void OLED_printU(uint32_t value);     // Print unsigned
void OLED_printf(const char *fmt, ...); // Printf-style formatting
void OLED_printAlign(const char *str, TEXT_ALIGN align);

// Character drawing
void OLED_drawChar(uint8_t x, uint8_t y, char c, SSD1306_COLOR color, uint8_t size);
void OLED_drawSymbol(uint8_t x, uint8_t y, uint8_t s, SSD1306_COLOR color);
void OLED_write(uint8_t c);

// Position functions
void OLED_setpos(uint8_t x, uint8_t page);
void OLED_getTextBounds(const char *str, uint8_t x, uint8_t y, 
                        uint8_t *x1, uint8_t *y1, uint8_t *w, uint8_t *h);

// Graphics primitives
void OLED_drawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void OLED_drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SSD1306_COLOR color);
void OLED_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SSD1306_COLOR color); // Alias
void OLED_drawFastHLine(uint8_t x, uint8_t y, uint8_t w, SSD1306_COLOR color);
void OLED_drawFastVLine(uint8_t x, uint8_t y, uint8_t h, SSD1306_COLOR color);

// Rectangles
void OLED_drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, SSD1306_COLOR color);
void OLED_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, SSD1306_COLOR color);
void OLED_drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, SSD1306_COLOR color);
void OLED_fillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, SSD1306_COLOR color);

// Circles
void OLED_drawCircle(uint8_t x0, uint8_t y0, uint8_t r, SSD1306_COLOR color);
void OLED_fillCircle(uint8_t x0, uint8_t y0, uint8_t r, SSD1306_COLOR color);

// Triangles
void OLED_drawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, 
                       uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void OLED_fillTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                       uint8_t x2, uint8_t y2, SSD1306_COLOR color);

// Bitmap drawing
void OLED_drawBitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, 
                     uint8_t w, uint8_t h, SSD1306_COLOR color);
void OLED_drawXBitmap(uint8_t x, uint8_t y, const uint8_t *bitmap,
                      uint8_t w, uint8_t h, SSD1306_COLOR color);

// Scrolling
void OLED_startScrollRight(uint8_t start, uint8_t stop);
void OLED_startScrollLeft(uint8_t start, uint8_t stop);
void OLED_startScrollDiagRight(uint8_t start, uint8_t stop);
void OLED_startScrollDiagLeft(uint8_t start, uint8_t stop);
void OLED_stopScroll(void);

// Progress bars and gauges
void OLED_drawProgressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t percent);
void OLED_drawBargraph(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bars, uint8_t filled);

// Buffer access
uint8_t* OLED_getBuffer(void);
void OLED_clearBuffer(void);

// Direct command sending (for advanced users)
void OLED_sendCommand(uint8_t cmd);
void OLED_sendData(uint8_t data);

#endif // __SSD1306_H