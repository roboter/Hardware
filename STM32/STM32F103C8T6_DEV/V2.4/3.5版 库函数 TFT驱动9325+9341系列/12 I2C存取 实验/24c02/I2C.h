

#ifndef I2C_H
#define I2C_H
#include "stm32f10x.h"
#include "delay.h"


//IO方向设置
#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO操作函数	 
#define SCL    PCout(12) //SCL
#define SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //输入SDA 



void IIC_Init(void);      //IIC端口初始化
void Start_I2c(void);		  //启动总线
void Stop_I2c(void);		  //停止总线
void SendByte(u8 c);	  //字节数据发送函数
u8  RcvByte(u8 ack);	  //字节数据接收函数 	    

u8 I2c_wait_ack(void);	  //等待应答信号到来


#endif
