#ifndef __MODEL_H
#define __MODEL_H

#include "spi.h"


void LCD_Test_Clear1(void);// 清屏测试 
void LCD_Test(void);//文本显示
void LCD_Line(void);//画线
void LCD_Rectangle(void);//矩形
void LCD_RouRectangle(void);//圆角矩形
void LCD_Ellipse(void);//椭圆
void LCD_Circle(void);//圆
void LCD_Triangle(void);//三角形
void LCD_Picture(void);//图片
void LCD_Arc(void);//圆弧
void LCD_Polygon(void);//多边形
void LCD_Clock(void);//时钟
void Clock_Needle(int t,int l);//时钟、分钟移动轨迹
void Clock_Sec(int t,int l);//秒针移动轨迹和表盘
void DrawClockHand(int t, int l, uint32_t color);

#endif 
 
