

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32F103RBT6 ������ �⺯������	  */

/*SPIʵ��  ��ʵ����Ҫ ����Ƭ��SPI���ܵײ㺯��  ���ÿ⺯����SPI������Ӧ����
  ��� ����� ������ flashоƬ ���� W25X16�ȣ� �Ϳ���ͨ���˳���  ���� ��flash��д��Ӧ����
  �������ݶ�ȡ ��ʾ��TFT��

  ����ǵ�һ�����ش˳��� Ҫ�Ȱ�S3 �������������ݵ�FLASH�洢  Ȼ���ڰ�S4 ��ȡ�����ȥ������

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"



const u8 TEXT_Buffer[]={"STM32-ZD SPI1 FLASH IS OK"};
#define SIZE sizeof(TEXT_Buffer)

//u8 scan[]={"STM32-ZD SPI1 FLASH IS OK"};	 //�����ַ���
//u8 buffer[25];						 //��������

int main(void)
 {
 

	 u8 datatemp[SIZE];

	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������			
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 //SPI FLASH ��ʼ��
	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);		//����


	 while(SPI_Flash_ReadID()!=W25Q16)							//��ⲻ��W25Q64
	  {
		GUI_sprintf_hzstr16x(20,150,"25X16 Check Failed!",Blue,White);
		delay_ms(500);
		GUI_sprintf_hzstr16x(20,180,"Please Check!      ",Blue,White);
		delay_ms(500);
	  }

	 GUI_sprintf_hzstr16x(60,20,"SPI-25X16 TEST",White,Red);

	 GUI_sprintf_hzstr16x(50,60,"S3 for save DATA",Black,White);
	 GUI_sprintf_hzstr16x(50,80,"S4 for read DATA",Black,White);

	 while(1)
	 {
		if(KEY1==0)																   //PA0 
		 {
		 delay_ms(150);	//ȥ��
		 if(KEY1==0)
		  {
			 GUI_Clear(White);		//����
			 GUI_sprintf_hzstr16x(20,60,"Start Write W25X16....",Blue,White);
			 SPI_Flash_Write((u8*)TEXT_Buffer,100,SIZE);						//��flashд �Ѿ�׼���õ�����
			 GUI_sprintf_hzstr16x(20,60,"W25X16 Write Finished!",Blue,White);
		  }
		 }

		if(KEY0==1)																  //PD2
		{
		 delay_ms(150);	//ȥ��
		 if(KEY0==1)
		  {
		     GUI_Clear(White);		//����
			 GUI_sprintf_hzstr16x(20,60,"Start Read W25X16.... ",Red,White);
			 SPI_Flash_Read(datatemp,100,SIZE);								//��ȡ ������flash�������
			 GUI_sprintf_hzstr16x(20,60,"The Data Readed Is:  ",Red,White);
			 GUI_sprintf_hzstr16x(10,76,datatemp,Blue,White);					//��������ʾ����		  		  
		  }

		 }
	 }							  


 }





