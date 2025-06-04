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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "rf_driver.h"
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
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void CC1101_DumpRegisters(char *buf, size_t bufsize) {
	uint8_t regVal;
	size_t idx = 0;

	for (uint8_t addr = 0x00; addr <= 0x2F; addr++) {
		regVal = rf_read_register(addr);
		idx += snprintf(buf + idx, bufsize - idx, "[0x%02X]=0x%02X,", addr,
				regVal);
		if (idx >= bufsize - 1)
			break; // Prevent buffer overflow
	}
	// volatile uint8_t raw_state = rf_read_register(MARCSTATE);
	// Append PARTNUM and VERSION explicitly
	regVal = rf_read_register(PARTNUM); // PARTNUM
	idx += snprintf(buf + idx, bufsize - idx, "PARTNUM = 0x%02X\r\n", regVal);

	regVal = rf_read_register(VERSION); // VERSION
	idx += snprintf(buf + idx, bufsize - idx, "VERSION = 0x%02X\r\n", regVal);
}

void CC1101_Init4FSK() {
	// 1. Reset and put in IDLE state
	rf_write_strobe(SRES);  // Hardware reset
	rf_sidle();             // Ensure IDLE state
	while (rf_read_register(MARCSTATE) != 0x01)
		; // Wait for IDLE

	// 2. Core 4-FSK Configuration
	rf_write_register(MDMCFG2, 0x3B);  // 4-FSK | DC filter | 32/32 sync bits
	rf_write_register(MDMCFG1, 0x22);  // FEC enabled | 4 preamble bytes
	rf_write_register(MDMCFG0, 0xF8);  // Channel spacing

	// 3. Data Rate and Bandwidth (optimized for 48.8kbps)
	rf_write_register(MDMCFG4, 0x7A);  // Rx BW = 203kHz
	rf_write_register(MDMCFG3, 0x83);  // Data rate mantissa
	rf_write_register(DEVIATN, 0x47);  // 38.4kHz deviation (optimal for 4-FSK)

	// 4. Frequency Settings (434MHz)
	rf_write_register(FREQ2, 0x10);
	rf_write_register(FREQ1, 0xA7);
	rf_write_register(FREQ0, 0x62);

	// 5. Power Amplifier Configuration
	rf_write_register(FREND0, 0x11);   // Optimized PA for 4-FSK
	rf_write_register(PATABLE_SINGLE_BYTE, 0xC5); // +10dBm output

	// 6. Sync Word (default 0xD391)
	rf_write_register(SYNC1, 0xD3);
	rf_write_register(SYNC0, 0x91);

	// 7. FIFO and Packet Settings
	rf_write_register(FIFOTHR, 0x47);  // Optimal TX/RX thresholds
	rf_write_register(PKTCTRL0, 0x05); // Variable length, CRC enabled

	// 8. Calibration Sequence
	rf_write_strobe(SCAL);  // Frequency synthesizer calibration
	uint8_t timeout = 100;
	while ((rf_read_register(MARCSTATE) != 0x01) && timeout--) {
		HAL_Delay(1);
	}

	// 9. Enter RX Mode
	rf_write_strobe(SRX);
	while (rf_read_register(MARCSTATE) != 0x0D)
		; // Wait for RX state
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

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
	MX_SPI3_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	//Init rf driver
	rf_begin(&hspi3, GFSK_1_2_kb, MHz434, CS_GPIO_Port, CS_Pin, GDO0_Pin);
	//rf_set_carrier_offset(0x4b);
	//check if idle
//	rf_sidle();
//	uint8_t result = rf_read_register(MARCSTATE);
//	printf("result %#02x (Should be 0x01)\n\r", result);
//
//	rf_set_carrier_frequency(433.98);
//	rf_set_carrier_offset(50);

	uint8_t crc;
	uint16_t len = (1 << 16) - 1;
	uint8_t buffer[len];
	uint8_t lqi;
	uint8_t rssi;

	rf_receive();

	char buff[650] = { };
	//TI_FixCriticalRegisters();
	//CC1101_Init4FSK();
	CC1101_DumpRegisters(buff, 650);
	printf(buff);

	/* USER CODE BEGIN WHILE */
	while (1) {
		if (rf_incoming_packet()) {
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			printf("PACKET FOUND\n\r");
			len = (1 << 16) - 1;
			crc = receive_frame(buffer, &len, 0, 16, &lqi, &rssi);
			if (crc) {
				printf("%d CRC OK\n\r", len);
			} else {
				printf("%d BAD CRC OK\n\r", len);
			}
			rf_write_strobe(SFRX);
			//printf("CRC: %d, LQI: %d, RSSI: %d, LEN: %d\n\r", crc, lqi, rssi, len);
			rf_receive();
		}
		printf("While loop!\n");
		HAL_Delay(10);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief SPI3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI3_Init(void) {

	/* USER CODE BEGIN SPI3_Init 0 */

	/* USER CODE END SPI3_Init 0 */

	/* USER CODE BEGIN SPI3_Init 1 */

	/* USER CODE END SPI3_Init 1 */
	/* SPI3 parameter configuration*/
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI3_Init 2 */

	/* USER CODE END SPI3_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : LED1_Pin LED0_Pin */
	GPIO_InitStruct.Pin = LED1_Pin | LED0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : GDO0_Pin */
	GPIO_InitStruct.Pin = GDO0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GDO0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : CS_Pin */
	GPIO_InitStruct.Pin = CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//int _write(int file, char *ptr, int len) {
//	int DataIdx;
//	HAL_UART_Transmit(&huart1, (uint8_t*) ptr, len, HAL_MAX_DELAY);
//	for (DataIdx = 0; DataIdx < len; DataIdx++) {
//		ITM_SendChar(*ptr++);
//	}
//	return len;
//}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
