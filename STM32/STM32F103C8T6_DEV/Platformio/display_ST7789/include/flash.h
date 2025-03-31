#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x.h"
//#include "sys.h"  // Assuming this contains type definitions like u8, u16, u32

/* W25X/Q Series Chip IDs */
#define W25Q80     0xEF13
#define W25Q16     0xEF14
#define W25Q32     0xEF15
#define W25Q64     0xEF16

/* Flash Chip Select Control (PC13) */
#define SPI_FLASH_CS_0    GPIO_ResetBits(GPIOC, GPIO_Pin_13)  /* Activate CS (low) */
#define SPI_FLASH_CS_1    GPIO_SetBits(GPIOC, GPIO_Pin_13)    /* Deactivate CS (high) */

/* Command Definitions */
#define W25X_WriteEnable          0x06
#define W25X_WriteDisable         0x04
#define W25X_ReadStatusReg        0x05
#define W25X_WriteStatusReg       0x01
#define W25X_ReadData             0x03
#define W25X_FastReadData         0x0B
#define W25X_FastReadDual         0x3B
#define W25X_PageProgram          0x02
#define W25X_BlockErase           0xD8
#define W25X_SectorErase          0x20
#define W25X_ChipErase            0xC7
#define W25X_PowerDown            0xB9
#define W25X_ReleasePowerDown     0xAB
#define W25X_DeviceID             0xAB
#define W25X_ManufactDeviceID     0x90
#define W25X_JedecDeviceID        0x9F

/* Function Prototypes */
void SPI_Flash_Init(void);                              /* Initialize SPI Flash interface */
u16  SPI_Flash_ReadID(void);                            /* Read Flash Device ID */
u8   SPI_Flash_ReadSR(void);                            /* Read Status Register */
void SPI_FLASH_Write_SR(u8 sr);                         /* Write Status Register */
void SPI_FLASH_Write_Enable(void);                      /* Enable Write Operations */
void SPI_FLASH_Write_Disable(void);                     /* Disable Write Operations */
void SPI_Flash_Write_NoCheck(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);  /* Unchecked write */
void SPI_Flash_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);             /* Read data from Flash */
void SPI_Flash_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);          /* Write data to Flash */
void SPI_Flash_Erase_Chip(void);                        /* Perform full chip erase */
void SPI_Flash_Erase_Sector(u32 Dst_Addr);              /* Erase 4KB sector */
void SPI_Flash_Wait_Busy(void);                         /* Wait until flash is ready */
void SPI_Flash_PowerDown(void);                         /* Enter low-power mode */
void SPI_Flash_WAKEUP(void);                            /* Wake up from power-down */

#endif /* __FLASH_H */