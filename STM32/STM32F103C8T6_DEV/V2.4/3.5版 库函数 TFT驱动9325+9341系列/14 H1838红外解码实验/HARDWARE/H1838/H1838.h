
#ifndef _H1838_H
#define _H1838_H  
#include "stm32f10x.h"
#include "delay.h"
  
#define RDATA PAin(3)	 //�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;	//�������µĴ���

void Remote_Init(void);    //���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);	     


void TIM2_Int_Init(u16 arr,u16 psc);
#endif







