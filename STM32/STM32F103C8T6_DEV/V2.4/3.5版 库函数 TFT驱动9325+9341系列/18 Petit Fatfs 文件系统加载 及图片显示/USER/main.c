

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32开发板 库函数部分	  */

/*
  STM32 紫电a  Petit Fatfs 文件系统的加载  并用加载的系统显示一张TF卡上指定的 图片数据
  显示的图片数据为 bin图片  相关的参考图片在资料里有  

  tf卡采用我们店TFT屏上的tf卡模块   
  tf卡模块 采用SPI1总线   CS片选IO为 PA4  

  TFT  驱动芯片为 ili9325	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位

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

#include  "pff.h"				  //文件系统调用.h加载


FATFS fatfs;	//文件系统结构体定义







u8 tbuf[512];			   //512字节 SD卡数据缓存空间


//显示BIN文件  bin文件大小为240x320
//path  bin文件名
//返回0 显示完成 1  读取失败
u8 play_bin(const char  *path)
{

FRESULT res; 
u16 br,i1;

	
res=pf_open(path);		             //打开指定路径文件	 这一步可以打开任何路径下的文件 注意它的功能就是打开文件，不是文件夹
                                     //读文件内数据的前提是必须要打开这个文件

if(res == FR_OK){

  Address_set(0,0,239,319,0,0);      // 先扫横行 在扫纵行	   要符合BIN 生成方式 否则产生乱码
 

  TFT_RS_1;		 //写数据线拉高		为提高写入速度
  while(1)
  {
     pf_read(tbuf, 512, &br);		//上面 res=pf_open(path);打开的是指定路径下的文件，这里就可以直接读取文件的数据
	                                //从初始位置读取512个字节到缓存区  再次读取无需偏移 自动跳到下512字节
									//pf_read的特点：不仅可以读取路径下的文件数据，而在你不改变路径的前提它会自动加地址读取下面的数据
									//从程序可以看出 程序在不停的循环pf_read(tbuf, 512, &br);函数来读取512个字节，
									//那么它内部的工作就是从给的路径开始读去512个字节然后自动指向加512字节的路径，读取下512个字节直到图片显示完成
	   
       for(i1=0;i1<256;i1++)                    //写到液晶屏，可以显示256个像素，每个像素16位即2个字节  也就是每两个字节能显示一个像素点 
	      {  									//512个字节/2  就是256个像素
		 					
  	       		  
//           Lcd_Write_Data((tbuf[i1*2+1]<<8)+(tbuf[i1*2]));


		    GPIOB->ODR=(tbuf[i1*2+1]<<8)+(tbuf[i1*2]);	  //写数据  因为高位在前面 所以前面的数要比后面的多1  void Lcd_Write_Data(u16 Data)函数的分解

		    TFT_WR_0;								      //开始写入
            TFT_WR_1;
				
            if(br==0){led(1);return 0;}   	 //没有数据 br将为0  这时跳出函数
	        

          }
	}

   }

 return 1;  	//说明读取数据出现问题
 }  	
 
 
 			

int main(void)
 {

	  u8 m;
	  delay_init();	    	 //延时函数初始化	 	  
	  LED_Init();		  	 //初始化与LED连接的硬件接口
	  KEY_Init();            //初始化按键	
	  SPI1_Init();			 //初始化SPI1总线
	  SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式		
	  Lcd_Init();			 //LCD  初始化
	  SPI_Flash_Init();  	 // FLASH 初始化
	  XPT2046_Init();		 //触摸芯片XPT2046 io配置
	  AT24CXX_Init();        //IIC初始化



	  TFT_CS(0);			 //打开LCD片选使能 
	  GUI_Clear(White);			  //白色清屏

								 //
	  pf_mount(&fatfs);	         //初始化petit FATFS文件系统  并提取tf卡相应数据
	                              
      play_bin("/4.bin");	  //显示指定路径下的bin文件	   
                              //这是要已知存入TF卡里的路径 “/4.bin”就是在TF卡根目录下文件名为4.bin文件
							  //比如文件在文件夹 测试文件夹下的4.bin 那么就要写"/测试/4.bin"


//	  if(SD_Init()==0)GUI_sprintf_hzstr16x(0,20,"TF Card  ok",Black,White);	  //初始化TF卡
//	  else GUI_sprintf_hzstr16x(0,20,"TF Card Error",Red,White);



	  number(20,200,m,Blue,White);


	  while(1);  

}
	    





