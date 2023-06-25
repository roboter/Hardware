



#ifndef SD_H
#define SD_H
#include "stm32f10x.h"


//TF��Ƭѡ  IO  PA4
#define	SD_CS_0  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define SD_CS_1    GPIO_SetBits(GPIOA,GPIO_Pin_4)






//�����붨��
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0����
#define INIT_CMD1_ERROR     0x02 //CMD1����
#define WRITE_BLOCK_ERROR   0x03 //д�����
#define READ_BLOCK_ERROR    0x04 //�������
//-------------------------------------------------------------




// SD�����Ͷ���  
#define SD_TYPE_ERR     0X00
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06

//SD�������ݽ������Ƿ��ͷ����ߺ궨��  
#define NO_RELEASE      0
#define RELEASE         1	


//SD����Ӧ�����
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF	 

// SD��ָ���  	   
#define CMD0    0       //����λ
#define CMD1    1
#define CMD8    8       //����8 ��SEND_IF_COND
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define CMD23   23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define CMD41   41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00


u8 SD_WaitReady(void);						//�ȴ�SD��׼��
u8 SD_Init(void);							//��ʼ��
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc);		//д����
void SD_DisSelect(void);					//�ͷ�Ƭѡ
u32 SD_GetCapacity(void);                   //��ȡSD�����������ֽڣ�  

#define TRY_TIME 10    //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��




u8  SD_read_sector(u32 Sector_NUM,u8 *Tmp_Buffer);	   //ָ������ ��ȡ512�ֽ�����
//u8 SD_read_Byte(u32 addr,u8 *buf,u32 Bytes);

#endif
