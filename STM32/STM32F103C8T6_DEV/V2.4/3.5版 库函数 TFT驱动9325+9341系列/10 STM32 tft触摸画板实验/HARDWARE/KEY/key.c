

#include "key.h"




void KEY_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;	 //�ṹ�嶨��
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);	//����GPIOA GPIODʱ��
GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;								   //IO����ΪPD2
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;		   //���ó���������
GPIO_Init(GPIOD,&GPIO_InitStructure);	           //��ʼ��GPIOD2


//��ʼ�� WK_UP-->GPIOA.0	  ��������
GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}












