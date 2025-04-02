#ifndef __ST7789_H
#define __ST7789_H

#include "font5x7.h"
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_rcc.h>


// Font definition structure
typedef struct {
    const uint8_t width;    // Character width in pixels
    const uint8_t height;   // Character height in pixels
    const uint16_t *data;   // Pointer to font data array
} FontDef;

// Example font declarations (should be defined in fonts.c)
extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

/* choose whether use DMA or not */
//#define USE_DMA

/* If u need CS control, comment below*/
#define CFG_NO_CS

#define LCD_PORT GPIOB

// Control pins configuration
#define ST7789_DC_PIN          GPIO_Pin_9
#define ST7789_RST_PIN         GPIO_Pin_7


#define ST7789_RST_PORT LCD_PORT
#define ST7789_DC_PORT  LCD_PORT

#ifndef CFG_NO_CS
// #define ST7789_CS_PORT  GPIOB
// #define ST7789_CS_PIN   GPIO_Pin_10
#endif

/* Backlight control */
#define ST7789_BLK_PORT LCD_PORT
#define ST7789_BLK_PIN GPIO_Pin_11

#define ST7789_BLK_On()        GPIO_SetBits(ST7789_BLK_PORT, ST7789_BLK_PIN)
#define ST7789_BLK_Off()       GPIO_ResetBits(ST7789_BLK_PORT, ST7789_BLK_PIN)

/*
 * Display types and rotations
 */
//#define USING_135X240
#define USING_240X240
//#define USING_170X320

/* Choose a display rotation you want to use: (0-3) */
//#define ST7789_ROTATION 0
//#define ST7789_ROTATION 1
#define ST7789_ROTATION 2                // use Normally on 240x240
//#define ST7789_ROTATION 3

#ifdef USING_135X240
    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 53
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 52
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 52
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 53
    #endif
#endif

#ifdef USING_240X240
    #define ST7789_WIDTH 240
    #define ST7789_HEIGHT 240

    #if ST7789_ROTATION == 0
        #define X_SHIFT 0
        #define Y_SHIFT 80
    #elif ST7789_ROTATION == 1
        #define X_SHIFT 80
        #define Y_SHIFT 0
    #elif ST7789_ROTATION == 2
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #elif ST7789_ROTATION == 3
        #define X_SHIFT 0
        #define Y_SHIFT 0
    #endif
#endif

#ifdef USING_170X320
    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
    #endif
#endif

/* Color definitions in RGB565 format */
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define GRAY        0X8430
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define BROWN       0XBC40
#define BRRED       0XFC07
#define DARKBLUE    0X01CF
#define LIGHTBLUE   0X7D7C
#define GRAYBLUE    0X5458

#define LIGHTGREEN  0X841F
#define LGRAY       0XC618
#define LGRAYBLUE   0XA651
#define LBBLUE      0X2B12

/* ST7789 Command definitions */
#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

/* Memory Data Access Control Register (0x36H) */
#define ST7789_MADCTL_MY  0x80
#define ST7789_MADCTL_MX  0x40
#define ST7789_MADCTL_MV  0x20
#define ST7789_MADCTL_ML  0x10
#define ST7789_MADCTL_RGB 0x00

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Color modes */
#define ST7789_COLOR_MODE_16bit 0x55    // RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    // RGB666 (18bit)

/* GPIO control macros */
#define ST7789_RST_Clr() GPIO_ResetBits(ST7789_RST_PORT, ST7789_RST_PIN)
#define ST7789_RST_Set() GPIO_SetBits(ST7789_RST_PORT, ST7789_RST_PIN)

#define ST7789_DC_Clr()  GPIO_ResetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define ST7789_DC_Set()  GPIO_SetBits(ST7789_DC_PORT, ST7789_DC_PIN)

#ifndef CFG_NO_CS
#define ST7789_Select()   GPIO_ResetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define ST7789_UnSelect() GPIO_SetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#else
#define ST7789_Select()   do{}while(0)
#define ST7789_UnSelect() do{}while(0)
#endif

#define ABS(x) ((x) > 0 ? (x) : -(x))

/* Function prototypes */
void ST7789_Init(void);
void ST7789_SetRotation(uint8_t m);
void ST7789_Fill_Color(uint16_t color);
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);

void ST7789_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7789_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
void ST7789_InvertColors(uint8_t invert);

void ST7789_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7789_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);

void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void ST7789_TearEffect(uint8_t tear);
void ST7789_Test(void);

// Add this with the other function prototypes
uint16_t RGB565(uint8_t r, uint8_t g, uint8_t b);

#ifndef ST7789_ROTATION
    #error You should at least choose a display rotation!
#endif

#endif