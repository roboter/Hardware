/**
 ******************************************************************************
 * @file    display.h
 * @brief   Header for ST7789 TFT LCD driver using STM32 SPL
 ******************************************************************************
 */

#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdint.h>

/* Display dimensions */
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320

/* Color definitions (RGB565 format) */
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE 0x001F
#define COLOR_YELLOW 0xFFE0
#define COLOR_CYAN 0x07FF
#define COLOR_MAGENTA 0xF81F

    /* Display orientation */
    typedef enum
    {
        DISPLAY_ORIENTATION_PORTRAIT = 0,
        DISPLAY_ORIENTATION_LANDSCAPE,
        DISPLAY_ORIENTATION_PORTRAIT_INVERTED,
        DISPLAY_ORIENTATION_LANDSCAPE_INVERTED
    } DisplayOrientation;

    /* Function prototypes -------------------------------------------------------*/

    /**
     * @brief  Initializes the display and required peripherals
     * @retval None
     */
    void LCD_Init(void);

    /**
     * @brief  Sets display orientation
     * @param  orientation: Display orientation to set
     * @retval None
     */
    void DISPLAY_SetOrientation(DisplayOrientation orientation);

    /**
     * @brief  Fills entire screen with specified color
     * @param  color: RGB565 color value
     * @retval None
     */
    void LCD_FillScreen(uint16_t color);

    /**
     * @brief  Draws a single pixel at specified coordinates
     * @param  x: X coordinate (0 to DISPLAY_WIDTH-1)
     * @param  y: Y coordinate (0 to DISPLAY_HEIGHT-1)
     * @param  color: RGB565 color value
     * @retval None
     */
    void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

    /**
     * @brief  Draws a filled rectangle
     * @param  x: Top-left X coordinate
     * @param  y: Top-left Y coordinate
     * @param  width: Rectangle width
     * @param  height: Rectangle height
     * @param  color: RGB565 color value
     * @retval None
     */
    void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

    /**
     * @brief  Draws an image to the display
     * @param  x: Top-left X coordinate
     * @param  y: Top-left Y coordinate
     * @param  width: Image width
     * @param  height: Image height
     * @param  image: Pointer to image data (RGB565 format)
     * @retval None
     */
    void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *image);

    /**
     * @brief  Sets display brightness (if supported by hardware)
     * @param  brightness: Brightness level (0-255)
     * @retval None
     */
    void DISPLAY_SetBrightness(uint8_t brightness);

    /**
     * @brief  Turns display on
     * @retval None
     */
    void DISPLAY_On(void);

    /**
     * @brief  Turns display off
     * @retval None
     */
    void DISPLAY_Off(void);

    /**
     * @brief  Reads display ID (for diagnostic purposes)
     * @retval Display ID
     */
    uint16_t DISPLAY_ReadID(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */