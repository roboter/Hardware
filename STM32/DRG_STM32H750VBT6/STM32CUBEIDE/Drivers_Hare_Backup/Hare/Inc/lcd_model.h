#ifndef __MODEL_H
#define __MODEL_H

#include "spi.h"


void LCD_Test_Clear1(void);// �������� 
void LCD_Test(void);//�ı���ʾ
void LCD_Line(void);//����
void LCD_Rectangle(void);//����
void LCD_RouRectangle(void);//Բ�Ǿ���
void LCD_Ellipse(void);//��Բ
void LCD_Circle(void);//Բ
void LCD_Triangle(void);//������
void LCD_Picture(void);//ͼƬ
void LCD_Arc(void);//Բ��
void LCD_Polygon(void);//�����
void LCD_Clock(void);//ʱ��
void Clock_Needle(int t,int l);//ʱ�ӡ������ƶ��켣
void Clock_Sec(int t,int l);//�����ƶ��켣�ͱ���
void DrawClockHand(int t, int l, uint32_t color);

#endif 
 
