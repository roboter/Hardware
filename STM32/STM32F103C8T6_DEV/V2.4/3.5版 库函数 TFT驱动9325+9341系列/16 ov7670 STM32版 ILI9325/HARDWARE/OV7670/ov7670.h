	


#ifndef _OV7670_H
#define _OV7670_H
#include "stm32f10x.h"
#include "sccb.h"


#define OV7670_VSYNC  	PDin(2)			//ͬ���źż��IO
#define OV7670_WRST		PAout(0)		//дָ�븴λ
#define OV7670_WREN		PAout(8)		//д��FIFOʹ��
#define OV7670_RCK		PAout(3)		//������ʱ��
#define OV7670_RRST		PAout(2)  		//��ָ�븴λ
#define OV7670_CS		PAout(1)  		//Ƭѡ�ź�(OE)


//����RCK  RRST	  
//ȥ��������λ��Ч��  ʹIO�ĵ����ٶȴﵽ���
#define	OV7670_RCK_1    GPIOA->BSRR=1<<3     //RCK�˿�  	     PA3
#define	OV7670_RCK_0    GPIOA->BRR=1<<3     //RCK�˿�  	     PA3

#define	OV7670_RRST_1    GPIOA->BSRR=1<<2     //RRST�˿�  	     PA2
#define	OV7670_RRST_0    GPIOA->BRR=1<<2     //RRST�˿�  	     PA2


															  					 
#define OV7670_DATA   GPIO_ReadInputData(GPIOA,0x00FF) 					//��������˿�
//GPIOC->IDR&0x00FF 
/////////////////////////////////////////
#define CHANGE_REG_NUM 							171			//��Ҫ���õļĴ�������		  
extern const u8 ov7670_init_reg_tbl[CHANGE_REG_NUM][2];		//�Ĵ����������ñ�
	    				 
u8   OV7670_Init(void);		  	   		 
void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);
void EXTI2_Init(void);

#endif





















