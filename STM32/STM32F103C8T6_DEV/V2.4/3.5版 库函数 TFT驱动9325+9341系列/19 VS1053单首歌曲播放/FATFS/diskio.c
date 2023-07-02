/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2009   
   �Ͷ˵Ĵ���I/Oģ��Ǽ�Petit FatFs��C����2009   */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "stm32f10x.h"
#include "spi.h"
#include "sd.h"




/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive      
   ��ʼ������������    
   ����0 Ϊ�ɹ�  ����1 Ϊʧ��                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	DSTATUS stat;

	// Put your code here	   ����Ĵ���д������
	 stat=SD_Init();	  //��ʼ��SD�� ��������ֵ��stat


	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector
   ������                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* dest,			/* Pointer to the destination object ������ݵĵ�ַ*/
	DWORD sector,		/* Sector number (LBA)  Ҫ����������*/
	WORD sofs,			/* Offset in the sector ����ƫ��ֵ*/
	WORD count			/* Byte count (bit15:destination) ���������ݸ���*/
)
{
	DRESULT res;

	// Put your code here	 ����Ĵ���д������

	u16 tmp,i;
	u8 r1;
    res=RES_ERROR;

	r1=SD_SendCmd(CMD17,sector<<9,0X01);//������
	
	if(r1==0)//ָ��ͳɹ�
		{
		    while(SPI1_ReadWriteByte(0xff)!=0xfe);  //�ȴ���������
			 if(sofs)  //�����ƫ����
			 {		  
			 for(i=0;i<sofs;i++)SPI1_ReadWriteByte(0xff);  //��ƫ��ֵѭ����
			 			      
			 for(i=0;i<count;i++) *(dest++)=SPI1_ReadWriteByte(0xff);  //����Ҫ������������		   
			 }
			 else   //û��ƫ��ֵ ��ƫ��ֵΪ0
			 {
			   //Ҫ�������ݸ������Ƹ�tmp
			   for(i=0;i<count;i++) *(dest++)=SPI1_ReadWriteByte(0xff);  //����Ҫ������������
			 }
			 tmp=512-sofs-count;  //ʣ��Ϊ������   ������-ƫ��ֵ-��ȡ����
			 for(i=0;i<tmp;i++)SPI1_ReadWriteByte(0xff);// ��ʣ������ѭ���� ��������������и���


			//������2��αCRC��dummy CRC��
			  SPI1_ReadWriteByte(0xff); 
              SPI1_ReadWriteByte(0xff); 		   
		}
	  else  return res;	 //��ָ��ʧ��

	SD_DisSelect();//ȡ��Ƭѡ
	res=RES_OK;	   //���ݶ�ȡ�ɹ�
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector 
   д����                                                 
   
   disk_writep��д��������������ֻ������������
   д������ݵ�ַ* buff��ڼ�������sc�������ݡ�

   ���ڱ�д��������ʱ��Ҫע�⣬����FatFs�ڲ����ú�������Ҫ�����밴�����µ�˳������
   �� buff ָ��һ����ָ�룬��sc ��Ϊ0 ʱ�����ʾ�����������д�������г�ʼ����
   ��sc Ϊ0 ʱ�����ʾ�����������д�������н���������
   �� buff ָ��һ���ڴ滺���������ǽ��������Ķ�д��*/
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation ָ������ݱ�д�룬�գ�����/���д����*/
	DWORD sc		/* Sector number (LBA) or Number of bytes to send ��������LBA����Ҫ���͵��ֽ���*/
)
{
	DRESULT res;

	 u8 r1;
	 u16 t;
	 u32 m;
	res = RES_ERROR;

	if (!buff) {						  //���ָ���ָ��
		if (sc) {						  //sc��Ϊ0 ����д������ʼ��

			// Initiate write process		  ��ʼд����
				  r1=SD_SendCmd(CMD24,sc<<9,0X01);
				  if(r1!=0) return res;	 //Ӧ����ȷ
			      do
		          {
			        if(SPI1_ReadWriteByte(0XFF)==0XFF)break;//OK	  �ſ����ݵȴ�SD��׼����
			          m++;		  	
		           }while(m<0XFFFFFF);//�ȴ� 
	
		          SPI1_ReadWriteByte(0XFE);		  //��������
				  res=RES_OK;

		} else {							 //scΪ0  ��ʾд��������

			// Finalize write process		  ���д����

		           	//������2��αCRC��dummy CRC��
				 	SPI1_ReadWriteByte(0xFF);
					SPI1_ReadWriteByte(0xFF);
					r1 = SPI1_ReadWriteByte(0xFF);
		
					if( (r1&0x1f) != 0x05)//�ȴ�SD��Ӧ��
					{
						SD_DisSelect();
						return res;
					}
					//�ȴ�������
					while(!SPI1_ReadWriteByte(0xFF));
		
					SD_DisSelect();	
					res = RES_OK;




		}
	} else {

		// Send data to the disk			  �������ݵ�����
			for(t=0;t<512;t++)SPI1_ReadWriteByte(*buff++);//����ٶ�,���ٺ�������ʱ��
		    res = RES_OK;


	}

	return res;
}

