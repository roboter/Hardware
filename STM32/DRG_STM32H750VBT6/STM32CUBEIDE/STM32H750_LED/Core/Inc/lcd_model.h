#ifndef __MODEL_H
#define __MODEL_H

#include "spi.h"


void LCD_Test_Clear1(void);// Clear screen test
void LCD_Test(void);//Text display test
void LCD_Line(void);//Line test
void LCD_Rectangle(void);//Rectangle test
void LCD_RouRectangle(void);//Rounded rectangle test
void LCD_Ellipse(void);//Ellipse test
void LCD_Circle(void);//Circle test
void LCD_Triangle(void);//Triangle test
void LCD_Picture(void);//Picture test
void LCD_Arc(void);//Arc test
void LCD_Polygon(void);//Polygon test
void LCD_Clock(void);//Clock test
void Clock_Needle(int t,int l);//Clock needle movement trajectory
void Clock_Sec(int t,int l);//Second needle movement trajectory and display
void DrawClockHand(int t, int l, uint32_t color);

#endif 