



#ifndef SD_H
#define SD_H
#include "stm32f10x.h"


//TF卡片选  IO  PA4
#define	SD_CS_0  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define SD_CS_1    GPIO_SetBits(GPIOA,GPIO_Pin_4)






//错误码定义
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0错误
#define INIT_CMD1_ERROR     0x02 //CMD1错误
#define WRITE_BLOCK_ERROR   0x03 //写块错误
#define READ_BLOCK_ERROR    0x04 //读块错误
//-------------------------------------------------------------




// SD卡类型定义  
#define SD_TYPE_ERR     0X00
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06

//SD传输数据结束后是否释放总线宏定义  
#define NO_RELEASE      0
#define RELEASE         1	


//SD卡回应标记字
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF	 

// SD卡指令表  	   
#define CMD0    0       //卡复位
#define CMD1    1
#define CMD8    8       //命令8 ，SEND_IF_COND
#define CMD9    9       //命令9 ，读CSD数据
#define CMD10   10      //命令10，读CID数据
#define CMD12   12      //命令12，停止数据传输
#define CMD16   16      //命令16，设置SectorSize 应返回0x00
#define CMD17   17      //命令17，读sector
#define CMD18   18      //命令18，读Multi sector
#define CMD23   23      //命令23，设置多sector写入前预先擦除N个block
#define CMD24   24      //命令24，写sector
#define CMD25   25      //命令25，写Multi sector
#define CMD41   41      //命令41，应返回0x00
#define CMD55   55      //命令55，应返回0x01
#define CMD58   58      //命令58，读OCR信息
#define CMD59   59      //命令59，使能/禁止CRC，应返回0x00


u8 SD_WaitReady(void);						//等待SD卡准备
u8 SD_Init(void);							//初始化
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc);		//写命令
void SD_DisSelect(void);					//释放片选
u32 SD_GetCapacity(void);                   //获取SD卡的容量（字节）  

#define TRY_TIME 10    //向SD卡写入命令之后，读取SD卡的回应次数，即读TRY_TIME次，如果在TRY_TIME次中读不到回应，产生超时错误，命令写入失败




u8  SD_read_sector(u32 Sector_NUM,u8 *Tmp_Buffer);	   //指定扇区 读取512字节数据
//u8 SD_read_Byte(u32 addr,u8 *buf,u32 Bytes);

#endif
