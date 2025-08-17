/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
#include "stm32h7xx_hal.h"
#include "usart.h"

#include "lcd_fonts.h"	// Font and image library files, users cannot delete
#include	"lcd_image.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */


/*----------------------------------------------- LCD Configuration -------------------------------------------*/
#define LCD_Width     240		// LCD screen pixel width
#define LCD_Height    280		// LCD screen pixel height

#define RADIAN(angle)  ((angle==0)?0:(3.14159*angle/180))   // Angle conversion
#define MAX(x,y)  		((x)>(y)? (x):(y))
#define MIN(x,y)  		((x)<(y)? (x):(y))
#define SWAP(x, y) \
	(y) = (x) + (y); \
	(x) = (y) - (x); \
	(y) = (y) - (x);
#define ABS(X)  ((X) > 0 ? (X) : -(X))   // Get absolute value of signed number
	
// 2D coordinate structure, x is horizontal, y is vertical
typedef struct COORDINATE 
{
    int x;  // Horizontal coordinate
    int y;  // Vertical coordinate
} TypeXY;

#define point TypeXY 

// Rotation structure, including rotation center center, rotation angle angle, rotation direction direct
typedef struct ROATE
{
    TypeXY center;   // Rotation center coordinates
    float angle;     // Rotation angle
    int direct;      // Rotation direction
} TypeRoate;

// Display direction settings
// Use LCD_DisplayDirection(Direction_H) to set screen display direction
#define	Direction_H				0					//LCD horizontal display
#define	Direction_H_Flip	   1					//LCD horizontal display, vertical flip
#define	Direction_V				2					//LCD vertical display 
#define	Direction_V_Flip	   3					//LCD vertical display, horizontal flip 

// Set whether to fill 0 when displaying numbers (0 means no space)
// Only affects LCD_DisplayNumber() display numbers and LCD_DisplayDecimals() display decimals
// Use LCD_ShowNumMode(Fill_Zero) to set number of digits to fill 0, 123 will display as 000123
#define  Fill_Zero  0		//Fill 0
#define  Fill_Space 1		//Fill space


/*---------------------------------------- LCD Color Definitions ------------------------------------------------------

 1. For user convenience, supports 24-bit RGB888 color, then automatically converts to 16-bit RGB565 through algorithm
 2. In 24-bit color, from high to low bits correspond to R, G, B 3 color channels
 3. Users can directly use 24-bit RGB color values, then pass color to LCD_SetColor() and LCD_SetBackColor() to display corresponding colors
 */                                                  						
#define 	LCD_WHITE       0xFFFFFF	 // White
#define 	LCD_BLACK       0x000000    // Black
                        
#define 	LCD_BLUE        0x0000FF	 //	Blue
#define 	LCD_GREEN       0x00FF00    //	Green
#define 	LCD_RED         0xFF0000    //	Red
#define 	LCD_CYAN        0x00FFFF    //	Cyan
#define 	LCD_MAGENTA     0xFF00FF    //	Magenta
#define 	LCD_YELLOW      0xFFFF00    //	Yellow
#define 	LCD_GREY        0x2C2C2C    //	Grey
												
#define 	LIGHT_BLUE      0x8080FF    //	Light blue
#define 	LIGHT_GREEN     0x80FF80    //	Light green
#define 	LIGHT_RED       0xFF8080    //	Light red
#define 	LIGHT_CYAN      0x80FFFF    //	Light cyan
#define 	LIGHT_MAGENTA   0xFF80FF    //	Light magenta
#define 	LIGHT_YELLOW    0xFFFF80    //	Light yellow
#define 	LIGHT_GREY      0xA3A3A3    //	Light grey
												
#define 	DARK_BLUE       0x000080    //	Dark blue
#define 	DARK_GREEN      0x008000    //	Dark green
#define 	DARK_RED        0x800000    //	Dark red
#define 	DARK_CYAN       0x008080    //	Dark cyan
#define 	DARK_MAGENTA    0x800080    //	Dark magenta
#define 	DARK_YELLOW     0x808000    //	Dark yellow
#define 	DARK_GREY       0x404040    //	Dark grey

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


void  MX_SPI4_Init(void);
void  SPI_LCD_Init(void);      // LCD and SPI initialization   
void  LCD_Clear(void);			 // Clear screen
void  LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// Partial clear screen

void  LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);	// Set address		
void  LCD_SetColor(uint32_t Color); 				   //	Set foreground color
void  LCD_SetBackColor(uint32_t Color);  				//	Set background color
void  LCD_SetDirection(uint8_t direction);  	      //	Set display direction

//>>>>>	Display ASCII characters
void  LCD_SetAsciiFont(pFONT *fonts);										//	Set ASCII font
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	Display single ASCII character
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	Display ASCII string

//>>>>>	Display Chinese characters (including ASCII)
void 	LCD_SetTextFont(pFONT *fonts);										// Set text font, including Chinese and ASCII fonts
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// Display Chinese characters
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// Display character string, including Chinese and ASCII characters

//>>>>>	Display numbers and decimals
void  LCD_ShowNumMode(uint8_t mode);		// Set number display mode, fill space or fill 0
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// Display number
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// Display decimal

//>>>>>	2D graphics functions
void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   	//Draw point

void  LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // Draw vertical line
void  LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // Draw horizontal line
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	// Draw line between two points

void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//Draw rectangle
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									//Draw circle
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											//Draw ellipse

//>>>>>	Fill graphics functions
void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//Fill rectangle
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									//Fill circle

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pImage); // Draw image
void DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // Draw rounded rectangle border
void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // Fill rounded rectangle
void DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername); // Draw circle corner helper
void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta); // Fill circle corner helper
void DrawFillEllipse(int x0, int y0, int rx, int ry);         // Fill ellipse

void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2); // Draw triangle
void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2); // Fill triangle
void DrawArc(int x, int y, unsigned char r, int angle_start, int angle_end); // Draw arc
TypeXY GetXY(void);   // Get current coordinates
void SetRotateCenter(int x0, int y0);  // Set rotation center
void SetAngleDir(int direction);       // Set rotation direction
void SetAngle(float angle);             // Set rotation angle
static void Rotate(int x0, int y0, int *x, int *y, double angle, int direction); // Rotation function
float mySqrt(float x);  // Square root
TypeXY GetRotateXY(int x, int y);  // Get rotated coordinates
void MoveTo(int x, int y);  // Move to specified coordinates
void LineTo(int x, int y);  // Draw line to specified coordinates
void SetRotateValue(int x, int y, float angle, int direct); // Set rotation value

//>>>>>	Draw color images
void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)  ;

//>>>>>	Copy buffer function, directly copy data to screen buffer
void	LCD_CopyBuffer(uint16_t x, uint16_t y,uint16_t width,uint16_t height,uint16_t *DataBuff);

 /*--------------------------------------------- LCD Control Functions -----------------------------------------------*/

#define  LCD_Backlight_PIN								GPIO_PIN_15				         // Backlight pin				
#define	LCD_Backlight_PORT							GPIOD									// Backlight GPIO port
#define 	GPIO_LDC_Backlight_CLK_ENABLE        	__HAL_RCC_GPIOD_CLK_ENABLE()	// Backlight GPIO clock 	

#define	LCD_Backlight_OFF		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);	// Low level turns off backlight
#define 	LCD_Backlight_ON		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);		// High level turns on backlight
 
#define  LCD_DC_PIN						GPIO_PIN_15				         // Data/command selection pin				
#define	LCD_DC_PORT						GPIOE									// Data/command selection GPIO port
#define 	GPIO_LDC_DC_CLK_ENABLE     __HAL_RCC_GPIOE_CLK_ENABLE()	// Data/command selection GPIO clock 	

#define	LCD_DC_Command		   HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	   // Low level for command transmission 
#define 	LCD_DC_Data		      HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// High level for data transmission

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

