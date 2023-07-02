#include "timer.h"
#include "led.h"

 u8  LED0;	 

//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M	����ʱ������ƵΪ72M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��2

// ���㹫ʽ��
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;				//��ʱ�����ýṹ�嶨��
	NVIC_InitTypeDef NVIC_InitStructure;						//�ж����ýṹ�嶨��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;  //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�	TIM_IT_Update

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2			 
}


//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );   //���TIM2�����жϱ�־ 
		LED0=!LED0;						 //0 1�䷭ת
		led(LED0);						 //LED��˸
		}
}












