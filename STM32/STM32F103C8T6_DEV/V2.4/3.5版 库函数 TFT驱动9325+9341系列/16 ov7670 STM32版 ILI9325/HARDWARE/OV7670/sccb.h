#ifndef __SCCB_H
#define __SCCB_H
#include "stm32f10x.h"


//////////////////////////////////////////////////////////////////////////////////	 
//本程序参考自网友guanfu_wang代码。
//ALIENTEK战舰STM32开发板
//SCCB 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/14
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=0X00008000;}
#define SCCB_SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=0X00003000;}

//IO操作函数	 
#define SCCB_SCL    		PCout(12)	 	//SCL
#define SCCB_SDA    		PCout(11) 		//SDA	 

#define SCCB_READ_SDA    	PCin(11)  		//输入SDA    
#define SCCB_ID   			0X42  			//OV7670的ID

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













