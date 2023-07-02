
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


void TFT_CS(u8 d);

void Lcd_Init(void);

void GUI_Clear(u16 color);

void Lcd_Write_Data(u16 data);								 //写16位数据

void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq);    //设置显示范围

//颜色定义
/*定义常用颜色码*/
#define Red      0xf800	//红
#define Yellow   0xffe0	//黄
#define Green    0x07e0	//绿
#define Cyan     0x07ff	//青
#define Blue     0x001f	//蓝
#define Purple   0xf81f	//紫
#define Black    0x0000	//黑
#define White    0xffff	//白
#define Gray     0x7bef	//灰
#define Blue1    0xa5ff //淡蓝
#define Blue2	 0x7cdf
#define Purple1  0x8a9e //淡紫
#define Green1   0x0410 //墨绿
#define Green2   0x2616
#define Blue3	 0x751E
#define Purple2  0xcd9e //淡紫
#define Red2	 0XF260	//淡红
#define Red3	 0X8000	//棕红
#define window   0XDED7


//屏幕尺寸
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






