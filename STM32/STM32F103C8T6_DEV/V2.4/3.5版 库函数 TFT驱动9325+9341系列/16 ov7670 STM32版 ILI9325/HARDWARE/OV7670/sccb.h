#ifndef __SCCB_H
#define __SCCB_H
#include "stm32f10x.h"


//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEKս��STM32������
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/14
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=0X00008000;}
#define SCCB_SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=0X00003000;}

//IO��������	 
#define SCCB_SCL    		PCout(12)	 	//SCL
#define SCCB_SDA    		PCout(11) 		//SDA	 

#define SCCB_READ_SDA    	PCin(11)  		//����SDA    
#define SCCB_ID   			0X42  			//OV7670��ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













