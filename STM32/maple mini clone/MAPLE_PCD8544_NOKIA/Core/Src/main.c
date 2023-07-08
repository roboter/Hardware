/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "pcd8544.h"
#include "font.h"
typedef uint8_t byte;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void shiftOut(uint8_t val) {
	uint8_t i;

	for (i = 0; i < 8; i++) {

//		HAL_GPIO_WritePin(dataPort, dataPin, val & 1);
//		val >>= 1;

		HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, (val & 128) != 0);
		val <<= 1;

		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
		//HAL_Delay(1);
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
	}
}

void LcdWriteData(uint8_t dat) {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET); // GPIO_Pin, PinState), GPIO_Pin, HIGH);//(DC, HIGH); //DC pin is low for commands
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
	shiftOut(dat); //transmit serial data
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

void LcdWriteCmd(byte cmd) {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET); //DC pin is low for commands
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
	shiftOut(cmd); //transmit serial data
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

void LcdXY(int x, int y) {
	LcdWriteCmd(0x80 | x);  // Column.
	LcdWriteCmd(0x40 | y);  // Row.
}

void LcdWriteCharacter(char character) {
	for (int i = 0; i < 5; i++)
		LcdWriteData(ASCII[character - 0x20][i]);
	LcdWriteData(0x00);
}

void LcdWriteString(char *characters) {
	while (*characters)
		LcdWriteCharacter(*characters++);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t spi_address_cmd = 0xFF;
	HAL_StatusTypeDef hal_res;
	HAL_GPIO_TogglePin(CLK_GPIO_Port, CLK_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(CLK_GPIO_Port, CLK_Pin);
	while (1) {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		//HAL_GPIO_TogglePin(BP_LED_GPIO_Port, BP_LED_Pin);
		HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);

		LcdWriteCmd(0x21);  // LCD extended commands
		LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
		LcdWriteCmd(0x04);  // set temp coefficent
		LcdWriteCmd(0x14);  // LCD bias mode 1:40
		LcdWriteCmd(0x20);  // LCD basic commands
//		LcdWriteCmd(0x09);  // LCD all segments on
		LcdWriteCmd(0x0C);  // LCD normal video
//
		for (int i = 0; i < 504; i++)
			LcdWriteData(0x00); // clear LCD

		LcdXY(20, 2);
		LcdWriteString("THE END");
		//  HAL_GPIO_TogglePin(LIGHT_GPIO_Port, LIGHT_Pin); // HIGH - OFF
		// HAL_GPIO_TogglePin(CLK_GPIO_Port, CLK_Pin);
//		HAL_GPIO_TogglePin(BP_LED_GPIO_Port, BP_LED_Pin);
//		// delay_ms(100);
//		hal_res = HAL_SPI_Transmit(&hspi1, &spi_address_cmd, 1, 500);
//		// Create the handle for the driver (Includes 504 byte of memory for the back buffer).
//		pcd8544_handle_t pcd8544_handle = { .spi_handle = &hspi1, .nsce_port =
//		NOKIA5110_NSCE_GPIO_Port, .nsce_pin = NOKIA5110_NSCE_Pin, .dnc_port =
//				NOKIA5110_DNC_GPIO_Port, .dnc_pin =
//		NOKIA5110_DNC_Pin, .nrst_port = NOKIA5110_NRST_GPIO_Port, .nrst_pin =
//		NOKIA5110_NRST_Pin, };
//
//		// Initialise driver (performs basic setup and clears back buffer).
//		pcd8544_init(&pcd8544_handle);
//
//		// Set every second row to black (changes are only applied to back buffer).
//		for (uint8_t x = 0; x < PCD8544_LCD_WIDTH; x++) {
//			for (uint8_t y = 0; y < PCD8544_LCD_HEIGHT; y++) {
//				pcd8544_set_pixel(&pcd8544_handle, x, y,
//						(pcd8544_color_t) (y % 2 == 0));
//			}
//		}

		// Send back buffer to display.
		//pcd8544_update(&pcd8544_handle);

		HAL_Delay(1000);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CE_Pin|CLK_Pin|DIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Pin|RST_Pin|LIGHT_Pin|DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CE_Pin CLK_Pin DIN_Pin */
  GPIO_InitStruct.Pin = CE_Pin|CLK_Pin|DIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin LIGHT_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RST_Pin DC_Pin */
  GPIO_InitStruct.Pin = RST_Pin|DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
