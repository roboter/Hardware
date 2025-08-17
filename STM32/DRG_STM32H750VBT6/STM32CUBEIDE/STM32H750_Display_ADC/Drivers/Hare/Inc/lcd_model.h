#ifndef __MODEL_H
#define __MODEL_H

#include "spi.h"

void LCD_Test_ADC(void);       // Display internal ADC measurement
void LCD_Test_Clear1(void);    // Clear the screen
void LCD_Test(void);           // Text display test
void LCD_Line(void);           // Draw lines
void LCD_Rectangle(void);      // Draw rectangles
void LCD_RouRectangle(void);   // Draw rounded rectangles
void LCD_Ellipse(void);        // Draw ellipses
void LCD_Circle(void);         // Draw circles
void LCD_Triangle(void);       // Draw triangles
void LCD_Picture(void);        // Display picture
void LCD_Arc(void);            // Draw arcs
void LCD_Polygon(void);        // Draw polygons
void LCD_Clock(void);          // Display clock
void Clock_Needle(int t,int l);// Draw hour/minute hand path
void Clock_Sec(int t,int l);   // Draw second hand path and dial marks
void DrawClockHand(int t, int l, uint32_t color); // Draw clock hand in given color

#endif 
 
