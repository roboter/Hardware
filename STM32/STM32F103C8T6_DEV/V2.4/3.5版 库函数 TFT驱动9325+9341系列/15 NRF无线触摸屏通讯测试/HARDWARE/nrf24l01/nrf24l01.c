




#include "delay.h"
#include "nrf24l01.h"
#include "xpt2046.h"
#include "tft.h"
#include "spi.h"




u8 const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
u8 const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ





//��ʼ��NRF IO����
void NRF_IO_Init(void)
{	
  	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );//PORTBʱ��ʹ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;  // PC0 1 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);			  //���� ȡ��SPI����Ƭѡ


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;	      //PC2 ��������  ��IO�ж� NRF�Ƿ��иߵ�ƽ�ź�
    GPIO_Init(GPIOC, &GPIO_InitStructure);


	SPI_Cmd(SPI1, DISABLE); // SPI���費ʹ��			  NRF��SPIҪ��������һ��

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI����
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//���ͽ���8λ֡�ṹ

	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����


	CEN=0; 			//ʹ��24L01
	CSN=1;			//SPIƬѡȡ��  
}  





//��NRF��ȡһ���ֽ�����
//reg �Ĵ�����ַ
u8 SPI_Read(u8 reg)
{
	u8 reg_val;
	
	CSN = 0;                //Ƭѡʹ��  
    SPI1_ReadWriteByte(reg);
	reg_val = SPI1_ReadWriteByte(0xff);    // ��ȡ���ݵ�reg_val
	CSN = 1;                // ȡ��Ƭѡ
	
	return(reg_val);        // ���ض�ȡ������
}
   


//��NRFд��һ���ֽ�����
//reg �Ĵ�����ַ  value Ҫд�������
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI1_ReadWriteByte(reg);
    SPI1_ReadWriteByte(value);
	CSN = 1;                   // CSN high again
		
	return(status);            // return nRF24L01 status uchar
}



//��NRF��ȡ����ֽ�����
//reg �Ĵ�����ַ  *pBuf ��ȡ���ݴ洢ָ��  uchars ��ȡ���ֽڸ���
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction

	status = SPI1_ReadWriteByte(reg);
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)		  //ѭ�� uchars��
    pBuf[uchar_ctr] = SPI1_ReadWriteByte(0xff); 				  //�ֱ�	 SPI_RW(0)���������ݵ�ַ ����������
	
	CSN = 1;                           
	
	return status;                    // return nRF24L01 status uchar
}


//��NRFд�����ֽ�����
//reg �Ĵ�����ַ  *pBuf Ҫд�������  uchars д����ֽڸ���
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 status,uchar_ctr;
	
	CSN = 0;            //SPIʹ��       

	  status = SPI1_ReadWriteByte(reg);
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //	 �������ݸ���ѭ��							 
		SPI1_ReadWriteByte(*pBuf++);						//����������� ����д��

	CSN = 1;           //�ر�SPI
	return(status);    // 
}


//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
    SPI1_SetSpeed(SPI_BaudRatePrescaler_8);       //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	SPI_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);   //д��5���ֽڵĵ�ַ.	
	SPI_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}




//NRF�������ݺ���
//rx_buf  ���ݻ�����
//�ú������NRF״̬�Ĵ���״̬ �����ж������������ݵ�rx_buf������
u8 nRF24L01_RxPacket(u8 *rx_buf)
{	 
    u8 sta;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz�� 

	sta=SPI_Read(STATUS);	    // ��ȡ״̬�Ĵ������ж����ݽ���״��
	SPI_RW_Reg(WRITE_REG_NRF+STATUS,sta);   //���ж� �����յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־��
	if(sta&RX_OK)				// �ж��Ƿ���յ�����
	{

		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		SPI_RW_Reg(FLUSH_RX,0xff);

		return 0; 
	}
	
	return 1;
}


//��������tx_buf�е����ݷ��ͳ�ȥ
//tx_buf  Ҫ���͵����ݻ�����
u8 nRF24L01_TxPacket(u8 *tx_buf)
{	 
    u8 st;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz�� 
	CEN=0;			//StandBy Iģʽ	

	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	

	CEN=1;		 //�ø�CE���������ݷ���
	while(IRQ!=0);		   //�ȴ��������
	st=	SPI_Read(STATUS);			  //��NRF�Ĵ���״̬
	SPI_RW_Reg(WRITE_REG_NRF+STATUS,st);  //���ж�

		if(st&MAX_TX)//�ﵽ����ط�����
	{
		SPI_RW_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}

	if(st&TX_OK)				 //���ͳɹ�
	{
	return TX_OK;
	}
	return 0xff;

}


//NRF24L01��ʼ��
//m 1 ����ģʽ   0 ����ģʽ
void RX_TX_Mode(u8 m)	        //���� or ���� ģʽ ��ʼ��
{
 	CEN=0;    // chip enable
 	CSN=1;   // Spi disable 
	SPI_Write_Buf(WRITE_REG_NRF + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH);    // д���ص�ַ	
	SPI_Write_Buf(WRITE_REG_NRF + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ
	SPI_RW_Reg(WRITE_REG_NRF + EN_AA, 0x01);      //  Ƶ��0�Զ�	ACKӦ������	
	SPI_RW_Reg(WRITE_REG_NRF + EN_RXADDR, 0x01);  //  ������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21  
	SPI_RW_Reg(WRITE_REG_NRF + RF_CH, 0);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI_RW_Reg(WRITE_REG_NRF + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
	SPI_RW_Reg(WRITE_REG_NRF + RF_SETUP, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB

	if(m==1) SPI_RW_Reg(WRITE_REG_NRF + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	else if(m==0) SPI_RW_Reg(WRITE_REG_NRF + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������

	CEN=1;
}



///*
//nrf24c04 ���Ժ���	  �˺���֧��ѡ���� ���չ��� 
//�ڷ���˴��������Ϸ����������� 
//����˵�л��߳��� ͬʱ���ڽ��ջ�������ʾ
//*/
//void nrf24()
//{
//  struct TFT_Pointer Tp_pix;      	 //�������庯��
//
//  u8 Buf[3],						 //��������
//     t,								 //��ʱ����
//	 mode=1;							 //ģʽ��־λ   Ĭ��Ϊ����ģʽ
//  u16 pix,piy;						 //��ʱ����	   ���ڴ�����յ�������
//
//
//  Dialog_box(70,120,170,200,window,Red,window,"  ģʽѡ��");	  //������˵���ľ��ͶԻ���
//
//  GUI_arc(80,149,6,Blue,0);						 //��ѡ��ԲȦ��
//  GUI_arc(80,149,4,Red3,1);						 //Ĭ��ѡ����ģʽ
//  GUI_arc(80,167,6,Blue,0);
//
//  GUI_sprintf_hzstr16x(96,141,"����ģʽ",Black,1);//ѡ��˵��
//  GUI_sprintf_hzstr16x(96,159,"����ģʽ",Black,1);
//
//  Touch_key(130,180,Blue2,Blue,0);    //ȷ����ť��
//
//  while(1)
//  {	      
//    Tp_pix=TFT_Cm();	                   //ɨ�败����
//    if(Tp_pix.flag==1)                     //�Ƿ��д����¼�  
//     {
//      if(Tp_pix.x>96&&Tp_pix.x<164) 
//       {
//   	    if(Tp_pix.y>141&&Tp_pix.y<157)     //����
//	     {
//	      GUI_arc(80,167,4,White,1);	   //�� ѡ���
//	      GUI_arc(80,149,4,Red3,1);		   //�� ѡ���
//	      mode=1;					       //����  	 
//	     }
//	    if(Tp_pix.y>159&&Tp_pix.y<178)	   //����
//	     {
//	      GUI_arc(80,149,4,White,1);	   //�� ѡ���
//	      GUI_arc(80,167,4,Red3,1);		   //�� ѡ���
//	      mode=0;					       //����
//	     }   
//       }
//      if(Tp_pix.x>130&&Tp_pix.x<164&&Tp_pix.y>180&&Tp_pix.y<200) break;	   //ȷ������
//     }
//  }
//  GUI_Clear(White);	   //��������
//  tian(1);//���
//
//  if(mode==0)	       //�������ģʽ
//  {
//    GUI_sprintf_hzstr16x(0,0,"����ģʽ",White,1);
//	    
//	RX_Mode();	           //����ģʽ��ʼ��
//
// 	while(1)
//	{
//	 led=1;				  //��led  
//	 if(nRF24L01_RxPacket(Buf)==0)		   //�ɼ����� 
//	  {				
//			  
//		   pix=Buf[0];			   //�������� ��Ļ�ֱ���Ϊ320X240 һ�ֽ������װ255  320���� ����һ���ֽ����Է����ֽ�װ����
//		   piy=(Buf[1]<<8)+Buf[2];
//           Address_set(pix,piy,pix+2,piy+2,pix,piy);			//3*3����Ϊһ����Ԫ��
//		   for(t=0;t<9;t++)				
//			Lcd_Write_Data(Red);										
//
//		   led=0;									 //ָʾ���ж��Ƿ���յ�����
//	       delay1ms(10);								//С��ʱ
//       }
//	      
//	  Tp_pix=TFT_Cm();	                            // ɨ�败����
//      if(Tp_pix.flag==1)                              //�Ƿ��д����¼� ���� 	   
//	    if(Tp_pix.x>=200&&Tp_pix.x<=239&&Tp_pix.y>=295&&Tp_pix.y<=320){led=1;Return();break;}
//	  
//	 }
//  }
//
//
//  if(mode==1)	       //���뷢��ģʽ
//  {
//	GUI_sprintf_hzstr16x(0,0,"����ģʽ",White,1);
//	 
//	TX_Mode();			 //����ģʽ��ʼ��
//	
//   	while(1)
//	 {	
//       Tp_pix=TFT_Cm();	                            // ɨ�败����
//       if(Tp_pix.flag==1)                              //�Ƿ��д����¼� ���� 
//		{
//		  if(Tp_pix.y>=20&&Tp_pix.y<=302)		//�ж� ��ǰֵ �Ƿ���Ԥ��� ��ͼ����
//	      {
//																			//�趨��ͼλ�� 
//			Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2,Tp_pix.x,Tp_pix.y);			//3*3����Ϊһ����Ԫ��	
//		    for(t=0;t<9;t++)				
//			 Lcd_Write_Data(Red);
//	
//	
//			Buf[0]= Tp_pix.x;                               //����ǰ������λ�ô��������� 
//			Buf[2]= Tp_pix.y;
//			Buf[1]= Tp_pix.y>>8;
//	
//	        nRF24L01_TxPacket(Buf);	//��������	
//	        delay1ms(10);	
//		  }
//		if(Tp_pix.x>=200&&Tp_pix.x<=239&&Tp_pix.y>=295&&Tp_pix.y<=320){Return();break;}
//	    }
//
//	  }
//
//  }
//}








