#ifndef MAIN_H
#define MAIN_H
#include <ch32v00x_i2c.h>
#include <stddef.h>

#define BUTTONPORT GPIOC 
#define UP		GPIO_Pin_7
#define RIGHT GPIO_Pin_6
#define LEFT	GPIO_Pin_5
#define DOWN	GPIO_Pin_4
#define ENTER GPIO_Pin_3

#define I2C_TIMEOUT 100

/*** Hardware Definitions ****************************************************/
// Predefined Clock Speeds
#define I2C_CLK_10KHZ     10000
#define I2C_CLK_50KHZ     50000
#define I2C_CLK_100KHZ    100000
#define I2C_CLK_400KHZ    400000
#define I2C_CLK_500KHZ    500000
#define I2C_CLK_600KHZ    600000
#define I2C_CLK_750KHZ    750000
#define I2C_CLK_1MHZ      1000000

// Hardware CLK Prerate and timeout
#define I2C_PRERATE       1000000

#define I2C_AFIO_REG	((uint32_t)0x00000000)
#define I2C_PORT_RCC	RCC_APB2Periph_GPIOC
#define I2C_PORT		GPIOC
#define I2C_PIN_SCL 	2
#define I2C_PIN_SDA 	1

/*** Types and Enums *********************************************************/
/// @brief I2C Error Codes
typedef enum {
	I2C_OK	  = 0, // No Error. All OK
	I2C_ERR_BERR,	 // Bus Error
	I2C_ERR_NACK,	 // ACK Bit failed
	I2C_ERR_ARLO,	 // Arbitration Lost
	I2C_ERR_OVR,	 // Overun/underrun condition
	I2C_ERR_BUSY,	 // Bus was busy and timed out
} i2c_err_t;


/// @brief I2C Address Mode Types:
/// 7bit is the standard I2C Address mode. ADDR[LSB] is the read/write bit
/// 10bit ADDR is 2 bytes, the ADDR[0][LSB] is the read/write bit.
/// 16bit Mode sends the Address raw as 2 bytes to support some devices
typedef enum {
	I2C_ADDR_7BIT     = 0,
	I2C_ADDR_10BIT,
} i2c_addr_t;

typedef struct {
	uint32_t      clkr;  // Clock Rate (in Hz)
	i2c_addr_t    type;  // Address Type - Determines address behaviour
	uint16_t      addr;  // Address Value. Default is WRITE in 7 and 10bit
	uint8_t       regb;  // Register Bytes 1-4 (Capped to sane range in in init())
	uint32_t      tout;  // Number of cycles before the master timesout. Useful for clock-stretch
} i2c_device_t;

#endif