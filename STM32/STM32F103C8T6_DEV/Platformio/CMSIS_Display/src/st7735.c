#include "st7735.h"
#include "font5x7.h"
#include <string.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_spi.h>
#include "delay.h"


// Low-level GPIO control
#define ST7789_Select()   //GPIO_ResetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define ST7789_UnSelect() //GPIO_SetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define ST7789_DC_Set()   GPIO_SetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define ST7789_DC_Clr()   GPIO_ResetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define ST7789_RST_Set()  GPIO_SetBits(ST7789_RST_PORT, ST7789_RST_PIN)
#define ST7789_RST_Clr()  GPIO_ResetBits(ST7789_RST_PORT, ST7789_RST_PIN)

static void ST7735_SPI_Init(void) {
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // Enable clocks for SPI1 and GPIOB (both SPI and control pins)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOB, ENABLE);
    
    // Configure SPI pins on PORTB: SCK (PB3), MOSI (PB5)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // Configure control pins: CS (PB10), DC (PB1), RST (PB0)
    GPIO_InitStruct.GPIO_Pin =   ST7789_DC_PIN | ST7789_RST_PIN | ST7789_BLK_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_PORT, &GPIO_InitStruct);
    
    // SPI configuration for ST7735
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  // Adjust based on your clock speed
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;  // Not used but required
    
    // Initialize and enable SPI1
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
}
static void ST7789_WriteCommand(uint8_t cmd) {
    ST7789_Select();
    ST7789_DC_Clr();
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, cmd);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    
    ST7789_UnSelect();
}

static void ST7789_WriteData(uint8_t *buff, size_t buff_size) {
    ST7789_Select();
    ST7789_DC_Set();

    // Send all data in one go (no chunking)
    for (size_t i = 0; i < buff_size; i++) {
        // Wait until TX buffer is empty
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        // Send next byte
        SPI_I2S_SendData(SPI1, buff[i]);
    }

    ST7789_UnSelect();
}

static void ST7789_WriteSmallData(uint8_t data) {
    ST7789_Select();
    ST7789_DC_Set();
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    
    ST7789_UnSelect();
}

void ST7789_SetRotation(uint8_t m) {
    ST7789_WriteCommand(ST7789_MADCTL);
    switch (m) {
        case 0:
            ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
            break;
        case 1:
            ST7789_WriteSmallData(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
            break;
        case 2:
            ST7789_WriteSmallData(ST7789_MADCTL_RGB);
            break;
        case 3:
            ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
            break;
        default:
            break;
    }
}

static void ST7789_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    ST7789_Select();
    uint16_t x_start = x0 + X_SHIFT, x_end = x1 + X_SHIFT;
    uint16_t y_start = y0 + Y_SHIFT, y_end = y1 + Y_SHIFT;

    /* Column Address set */
    ST7789_WriteCommand(ST7789_CASET);
    {
        uint8_t data[] = {x_start >> 8, x_start & 0xFF, x_end >> 8, x_end & 0xFF};
        ST7789_WriteData(data, sizeof(data));
    }

    /* Row Address set */
    ST7789_WriteCommand(ST7789_RASET);
    {
        uint8_t data[] = {y_start >> 8, y_start & 0xFF, y_end >> 8, y_end & 0xFF};
        ST7789_WriteData(data, sizeof(data));
    }
    /* Write to RAM */
    ST7789_WriteCommand(ST7789_RAMWR);
    ST7789_UnSelect();
}

void ST7789_Init(void) {
    ST7735_SPI_Init();

    DelayMs(10);
    ST7789_RST_Clr();
    DelayMs(10);
    ST7789_RST_Set();
    DelayMs(20);

    ST7789_WriteCommand(ST7789_COLMOD);
    ST7789_WriteSmallData(ST7789_COLOR_MODE_16bit);
    ST7789_WriteCommand(0xB2);
    {
        uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
        ST7789_WriteData(data, sizeof(data));
    }
    ST7789_SetRotation(ST7789_ROTATION);

    /* Internal LCD Voltage generator settings */
    ST7789_WriteCommand(0XB7);
    ST7789_WriteSmallData(0x35);
    ST7789_WriteCommand(0xBB);
    ST7789_WriteSmallData(0x19);
    ST7789_WriteCommand(0xC0);
    ST7789_WriteSmallData(0x2C);
    ST7789_WriteCommand(0xC2);
    ST7789_WriteSmallData(0x01);
    ST7789_WriteCommand(0xC3);
    ST7789_WriteSmallData(0x12);
    ST7789_WriteCommand(0xC4);
    ST7789_WriteSmallData(0x20);
    ST7789_WriteCommand(0xC6);
    ST7789_WriteSmallData(0x0F);
    ST7789_WriteCommand(0xD0);
    ST7789_WriteSmallData(0xA4);
    ST7789_WriteSmallData(0xA1);

    ST7789_WriteCommand(0xE0);
    {
        uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
        ST7789_WriteData(data, sizeof(data));
    }

    ST7789_WriteCommand(0xE1);
    {
        uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
        ST7789_WriteData(data, sizeof(data));
    }
    
    ST7789_WriteCommand(ST7789_INVON);
    ST7789_WriteCommand(ST7789_SLPOUT);
    ST7789_WriteCommand(ST7789_NORON);
    ST7789_WriteCommand(ST7789_DISPON);

    DelayMs(50);
    ST7789_Fill_Color(RED);
}


/**
 * @brief Fill the entire screen with a single color
 * @param color 16-bit color value in RGB565 format
 */
 void ST7789_Fill_Color(uint16_t color) {
    // Set address window to full screen
    ST7789_SetAddressWindow(0, 0, ST7789_WIDTH - 1, ST7789_HEIGHT - 1);
    
    // Prepare color data (2 bytes per pixel)
    uint8_t color_data[] = {color >> 8, color & 0xFF};
    
    ST7789_Select();
    

    
    ST7789_UnSelect();
}

/**
 * @brief Draw a filled rectangle with single color
 * @param x Start x coordinate (top-left corner)
 * @param y Start y coordinate (top-left corner)
 * @param w Width of rectangle
 * @param h Height of rectangle
 * @param color 16-bit RGB565 color
 */
 void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // Check boundaries
    if (x >= ST7789_WIDTH || y >= ST7789_HEIGHT) return;
    
    // Adjust width/height if they exceed display bounds
    if ((x + w) > ST7789_WIDTH) w = ST7789_WIDTH - x;
    if ((y + h) > ST7789_HEIGHT) h = ST7789_HEIGHT - y;
    
    // Set address window to the rectangle area
    ST7789_SetAddressWindow(x, y, x + w - 1, y + h - 1);
    
    // Prepare color data (2 bytes per pixel)
    uint8_t color_data[] = {color >> 8, color & 0xFF};
    uint32_t pixel_count = w * h;
    
    ST7789_Select();
    ST7789_DC_Set();
    
    // Send all pixels
    while (pixel_count--) {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, color_data[0]);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, color_data[1]);
    }
    
    ST7789_UnSelect();
}

/**
 * @brief Convert 8-bit RGB values to 16-bit RGB565 format
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 * @return 16-bit RGB565 color value
 */
 uint16_t RGB565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}