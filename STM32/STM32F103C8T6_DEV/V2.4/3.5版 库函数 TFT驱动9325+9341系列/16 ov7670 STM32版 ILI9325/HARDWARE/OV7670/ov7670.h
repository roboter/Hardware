	


#ifndef _OV7670_H
#define _OV7670_H
#include "stm32f10x.h"
#include "sccb.h"


#define OV7670_VSYNC  	PDin(2)			//同步信号检测IO
#define OV7670_WRST		PAout(0)		//写指针复位
#define OV7670_WREN		PAout(8)		//写入FIFO使能
#define OV7670_RCK		PAout(3)		//读数据时钟
#define OV7670_RRST		PAout(2)  		//读指针复位
#define OV7670_CS		PAout(1)  		//片选信号(OE)


//快速RCK  RRST	  
//去除繁琐的位带效果  使IO的调用速度达到最快
#define	OV7670_RCK_1    GPIOA->BSRR=1<<3     //RCK端口  	     PA3
#define	OV7670_RCK_0    GPIOA->BRR=1<<3     //RCK端口  	     PA3

#define	OV7670_RRST_1    GPIOA->BSRR=1<<2     //RRST端口  	     PA2
#define	OV7670_RRST_0    GPIOA->BRR=1<<2     //RRST端口  	     PA2


															  					 
#define OV7670_DATA   GPIO_ReadInputData(GPIOA,0x00FF) 					//数据输入端口
//GPIOC->IDR&0x00FF 
/////////////////////////////////////////
#define CHANGE_REG_NUM 							171			//需要配置的寄存器总数		  
extern const u8 ov7670_init_reg_tbl[CHANGE_REG_NUM][2];		//寄存器及其配置表
	    				 
u8   OV7670_Init(void);		  	   		 
void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);
void EXTI2_Init(void);

#endif





















