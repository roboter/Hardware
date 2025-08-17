/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dcmi.c
  * @brief   This file provides code for the configuration
  *          of the DCMI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "dcmi.h"
#include "dcmi_ov2640_cfg.h"  

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

DCMI_HandleTypeDef hdcmi;
DMA_HandleTypeDef    DMA_Handle_dcmi;  // DMA句柄

volatile uint8_t DCMI_FrameState = 0;  // DCMI状态标志，当数据帧传输完成时，会被 HAL_DCMI_FrameEventCallback() 中断回调函数置 1     
volatile uint8_t OV2640_FPS ;          // 帧率

/* DCMI init function */
void MX_DCMI_Init(void)
{

  hdcmi.Instance = DCMI;
  hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
  hdcmi.Init.PCKPolarity = DCMI_PCKPOLARITY_FALLING;
  hdcmi.Init.VSPolarity = DCMI_VSPOLARITY_LOW;
  hdcmi.Init.HSPolarity = DCMI_HSPOLARITY_LOW;
  hdcmi.Init.CaptureRate = DCMI_CR_ALL_FRAME;
  hdcmi.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
  hdcmi.Init.JPEGMode = DCMI_JPEG_DISABLE;
  hdcmi.Init.ByteSelectMode = DCMI_BSM_ALL;
  hdcmi.Init.ByteSelectStart = DCMI_OEBS_ODD;
  hdcmi.Init.LineSelectMode = DCMI_LSM_ALL;
  hdcmi.Init.LineSelectStart = DCMI_OELS_ODD;
	HAL_DCMI_Init(&hdcmi) ;
	
	HAL_NVIC_SetPriority(DCMI_IRQn, 0 ,5);    // 设置中断优先级
  HAL_NVIC_EnableIRQ(DCMI_IRQn); 		      // 开启DCMI中断
	
//// 在JPG模式下，一定要单独使能该中断	
//	__HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME); // 使能 FRAME 中断
	
	
  if (HAL_DCMI_Init(&hdcmi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DCMI_Init 2 */

  /* USER CODE END DCMI_Init 2 */

}

void HAL_DCMI_MspInit(DCMI_HandleTypeDef* dcmiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  if(dcmiHandle->Instance==DCMI)
  {

    __HAL_RCC_DCMI_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
		
		GPIO_OV2640_PWDN_CLK_ENABLE;    // 使能PWDN 引脚的 GPIO 时钟
		
    /**DCMI GPIO Configuration
    PE4     ------> DCMI_D4
    PE5     ------> DCMI_D6
    PE6     ------> DCMI_D7
    PA4     ------> DCMI_HSYNC
    PA6     ------> DCMI_PIXCLK
    PC6     ------> DCMI_D0
    PC7     ------> DCMI_D1
    PD3     ------> DCMI_D5
    PB7     ------> DCMI_VSYNC
    PE0     ------> DCMI_D2
    PE1     ------> DCMI_D3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_0
                          |GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN DCMI_MspInit 1 */

  /* USER CODE END DCMI_MspInit 1 */
	
	// 初始化 PWDN 引脚  
		OV2640_PWDN_ON;	// 高电平，进入掉电模式，摄像头停止工作，此时功耗降到最低
		
		GPIO_InitStruct.Pin 		= OV2640_PWDN_PIN;				// PWDN 引脚
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// 推挽输出模式
		GPIO_InitStruct.Pull 	= GPIO_PULLUP;						// 上拉
		GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// 速度等级低
		HAL_GPIO_Init(OV2640_PWDN_PORT, &GPIO_InitStruct);	   // 初始化  
  }
}

//void HAL_DCMI_MspDeInit(DCMI_HandleTypeDef* dcmiHandle)
//{

//  if(dcmiHandle->Instance==DCMI)
//  {
//  /* USER CODE BEGIN DCMI_MspDeInit 0 */

//  /* USER CODE END DCMI_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_DCMI_CLK_DISABLE();

//    /**DCMI GPIO Configuration
//    PE4     ------> DCMI_D4
//    PE5     ------> DCMI_D6
//    PE6     ------> DCMI_D7
//    PA4     ------> DCMI_HSYNC
//    PA6     ------> DCMI_PIXCLK
//    PC6     ------> DCMI_D0
//    PC7     ------> DCMI_D1
//    PD3     ------> DCMI_D5
//    PB7     ------> DCMI_VSYNC
//    PE0     ------> DCMI_D2
//    PE1     ------> DCMI_D3
//    */
//    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_0
//                          |GPIO_PIN_1);

//    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_6);

//    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

//    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3);

//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

//  /* USER CODE BEGIN DCMI_MspDeInit 1 */

//  /* USER CODE END DCMI_MspDeInit 1 */
//  }
//}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DMA_Init
*
*	函数功能: 配置 DMA 相关参数
*
*	说    明: 使用的是DMA2，外设到存储器模式、数据位宽32bit、并开启中断 			          
*
*****************************************************************************************************************************************/
void OV2640_DMA_Init(void)
{
   __HAL_RCC_DMA2_CLK_ENABLE();   // 使能DMA2时钟

   DMA_Handle_dcmi.Instance                     = DMA2_Stream7;               // DMA2数据流7      
   DMA_Handle_dcmi.Init.Request                 = DMA_REQUEST_DCMI;           // DMA请求来自DCMI
   DMA_Handle_dcmi.Init.Direction               = DMA_PERIPH_TO_MEMORY;       // 外设到存储器模式
   DMA_Handle_dcmi.Init.PeriphInc               = DMA_PINC_DISABLE;           // 外设地址禁止自增
   DMA_Handle_dcmi.Init.MemInc                  = DMA_MINC_ENABLE;			   // 存储器地址自增
   DMA_Handle_dcmi.Init.PeriphDataAlignment     = DMA_PDATAALIGN_WORD;        // DCMI数据位宽，32位  
   DMA_Handle_dcmi.Init.MemDataAlignment        = DMA_MDATAALIGN_WORD;        // 存储器数据位宽，32位
   DMA_Handle_dcmi.Init.Mode                    = DMA_CIRCULAR;               // 循环模式					
   DMA_Handle_dcmi.Init.Priority                = DMA_PRIORITY_LOW;           // 优先级低
   DMA_Handle_dcmi.Init.FIFOMode                = DMA_FIFOMODE_ENABLE;        // 使能fifo
   DMA_Handle_dcmi.Init.FIFOThreshold           = DMA_FIFO_THRESHOLD_FULL;    // 全fifo模式，4*32bit大小
   DMA_Handle_dcmi.Init.MemBurst                = DMA_MBURST_SINGLE;          // 单次传输
   DMA_Handle_dcmi.Init.PeriphBurst             = DMA_PBURST_SINGLE;          // 单次传输

   HAL_DMA_Init(&DMA_Handle_dcmi);                        // 配置DMA
   __HAL_LINKDMA(&hdcmi, DMA_Handle, DMA_Handle_dcmi);    // 关联DCMI句柄
   HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);         // 设置中断优先级
   HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);                 // 使能中断
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Delay
*	入口参数: Delay - 延时时间，单位 ms 
*	函数功能: 简单延时函数，不是很精确
*	说    明: 为了移植的简便性,此处采用软件延时，实际项目中可以替换成RTOS的延时或者HAL库的延时
*****************************************************************************************************************************************/
void OV2640_Delay(volatile uint32_t Delay)
{
	volatile uint16_t i;

	while (Delay --)				
	{
		for (i = 0; i < 40000; i++);
	}	
//	HAL_Delay(Delay);	  // 可使用HAL库的延时 或其它OS的延时
}

/***************************************************************************************************************************************
*	函 数 名: DCMI_OV2640_Init
*
*	函数功能: 初始SCCB、DCMI、DMA以及配置OV2640
*
*****************************************************************************************************************************************/
int8_t DCMI_OV2640_Init(void)
{
	uint16_t	Device_ID;		// 定义变量存储器件ID
	
  SCCB_GPIO_Config();		               // SCCB引脚初始化
	MX_DCMI_Init();                        // 初始化DCMI配置引脚
  OV2640_DMA_Init();                     // 初始化DMA配置
	OV2640_Reset();	                     // 执行软件复位
	Device_ID = OV2640_ReadID();		      // 读取器件ID
	
	if( (Device_ID == 0x2640) || (Device_ID == 0x2642) )		// 进行匹配，实际的器件ID可能是 0x2640 或者 0x2642
	{
		printf ("OV2640 OK,ID:0x%X\r\n",Device_ID);		      // 匹配通过
	
      OV2640_Config( OV2640_SVGA_Config );             		// 配置 SVGA模式  ------>  800*600，  最大帧率30帧
//		OV2640_Config( OV2640_UXGA_Config );                  // 配置 UXGA模式  ------>  1600*1200，最大帧率15帧

		OV2640_Set_Framesize(OV2640_Width,OV2640_Height);		// 设置OV2640输出的图像大小
	
		OV2640_DCMI_Crop( Display_Width, Display_Height, OV2640_Width, OV2640_Height );	// 将OV2640输出图像裁剪成适应屏幕的大小
		
		return OV2640_Success;	 // 返回成功标志		
	}
	else
	{
		printf ("OV2640 ERROR!!!!!  ID:%X\r\n",Device_ID);	   // 读取ID错误
		return  OV2640_Error;	 // 返回错误标志
	}	
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DMA_Transmit_Continuous
*
*	入口参数:  DMA_Buffer - DMA将要传输的地址，即用于存储摄像头数据的存储区地址
*            DMA_BufferSize - 传输的数据大小，32位宽
*
*	函数功能: 启动DMA传输，连续模式
*
*	说    明: 1. 开启连续模式之后，会一直进行传输，除非挂起或者停止DCMI
*            2. OV2640使用RGB565模式时，1个像素点需要2个字节来存储
*				 3. 因为DMA配置传输数据为32位宽，计算 DMA_BufferSize 时，需要除以4，例如：
*               要获取 240*240分辨率 的图像，需要传输 240*240*2 = 115200 字节的数据，
*               则 DMA_BufferSize = 115200 / 4 = 28800 。
*fanke
*****************************************************************************************************************************************/
void OV2640_DMA_Transmit_Continuous(uint32_t DMA_Buffer,uint32_t DMA_BufferSize)
{
   DMA_Handle_dcmi.Init.Mode  = DMA_CIRCULAR;  // 循环模式					

   HAL_DMA_Init(&DMA_Handle_dcmi);    // 配置DMA

  // 使能DCMI采集数据,连续采集模式
   HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)DMA_Buffer,DMA_BufferSize);
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DMA_Transmit_Snapshot
*
*	入口参数:  DMA_Buffer - DMA将要传输的地址，即用于存储摄像头数据的存储区地址
*            DMA_BufferSize - 传输的数据大小，32位宽
*
*	函数功能: 启动DMA传输，快照模式，传输一帧图像后停止
*
*	说    明: 1. 快照模式，只传输一帧的数据
*            2. OV2640使用RGB565模式时，1个像素点需要2个字节来存储
*				 3. 因为DMA配置传输数据为32位宽，计算 DMA_BufferSize 时，需要除以4，例如：
*               要获取 240*240分辨率 的图像，需要传输 240*240*2 = 115200 字节的数据，
*               则 DMA_BufferSize = 115200 / 4 = 28800 。
*            4. 使用该模式传输完成之后，DCMI会被挂起，再次启用传输之前，需要调用 OV2640_DCMI_Resume() 恢复DCMI
*
*****************************************************************************************************************************************/
void OV2640_DMA_Transmit_Snapshot(uint32_t DMA_Buffer,uint32_t DMA_BufferSize)
{
   DMA_Handle_dcmi.Init.Mode  = DMA_NORMAL;  // 正常模式					

   HAL_DMA_Init(&DMA_Handle_dcmi);    // 配置DMA

   HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)DMA_Buffer,DMA_BufferSize);
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DCMI_Suspend
*
*	函数功能: 挂起DCMI，停止捕获数据
*
*	说    明: 1. 开启连续模式之后，再调用该函数，会停止捕获DCMI的数据
*            2. 可以调用 OV2640_DCMI_Resume() 恢复DCMI
*				 3. 需要注意的，挂起DCMI期间，DMA是没有停止工作的
*FANKE
*****************************************************************************************************************************************/
void OV2640_DCMI_Suspend(void) 
{
   HAL_DCMI_Suspend(&hdcmi);    // 挂起DCMI
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DCMI_Resume
*
*	函数功能: 恢复DCMI，开始捕获数据
*
*	说    明: 1. 当DCMI被挂起时，可以调用该函数恢复
*            2. 使用 OV2640_DMA_Transmit_Snapshot() 快照模式，传输完成之后，DCMI也会被挂起，再次启用传输之前，
*				    需要调用本函数恢复DCMI捕获
*
*****************************************************************************************************************************************/
void  OV2640_DCMI_Resume(void) 
{
   (&hdcmi)->State = HAL_DCMI_STATE_BUSY;       // 变更DCMI标志
   (&hdcmi)->Instance->CR |= DCMI_CR_CAPTURE;   // 开启DCMI捕获
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DCMI_Stop
*
*	函数功能: 禁止DCMI的DMA请求，停止DCMI捕获，禁止DCMI外设
*
*****************************************************************************************************************************************/
void  OV2640_DCMI_Stop(void) 
{
   HAL_DCMI_Stop(&hdcmi);
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_DCMI_Crop
*
*	入口参数:  Displey_XSize 、Displey_YSize - 显示器的长宽
*				  Sensor_XSize、Sensor_YSize - 摄像头传感器输出图像的长宽
*
*	函数功能: 使用DCMI的裁剪功能，将传感器输出的图像裁剪成适应屏幕的大小
*
*	说    明: 1. 因为摄像头输出的画面比例固定为4:3，不一定匹配显示器
*				 2. 需要注意的是，摄像头输出的图像长、宽必须要能被4整除！（ 使用OV2640_Set_Framesize函数进行设置 ）
*            3. DCMI的水平有效像素也必须要能被4整除！
*				 4. 函数会计算水平和垂直偏移，尽量让画面居中裁剪
*****************************************************************************************************************************************/
int8_t OV2640_DCMI_Crop(uint16_t Displey_XSize,uint16_t Displey_YSize,uint16_t Sensor_XSize,uint16_t Sensor_YSize )
{
	uint16_t DCMI_X_Offset,DCMI_Y_Offset;	// 水平和垂直偏移，垂直代表的是行数，水平代表的是像素时钟数（PCLK周期数）
	uint16_t DCMI_CAPCNT;		// 水平有效像素，代表的是像素时钟数（PCLK周期数）
	uint16_t DCMI_VLINE;			// 垂直有效行数

	if( (Displey_XSize>=Sensor_XSize)|| (Displey_YSize>=Sensor_YSize) )
	{
//		printf("实际显示的尺寸大于或等于摄像头输出的尺寸，退出DCMI裁剪\r\n");
		return OV2640_Error;  //如果实际显示的尺寸大于或等于摄像头输出的尺寸，则退出当前函数，不进行裁剪
	}
	
// 在设置为RGB565格式时，水平偏移，必须是奇数，否则画面色彩不正确，
// 因为一个有效像素是2个字节，需要2个PCLK周期，所以必须从奇数位开始，不然数据会错乱，
// 需要注意的是，寄存器值是从0开始算起的	！
	DCMI_X_Offset = Sensor_XSize - Displey_XSize; // 实际计算过程为（Sensor_XSize - LCD_XSize）/2*2

// 计算垂直偏移，尽量让画面居中裁剪，该值代表的是行数，	
	DCMI_Y_Offset = (Sensor_YSize - Displey_YSize)/2-1; // 寄存器值是从0开始算起的，所以要-1

// 因为一个有效像素是2个字节，需要2个PCLK周期，所以要乘2
// 最终得到的寄存器值，必须要能被4整除！
	DCMI_CAPCNT = Displey_XSize*2-1;	// 寄存器值是从0开始算起的，所以要-1
	
	DCMI_VLINE = Displey_YSize-1;		// 垂直有效行数
	
//	printf("%d  %d  %d  %d\r\n",DCMI_X_Offset,DCMI_Y_Offset,DCMI_CAPCNT,DCMI_VLINE);
	
	HAL_DCMI_ConfigCrop (&hdcmi,DCMI_X_Offset,DCMI_Y_Offset,DCMI_CAPCNT,DCMI_VLINE);// 设置裁剪窗口
	HAL_DCMI_EnableCrop(&hdcmi);		// 使能裁剪

	return OV2640_Success;	
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Reset
*
*	函数功能: 执行软件复位
*
*	说    明: 在配置OV2640之前，需要执行一次软件复位		 			          
*
*****************************************************************************************************************************************/
void OV2640_Reset(void)
{
	OV2640_Delay(5);  // 等待模块上电稳定，最少5ms，然后拉低PWDN  	
	
	OV2640_PWDN_OFF;  // PWDN 引脚输出低电平，不开启掉电模式，摄像头正常工作，此时摄像头模块的白色LED会点亮
  
// 根据OV2640的上电时序，硬件复位的持续时间要>=3ms，反客的OV2640采用硬件RC复位，持续时间大概在6ms左右
// 因此加入延时，等待硬件复位完成并稳定下来
	OV2640_Delay(5);    
	
	SCCB_WriteReg( OV2640_SEL_Registers, OV2640_SEL_SENSOR);   // 选择 SENSOR 寄存器组
	SCCB_WriteReg( OV2640_SENSOR_COM7, 0x80);                  // 启动软件复位

// 根据OV2640的软件复位时序，软件复位执行后，要>=2ms方可执行SCCB配置，此处采用保守一点的参数，延时10ms
	OV2640_Delay(10);    
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_ReadID
*
*	函数功能: 读取 OV2640 的器件ID
*
*	说    明: 实际的器件ID可能是 0x2640 或者 0x2642，批次不同ID可能会不一样		 
*
*****************************************************************************************************************************************/
uint16_t OV2640_ReadID(void)
{
   uint8_t PID_H,PID_L;     // ID变量
	
	SCCB_WriteReg( OV2640_SEL_Registers, OV2640_SEL_SENSOR);   // 选择 SENSOR 寄存器组

   PID_H = SCCB_ReadReg(OV2640_SENSOR_PIDH); // 读取ID高字节
   PID_L = SCCB_ReadReg(OV2640_SENSOR_PIDL); // 读取ID低字节
	
	return(PID_H<<8)|PID_L; // 返回完整的器件ID
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Config
*
*	入口参数:  (*ConfigData)[2] - 要配置的参数，可配置为 OV2640_SVGA_Config 或 OV2640_UXGA_Config
*
*	函数功能: 配置 OV2640 传感器和DSP参数
*
*	说    明: 1. 可配置为 SVGA 或者 UXGA模式
*				 2. SVGA 分辨率为800*600，最高支持30帧
*				 3. UXGA 分辨率为1600*1200，最高支持15帧
*            4. 参数定义在 dcmi_ov2640_cfg.h
*
*****************************************************************************************************************************************/
void OV2640_Config( const uint8_t (*ConfigData)[2] )
{
   uint32_t i; // 计数变量

	for( i=0;ConfigData[i][0] ; i++)
	{
		SCCB_WriteReg( ConfigData[i][0], ConfigData[i][1]);  // 进行参数配置   	
	} 
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Framesize
*
*	入口参数:  pixformat - 像素格式，可选择 Pixformat_RGB565、Pixformat_JPEG
*
*	函数功能: 设置输出的像素格式
*
*****************************************************************************************************************************************/
void OV2640_Set_Pixformat(uint8_t pixformat)
{
   const uint8_t (*ConfigData)[2];
   uint32_t i; // 计数变量

    switch (pixformat) 
    {
        case Pixformat_RGB565:
            ConfigData = OV2640_RGB565_Config;
            break;
        case Pixformat_JPEG:
            ConfigData = OV2640_JPEG_Config;
            break;
        default:  break;
    }

   for( i=0; ConfigData[i][0]; i++)
   {
      SCCB_WriteReg( ConfigData[i][0], ConfigData[i][1]);  // 进行参数配置   
   } 
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Framesize
*
*	入口参数:  width - 实际输出图像的长度，height - 实际输出图像的宽度
*
*	函数功能: 设置实际输出的图像大小
*
*	说    明: 1. OV2640设置为 SVGA（800*600） 或者 UXGA（1600*1200）模式，图像大小通常与实际用的屏幕分辨率不一样，
*				    因此可以调用次函数，设置实际输出的图像大小
*				 2. 需要注意的是，要设置的图像长、宽必须能被4整除！
*            3. 并不是设置输出的图像分辨率越小帧率就越高，帧率只和配置的模式有关，例如配置为SVGA最高只能支持30帧
*
*****************************************************************************************************************************************/
int8_t OV2640_Set_Framesize(uint16_t width,uint16_t height)
{
	if( (width%4)||(height%4) )   // 输出图像的大小一定要能被4整除
   {
       return OV2640_Error;  // 返回错误标志
   }
	 
	SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_DSP);	// 选择 DSP寄存器组

	SCCB_WriteReg(0X5A, width/4  &0XFF);		// 实际图像输出的宽度（OUTW），7~0 bit，寄存器的值等于实际值/4
	SCCB_WriteReg(0X5B, height/4 &0XFF);		// 实际图像输出的高度（OUTH），7~0 bit，寄存器的值等于实际值/4
	SCCB_WriteReg(0X5C, (width/4>>8&0X03)|(height/4>>6&0x04) );	 // 设置ZMHH的Bit[2:0]，也就是OUTH 的第 8 bit，OUTW 的第 9~8 bit，

	SCCB_WriteReg(OV2640_DSP_RESET,0X00);	   // 复位

	return OV2640_Success;  // 成功
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Horizontal_Mirror
*
*	入口参数:  ConfigState - 置1时，图像会水平镜像，置0时恢复正常
*
*	函数功能: 用于设置输出的图像是否进行水平镜像
*
*****************************************************************************************************************************************/
int8_t OV2640_Set_Horizontal_Mirror( int8_t ConfigState )
{
   uint8_t OV2640_Reg;  // 寄存器的值

   SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_SENSOR);	// 选择 SENSOR 寄存器组
   OV2640_Reg = SCCB_ReadReg(OV2640_SENSOR_REG04);          // 读取 0x04 的寄存器值

// REG04,寄存器组4，寄存器地址为 0x04，该寄存器的Bit[7]，用于设置水平是否镜像
   if ( ConfigState == OV2640_Enable )    // 如果使能镜像
   { 
      OV2640_Reg |= 0X80;  // Bit[7]置1则镜像	 
   } 
   else                    // 取消镜像
   {
      OV2640_Reg &= ~0X80; // Bit[7]置0则是正常模式
   }
   return  SCCB_WriteReg(OV2640_SENSOR_REG04,OV2640_Reg);   // 写入寄存器
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Vertical_Flip
*
*	入口参数:  ConfigState - 置1时，图像会垂直翻转，置0时恢复正常
*
*	函数功能: 用于设置输出的图像是否进行垂直翻转
*
*****************************************************************************************************************************************/
int8_t OV2640_Set_Vertical_Flip( int8_t ConfigState )
{
   uint8_t OV2640_Reg;  // 寄存器的值

   SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_SENSOR);	// 选择 SENSOR 寄存器组
   OV2640_Reg = SCCB_ReadReg(OV2640_SENSOR_REG04);          // 读取 0x04 的寄存器值

// REG04,寄存器组4，寄存器地址为 0x04，该寄存器的第Bit[6]，用于设置水平是垂直翻转
   if ( ConfigState == OV2640_Enable )   
   { 
      // 此处设置参考OpenMV的驱动
      // Bit[4]具体的作用是什么手册没有说，如果垂直翻转之后，该位不置1的话，颜色会不对
      OV2640_Reg |= 0X40|0x10 ;     // Bit[6]置1时，图像会垂直翻转
   } 
   else   // 取消翻转
   {
      OV2640_Reg &= ~(0X40|0x10 ); // 将Bit[6]和Bit[4]都写0
   }
   return  SCCB_WriteReg(OV2640_SENSOR_REG04,OV2640_Reg);   // 写入寄存器
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Saturation
*
*	入口参数:  Saturation - 饱和度，可设置为5个等级：2，1，0，-1，-2                   
*
*	说    明: 1. 手册里没有说明配置中的那2个寄存器如何使用，因此这里直接使用OV2640编程手册给出的代码
*            2.饱和度越高，色彩就越鲜艳，但当相应的清晰度会下降，噪点变多
*
*****************************************************************************************************************************************/
void OV2640_Set_Saturation(int8_t Saturation)
{
	SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_DSP);	// 选择 DSP寄存器组

   switch (Saturation)
   {
      case 2:      
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x02);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x03);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x68);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x68);	         
      break;
      
      case 1:    
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x02);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x03);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x58);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x58);	          
      break;

      case 0:         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x02);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x03);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x48);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x48);	       
      break;

      case -1: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x02);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x03);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x38);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x38);	       
      break;

      case -2: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x02);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x03);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x28);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x28);	       
      break;

      default: break;  
   }
}

/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Brightness
*
*	入口参数:  Brightness - 亮度，可设置为5个等级：2，1，0，-1，-2                   
*
*	说    明: 1. 手册里没有说明配置中的那2个寄存器如何使用，因此这里直接使用OV2640编程手册给出的代码
*           2. 亮度越高，画面就越明亮，但是会变模糊一些
*
*****************************************************************************************************************************************/
void OV2640_Set_Brightness(int8_t Brightness)
{
	SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_DSP);	// 选择 DSP寄存器组

   switch (Brightness)
   {
      case 2:      
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x09);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x40);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	         
      break;
      
      case 1:    
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x09);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x30);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	            
      break;

      case 0:         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x09);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	       
      break;

      case -1: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x09);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x10);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	          
      break;

      case -2: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x09);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	      
      break;

      default: break;  
   }
}
/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Contrast
*
*	入口参数: Contrast - 对比度，可设置为5个等级：2，1，0，-1，-2                   
*
*	说    明: 1. 手册里没有说明配置中的那2个寄存器如何使用，因此这里直接使用OV2640编程手册给出的代码
*            2. 对比度越高，画面越清晰，黑白越加分明
*
*****************************************************************************************************************************************/
void OV2640_Set_Contrast(int8_t Contrast)
{
	SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_DSP);	// 选择 DSP寄存器组

   switch (Contrast)
   {
      case 2:      
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x07);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x28);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x0c);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x06);	         
      break;
      
      case 1:    
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x07);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x24);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x16);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x06);	             
      break;

      case 0:         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x07);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x20);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x06);	         
      break;

      case -1: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x07);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x1c);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x2a);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x06);	              
      break;

      case -2: 
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x04);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x07);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x20);         
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x18);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x34);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x06);	         
      break;

      default: break;  
   }
}
/***************************************************************************************************************************************
*	函 数 名: OV2640_Set_Effect
*
*	入口参数:  effect_Mode - 特效模式，可选择参数 OV2640_Effect_Normal、OV2640_Effect_Negative、
*                          OV2640_Effect_BW、OV2640_Effect_BW_Negative
*
*	函数功能: 用于设置OV2640的特效，正常、负片、黑白、黑白+负片等模式
*
*	说    明: 手册里没有说明配置中的那2个寄存器如何使用，因此这里直接使用OV2640编程手册给出的代码
*
*****************************************************************************************************************************************/
void OV2640_Set_Effect(uint8_t effect_Mode)
{
	SCCB_WriteReg(OV2640_SEL_Registers,OV2640_SEL_DSP);	// 选择 DSP寄存器组

   switch (effect_Mode)
   {
      case OV2640_Effect_Normal:       // 正常模式
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x05);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	         
      break;
      
      case OV2640_Effect_Negative:     // 负片模式，也就是颜色全部取反
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x40);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x05);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	          
      break;

      case OV2640_Effect_BW:          // 黑白模式
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x18);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x05);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	       
      break;

      case OV2640_Effect_BW_Negative: // 黑白+负片模式
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x00);	
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x58);	
         SCCB_WriteReg(OV2640_DSP_BPADDR,0x05);	   
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	 
         SCCB_WriteReg(OV2640_DSP_BPDATA,0x80);	       
      break;

      default: break;  
   }
}

/***************************************************************************************************************************************
*	函 数 名: HAL_DCMI_FrameEventCallback
*
*	函数功能: 帧回调函数，每传输一帧数据，会进入该中断服务函数
*
*	说    明: 每次传输完一帧，对相应的标志位进行操作，并计算帧率
*****************************************************************************************************************************************/
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	static uint32_t DCMI_Tick = 0;         // 用于保存当前的时间计数值
   static uint8_t DCMI_Frame_Count = 0;   // 帧数计数   

 	if(HAL_GetTick() - DCMI_Tick >= 1000)    // 每隔 1s 计算一次帧率
	{
		DCMI_Tick = HAL_GetTick();            // 重新获取当前时间计数值
		OV2640_FPS = DCMI_Frame_Count;   // 获得fps 
		DCMI_Frame_Count = 0;            // 计数清0
	}
	DCMI_Frame_Count ++;    // 没进入一次中断（每次传输完一帧数据），计数值+1

   DCMI_FrameState = 1;  // 传输完成标志位置1
}

/***************************************************************************************************************************************
*	函 数 名: HAL_DCMI_ErrorCallback
*
*	函数功能: 错误回调函数
*
*	说    明: 当发生DMA传输错误或者FIFO溢出错误就会进入
*****************************************************************************************************************************************/

void  HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{
   // if( HAL_DCMI_GetError(hdcmi) == HAL_DCMI_ERROR_OVR)
   // {
   //    printf("FIFO溢出错误！！！\r\n");
   // }
//   printf("error:0x%x！！！\r\n",HAL_DCMI_GetError(hdcmi));
}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
