

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32������ �⺯������	  */

/*
  STM32 �ϵ�a  Petit Fatfs �ļ�ϵͳ�ļ���  ���ü��ص�ϵͳ��ʾһ��TF����ָ���� ͼƬ����
  ��ʾ��ͼƬ����Ϊ binͼƬ  ��صĲο�ͼƬ����������  

  tf���������ǵ�TFT���ϵ�tf��ģ��   
  tf��ģ�� ����SPI1����   CSƬѡIOΪ PA4  

  TFT  ����оƬΪ ili9325	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ

*/

#include  "stm32f10x.h"
#include  "delay.h"
#include  "led.h"
#include  "spi.h"
#include  "tft.h"
#include  "key.h"
#include  "flash.h"
#include  "gui.h"
#include  "z24c02.h"
#include  "xpt2046.h"
#include  "sd.h"

#include  "pff.h"				  //�ļ�ϵͳ����.h����


FATFS fatfs;	//�ļ�ϵͳ�ṹ�嶨��







u8 tbuf[512];			   //512�ֽ� SD�����ݻ���ռ�


//��ʾBIN�ļ�  bin�ļ���СΪ240x320
//path  bin�ļ���
//����0 ��ʾ��� 1  ��ȡʧ��
u8 play_bin(const char  *path)
{

FRESULT res; 
u16 br,i1;

	
res=pf_open(path);		             //��ָ��·���ļ�	 ��һ�����Դ��κ�·���µ��ļ� ע�����Ĺ��ܾ��Ǵ��ļ��������ļ���
                                     //���ļ������ݵ�ǰ���Ǳ���Ҫ������ļ�

if(res == FR_OK){

  Address_set(0,0,239,319,0,0);      // ��ɨ���� ��ɨ����	   Ҫ����BIN ���ɷ�ʽ �����������
 

  TFT_RS_1;		 //д����������		Ϊ���д���ٶ�
  while(1)
  {
     pf_read(tbuf, 512, &br);		//���� res=pf_open(path);�򿪵���ָ��·���µ��ļ�������Ϳ���ֱ�Ӷ�ȡ�ļ�������
	                                //�ӳ�ʼλ�ö�ȡ512���ֽڵ�������  �ٴζ�ȡ����ƫ�� �Զ�������512�ֽ�
									//pf_read���ص㣺�������Զ�ȡ·���µ��ļ����ݣ������㲻�ı�·����ǰ�������Զ��ӵ�ַ��ȡ���������
									//�ӳ�����Կ��� �����ڲ�ͣ��ѭ��pf_read(tbuf, 512, &br);��������ȡ512���ֽڣ�
									//��ô���ڲ��Ĺ������ǴӸ���·����ʼ��ȥ512���ֽ�Ȼ���Զ�ָ���512�ֽڵ�·������ȡ��512���ֽ�ֱ��ͼƬ��ʾ���
	   
       for(i1=0;i1<256;i1++)                    //д��Һ������������ʾ256�����أ�ÿ������16λ��2���ֽ�  Ҳ����ÿ�����ֽ�����ʾһ�����ص� 
	      {  									//512���ֽ�/2  ����256������
		 					
  	       		  
//           Lcd_Write_Data((tbuf[i1*2+1]<<8)+(tbuf[i1*2]));


		    GPIOB->ODR=(tbuf[i1*2+1]<<8)+(tbuf[i1*2]);	  //д����  ��Ϊ��λ��ǰ�� ����ǰ�����Ҫ�Ⱥ���Ķ�1  void Lcd_Write_Data(u16 Data)�����ķֽ�

		    TFT_WR_0;								      //��ʼд��
            TFT_WR_1;
				
            if(br==0){led(1);return 0;}   	 //û������ br��Ϊ0  ��ʱ��������
	        

          }
	}

   }

 return 1;  	//˵����ȡ���ݳ�������
 }  	
 
 
 			

int main(void)
 {

	  u8 m;
	  delay_init();	    	 //��ʱ������ʼ��	 	  
	  LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  KEY_Init();            //��ʼ������	
	  SPI1_Init();			 //��ʼ��SPI1����
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ		
	  Lcd_Init();			 //LCD  ��ʼ��
	  SPI_Flash_Init();  	 // FLASH ��ʼ��
	  XPT2046_Init();		 //����оƬXPT2046 io����
	  AT24CXX_Init();        //IIC��ʼ��



	  TFT_CS(0);			 //��LCDƬѡʹ�� 
	  GUI_Clear(White);			  //��ɫ����

								 //
	  pf_mount(&fatfs);	         //��ʼ��petit FATFS�ļ�ϵͳ  ����ȡtf����Ӧ����
	                              
      play_bin("/4.bin");	  //��ʾָ��·���µ�bin�ļ�	   
                              //����Ҫ��֪����TF�����·�� ��/4.bin��������TF����Ŀ¼���ļ���Ϊ4.bin�ļ�
							  //�����ļ����ļ��� �����ļ����µ�4.bin ��ô��Ҫд"/����/4.bin"


//	  if(SD_Init()==0)GUI_sprintf_hzstr16x(0,20,"TF Card  ok",Black,White);	  //��ʼ��TF��
//	  else GUI_sprintf_hzstr16x(0,20,"TF Card Error",Red,White);



	  number(20,200,m,Blue,White);


	  while(1);  

}
	    





