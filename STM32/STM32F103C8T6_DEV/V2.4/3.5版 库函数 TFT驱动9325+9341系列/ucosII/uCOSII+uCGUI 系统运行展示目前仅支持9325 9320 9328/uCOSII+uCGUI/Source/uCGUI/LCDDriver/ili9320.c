#include "stm32f10x_lib.h"
#include "ili9320.h"
#include "ili9320_font.h"

//#define ili9320_WriteData(x)\
//{GPIOB->ODR=((GPIOB->ODR&0x00ff)|(x<<8));\
//GPIOC->ODR=((GPIOC->ODR&0xff00)|(x>>8));}

u16 DeviceCode;

void Lcd_Configuration(void)
{ 
   GPIO_InitTypeDef  GPIO_InitStructure;					 //����GPIO�ṹ��


 //PB 0-15��Ϊ���ݿ� ����Ҫ�ص� PB�ϵ�JTAG���� 	ֻ����SWJ����
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  //����AFIOʱ��
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //����JTAG-DP Disabled and SW-DP Enabled 
 
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;			 //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.13
 GPIO_SetBits(GPIOB,GPIO_Pin_All);						 //PB.5 �����


 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
 GPIO_Init(GPIOC, &GPIO_InitStructure);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
 GPIO_Init(GPIOA, &GPIO_InitStructure);


} 


////�Ĵ�������
//
////���Ŷ���
//void Set_Rs(void)		   //����/����,0=����,1=����
//{
//  GPIOC->BSRR|=GPIO_Pin_9;
//}
//void Clr_Rs(void)
//{
//  GPIOC->BRR|=GPIO_Pin_9;
//}     
//          		
//							   
//void Set_nWr(void)		   //д����
//{
//  GPIOC->BSRR|=GPIO_Pin_10;
//}
//void Clr_nWr(void)
//{
//  GPIOC->BRR|=GPIO_Pin_10;
//}                  
//
//
//void Set_nRd(void)		   //������
//{									   
//  GPIOA->BSRR|=GPIO_Pin_15;
//}
//void Clr_nRd(void)
//{
//  GPIOA->BRR|=GPIO_Pin_15;
//}                   
//
// 
//void Set_Cs(void)	   //Ƭѡ
//{
//  GPIOC->BSRR|=GPIO_Pin_8;
// }
//
//void Clr_Cs(void)
//{
//  GPIOC->BRR|=GPIO_Pin_8;
//}  



/****************************************************************************
* ��    �ƣ�void ili9320_Initializtion()
* ��    �ܣ���ʼ�� ILI9320 ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Initializtion();
****************************************************************************/
void ili9320_Initializtion()
{
  /*****************************
  **    Ӳ������˵��          **
  ** STM32         ili9320    **
  ** PE0~15 <----> DB0~15     **
  ** PD15   <----> nRD        **
  ** PD14   <----> RS         **
  ** PD13   <----> nWR        **
  ** PD12   <----> nCS        **
  ** PD11   <----> nReset     **
  ** PC0    <----> BK_LED     **
  ******************************/
 	u16 i;

  	ili9320_WriteData(0xffff);
	Clr_Cs();
//  	Set_Rst;
	Set_nWr();
	Set_Cs();
	Set_Rs();
	Set_nRd();
//	Set_Rst;
//  ili9320_Reset();                                        // ��λ ili9320_Reset
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  ili9320_WriteRegister(0x0000,0x0001);ili9320_Delay(10000);
  for(i=50000;i>0;i--);
  for(i=50000;i>0;i--);
  DeviceCode = ili9320_ReadRegister(0x0000);
	if(DeviceCode==0x9325||DeviceCode==0x9328)
	{
 		ili9320_WriteRegister(0x00e5,0x78F0);      
//        ili9320_WriteRegister(0x0000,0x0001);
        ili9320_WriteRegister(0x0001,0x0100);     
        ili9320_WriteRegister(0x0002,0x0700);                   
        ili9320_WriteRegister(0x0003,0x1030);    
        ili9320_WriteRegister(0x0004,0x0000);                                   
        ili9320_WriteRegister(0x0008,0x0202);	           
        ili9320_WriteRegister(0x0009,0x0000);         
        ili9320_WriteRegister(0x000a,0x0000);         
        ili9320_WriteRegister(0x000c,0x0001);         
        ili9320_WriteRegister(0x000d,0x0000);          
        ili9320_WriteRegister(0x000f,0x0000);
//Power On sequence //
        ili9320_WriteRegister(0x0010,0x0000);   
        ili9320_WriteRegister(0x0011,0x0007);
        ili9320_WriteRegister(0x0012,0x0000);                                                                 
        ili9320_WriteRegister(0x0013,0x0000);
        ili9320_WriteRegister(0x0007,0x0001);                 
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0010,0x1690);   
        ili9320_WriteRegister(0x0011,0x0227);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0012,0x009d);                  
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0013,0x1900);   
        ili9320_WriteRegister(0x0029,0x0025);
        ili9320_WriteRegister(0x002b,0x000d);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0020,0x0000);                                                            
        ili9320_WriteRegister(0x0021,0x0000);           
///////////////////////////////////////////////////////      
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0030,0x0007); 
        ili9320_WriteRegister(0x0031,0x0303);   
        ili9320_WriteRegister(0x0032,0x0003);
        ili9320_WriteRegister(0x0035,0x0206);
        ili9320_WriteRegister(0x0036,0x0008); 
        ili9320_WriteRegister(0x0037,0x0406);
        ili9320_WriteRegister(0x0038,0x0304);        
        ili9320_WriteRegister(0x0039,0x0007);     
        ili9320_WriteRegister(0x003c,0x0602);
        ili9320_WriteRegister(0x003d,0x0008);
        for(i=50000;i>0;i--);
		for(i=50000;i>0;i--);
        ili9320_WriteRegister(0x0050,0x0000);
        ili9320_WriteRegister(0x0051,0x00ef);                   
        ili9320_WriteRegister(0x0052,0x0000);                   
        ili9320_WriteRegister(0x0053,0x013f); 
        
        ili9320_WriteRegister(0x0060,0xa700);        
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006a,0x0000);
        ili9320_WriteRegister(0x0080,0x0000);
        ili9320_WriteRegister(0x0081,0x0000);
        ili9320_WriteRegister(0x0082,0x0000);
        ili9320_WriteRegister(0x0083,0x0000);
        ili9320_WriteRegister(0x0084,0x0000);
        ili9320_WriteRegister(0x0085,0x0000);
      
        ili9320_WriteRegister(0x0090,0x0010);     
        ili9320_WriteRegister(0x0092,0x0600);  
		   
        ili9320_WriteRegister(0x0007,0x0133);
	}
	else
	{
	
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
		for(i=50000;i>0;i--);
		Lcd_WR_Reg(0x29); //display on		
	
	}

//	else if(DeviceCode==0x9320)
//	{
//		ili9320_WriteRegister(0x00,0x0000);
//		ili9320_WriteRegister(0x01,0x0100);	//Driver Output Contral.
//		ili9320_WriteRegister(0x02,0x0700);	//LCD Driver Waveform Contral.
////		ili9320_WriteRegister(0x03,0x1030);	//Entry Mode Set.
//		ili9320_WriteRegister(0x03,0x1018);	//Entry Mode Set.
//	
//		ili9320_WriteRegister(0x04,0x0000);	//Scalling Contral.
//		ili9320_WriteRegister(0x08,0x0202);	//Display Contral 2.(0x0207)
//		ili9320_WriteRegister(0x09,0x0000);	//Display Contral 3.(0x0000)
//		ili9320_WriteRegister(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
//		ili9320_WriteRegister(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
//		ili9320_WriteRegister(0x0d,0x0000);	//Frame Maker Position.
//		ili9320_WriteRegister(0x0f,0x0000);	//Extern Display Interface Contral 2.
//	
//		for(i=50000;i>0;i--);
//		for(i=50000;i>0;i--);
//		ili9320_WriteRegister(0x07,0x0101);	//Display Contral.
//		for(i=50000;i>0;i--);
//		for(i=50000;i>0;i--);
//	
//		ili9320_WriteRegister(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
//		ili9320_WriteRegister(0x11,0x0007);								//Power Control 2.(0x0001)
//		ili9320_WriteRegister(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
//		ili9320_WriteRegister(0x13,0x0b00);								//Power Control 4.
//		ili9320_WriteRegister(0x29,0x0000);								//Power Control 7.
//	
//		ili9320_WriteRegister(0x2b,(1<<14)|(1<<4));
//		
//		ili9320_WriteRegister(0x50,0);		//Set X Start.
//		ili9320_WriteRegister(0x51,239);	//Set X End.
//		ili9320_WriteRegister(0x52,0);		//Set Y Start.
//		ili9320_WriteRegister(0x53,319);	//Set Y End.
//	
//		ili9320_WriteRegister(0x60,0x2700);	//Driver Output Control.
//		ili9320_WriteRegister(0x61,0x0001);	//Driver Output Control.
//		ili9320_WriteRegister(0x6a,0x0000);	//Vertical Srcoll Control.
//	
//		ili9320_WriteRegister(0x80,0x0000);	//Display Position? Partial Display 1.
//		ili9320_WriteRegister(0x81,0x0000);	//RAM Address Start? Partial Display 1.
//		ili9320_WriteRegister(0x82,0x0000);	//RAM Address End-Partial Display 1.
//		ili9320_WriteRegister(0x83,0x0000);	//Displsy Position? Partial Display 2.
//		ili9320_WriteRegister(0x84,0x0000);	//RAM Address Start? Partial Display 2.
//		ili9320_WriteRegister(0x85,0x0000);	//RAM Address End? Partial Display 2.
//	
//		ili9320_WriteRegister(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
//		ili9320_WriteRegister(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
//		ili9320_WriteRegister(0x93,0x0001);	//Panel Interface Contral 3.
//		ili9320_WriteRegister(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
//		ili9320_WriteRegister(0x97,(0<<8));	//
//		ili9320_WriteRegister(0x98,0x0000);	//Frame Cycle Contral.
//
//	
//		ili9320_WriteRegister(0x07,0x0173);	//(0x0173)
//	}
//	else if(DeviceCode==0x9919)
//	{
//		//------POWER ON &RESET DISPLAY OFF
//		 ili9320_WriteRegister(0x28,0x0006);
//		
//		 ili9320_WriteRegister(0x00,0x0001);
//		
//		 ili9320_WriteRegister(0x10,0x0000);
//		
//		 ili9320_WriteRegister(0x01,0x72ef);
//
//		 ili9320_WriteRegister(0x02,0x0600);
//
//		 ili9320_WriteRegister(0x03,0x6a38);
//		
//		 ili9320_WriteRegister(0x11,0x6874);//70
//		
//		 
//		     //  RAM WRITE DATA MASK
//		 ili9320_WriteRegister(0x0f,0x0000); 
//		    //  RAM WRITE DATA MASK
//		 ili9320_WriteRegister(0x0b,0x5308); 
//		
//		 ili9320_WriteRegister(0x0c,0x0003);
//		
//		 ili9320_WriteRegister(0x0d,0x000a);
//		
//		 ili9320_WriteRegister(0x0e,0x2e00);  //0030
//		
//		 ili9320_WriteRegister(0x1e,0x00be);
//		
//		 ili9320_WriteRegister(0x25,0x8000);
//		
//		 ili9320_WriteRegister(0x26,0x7800);
//		
//		 ili9320_WriteRegister(0x27,0x0078);
//		
//		 ili9320_WriteRegister(0x4e,0x0000);
//		
//		 ili9320_WriteRegister(0x4f,0x0000);
//		
//		 ili9320_WriteRegister(0x12,0x08d9);
//		
//		 // -----------------Adjust the Gamma Curve----//
//		 ili9320_WriteRegister(0x30,0x0000);	 //0007
//		
//		 ili9320_WriteRegister(0x31,0x0104);	   //0203
//		
//		 ili9320_WriteRegister(0x32,0x0100);		//0001
//
//		 ili9320_WriteRegister(0x33,0x0305);	  //0007
//
//		 ili9320_WriteRegister(0x34,0x0505);	  //0007
//		
//		 ili9320_WriteRegister(0x35,0x0305);		 //0407
//		
//		 ili9320_WriteRegister(0x36,0x0707);		 //0407
//		
//		 ili9320_WriteRegister(0x37,0x0300);		  //0607
//		
//		 ili9320_WriteRegister(0x3a,0x1200);		 //0106
//		
//		 ili9320_WriteRegister(0x3b,0x0800);		 
//
//		 ili9320_WriteRegister(0x07,0x0033);
//	} 
/*	else if(DeviceCode==0x9331)
	{
	 	//POWER ON &RESET DISPLAY OFF///////////
		// Start Initial Sequence //////////
		ili9320_WriteRegister(0x00E7, 0x1014);
		ili9320_WriteRegister(0x0001, 0x0100); // set SS and SM bit   0x0100
		ili9320_WriteRegister(0x0002, 0x0200); // set 1 line inversion
		ili9320_WriteRegister(0x0003, 0x1030); // set GRAM write direction and BGR=1.     0x1030
		ili9320_WriteRegister(0x0008, 0x0202); // set the back porch and front porch
		ili9320_WriteRegister(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		ili9320_WriteRegister(0x000A, 0x0000); // FMARK function
		ili9320_WriteRegister(0x000C, 0x0000); // RGB interface setting
		ili9320_WriteRegister(0x000D, 0x0000); // Frame marker Position
		ili9320_WriteRegister(0x000F, 0x0000); // RGB interface polarity
		//Power On sequence 
		ili9320_WriteRegister(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_WriteRegister(0x0012, 0x0000); // VREG1OUT voltage
		ili9320_WriteRegister(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		ili9320_Delay(200); // Dis-charge capacitor power voltage
		ili9320_WriteRegister(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0012, 0x000C); // Internal reference voltage= Vci;
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		ili9320_WriteRegister(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		ili9320_WriteRegister(0x002B, 0x000B); // Set Frame Rate
		ili9320_Delay(50); // Delay 50ms
		ili9320_WriteRegister(0x0020, 0x0000); // GRAM horizontal Address
		ili9320_WriteRegister(0x0021, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		ili9320_WriteRegister(0x0030, 0x0000);
		ili9320_WriteRegister(0x0031, 0x0106);
		ili9320_WriteRegister(0x0032, 0x0000);
		ili9320_WriteRegister(0x0035, 0x0204);
		ili9320_WriteRegister(0x0036, 0x160A);
		ili9320_WriteRegister(0x0037, 0x0707);
		ili9320_WriteRegister(0x0038, 0x0106);
		ili9320_WriteRegister(0x0039, 0x0707);
		ili9320_WriteRegister(0x003C, 0x0402);
		ili9320_WriteRegister(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		ili9320_WriteRegister(0x0050, 0x0000); // Horizontal GRAM Start Address
		ili9320_WriteRegister(0x0051, 0x00EF); // Horizontal GRAM End Address
		ili9320_WriteRegister(0x0052, 0x0000); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0053, 0x013F); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0060, 0x2700); // Gate Scan Line
		ili9320_WriteRegister(0x0061, 0x0001); // NDL,VLE, REV
		ili9320_WriteRegister(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		ili9320_WriteRegister(0x0080, 0x0000);
		ili9320_WriteRegister(0x0081, 0x0000);
		ili9320_WriteRegister(0x0082, 0x0000);
		ili9320_WriteRegister(0x0083, 0x0000);
		ili9320_WriteRegister(0x0084, 0x0000);
		ili9320_WriteRegister(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		ili9320_WriteRegister(0x0090, 0x0010);
		ili9320_WriteRegister(0x0092, 0x0600);
		ili9320_WriteRegister(0x0007,0x0021);		
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0007,0x0061);
		ili9320_Delay(50);
		ili9320_WriteRegister(0x0007,0x0133);  // 262K color and display ON
		ili9320_Delay(50);
	} 								   */
//	else if(DeviceCode==0x4531)
//	{		
//		// Setup display
//		ili9320_WriteRegister(0x00,0x0001);
//	    ili9320_WriteRegister(0x10,0x0628);
//	    ili9320_WriteRegister(0x12,0x0006);
//	    ili9320_WriteRegister(0x13,0x0A32);
//	    ili9320_WriteRegister(0x11,0x0040);
//	    ili9320_WriteRegister(0x15,0x0050);
//	    ili9320_WriteRegister(0x12,0x0016);
//	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x10,0x5660);
//	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x13,0x2A4E);
//	    ili9320_WriteRegister(0x01,0x0100);
//	    ili9320_WriteRegister(0x02,0x0300);
//	
//	    ili9320_WriteRegister(0x03,0x1030);
////	    ili9320_WriteRegister(0x03,0x1038);
//	
//	    ili9320_WriteRegister(0x08,0x0202);
//	    ili9320_WriteRegister(0x0A,0x0000);
//	    ili9320_WriteRegister(0x30,0x0000);
//	    ili9320_WriteRegister(0x31,0x0402);
//	    ili9320_WriteRegister(0x32,0x0106);
//	    ili9320_WriteRegister(0x33,0x0700);
//	    ili9320_WriteRegister(0x34,0x0104);
//	    ili9320_WriteRegister(0x35,0x0301);
//	    ili9320_WriteRegister(0x36,0x0707);
//	    ili9320_WriteRegister(0x37,0x0305);
//	    ili9320_WriteRegister(0x38,0x0208);
//	    ili9320_WriteRegister(0x39,0x0F0B);
//	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x41,0x0002);
//	    ili9320_WriteRegister(0x60,0x2700);
//	    ili9320_WriteRegister(0x61,0x0001);
//	    ili9320_WriteRegister(0x90,0x0119);
//	    ili9320_WriteRegister(0x92,0x010A);
//	    ili9320_WriteRegister(0x93,0x0004);
//	    ili9320_WriteRegister(0xA0,0x0100);
////	    ili9320_WriteRegister(0x07,0x0001);
//	    ili9320_Delay(15);
////	    ili9320_WriteRegister(0x07,0x0021); 
//	    ili9320_Delay(15);
////	    ili9320_WriteRegister(0x07,0x0023);
//	    ili9320_Delay(15);
////	    ili9320_WriteRegister(0x07,0x0033);
//	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0x07,0x0133);
//	    ili9320_Delay(15);
//	    ili9320_WriteRegister(0xA0,0x0000);
//	    ili9320_Delay(20);
//	} 									   
//	else if(DeviceCode==0x7783)
//	{
//		// Start Initial Sequence
//		ili9320_WriteRegister(0x00FF,0x0001);
//		ili9320_WriteRegister(0x00F3,0x0008);
//		ili9320_WriteRegister(0x0001,0x0100);
//		ili9320_WriteRegister(0x0002,0x0700);
//		ili9320_WriteRegister(0x0003,0x1030);  //0x1030
//		ili9320_WriteRegister(0x0008,0x0302);
//		ili9320_WriteRegister(0x0008,0x0207);
//		ili9320_WriteRegister(0x0009,0x0000);
//		ili9320_WriteRegister(0x000A,0x0000);
//		ili9320_WriteRegister(0x0010,0x0000);  //0x0790
//		ili9320_WriteRegister(0x0011,0x0005);
//		ili9320_WriteRegister(0x0012,0x0000);
//		ili9320_WriteRegister(0x0013,0x0000);
//		ili9320_Delay(50);
//		ili9320_WriteRegister(0x0010,0x12B0);
//		ili9320_Delay(50);
//		ili9320_WriteRegister(0x0011,0x0007);
//		ili9320_Delay(50);
//		ili9320_WriteRegister(0x0012,0x008B);
//		ili9320_Delay(50);
//		ili9320_WriteRegister(0x0013,0x1700);
//		ili9320_Delay(50);
//		ili9320_WriteRegister(0x0029,0x0022);
//		
//		//################# void Gamma_Set(void) ####################//
//		ili9320_WriteRegister(0x0030,0x0000);
//		ili9320_WriteRegister(0x0031,0x0707);
//		ili9320_WriteRegister(0x0032,0x0505);
//		ili9320_WriteRegister(0x0035,0x0107);
//		ili9320_WriteRegister(0x0036,0x0008);
//		ili9320_WriteRegister(0x0037,0x0000);
//		ili9320_WriteRegister(0x0038,0x0202);
//		ili9320_WriteRegister(0x0039,0x0106);
//		ili9320_WriteRegister(0x003C,0x0202);
//		ili9320_WriteRegister(0x003D,0x0408);
//		ili9320_Delay(50);
//		
//		
//		ili9320_WriteRegister(0x0050,0x0000);		
//		ili9320_WriteRegister(0x0051,0x00EF);		
//		ili9320_WriteRegister(0x0052,0x0000);		
//		ili9320_WriteRegister(0x0053,0x013F);		
//		ili9320_WriteRegister(0x0060,0xA700);		
//		ili9320_WriteRegister(0x0061,0x0001);
//		ili9320_WriteRegister(0x0090,0x0033);				
//		ili9320_WriteRegister(0x002B,0x000B);		
//		ili9320_WriteRegister(0x0007,0x0133);
//		ili9320_Delay(50);
//	}  
	/*
	else if(DeviceCode==0x1505)
	{
// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        ili9320_WriteRegister(0x0007,0x0000);
        ili9320_Delay(5);
        ili9320_WriteRegister(0x0012,0x011C);//0x011A   why need to set several times?
        ili9320_WriteRegister(0x00A4,0x0001);//NVM
    //
        ili9320_WriteRegister(0x0008,0x000F);
        ili9320_WriteRegister(0x000A,0x0008);
        ili9320_WriteRegister(0x000D,0x0008);
       
  //GAMMA CONTROL/
        ili9320_WriteRegister(0x0030,0x0707);
        ili9320_WriteRegister(0x0031,0x0007); //0x0707
        ili9320_WriteRegister(0x0032,0x0603); 
        ili9320_WriteRegister(0x0033,0x0700); 
        ili9320_WriteRegister(0x0034,0x0202); 
        ili9320_WriteRegister(0x0035,0x0002); //?0x0606
        ili9320_WriteRegister(0x0036,0x1F0F);
        ili9320_WriteRegister(0x0037,0x0707); //0x0f0f  0x0105
        ili9320_WriteRegister(0x0038,0x0000); 
        ili9320_WriteRegister(0x0039,0x0000); 
        ili9320_WriteRegister(0x003A,0x0707); 
        ili9320_WriteRegister(0x003B,0x0000); //0x0303
        ili9320_WriteRegister(0x003C,0x0007); //?0x0707
        ili9320_WriteRegister(0x003D,0x0000); //0x1313//0x1f08
        ili9320_Delay(5);
        ili9320_WriteRegister(0x0007,0x0001);
        ili9320_WriteRegister(0x0017,0x0001);   //Power supply startup enable
        ili9320_Delay(5);
  
  //power control//
        ili9320_WriteRegister(0x0010,0x17A0); 
        ili9320_WriteRegister(0x0011,0x0217); //reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        ili9320_WriteRegister(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        ili9320_WriteRegister(0x0013,0x0F00); //VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        ili9320_WriteRegister(0x002A,0x0000);  
        ili9320_WriteRegister(0x0029,0x000A); //0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        ili9320_WriteRegister(0x0012,0x013E); // 0x013C  power supply on
           //Coordinates Control//
        ili9320_WriteRegister(0x0050,0x0000);//0x0e00
        ili9320_WriteRegister(0x0051,0x00EF); 
        ili9320_WriteRegister(0x0052,0x0000); 
        ili9320_WriteRegister(0x0053,0x013F); 
    //Pannel Image Control//
        ili9320_WriteRegister(0x0060,0x2700); 
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006A,0x0000); 
        ili9320_WriteRegister(0x0080,0x0000); 
    //Partial Image Control//
        ili9320_WriteRegister(0x0081,0x0000); 
        ili9320_WriteRegister(0x0082,0x0000); 
        ili9320_WriteRegister(0x0083,0x0000); 
        ili9320_WriteRegister(0x0084,0x0000); 
        ili9320_WriteRegister(0x0085,0x0000); 
  //Panel Interface Control//
        ili9320_WriteRegister(0x0090,0x0013); //0x0010 frenqucy
        ili9320_WriteRegister(0x0092,0x0300); 
        ili9320_WriteRegister(0x0093,0x0005); 
        ili9320_WriteRegister(0x0095,0x0000); 
        ili9320_WriteRegister(0x0097,0x0000); 
        ili9320_WriteRegister(0x0098,0x0000); 
  
        ili9320_WriteRegister(0x0001,0x0100); 
        ili9320_WriteRegister(0x0002,0x0700); 
        ili9320_WriteRegister(0x0003,0x1030); 
        ili9320_WriteRegister(0x0004,0x0000); 
        ili9320_WriteRegister(0x000C,0x0000); 
        ili9320_WriteRegister(0x000F,0x0000); 
        ili9320_WriteRegister(0x0020,0x0000); 
        ili9320_WriteRegister(0x0021,0x0000); 
        ili9320_WriteRegister(0x0007,0x0021); 
        ili9320_Delay(20);
        ili9320_WriteRegister(0x0007,0x0061); 
        ili9320_Delay(20);
        ili9320_WriteRegister(0x0007,0x0173); 
        ili9320_Delay(20);
	}							 			  
	else if(DeviceCode==0x8989)
	{
		ili9320_WriteRegister(0x0000,0x0001);    ili9320_Delay(50000);  //�򿪾���
    	ili9320_WriteRegister(0x0003,0xA8A4);    ili9320_Delay(50000);   //0xA8A4
    	ili9320_WriteRegister(0x000C,0x0000);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x000D,0x080C);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x000E,0x2B00);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x001E,0x00B0);    ili9320_Delay(50000);   
    	ili9320_WriteRegister(0x0001,0x2B3F);    ili9320_Delay(50000);   //�����������320*240  0x6B3F
    	ili9320_WriteRegister(0x0002,0x0600);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0010,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0011,0x6070);    ili9320_Delay(50000);        //0x4030           //�������ݸ�ʽ  16λɫ 		���� 0x6058
    	ili9320_WriteRegister(0x0005,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0006,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0016,0xEF1C);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0017,0x0003);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0007,0x0233);    ili9320_Delay(50000);        //0x0233       
    	ili9320_WriteRegister(0x000B,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x000F,0x0000);    ili9320_Delay(50000);        //ɨ�迪ʼ��ַ
    	ili9320_WriteRegister(0x0041,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0042,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0048,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0049,0x013F);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004A,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004B,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0044,0xEF00);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0045,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0046,0x013F);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0030,0x0707);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0031,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0032,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0033,0x0502);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0034,0x0507);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0035,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0036,0x0204);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0037,0x0502);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x003A,0x0302);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x003B,0x0302);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0023,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0024,0x0000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x0025,0x8000);    ili9320_Delay(50000);
    	ili9320_WriteRegister(0x004f,0);        //����ַ0
    	ili9320_WriteRegister(0x004e,0);        //����ַ0
	}  									*/
  for(i=50000;i>0;i--);
  ili9320_Clear(0x00f8);
  ili9320_Clear(0xf800);
}

/****************************************************************************
* ��    �ƣ�void ili9320_SetCursor(u16 x,u16 y)
* ��    �ܣ�������Ļ����
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetCursor(10,10);
****************************************************************************/
__inline void ili9320_SetCursor(u16 x,u16 y)
{
	if(DeviceCode==0x8989)
	{
	 	ili9320_WriteRegister(0x004e,y);        //��
    	ili9320_WriteRegister(0x004f,0x13f-x);  //��
	}
	else if(DeviceCode==0x9919)
	{
		ili9320_WriteRegister(0x004e,x); // ��
  		ili9320_WriteRegister(0x004f,y); // ��	
	}
	else
	{
  		ili9320_WriteRegister(0x0020,y); // ��
  		ili9320_WriteRegister(0x0021,0x13f-x); // ��
	}
}

/****************************************************************************
* ��    �ƣ�void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* ��    �ܣ����ô�������
* ��ڲ�����StartX     ����ʼ����
*           StartY     ����ʼ����
*           EndX       �н�������
*           EndY       �н�������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetWindows(0,0,100,100)��
****************************************************************************/
__inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  ili9320_SetCursor(StartX,StartY);
  ili9320_WriteRegister(0x0050, StartX);
  ili9320_WriteRegister(0x0052, StartY);
  ili9320_WriteRegister(0x0051, EndX);
  ili9320_WriteRegister(0x0053, EndY);
}

/****************************************************************************
* ��    �ƣ�void ili9320_Clear(u16 dat)
* ��    �ܣ�����Ļ����ָ������ɫ��������������� 0xffff
* ��ڲ�����dat      ���ֵ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Clear(0xffff);
****************************************************************************/
void ili9320_Clear(u16 dat)
{
  u32  i;

  ili9320_SetCursor(0x0000, 0x0000);  
  Clr_Cs(); 
  ili9320_WriteIndex(0x0022); 
  Set_Rs();   
  for(i=0;i<76800;i++)
  {
    ili9320_WriteData(dat);
	Clr_nWr();
	Set_nWr();
  }

  Set_Cs();
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_GetPoint(u16 x,u16 y)
* ��    �ܣ���ȡָ���������ɫֵ
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������ǰ������ɫֵ
* ˵    ����
* ���÷�����i=ili9320_GetPoint(10,10);
****************************************************************************/
//u16 ili9320_GetPoint(u16 x,u16 y)
//{
//  ili9320_SetCursor(x,y);
//  return (ili9320_BGR2RGB(ili9320_ReadRegister(0x0022)));
//}


u16 ili9320_GetPoint(u16 x,u16 y)
{
	u16 temp;
	ili9320_SetCursor(x,y);
	Clr_Cs();
	ili9320_WriteIndex(0x0022);

	Clr_nRd();  
	temp = ili9320_ReadData(); //dummy
	temp=ili9320_BGR2RGB(temp);										 
	Set_nRd();
	   
//	Clr_nRd;  
//	temp = temp | ili9320_ReadData(); 
//	Set_nRd;
		
	Set_Cs();
	//if(DeviceCode!=0x7783&&DeviceCode!=0x4531)
	//temp=ili9320_BGR2RGB(temp);
	
	return (temp);
}

/****************************************************************************
* ��    �ƣ�void ili9320_SetPoint(u16 x,u16 y,u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);

  Clr_Cs();
  ili9320_WriteIndex(0x0022);
  Set_Rs();
  ili9320_WriteData(point);
  Clr_nWr();Set_nWr();
  Set_Cs();
}

/****************************************************************************
* ��    �ƣ�void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* ��    �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ��ڲ�����StartX     ����ʼ����
*           StartY     ����ʼ����
*           EndX       �н�������
*           EndY       �н�������
            pic        ͼƬͷָ��
* ���ڲ�������
* ˵    ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
* ���÷�����ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u16  i;
  ili9320_SetWindows(StartX,StartY,EndX,EndY);
  ili9320_SetCursor(StartX,StartY);
  
  Clr_Cs();

  ili9320_WriteIndex(0x0022);
  Set_Rs();
  for (i=0;i<(EndX*EndY);i++)
  {
      ili9320_WriteData(*pic++);
	  Clr_nWr();Set_nWr();
  }
      
  Set_Cs();
}

/****************************************************************************
* ��    �ƣ�void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* ��    �ܣ���ָ��������ʾһ��8x16�����ascii�ַ�
* ��ڲ�����x          ������
*           y          ������
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ��Χ�޶�Ϊ����ʾ��ascii��
* ���÷�����ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;

  for (i=0;i<16;i++)
  {
    tmp_char=ascii_8x16[((c-0x20)*16)+i];
    for (j=0;j<8;j++)
    {
      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
        {
          ili9320_SetPoint(x+j,y+i,charColor); // �ַ���ɫ
        }
        else
        {
          ili9320_SetPoint(x+j,y+i,bkColor); // ������ɫ
        }
    }
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_Test()
* ��    �ܣ�����Һ����
* ��ڲ�������
* ���ڲ�������
* ˵    ������ʾ����������Һ�����Ƿ���������
* ���÷�����ili9320_Test();
****************************************************************************/
void ili9320_Test()
{
  u8  R_data,G_data,B_data,i,j;

	ili9320_SetCursor(0x00, 0x0000);
	ili9320_WriteRegister(0x0050,0x00);//ˮƽ GRAM��ʼλ��
	ili9320_WriteRegister(0x0051,239);//ˮƽGRAM��ֹλ��
	ili9320_WriteRegister(0x0052,0);//��ֱGRAM��ʼλ��
	ili9320_WriteRegister(0x0053,319);//��ֱGRAM��ֹλ��  
	Clr_Cs(); 
	ili9320_WriteIndex(0x0022);
	Set_Rs();
    R_data=0;G_data=0;B_data=0;     
    for(j=0;j<50;j++)//��ɫ��ǿ��
    {
        for(i=0;i<240;i++)
            {R_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();Set_nWr();}
    }
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();
			Set_nWr();
			}
    }
//----------------------------------
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<50;j++)//��ɫ��ǿ��
    {
        for(i=0;i<240;i++)
            {G_data=i/4;
			ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();
			Set_nWr();}
    }

    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            R_data=0x1f-(i/8);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();
			Set_nWr();
		}
    }
//----------------------------------
 
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<60;j++)//��ɫ��ǿ��
    {
        for(i=0;i<240;i++)
            {B_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();
			Set_nWr();}
    } 

    B_data=0; 
    R_data=0x1f;G_data=0x3f;B_data=0x1f;

    for(j=0;j<60;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            R_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			Clr_nWr();
			Set_nWr();
		}
    }	  
	Set_Cs();
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_BGR2RGB(u16 c)
* ��    �ܣ�RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
* ��ڲ�����c      BRG ��ɫֵ
* ���ڲ�����RGB ��ɫֵ
* ˵    �����ڲ���������
* ���÷�����
****************************************************************************/
u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}

/****************************************************************************
* ��    �ƣ�void ili9320_WriteIndex(u16 idx)
* ��    �ܣ�д ili9320 �������Ĵ�����ַ
* ��ڲ�����idx   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
* ���÷�����ili9320_WriteIndex(0x0000);
****************************************************************************/
__inline void ili9320_WriteIndex(u16 idx)
{
    Clr_Rs();
	Set_nRd();
	ili9320_WriteData(idx);
	Clr_nWr();
	Set_nWr();
	Set_Rs();
}

/****************************************************************************
* ��    �ƣ�void ili9320_WriteData(u16 dat)
* ��    �ܣ�д ili9320 �Ĵ�������
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ�����ǰ����д�Ĵ�����ַ���ڲ�����
* ���÷�����ili9320_WriteData(0x1030)
****************************************************************************/
void ili9320_WriteData(u16 data)
{
//	GPIOC->ODR = (GPIOC->ODR&0xff00)|(data&0x00ff);
//	GPIOB->ODR = (GPIOB->ODR&0x00ff)|(data&0xff00);

  GPIOB->BRR=GPIO_Pin_All;
  GPIOB->BSRR=data;
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_ReadData(void)
* ��    �ܣ���ȡ����������
* ��ڲ�������
* ���ڲ��������ض�ȡ��������
* ˵    �����ڲ�����
* ���÷�����i=ili9320_ReadData();
****************************************************************************/
__inline u16 ili9320_ReadData(void)
{
//========================================================================
// **                                                                    **
// ** nCS       ----\__________________________________________/-------  **
// ** RS        ------\____________/-----------------------------------  **
// ** nRD       -------------------------\_____/---------------------  **
// ** nWR       --------\_______/--------------------------------------  **
// ** DB[0:15]  ---------[index]----------[data]-----------------------  **
// **                                                                    **
//========================================================================
	u16 tmp;
	GPIOB->CRH = (GPIOB->CRH & 0x00000000) | 0x44444444;
	GPIOB->CRL = (GPIOC->CRL & 0x00000000) | 0x44444444;
	tmp = ((GPIOB->IDR&0xffff));
	GPIOB->CRH = (GPIOB->CRH & 0x00000000) | 0x33333333;
	GPIOB->CRL = (GPIOC->CRL & 0x00000000) | 0x33333333;
	return tmp;
}

/****************************************************************************
* ��    �ƣ�u16 ili9320_ReadRegister(u16 index)
* ��    �ܣ���ȡָ����ַ�Ĵ�����ֵ
* ��ڲ�����index    �Ĵ�����ַ
* ���ڲ������Ĵ���ֵ
* ˵    �����ڲ�����
* ���÷�����i=ili9320_ReadRegister(0x0022);
****************************************************************************/
__inline u16 ili9320_ReadRegister(u16 index)
{ 
  	Clr_Cs();
	ili9320_WriteIndex(index);
	Clr_nRd();     
	index = ili9320_ReadData(); 
	Set_nRd();      	

	Set_Cs();
	return index;
}

/****************************************************************************
* ��    �ƣ�void ili9320_WriteRegister(u16 index,u16 dat)
* ��    �ܣ�дָ����ַ�Ĵ�����ֵ
* ��ڲ�����index    �Ĵ�����ַ
*         ��dat      �Ĵ���ֵ
* ���ڲ�������
* ˵    �����ڲ�����
* ���÷�����ili9320_WriteRegister(0x0000,0x0001);
****************************************************************************/
__inline void ili9320_WriteRegister(u16 index,u16 dat)
{
 /************************************************************************
  **                                                                    **
  ** nCS       ----\__________________________________________/-------  **
  ** RS        ------\____________/-----------------------------------  **
  ** nRD       -------------------------------------------------------  **
  ** nWR       --------\_______/--------\_____/-----------------------  **
  ** DB[0:15]  ---------[index]----------[data]-----------------------  **
  **                                                                    **
  ************************************************************************/
//   u16 temp;
    Clr_Cs();
	Clr_Rs();
	Set_nRd();
	ili9320_WriteData(index);
//	temp=(*((volatile unsigned long *) 0x40010C0C));
//	(*((volatile unsigned long *) 0x40010C0C))=(index<<8)|(temp&0x00ff);
//	temp=(*((volatile unsigned long *) 0x4001100C));
//	(*((volatile unsigned long *) 0x4001100C))=(index>>8)|(temp&0xff00);
	Clr_nWr();
	Set_nWr();
	Set_Rs();       
	ili9320_WriteData(dat);  
//	temp=(*((volatile unsigned long *) 0x40010C0C));
//	(*((volatile unsigned long *) 0x40010C0C))=(dat<<8)|(temp&0x00ff);
//	temp=(*((volatile unsigned long *) 0x4001100C));
//	(*((volatile unsigned long *) 0x4001100C))=(dat>>8)|(temp&0xff00);     
	Clr_nWr();
	Set_nWr();
	Set_Cs();
}


//д����
void Lcd_WR_Reg(u16 data)
{
 Clr_Cs();
 Clr_Rs();       //ѡ������
 ili9320_WriteData(data);  //��ֵ
 Clr_nWr();
 Set_nWr();       //д�����ߵ�ƽ
 Set_Cs();
}

//д����
void Lcd_Write_Data(u16 data)
{
 Clr_Cs();
 Set_Rs();        //ѡ������
 ili9320_WriteData(data);  //��ֵ
 Clr_nWr();
 Set_nWr();      //д�����ߵ�ƽ
 Set_Cs();
}


/****************************************************************************
* ��    �ƣ�void ili9320_Reset()
* ��    �ܣ���λ ili9320 ������
* ��ڲ�������
* ���ڲ�������
* ˵    ������λ���������ڲ�����
* ���÷�����ili9320_Reset()
****************************************************************************/
void ili9320_Reset()
{
  /***************************************
   **                                   **
   **  -------\______________/-------   **
   **         | <---Tres---> |          **
   **                                   **
   **  Tres: Min.1ms                    **
   ***************************************/
    
//  	Set_Rst;;
//    ili9320_Delay(50000);
//  	Clr_Rst;
//    ili9320_Delay(50000);
//  	Set_Rst;
//    ili9320_Delay(50000);
}

/****************************************************************************
* ��    �ƣ�void ili9320_BackLight(u8 status)
* ��    �ܣ�������Һ������
* ��ڲ�����status     1:���⿪  0:�����
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_BackLight(1);
****************************************************************************/
void ili9320_BackLight(u8 status)
{
  if ( status >= 1 )
  {
    //Lcd_Light_ON;
  }
  else
  {
  //  Lcd_Light_OFF;
  }
}

/****************************************************************************
* ��    �ƣ�void ili9320_Delay(vu32 nCount)
* ��    �ܣ���ʱ
* ��ڲ�����nCount   ��ʱֵ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Delay(10000);
****************************************************************************/
void ili9320_Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
