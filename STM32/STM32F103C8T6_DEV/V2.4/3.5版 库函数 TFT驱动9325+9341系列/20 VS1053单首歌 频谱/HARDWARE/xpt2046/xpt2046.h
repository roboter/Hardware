 
 
#ifndef XPT2046_H
#define XPT2046_H






#define	xpt2046_CS_0  GPIO_ResetBits(GPIOA,GPIO_Pin_11)		   //Ƭѡ
#define xpt2046_CS_1    GPIO_SetBits(GPIOA,GPIO_Pin_11)

#define xpt2046_isClick  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)		 //�жϴ������Ƿ��£�����ֵ����1ʱ����


struct TFT_Pointer			  //�������������Ľṹ�庯��  ��ҪӦ���� �Բɼ���ADֵ X Y  ���Ƿ��д������������ı�־λflag
{
 u16 x;
 u16 y;
 u8 flag;
};


void XPT2046_Init(void);             //xpt2046 IO�ڳ�ʼ��

struct TFT_Pointer TFT_Cm(void);     //TFT ����������

#endif
