 
 
#ifndef XPT2046_H
#define XPT2046_H






#define	xpt2046_CS_0  GPIO_ResetBits(GPIOA,GPIO_Pin_11)		   //片选
#define xpt2046_CS_1    GPIO_SetBits(GPIOA,GPIO_Pin_11)

#define xpt2046_isClick  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)		 //判断触摸屏是否按下，返回值等于1时按下


struct TFT_Pointer			  //定义三个变量的结构体函数  主要应用于 对采集的AD值 X Y  和是否有触摸屏被激发的标志位flag
{
 u16 x;
 u16 y;
 u8 flag;
};


void XPT2046_Init(void);             //xpt2046 IO口初始化

struct TFT_Pointer TFT_Cm(void);     //TFT 触摸屏函数

#endif
