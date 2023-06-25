
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"



//����IO
//�ö�����ҪӦ���� ��ʾ  
//����IO����ʾ������ û���κ��������� ֱ�ӵ���IO��ײ�Ĵ�������
//�Դﵽ ��MCU������Χ�ڵ������ʾЧ��
#define	TFT_CS_1    GPIOC->BSRR=1<<8     //Ƭѡ�˿�  	     PC8
#define	TFT_RS_1	GPIOC->BSRR=1<<9     //����/����          PC9	   
#define	TFT_WR_1	GPIOC->BSRR=1<<10    //д����			 PC9
#define	TFT_RD_1	GPIOA->BSRR=1<<15    //������			 PA15
								    
#define	TFT_CS_0    GPIOC->BRR=1<<8      //Ƭѡ�˿�  	     PC8
#define	TFT_RS_0	GPIOC->BRR=1<<9      //����/����          PC9	   
#define	TFT_WR_0	GPIOC->BRR=1<<10     //д����			 PC10
#define	TFT_RD_0	GPIOA->BRR=1<<15     //������			 PA15



void TFT_CS(u8 d);

void Lcd_Init(void);


void Lcd_Write_Data(u16 data);								 //д16λ����

void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq);    //������ʾ��Χ

void Lcd_WriteReg(u16 com,u16 val);	

void Lcd_WR_Reg(u16 data);


void TFT_SCAN(u8 mode);//tft������ɨ�跽ʽ����


//��Ļ�ߴ�
#define TFT_XMAX       239
#define TFT_YMAX       319




#endif






