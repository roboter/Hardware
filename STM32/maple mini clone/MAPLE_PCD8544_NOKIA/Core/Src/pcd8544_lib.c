/**
 ******************************************************************************
 * @file           : pcd8544_lib.c
 * @brief          : PCD8544 Nokia 5110 LCD display library implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "pcd8544_lib.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
// 5x7 font data (based on Adafruit GFX library)
static const uint8_t font5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x32, 0x49, 0x79, 0x41, 0x3E}, // @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // backslash
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // _
    {0x00, 0x01, 0x02, 0x04, 0x00}, // `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x18, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // p
    {0x08, 0x14, 0x14, 0x18, 0x7C}, // q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x00, 0x41, 0x36, 0x08, 0x00}, // }
    {0x10, 0x08, 0x08, 0x10, 0x08}, // ~
    {0x78, 0x46, 0x41, 0x46, 0x78}  // DEL
};

/* Private function prototypes -----------------------------------------------*/
static void PCD8544_WriteCommand(uint8_t cmd);
static void PCD8544_WriteData(uint8_t data);
static void PCD8544_ShiftOut(uint8_t val);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize PCD8544 display
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval HAL status
 */
HAL_StatusTypeDef PCD8544_Init(PCD8544_HandleTypeDef *hlcd) {
    // Initialize handle
    memset(hlcd->buffer, 0, PCD8544_BUFFER_SIZE);
    hlcd->cursor_x = 0;
    hlcd->cursor_y = 0;
    hlcd->textsize = 1;
    hlcd->textcolor = BLACK;
    hlcd->wrap = 1;
    
    // Hardware reset
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    
    // Initialize display
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET | 0x01); // Extended instructions
    PCD8544_WriteCommand(PCD8544_SETVOP | 0x3F);      // Set contrast
    PCD8544_WriteCommand(PCD8544_SETBIAS | 0x03);     // Set bias
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET);        // Basic instructions
    PCD8544_WriteCommand(PCD8544_SETDISPLAYNORMAL);   // Normal display mode
    
    return HAL_OK;
}

/**
 * @brief  Clear the display buffer
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval None
 */
void PCD8544_Clear(PCD8544_HandleTypeDef *hlcd) {
    memset(hlcd->buffer, 0, PCD8544_BUFFER_SIZE);
}

/**
 * @brief  Update the display with buffer contents
 * @param  hlcd: Pointer to PCD8544 handle
 * @retval None
 */
void PCD8544_Display(PCD8544_HandleTypeDef *hlcd) {
    uint16_t i;
    
    // Set address to 0,0
    PCD8544_WriteCommand(PCD8544_SETXADDR | 0);
    PCD8544_WriteCommand(PCD8544_SETYADDR | 0);
    
    // Send all buffer data
    for (i = 0; i < PCD8544_BUFFER_SIZE; i++) {
        PCD8544_WriteData(hlcd->buffer[i]);
    }
}

/**
 * @brief  Set display contrast
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  contrast: Contrast value (0-127)
 * @retval None
 */
void PCD8544_SetContrast(PCD8544_HandleTypeDef *hlcd, uint8_t contrast) {
    if (contrast > 127) contrast = 127;
    
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET | 0x01); // Extended instructions
    PCD8544_WriteCommand(PCD8544_SETVOP | contrast);  // Set contrast
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET);        // Basic instructions
}

/**
 * @brief  Set display mode
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  mode: Display mode
 * @retval None
 */
void PCD8544_SetDisplayMode(PCD8544_HandleTypeDef *hlcd, uint8_t mode) {
    PCD8544_WriteCommand(mode);
}

/**
 * @brief  Set cursor position
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @retval None
 */
void PCD8544_SetCursor(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y) {
    hlcd->cursor_x = x;
    hlcd->cursor_y = y;
}

/**
 * @brief  Set text size
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  size: Text size (1-4)
 * @retval None
 */
void PCD8544_SetTextSize(PCD8544_HandleTypeDef *hlcd, uint8_t size) {
    if (size > 4) size = 4;
    hlcd->textsize = size;
}

/**
 * @brief  Set text color
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  color: Text color (BLACK or WHITE)
 * @retval None
 */
void PCD8544_SetTextColor(PCD8544_HandleTypeDef *hlcd, uint8_t color) {
    hlcd->textcolor = color;
}

/**
 * @brief  Write a character
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  c: Character to write
 * @retval None
 */
void PCD8544_WriteChar(PCD8544_HandleTypeDef *hlcd, char c) {
    uint8_t i, j;
    uint8_t char_index;
    
    if (c < 32 || c > 127) c = 32; // Use space for invalid characters
    char_index = c - 32;
    
    for (i = 0; i < 5; i++) {
        uint8_t line = font5x7[char_index][i];
        for (j = 0; j < 7; j++) {
            if (line & 0x01) {
                PCD8544_DrawPixel(hlcd, hlcd->cursor_x + i * hlcd->textsize, 
                                 hlcd->cursor_y + j * hlcd->textsize, hlcd->textcolor);
            }
            line >>= 1;
        }
    }
    
    hlcd->cursor_x += 6 * hlcd->textsize;
    if (hlcd->wrap && hlcd->cursor_x > PCD8544_WIDTH - 6 * hlcd->textsize) {
        hlcd->cursor_x = 0;
        hlcd->cursor_y += 8 * hlcd->textsize;
    }
}

/**
 * @brief  Write a string
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  str: String to write
 * @retval None
 */
void PCD8544_WriteString(PCD8544_HandleTypeDef *hlcd, const char* str) {
    while (*str) {
        PCD8544_WriteChar(hlcd, *str++);
    }
}

/**
 * @brief  Draw a pixel
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x: X coordinate
 * @param  y: Y coordinate
 * @param  color: Pixel color
 * @retval None
 */
void PCD8544_DrawPixel(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t color) {
    if (x >= PCD8544_WIDTH || y >= PCD8544_HEIGHT) return;
    
    uint16_t byte_index = (y / 8) * PCD8544_WIDTH + x;
    uint8_t bit_mask = 1 << (y % 8);
    
    if (color) {
        hlcd->buffer[byte_index] |= bit_mask;
    } else {
        hlcd->buffer[byte_index] &= ~bit_mask;
    }
}

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
void PCD8544_DrawLine(PCD8544_HandleTypeDef *hlcd, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;
    
    while (1) {
        PCD8544_DrawPixel(hlcd, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int16_t e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

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
void PCD8544_DrawRect(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
    PCD8544_DrawLine(hlcd, x, y, x + w - 1, y, color);
    PCD8544_DrawLine(hlcd, x + w - 1, y, x + w - 1, y + h - 1, color);
    PCD8544_DrawLine(hlcd, x + w - 1, y + h - 1, x, y + h - 1, color);
    PCD8544_DrawLine(hlcd, x, y + h - 1, x, y, color);
}

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
void PCD8544_FillRect(PCD8544_HandleTypeDef *hlcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
    uint8_t i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            PCD8544_DrawPixel(hlcd, x + i, y + j, color);
        }
    }
}

/**
 * @brief  Draw a circle
 * @param  hlcd: Pointer to PCD8544 handle
 * @param  x0: Center X coordinate
 * @param  y0: Center Y coordinate
 * @param  r: Radius
 * @param  color: Circle color
 * @retval None
 */
void PCD8544_DrawCircle(PCD8544_HandleTypeDef *hlcd, uint8_t x0, uint8_t y0, uint8_t r, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    
    PCD8544_DrawPixel(hlcd, x0, y0 + r, color);
    PCD8544_DrawPixel(hlcd, x0, y0 - r, color);
    PCD8544_DrawPixel(hlcd, x0 + r, y0, color);
    PCD8544_DrawPixel(hlcd, x0 - r, y0, color);
    
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        PCD8544_DrawPixel(hlcd, x0 + x, y0 + y, color);
        PCD8544_DrawPixel(hlcd, x0 - x, y0 + y, color);
        PCD8544_DrawPixel(hlcd, x0 + x, y0 - y, color);
        PCD8544_DrawPixel(hlcd, x0 - x, y0 - y, color);
        PCD8544_DrawPixel(hlcd, x0 + y, y0 + x, color);
        PCD8544_DrawPixel(hlcd, x0 - y, y0 + x, color);
        PCD8544_DrawPixel(hlcd, x0 + y, y0 - x, color);
        PCD8544_DrawPixel(hlcd, x0 - y, y0 - x, color);
    }
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Write a command to the display
 * @param  cmd: Command to write
 * @retval None
 */
static void PCD8544_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET); // Command mode
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET); // Enable
    PCD8544_ShiftOut(cmd);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);   // Disable
}

/**
 * @brief  Write data to the display
 * @param  data: Data to write
 * @retval None
 */
static void PCD8544_WriteData(uint8_t data) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);   // Data mode
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET); // Enable
    PCD8544_ShiftOut(data);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);   // Disable
}

/**
 * @brief  Shift out a byte
 * @param  val: Byte to shift out
 * @retval None
 */
static void PCD8544_ShiftOut(uint8_t val) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, (val & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        val <<= 1;
        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
    }
} 