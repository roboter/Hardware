

#ifndef I2C_H
#define I2C_H
#include <stm32f1xx.h>
//#include "stm32f1xx_hal.h"
#include <delay.h>
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

//IO��������
#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO��������	 
#define SCL    PCout(12) //SCL
#define SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //����SDA 



void IIC_Init(void);      //IIC�˿ڳ�ʼ��
void Start_I2c(void);		  //��������
void Stop_I2c(void);		  //ֹͣ����
void SendByte(u8 c);	  //�ֽ����ݷ��ͺ���
u8  RcvByte(u8 ack);	  //�ֽ����ݽ��պ��� 	    

u8 I2c_wait_ack(void);	  //�ȴ�Ӧ���źŵ���


#endif
