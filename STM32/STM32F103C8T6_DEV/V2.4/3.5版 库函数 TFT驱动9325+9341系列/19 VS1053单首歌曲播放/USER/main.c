

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
  STM32 紫电a  Petit Fatfs 文件系统的加载  
  利用文件系统函数结合VS1053播放单首音乐

  tf卡采用我们店TFT屏上的tf卡模块   
  tf卡模块 采用SPI1总线   CS片选IO为 PA4  

  TFT  驱动芯片为 ili9325	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位
    
  VS1053 采用SPI1 总线 
  VS_DQ       PA3  	//DREQ 
  VS_RST      PA2 	//RST
  VS_XCS      PA1  	//XCS
  VS_XDCS     PA0 	//XDCS  

  程序主要流程：
  配置文件系统  初始化VS1053模块  读取TF卡上音乐文件数据 通过VS1053模块播放


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

#include  "pff.h"				  //文件系统调用.h加载


FATFS fatfs;	//文件系统结构体定义







u8 tbuf[512];			   //512字节 SD卡数据缓存空间


 
 			

int main(void)
 {
 FRESULT res;
 u16 br;
 u32 cnt=0;					  //音乐进度递增变量
 u8 mp3in;

	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键	
	  SPI1_Init();			 //初始化SPI1总线
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式		
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 // FLASH 初始化
	  XPT2046_Init();		 //触摸芯片XPT2046 io配置
	  AT24CXX_Init();        //IIC初始化

	  VS1053_Init();



	  TFT_CS(0);			     //打开LCD片选使能 
							
	  pf_mount(&fatfs);	         //初始化petit FATFS文件系统  并提取tf卡相应数据
	                              

      GUI_Clear(White);			  //白色清屏 


      GUI_sprintf_hzstr16x(0,0,"VS1053--TEST",Black,White);

	  //MP3初始化
      mp3in=Mp3Player_Init(); 
      if(mp3in==1)GUI_sprintf_hzstr16x(0,30,"MP3 Init OK",Red,White);
      else 
      {
        GUI_sprintf_hzstr16x(0,30,"MP3 Init Error",Red,White);
	    while(1);	 //如果初始化出问题 则说明模块访问有问题 检查接触口
	  }

      res=pf_open("/music/童话.mp3");			//打开指定路径下的音乐文件名

      if(res == FR_OK)GUI_sprintf_hzstr16x(0,80,"The music is already open!",Blue,White);


      VS_Restart_Play();  					    // 重启播放 
      VS_Set_All();        					    // 设置音量等信息 			 
      VS_Reset_DecodeTime();					// 复位解码时间 
      VS_Set_Vol(200);                          // 设置音量
      VS_SPI_SpeedHigh();	                    // SPI设置为高速

      // SetBands(); 							// 频谱补丁初始化

      GUI_sprintf_hzstr16x(0,110,"Play music...",Blue,White);


      while(1)
      {
	    res=pf_read(tbuf,512,&br);				//通过文件系统读取指定文件夹下的一音乐数据

	    if((res!=FR_OK))
	    {
         while(1);
	     }
        cnt=0;

	    do{
	   	  if(VS_Send_MusicData(tbuf+cnt)==0)	  //一次送32个字节音乐数据
		  {
		   cnt+=32;	
		  }

	      }while(cnt<512);

        if(br!=512)           // br不足 说明已经到文件结尾
        {
         while(1);
        }

      }


}
	    





