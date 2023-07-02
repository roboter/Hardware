
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


void TFT_CS(u8 d);

void Lcd_Init(void);


void Lcd_Write_Data(u16 data);								 //写16位数据

void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq);    //设置显示范围




//屏幕尺寸
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






