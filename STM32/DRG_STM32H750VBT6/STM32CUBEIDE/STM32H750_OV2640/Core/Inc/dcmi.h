/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dcmi.h
  * @brief   This file contains all the function prototypes for
  *          the dcmi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DCMI_H__
#define __DCMI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
#include "sccb.h"  
#include "usart.h"
#include "spi.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern DCMI_HandleTypeDef hdcmi;

// DCMI status flag, when a new frame is captured, it will be set to 1 by HAL_DCMI_FrameEventCallback() interrupt callback
extern volatile uint8_t DCMI_FrameState;  // DCMI frame status flag
extern volatile uint8_t OV2640_FPS ;      // Frame rate

#define  OV2640_Success   0            // Communication success flag
#define  OV2640_Error     -1           // Communication error

#define  OV2640_Enable    1
#define  OV2640_Disable   0

// Camera image format, used in OV2640_Set_Pixformat() function
#define Pixformat_RGB565   0
#define Pixformat_JPEG     1

// OV2640 special effects mode, used in OV2640_Set_Effect() function
#define  OV2640_Effect_Normal       0  // Normal mode
#define  OV2640_Effect_Negative     1  // Negative mode (also called color inversion)
#define  OV2640_Effect_BW           2  // Black and white mode
#define  OV2640_Effect_BW_Negative  3  // Black and white mode + negative mode

// 1. Set OV2640 actual image size, you can adjust according to actual application or display screen requirements, and also need to modify the corresponding clock frequency
// 2. The image size affects the frame rate, and cannot exceed the corresponding mode limit
// 3. In SVGA mode, the actual image resolution is 800*600, and the frame rate is 30fps
// 4. In UXGA mode, the actual image resolution is 1600*1200, and the frame rate is 15fps
// 5. The set image length and width must be divisible by 4
// 6. The set image length and width must maintain a 4:3 ratio, otherwise it will be automatically adjusted
#define OV2640_Width          400   // Image length
#define OV2640_Height         300  // Image width

// 1. Set the display screen size, the value must be divisible by 4
// 2. In RGB565 format, the display screen and DCMI and OV2640 must maintain a 4:3 image ratio
// 3. The resolution here cannot exceed OV2640_Width and OV2640_Height
// 4. When the resolution is too large, you need to modify the PCLK clock speed. For details, please refer to the 0xd3 register in dcmi_ov2640_cfg.h
#define	Display_Width			 LCD_Width
#define	Display_Height			 LCD_Height

// 1. In RGB565 mode, you need image resolution*2 size
// 2. In JPG mode, you need the screen buffer size, which is fixed. For 640*480 resolution, JPG images need to occupy 30K
//   It is recommended to reserve 2 times the size, and users can adjust according to actual needs
#define 	OV2640_BufferSize     Display_Width * Display_Height*2 /4   // DMA buffer data size (32-bit data)
//#define 	OV2640_BufferSize     	100*1024/4   // DMA buffer data size (32-bit data)

#define  OV2640_SEL_Registers       0xFF	// Register bank selection register
#define  OV2640_SEL_DSP             0x00	// When set to 0x00, select DSP register bank
#define  OV2640_SEL_SENSOR          0x01	// When set to 0x01, select SENSOR register bank


// DSP register bank (0xFF = 0x00) 
#define 	OV2640_DSP_RESET           0xE0	// Selection bit, resets SCCB unit, JPEG unit, DVP interface unit
#define 	OV2640_DSP_BPADDR          0x7C	// Bypass register address: address
#define 	OV2640_DSP_BPDATA          0x7D	// Bypass register data: data

// SENSOR register bank (0xFF = 0x01) 
#define 	OV2640_SENSOR_COM7         0x12	// Common control 7, system reset, camera resolution selection, image mode, color format
#define 	OV2640_SENSOR_REG04        0x04	// Register 4, controls camera scanning direction
#define  OV2640_SENSOR_PIDH         0x0a	// ID high byte
#define  OV2640_SENSOR_PIDL         0x0b	// ID low byte

/*------------------------------------------------------------ Function declarations ------------------------------------------------*/

//void     MX_DCMI_Init(void);
int8_t   DCMI_OV2640_Init(void);	// Initialize SCCB, DCMI, DMA and configure OV2640

void     OV2640_DMA_Transmit_Continuous(uint32_t DMA_Buffer,uint32_t DMA_BufferSize);	// Start DMA transmission, continuous mode
void     OV2640_DMA_Transmit_Snapshot(uint32_t DMA_Buffer,uint32_t DMA_BufferSize);		//  Start DMA transmission, snapshot mode, capture one frame and stop
void     OV2640_DCMI_Suspend(void);		// Suspend DCMI and stop data transmission
void     OV2640_DCMI_Resume(void);		// Resume DCMI and start data transmission
void     OV2640_DCMI_Stop(void);			// Stop DCMI and DMA transmission, stop DCMI clock, stop DCMI
int8_t 	OV2640_DCMI_Crop(uint16_t Displey_XSize,uint16_t Displey_YSize,uint16_t Sensor_XSize,uint16_t Sensor_YSize );	// Crop function

void     OV2640_Reset(void);				//	Execute software reset		
uint16_t OV2640_ReadID(void);				// Read camera ID
void     OV2640_Config( const uint8_t (*ConfigData)[2] );		// Configure camera
void     OV2640_Set_Pixformat(uint8_t pixformat);					// Set image data format
int8_t   OV2640_Set_Framesize(uint16_t width,uint16_t height);	// Set actual camera image size
int8_t   OV2640_Set_Horizontal_Mirror( int8_t ConfigState );	// Set whether the camera image is horizontally mirrored
int8_t   OV2640_Set_Vertical_Flip( int8_t ConfigState );			//	Set whether the camera image is vertically flipped
void     OV2640_Set_Saturation(int8_t Saturation);					// Set saturation
void     OV2640_Set_Brightness(int8_t Brightness);					// Set brightness
void     OV2640_Set_Contrast(int8_t Contrast);						// Set contrast
void     OV2640_Set_Effect(uint8_t effect_Mode );					// Set camera special effects (normal, negative, black and white, black and white + negative mode)

/*-------------------------------------------------------------- Pin configuration ---------------------------------------------*/

#define OV2640_PWDN_PIN            			 GPIO_PIN_14        				 	// PWDN pin      
#define OV2640_PWDN_PORT           			 GPIOD                 			 	// PWDN GPIO port     
#define GPIO_OV2640_PWDN_CLK_ENABLE    	__HAL_RCC_GPIOD_CLK_ENABLE() 		// PWDN GPIO port clock

// Low level enables camera working mode, camera starts working
#define	OV2640_PWDN_OFF	HAL_GPIO_WritePin(OV2640_PWDN_PORT, OV2640_PWDN_PIN, GPIO_PIN_RESET)	

// High level enables sleep mode, camera stops working and enters sleep state
#define 	OV2640_PWDN_ON		HAL_GPIO_WritePin(OV2640_PWDN_PORT, OV2640_PWDN_PIN, GPIO_PIN_SET)	

#ifdef __cplusplus
}
#endif

#endif /* __DCMI_H__ */

