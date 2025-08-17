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

// DCMI状态标志，当数据帧传输完成时，会被 HAL_DCMI_FrameEventCallback() 中断回调函数置 1 
extern volatile uint8_t DCMI_FrameState;  // 声明变量，方便其它文件进行调用
extern volatile uint8_t OV2640_FPS ;      // 帧率

#define  OV2640_Success   0            // 通讯成功标志
#define  OV2640_Error     -1           // 通讯错误

#define  OV2640_Enable    1
#define  OV2640_Disable   0

// 用于设置输出的格式，被 OV2640_Set_Pixformat() 引用
#define Pixformat_RGB565   0
#define Pixformat_JPEG     1

// OV2640的特效模式，被 OV2640_Set_Effect() 引用
#define  OV2640_Effect_Normal       0  // 正常模式
#define  OV2640_Effect_Negative     1  // 负片模式，也就是颜色全部取反
#define  OV2640_Effect_BW           2  // 黑白模式
#define  OV2640_Effect_BW_Negative  3  // 黑白模式+负片模式

// 1. 定义OV2640实际输出的图像大小，可以根据实际的应用或者显示屏进行调整（同时也要修改配置参数里的时钟分频）
// 2. 这两个参数不会影响帧率，且不能超过对应模式的最大尺寸
// 3. SVGA模式下，输出图像最大分辨率为 800*600,  最大帧率30帧
// 4. UXGA模式下，输出图像最大分辨率为 1600*1200,最大帧率15帧
// 5. 要设置的图像长、宽必须能被4整除！
// 6. 要设置的图像长、宽比必须满足4:3，不然画面会被拉伸畸变
#define OV2640_Width          400   // 图像长度 
#define OV2640_Height         300  // 图像宽度

// 1. 定义要显示的画面大小，数值一定要能被4整除！！
// 2. RGB565格式下，最终会由DCMI将OV2640输出的4:3图像裁剪为适应屏幕的比例
// 3. 此处的分辨率不能超过 OV2640_Width 和 OV2640_Height
// 4. 分辨率太高时，需要修改PCLK的时钟速度，详细计算说明可参考 dcmi_ov2640_cfg.h 里的 0xd3 寄存器配置
#define	Display_Width			 LCD_Width
#define	Display_Height			 LCD_Height

// 1.RGB565模式下，需要 图像分辨率*2 的大小
// 2.JPG模式下，需要的缓冲区大小并不是固定的，例如 640*480分辨率，JPG图像大概要占30K，
//   缓冲区预留2倍左右大小即可，用户可根据实际情况去设置,
#define 	OV2640_BufferSize     Display_Width * Display_Height*2 /4   // DMA传输数据大小（32位宽）
//#define 	OV2640_BufferSize     	100*1024/4   // DMA传输数据大小（32位宽）

#define  OV2640_SEL_Registers       0xFF	// 寄存器组选择寄存器
#define  OV2640_SEL_DSP             0x00	// 设置为0x00时，选择  DSP    寄存器组
#define  OV2640_SEL_SENSOR          0x01	// 设置为0x01时，选择  SENSOR 寄存器组


// DSP 寄存器组 (0xFF = 0x00) 
#define 	OV2640_DSP_RESET           0xE0	// 可选择复位 控制器、SCCB单元、JPEG单元、DVP接口单元等
#define 	OV2640_DSP_BPADDR          0x7C	// 间接寄存器访问:地址
#define 	OV2640_DSP_BPDATA          0x7D	// 间接寄存器访问:数据

// SENSOR 寄存器组 (0xFF = 0x01) 
#define 	OV2640_SENSOR_COM7         0x12	// 公共控制,系统复位、摄像头分辨率选择、缩放模式、颜色彩条设置 
#define 	OV2640_SENSOR_REG04        0x04	// 寄存器组4,可设置摄像头扫描方向等
#define  OV2640_SENSOR_PIDH         0x0a	// ID高字节
#define  OV2640_SENSOR_PIDL         0x0b	// ID低字节

/*------------------------------------------------------------ 函数声明 ------------------------------------------------*/

//void     MX_DCMI_Init(void);
int8_t   DCMI_OV2640_Init(void);	// 初始SCCB、DCMI、DMA以及配置OV2640

void     OV2640_DMA_Transmit_Continuous(uint32_t DMA_Buffer,uint32_t DMA_BufferSize);	// 启动DMA传输，连续模式
void     OV2640_DMA_Transmit_Snapshot(uint32_t DMA_Buffer,uint32_t DMA_BufferSize);		//  启动DMA传输，快照模式，传输一帧图像后停止
void     OV2640_DCMI_Suspend(void);		// 挂起DCMI，停止捕获数据
void     OV2640_DCMI_Resume(void);		// 恢复DCMI，开始捕获数据
void     OV2640_DCMI_Stop(void);			// 禁止DCMI的DMA请求，停止DCMI捕获，禁止DCMI外设
int8_t 	OV2640_DCMI_Crop(uint16_t Displey_XSize,uint16_t Displey_YSize,uint16_t Sensor_XSize,uint16_t Sensor_YSize );	// 裁剪画面

void     OV2640_Reset(void);				//	执行软件复位		
uint16_t OV2640_ReadID(void);				// 读取器件ID
void     OV2640_Config( const uint8_t (*ConfigData)[2] );		// 配置各项参数
void     OV2640_Set_Pixformat(uint8_t pixformat);					// 设置图像输出格式
int8_t   OV2640_Set_Framesize(uint16_t width,uint16_t height);	// 设置实际输出的图像大小
int8_t   OV2640_Set_Horizontal_Mirror( int8_t ConfigState );	// 用于设置输出的图像是否进行水平镜像
int8_t   OV2640_Set_Vertical_Flip( int8_t ConfigState );			//	用于设置输出的图像是否进行垂直翻转 
void     OV2640_Set_Saturation(int8_t Saturation);					// 设置饱和度
void     OV2640_Set_Brightness(int8_t Brightness);					// 设置亮度
void     OV2640_Set_Contrast(int8_t Contrast);						// 设置对比度
void     OV2640_Set_Effect(uint8_t effect_Mode );					// 用于设置特效，正常、负片、黑白、黑白+负片等模式

/*-------------------------------------------------------------- 引脚配置宏 ---------------------------------------------*/

#define OV2640_PWDN_PIN            			 GPIO_PIN_14        				 	// PWDN 引脚      
#define OV2640_PWDN_PORT           			 GPIOD                 			 	// PWDN GPIO端口     
#define GPIO_OV2640_PWDN_CLK_ENABLE    	__HAL_RCC_GPIOD_CLK_ENABLE() 		// PWDN GPIO端口时钟

// 低电平，不开启掉电模式，摄像头正常工作
#define	OV2640_PWDN_OFF	HAL_GPIO_WritePin(OV2640_PWDN_PORT, OV2640_PWDN_PIN, GPIO_PIN_RESET)	

// 高电平，进入掉电模式，摄像头停止工作，此时功耗降到最低
#define 	OV2640_PWDN_ON		HAL_GPIO_WritePin(OV2640_PWDN_PORT, OV2640_PWDN_PIN, GPIO_PIN_SET)	

#ifdef __cplusplus
}
#endif

#endif /* __DCMI_H__ */

