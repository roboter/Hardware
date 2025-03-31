

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*��ָ����������ʾһ��180*240 ��ͼƬ	����ԥ����ռ����� ���Բ���ȫ����ʾ��
  ������ �õ���TFT Ϊ ���ǵ�� 2.4��TFT  ����оƬΪ ili9325	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ
  �˺��� �üĴ�����ʽ����GPIO  ��TFT������ ������������õ��ǼĴ���  �����ܴ�����������ٶ�
*/



#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "picture.h"	   //Ϊ ���ɵ�ͼƬ����




int main(void)
 {
	 unsigned int i;
	  delay_init();	    	 //��ʱ������ʼ��	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�			
	  Lcd_Init();			 //LCD  ��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 

	  GUI_Clear(Green1);		//����
	
	  
	  Address_set(30,40,209,279,30,40);		   //������ʾ��Χ
	  for(i=0;i<43200;i++)				   //��ʾ�Դ�õ�ͼƬ����
	    {
		 Lcd_Write_Data((gImage_t[i*2+1]<<8)+(gImage_t[i*2]));
		}
	  
	  while(1);							   //������ͣ������


 }

