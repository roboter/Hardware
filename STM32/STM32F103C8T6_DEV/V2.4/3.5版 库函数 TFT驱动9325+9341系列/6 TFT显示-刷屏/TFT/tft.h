
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


void TFT_CS(u8 d);

void Lcd_Init(void);

void GUI_Clear(u16 color);

//ÑÕÉ«¶¨Òå
/*¶¨Òå³£ÓÃÑÕÉ«Âë*/
#define Red      0xf800	//ºì
#define Yellow   0xffe0	//»Æ
#define Green    0x07e0	//ÂÌ
#define Cyan     0x07ff	//Çà
#define Blue     0x001f	//À¶
#define Purple   0xf81f	//×Ï
#define Black    0x0000	//ºÚ
#define White    0xffff	//°×
#define Gray     0x7bef	//»Ò
#define Blue1    0xa5ff //µ­À¶
#define Blue2	 0x7cdf
#define Purple1  0x8a9e //µ­×Ï
#define Green1   0x0410 //Ä«ÂÌ
#define Green2   0x2616
#define Blue3	 0x751E
#define Purple2  0xcd9e //µ­×Ï
#define Red2	 0XF260	//µ­ºì
#define Red3	 0X8000	//×Øºì
#define window   0XDED7


//ÆÁÄ»³ß´ç
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






