


#ifndef  DS18B20_H
#define  DS18B20_H
#include "delay.h"
#include  "stm32f10x.h"

//IO方向设置
#define DS18B20_IO_IN()  {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00800000;}
#define DS18B20_IO_OUT() {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00300000;}
////IO操作函数											   
#define	DQ_OUT PAout(13) //数据端口	PA13 
#define	DQ_IN  PAin(13)  //数据端口	PA13 


u8 ds18b20_init(void);   //DS18B20 对应STM32io初始化 同时检测是否在线
short read_temp(void);	 //温度读取
void ow_reset(void);     //总线复位
u8 ds18B20_check(void);  //判断DS是否在线


#endif




