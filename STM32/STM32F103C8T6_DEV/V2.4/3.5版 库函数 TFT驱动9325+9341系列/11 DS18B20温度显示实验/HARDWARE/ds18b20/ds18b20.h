


#ifndef  DS18B20_H
#define  DS18B20_H
#include "delay.h"
#include  "stm32f10x.h"

//IO��������
#define DS18B20_IO_IN()  {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00800000;}
#define DS18B20_IO_OUT() {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=0X00300000;}
////IO��������											   
#define	DQ_OUT PAout(13) //���ݶ˿�	PA13 
#define	DQ_IN  PAin(13)  //���ݶ˿�	PA13 


u8 ds18b20_init(void);   //DS18B20 ��ӦSTM32io��ʼ�� ͬʱ����Ƿ�����
short read_temp(void);	 //�¶ȶ�ȡ
void ow_reset(void);     //���߸�λ
u8 ds18B20_check(void);  //�ж�DS�Ƿ�����


#endif




