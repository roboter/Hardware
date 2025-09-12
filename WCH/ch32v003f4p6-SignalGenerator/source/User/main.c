/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Robby Roboter
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.

/*
      Hardware connection:
			      PC1 -- SDA
            PC2 -- SCL
*/

#include <ch32v00x_i2c.h>
#include <ch32v00x_gpio.h>
#include <ch32v00x_rcc.h>
#include <debug.h>
#include <ssd1306.h>
#include <si5351.h>
#include <string.h>
#include "main.h"

/*** Static Types ************************************************************/
typedef enum {
	I2C_READ   = 0x00,
	I2C_WRITE  = 0x01
} i2c_addr_rw_t;


/*** Static Variables ********************************************************/
/// @brief This variable is set by init() and defines how many cycles to wait
/// before a timeout is triggered
static uint32_t _i2c_timeout = 0;

void scan_all_i2c_addresses(void);
void display_i2c_results(uint8_t found_addresses[], uint8_t count);
bool test_si5351_response(uint8_t addr_7bit);

/// @brief Gets and returns any error state on the I2C Interface, and resets
/// the bit flags
/// @param none
/// @return i2c_err_t error value
static inline i2c_err_t i2c_error(void)
{
	if(I2C1->STAR1 & I2C_STAR1_BERR)  {I2C1->STAR1 &= ~I2C_STAR1_BERR;  return I2C_ERR_BERR;}
	if(I2C1->STAR1 & I2C_STAR1_AF)    {I2C1->STAR1 &= ~I2C_STAR1_AF;    return I2C_ERR_NACK;}
	if(I2C1->STAR1 & I2C_STAR1_ARLO)  {I2C1->STAR1 &= ~I2C_STAR1_ARLO;  return I2C_ERR_ARLO;}
	if(I2C1->STAR1 & I2C_STAR1_OVR)   {I2C1->STAR1 &= ~I2C_STAR1_OVR;   return I2C_ERR_OVR;}

	return I2C_OK;
}

i2c_err_t I2C_HAL_Init(i2c_device_t *dev)
{
    // 1. Clamp regb to 1-4
    if(dev->regb == 0) dev->regb = 1;
    if(dev->regb > 4) dev->regb = 4;

    // 2. Set timeout
    _i2c_timeout = dev->tout;

    // 3. Reset I2C1 peripheral
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

    // 4. Enable I2C1 clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // 5. Enable GPIO and AFIO clocks
    RCC_APB2PeriphClockCmd(I2C_PORT_RCC | RCC_APB2Periph_AFIO, ENABLE);

    // 6. Set AFIO remap if needed
    AFIO->PCFR1 &= ~(0x04400002); // Clear
    AFIO->PCFR1 |= I2C_AFIO_REG;  // Set remap

    // 7. Configure SDA/SCL pins (Open-Drain Alternate Function)
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = (1 << I2C_PIN_SDA) | (1 << I2C_PIN_SCL);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_PORT, &GPIO_InitStructure);

    // 8. Set peripheral clock frequency in MHz (CTLR2.FREQ)
    I2C1->CTLR2 &= ~I2C_CTLR2_FREQ;
    I2C1->CTLR2 |= (SystemCoreClock / 1000000) & I2C_CTLR2_FREQ;

    // 9. Configure I2C clock
    if(dev->clkr <= 100000) {
        // Standard mode 100kHz
        I2C1->CKCFGR = (SystemCoreClock / (2 * dev->clkr)) & I2C_CKCFGR_CCR;
    } else {
        // Fast mode 400kHz default 33% duty cycle
        I2C1->CKCFGR = ((SystemCoreClock / (3 * dev->clkr)) & I2C_CKCFGR_CCR) | I2C_CKCFGR_FS;
    }

    // 10. Enable the I2C peripheral
    I2C_Cmd(I2C1, ENABLE);

    // 11. Return error status
    return i2c_error();
}


// ------------------------------------------------------------------
// MY_i2c_start
// ------------------------------------------------------------------
i2c_err_t MY_i2c_start(void)
{
    I2C_GenerateSTART(I2C1, ENABLE);
    uint32_t timeout = I2C_TIMEOUT;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if(--timeout == 0) return I2C_TIMEOUT;
    }
    return I2C_OK;
}

// ------------------------------------------------------------------
// MY_i2c_send_addr
// ------------------------------------------------------------------
i2c_err_t MY_i2c_send_addr(uint8_t addr)
{
    I2C_Send7bitAddress(I2C1, addr<<1, I2C_Direction_Receiver);

    uint32_t timeout = I2C_TIMEOUT;
    
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
            if(--timeout == 0) return I2C_TIMEOUT;
        }
    
    return I2C_OK;
}

void GPIO_Buttons_INIT(void)
{
   GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable the clock for the GPIO port
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configure the pins as input floating
    GPIO_InitStructure.GPIO_Pin = ENTER | UP | DOWN | RIGHT | LEFT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(BUTTONPORT, &GPIO_InitStructure);
}

// Display test result on OLED
void display_i2c_results(uint8_t found_addresses[], uint8_t count) {
    OLED_clear();
    OLED_println("I2C Devices:");

    uint8_t page = 1; // OLED page (0-7)
    for(uint8_t i = 0; i < count; i++) {
        if(page > 7) { // screen full
            Delay_Ms(2000);
            OLED_clear();
            page = 0;
        }

        OLED_setpos(0, page++); // move to next page
        OLED_printS("0x");
        if(found_addresses[i] < 0x10) OLED_print("0");
        OLED_printB(found_addresses[i]);
    }
}

int main(void)
{
  Delay_Init();
  GPIO_Buttons_INIT();
  USART_Printf_Init(115200);
  printf("SystemClk:%d\r\n", SystemCoreClock);

  // Create an I2C Device Struct. This defines the I2C
	// * Clock Speed
	// * Address Type                 (7bit or 10bit)
	// * Address Value                (1 Byte for 7bit, 2 Bytes for 10bit)
	// * Register Bytes               (1, 2, 3 & 4 bytes supported)
	// * Timeout Count                (Number of clock cycles to wait for clock stretching)
	// NOTE: This demo example is using a DS3231 RTC
	i2c_device_t dev = {
		.clkr = I2C_CLK_400KHZ,
		.type = I2C_ADDR_7BIT,
		.addr = 0x68,
		.regb = 1,
		.tout = 2000,
	};

	// Initialise the I2C Interface  
  if(I2C_HAL_Init(&dev) != I2C_OK) printf("Failed to init the I2C Bus\n");
 
  OLED_init();  // Add OLED initialization    
  OLED_clear();
  OLED_println("I2C Scanner Demo");
  Delay_Ms(1000);

  int previous = 0;
  while(1){
    // Read the button values
    int up = GPIO_ReadInputDataBit(BUTTONPORT, UP);
    int right = GPIO_ReadInputDataBit(BUTTONPORT, RIGHT);
    int left = GPIO_ReadInputDataBit(BUTTONPORT, LEFT);
    int down = GPIO_ReadInputDataBit(BUTTONPORT, DOWN);
    int enter = GPIO_ReadInputDataBit(BUTTONPORT, ENTER);
    
        if (up && previous != UP) {
					OLED_clear();
					OLED_println("UP\n");
					printf("UP\n");
					previous = UP;
        } else if (right && previous != RIGHT)  {
					OLED_clear();
					OLED_println("RIGHT\n");
					printf("RIGHT\n");
          
					previous = RIGHT;
        } else if (left && previous != LEFT) {
					OLED_clear();
					OLED_println("LEFT\n");
					printf("LEFT\n");
					previous = LEFT;
        } else if (down && previous != DOWN) {
					OLED_clear();
					OLED_println("DOWN\n");
					printf("DOWN\n");
					previous = DOWN;
          //scan_all_i2c_addresses();
        } else if (enter && previous != ENTER) {
					OLED_clear();
					OLED_println("ENTER button pressed\n");
					printf("ENTER button pressed\n");
					previous = ENTER;

        } 
    Delay_Ms(150);
  }
}

void scan_all_i2c_addresses(void) {
    uint8_t found_addresses[128] = {0};
    uint8_t found_count = 0;

    printf("----Scanning I2C Bus for Devices----\n");

    for(uint8_t addr = 1; addr < 0x78; addr++) { // valid 7-bit addresses 0x08-0x77
        // Start condition
        uint32_t timeout = I2C_TIMEOUT;
        I2C_GenerateSTART(I2C1, ENABLE);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
            if(--timeout == 0) {
                I2C_GenerateSTOP(I2C1, ENABLE);
                goto next_addr;
            }
        }

        // Send 7-bit address (write mode)
        if(MY_i2c_send_addr(addr) == I2C_OK) {
            found_addresses[found_count++] = addr;
            printf("Address 0x%02X Responded.\n", addr);
        }

        // STOP
        I2C_GenerateSTOP(I2C1, ENABLE);

    next_addr:
        ; // nothing
    }

    printf("----Done Scanning----\n");
    printf("Total devices found: %d\n", found_count);

    // Display on OLED
    display_i2c_results(found_addresses, found_count);
}



