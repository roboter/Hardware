#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

// ST7789 commands (add any missing ones)
#define ST7789_NOP 0x00
#define ST7789_SWRESET 0x01
#define ST7789_SLPIN 0x10
#define ST7789_SLPOUT 0x11
#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON 0x29
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C
#define ST7789_MADCTL 0x36
#define ST7789_COLMOD 0x3A

// Screen dimensions
#define LCD_WIDTH 240
#define LCD_HEIGHT 320

// Color modes
#define ST7789_COLOR_MODE_16BIT 0x55
#define ST7789_COLOR_MODE_18BIT 0x66

// MADCTL values
#define MADCTL_MY 0x80
#define MADCTL_MX 0x40
#define MADCTL_MV 0x20
#define MADCTL_ML 0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH 0x04

static void Delay(uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}

// Redefined pin configuration
#define LCD_SPI SPI2
#define LCD_SPI_CLK RCC_APB1Periph_SPI2
#define LCD_GPIO GPIOB
#define LCD_GPIO_CLK RCC_APB2Periph_GPIOB

// New pin assignments
#define LCD_PIN_SCK GPIO_Pin_1  // PB1 as SCK
#define LCD_PIN_MOSI GPIO_Pin_3 // PB3 as SDA (MOSI)
#define LCD_PIN_RES GPIO_Pin_5  // PB5 as RESET
#define LCD_PIN_DC GPIO_Pin_7   // PB7 as DC
#define LCD_PIN_BLK GPIO_Pin_9  // PB9 as Backlight control
// Your pin definitions (corrected for backlight)

#define BLK_GPIO GPIOB

static uint8_t _colstart = 0;
static uint8_t _rowstart = 0;
static uint8_t _rotation = 0;

#define SPI_TIMEOUT 100000 // Adjust based on your clock speed

uint8_t SPI_Write(uint8_t data)
{
    uint32_t timeout = SPI_TIMEOUT;

    // Wait for TX buffer empty
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
        if (timeout-- == 0)
            return 0; // Error
    }

    // Send data
    SPI_I2S_SendData(SPI2, data);

    timeout = SPI_TIMEOUT;
    // Wait for RX buffer not empty
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if (timeout-- == 0)
            return 0; // Error
    }

    // Read data to clear RXNE flag (important!)
    return SPI_I2S_ReceiveData(SPI2);
}

static void LCD_WriteCommand(uint8_t cmd)
{
    GPIO_ResetBits(LCD_GPIO, LCD_PIN_DC); // DC low for command
    SPI_Write(cmd);
}

static void LCD_WriteData(uint8_t data)
{
    GPIO_SetBits(LCD_GPIO, LCD_PIN_DC); // DC high for data
    SPI_Write(data);
}

static void LCD_WriteData16(uint16_t data)
{
    GPIO_SetBits(LCD_GPIO, LCD_PIN_DC);
    SPI_Write(data >> 8);
    SPI_Write(data & 0xFF);
}

static void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    x0 += _colstart;
    x1 += _colstart;
    y0 += _rowstart;
    y1 += _rowstart;

    LCD_WriteCommand(ST7789_CASET);
    LCD_WriteData16(x0);
    LCD_WriteData16(x1);

    LCD_WriteCommand(ST7789_RASET);
    LCD_WriteData16(y0);
    LCD_WriteData16(y1);

    LCD_WriteCommand(ST7789_RAMWR);
}
void LCD_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    // 1. Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // 2. Configure SPI pins
    // SCK (PB1) and MOSI (PB3) as Alternate Function Push-Pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 3. Configure control pins (PB5-RES, PB7-DC, PB9-BLK) as Output
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // Lower speed for control lines
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 4. SPI configuration
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx; // Transmit only
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                         // Clock polarity
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;                       // Clock phase
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                          // Software NSS management
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // Start slower (9MHz @72MHz)
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStruct);

    // 5. Enable SPI
    SPI_Cmd(SPI2, ENABLE);

    // 6. Add small delay after initialization
    Delay(1000);

    // Hardware reset
    GPIO_ResetBits(LCD_GPIO, LCD_PIN_RES);
    Delay(100000);
    GPIO_SetBits(LCD_GPIO, LCD_PIN_RES);
    Delay(100000);

    // Turn on backlight
    GPIO_SetBits(LCD_GPIO, LCD_PIN_BLK);

    // Software reset
    LCD_WriteCommand(ST7789_SWRESET);
    Delay(150000);

    // Sleep out
    LCD_WriteCommand(ST7789_SLPOUT);
    Delay(500000);

    // Color mode - 16bit/pixel
    LCD_WriteCommand(ST7789_COLMOD);
    LCD_WriteData(0x55); // RGB565

    // Memory data access control
    LCD_WriteCommand(ST7789_MADCTL);
    LCD_WriteData(0x00);

    // Display inversion on
    LCD_WriteCommand(ST7789_INVON);
    Delay(10000);

    // Display on
    LCD_WriteCommand(ST7789_DISPON);
    Delay(100000);
}
void LCD_Init_(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    // Enable clocks
    RCC_APB2PeriphClockCmd(LCD_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(LCD_SPI_CLK, ENABLE);

    // Configure SPI pins
    GPIO_InitStruct.GPIO_Pin = LCD_PIN_SCK | LCD_PIN_MOSI;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

    // Configure control pins as output
    GPIO_InitStruct.GPIO_Pin = LCD_PIN_RES | LCD_PIN_DC | LCD_PIN_BLK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

    // SPI configuration
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(LCD_SPI, &SPI_InitStruct);

    SPI_Cmd(LCD_SPI, ENABLE);

    // Hardware reset
    GPIO_ResetBits(LCD_GPIO, LCD_PIN_RES);
    Delay(100000);
    GPIO_SetBits(LCD_GPIO, LCD_PIN_RES);
    Delay(100000);

    // Turn on backlight
    GPIO_SetBits(LCD_GPIO, LCD_PIN_BLK);

    // Software reset
    LCD_WriteCommand(ST7789_SWRESET);
    Delay(150000);

    // Sleep out
    LCD_WriteCommand(ST7789_SLPOUT);
    Delay(500000);

    // Color mode - 16bit/pixel
    LCD_WriteCommand(ST7789_COLMOD);
    LCD_WriteData(0x55); // RGB565

    // Memory data access control
    LCD_WriteCommand(ST7789_MADCTL);
    LCD_WriteData(0x00);

    // Display inversion on
    LCD_WriteCommand(ST7789_INVON);
    Delay(10000);

    // Display on
    LCD_WriteCommand(ST7789_DISPON);
    Delay(100000);
}
void LCD_SetRotation(uint8_t m)
{
    _rotation = m % 4;
    LCD_WriteCommand(ST7789_MADCTL);

    switch (_rotation)
    {
    case 0:
        LCD_WriteData(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
        _colstart = 0;
        _rowstart = 0;
        break;
    case 1:
        LCD_WriteData(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
        _colstart = 0;
        _rowstart = 0;
        break;
    case 2:
        LCD_WriteData(MADCTL_RGB);
        _colstart = 0;
        _rowstart = 80;
        break;
    case 3:
        LCD_WriteData(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
        _colstart = 80;
        _rowstart = 0;
        break;
    }
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT))
        return;

    LCD_SetWindow(x, y, x, y);
    LCD_WriteData16(color);
}

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    // Boundary checks
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT)
        return;
    if ((x + w) > LCD_WIDTH)
        w = LCD_WIDTH - x;
    if ((y + h) > LCD_HEIGHT)
        h = LCD_HEIGHT - y;

    // Set the drawing window
    LCD_SetWindow(x, y, x + w - 1, y + h - 1);

    // Prepare for data writing
    GPIO_SetBits(LCD_GPIO, LCD_PIN_DC); // Data mode

    // Optimized pixel writing
    uint32_t pixelCount = (uint32_t)w * h;
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    while (pixelCount--)
    {
        SPI_Write(hi);
        SPI_Write(lo);
    }
}

void LCD_FillScreen(uint16_t color)
{
    LCD_FillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, color);
}

void LCD_DrawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color)
{
    LCD_FillRect(x, y, w, 1, color);
}

void LCD_DrawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color)
{
    LCD_FillRect(x, y, 1, h, color);
}

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{
    // Boundary checks
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT)
        return;
    if ((x + w) > LCD_WIDTH)
        w = LCD_WIDTH - x;
    if ((y + h) > LCD_HEIGHT)
        h = LCD_HEIGHT - y;

    // Set the drawing window
    LCD_SetWindow(x, y, x + w - 1, y + h - 1);

    // Prepare for data writing
    GPIO_SetBits(LCD_GPIO, LCD_PIN_DC); // Data mode

    // Optimized pixel writing
    uint32_t pixelCount = (uint32_t)w * h;
    const uint16_t *ptr = data;

    while (pixelCount--)
    {
        SPI_Write(*ptr >> 8);
        SPI_Write(*ptr & 0xFF);
        ptr++;
    }
}

void LCD_InvertColors(uint8_t invert)
{
    LCD_WriteCommand(invert ? ST7789_INVON : ST7789_INVOFF);
}