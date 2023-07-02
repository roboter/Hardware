
/**********************************************************************************
 * ϵͳʱ��SysTick	 ���δ�ʱ��
 * ������ͨ��STM32�ġ������࡯��
 * ��汾  ��ST_v3.5
**********************************************************************************/

#define SysTick_CLKSource_HCLK_Div8 ((uint32_t)0xFFFFFFFB)
#include <delay.h>

static uint8_t fac_us = 0; // us��ʱ������
static uint16_t fac_ms = 0; // ms��ʱ������

void delay_init()	 
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8

	fac_ms = (uint16_t)fac_us * 1000; // ����ÿ��ms��Ҫ��systickʱ����
}


//��ʱnus
//nusΪҪ��ʱ��us��.
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   	   temp&0x01  0x01��ʾ�Ƿ�ʹ�� ��ֹ����ر�ʱ������ѭ��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
void delay_ms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD = (uint32_t)nms * fac_ms; // ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
} 

