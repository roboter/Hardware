

#include "sd.h"
#include "spi.h"
#include "delay.h"



u8  SD_Type=0;//SD�������� 



//TF��ƬѡIO���� ��ʼ��
//TF��������λ��Ϊ�������׵�TFT����
//����STM32  SPI1 ����
//���õ�ƬѡIOΪ  PA4
void SD_CS_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;					 //����GPIO�ṹ��
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			    //LED-->PA.4 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA.4
 GPIO_SetBits(GPIOA,GPIO_Pin_4);						//����ƬѡIO

}



///////////////////////////////////////////////////////////////////////////////////


//�ȴ���׼����
//����ֵ:0,׼������;����,�������
u8 SD_WaitReady(void)
{
	u32 t=0;
	do
	{
		if(SPI1_ReadWriteByte(0XFF)==0XFF)return 0;//OK
		t++;		  	
	}while(t<0XFFFFFF);//�ȴ� 
	return 1;
}

//ȡ��ѡ��,�ͷ�SPI����
void SD_DisSelect(void)
{
	SD_CS_1;
 	SPI1_ReadWriteByte(0xff);//�ṩ�����8��ʱ��
}

//ѡ��sd��,���ҵȴ���׼��OK
//����ֵ:0,�ɹ�;1,ʧ��;
u8 SD_Select(void)
{
	SD_CS_0;
	if(SD_WaitReady()==0)return 0;//�ȴ��ɹ�
	SD_DisSelect();
	return 1;//�ȴ�ʧ��
}

//��SD������һ������
//����: u8 cmd   ���� 
//      u32 arg  �������
//      u8 crc   crcУ��ֵ	   
//����ֵ:SD�����ص���Ӧ															  
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc)
{
    u8 r1;	
	u8 Retry=0; 

	SD_DisSelect();//ȡ���ϴ�Ƭѡ
	if(SD_Select())return 0XFF;//ƬѡʧЧ 


	//����
	SD_CS_1;		                                //Ƭѡ����																		 
	SPI1_ReadWriteByte(0xff);
	SPI1_ReadWriteByte(0xff);	 
	SPI1_ReadWriteByte(0xff);							    
	SD_CS_0; 

    SPI1_ReadWriteByte(cmd | 0x40);       //�ֱ�д������	λ6�̶�Ϊ1  
    SPI1_ReadWriteByte(arg >> 24);		//������� 2-5�ֽ�  4���ֽ� 32λ
    SPI1_ReadWriteByte(arg >> 16);
    SPI1_ReadWriteByte(arg >> 8);
    SPI1_ReadWriteByte(arg);	  
    SPI1_ReadWriteByte(crc); 
	                                 //ֹͣ����������
	if(cmd==CMD12)SPI1_ReadWriteByte(0xff);//Skip a stuff byte when stop reading
    //�ȴ���Ӧ����ʱ�˳�
	Retry=0X1F;		   //ѭ��32��
	do
	{
		r1=SPI1_ReadWriteByte(0xFF);
	}while((r1&0X80) && Retry--);	 
	//����״ֵ̬
    return r1;
}







//��ʼ��SD��
u8 SD_Init(void)
{
    u8 r1;      // ���SD���ķ���ֵ
    u16 retry;  // �������г�ʱ����
    u8 buf[4];  
	u8 i;

	SD_CS_Init();      //����spiƬѡIO

	
 	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);		//���õ�����ģʽ 

 	for(i=0;i<10;i++)SPI1_ReadWriteByte(0XFF);//��������74������ �ȴ�SD���ڲ������ѹ����ʱ��	  ����SPIģʽ

	
	retry=20;
	do
	{
		r1=SD_SendCmd(CMD0,0,0x95);//����IDLE״̬ 	 ����λsd�� ����״̬
	}while((r1!=0X01) && retry--);

	 
 	SD_Type=0;//Ĭ���޿�
	 
	if(r1==0X01)   //��ȡ�汾��Ϣ
	{	
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0	  ���ͽӿ�״̬����		                                  
		{							      //�������ֵΪ1 ���� SDV2.0�汾
			for(i=0;i<4;i++)buf[i]=SPI1_ReadWriteByte(0XFF);	//Get trailing return value of R7 resp
														//��ȡ����ֵR7����
			if(buf[2]==0X01&&buf[3]==0XAA)//���Ƿ�֧��2.7~3.6V
			{  
				retry=0XFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	//����CMD55
					r1=SD_SendCmd(CMD41,0x40000000,0X01);//����CMD41
				}while(r1&&retry--);
				if(retry&&SD_SendCmd(CMD58,0,0X01)==0)//����SD2.0���汾��ʼ
				{	
					for(i=0;i<4;i++)buf[i]=SPI1_ReadWriteByte(0XFF);//�õ�OCRֵ
					if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //���CCS
					else SD_Type=SD_TYPE_V2;  					     						
				}
				else SD_Type=SD_TYPE_ERR;//����Ŀ�
			}
		}
	
	}

	SD_DisSelect();//ȡ��Ƭѡ
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);;//����	
	if(SD_Type)return 0;	//���û�вɼ���SD���汾 ����������
	else if(r1)return r1; 	   
	return 0xaa;//��������
}




//��ָ��������SD��һ�������� ��512�ֽ�
//buf:���ݻ�����
//sector:����
//����ֵ:0,ok;����,ʧ��. 
u8 SD_read_sector(u32 sector,u8 *buf) 
{ 
    u16 i;
	u8 r1;
	SD_DisSelect();//ȡ���ϴ�Ƭѡ
 	if(SD_Select())return 0XFF;//ƬѡʧЧ 

    if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;//ת��Ϊ�ֽڵ�ַ


    r1=SD_SendCmd(CMD17,sector,0X01);//������
		if(r1==0)//ָ��ͳɹ�
		{
		    while(SPI1_ReadWriteByte(0xff)!=0xfe);
			 for(i=0;i<512;i++) 
			    {
			   //��������һ�������� 
			    buf[i]=SPI1_ReadWriteByte(0xff);  
			    }
			 //������2��αCRC��dummy CRC��
			  SPI1_ReadWriteByte(0xff); 
              SPI1_ReadWriteByte(0xff); 		   
		}


	SD_DisSelect();//ȡ��Ƭѡ
	return r1;//

} 

////дSD��д��512�ֽ�����
////buf:���ݻ�����
////sector:��ʼ����
////����ֵ:0,ok;����,ʧ��.
//u8 SD_WriteDisk(u8*buf,u32 sector)
//{
//	u8 r1;
//	u16 t;
//    sector *= 512;//ת��Ϊ�ֽڵ�ַ
//
//	r1=SD_SendCmd(CMD24,sector,0X01);//������
//	if(r1==0)//ָ��ͳɹ�
//	{
//
//     if(SD_WaitReady()){SD_DisSelect();return 1;}//�ȴ�׼��ʧЧ
//	 SPI1_ReadWriteByte(0xFE); //��������
//
//	 for(t=0;t<512;t++)SPI1_ReadWriteByte(buf[t]);//д�ֽ�
//	 SPI1_ReadWriteByte(0xFF);    //����crc
//	 SPI1_ReadWriteByte(0xFF);
//	 t=SPI1_ReadWriteByte(0xFF);  //������Ӧ
//	 if((t&0x1F)!=0x05)r1=2;//��Ӧ����									  					    
//	 	 	   
//	}
//
//
//	SD_DisSelect();//ȡ��Ƭѡ
//	return r1;
//}


/*************************************************************************************
����������ڵĺ��� ��Ҫ��������ȡSD��������
������ڲ��ÿ���ֱ��ȥ��
*************************************************************************************/


//�ȴ�SD����Ӧ
//Response:Ҫ�õ��Ļ�Ӧֵ
//����ֵ:0,�ɹ��õ��˸û�Ӧֵ
//    ����,�õ���Ӧֵʧ��
u8 SD_GetResponse(u8 Response)
{
	u16 Count=0xFFF;//�ȴ�����	   						  
	while ((SPI1_ReadWriteByte(0XFF)!=Response)&&Count)Count--;//�ȴ��õ�׼ȷ�Ļ�Ӧ  	  
	if (Count==0)return MSD_RESPONSE_FAILURE;//�õ���Ӧʧ��   
	else return MSD_RESPONSE_NO_ERROR;//��ȷ��Ӧ
}



//��SD���ж���ָ�����ȵ����ݣ������ڸ���λ��
//����: u8 *data(��Ŷ������ݵ��ڴ�>len)
//      u16 len(���ݳ��ȣ�
//      u8 release(������ɺ��Ƿ��ͷ�����CS�ø� 0�����ͷ� 1���ͷţ�	 
//����ֵ:0��NO_ERR
//  	 other��������Ϣ														  
u8 SD_ReceiveData(u8 *dat, u16 len, u8 release)
{
    // ����һ�δ���
    SD_CS_0;				  	  
	if(SD_GetResponse(0xFE))//�ȴ�SD������������ʼ����0xFE
	{	  
		SD_CS_1;
		return 1;
	}
    while(len--)//��ʼ��������
    {
        *dat=SPI1_ReadWriteByte(0xFF);
        dat++;
    }
    //������2��αCRC��dummy CRC��
    SPI1_ReadWriteByte(0xFF);
    SPI1_ReadWriteByte(0xFF);
    if(release==RELEASE)//�����ͷ����ߣ���CS�ø�
    {
        SD_CS_1;//�������
        SPI1_ReadWriteByte(0xFF);
    }											  					    
    return 0;
}


//��ȡSD����CSD��Ϣ�������������ٶ���Ϣ
//����:u8 *cid_data(���CID���ڴ棬����16Byte��	    
//����ֵ:0��NO_ERR
//       1��TIME_OUT
//       other��������Ϣ														   
u8 SD_GetCSD(u8 *csd_data)
{
    u8 r1;	 
    r1=SD_SendCmd(CMD9,0,0xFF);//��CMD9�����CSD
    if(r1)return r1;  //û������ȷӦ�����˳�������  
    SD_ReceiveData(csd_data, 16, RELEASE);//����16���ֽڵ����� 
    return 0;
}  


//��ȡSD�����������ֽڣ�   
//����ֵ:0�� ȡ�������� 
//       ����:SD��������(�ֽ�)														  
u32 SD_GetCapacity(void)
{
    u8 csd[16];
    u32 Capacity;
	u8 r1;
    u16 i;
	u16 temp;  						    
	//ȡCSD��Ϣ������ڼ��������0
    if(SD_GetCSD(csd)!=0) return 0;	    
    //���ΪSDHC�����������淽ʽ����
    if((csd[0]&0xC0)==0x40)
    {									  
	    Capacity=((u32)csd[8])<<8;
		Capacity+=(u32)csd[9]+1;	 
        Capacity = (Capacity)*1024;//�õ�������
		Capacity*=512;//�õ��ֽ���			   
    }
    else
    {		    
    	i = csd[6]&0x03;
    	i<<=8;
    	i += csd[7];
    	i<<=2;
    	i += ((csd[8]&0xc0)>>6);
        //C_SIZE_MULT
    	r1 = csd[9]&0x03;
    	r1<<=1;
    	r1 += ((csd[10]&0x80)>>7);	 
    	r1+=2;//BLOCKNR
    	temp = 1;
    	while(r1)
    	{
    		temp*=2;
    		r1--;
    	}
    	Capacity = ((u32)(i+1))*((u32)temp);	 
        // READ_BL_LEN
    	i = csd[5]&0x0f;
        //BLOCK_LEN
    	temp = 1;
    	while(i)
    	{
    		temp*=2;
    		i--;
    	}
        //The final result
    	Capacity *= (u32)temp;//�ֽ�Ϊ��λ 	  
    }

    return (u32)Capacity;
}

/*************************************************************************************
**************************************************************************************
*************************************************************************************/



//��ָ������дSD��һ�������� ��512�ֽ�
//buf:���ݻ�����
//sector:��ʼ����
//cnt:������
//����ֵ:0,ok;����,ʧ��.
//u8 SD_write_sector(u32 sector,u8*buf)
//{
//	u8 r1;
//	u16 t;
//	u32 m=0;
//	if(SD_Type!=SD_TYPE_V2HC)sector *= 512;//ת��Ϊ�ֽڵ�ַ
//
//	 r1=SD_SendCmd(CMD24,sector,0X01);//������
//		if(r1==0)//ָ��ͳɹ�
//		{
//			//r1=SD_SendBlock(buf,0xFE);//д512���ֽ�	 
//			 //�ȴ���׼������	
//	          do
//	          {
//		        if(SPI1_ReadWriteByte(0XFF)==0XFF)break;//OK
//		          m++;		  	
//	           }while(m<0XFFFFFF);//�ȴ� 
//
//	          SPI1_ReadWriteByte(0XFE);
//			  
//				for(t=0;t<512;t++)SPI1_ReadWriteByte(buf[t]);//����ٶ�,���ٺ�������ʱ��
//			    SPI1_ReadWriteByte(0xFF);//����crc
//			    SPI1_ReadWriteByte(0xFF);
//				t=SPI1_ReadWriteByte(0xFF);//������Ӧ
//				if((t&0x1F)!=0x05)return 2;//��Ӧ����									  					    
//		}
//	SD_DisSelect();//ȡ��Ƭѡ
//	return 0;  //д��ɹ�
//
//					
//}



//��ָ����ַ ��ȡ ָ���ֽ���
//addr:��ַ
//buf:���ݻ�����
//Bytes��Ҫ��ȡ���ֽ���
//����ֵ:0,ok;����,ʧ��.   
//u8 SD_read_Byte(u32 addr,u8 *buf,u32 Bytes) 
//{ 
//    u16 i;
//    u8 temp=0,retry;
//
//    // ����16���ÿ鳤�� 
//    SD_SendCmd(16,Bytes,0xff); 
//
//    retry = 0;
//
//    do
//    {
//    // д��CMD17 	��ȡ����
//    temp=SD_SendCmd(17,addr,0xff);
//    retry++;
//    }
//		
//	while((temp!=0x00) && (retry < TRY_TIME)); 
//
//	
//    if (retry >= TRY_TIME) 
//    {
//    return READ_BLOCK_ERROR; 
//    }
//
//    // ����0xfe��ͷ  
//    while(SPI1_ReadWriteByte(0xff)!=0xfe);
//
//     for(i=0;i<Bytes;i++) 
//    {
//
//        //��������ָ�� �����ֽ����ݵ�buf
//        buf[i] = SPI1_ReadWriteByte(0xff);  
//    }
//
//   //������2��αCRC��dummy CRC��
//    SPI1_ReadWriteByte(0xff); 
//    SPI1_ReadWriteByte(0xff);  
//
//
//    //* ����16�ָ��鳤�� Ϊ512���ֽ�
//    SD_SendCmd(16,512,0xff);
//	SD_DisSelect();//ȡ��Ƭѡ
//    
//    return 0; 
//
//} 


