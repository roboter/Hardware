

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
  STM32 �ϵ�a  Petit Fatfs �ļ�ϵͳ�ļ���  
  �����ļ�ϵͳ�������VS1053���ŵ�������

  tf���������ǵ�TFT���ϵ�tf��ģ��   
  tf��ģ�� ����SPI1����   CSƬѡIOΪ PA4  

  TFT  ����оƬΪ ili9325	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ
    
  VS1053 ����SPI1 ���� 
  VS_DQ       PA3  	//DREQ 
  VS_RST      PA2 	//RST
  VS_XCS      PA1  	//XCS
  VS_XDCS     PA0 	//XDCS  

  ������Ҫ���̣�
  �����ļ�ϵͳ  ��ʼ��VS1053ģ��  ��ȡTF���������ļ����� ͨ��VS1053ģ�鲥��


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

#include  "vs1053.h"
#include  "mp3player.h"

#include  "pff.h"				  //�ļ�ϵͳ����.h����


FATFS fatfs;	//�ļ�ϵͳ�ṹ�嶨��







u8 tbuf[512];			   //512�ֽ� SD�����ݻ���ռ�


 
 			

int main(void)
 {
// FRESULT res;
// u16 br;
// u32 cnt=0;					  //���ֽ��ȵ�������
// u8 mp3in;

	  delay_init();	    	 //��ʱ������ʼ��	 	  
	 // LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	  //KEY_Init();            //��ʼ������	
	  SPI1_Init();			 //��ʼ��SPI1����
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_8);//����Ϊ18Mʱ��,����ģʽ		
	  Lcd_Init();			 //LCD  ��ʼ��
	 // SPI_Flash_Init();  	 // FLASH ��ʼ��
	  XPT2046_Init();		 //����оƬXPT2046 io����
	  //AT24CXX_Init();        //IIC��ʼ��

	  VS1053_Init();



	  TFT_CS(0);			     //��LCDƬѡʹ�� 
							
	  pf_mount(&fatfs);	         //��ʼ��petit FATFS�ļ�ϵͳ  ����ȡtf����Ӧ����
	                     
						 
						          

  GUI_Clear(window);			  //��ɫ���� 
  GUI_box(0,0,239,20,Blue);
  GUI_sprintf_hzstr16x(0,2,"Music Player",White,Blue);

  GUI_box(fft_col_x,125,206,125,Blue);	  //Ƶ��������

  GUI_box(0,132,239,319,Black);	  //�����°벿

  GUI_box(2,140,237,151,White);	  //������������ʼ��
  GUI_box(4,142,235,149,Black);

  GUI_sprintf_hzstr16x(6,153,"--:--/--:--",Yellow,Black);	//��ʾʱ���ֵ

  GUI_sprintf_hzstr16x(6,178,"vol:",Gray,Black);			//������ʼ����
  GUI_arcrectangle(38,183,150,10,3,Gray,Gray);
  GUI_sprintf_hzstr16x(56,194,"/48",Gray,Black);			//���������������ֵΪ48
  GUI_arcrectangle(40,185,(Int_vol*146)/254,6,2,Cyan,Cyan);	  //��ʾ������������ֵ 146 ���������� 254 �������ֵ
  number10(40,194,(Int_vol*48)/254,Gray,Black);	        //��ʾ������ֵ

  GUI_box(0,268,239,269,Red);	  //������
  mp3_button(1,1);
  mp3_button(2,1);
  mp3_button(3,1);
  mp3_button(4,1);

  Mp3Player_Init(); 			  //vs1053 ��ʼ��

  play_mp3();					  //���������� ����ʼ����
  while(1);

//      GUI_Clear(White);			  //��ɫ���� 
//
//
//      GUI_sprintf_hzstr16x(0,0,"VS1053--TEST",Black,White);
//
//	  //MP3��ʼ��
//      mp3in=Mp3Player_Init(); 
//      if(mp3in==1)GUI_sprintf_hzstr16x(0,30,"MP3 Init OK",Red,White);
//      else 
//      {
//        GUI_sprintf_hzstr16x(0,30,"MP3 Init Error",Red,White);
//	    while(1);	 //�����ʼ�������� ��˵��ģ����������� ���Ӵ���
//	  }
//
//      res=pf_open("/music/ͯ��.mp3");			//��ָ��·���µ������ļ���
//
//      if(res == FR_OK)GUI_sprintf_hzstr16x(0,80,"The music is already open!",Blue,White);
//
//
//      VS_Restart_Play();  					    // �������� 
//      VS_Set_All();        					    // ������������Ϣ 			 
//      VS_Reset_DecodeTime();					// ��λ����ʱ�� 
//      VS_Set_Vol(200);                          // ��������
//      VS_SPI_SpeedHigh();	                    // SPI����Ϊ����
//
//      // SetBands(); 							// Ƶ�ײ�����ʼ��
//
//      GUI_sprintf_hzstr16x(0,110,"Play music...",Blue,White);
//
//
//      while(1)
//      {
//	    res=pf_read(tbuf,512,&br);				//ͨ���ļ�ϵͳ��ȡָ���ļ����µ�һ��������
//
//	    if((res!=FR_OK))
//	    {
//         while(1);
//	     }
//        cnt=0;
//
//	    do{
//	   	  if(VS_Send_MusicData(tbuf+cnt)==0)	  //һ����32���ֽ���������
//		  {
//		   cnt+=32;	
//		  }
//
//	      }while(cnt<512);
//
//        if(br!=512)           // br���� ˵���Ѿ����ļ���β
//        {
//         while(1);
//        }
//
//      }


}
	    





