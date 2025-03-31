

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*�˳��� Ϊ��ʾTFTˢ��ɫ����

  ������ �õ���TFT Ϊ ���ǵ�� 2.4��TFT  ����оƬ��֧��  ili9325   9328  9320  9341 	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ
  �˺��� �üĴ�����ʽ����GPIO  ��TFT������ ������������õ��ǼĴ���  �����ܴ�����������ٶ�

*/


#include  "delay.h"
#include  "led.h"
#include  "tft.h"



int main(void)
 {
	  delay_init();	    	 //��ʱ������ʼ��	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�			
	  Lcd_Init();			 //LCD  ��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 

   while(1)
   {	 	
	GUI_Clear(Red);
	led(1); //����LED
	delay_ms(300);
	GUI_Clear(Yellow);
	delay_ms(300);
	GUI_Clear(Green);
	delay_ms(300);
	GUI_Clear(Blue);
	led(0); //�ص�LED
	delay_ms(300);
	GUI_Clear(Black);
	delay_ms(300);
	GUI_Clear(window);
	delay_ms(300);

   }
 }

