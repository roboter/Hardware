/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : spi.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
	* @note:     ��ʹ�ô�ͷ�ļ�ʱ����ȷ����ص�����������ȷ���ã�
	*
	* @contact:  ΢�Ź��ں� - [GenBotter]��������������
  *            QQȺ�� - [366182133]�����߼���֧��
  *            �Ա����� - [https://genbotter.taobao.com]���ṩ����Ӳ����Ʒ
	*
>>>>> ��Ҫ˵����
	*
	*  1.��Ļ����Ϊ16λRGB565��ʽ
	*  2.SPIͨ���ٶ�Ϊ60M������ LCD_Clear() ����ʱ��Ϊ18ms��ԼΪ55.5֡
   *
>>>>> ����˵����
	*
	*	1. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ���û����Ը�����������������ɾ��
	*	2. ���������Ĺ��ܺ�ʹ�ÿ��Բο�������˵��
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi4;

#define  LCD_SPI hspi4           // SPI�ֲ��꣬�����޸ĺ���ֲ

static pFONT *LCD_AsciiFonts;		// Ӣ�����壬ASCII�ַ���
static pFONT *LCD_CHFonts;		   // �������壨ͬʱҲ����Ӣ�����壩

static int  _pointx=0;
static int 	_pointy=0;
unsigned char ScreenBuffer[8][240]={0};   //8  240
TypeRoate _RoateValue={{0,0},0,1}; //������ת�����������Ϣ

// ��Ϊ����SPI����Ļ��ÿ�θ�����ʾʱ����Ҫ����������������д�Դ棬
// ����ʾ�ַ�ʱ�������һ������ȥд����д�Դ棬��ǳ�����
// ��˿���һƬ���������Ƚ���Ҫ��ʾ������д�������������������д���Դ档
// �û����Ը���ʵ�����ȥ�޸Ĵ˴��������Ĵ�С��
// ���磬�û���Ҫ��ʾ32*32�ĺ���ʱ����Ҫ�Ĵ�СΪ 32*32*2 = 2048 �ֽڣ�ÿ�����ص�ռ2�ֽڣ�
uint16_t  LCD_Buff[1024];        // LCD��������16λ����ÿ�����ص�ռ2�ֽڣ�

struct	//LCD��ز����ṹ��
{
	uint32_t Color;  				//	LCD��ǰ������ɫ
	uint32_t BackColor;			//	����ɫ
   uint8_t  ShowNum_Mode;		// ������ʾģʽ
	uint8_t  Direction;			//	��ʾ����
   uint16_t Width;            // ��Ļ���س���
   uint16_t Height;           // ��Ļ���ؿ���
   uint8_t  X_Offset;         // X����ƫ�ƣ�����������Ļ���������Դ�д�뷽ʽ
   uint8_t  Y_Offset;         // Y����ƫ�ƣ�����������Ļ���������Դ�д�뷽ʽ
}LCD;

// �ú����޸���HAL��SPI�⺯����רΪ LCD_Clear() ���������޸ģ�
// Ŀ����Ϊ��SPI�������ݲ������ݳ��ȵ�д��
HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t pData, uint32_t Size);
HAL_StatusTypeDef LCD_SPI_TransmitBuffer (SPI_HandleTypeDef *hspi, uint16_t *pData, uint32_t Size);


/* SPI4 init function */
void MX_SPI4_Init(void)
{

  /* USER CODE BEGIN SPI4_Init 0 */

  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */

  /* USER CODE END SPI4_Init 1 */
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_HARD_OUTPUT;

  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;

  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 0x0;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
  hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspInit 0 */

  /* USER CODE END SPI4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
    PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* SPI4 clock enable */
    __HAL_RCC_SPI4_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**SPI4 GPIO Configuration
    PE11     ------> SPI4_NSS
    PE12     ------> SPI4_SCK
    PE14     ------> SPI4_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// ��ʼ�� ���� ����
		GPIO_InitStruct.Pin 		= LCD_Backlight_PIN;				// ���� ����
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// �������ģʽ
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;						// ��������
		GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// �ٶȵȼ���
		HAL_GPIO_Init(LCD_Backlight_PORT, &GPIO_InitStruct);	// ��ʼ��

// ��ʼ�� ����ָ��ѡ�� ����
		GPIO_InitStruct.Pin 		= LCD_DC_PIN;				      // ����ָ��ѡ�� ����
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// �������ģʽ
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;						// ��������
		GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// �ٶȵȼ���
		HAL_GPIO_Init(LCD_DC_PORT, &GPIO_InitStruct);	      // ��ʼ��

  /* USER CODE BEGIN SPI4_MspInit 1 */

  /* USER CODE END SPI4_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI4)
  {
  /* USER CODE BEGIN SPI4_MspDeInit 0 */

  /* USER CODE END SPI4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI4_CLK_DISABLE();

    /**SPI4 GPIO Configuration
    PE11     ------> SPI4_NSS
    PE12     ------> SPI4_SCK
    PE14     ------> SPI4_MOSI
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14);

  /* USER CODE BEGIN SPI4_MspDeInit 1 */

  /* USER CODE END SPI4_MspDeInit 1 */
  }
}

/****************************************************************************************************************************************
*	�� �� ��: LCD_WriteCommand
*
*	��ڲ���: lcd_command - ��Ҫд��Ŀ���ָ��
*
*	��������: ��������Ļ������д��ָ��
*
****************************************************************************************************************************************/

void  LCD_WriteCommand(uint8_t lcd_command)
{
   LCD_DC_Command;     // ����ָ��ѡ�� ��������͵�ƽ���������δ��� ָ��

   HAL_SPI_Transmit(&LCD_SPI, &lcd_command, 1, 1000); // ����SPI����
}

/****************************************************************************************************************************************
*	�� �� ��: LCD_WriteData_8bit
*
*	��ڲ���: lcd_data - ��Ҫд������ݣ�8λ
*
*	��������: д��8λ����
*
****************************************************************************************************************************************/

void  LCD_WriteData_8bit(uint8_t lcd_data)
{
   LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

   HAL_SPI_Transmit(&LCD_SPI, &lcd_data, 1, 1000) ; // ����SPI����
}

/****************************************************************************************************************************************
*	�� �� ��: LCD_WriteData_16bit
*
*	��ڲ���: lcd_data - ��Ҫд������ݣ�16λ
*
*	��������: д��16λ����
*
****************************************************************************************************************************************/

void  LCD_WriteData_16bit(uint16_t lcd_data)
{
   uint8_t lcd_data_buff[2];    // ���ݷ�����
   LCD_DC_Data;      // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

   lcd_data_buff[0] = lcd_data>>8;  // �����ݲ��
   lcd_data_buff[1] = lcd_data;

	HAL_SPI_Transmit(&LCD_SPI, lcd_data_buff, 2, 1000) ;   // ����SPI����
}

/****************************************************************************************************************************************
*	�� �� ��: LCD_WriteBuff
*
*	��ڲ���: DataBuff - ��������DataSize - ���ݳ���
*
*	��������: ����д�����ݵ���Ļ
*
****************************************************************************************************************************************/

void  LCD_WriteBuff(uint16_t *DataBuff, uint16_t DataSize)
{
	LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

// �޸�Ϊ16λ���ݿ��ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
   LCD_SPI.Init.DataSize 	= SPI_DATASIZE_16BIT;   //	16λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

	HAL_SPI_Transmit(&LCD_SPI, (uint8_t *)DataBuff, DataSize, 1000) ; // ����SPI����

// �Ļ�8λ���ݿ��ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
	LCD_SPI.Init.DataSize 	= SPI_DATASIZE_8BIT;    //	8λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);
}

/****************************************************************************************************************************************
*	�� �� ��: SPI_LCD_Init
*
*	��������: ��ʼ��SPI�Լ���Ļ�������ĸ��ֲ���
*
****************************************************************************************************************************************/

void SPI_LCD_Init(void)
{
   MX_SPI4_Init();               // ��ʼ��SPI�Ϳ�������

   HAL_Delay(10);               	// ��Ļ����ɸ�λʱ�������ϵ縴λ������Ҫ�ȴ�����5ms���ܷ���ָ��

 	LCD_WriteCommand(0x36);       // �Դ���ʿ��� ָ��������÷����Դ�ķ�ʽ
	LCD_WriteData_8bit(0x00);     // ���ó� ���ϵ��¡������ң�RGB���ظ�ʽ

	LCD_WriteCommand(0x3A);			// �ӿ����ظ�ʽ ָ���������ʹ�� 12λ��16λ����18λɫ
	LCD_WriteData_8bit(0x05);     // �˴����ó� 16λ ���ظ�ʽ

// �������ܶ඼�ǵ�ѹ����ָ�ֱ��ʹ�ó��Ҹ��趨ֵ
 	LCD_WriteCommand(0xB2);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x00);
	LCD_WriteData_8bit(0x33);
	LCD_WriteData_8bit(0x33);

	LCD_WriteCommand(0xB7);		   // դ����ѹ����ָ��
	LCD_WriteData_8bit(0x35);     // VGH = 13.26V��VGL = -10.43V

	LCD_WriteCommand(0xBB);			// ������ѹ����ָ��
	LCD_WriteData_8bit(0x19);     // VCOM = 1.35V

	LCD_WriteCommand(0xC0);
	LCD_WriteData_8bit(0x2C);

	LCD_WriteCommand(0xC2);       // VDV �� VRH ��Դ����
	LCD_WriteData_8bit(0x01);     // VDV �� VRH ���û���������

	LCD_WriteCommand(0xC3);			// VRH��ѹ ����ָ��
	LCD_WriteData_8bit(0x12);     // VRH��ѹ = 4.6+( vcom+vcom offset+vdv)

	LCD_WriteCommand(0xC4);		   // VDV��ѹ ����ָ��
	LCD_WriteData_8bit(0x20);     // VDV��ѹ = 0v

	LCD_WriteCommand(0xC6); 		// ����ģʽ��֡�ʿ���ָ��
	LCD_WriteData_8bit(0x0F);   	// ������Ļ��������ˢ��֡��Ϊ60֡

	LCD_WriteCommand(0xD0);			// ��Դ����ָ��
	LCD_WriteData_8bit(0xA4);     // ��Ч���ݣ��̶�д��0xA4
	LCD_WriteData_8bit(0xA1);     // AVDD = 6.8V ��AVDD = -4.8V ��VDS = 2.3V

	LCD_WriteCommand(0xE0);       // ������ѹ٤��ֵ�趨
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2B);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x54);
	LCD_WriteData_8bit(0x4C);
	LCD_WriteData_8bit(0x18);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x0B);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0xE1);      // ������ѹ٤��ֵ�趨
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2C);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x44);
	LCD_WriteData_8bit(0x51);
	LCD_WriteData_8bit(0x2F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x20);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0x21);       // �򿪷��ԣ���Ϊ����ǳ����ͣ�������Ҫ������

 // �˳�����ָ�LCD�������ڸ��ϵ硢��λʱ�����Զ���������ģʽ ����˲�����Ļ֮ǰ����Ҫ�˳�����
	LCD_WriteCommand(0x11);       // �˳����� ָ��
   HAL_Delay(120);               // ��Ҫ�ȴ�120ms���õ�Դ��ѹ��ʱ�ӵ�·�ȶ�����

 // ����ʾָ�LCD�������ڸ��ϵ硢��λʱ�����Զ��ر���ʾ
	LCD_WriteCommand(0x29);       // ����ʾ

// ���½���һЩ������Ĭ������
	LCD_SetDirection(Direction_V);  	      //	������ʾ����
	LCD_SetBackColor(LCD_BLACK);           // ���ñ���ɫ
 	LCD_SetColor(LCD_WHITE);               // ���û���ɫ
	LCD_Clear();                           // ����

   LCD_SetAsciiFont(&ASCII_Font24);       // ����Ĭ������
   LCD_ShowNumMode(Fill_Zero);	      	// ���ñ�����ʾģʽ������λ���ո������0

// ȫ���������֮�󣬴򿪱���
   LCD_Backlight_ON;  // ��������ߵ�ƽ��������
}

/****************************************************************************************************************************************
*	�� �� ��:	 LCD_SetAddress
*
*	��ڲ���:	 x1 - ��ʼˮƽ����   y1 - ��ʼ��ֱ����
*              x2 - �յ�ˮƽ����   y2 - �յ㴹ֱ����
*
*	��������:   ������Ҫ��ʾ����������
*****************************************************************************************************************************************/

void LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD_WriteCommand(0x2a);			//	�е�ַ���ã���X����
	LCD_WriteData_16bit(x1+LCD.X_Offset);
	LCD_WriteData_16bit(x2+LCD.X_Offset);

	LCD_WriteCommand(0x2b);			//	�е�ַ���ã���Y����
	LCD_WriteData_16bit(y1+LCD.Y_Offset);
	LCD_WriteData_16bit(y2+LCD.Y_Offset);

	LCD_WriteCommand(0x2c);			//	��ʼд���Դ棬��Ҫ��ʾ����ɫ����
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_SetColor
*
*	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0x0000FF ��ʾ��ɫ
*
*	��������:	�˺����������û��ʵ���ɫ��������ʾ�ַ������㻭�ߡ���ͼ����ɫ
*
*	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��24λ RGB888����ɫ��ʽ���û����������ɫ��ʽ��ת��
*					2. 24λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ R��G��B  3����ɫͨ��
*
*****************************************************************************************************************************************/

void LCD_SetColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ

	Red_Value   = (uint16_t)((Color&0x00F80000)>>8);   // ת���� 16λ ��RGB565��ɫ
	Green_Value = (uint16_t)((Color&0x0000FC00)>>5);
	Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);

	LCD.Color = (uint16_t)(Red_Value | Green_Value | Blue_Value);  // ����ɫд��ȫ��LCD����
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_SetBackColor
*
*	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0x0000FF ��ʾ��ɫ
*
*	��������:	���ñ���ɫ,�˺������������Լ���ʾ�ַ��ı���ɫ
*
*	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��24λ RGB888����ɫ��ʽ���û����������ɫ��ʽ��ת��
*					2. 24λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ R��G��B  3����ɫͨ��
*
*****************************************************************************************************************************************/

void LCD_SetBackColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ

	Red_Value   = (uint16_t)((Color&0x00F80000)>>8);   // ת���� 16λ ��RGB565��ɫ
	Green_Value = (uint16_t)((Color&0x0000FC00)>>5);
	Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);

	LCD.BackColor = (uint16_t)(Red_Value | Green_Value | Blue_Value);	// ����ɫд��ȫ��LCD����
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_SetDirection
*
*	��ڲ���:	direction - Ҫ��ʾ�ķ���
*
*	��������:	����Ҫ��ʾ�ķ���
*
*	˵    ��:   1. ��������� Direction_H ��Direction_V ��Direction_H_Flip ��Direction_V_Flip
*              2. ʹ��ʾ�� LCD_DisplayDirection(Direction_H) ����������Ļ������ʾ
*
*****************************************************************************************************************************************/

void LCD_SetDirection(uint8_t direction)
{
	LCD.Direction = direction;    // д��ȫ��LCD����

   if( direction == Direction_H )   // ������ʾ
   {
      LCD_WriteCommand(0x36);    		// �Դ���ʿ��� ָ��������÷����Դ�ķ�ʽ
      LCD_WriteData_8bit(0x70);        // ������ʾ
      LCD.X_Offset   = 20;             // ���ÿ���������ƫ����
      LCD.Y_Offset   = 0;
      LCD.Width      = LCD_Height;		// ���¸�ֵ������
      LCD.Height     = LCD_Width;
   }
   else if( direction == Direction_V )
   {
      LCD_WriteCommand(0x36);    		// �Դ���ʿ��� ָ��������÷����Դ�ķ�ʽ
      LCD_WriteData_8bit(0x00);        // ��ֱ��ʾ
      LCD.X_Offset   = 0;              // ���ÿ���������ƫ����
      LCD.Y_Offset   = 20;
      LCD.Width      = LCD_Width;		// ���¸�ֵ������
      LCD.Height     = LCD_Height;
   }
   else if( direction == Direction_H_Flip )
   {
      LCD_WriteCommand(0x36);   			 // �Դ���ʿ��� ָ��������÷����Դ�ķ�ʽ
      LCD_WriteData_8bit(0xA0);         // ������ʾ�������·�ת��RGB���ظ�ʽ
      LCD.X_Offset   = 20;              // ���ÿ���������ƫ����
      LCD.Y_Offset   = 0;
      LCD.Width      = LCD_Height;		 // ���¸�ֵ������
      LCD.Height     = LCD_Width;
   }
   else if( direction == Direction_V_Flip )
   {
      LCD_WriteCommand(0x36);    		// �Դ���ʿ��� ָ��������÷����Դ�ķ�ʽ
      LCD_WriteData_8bit(0xC0);        // ��ֱ��ʾ �������·�ת��RGB���ظ�ʽ
      LCD.X_Offset   = 0;              // ���ÿ���������ƫ����
      LCD.Y_Offset   = 20;
      LCD.Width      = LCD_Width;		// ���¸�ֵ������
      LCD.Height     = LCD_Height;
   }
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_SetAsciiFont
*
*	��ڲ���:	*fonts - Ҫ���õ�ASCII����
*
*	��������:	����ASCII���壬��ѡ��ʹ�� 3216/2412/2010/1608/1206 ���ִ�С������
*
*	˵    ��:	1. ʹ��ʾ�� LCD_SetAsciiFont(&ASCII_Font24) �������� 2412�� ASCII����
*					2. �����ģ����� lcd_fonts.c
*
*****************************************************************************************************************************************/

void LCD_SetAsciiFont(pFONT *Asciifonts)
{
  LCD_AsciiFonts = Asciifonts;
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_Clear
*
*	��������:	������������LCD���Ϊ LCD.BackColor ����ɫ
*
*	˵    ��:	���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
*
*****************************************************************************************************************************************/

void LCD_Clear(void)
{
   LCD_SetAddress(0,0,LCD.Width-1,LCD.Height-1);	// ��������

	LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

// �޸�Ϊ16λ���ݿ��ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
   LCD_SPI.Init.DataSize 	= SPI_DATASIZE_16BIT;   //	16λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

   LCD_SPI_Transmit(&LCD_SPI, LCD.BackColor, LCD.Width * LCD.Height) ;   // ��������

// �Ļ�8λ���ݿ��ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
	LCD_SPI.Init.DataSize 	= SPI_DATASIZE_8BIT;    //	8λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_ClearRect
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					width  - Ҫ�������ĺ��򳤶�
*					height - Ҫ���������������
*
*	��������:	�ֲ�������������ָ��λ�ö�Ӧ���������Ϊ LCD.BackColor ����ɫ
*
*	˵    ��:	1. ���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
*				   2. ʹ��ʾ�� LCD_ClearRect( 10, 10, 100, 50) ���������(10,10)��ʼ�ĳ�100��50������
*
*****************************************************************************************************************************************/

void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
   LCD_SetAddress( x, y, x+width-1, y+height-1);	// ��������

	LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

// �޸�Ϊ16λ���ݿ��ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
   LCD_SPI.Init.DataSize 	= SPI_DATASIZE_16BIT;   //	16λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

   LCD_SPI_Transmit(&LCD_SPI, LCD.BackColor, width*height) ;  // ��������

// �Ļ�8λ���ݿ��ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
	LCD_SPI.Init.DataSize 	= SPI_DATASIZE_8BIT;    //	8λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_DrawPoint
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					color  - Ҫ���Ƶ���ɫ��ʹ�� 24λ RGB888 ����ɫ��ʽ���û����������ɫ��ʽ��ת��
*
*	��������:	��ָ���������ָ����ɫ�ĵ�
*
*	˵    ��:	ʹ��ʾ�� LCD_DrawPoint( 10, 10, 0x0000FF) ��������(10,10)������ɫ�ĵ�
*
*****************************************************************************************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color)
{
	LCD_SetAddress(x,y,x,y);	//	��������

	LCD_WriteData_16bit(color)	;
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayChar
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					c  - ASCII�ַ�
*
*	��������:	��ָ��������ʾָ�����ַ�
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetAsciiFont(&ASCII_Font24) ����Ϊ 2412��ASCII����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0x000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayChar( 10, 10, 'a') ��������(10,10)��ʾ�ַ� 'a'
*
*****************************************************************************************************************************************/

void LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c)
{
	uint16_t  index = 0, counter = 0 ,i = 0, w = 0;		// ��������
   uint8_t   disChar;		//�洢�ַ��ĵ�ַ

	c = c - 32; 	// ����ASCII�ַ���ƫ��

	for(index = 0; index < LCD_AsciiFonts->Sizes; index++)
	{
		disChar = LCD_AsciiFonts->pTable[c*LCD_AsciiFonts->Sizes + index]; //��ȡ�ַ���ģֵ
		for(counter = 0; counter < 8; counter++)
		{
			if(disChar & 0x01)
			{
            LCD_Buff[i] =  LCD.Color;			// ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
			}
			else
			{
            LCD_Buff[i] = LCD.BackColor;		//����ʹ�ñ���ɫ���Ƶ�
			}
			disChar >>= 1;
			i++;
         w++;
 			if( w == LCD_AsciiFonts->Width ) // ���д������ݴﵽ���ַ����ȣ����˳���ǰѭ��
			{								   // ������һ�ַ���д��Ļ���
				w = 0;
				break;
			}
		}
	}
   LCD_SetAddress( x, y, x+LCD_AsciiFonts->Width-1, y+LCD_AsciiFonts->Height-1);	   // ��������
   LCD_WriteBuff(LCD_Buff,LCD_AsciiFonts->Width*LCD_AsciiFonts->Height);          // д���Դ�
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayString
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					p - ASCII�ַ������׵�ַ
*
*	��������:	��ָ��������ʾָ�����ַ���
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetAsciiFont(&ASCII_Font24) ����Ϊ 2412��ASCII����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0x0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0x000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayString( 10, 10, "FANKE") ������ʼ����Ϊ(10,10)�ĵط���ʾ�ַ���"FANKE"
*
*****************************************************************************************************************************************/

void LCD_DisplayString( uint16_t x, uint16_t y, char *p)
{
	while ((x < LCD.Width) && (*p != 0))	//�ж���ʾ�����Ƿ񳬳���ʾ�������ַ��Ƿ�Ϊ���ַ�
	{
		 LCD_DisplayChar( x,y,*p);
		 x += LCD_AsciiFonts->Width; //��ʾ��һ���ַ�
		 p++;	//ȡ��һ���ַ���ַ
	}
}

/****************************************************************************************************************************************
*	�� �� ��:	LCD_SetTextFont
*
*	��ڲ���:	*fonts - Ҫ���õ��ı�����
*
*	��������:	�����ı����壬�������ĺ�ASCII�ַ���
*
*	˵    ��:	1. ��ѡ��ʹ�� 3232/2424/2020/1616/1212 ���ִ�С���������壬
*						���Ҷ�Ӧ������ASCII����Ϊ 3216/2412/2010/1608/1206
*					2. �����ģ����� lcd_fonts.c
*					3. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ
*					4. ʹ��ʾ�� LCD_SetTextFont(&CH_Font24) �������� 2424�����������Լ�2412��ASCII�ַ�����
*
*****************************************************************************************************************************************/

void LCD_SetTextFont(pFONT *fonts)
{
	LCD_CHFonts = fonts;		// ������������
	switch(fonts->Width )
	{
		case 12:	LCD_AsciiFonts = &ASCII_Font12;	break;	// ����ASCII�ַ�������Ϊ 1206
		case 16:	LCD_AsciiFonts = &ASCII_Font16;	break;	// ����ASCII�ַ�������Ϊ 1608
		case 20:	LCD_AsciiFonts = &ASCII_Font20;	break;	// ����ASCII�ַ�������Ϊ 2010
		case 24:	LCD_AsciiFonts = &ASCII_Font24;	break;	// ����ASCII�ַ�������Ϊ 2412
		case 32:	LCD_AsciiFonts = &ASCII_Font32;	break;	// ����ASCII�ַ�������Ϊ 3216
		default: break;
	}
}
/******************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayChinese
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					pText - �����ַ�
*
*	��������:	��ָ��������ʾָ���ĵ��������ַ�
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayChinese( 10, 10, "��") ��������(10,10)��ʾ�����ַ�"��"
*
*****************************************************************************************************************************************/

void LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText)
{
	uint16_t  i=0,index = 0, counter = 0;	// ��������
	uint16_t  addr;	// ��ģ��ַ
   uint8_t   disChar;	//��ģ��ֵ
	uint16_t  Xaddress = 0; //ˮƽ����

	while(1)
	{
		// �Ա������еĺ��ֱ��룬���Զ�λ�ú�����ģ�ĵ�ַ
		if ( *(LCD_CHFonts->pTable + (i+1)*LCD_CHFonts->Sizes + 0)==*pText && *(LCD_CHFonts->pTable + (i+1)*LCD_CHFonts->Sizes + 1)==*(pText+1) )
		{
			addr=i;	// ��ģ��ַƫ��
			break;
		}
		i+=2;	// ÿ�������ַ�����ռ���ֽ�

		if(i >= LCD_CHFonts->Table_Rows)	break;	// ��ģ�б�������Ӧ�ĺ���
	}
	i=0;
	for(index = 0; index <LCD_CHFonts->Sizes; index++)
	{
		disChar = *(LCD_CHFonts->pTable + (addr)*LCD_CHFonts->Sizes + index);	// ��ȡ��Ӧ����ģ��ַ

		for(counter = 0; counter < 8; counter++)
		{
			if(disChar & 0x01)
			{
            LCD_Buff[i] =  LCD.Color;			// ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
			}
			else
			{
            LCD_Buff[i] = LCD.BackColor;		// ����ʹ�ñ���ɫ���Ƶ�
			}
         i++;
			disChar >>= 1;
			Xaddress++;  //ˮƽ�����Լ�

			if( Xaddress == LCD_CHFonts->Width ) 	//	���ˮƽ����ﵽ���ַ����ȣ����˳���ǰѭ��
			{														//	������һ�еĻ���
				Xaddress = 0;
				break;
			}
		}
	}
   LCD_SetAddress( x, y, x+LCD_CHFonts->Width-1, y+LCD_CHFonts->Height-1);	   // ��������
   LCD_WriteBuff(LCD_Buff,LCD_CHFonts->Width*LCD_CHFonts->Height);            // д���Դ�
}

/*****************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayText
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					pText - �ַ�����������ʾ���Ļ���ASCII�ַ�
*
*	��������:	��ָ��������ʾָ�����ַ���
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayChinese( 10, 10, "���ͿƼ�STM32") ��������(10,10)��ʾ�ַ���"���ͿƼ�STM32"
*
**********************************************************************************************************************************fanke*******/

void LCD_DisplayText(uint16_t x, uint16_t y, char *pText)
{

	while(*pText != 0)	// �ж��Ƿ�Ϊ���ַ�
	{
		if(*pText<=0x7F)	// �ж��Ƿ�ΪASCII��
		{
			LCD_DisplayChar(x,y,*pText);	// ��ʾASCII
			x+=LCD_AsciiFonts->Width;				// ˮƽ���������һ���ַ���
			pText++;								// �ַ�����ַ+1
		}
		else					// ���ַ�Ϊ����
		{
			LCD_DisplayChinese(x,y,pText);	// ��ʾ����
			x+=LCD_CHFonts->Width;				// ˮƽ���������һ���ַ���
			pText+=2;								// �ַ�����ַ+2�����ֵı���Ҫ2�ֽ�
		}
	}
}

/*****************************************************************************************************************************************
*	�� �� ��:	LCD_ShowNumMode
*
*	��ڲ���:	mode - ���ñ�������ʾģʽ
*
*	��������:	���ñ�����ʾʱ����λ��0���ǲ��ո񣬿�������� Fill_Space ���ո�Fill_Zero �����
*
*	˵    ��:   1. ֻ�� LCD_DisplayNumber() ��ʾ���� �� LCD_DisplayDecimals()��ʾС�� �����������õ�
*					2. ʹ��ʾ�� LCD_ShowNumMode(Fill_Zero) ���ö���λ���0������ 123 ������ʾΪ 000123
*
*****************************************************************************************************************************************/

void LCD_ShowNumMode(uint8_t mode)
{
	LCD.ShowNum_Mode = mode;
}

/*****************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayNumber
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					number - Ҫ��ʾ������,��Χ�� -2147483648~2147483647 ֮��
*					len - ���ֵ�λ�������λ������len��������ʵ�ʳ�������������Ҫ��ʾ��������Ԥ��һ��λ�ķ�����ʾ�ռ�
*
*	��������:	��ָ��������ʾָ������������
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetAsciiFont(&ASCII_Font24) ����Ϊ��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0x0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0x000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayNumber( 10, 10, a, 5) ��������(10,10)��ʾָ������a,�ܹ�5λ������λ��0��ո�
*						���� a=123 ʱ������� LCD_ShowNumMode()����������ʾ  123(ǰ�������ո�λ) ����00123
*
*****************************************************************************************************************************************/

void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number, uint8_t len)
{
	char   Number_Buffer[15];				// ���ڴ洢ת������ַ���

	if( LCD.ShowNum_Mode == Fill_Zero)	// ����λ��0
	{
		sprintf( Number_Buffer , "%.*ld",len, (long)number );	// �� number ת�����ַ�����������ʾ
	}
	else			// ����λ���ո�
	{
		sprintf( Number_Buffer , "%*ld",len, (long)number );	// �� number ת�����ַ�����������ʾ
	}

	LCD_DisplayString( x, y,(char *)Number_Buffer) ;  // ��ת���õ����ַ�����ʾ����

}

/***************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayDecimals
*
*	��ڲ���:	x - ��ʼˮƽ����
*					y - ��ʼ��ֱ����
*					decimals - Ҫ��ʾ������, double��ȡֵ1.7 x 10^��-308��~ 1.7 x 10^��+308����������ȷ��׼ȷ����Чλ��Ϊ15~16λ
*
*       			len - ������������λ��������С����͸��ţ�����ʵ�ʵ���λ��������ָ������λ��������ʵ�ʵ��ܳ���λ�����
*							ʾ��1��С�� -123.123 ��ָ�� len <=8 �Ļ�����ʵ���ճ���� -123.123
*							ʾ��2��С�� -123.123 ��ָ�� len =10 �Ļ�����ʵ�����   -123.123(����ǰ����������ո�λ)
*							ʾ��3��С�� -123.123 ��ָ�� len =10 �Ļ��������ú��� LCD_ShowNumMode() ����Ϊ���0ģʽʱ��ʵ����� -00123.123
*
*					decs - Ҫ������С��λ������С����ʵ��λ��������ָ����С��λ����ָ���Ŀ��������������
*							 ʾ����1.12345 ��ָ�� decs Ϊ4λ�Ļ�����������Ϊ1.1235
*
*	��������:	��ָ��������ʾָ���ı���������С��
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetAsciiFont(&ASCII_Font24) ����Ϊ��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0x0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0x000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayDecimals( 10, 10, a, 5, 3) ��������(10,10)��ʾ�ֱ���a,�ܳ���Ϊ5λ�����б���3λС��
*
*****************************************************************************************************************************************/

void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double decimals, uint8_t len, uint8_t decs)
{
	char  Number_Buffer[20];				// ���ڴ洢ת������ַ���

	if( LCD.ShowNum_Mode == Fill_Zero)	// ����λ���0ģʽ
	{
		sprintf( Number_Buffer , "%0*.*lf",len,decs, decimals );	// �� number ת�����ַ�����������ʾ
	}
	else		// ����λ���ո�
	{
		sprintf( Number_Buffer , "%*.*lf",len,decs, decimals );	// �� number ת�����ַ�����������ʾ
	}

	LCD_DisplayString( x, y,(char *)Number_Buffer) ;	// ��ת���õ����ַ�����ʾ����
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawLine
*
*	��ڲ���: x1 - ��� ˮƽ����
*			 	 y1 - ��� ��ֱ����
*
*				 x2 - �յ� ˮƽ����
*            y2 - �յ� ��ֱ����
*
*	��������: ������֮�仭��
*
*	˵    ��: �ú�����ֲ��ST�ٷ������������
*
*****************************************************************************************************************************************/

#define ABS(X)  ((X) > 0 ? (X) : -(X))

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

	deltax = ABS(x2 - x1);        /* The difference between the x's */
	deltay = ABS(y2 - y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1)                 /* The x-values are increasing */
	{
	 xinc1 = 1;
	 xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
	 xinc1 = -1;
	 xinc2 = -1;
	}

	if (y2 >= y1)                 /* The y-values are increasing */
	{
	 yinc1 = 1;
	 yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
	 yinc1 = -1;
	 yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
	 xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
	 yinc2 = 0;                  /* Don't change the y for every iteration */
	 den = deltax;
	 num = deltax / 2;
	 numadd = deltay;
	 numpixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
	 xinc2 = 0;                  /* Don't change the x for every iteration */
	 yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
	 den = deltay;
	 num = deltay / 2;
	 numadd = deltax;
	 numpixels = deltay;         /* There are more y-values than x-values */
	}
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
	 LCD_DrawPoint(x,y,LCD.Color);             /* Draw the current pixel */
	 num += numadd;              /* Increase the numerator by the top of the fraction */
	 if (num >= den)             /* Check if numerator >= denominator */
	 {
		num -= den;               /* Calculate the new numerator value */
		x += xinc1;               /* Change the x as appropriate */
		y += yinc1;               /* Change the y as appropriate */
	 }
	 x += xinc2;                 /* Change the x as appropriate */
	 y += yinc2;                 /* Change the y as appropriate */
	}
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawLine_V
*
*	��ڲ���: x - ˮƽ����
*			 	 y - ��ֱ����
*				 height - ��ֱ����
*
*	��������: ��ָ��λ�û���ָ�������� ��ֱ ��
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*            3. ���ֻ�ǻ���ֱ���ߣ�����ʹ�ô˺������ٶȱ� LCD_DrawLine ��ܶ�
*  ���ܲ��ԣ�
*****************************************************************************************************************************************/

void LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height)
{
   uint16_t i ; // ��������

	for (i = 0; i < height; i++)
	{
       LCD_Buff[i] =  LCD.Color;  // д�뻺����
   }
   LCD_SetAddress( x, y, x, y+height-1);	     // ��������

   LCD_WriteBuff(LCD_Buff,height);          // д���Դ�
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawLine_H
*
*	��ڲ���: x - ˮƽ����
*			 	 y - ��ֱ����
*				 width  - ˮƽ����
*
*	��������: ��ָ��λ�û���ָ�������� ˮƽ ��
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*            3. ���ֻ�ǻ� ˮƽ ���ߣ�����ʹ�ô˺������ٶȱ� LCD_DrawLine ��ܶ�
*  ���ܲ��ԣ�
**********************************************************************************************************************************fanke*******/

void LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width)
{
   uint16_t i ; // ��������

	for (i = 0; i < width; i++)
	{
       LCD_Buff[i] =  LCD.Color;  // д�뻺����
   }
   LCD_SetAddress( x, y, x+width-1, y);	     // ��������

   LCD_WriteBuff(LCD_Buff,width);          // д���Դ�
}
/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawRect
*
*	��ڲ���: x - ˮƽ����
*			 	 y - ��ֱ����
*			 	 width  - ˮƽ����
*				 height - ��ֱ����
*
*	��������: ��ָ��λ�û���ָ�������ľ�������
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
   // ����ˮƽ��
   LCD_DrawLine_H( x,  y,  width);
   LCD_DrawLine_H( x,  y+height-1,  width);

   // ���ƴ�ֱ��
   LCD_DrawLine_V( x,  y,  height);
   LCD_DrawLine_V( x+width-1,  y,  height);
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawCircle
*
*	��ڲ���: x - Բ�� ˮƽ����
*			 	 y - Բ�� ��ֱ����
*			 	 r  - �뾶
*
*	��������: ������ (x,y) ���ư뾶Ϊ r ��Բ������
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r)
{
	int Xadd = -r, Yadd = 0, err = 2-2*r, e2;
	do {

		LCD_DrawPoint(x-Xadd,y+Yadd,LCD.Color);
		LCD_DrawPoint(x+Xadd,y+Yadd,LCD.Color);
		LCD_DrawPoint(x+Xadd,y-Yadd,LCD.Color);
		LCD_DrawPoint(x-Xadd,y-Yadd,LCD.Color);

		e2 = err;
		if (e2 <= Yadd) {
			err += ++Yadd*2+1;
			if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
		}
		if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawEllipse
*
*	��ڲ���: x - Բ�� ˮƽ����
*			 	 y - Բ�� ��ֱ����
*			 	 r1  - ˮƽ����ĳ���
*				 r2  - ��ֱ����ĳ���
*
*	��������: ������ (x,y) ����ˮƽ����Ϊ r1 ��ֱ����Ϊ r2 ����Բ����
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_DrawEllipse(int x, int y, int r1, int r2)
{
  int Xadd = -r1, Yadd = 0, err = 2-2*r1, e2;
  float K = 0, rad1 = 0, rad2 = 0;

  rad1 = r1;
  rad2 = r2;

  if (r1 > r2)
  {
    do {
      K = (float)(rad1/rad2);

		LCD_DrawPoint(x-Xadd,y+(uint16_t)(Yadd/K),LCD.Color);
		LCD_DrawPoint(x+Xadd,y+(uint16_t)(Yadd/K),LCD.Color);
		LCD_DrawPoint(x+Xadd,y-(uint16_t)(Yadd/K),LCD.Color);
		LCD_DrawPoint(x-Xadd,y-(uint16_t)(Yadd/K),LCD.Color);

      e2 = err;
      if (e2 <= Yadd) {
        err += ++Yadd*2+1;
        if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
      }
      if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);
  }
  else
  {
    Yadd = -r2;
    Xadd = 0;
    do {
      K = (float)(rad2/rad1);

		LCD_DrawPoint(x-(uint16_t)(Xadd/K),y+Yadd,LCD.Color);
		LCD_DrawPoint(x+(uint16_t)(Xadd/K),y+Yadd,LCD.Color);
		LCD_DrawPoint(x+(uint16_t)(Xadd/K),y-Yadd,LCD.Color);
		LCD_DrawPoint(x-(uint16_t)(Xadd/K),y-Yadd,LCD.Color);

      e2 = err;
      if (e2 <= Xadd) {
        err += ++Xadd*3+1;
        if (-Yadd == Xadd && e2 <= Yadd) e2 = 0;
      }
      if (e2 > Yadd) err += ++Yadd*3+1;
    }
    while (Yadd <= 0);
  }
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_FillCircle
*
*	��ڲ���: x - Բ�� ˮƽ����
*			 	 y - Բ�� ��ֱ����
*			 	 r  - �뾶
*
*	��������: ������ (x,y) ���뾶Ϊ r ��Բ������
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r)
{
  int32_t  D;    /* Decision Variable */
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */

  D = 3 - (r << 1);

  CurX = 0;
  CurY = r;

  while (CurX <= CurY)
  {
    if(CurY > 0)
    {
      LCD_DrawLine_V(x - CurX, y - CurY,2*CurY);
      LCD_DrawLine_V(x + CurX, y - CurY,2*CurY);
    }

    if(CurX > 0)
    {
		// LCD_DrawLine(x - CurY, y - CurX,x - CurY,y - CurX + 2*CurX);
		// LCD_DrawLine(x + CurY, y - CurX,x + CurY,y - CurX + 2*CurX);

      LCD_DrawLine_V(x - CurY, y - CurX,2*CurX);
      LCD_DrawLine_V(x + CurY, y - CurX,2*CurX);
    }
    if (D < 0)
    {
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
  LCD_DrawCircle(x, y, r);
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_FillRect
*
*	��ڲ���: x - ˮƽ����
*			 	 y - ��ֱ����
*			 	 width  - ˮƽ����
*				 height -��ֱ����
*
*	��������: ������ (x,y) ���ָ��������ʵ�ľ���
*
*	˵    ��: Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
   LCD_SetAddress( x, y, x+width-1, y+height-1);	// ��������

	LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

// �޸�Ϊ16λ���ݿ��ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
   LCD_SPI.Init.DataSize 	= SPI_DATASIZE_16BIT;   //	16λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

   LCD_SPI_Transmit(&LCD_SPI, LCD.Color, width*height) ;

// �Ļ�8λ���ݿ��ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
	LCD_SPI.Init.DataSize 	= SPI_DATASIZE_8BIT;    //	8λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawImage
*
*	��ڲ���: x - ��ʼˮƽ����
*				 y - ��ʼ��ֱ����
*			 	 width  - ͼƬ��ˮƽ����
*				 height - ͼƬ�Ĵ�ֱ����
*				*pImage - ͼƬ���ݴ洢�����׵�ַ
*
*	��������: ��ָ�����괦��ʾͼƬ
*
*	˵    ��: 1.Ҫ��ʾ��ͼƬ��Ҫ���Ƚ���ȡģ����ϤͼƬ�ĳ��ȺͿ���
*            2.ʹ�� LCD_SetColor() �������û���ɫ��LCD_SetBackColor() ���ñ���ɫ
*
*****************************************************************************************************************************************/

void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)
{
   uint8_t   disChar;	         // ��ģ��ֵ
	uint16_t  Xaddress = x;       // ˮƽ����
 	uint16_t  Yaddress = y;       // ��ֱ����
	uint16_t  i=0,j=0,m=0;        // ��������
	uint16_t  BuffCount = 0;      // ����������
   uint16_t  Buff_Height = 0;    // ������������

// ��Ϊ��������С���ޣ���Ҫ�ֶ��д��
   Buff_Height = (sizeof(LCD_Buff)/2) / height;    // ���㻺�����ܹ�д��ͼƬ�Ķ�����

	for(i = 0; i <height; i++)             // ѭ������д��
	{
		for(j = 0; j <(float)width/8; j++)
		{
			disChar = *pImage;

			for(m = 0; m < 8; m++)
			{
				if(disChar & 0x01)
				{
               LCD_Buff[BuffCount] =  LCD.Color;			// ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
				}
				else
				{
				   LCD_Buff[BuffCount] = LCD.BackColor;		//����ʹ�ñ���ɫ���Ƶ�
				}
				disChar >>= 1;     // ģֵ��λ
				Xaddress++;        // ˮƽ�����Լ�
				BuffCount++;       // ����������
				if( (Xaddress - x)==width ) // ���ˮƽ����ﵽ���ַ����ȣ����˳���ǰѭ��,������һ�еĻ���
				{
					Xaddress = x;
					break;
				}
			}
			pImage++;
		}
      if( BuffCount == Buff_Height*width  )  // �ﵽ�������������ɵ��������ʱ
      {
         BuffCount = 0; // ������������0

         LCD_SetAddress( x, Yaddress , x+width-1, Yaddress+Buff_Height-1);	// ��������
         LCD_WriteBuff(LCD_Buff,width*Buff_Height);          // д���Դ�

         Yaddress = Yaddress+Buff_Height;    // ������ƫ�ƣ���ʼд����һ��������
      }
      if( (i+1)== height ) // �������һ��ʱ
      {
         LCD_SetAddress( x, Yaddress , x+width-1,i+y);	   // ��������
         LCD_WriteBuff(LCD_Buff,width*(i+1+y-Yaddress));    // д���Դ�
      }
	}
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_CopyBuffer
*
*	��ڲ���: x - ��ʼˮƽ����
*				 y - ��ʼ��ֱ����
*			 	 width  - Ŀ�������ˮƽ����
*				 height - Ŀ������Ĵ�ֱ����
*				*pImage - ���ݴ洢�����׵�ַ
*
*	��������: ��ָ�����괦��ֱ�ӽ����ݸ��Ƶ���Ļ���Դ�
*
*	˵    ��: �������ƺ�������������ֲ LVGL ���߽�����ͷ�ɼ���ͼ����ʾ����
*
*****************************************************************************************************************************************/

void	LCD_CopyBuffer(uint16_t x, uint16_t y,uint16_t width,uint16_t height,uint16_t *DataBuff)
{

	LCD_SetAddress(x,y,x+width-1,y+height-1);

	LCD_DC_Data;     // ����ָ��ѡ�� ��������ߵ�ƽ���������δ��� ����

// �޸�Ϊ16λ���ݿ��ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
   LCD_SPI.Init.DataSize 	= SPI_DATASIZE_16BIT;   //	16λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

	LCD_SPI_TransmitBuffer(&LCD_SPI, DataBuff,width * height) ;

//	HAL_SPI_Transmit(&hspi5, (uint8_t *)DataBuff, (x2-x1+1) * (y2-y1+1), 1000) ;

// �Ļ�8λ���ݿ��ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
	LCD_SPI.Init.DataSize 	= SPI_DATASIZE_8BIT;    //	8λ���ݿ���
   HAL_SPI_Init(&LCD_SPI);

}

/*****************************************************************************************
* �� �� ��: DrawRoundRect
* ��ڲ���: int x - Բ�Ǿ������ϽǺ�����
*           int y - Բ�Ǿ������Ͻ�������
*           unsigned char w - Բ�Ǿ��ο���
*           unsigned char h - Բ�Ǿ��θ߶�
*           unsigned char r - Բ�ǰ뾶
* �� �� ֵ: ��
* ��������: ��LCD�ϻ���Բ�Ǿ���
* ˵    ��: ͨ������ˮƽ�ʹ�ֱ�ߣ��Լ����ĸ����ϻ���Բ����ʵ��Բ�Ǿ��εĻ��ơ�������ʹ
*           �� DrawCircleHelper ��������Բ�Ǿ��ε��ĸ�Բ�ǡ�
******************************************************************************************/
void DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r)
{
    // ������������ˮƽ��
    LCD_DrawLine_H(x + r, y, w - 2 * r);        // �ϱ�
    LCD_DrawLine_H(x + r, y + h - 1, w - 2 * r); // �±�

    // ��������������ֱ��
    LCD_DrawLine_V(x, y + r, h - 2 * r);        // ���
    LCD_DrawLine_V(x + w - 1, y + r, h - 2 * r); // �ұ�

    // �����ĸ�Բ��
    DrawCircleHelper(x + r, y + r, r, 1);                 // ���Ͻ�
    DrawCircleHelper(x + w - r - 1, y + r, r, 2);         // ���Ͻ�
    DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4); // ���½�
    DrawCircleHelper(x + r, y + h - r - 1, r, 8);         // ���½�
}

/*****************************************************************************************
* �� �� ��: DrawfillRoundRect
* ��ڲ���: int x - Բ�Ǿ������ϽǺ�����
*           int y - Բ�Ǿ������Ͻ�������
*           unsigned char w - Բ�Ǿ��ο���
*           unsigned char h - Բ�Ǿ��θ߶�
*           unsigned char r - Բ�ǰ뾶
* �� �� ֵ: ��
* ��������: ��LCD�ϻ�������Բ�Ǿ���
* ˵    ��: ͨ������һ��ˮƽ�ߺ����������ϻ�������Բ����ʵ������Բ�Ǿ��εĻ��ơ�����
*           ��ʹ�� DrawFillCircleHelper �������������ǵ����Բ����ͬʱʹ�� LCD_FillRect
*           �������ƾ��ε��м䲿�֡�
******************************************************************************************/
void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r)
{
    // ���ƾ��ε��м䲿��
    LCD_FillRect(x + r, y, w - 2 * r, h);

    // ���������ǵ����Բ��
    DrawFillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1); // ���Ͻ�
    DrawFillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1);         // ���Ͻ�
}


/*****************************************************************************************
* �� �� ��: DrawCircleHelper
* ��ڲ���: int x0 - Բ�ĺ�����
*           int y0 - Բ��������
*           unsigned char r - Բ�뾶
*           unsigned char cornername - Բ���ĸ��ǵ����ֵ
* �� �� ֵ: ��
* ��������: ��LCD�ϻ���Բ��һ���֣���ѡ����Ƶ�Բ��
* ˵    ��: ʹ�� Bresenham �㷨����Բ��һ���֣�����ѡ�����ĸ����е�һ����������Բ�ǡ�
*           Բ�ǵ����ֵ�� cornername ������ÿ��λ����һ���ǣ�1 �������ƣ�0 ���������ơ�
*           ������ʹ�� LCD_DrawPoint ��������ÿ�����ص㡣
******************************************************************************************/
void DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername)
{
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x4)
        {
            LCD_DrawPoint(x0 + x, y0 + y, LIGHT_GREEN);
            LCD_DrawPoint(x0 + y, y0 + x, LIGHT_GREEN);
        }
        if (cornername & 0x2)
        {
            LCD_DrawPoint(x0 + x, y0 - y, LIGHT_GREEN);
            LCD_DrawPoint(x0 + y, y0 - x, LIGHT_GREEN);
        }
        if (cornername & 0x8)
        {
            LCD_DrawPoint(x0 - y, y0 + x, LIGHT_GREEN);
            LCD_DrawPoint(x0 - x, y0 + y, LIGHT_GREEN);
        }
        if (cornername & 0x1)
        {
            LCD_DrawPoint(x0 - y, y0 - x, LIGHT_GREEN);
            LCD_DrawPoint(x0 - x, y0 - y, LIGHT_GREEN);
        }
    }
}

/*****************************************************************************************
* �� �� ��: DrawFillCircleHelper
* ��ڲ���: int x0 - Բ�ĺ�����
*           int y0 - Բ��������
*           unsigned char r - Բ�뾶
*           unsigned char cornername - Բ���ĸ��ǵ����ֵ
*           int delta - ����ֵ������΢������Ч��
* �� �� ֵ: ��
* ��������: ��LCD�ϻ������Բ��һ���֣���ѡ����Ƶ�Բ��
* ˵    ��: ʹ�� Bresenham �㷨�������Բ��һ���֣�����ѡ�����������е�һ������������Բ�ǡ�
*           Բ�ǵ����ֵ�� cornername ������ÿ��λ����һ���ǣ�1 �������ƣ�0 ���������ơ�
*           ������ʹ�� LCD_DrawLine_V ��������ÿ�����ص㡣
******************************************************************************************/
void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta)
{
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1)
        {
            LCD_DrawLine_V(x0 + x, y0 - y, 2 * y + 1 + delta);
            LCD_DrawLine_V(x0 + y, y0 - x, 2 * x + 1 + delta);
        }

        if (cornername & 0x2)
        {
            LCD_DrawLine_V(x0 - x, y0 - y, 2 * y + 1 + delta);
            LCD_DrawLine_V(x0 - y, y0 - x, 2 * x + 1 + delta);
        }
    }
}

/*****************************************************************************************
* �� �� ��: DrawFillEllipse
* ��ڲ���: int x0 - ��Բ���ĺ�����
*           int y0 - ��Բ����������
*           int rx - ��Բ x ��뾶
*           int ry - ��Բ y ��뾶
* �� �� ֵ: ��
* ��������: ��LCD�ϻ��������Բ
* ˵    ��: ʹ�� Bresenham �㷨���������Բ��������ʹ�� LCD_DrawLine_V ��������ÿ�����ص㡣
******************************************************************************************/
void DrawFillEllipse(int x0, int y0, int rx, int ry)
{
    int x, y;
    int xchg, ychg;
    int err;
    int rxrx2;
    int ryry2;
    int stopx, stopy;

    rxrx2 = rx;
    rxrx2 *= rx;
    rxrx2 *= 2;

    ryry2 = ry;
    ryry2 *= ry;
    ryry2 *= 2;

    x = rx;
    y = 0;

    xchg = 1;
    xchg -= rx;
    xchg -= rx;
    xchg *= ry;
    xchg *= ry;

    ychg = rx;
    ychg *= rx;

    err = 0;

    stopx = ryry2;
    stopx *= rx;
    stopy = 0;

    while (stopx >= stopy)
    {
        // ������Բ���ĸ����޵�һ�����ص�
        LCD_DrawLine_V(x0 + x, y0 - y, y + 1);
        LCD_DrawLine_V(x0 - x, y0 - y, y + 1);
        LCD_DrawLine_V(x0 + x, y0, y + 1);
        LCD_DrawLine_V(x0 - x, y0, y + 1);

        y++;
        stopy += rxrx2;
        err += ychg;
        ychg += rxrx2;

        if (2 * err + xchg > 0)
        {
            x--;
            stopx -= ryry2;
            err += xchg;
            xchg += ryry2;
        }
    }

    x = 0;
    y = ry;

    xchg = ry;
    xchg *= ry;

    ychg = 1;
    ychg -= ry;
    ychg -= ry;
    ychg *= rx;
    ychg *= rx;

    err = 0;

    stopx = 0;
    stopy = rxrx2;
    stopy *= ry;

    while (stopx <= stopy)
    {
        // ������Բ���ĸ����޵�һ�����ص�
        LCD_DrawLine_V(x0 + x, y0 - y, y + 1);
        LCD_DrawLine_V(x0 - x, y0 - y, y + 1);
        LCD_DrawLine_V(x0 + x, y0, y + 1);
        LCD_DrawLine_V(x0 - x, y0, y + 1);

        x++;
        stopx += ryry2;
        err += xchg;
        xchg += ryry2;

        if (2 * err + ychg > 0)
        {
            y--;
            stopy -= rxrx2;
            err += ychg;
            ychg += rxrx2;
        }
    }
}

/*****************************************************************************************
* �� �� ��: DrawTriangle
* ��ڲ���: unsigned char x0 - �����ε�һ�����������
*           unsigned char y0 - �����ε�һ������������
*           unsigned char x1 - �����εڶ������������
*           unsigned char y1 - �����εڶ�������������
*           unsigned char x2 - �����ε��������������
*           unsigned char y2 - �����ε���������������
* �� �� ֵ: ��
* ��������: ��LCD�ϻ���������
* ˵    ��: ʹ�� LCD_DrawLine �������������ε������ߡ�
******************************************************************************************/
void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
    LCD_DrawLine(x0, y0, x1, y1);
    LCD_DrawLine(x1, y1, x2, y2);
    LCD_DrawLine(x2, y2, x0, y0);
}

/*****************************************************************************************
* �� �� ��: DrawFillTriangle
* ��ڲ���: int x0 - �����ε�һ�����������
*           int y0 - �����ε�һ������������
*           int x1 - �����εڶ������������
*           int y1 - �����εڶ�������������
*           int x2 - �����ε��������������
*           int y2 - �����ε���������������
* �� �� ֵ: ��
* ��������: ��LCD�ϻ�������������
* ˵    ��: ʹ�� LCD_DrawLine_H �������������εĸ���ˮƽɨ���ߡ�
******************************************************************************************/
void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
    int a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12, sa = 0, sb = 0;

    // ��֤y0<=y1<=y2
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }
    if (y1 > y2) { SWAP(y2, y1); SWAP(x2, x1); }
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }

    // �������˻����߶λ�Ϊ����
    if (y0 == y2)
    {
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;

        LCD_DrawLine_H(a, y0, b - a + 1);
        return;
    }

    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;
    sa = 0;
    sb = 0;

    if (y1 == y2)
    {
        last = y1;   // Include y1 scanline
    }
    else
    {
        last = y1 - 1; // Skip it
    }

    // �����ϰ벿��������
    for (y = y0; y <= last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if (a > b) {SWAP(a, b);}

        LCD_DrawLine_H(a, y, b - a + 1);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);

    // �����°벿��������
    for (; y <= y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if (a > b) {SWAP(a, b);}

        LCD_DrawLine_H(a, y, b - a + 1);
    }

}


/*****************************************************************************************
* �� �� ��: DrawArc
* ��ڲ���: int x - Բ�ĺ�����
*           int y - Բ��������
*           unsigned char r - ���ΰ뾶
*           int angle_start - ������ʼ�Ƕ�
*           int angle_end - ������ֹ�Ƕ�
* �� �� ֵ: ��
* ��������: ����ָ��Բ�ġ��뾶�Ļ��Ρ�
* ˵    ��: �ú�������ʼ�Ƕȵ���ֹ�Ƕ���5�Ȳ������ƻ��Σ�ʹ������ת������ֱ�߻��ƺ�����
******************************************************************************************/
void DrawArc(int x, int y, unsigned char r, int angle_start, int angle_end)
{
    float i = 0;
    TypeXY m, temp;
    temp = GetXY();
    SetRotateCenter(x, y);
    SetAngleDir(0);

    if (angle_end > 360)
        angle_end = 360;

    SetAngle(0);
    m = GetRotateXY(x, y + r);
    MoveTo(m.x, m.y);

    for (i = angle_start; i < angle_end; i += 5)
    {
        SetAngle(i);
        m = GetRotateXY(x, y + r);
        LineTo(m.x, m.y);
    }

    MoveTo(temp.x, temp.y);
}

/*****************************************************************************************
* �� �� ��: GetXY
* �� �� ֵ: TypeXY - �����������������Ķ�ά����ṹ��
* ��������: ��ȡ����ֵ�ĺ���
* ˵    ��: ����һ�� TypeXY �ṹ�壬���а�����������������ֵ��
******************************************************************************************/
TypeXY GetXY(void)
{
    TypeXY m;
    m.x = _pointx;  // ��ȡ������ֵ
    m.y = _pointy;  // ��ȡ������ֵ
    return m;       // ���ذ�������ֵ�Ľṹ��
}

/*****************************************************************************************
* �� �� ��: SetRotateCenter
* ��ڲ���: int x0 - ��ת���ĵĺ�����
*           int y0 - ��ת���ĵ�������
* �� �� ֵ: ��
* ��������: ������ת���ĵ����ꡣ
* ˵    ��: ͨ�����øú���������������ת�������������꣬��Χ���ĸ��������ת��
******************************************************************************************/
void SetRotateCenter(int x0, int y0)
{
    _RoateValue.center.x = x0;
    _RoateValue.center.y = y0;
}

/*****************************************************************************************
* �� �� ��: SetAngleDir
* ��ڲ���: int direction - ��ת����1Ϊ˳ʱ�룬-1Ϊ��ʱ��
* �� �� ֵ: ��
* ��������: ������ת�ķ���
* ˵    ��: ͨ�����øú���������������ת�ķ���1��ʾ˳ʱ�룬-1��ʾ��ʱ�롣
******************************************************************************************/
void SetAngleDir(int direction)
{
    _RoateValue.direct = direction;
}


/*****************************************************************************************
* �� �� ��: SetAngle
* ��ڲ���: float angle - ��ת�Ƕȣ���λ���ȣ�
* �� �� ֵ: ��
* ��������: ������ת�ĽǶȡ�
* ˵    ��: ͨ�����øú���������������ת�ĽǶȣ���λΪ�ȡ��ڲ��Ὣ�Ƕ�ת��Ϊ���Ƚ��д�����
******************************************************************************************/
void SetAngle(float angle)
{
    _RoateValue.angle = RADIAN(angle);
}

/*****************************************************************************************
* �� �� ��: Rotate
* ��ڲ���: int x0 - ��ת���ĵĺ�����
*           int y0 - ��ת���ĵ�������
*           int *x - ����ת��ĺ�����
*           int *y - ����ת���������
*           double angle - ��ת�Ƕȣ����ȣ�
*           int direction - ��ת���򣬷����ʾ˳ʱ�룬���ʾ��ʱ��
* �� �� ֵ: ��
* ��������: ��ָ���������ת��
* ˵    ��: ͨ�����øú��������ԶԸ����ĵ�Χ��ָ�����Ľ�����ת����ת�Ƕ��� angle ����ָ����
*           direction ����ָ����ת���򣬷����ʾ˳ʱ�룬���ʾ��ʱ�롣
******************************************************************************************/
static void Rotate(int x0, int y0, int *x, int *y, double angle, int direction)
{
    int temp = (*y - y0) * (*y - y0) + (*x - x0) * (*x - x0);
    double r = mySqrt(temp);
    double a0 = atan2(*x - x0, *y - y0);

    if (direction)
    {
        *x = x0 + r * cos(a0 + angle);
        *y = y0 + r * sin(a0 + angle);
    }
    else
    {
        *x = x0 + r * cos(a0 - angle);
        *y = y0 + r * sin(a0 - angle);
    }
}


/*****************************************************************************************
* �� �� ��: mySqrt
* ��ڲ���: float x - ����ƽ��������ֵ
* �� �� ֵ: float - ����õ���ƽ����ֵ
* ��������: ���������ֵ��ƽ������
* ˵    ��: �ú�������ţ�ٵ���������ƽ������������ε����ƽ�ƽ��������ʵֵ��
******************************************************************************************/
float mySqrt(float x)
{
    float a = x;
    unsigned int i = *(unsigned int *)&x;
    i = (i + 0x3f76cf62) >> 1;
    x = *(float *)&i;
    x = (x + a / x) * 0.5;
    return x;
}


/*****************************************************************************************
* �� �� ��: GetRotateXY
* ��ڲ���: int x - ����ת�ĵ��ԭʼ������
*           int y - ����ת�ĵ��ԭʼ������
* �� �� ֵ: TypeXY - ��ת��ĵ�����
* ��������: ��ȡ������ת�任��ĵ����ꡣ
* ˵    ��: �����ת�ǶȲ�Ϊ0��ͨ������ Rotate ����ʵ�ֶԸ��������ת��
*          Ȼ����ת������걣���� TypeXY �ṹ���з��ء�
******************************************************************************************/
TypeXY GetRotateXY(int x, int y)
{
    TypeXY temp;
    int m = x, n = y;
    Rotate(_RoateValue.center.x, _RoateValue.center.y, &m, &n, _RoateValue.angle, _RoateValue.direct);
    temp.x = m;
    temp.y = n;
    return temp;
}


/*****************************************************************************************
* �� �� ��: MoveTo
* ��ڲ���: int x - �ƶ�����Ŀ�������
*           int y - �ƶ�����Ŀ��������
* �� �� ֵ: ��
* ��������: �ƶ���ͼ��굽ָ����Ŀ��λ�á�
* ˵    ��: ����ͼ���ĵ�ǰλ�ø���Ϊ������Ŀ��λ�ã��Ա�����Ļ�ͼ���������ڸ�Ŀ��λ���ϡ�
******************************************************************************************/
void MoveTo(int x, int y)
{
    _pointx = x;
    _pointy = y;
}


/*****************************************************************************************
* �� �� ��: LineTo
* ��ڲ���: int x - Ŀ�������
*           int y - Ŀ��������
* �� �� ֵ: ��
* ��������: �ڵ�ǰ���λ����ָ��Ŀ��λ��֮�����ֱ�ߡ�
* ˵    ��: �ú������ƴӵ�ǰ���λ�õ�Ŀ��λ�õ�ֱ�ߣ�����������ΪĿ��λ�á�
******************************************************************************************/
void LineTo(int x, int y)
{
    LCD_DrawLine(_pointx, _pointy, x, y);
    _pointx = x;
    _pointy = y;
}


/*****************************************************************************************
* �� �� ��: SetRotateValue
* ��ڲ���: int x - ��ת���ĺ�����
*           int y - ��ת����������
*           float angle - ��ת�Ƕȣ����ȣ�
*           int direct - ��ת����0Ϊ˳ʱ�룬1Ϊ��ʱ�룩
* �� �� ֵ: ��
* ��������: ������ת������������ת���ġ���ת�ǶȺ���ת����
* ˵    ��: �ú���ͨ�������������ú�����ʵ���˶���ת������һ�������á�
******************************************************************************************/
void SetRotateValue(int x, int y, float angle, int direct)
{
    SetRotateCenter(x, y);
    SetAngleDir(direct);
    SetAngle(angle);
}

/**********************************************************************************************************************************
*
* ���¼��������޸���HAL�Ŀ⺯����Ŀ����Ϊ��SPI�������ݲ������ݳ��ȵ�д�룬��������������ٶ�
*
*****************************************************************************************************************FANKE************/


/**
  * @brief Handle SPI Communication Timeout.
  * @param hspi: pointer to a SPI_HandleTypeDef structure that contains
  *              the configuration information for SPI module.
  * @param Flag: SPI flag to check
  * @param Status: flag state to check
  * @param Timeout: Timeout duration
  * @param Tickstart: Tick start value
  * @retval HAL status
  */
HAL_StatusTypeDef LCD_SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status,
                                                    uint32_t Tickstart, uint32_t Timeout)
{
   /* Wait until flag is set */
   while ((__HAL_SPI_GET_FLAG(hspi, Flag) ? SET : RESET) == Status)
   {
      /* Check for the Timeout */
      if ((((HAL_GetTick() - Tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
      {
         return HAL_TIMEOUT;
      }
   }
   return HAL_OK;
}


/**
 * @brief  Close Transfer and clear flags.
 * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval HAL_ERROR: if any error detected
 *         HAL_OK: if nothing detected
 */
 void LCD_SPI_CloseTransfer(SPI_HandleTypeDef *hspi)
{
  uint32_t itflag = hspi->Instance->SR;

  __HAL_SPI_CLEAR_EOTFLAG(hspi);
  __HAL_SPI_CLEAR_TXTFFLAG(hspi);

  /* Disable SPI peripheral */
  __HAL_SPI_DISABLE(hspi);

  /* Disable ITs */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_RXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF));

  /* Disable Tx DMA Request */
  CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

  /* Report UnderRun error for non RX Only communication */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    if ((itflag & SPI_FLAG_UDR) != 0UL)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_UDR);
      __HAL_SPI_CLEAR_UDRFLAG(hspi);
    }
  }

  /* Report OverRun error for non TX Only communication */
  if (hspi->State != HAL_SPI_STATE_BUSY_TX)
  {
    if ((itflag & SPI_FLAG_OVR) != 0UL)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
      __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }
  }

  /* SPI Mode Fault error interrupt occurred -------------------------------*/
  if ((itflag & SPI_FLAG_MODF) != 0UL)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
    __HAL_SPI_CLEAR_MODFFLAG(hspi);
  }

  /* SPI Frame error interrupt occurred ------------------------------------*/
  if ((itflag & SPI_FLAG_FRE) != 0UL)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
    __HAL_SPI_CLEAR_FREFLAG(hspi);
  }

  hspi->TxXferCount = (uint16_t)0UL;
  hspi->RxXferCount = (uint16_t)0UL;
}


/**
  * @brief  רΪ��Ļ�������޸ģ�����Ҫ��������ɫ��������
  * @param  hspi   : spi�ľ��
  * @param  pData  : Ҫд�������
  * @param  Size   : ���ݴ�С
  * @retval HAL status
  */

HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi,uint16_t pData, uint32_t Size)
{
   uint32_t    tickstart;
   uint32_t    Timeout = 1000;      // ��ʱ�ж�
   uint32_t    LCD_pData_32bit;     // ��32λ����ʱ������
   uint32_t    LCD_TxDataCount;     // �������
   HAL_StatusTypeDef errorcode = HAL_OK;

	/* Check Direction parameter */
	assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

	/* Process Locked */
	__HAL_LOCK(hspi);

	/* Init tickstart for timeout management*/
	tickstart = HAL_GetTick();

	if (hspi->State != HAL_SPI_STATE_READY)
	{
		errorcode = HAL_BUSY;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	if ( Size == 0UL)
	{
		errorcode = HAL_ERROR;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	/* Set the transaction information */
	hspi->State       = HAL_SPI_STATE_BUSY_TX;
	hspi->ErrorCode   = HAL_SPI_ERROR_NONE;

	LCD_TxDataCount   = Size;                // ��������ݳ���
	LCD_pData_32bit   = (pData<<16)|pData ;  // ��32λ����ʱ���ϲ�2�����ص����ɫ

	/*Init field not used in handle to zero */
	hspi->pRxBuffPtr  = NULL;
	hspi->RxXferSize  = (uint16_t) 0UL;
	hspi->RxXferCount = (uint16_t) 0UL;
	hspi->TxISR       = NULL;
	hspi->RxISR       = NULL;

	/* Configure communication direction : 1Line */
	if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
	{
		SPI_1LINE_TX(hspi);
	}

// ��ʹ��Ӳ�� TSIZE ���ƣ��˴�����Ϊ0���������ƴ�������ݳ���
	MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

	/* Enable SPI peripheral */
	__HAL_SPI_ENABLE(hspi);

	if (hspi->Init.Mode == SPI_MODE_MASTER)
	{
		 /* Master transfer start */
		 SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
	}

	/* Transmit data in 16 Bit mode */
	while (LCD_TxDataCount > 0UL)
	{
		/* Wait until TXP flag is set to send data */
		if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP))
		{
			if ((hspi->TxXferCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
			{
				*((__IO uint32_t *)&hspi->Instance->TXDR) = (uint32_t )LCD_pData_32bit;
				LCD_TxDataCount -= (uint16_t)2UL;
			}
			else
			{
				*((__IO uint16_t *)&hspi->Instance->TXDR) =  (uint16_t )pData;
				LCD_TxDataCount--;
			}
		}
		else
		{
			/* Timeout management */
			if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
			{
				/* Call standard close procedure with error check */
				LCD_SPI_CloseTransfer(hspi);

				/* Process Unlocked */
				__HAL_UNLOCK(hspi);

				SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
				hspi->State = HAL_SPI_STATE_READY;
				return HAL_ERROR;
			}
		}
	}

	if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}

	SET_BIT((hspi)->Instance->CR1 , SPI_CR1_CSUSP); // �������SPI����
	/* �ȴ�SPI���� */
	if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}
	LCD_SPI_CloseTransfer(hspi);   /* Call standard close procedure with error check */

	SET_BIT((hspi)->Instance->IFCR , SPI_IFCR_SUSPC);  // ��������־λ


	/* Process Unlocked */
	__HAL_UNLOCK(hspi);

	hspi->State = HAL_SPI_STATE_READY;

	if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
	{
		return HAL_ERROR;
	}
	return errorcode;
}

/**
  * @brief  רΪ����д�������޸ģ�ʹ֮���޳��ȵĴ�������
  * @param  hspi   : spi�ľ��
  * @param  pData  : Ҫд�������
  * @param  Size   : ���ݴ�С
  * @retval HAL status
  */
HAL_StatusTypeDef LCD_SPI_TransmitBuffer (SPI_HandleTypeDef *hspi, uint16_t *pData, uint32_t Size)
{
   uint32_t    tickstart;
   uint32_t    Timeout = 1000;      // ��ʱ�ж�
   uint32_t    LCD_TxDataCount;     // �������
   HAL_StatusTypeDef errorcode = HAL_OK;

	/* Check Direction parameter */
	assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

	/* Process Locked */
	__HAL_LOCK(hspi);

	/* Init tickstart for timeout management*/
	tickstart = HAL_GetTick();

	if (hspi->State != HAL_SPI_STATE_READY)
	{
		errorcode = HAL_BUSY;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	if ( Size == 0UL)
	{
		errorcode = HAL_ERROR;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	/* Set the transaction information */
	hspi->State       = HAL_SPI_STATE_BUSY_TX;
	hspi->ErrorCode   = HAL_SPI_ERROR_NONE;

	LCD_TxDataCount   = Size;                // ��������ݳ���

	/*Init field not used in handle to zero */
	hspi->pRxBuffPtr  = NULL;
	hspi->RxXferSize  = (uint16_t) 0UL;
	hspi->RxXferCount = (uint16_t) 0UL;
	hspi->TxISR       = NULL;
	hspi->RxISR       = NULL;

	/* Configure communication direction : 1Line */
	if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
	{
		SPI_1LINE_TX(hspi);
	}

// ��ʹ��Ӳ�� TSIZE ���ƣ��˴�����Ϊ0���������ƴ�������ݳ���
	MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

	/* Enable SPI peripheral */
	__HAL_SPI_ENABLE(hspi);

	if (hspi->Init.Mode == SPI_MODE_MASTER)
	{
		 /* Master transfer start */
		 SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
	}

	/* Transmit data in 16 Bit mode */
	while (LCD_TxDataCount > 0UL)
	{
		/* Wait until TXP flag is set to send data */
		if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP))
		{
			if ((LCD_TxDataCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
			{
				*((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)pData);
				pData += 2;
				LCD_TxDataCount -= 2;
			}
			else
			{
				*((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)pData);
				pData += 1;
				LCD_TxDataCount--;
			}
		}
		else
		{
			/* Timeout management */
			if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
			{
				/* Call standard close procedure with error check */
				LCD_SPI_CloseTransfer(hspi);

				/* Process Unlocked */
				__HAL_UNLOCK(hspi);

				SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
				hspi->State = HAL_SPI_STATE_READY;
				return HAL_ERROR;
			}
		}
	}

	if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}

	SET_BIT((hspi)->Instance->CR1 , SPI_CR1_CSUSP); // �������SPI����
	/* �ȴ�SPI���� */
	if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}
	LCD_SPI_CloseTransfer(hspi);   /* Call standard close procedure with error check */

	SET_BIT((hspi)->Instance->IFCR , SPI_IFCR_SUSPC);  // ��������־λ


	/* Process Unlocked */
	__HAL_UNLOCK(hspi);

	hspi->State = HAL_SPI_STATE_READY;

	if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
	{
		return HAL_ERROR;
	}
	return errorcode;
}
