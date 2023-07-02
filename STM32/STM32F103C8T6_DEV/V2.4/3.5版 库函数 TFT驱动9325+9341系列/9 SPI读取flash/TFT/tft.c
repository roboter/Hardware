

#include "tft.h"
#include "delay.h"




u16 lcd_id;

//#define DATAIN     GPIOB->IDR;   //数据输入

//	   用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位
//
//

//tft  io口 配置
void Lcd_GPIO_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;					 //定义GPIO结构体


 //PB 0-15做为数据口 所以要关掉 PB上的JTAG仿真 	只开启SWJ仿真
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  //启动AFIO时钟
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //配置JTAG-DP Disabled and SW-DP Enabled 
 
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	//使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;			 //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);				

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
 GPIO_Init(GPIOC, &GPIO_InitStructure);


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
 GPIO_Init(GPIOA, &GPIO_InitStructure);

}


//库函数方法
//库函数在调用上 相对寄存器要慢很多 

////引脚定义
//void ILI9325_RS(unsigned int d)		   //命令/数据,0=命令,1=数据
//{
// if(d==1)
// GPIO_SetBits(GPIOC,GPIO_Pin_7);// GPIOC->BSRR|=pin7;
// else if(d==0)
//  GPIO_ResetBits(GPIOC,GPIO_Pin_7); //GPIOC->BRR|=pin7;
//} 
//
//void ILI9325_WR(unsigned int d)		   //写数据
//{
// if(d==1)
// GPIO_SetBits(GPIOC,GPIO_Pin_8);// GPIOC->BSRR|=pin8;
// else if(d==0)
//  GPIO_ResetBits(GPIOC,GPIO_Pin_8);//GPIOC->BRR|=pin8;
//}                  
//
//void ILI9325_RD(unsigned int d)		   //读数据
//{									   
// if(d==1)
// GPIO_SetBits(GPIOC,GPIO_Pin_9);// GPIOC->BSRR|=pin9;
// else if(d==0)
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);//GPIOC->BRR|=pin9;
//}                    
//void ILI9325_CS(unsigned int d)		   //片选
//{
// if(d==1)
//  GPIO_SetBits(GPIOC,GPIO_Pin_6);//GPIOC->BSRR|=pin6;
// else if(d==0)
//  GPIO_ResetBits(GPIOC,GPIO_Pin_6);//GPIOC->BRR|=pin6;
//}                 
//void ILI9325_RST(unsigned int d)	   //复位
//{
// if(d==1)
// GPIO_SetBits(GPIOC,GPIO_Pin_10);// GPIOC->BSRR|=pin10;
// else if(d==0)
// GPIO_ResetBits(GPIOC,GPIO_Pin_10);// GPIOC->BRR|=pin10;
//}                   
//void ILI9325_DATA(unsigned int data)   //数据接PD口
//{
//   GPIO_ResetBits(GPIOB,GPIO_Pin_All);//GPIOB->BRR=0xffff;
//   GPIO_SetBits(GPIOB,data);//GPIOB->BSRR=data;
//}  












//寄存器方法

//引脚定义
void TFT_RS(u8 d)		   //命令/数据,0=命令,1=数据
{
 if(d==1)
  GPIOC->BSRR|=GPIO_Pin_9;
 else if(d==0)
  GPIOC->BRR|=GPIO_Pin_9;
}     
          					   
void TFT_WR(u8 d)		   //写数据
{
 if(d==1)
  GPIOC->BSRR|=GPIO_Pin_10;
 else if(d==0)
  GPIOC->BRR|=GPIO_Pin_10;
}                  
void TFT_RD(u8 d)		   //读数据
{									   
 if(d==1)
  GPIOA->BSRR|=GPIO_Pin_15;
 else if(d==0)
  GPIOA->BRR|=GPIO_Pin_15;
}                    
void TFT_CS(u8 d)		   //片选
{
 if(d==1)
  GPIOC->BSRR|=GPIO_Pin_8;
 else if(d==0)
  GPIOC->BRR|=GPIO_Pin_8;
}                 
//void TFT_RES(unsigned int d)	   //复位
//{
// if(d==1)
//  GPIOC->BSRR|=GPIO_Pin_10;
// else if(d==0)
//  GPIOC->BRR|=GPIO_Pin_10;
//}                   
void TFT_DATA(u16 data)   //数据接PD口
{
  GPIOB->BRR=GPIO_Pin_All;
  GPIOB->BSRR=data;
}                          



//显示位置寄存器定义
// 0x0050   //X轴起始位置
// 0x0051   //X轴结束位置
// 0x0052   //Y轴起始位置
// 0x0053   //Y轴结束位置
// 0x0020   //当前坐标X轴位置
// 0x0021   //当前坐标Y轴位置



//写命令
void Lcd_WR_Reg(u16 data)
{
 TFT_RS(0);       //选择命令
 TFT_DATA(data);  //赋值
 TFT_WR(0);
 TFT_WR(1);       //写入拉高电平
}

//写数据
void Lcd_Write_Data(u16 data)
{
 TFT_RS(1);       //选择数据
 TFT_DATA(data);  //赋值
 TFT_WR(0);
 TFT_WR(1);       //写入拉高电平
}

//在某一个地址或者寄存器里写入一个16位值
void Lcd_WriteReg(u16 com,u16 val)	
{
 Lcd_WR_Reg(com);
 Lcd_Write_Data(val);
}





//读取 lcd内部指定寄存器数据
//输入 LCD_Reg lcd寄存器名称
//输出 对应LCD寄存器名称下 数据  
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	u16 t;

	Lcd_WR_Reg(LCD_Reg);  //写入要读的寄存器号  
	GPIOB->CRL=0X88888888; //PB0-7  上拉输入
	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
	GPIOB->ODR=0XFFFF;    //全部输出高

	TFT_RS(1);
	//读取数据(读寄存器时,并不需要读2次)
	TFT_RD(0);
	delay_us(5);//FOR 8989,延时5us					   
	TFT_RD(1);
	t=GPIOB->IDR;  


	GPIOB->CRL=0X33333333; //PB0-7  上拉输出
	GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    //全部输出高
	return t;  
}








//设置坐标范围		
//x1 y1  初始位置
//x2 y2  结束位置
//xq yq  起始点坐标	 (9341不需要这个值 随便输入个0即可)
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2,u16 xq,u16 yq)
{
  if(lcd_id==9325)
  {
	Lcd_WR_Reg(0x0050);Lcd_Write_Data(x1);		//设置要显示的区域
	Lcd_WR_Reg(0x0051);Lcd_Write_Data(x2);
	Lcd_WR_Reg(0x0052);Lcd_Write_Data(y1);
	Lcd_WR_Reg(0x0053);Lcd_Write_Data(y2);  
    Lcd_WR_Reg(0x0020);Lcd_Write_Data(xq);	  	//设置显示的初始位置
    Lcd_WR_Reg(0x0021);Lcd_Write_Data(yq); 
    Lcd_WR_Reg(0x0022);							//发送命令
  } 
  else if(lcd_id==9341)
  {
		Lcd_WR_Reg(0X2A); 
		Lcd_Write_Data(x1>>8); 
		Lcd_Write_Data(x1&0XFF);
		Lcd_Write_Data(x2>>8); 
		Lcd_Write_Data(x2&0XFF);

		Lcd_WR_Reg(0X2B); 
		Lcd_Write_Data(y1>>8); 
		Lcd_Write_Data(y1&0XFF);
		Lcd_Write_Data(y2>>8); 
		Lcd_Write_Data(y2&0XFF);
	   Lcd_WR_Reg(0X2C);      //开始写入GRAM
   }
}
















//TFT初始化
void Lcd_Init(void)
{
 Lcd_GPIO_Init();	//LCD 所用GPIO口配置

 //TFT_RES(1);
 //delay_ms(5);	
 //TFT_RES(0);
 //delay_ms(5) ;
 //TFT_RES(1);

 TFT_CS(1);
 TFT_RD(1);
 TFT_WR(1);
 delay_ms(5) ;
 TFT_CS(0);


	delay_ms(50); // delay 50 ms 
	Lcd_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
	lcd_id = LCD_ReadReg(0x0000); 		 //读取 lcd id数据 判断lcd型号

	if(lcd_id==0x9325||lcd_id==0x9328||lcd_id==0x933d||lcd_id==0x9320)//以上均为ILI9325类似系列 可用同一驱动
	{	 
	    lcd_id=9325;
		   
	    Lcd_WriteReg(0x0001,0x0100);	//Driver Output Contral.	
	    Lcd_WriteReg(0x0002,0x0700);	//LCD Driver Waveform Contral.
		Lcd_WriteReg(0x0003,0x1030);	//LCD显示方向设置   手册56页
		Lcd_WriteReg(0x0004,0x0000);	//Scalling Contral.			
		Lcd_WriteReg(0x0008,0x0202);	//Display Contral 2.(0x0207)		
		Lcd_WriteReg(0x0009,0x0000);	//Display Contral 3.(0x0000)
		Lcd_WriteReg(0x000A,0x0000);	//Frame Cycle Contal.(0x0000)
		Lcd_WriteReg(0x000C,0x0000);	
		Lcd_WriteReg(0x000D,0x0000);	//Frame Maker Position.
		Lcd_WriteReg(0x000F,0x0000);	//Extern Display Interface Contral 2.
	
		Lcd_WriteReg(0x0010,0x0000);	
		Lcd_WriteReg(0x0011,0x0007);								//Power Control 2.(0x0001)				    //Power Control 3.(0x0138)
		Lcd_WriteReg(0x0012,0x0000);	
		Lcd_WriteReg(0x0013,0x0000);								//Power Control 4.
		Lcd_WriteReg(0x0007,0x0001);								//Power Control 7.
		delay_ms(50);
	
	    Lcd_WriteReg(0x0010,0x1690);
		Lcd_WriteReg(0x0011,0x0227);
		delay_ms(50);
		Lcd_WriteReg(0x0012,0x009D);
		delay_ms(50);
		Lcd_WriteReg(0x0013,0x1900);	
		delay_ms(50);
		Lcd_WriteReg(0x0029,0x0025);	
		Lcd_WriteReg(0x002B,0x000D);
		delay_ms(50);
		Lcd_WriteReg(0x0020,0x0000);	//行地址设置 x
		Lcd_WriteReg(0x0021,0x0000);	//列地址设置 y
		delay_ms(50);
		Lcd_WriteReg(0x0030,0x0007);	
		Lcd_WriteReg(0x0031,0x0303);	
		Lcd_WriteReg(0x0032,0x0003);	
		Lcd_WriteReg(0x0035,0x0206);	
		Lcd_WriteReg(0x0036,0x0008);	
		Lcd_WriteReg(0x0037,0x0406);	
		Lcd_WriteReg(0x0038,0x0304);
		Lcd_WriteReg(0x0039,0x0007);	
		Lcd_WriteReg(0x003C,0x0601);	
		Lcd_WriteReg(0x003D,0x0008);			
						
		Lcd_WriteReg(0x0050,0x0000);	//行起始地址		  初始化设置屏幕显示范围为240x320
		Lcd_WriteReg(0x0051,0x00EF);	//行结束地址
		Lcd_WriteReg(0x0052,0x0000);	//列起始地址
		Lcd_WriteReg(0x0053,0x013F);	//列结束地址
		Lcd_WriteReg(0x0060,0xA700);	
		Lcd_WriteReg(0x0061,0x0001);	
		Lcd_WriteReg(0x006A,0x0000);	
		
		Lcd_WriteReg(0x0080,0x0000);	//Display Position? Partial Display 1.
		Lcd_WriteReg(0x0081,0x0000);	//RAM Address Start? Partial Display 1.
		Lcd_WriteReg(0x0082,0x0000);	//RAM Address End-Partial Display 1.
		Lcd_WriteReg(0x0083,0x0000);	//Displsy Position? Partial Display 2.
		Lcd_WriteReg(0x0084,0x0000);	//RAM Address Start? Partial Display 2.
		Lcd_WriteReg(0x0085,0x0000);	//RAM Address End? Partial Display 2.
	
		Lcd_WriteReg(0x0090,0x0010);	
		Lcd_WriteReg(0x0092,0x0600);	//Panel Interface Contral 2.(0x0000)
	
		Lcd_WriteReg(0x0007,0x0133);	//D1=D0=BASEE=1 开图像显示   GON=DTE=1   正常显示  用该命令设置显示器开关 以达到降低功耗效果
	       
	    Lcd_WR_Reg(0x0022);

	}
	else   //9341驱动		9341主要特点在于 改变扫描方向后 初始原点也随之改变 其他lcd做不到
	{
	    lcd_id=9341;

		Lcd_WR_Reg(0xCF);  
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0xC1); 
		Lcd_Write_Data(0X30); 
		Lcd_WR_Reg(0xED);  
		Lcd_Write_Data(0x64); 
		Lcd_Write_Data(0x03); 
		Lcd_Write_Data(0X12); 
		Lcd_Write_Data(0X81); 
		Lcd_WR_Reg(0xE8);  
		Lcd_Write_Data(0x85); 
		Lcd_Write_Data(0x10); 
		Lcd_Write_Data(0x7A); 
		Lcd_WR_Reg(0xCB);  
		Lcd_Write_Data(0x39); 
		Lcd_Write_Data(0x2C); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x34); 
		Lcd_Write_Data(0x02); 
		Lcd_WR_Reg(0xF7);  
		Lcd_Write_Data(0x20); 
		Lcd_WR_Reg(0xEA);  
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_WR_Reg(0xC0);    //Power control 
		Lcd_Write_Data(0x1B);   //VRH[5:0] 
		Lcd_WR_Reg(0xC1);    //Power control 
		Lcd_Write_Data(0x01);   //SAP[2:0];BT[3:0] 
		Lcd_WR_Reg(0xC5);    //VCM control 
		Lcd_Write_Data(0x30); 	 //3F
		Lcd_Write_Data(0x30); 	 //3C
		Lcd_WR_Reg(0xC7);    //VCM control2 
		Lcd_Write_Data(0XB7); 
		Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
		Lcd_Write_Data(0x08); 
		Lcd_WR_Reg(0x3A);   
		Lcd_Write_Data(0x55); 
		Lcd_WR_Reg(0xB1);   
		Lcd_Write_Data(0x00);   
		Lcd_Write_Data(0x1A); 
		Lcd_WR_Reg(0xB6);    // Display Function Control 
		Lcd_Write_Data(0x0A); 
		Lcd_Write_Data(0xA2); 
		Lcd_WR_Reg(0xF2);    // 3Gamma Function Disable 
		Lcd_Write_Data(0x00); 
		Lcd_WR_Reg(0x26);    //Gamma curve selected 
		Lcd_Write_Data(0x01); 
		Lcd_WR_Reg(0xE0);    //Set Gamma 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x2A); 
		Lcd_Write_Data(0x28); 
		Lcd_Write_Data(0x08); 
		Lcd_Write_Data(0x0E); 
		Lcd_Write_Data(0x08); 
		Lcd_Write_Data(0x54); 
		Lcd_Write_Data(0XA9); 
		Lcd_Write_Data(0x43); 
		Lcd_Write_Data(0x0A); 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 		 
		Lcd_WR_Reg(0XE1);    //Set Gamma 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x15); 
		Lcd_Write_Data(0x17); 
		Lcd_Write_Data(0x07); 
		Lcd_Write_Data(0x11); 
		Lcd_Write_Data(0x06); 
		Lcd_Write_Data(0x2B); 
		Lcd_Write_Data(0x56); 
		Lcd_Write_Data(0x3C); 
		Lcd_Write_Data(0x05); 
		Lcd_Write_Data(0x10); 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x3F); 
		Lcd_Write_Data(0x3F); 
		Lcd_Write_Data(0x0F); 
		Lcd_WR_Reg(0x2B); 
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x01);
		Lcd_Write_Data(0x3f);
		Lcd_WR_Reg(0x2A); 
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0xef);	 
		Lcd_WR_Reg(0x11); //Exit Sleep
		delay_ms(120);
		Lcd_WR_Reg(0x29); //display on	

	 }

}




