/**
 ******************************************************************************
 * @file           : pcd8544_lib.h
 * @brief          : PCD8544 Nokia 5110 LCD display library (based on Adafruit)
 ******************************************************************************
 */

#ifndef __PCD8544_LIB_H
#define __PCD8544_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported defines ---------------------------------------------------------*/
#define PCD8544_WIDTH           84
#define PCD8544_HEIGHT          48
#define PCD8544_BUFFER_SIZE     (PCD8544_WIDTH * PCD8544_HEIGHT / 8)

/* PCD8544 Commands */
#define PCD8544_FUNCTIONSET     0x20
#define PCD8544_DISPLAYCONTROL  0x08
#define PCD8544_SETDISPLAYNORMAL 0x0C
#define PCD8544_SETDISPLAYALLON 0x09
#define PCD8544_SETDISPLAYBLANK 0x08
#define PCD8544_SETDISPLAYINVERSE 0x0D
#define PCD8544_SETBANKS        0x04
#define PCD8544_SETBIAS         0x10
#define PCD8544_SETVOP          0x80
#define PCD8544_SETXADDR        0x80
#define PCD8544_SETYADDR        0x40

/* Color definitions */
#define BLACK                   1
#define WHITE                   0

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint8_t buffer[PCD8544_BUFFER_SIZE];
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t textsize;
    uint8_t textcolor;
    uint8_t wrap;
} PCD8544_HandleTypeDef;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Initialize PCD8544 display
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval HAL status
 */
HAL_StatusTypeDef PCD8544_Init(PCD8544_HandleTypeDef *hlcd);

/**
 * @brief  Clear the display buffer
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval None
 */
void PCD8544_Clear(PCD8544_HandleTypeDef *hlcd);

/**
 * @brief  Update the display with buffer contents
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval None
 */
void PCD8544_Display(PCD8544_HandleTypeDef *hlcd);

/**
 * @brief  Set display contrast
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  contrast: Contrast value (0-127)
 * @retval None
 */
void PCD8544_SetContrast(PCD8544_HandleTypeDef *hlcd, uint8_t contrast);

/**
 * @brief  Set display mode
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  mode: Display mode
 * @retval None
 */
void PCD8544_SetDisplayMode(PCD8544_HandleTypeDef *hlcd, uint8_t mode);

/**
 * @brief  Set cursor position
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @retval None
 */
void PCD8544_SetCursor(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y);

/**
 * @brief  Set text size
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  size: Text size (1-4)
 * @retval None
 */
void PCD8544_SetTextSize(PCD8544_HandleTypeDef *hlcd, uint8_t size);

/**
 * @brief  Set text color
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  color: Text color (BLACK or WHITE)
 * @retval None
 */
void PCD8544_SetTextColor(PCD8544_HandleTypeDef *hlcd, uint8_t color);

/**
 * @brief  Write a character
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  c: Character to write
 * @retval None
 */
void PCD8544_WriteChar(PCD8544_HandleTypeDef *hlcd, char c);

/**
 * @brief  Write a string
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  str: String to write
 * @retval None
 */
void PCD8544_WriteString(PCD8544_HandleTypeDef *hlcd, const char* str);

/**
 * @brief  Draw a pixel
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @param  color: Pixel color
 * @retval None
 */
void PCD8544_DrawPixel(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief  Draw a line
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x0: Start X coordinate
 * @param  y0: Start Y coordinate
 * @param  x1: End X coordinate
 * @param  y1: End Y coordinate
 * @param  color: Line color
 * @retval None
 */
void PCD8544_DrawLine(PCD8544_HandleTypeDef *hlcd, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

/**
 * @brief  Draw a rectangle
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @param  w: Width
 * @param  h: Height
 * @param  color: Rectangle color
 * @retval None
 */
void PCD8544_DrawRect(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * @brief  Fill a rectangle
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @param  w: Width
 * @param  h: Height
 * @param  color: Fill color
 * @retval None
 */
void PCD8544_FillRect(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * @brief  Draw a circle
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x0: Center X coordinate
 * @param  y0: Center Y coordinate
 * @param  r: Radius
 * @param  color: Circle color
 * @retval None
 */
void PCD8544_DrawCircle(PCD8544_HandleTypeDef *hlcd, uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);

#ifdef __cplusplus
}
#endif

#endif /* __PCD8544_LIB_H */ 