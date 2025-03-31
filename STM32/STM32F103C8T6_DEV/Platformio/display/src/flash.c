#include "flash.h"
#include "stm32f10x_spi.h"
#include "delay.h"
#include "led.h"

/* SPI Flash Memory Organization (W25X16) */
// 4KB per Sector
// 16 Sectors = 1 Block (64KB)
// Total capacity: 2MB (32 Blocks, 512 Sectors)

/**
 * @brief  Initializes SPI Flash GPIO and interface
 * @note   Configures CS pin and SPI peripheral
 */
void SPI_Flash_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable GPIOC clock

    // Configure CS pin (PC13)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_13); // CS high (inactive)

    SPI1_Init();                            // Initialize SPI interface
    SPI1_SetSpeed(SPI_BaudRatePrescaler_2); // Set SPI clock to 18MHz (assuming 72MHz system clock)
}

/**
 * @brief  Reads Status Register
 * @return Status register value
 * @note   Bit definitions:
 *         [7] SPR: Status Register Protect (WP pin control)
 *         [6:5] Reserved
 *         [4:2] BP[2:0]: Block Protect bits
 *         [1] WEL: Write Enable Latch
 *         [0] BUSY: Erase/Write in progress
 */
u8 SPI_Flash_ReadSR(void)
{
    u8 status = 0;
    SPI_FLASH_CS_0;                         // Activate CS
    SPI1_ReadWriteByte(W25X_ReadStatusReg); // Send read status command
    status = SPI1_ReadWriteByte(0xFF);      // Read status byte
    SPI_FLASH_CS_1;                         // Deactivate CS
    return status;
}

/**
 * @brief  Writes Status Register
 * @param  sr: Status register value to write
 * @note   Only SPR, BP[2:0] bits are writable
 */
void SPI_FLASH_Write_SR(u8 sr)
{
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_WriteStatusReg); // Send write status command
    SPI1_ReadWriteByte(sr);                  // Write new status
    SPI_FLASH_CS_1;
}

/**
 * @brief  Enables write operations
 */
void SPI_FLASH_Write_Enable(void)
{
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_WriteEnable); // Send write enable command
    SPI_FLASH_CS_1;
}

/**
 * @brief  Disables write operations
 */
void SPI_FLASH_Write_Disable(void)
{
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_WriteDisable); // Send write disable command
    SPI_FLASH_CS_1;
}

/**
 * @brief  Reads Flash Device ID
 * @return Device ID (0xEF14 for W25X16)
 */
u16 SPI_Flash_ReadID(void)
{
    u16 id = 0;
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(0x90); // Send read ID command
    SPI1_ReadWriteByte(0x00); // Dummy cycles
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    id = SPI1_ReadWriteByte(0xFF) << 8; // Read Manufacturer ID
    id |= SPI1_ReadWriteByte(0xFF);     // Read Device ID
    SPI_FLASH_CS_1;
    return id;
}

/**
 * @brief  Reads data from Flash
 * @param  pBuffer: Pointer to data buffer
 * @param  ReadAddr: Starting address (24-bit)
 * @param  NumByteToRead: Number of bytes to read (max 65535)
 */
void SPI_Flash_Read(u8 *pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
    u16 i;
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_ReadData);        // Send read command
    SPI1_ReadWriteByte((u8)(ReadAddr >> 16)); // Send address MSB
    SPI1_ReadWriteByte((u8)(ReadAddr >> 8));  // Send address middle byte
    SPI1_ReadWriteByte((u8)ReadAddr);         // Send address LSB
    for (i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI1_ReadWriteByte(0xFF); // Read data
    }
    SPI_FLASH_CS_1;
}

/* Additional functions follow the same commenting pattern... */

/**
 * @brief  Erases entire chip
 * @note   Takes significant time (25s for W25X16)
 */
void SPI_Flash_Erase_Chip(void)
{
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_ChipErase); // Send chip erase command
    SPI_FLASH_CS_1;
    SPI_Flash_Wait_Busy(); // Wait for completion
}

/**
 * @brief  Enters deep power-down mode
 */
void SPI_Flash_PowerDown(void)
{
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_PowerDown); // Send power-down command
    SPI_FLASH_CS_1;
    delay_us(3); // Wait for Tpd (typical 3μs)
}

/**
 * @brief  Wakes up from power-down
 */
void SPI_Flash_WAKEUP(void)
{
    SPI_FLASH_CS_0;
    SPI1_ReadWriteByte(W25X_ReleasePowerDown); // Send wakeup command
    SPI_FLASH_CS_1;
    delay_us(3); // Wait for Tres1 (typical 3μs)
}