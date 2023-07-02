

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny

OV7670ģ�� STM32����

ѡ��STM32оƬ   
TFT����IC��֧�� 9325 9320 9328 ��9341

  ������ �õ���TFT Ϊ ���ǵ�� 2.4��TFT  ����оƬΪ R61505V	
  TFT�õ���GPIO  PBΪ���ݿ�	PC.6  CS   PC.7  RS	  PC.8  WR   PC.9  RD	PC.10 RES
  �˺��� �üĴ�����ʽ����GPIO  ��TFT������ ������������õ��ǼĴ���  �����ܴ�����������ٶ�
 
����ͷ����
����ͷ ���ݿ� ΪPA��  AO-A7
SCL    PC11
SDA    PC12
OE	   PC3		 //Ƭѡ�ź�(OE)
WRST   PC4		 //дָ�븴λ
RRST   PC2		 //��ָ�븴λ
RCLK   PC1		 //������ʱ��
WEN	   PC5		 //д��FIFOʹ��
VSY	   PD2  	 //ͬ���źż��IO

�����������̽���

��ʼ��TFT   
��ʼ��ov7670  ov7670��ͨ��SCCB ��ʼ����  �� SCL ��SDA�Ϳ��Գ�ʼ��OV7670  SDA SCL������I2CЧ��
              �����ڵ�ģ��ǰ һ��Ҫȷ��OV7670�Ƿ��Ѿ���ʼ��
�����ж� �ж�֡�����Ƿ����
��ѭ�� ��ȡ����ʾ ��������

	   
*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "led.h"
#include "ov7670.h"
#include  "gui.h"




extern u8 ov_sta;	//֡���� ��λ��־λ


//����LCD��ʾ
void camera_refresh(void)
{
	u32 j;
 	u16 color;
		 
	if(ov_sta==2)				//�жϻ������Ƿ�����������
	{
	  	 
		OV7670_RRST_0;				//��ʼ��λ��ָ�� 
		OV7670_RCK_0;
		OV7670_RCK_1;
		OV7670_RCK_0;		
		OV7670_RRST_1;				//��λ��ָ����� 
		OV7670_RCK_1;  


		TFT_RS_1;		 //д����������		Ϊ���д���ٶ�

		//���÷� �ǽ� ����д���ݵĲ�����ȫ��  ��Ҫ��Ϊ�������ʾ�ٶ�  ������ע�Ͳ���Ϊ�ο����֣�
                     
		for(j=0;j<76800;j++)			   //�ֱ���Ϊ240x320   ÿ����ɫ��Ҫ�����ֽ� ���� 240x320x2=76800  ��
		{
		  	

			OV7670_RCK_0;				 //ÿһ��ʱ������ ��һ������
			color=GPIOC->IDR&0XFF;	//������   ��ȡ��ɫ���ֽ�����
			OV7670_RCK_1; 
			color<<=8;  				 //����8λ  �����ֽ��Ƶ���8λ  Ϊ���յ�8λ�ֽ���׼��
			OV7670_RCK_0;
			color|=GPIOC->IDR&0XFF;	//������   ��ȡ��ɫ���ֽ����� ��ת��Ϊ16λ 565 ��ɫ����
			OV7670_RCK_1; 

  		 // TFT_DATA(color);  //��ֵ

		    GPIOB->ODR=color;			   //��TFT���ڿ���д����

//		     GPIOB->BRR=GPIO_Pin_All;	   //��Ĵ�������
//             GPIOB->BSRR=color;			   //���ɼ�����ɫֵ��PB�ڼĴ��� 

		    TFT_WR_0;								      //��ʼд��
            TFT_WR_1;
		 // Lcd_Write_Data(color);

		}   							 
		EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE8�ϵ��жϱ�־λ
		ov_sta=0;					//��ʼ��һ�βɼ�
	} 
}



int main(void)
 {
 u8 lightmode=0,saturation=2,brightness=2,contrast=2;
 u8 effect=0;

	  delay_init();	    	 //��ʱ������ʼ��
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�			
	  Lcd_Init();			 //LCD  ��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
      GUI_Clear(White);		//����

	  	while(OV7670_Init())//��ʼ��OV7670
	{
		GUI_sprintf_hzstr16x(20,150,"OV7670 Error!!",Blue,White);
		delay_ms(200);
	    GUI_sprintf_hzstr16x(20,150,"              ",Blue,White);
		delay_ms(200);
	}

	  GUI_Clear(Red);		//����		��ʼ���ɹ��� ��ɫ����


//	 delay_ms(1500);

	 
	 //����ͷ ��������  ���κ�ΪĬ��Ч��	 	   
	OV7670_Light_Mode(lightmode);
	OV7670_Color_Saturation(saturation);
	OV7670_Brightness(brightness);
	OV7670_Contrast(contrast);
 	OV7670_Special_Effects(effect);	 

	EXTI2_Init();					   //��ʼ���ж���
	OV7670_Window_Set(10,174,240,320);	//���ô���
	OV7670_CS=0;					   //ʹ������ͷƬѡ

	 TFT_SCAN(5);   //����TFTɨ�跽�� Ϊ���µ��� ���ҵ���
	 //����˵��һ��  ����ͷ�ĳ���ɨ���� ���ϵ��� ������

	                                         //���������÷��� ����Ҫ���ֲ�

	 Address_set(0,0,239,319,0,0);		   //9325 ������ʾ��Χ		ȫ����ʾ


//	 Address_set(0,0,319,239,0,0);		   //9341 ����ɨ�跽��ı� 9341��ԭ��Ҳ��� ���Ժ�����93ϵ�в�һ��

	  while(1)							   //��ѭ����ʾ ��������
	  {
	  camera_refresh();
	  }

						 

 }

