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

#include "lcd_fonts.h"	// 图片和字库文件不是必须，用户可自行删减
#include	"lcd_image.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */


/*----------------------------------------------- 参数宏 -------------------------------------------*/
#define LCD_Width     240		// LCD的像素长度
#define LCD_Height    280		// LCD的像素宽度

#define RADIAN(angle)  ((angle==0)?0:(3.14159*angle/180))   //角度转换
#define MAX(x,y)  		((x)>(y)? (x):(y))
#define MIN(x,y)  		((x)<(y)? (x):(y))
#define SWAP(x, y) \
	(y) = (x) + (y); \
	(x) = (y) - (x); \
	(y) = (y) - (x);
#define ABS(X)  ((X) > 0 ? (X) : -(X))   //计算输入数值的绝对值
	
//二维坐标结构体，包含横坐标 x 和纵坐标 y
typedef struct COORDINATE 
{
    int x;  // 横坐标
    int y;  // 纵坐标
} TypeXY;

#define point TypeXY 

//旋转结构体，包含旋转中心 center、旋转角度 angle 和旋转方向 direct
typedef struct ROATE
{
    TypeXY center;   // 旋转中心坐标
    float angle;     // 旋转角度
    int direct;      // 旋转方向
} TypeRoate;

// 显示方向参数
// 使用示例：LCD_DisplayDirection(Direction_H) 设置屏幕横屏显示
#define	Direction_H				0					//LCD横屏显示
#define	Direction_H_Flip	   1					//LCD横屏显示,上下翻转
#define	Direction_V				2					//LCD竖屏显示 
#define	Direction_V_Flip	   3					//LCD竖屏显示,上下翻转 

// 设置变量显示时多余位补0还是补空格
// 只有 LCD_DisplayNumber() 显示整数 和 LCD_DisplayDecimals()显示小数 这两个函数用到
// 使用示例： LCD_ShowNumMode(Fill_Zero) 设置多余位填充0，例如 123 可以显示为 000123
#define  Fill_Zero  0		//填充0
#define  Fill_Space 1		//填充空格


/*---------------------------------------- 常用颜色 ------------------------------------------------------

 1. 这里为了方便用户使用，定义的是24位 RGB888颜色，然后再通过代码自动转换成 16位 RGB565 的颜色
 2. 24位的颜色中，从高位到低位分别对应 R、G、B  3个颜色通道
 3. 用户可以在电脑用调色板获取24位RGB颜色，再将颜色输入LCD_SetColor()或LCD_SetBackColor()就可以显示出相应的颜色 
 */                                                  						
#define 	LCD_WHITE       0xFFFFFF	 // 纯白色
#define 	LCD_BLACK       0x000000    // 纯黑色
                        
#define 	LCD_BLUE        0x0000FF	 //	纯蓝色
#define 	LCD_GREEN       0x00FF00    //	纯绿色
#define 	LCD_RED         0xFF0000    //	纯红色
#define 	LCD_CYAN        0x00FFFF    //	蓝绿色
#define 	LCD_MAGENTA     0xFF00FF    //	紫红色
#define 	LCD_YELLOW      0xFFFF00    //	黄色
#define 	LCD_GREY        0x2C2C2C    //	灰色
												
#define 	LIGHT_BLUE      0x8080FF    //	亮蓝色
#define 	LIGHT_GREEN     0x80FF80    //	亮绿色
#define 	LIGHT_RED       0xFF8080    //	亮红色
#define 	LIGHT_CYAN      0x80FFFF    //	亮蓝绿色
#define 	LIGHT_MAGENTA   0xFF80FF    //	亮紫红色
#define 	LIGHT_YELLOW    0xFFFF80    //	亮黄色
#define 	LIGHT_GREY      0xA3A3A3    //	亮灰色
												
#define 	DARK_BLUE       0x000080    //	暗蓝色
#define 	DARK_GREEN      0x008000    //	暗绿色
#define 	DARK_RED        0x800000    //	暗红色
#define 	DARK_CYAN       0x008080    //	暗蓝绿色
#define 	DARK_MAGENTA    0x800080    //	暗紫红色
#define 	DARK_YELLOW     0x808000    //	暗黄色
#define 	DARK_GREY       0x404040    //	暗灰色

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


void  MX_SPI4_Init(void);
void  SPI_LCD_Init(void);      // 液晶屏以及SPI初始化   
void  LCD_Clear(void);			 // 清屏函数
void  LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// 局部清屏函数

void  LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);	// 设置坐标		
void  LCD_SetColor(uint32_t Color); 				   //	设置画笔颜色
void  LCD_SetBackColor(uint32_t Color);  				//	设置背景颜色
void  LCD_SetDirection(uint8_t direction);  	      //	设置显示方向

//>>>>>	显示ASCII字符
void  LCD_SetAsciiFont(pFONT *fonts);										//	设置ASCII字体
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	显示单个ASCII字符
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	显示ASCII字符串

//>>>>>	显示中文字符，包括ASCII码
void 	LCD_SetTextFont(pFONT *fonts);										// 设置文本字体，包括中文和ASCII字体
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// 显示单个汉字
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// 显示字符串，包括中文和ASCII字符

//>>>>>	显示整数或小数
void  LCD_ShowNumMode(uint8_t mode);		// 设置变量显示模式，多余位填充空格还是填充0
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// 显示整数
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// 显示小数

//>>>>>	2D图形函数
void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   	//画点

void  LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // 画垂直线
void  LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // 画水平线
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	// 两点之间画线

void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//画矩形
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									//画圆
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											//画椭圆

//>>>>>	区域填充函数
void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//填充矩形
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									//填充圆

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pImage); // 画图像
void DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // 画圆角矩形边框
void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // 填充圆角矩形
void DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername); // 画圆角辅助函数
void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta); // 填充圆角辅助函数
void DrawFillEllipse(int x0, int y0, int rx, int ry);         // 填充椭圆

void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2); // 画三角形
void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2); // 填充三角形
void DrawArc(int x, int y, unsigned char r, int angle_start, int angle_end); // 画圆弧
TypeXY GetXY(void);   // 获取当前坐标
void SetRotateCenter(int x0, int y0);  // 设置旋转中心
void SetAngleDir(int direction);       // 设置旋转方向
void SetAngle(float angle);             // 设置旋转角度
static void Rotate(int x0, int y0, int *x, int *y, double angle, int direction); // 旋转坐标
float mySqrt(float x);  // 计算平方根
TypeXY GetRotateXY(int x, int y);  // 获取旋转后的坐标
void MoveTo(int x, int y);  // 移动到指定坐标
void LineTo(int x, int y);  // 画线到指定坐标
void SetRotateValue(int x, int y, float angle, int direct); // 设置旋转值

//>>>>>	绘制单色图片
void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)  ;

//>>>>>	批量复制函数，直接将数据复制到屏幕的显存
void	LCD_CopyBuffer(uint16_t x, uint16_t y,uint16_t width,uint16_t height,uint16_t *DataBuff);

 /*--------------------------------------------- LCD其它引脚 -----------------------------------------------*/

#define  LCD_Backlight_PIN								GPIO_PIN_15				         // 背光  引脚				
#define	LCD_Backlight_PORT							GPIOD									// 背光 GPIO端口
#define 	GPIO_LDC_Backlight_CLK_ENABLE        	__HAL_RCC_GPIOD_CLK_ENABLE()	// 背光 GPIO时钟 	

#define	LCD_Backlight_OFF		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);	// 低电平，关闭背光
#define 	LCD_Backlight_ON		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);		// 高电平，开启背光
 
#define  LCD_DC_PIN						GPIO_PIN_15				         // 数据指令选择  引脚				
#define	LCD_DC_PORT						GPIOE									// 数据指令选择  GPIO端口
#define 	GPIO_LDC_DC_CLK_ENABLE     __HAL_RCC_GPIOE_CLK_ENABLE()	// 数据指令选择  GPIO时钟 	

#define	LCD_DC_Command		   HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	   // 低电平，指令传输 
#define 	LCD_DC_Data		      HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// 高电平，数据传输

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

