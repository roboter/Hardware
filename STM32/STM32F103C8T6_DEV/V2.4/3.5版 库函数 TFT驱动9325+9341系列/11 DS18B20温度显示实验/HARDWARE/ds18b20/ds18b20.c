

#include "ds18b20.h"
#include "gui.h"



//配置DS18B20的IO    并检测DS是否存在
//返回1:不存在
//返回0:存在    
//注意 ds18b20采用的io 为PA13  而PA13位 SWD接口 所以用板上的DS18B20接口 就会影响SWD的仿真功能	 
u8 ds18b20_init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PORTG口时钟 
		
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//PORTG.11 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//配置为推挽输出  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_13);    //拉高IO

	ow_reset();							//复位总线

	return ds18B20_check();
} 




//DS18B20复位函数
void ow_reset(void)
{
	DS18B20_IO_OUT();
    DQ_OUT=0;				   //拉低
    delay_us(750);             //	  低电平复位信号
    DQ_OUT=1;
    delay_us(16);              //>15us 的上升沿	 15-60us高电平后  是60-240us 的应答信号
}



//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 ds18B20_check(void) 	   
{   
	u8 retry=0;	 		//检测计算变量
	DS18B20_IO_IN();    //配置IO为输入模式
    while (DQ_IN&&retry<50)
	{
		retry++;
		delay_us(4);		//大概4us
	};
	if(retry>=50)return 1;
	else retry=0;	 
    while (!DQ_IN&&retry<60)		 //保持240us的延时 完成整个的复位过程
	{
		retry++;
		delay_us(4);		//大概4us
	};

	if(retry>=60)return 1;	    //没有接到DS18B20应答
	return 0;					//接到应答
}



//DS18B20写命令函数
//向1-WIRE 总线上写1个字节
//u8 val 要写入字节
//DS18B20手册最下面有时序图
void write_byte(u8 val)
{
 u8 i,testb;
 DS18B20_IO_OUT();    //配置IO为输出模式
 for(i=8;i>0;i--)
 { 
   testb=val&0x01;            //最低位移出
   val=val>>1;
   if(testb)				  //写1
   {
   	 DQ_OUT=0;
	 delay_us(4);			  //4us
	 DQ_OUT=1;
	 delay_us(60);			  //60us
   }
   else						  //写0
   {
     DQ_OUT=0;
	 delay_us(60);			  //60us
	 DQ_OUT=1;
	 delay_us(4);			  //4us
   }
 }
}

//DS18B20读1字节函数
//从总线上取1个字节
//返回值为读取字节值
//说明  一次1bit的读取最少需要60us	  两次读取之间需要至少1us的恢复时间
//    单次读取1bit  总线拉低不能超过15us 然后马上拉高
u8 read_byte(void)
{
 u8 i;
 u8 value=0;
 
 for(i=8;i>0;i--)
 {
  DS18B20_IO_OUT();    //配置IO为输出模式
  DQ_OUT=1;
  value>>=1;           //value=value>>1
  DQ_OUT=0;                                  
  delay_us(8);							 //拉低4us 
  DQ_OUT=1;                              //拉高
  DS18B20_IO_IN();     //配置IO为输入模式
  delay_us(12);							 //拉高10us	 准备接收总线当前数据
  if(DQ_IN)value|=0x80;				 //将当前数据值存入临时变量
  delay_us(50);                          //50 us延时  完成一次读取的延时（一次读取最少60us）跳过1us的恢复时间
 }
 return(value);
}



//读出温度函数
//返回为温度值  温度值为short变量 有正负
short read_temp(void)	  //short可以表示-32768~+32767
{
  u8 TL,TH;
  u8 temp;
  short t;
  ow_reset();                  //总线复位
  ds18B20_check();			   //等待DS应答
  write_byte(0xcc);            //发命令
  write_byte(0x44);            //发转换命令
  ow_reset();				   //复位
  ds18B20_check();			   //等待DS应答
  write_byte(0xcc);            //发命令
  write_byte(0xbe);			   //发送读温度命令
  TL=read_byte();    //读温度值的低字节
  TH=read_byte();    //读温度值的高字节
  

  if(TH>7)
  {
    TH=~TH;
    TL=~TL; 
    temp=0;//温度为负   
  }else temp=1;

  t=TH;
  t<<=8;             
  t+=TL;             // 两字节合成一个整型变量。

  if(temp==0)t+=1;	 //如果是负数需要补1  负数转正数是取反后加1

  t=(float)t*0.625;  //0.0625为12位温度采集的分辨率	   t为采集的数值  这里扩大10倍提取小数点后一位
  if(temp)return t;
  else return -t;
  }














