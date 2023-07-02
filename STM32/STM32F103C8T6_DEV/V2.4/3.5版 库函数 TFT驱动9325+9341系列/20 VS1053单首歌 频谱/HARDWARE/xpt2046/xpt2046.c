
 
#include "stm32f10x.h"
#include "math.h"
#include "xpt2046.h"
#include "delay.h"
#include "spi.h"
#include "gui.h"
#include "tft.h"





//初始化 触摸芯片XPT2046 SPI片选IO 及判断IO
void XPT2046_Init(void)
{	
  	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;      // PA11 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);				//拉高片选IO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;      // PA12 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //设置成下拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}  




//SPI总线法 读取XPT2046数据
//采集触摸时xpt输出的物理坐标 x y  
//此函数没有转换成LCD的实际坐标 
//为校准函数做读取
//返回 xpt2046ad.x  物理x坐标
//     xpt2046ad.y  物理y坐标
//     xpt2046ad.flag 采集成功标志
struct TFT_Pointer xpt2046ad()		                                 
{
 struct TFT_Pointer result;
 u8   ax[8];
 u16 x1,y1;
 u16 x2,y2;

 result.x=0;
 result.y=0;
 result.flag=0;
 
#define ERR_RANGE 5 //误差范围 
  
 if(xpt2046_isClick==0)
 {	 
  delay_ms(1);
  if(xpt2046_isClick==0)
  {
    xpt2046_CS_0; 		//开片选
	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);		//降低 SPI通讯速度 使触摸芯片放回数据更稳定

//	SPI1_ReadWriteByte(0xff);
   
   /*这里采用16时钟周期采集  因为 此触摸功能采用的是SPI总线
     而SPI功能是只能8位传输  XPT2046的AD分辨率为12位  
	 这样8位的SPI接收是不行的
	 所以 根据XPT2046手册中 16时钟周期 时序图 可以看出
	 发送采集数据  接收一次SPI数据后 在发送空功能的SPI数据  就会把剩下的部分接收到
	 这样先接收的 是低字节数据  第二次接收的是高字节数据  移位后 便是12位的AD值   
   */
   ax[0]=SPI1_ReadWriteByte(0x90);  //送控制字10010000即用差分方式读X坐标，舍弃读取的数据
   ax[0]=SPI1_ReadWriteByte(0x00);  //发送任意数据（最高位不能为1，和2046命令冲突），接收X高字节
   ax[1]=SPI1_ReadWriteByte(0xD0);  //送控制字11010000即用差分方式读Y坐标，接收X低字节
   ax[2]=SPI1_ReadWriteByte(0x00);  //发送任意数据（同上），接收Y高字节
   ax[3]=SPI1_ReadWriteByte(0x90);  //送控制字10010000 （第二次）读X坐标，接收Y低字节
   ax[4]=SPI1_ReadWriteByte(0x00);  //发送任意数据（同上），接收X高字节
   ax[5]=SPI1_ReadWriteByte(0xD0);  //送控制字11010000  （第二次）读Y坐标，接收X低字节
   ax[6]=SPI1_ReadWriteByte(0x00);  //发送任意数据（同上)，接收Y高字节
   ax[7]=SPI1_ReadWriteByte(0x90);  //送控制字10010000  （第三次）读X坐标，接收Y低字节

								//提取两次采集值
   y1=(ax[0]<<5)|(ax[1]>>3);
   y2=(ax[4]<<5)|(ax[5]>>3);
   x1=(ax[2]<<5)|(ax[3]>>3);
   x2=(ax[6]<<5)|(ax[7]>>3);

if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-ERR_RANGE内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
   {
   	result.flag=1;			//打开标志位
	result.x=(x1+x2)/2;
	result.y=(y1+y2)/2;
   }
   else result.flag=0;

   SPI1_SetSpeed(SPI_BaudRatePrescaler_8);		//调整SPI速度为最高
   xpt2046_CS_1; 		//关片选
   
  }
 } 

 return result;
}





//触摸数据转换屏实际坐标函数体
//返回 result.x坐标 result.y坐标 
struct TFT_Pointer TFT_Cm(void)		                                  
{
 u16 a,b;				//临时变量
 struct TFT_Pointer result;

 result=xpt2046ad();	 //读取AD值

//触摸板X Y
   a=result.x;
   b=result.y;
/* 触摸屏计算公式
   lcdx=xa*tpx+xb;
   lcdy=ya*tpy+yb;
   lcdx,lcdy为屏坐标  tpx,tpy为触屏板值 xa,ya为比例因子  xb,yb为偏移量

   计算方法 
   在屏幕上指定lcdx,lcdy位置画出十字图形 分别画在屏幕上的4个角位置
   用触摸笔分别点击 得到其中的触摸值
   根据上面的公式 计算	xa,ya  xb,yb  这样就能使得触摸板和屏幕校准
  */
	 
		 result.x=0.065894*a-16;			//将得到的AD值带入公式 计算lcd屏的x y坐标 
		 result.y=320-(0.084031*b-14);

 return result;								//返回坐标值
}


















