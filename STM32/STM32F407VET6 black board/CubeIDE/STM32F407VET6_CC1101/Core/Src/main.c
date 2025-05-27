/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cc1101.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define state 	0
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
volatile uint8_t GDO0_FLAG;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void UserLEDHide() {
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
}

void UserLEDShow() {
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
}

#define CC1101_CS_PIN      CS_Pin
#define CC1101_CS_PORT     CS_GPIO_Port
#define CC1101_GDO0_PIN    GDO0_PIN
#define CC1101_GDO0_PORT   GDO0_GPIO_Port

void Test_CC1101_Connection(void) {
	printf("Starting CC1101 Test...\r\n");

	uint8_t partNum = TI_read_status(CCxxx0_PARTNUM);
	uint8_t version = TI_read_status(CCxxx0_VERSION);
	uint8_t marcstate = TI_read_status(CCxxx0_MARCSTATE) & 0x1F;
	printf("MARCSTATE: 0x%02X\r\n", marcstate);
	if (partNum == 0x00 && version == 0x14) {
		printf("CC1101 OK! PARTNUM=0x%02X, VERSION=0x%02X\r\n", partNum,
				version);
	} else {
		printf(
				"CC1101 ERROR! PARTNUM=0x%02X (expected 0x04), VERSION=0x%02X (expected 0x14)\r\n",
				partNum, version);
	}
}

void CC1101_Reset(void) {
    // Deassert CS (high)
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    // Assert CS (low)
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);

    // Deassert again briefly
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    // Assert CS again to start SRES
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

    // Wait for SO (MISO) to go low = CC1101 ready
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)); // GDB0_Pin (MISO)

    // Send SRES (Reset)
    uint8_t cmd = 0x30;
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);

    // Wait again for SO to go low = reset done
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)); // GDB0_Pin (MISO)

    // Deassert CS
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}


void CC1101_DumpRegisters(char *buf, size_t bufsize) {
	uint8_t regVal;
	size_t idx = 0;

	for (uint8_t addr = 0x00; addr <= 0x2F; addr++) {
		regVal = TI_read_reg(addr);
		idx += snprintf(buf + idx, bufsize - idx, "[0x%02X]=0x%02X,", addr,
				regVal);
		if (idx >= bufsize - 1)
			break; // Prevent buffer overflow
	}

	// Append PARTNUM and VERSION explicitly
	regVal = TI_read_status(CCxxx0_PARTNUM); // PARTNUM
	idx += snprintf(buf + idx, bufsize - idx, "PARTNUM = 0x%02X\r\n", regVal);

	regVal = TI_read_status(CCxxx0_VERSION); // VERSION
	idx += snprintf(buf + idx, bufsize - idx, "VERSION = 0x%02X\r\n", regVal);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
	setvbuf(stdout, NULL, _IONBF, 0);  // Disable printf buffer
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//	char packet[] = "RF Test";
//	 BYTE status;
//	status = TI_read_status(CCxxx0_VERSION); // it is for checking only //sadece kontrol için
//	//it must be 0x14 //0x14 değeri vermelidir
//
//	status = TI_read_status(CCxxx0_TXBYTES); // it is too // bu da kontrol için
//
//	TI_strobe(CCxxx0_SFTX); // flush the buffer //bufferi temizler
//
//	UserLEDShow(); // turn on the led before send the data // veri göndermeden önce ledi yakar
//
//	TI_send_packet(packet, sizeof(packet)); //the function is sending the data
//	BYTE status;
//	Power_up_reset();
	TI_init(&hspi1, CS_GPIO_Port, CS_Pin);
//
//	//for transiver
//	BYTE veri = 7;
//	char packet[] = "RF Test";
	char cc1101_dump[1024];
	CC1101_Reset();
	CC1101_DumpRegisters(cc1101_dump, sizeof(cc1101_dump));
	BYTE status = TI_read_status(CCxxx0_VERSION); // it is for checking only //sadece kontrol için
//	Test_CC1101_Connection();
//	TI_init(&hspi1, CS_GPIO_Port, CS_Pin);
//
//	  //for transiver
//	  BYTE veri = 7;
//	  char packet[] = "RF Test";
//
//	  while (1)
//	  {
//		  status = TI_read_status(CCxxx0_VERSION); // it is for checking only //sadece kontrol için
//		  //it must be 0x14 //0x14 değeri vermelidir
//
//		  status = TI_read_status(CCxxx0_TXBYTES); // it is too // bu da kontrol için
//
//		  TI_strobe(CCxxx0_SFTX); // flush the buffer //bufferi temizler
//
//		  UserLEDShow(); // turn on the led before send the data // veri göndermeden önce ledi yakar
//
//		  TI_send_packet(packet, sizeof(packet)); //the function is sending the data
//
//		  while(HAL_GPIO_ReadPin(GDO0_GPIO_Port, GDO0_Pin));
//		  while(!HAL_GPIO_ReadPin(GDO0_GPIO_Port, GDO0_Pin));
//		  //if the pass to this function, the data was sent. // veri gönderme işlemi tamamlanması için bekletir
//
//		  status = TI_read_status(CCxxx0_TXBYTES); // it is checking to send the data //veri gönderildiğini kontrol etmek için
//
//		  UserLEDHide(); // turn off the led // veri gönderildiğinde led söner
//		  HAL_Delay(100);
//	  }
	while (1) {
		//	printf("WHILE LOOP\n");
		GPIO_PinState key0 = HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin);
		GPIO_PinState wk_up = HAL_GPIO_ReadPin(WK_UP_GPIO_Port, WK_UP_Pin);

		if (wk_up == GPIO_PIN_SET) {
			char cc1101_dump[1024];
//			CC1101_Reset();
			CC1101_DumpRegisters(cc1101_dump, sizeof(cc1101_dump));


			BYTE status1 = TI_read_status(CCxxx0_VERSION);
			printf("%s", cc1101_dump);
			printf("0x%02X", status1);

			HAL_Delay(1000);
		}

		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
	// Configure SPI pins as Alternate Function (PB3-PB5)
	GPIO_InitTypeDef GPIO_InitSPI = { 0 };
	GPIO_InitSPI.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitSPI.Mode = GPIO_MODE_AF_PP;
	GPIO_InitSPI.Pull = GPIO_NOPULL;
	GPIO_InitSPI.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitSPI.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitSPI);
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GDB0_GPIO_Port, GDB0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : KEY1_Pin KEY0_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin|KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : WK_UP_Pin */
  GPIO_InitStruct.Pin = WK_UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(WK_UP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED0_Pin */
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : GDB0_Pin */
  GPIO_InitStruct.Pin = GDB0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GDB0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_Pin */
  GPIO_InitStruct.Pin = CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
	// Optional: Verify SPI pins
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET) {
		// MISO is floating - consider adding pull-down
		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	}
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* Send a char through ITM */
int _write(int file, char *data, int len) {
	// Wait until previous transmission is complete
	while (CDC_Transmit_FS((uint8_t*) data, len) == USBD_BUSY) {
		// Optionally add timeout here
	}
	return len;
}
int _write_debug(int file, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
