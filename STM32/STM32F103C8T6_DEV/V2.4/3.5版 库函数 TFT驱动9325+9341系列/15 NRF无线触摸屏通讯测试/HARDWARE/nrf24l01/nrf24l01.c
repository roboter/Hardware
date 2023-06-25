




#include "delay.h"
#include "nrf24l01.h"
#include "xpt2046.h"
#include "tft.h"
#include "spi.h"




u8 const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//本地地址
u8 const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//接收地址





//初始化NRF IO配置
void NRF_IO_Init(void)
{	
  	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;  // PC0 1 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);			  //上拉 取消SPI总线片选


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;	      //PC2 下拉输入  该IO判断 NRF是否有高电平信号
    GPIO_Init(GPIOC, &GPIO_InitStructure);


	SPI_Cmd(SPI1, DISABLE); // SPI外设不使能			  NRF的SPI要特殊配置一下

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI主机
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//发送接收8位帧结构

	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//时钟悬空低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//数据捕获于第1个时钟沿

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设


	CEN=0; 			//使能24L01
	CSN=1;			//SPI片选取消  
}  





//从NRF读取一个字节数据
//reg 寄存器地址
u8 SPI_Read(u8 reg)
{
	u8 reg_val;
	
	CSN = 0;                //片选使能  
    SPI1_ReadWriteByte(reg);
	reg_val = SPI1_ReadWriteByte(0xff);    // 读取数据到reg_val
	CSN = 1;                // 取消片选
	
	return(reg_val);        // 返回读取的数据
}
   


//向NRF写入一个字节数据
//reg 寄存器地址  value 要写入的数据
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI1_ReadWriteByte(reg);
    SPI1_ReadWriteByte(value);
	CSN = 1;                   // CSN high again
		
	return(status);            // return nRF24L01 status uchar
}



//从NRF读取多个字节数据
//reg 寄存器地址  *pBuf 读取数据存储指针  uchars 读取的字节个数
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction

	status = SPI1_ReadWriteByte(reg);
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)		  //循环 uchars次
    pBuf[uchar_ctr] = SPI1_ReadWriteByte(0xff); 				  //分别将	 SPI_RW(0)读出的数据地址 放入数组中
	
	CSN = 1;                           
	
	return status;                    // return nRF24L01 status uchar
}


//向NRF写入多个字节数据
//reg 寄存器地址  *pBuf 要写入的数据  uchars 写入的字节个数
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;            //SPI使能       

	  status = SPI1_ReadWriteByte(reg);
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //	 根据数据个数循环							 
		SPI1_ReadWriteByte(*pBuf++);						//将数组的数据 依次写入

	CSN = 1;           //关闭SPI
	return(status);    // 
}


//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
    SPI1_SetSpeed(SPI_BaudRatePrescaler_8);       //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   	 
	SPI_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);   //写入5个字节的地址.	
	SPI_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}




//NRF接收数据函数
//rx_buf  数据缓存区
//该函数检测NRF状态寄存器状态 当有中断立即接收数据到rx_buf缓存区
u8 nRF24L01_RxPacket(u8 *rx_buf)
{	 
    u8 sta;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz） 

	sta=SPI_Read(STATUS);	    // 读取状态寄存器来判断数据接收状况
	SPI_RW_Reg(WRITE_REG_NRF+STATUS,sta);   //清中断 （接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志）
	if(sta&RX_OK)				// 判断是否接收到数据
	{

		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		SPI_RW_Reg(FLUSH_RX,0xff);

		return 0; 
	}
	
	return 1;
}


//将缓存区tx_buf中的数据发送出去
//tx_buf  要发送的数据缓存区
u8 nRF24L01_TxPacket(u8 *tx_buf)
{	 
    u8 st;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz） 
	CEN=0;			//StandBy I模式	

	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	

	CEN=1;		 //置高CE，激发数据发送
	while(IRQ!=0);		   //等待发送完成
	st=	SPI_Read(STATUS);			  //读NRF寄存器状态
	SPI_RW_Reg(WRITE_REG_NRF+STATUS,st);  //清中断

		if(st&MAX_TX)//达到最大重发次数
	{
		SPI_RW_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}

	if(st&TX_OK)				 //发送成功
	{
	return TX_OK;
	}
	return 0xff;

}


//NRF24L01初始化
//m 1 发送模式   0 接收模式
void RX_TX_Mode(u8 m)	        //接收 or 发射 模式 初始化
{
 	CEN=0;    // chip enable
 	CSN=1;   // Spi disable 
	SPI_Write_Buf(WRITE_REG_NRF + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址	
	SPI_Write_Buf(WRITE_REG_NRF + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG_NRF + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG_NRF + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG_NRF + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG_NRF + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG_NRF + RF_SETUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB

	if(m==1) SPI_RW_Reg(WRITE_REG_NRF + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	else if(m==0) SPI_RW_Reg(WRITE_REG_NRF + CONFIG, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收

	CEN=1;
}



///*
//nrf24c04 测试函数	  此函数支持选择发送 接收功能 
//在发射端触摸画板上发生触摸现象 
//或者说有画线出现 同时将在接收画板上显示
//*/
//void nrf24()
//{
//  struct TFT_Pointer Tp_pix;      	 //触摸画板函数
//
//  u8 Buf[3],						 //缓存数组
//     t,								 //临时变量
//	 mode=1;							 //模式标志位   默认为发送模式
//  u16 pix,piy;						 //临时变量	   用于处理接收到的数据
//
//
//  Dialog_box(70,120,170,200,window,Red,window,"  模式选择");	  //画带有说明的巨型对话框
//
//  GUI_arc(80,149,6,Blue,0);						 //画选择圆圈区
//  GUI_arc(80,149,4,Red3,1);						 //默认选择发送模式
//  GUI_arc(80,167,6,Blue,0);
//
//  GUI_sprintf_hzstr16x(96,141,"发送模式",Black,1);//选择说明
//  GUI_sprintf_hzstr16x(96,159,"接收模式",Black,1);
//
//  Touch_key(130,180,Blue2,Blue,0);    //确定按钮框
//
//  while(1)
//  {	      
//    Tp_pix=TFT_Cm();	                   //扫描触摸屏
//    if(Tp_pix.flag==1)                     //是否有触摸事件  
//     {
//      if(Tp_pix.x>96&&Tp_pix.x<164) 
//       {
//   	    if(Tp_pix.y>141&&Tp_pix.y<157)     //发送
//	     {
//	      GUI_arc(80,167,4,White,1);	   //清 选择点
//	      GUI_arc(80,149,4,Red3,1);		   //画 选择点
//	      mode=1;					       //发送  	 
//	     }
//	    if(Tp_pix.y>159&&Tp_pix.y<178)	   //接收
//	     {
//	      GUI_arc(80,149,4,White,1);	   //清 选择点
//	      GUI_arc(80,167,4,Red3,1);		   //画 选择点
//	      mode=0;					       //接收
//	     }   
//       }
//      if(Tp_pix.x>130&&Tp_pix.x<164&&Tp_pix.y>180&&Tp_pix.y<200) break;	   //确定按键
//     }
//  }
//  GUI_Clear(White);	   //整体清屏
//  tian(1);//填充
//
//  if(mode==0)	       //进入接收模式
//  {
//    GUI_sprintf_hzstr16x(0,0,"接收模式",White,1);
//	    
//	RX_Mode();	           //接收模式初始化
//
// 	while(1)
//	{
//	 led=1;				  //关led  
//	 if(nRF24L01_RxPacket(Buf)==0)		   //采集数据 
//	  {				
//			  
//		   pix=Buf[0];			   //处理数据 屏幕分辨率为320X240 一字节最多能装255  320部分 大于一个字节所以分两字节装数据
//		   piy=(Buf[1]<<8)+Buf[2];
//           Address_set(pix,piy,pix+2,piy+2,pix,piy);			//3*3个点为一个单元点
//		   for(t=0;t<9;t++)				
//			Lcd_Write_Data(Red);										
//
//		   led=0;									 //指示灯判断是否接收到数据
//	       delay1ms(10);								//小延时
//       }
//	      
//	  Tp_pix=TFT_Cm();	                            // 扫描触摸屏
//      if(Tp_pix.flag==1)                              //是否有触摸事件 发送 	   
//	    if(Tp_pix.x>=200&&Tp_pix.x<=239&&Tp_pix.y>=295&&Tp_pix.y<=320){led=1;Return();break;}
//	  
//	 }
//  }
//
//
//  if(mode==1)	       //进入发送模式
//  {
//	GUI_sprintf_hzstr16x(0,0,"发送模式",White,1);
//	 
//	TX_Mode();			 //发送模式初始化
//	
//   	while(1)
//	 {	
//       Tp_pix=TFT_Cm();	                            // 扫描触摸屏
//       if(Tp_pix.flag==1)                              //是否有触摸事件 发生 
//		{
//		  if(Tp_pix.y>=20&&Tp_pix.y<=302)		//判断 当前值 是否在预设的 画图区域
//	      {
//																			//设定画图位置 
//			Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3个点为一个单元点	
//		    for(t=0;t<9;t++)				
//			 Lcd_Write_Data(Red);
//	
//	
//			Buf[0]= Tp_pix.x;                               //将当前触摸屏位置存入数组中 
//			Buf[2]= Tp_pix.y;
//			Buf[1]= Tp_pix.y>>8;
//	
//	        nRF24L01_TxPacket(Buf);	//发送数据	
//	        delay1ms(10);	
//		  }
//		if(Tp_pix.x>=200&&Tp_pix.x<=239&&Tp_pix.y>=295&&Tp_pix.y<=320){Return();break;}
//	    }
//
//	  }
//
//  }
//}








