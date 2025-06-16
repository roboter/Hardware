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
#include <string.h>
#include "NRF24.h"
#include "NRF24_reg_addresses.h"
#include "fonts.h"
#include "st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TANK

#define PIPE 1
#define MY_CHANNEL 0x6E

#if defined TANK
#define PAYLOAD_SIZE 1 // it is 4 in arduino code and on sender
#else
#define PAYLOAD_SIZE 32
#endif

//+---------+-------+-------+-------+----------+-------+-------+-------+
//|  Bit 7  | Bit 6 | Bit 5 | Bit 4 |  Bit 3   | Bit 2 | Bit 1 | Bit 0 |
//+--------------------------------------------------------------------+
//| leftDir |<------ leftSpeed ---->| rightDir | <--- rightSpeed --->  |
//+--------------------------------------------------------------------+

const uint64_t deviceID = 0xE8E8F0F0E1LL;  // Define the ID for this slave
const uint64_t transmitterId = 0x544d52687CLL;
// Pipe and address matching
uint8_t tx_addr[5] = { 0x7C, 0x68, 0x52, 0x4D, 0x54 }; // transmitterId in little-endian
uint8_t rx_addr[5] = { 0xE1, 0xF0, 0xF0, 0xE8, 0xE8 }; // deviceID in little-endian
uint16_t data = 0;

uint8_t dataR[PAYLOAD_SIZE];

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
bool TX_DataRdy = false;
uint8_t RxData[32] = { 0x00 };
uint8_t rxcount = 0, rxBuf = { 0x00 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if ((rxBuf == '\n') || (rxcount >= 32)) //keep filling the RxData buffer until carriage return
			{
		TX_DataRdy = true; //Let the main loop know data is ready for transmit
		rxcount = 0;
	} else {
		RxData[rxcount++] = rxBuf;
	}
	HAL_UART_Receive_IT(&huart1, &rxBuf, 1);
}

//To get microsecond delays for the nRF24 module
void Delay_us(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while (__HAL_TIM_GET_COUNTER(&htim3) < us)
		;
}

uint8_t noise_level[126] = { 0 };

bool nrf24_test_rpd() {
	uint8_t rpd = nrf24_r_reg(RPD, 1);
	return (rpd & 0x01) != 0;
}

void nrf24_scan_noise(void) {
	const int samples_per_channel = 100;

	printf("Scanning noise on channels 0–125 (%d samples each)...\r\n",
			samples_per_channel);

	for (uint8_t ch = 0; ch <= 125; ch++) {
		noise_level[ch] = 0;
		nrf24_set_channel(ch);

		for (int i = 0; i < samples_per_channel; i++) {
			nrf24_pwr_up();
			HAL_Delay(1); // 1 ms per sample
			if (nrf24_test_rpd()) {
				noise_level[ch]++;
			}
			nrf24_pwr_dwn();
		}

		// Show mini-bar chart
		printf("CH %3d [%3d]: ", ch, noise_level[ch]);
		int bars = noise_level[ch] / 5;  // max 20 bars for 100 samples
		for (int j = 0; j < bars; j++)
			printf("|");
		printf("\r\n");
	}

	printf("Done scanning.\r\n");
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
	MX_SPI2_Init();
	MX_SPI1_Init();
	MX_RTC_Init();
	MX_USART1_UART_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, &rxBuf, 1);
	HAL_TIM_Base_Start(&htim3);
	nrf24_init();

	nrf24_listen();

	nrf24_tx_pwr(_0dbm); //	  radio.setPALevel(RF24_PA_MAX);

	nrf24_data_rate(_1mbps);
#if defined TANK

//	  radio.openWritingPipe(transmitterId);
//	  radio.openReadingPipe(1, deviceID);

	//	  radio.enableAckPayload();
//	nrf24_auto_ack_all(enable);
//
//	nrf24_en_ack_pld(enable);
//	nrf24_transmit_rx_ack_pld(1, ackData, ackLen);
//	nrf24_en_ack_pld(disable);
//	nrf24_dpl(disable);

//	  radio.writeAckPayload(1, ackData, ackLen);
	nrf24_data_rate(_250kbps); //	  radio.setDataRate(RF24_250KBPS);

	nrf24_set_crc(en_crc, _1byte); //	  radio.setCRCLength(RF24_CRC_8);  // Use 8-bit CRC for performance
#else
	nrf24_auto_ack_all(disable);
	nrf24_en_ack_pld(disable);
	nrf24_dpl(disable);

	nrf24_data_rate(_1mbps);
	nrf24_set_crc(no_crc, _1byte);
#endif

	nrf24_set_channel(MY_CHANNEL);
	nrf24_set_addr_width(5);

	// No dynamic payloads on pipes
	for (int i = 0; i < 6; i++) {
		nrf24_set_rx_dpl(i, disable);
	}

	// Set payload size for RX pipe 0 (only used pipe)
	nrf24_pipe_pld_size(PIPE, PAYLOAD_SIZE);  // Arduino uses pipe 1 for reading

	// Auto retransmit
	nrf24_auto_retr_delay(4);  // ~1500us
	nrf24_auto_retr_limit(10); // Retry 10 times

	nrf24_open_tx_pipe(rx_addr); //RX TX is mismatch intentionally
	nrf24_open_rx_pipe(PIPE, tx_addr); // Pipe 1 used in Arduino
#if defined TESTNRF
	uint8_t test_value = 0x2A;
	WriteReg(RF_CH, &test_value, 1);
	uint8_t read_value = ReadReg(RF_CH);

	if (read_value == test_value)
	{
	    printf("nRF24 is responsive! RF_CH = 0x%02X\r\n", read_value);
	}
	else
	{
	    printf("nRF24 communication failed. Read: 0x%02X, Expected: 0x%02X\r\n", read_value, test_value);
	}
#endif

	ST7735_Init();
	// Check border
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0, "OK", Font_7x10,
	ST7735_RED, ST7735_BLACK);
#if defined TEST_DISPLAY
	for (int x = 0; x < ST7735_WIDTH; x++) {
		ST7735_DrawPixel(x, 0, ST7735_RED);
		ST7735_DrawPixel(x, ST7735_HEIGHT - 1, ST7735_RED);
	}

	for (int y = 0; y < ST7735_HEIGHT; y++) {
		ST7735_DrawPixel(0, y, ST7735_RED);
		ST7735_DrawPixel(ST7735_WIDTH - 1, y, ST7735_RED);
	}

	HAL_Delay(3000);

	// Check fonts
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0,
			"Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10,
			ST7735_RED, ST7735_BLACK);
	ST7735_WriteString(0, 3 * 10, "Font_11x18, green, lorem ipsum", Font_11x18,
	ST7735_GREEN, ST7735_BLACK);
	ST7735_WriteString(0, 3 * 10 + 3 * 18, "Font_16x26", Font_16x26,
	ST7735_BLUE, ST7735_BLACK);
	HAL_Delay(2000);
	// Check colors
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_BLUE);
	ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_RED);
	ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_GREEN);
	ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_CYAN);
	ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_MAGENTA);
	ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK,
	ST7735_MAGENTA);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_YELLOW);
	ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
	HAL_Delay(500);

	ST7735_FillScreen(ST7735_WHITE);
	ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
	HAL_Delay(500);
#endif
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	nrf24_scan_noise();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	char dataR[32];  // global or local depending on your use
	nrf24_listen();

	while (1) {
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

		//	printf("While loop\n");
		HAL_Delay(100);

		while (nrf24_data_available()) {
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);

			nrf24_receive(dataR, PAYLOAD_SIZE);  // receive 1 byte
			// nrf24_receive(dataR, 32);  // always read full payload length
			nrf24_flush_rx();      // flush remaining FIFO to avoid stuck buffer

			// Clear both lines
			ST7735_FillRectangle(0, 0, 160, 18, ST7735_BLACK);   // line 1
			ST7735_FillRectangle(0, 18, 160, 18, ST7735_BLACK);  // line 2

			// Display the command character (first line)
			//char direction[2] = { dataR[0], '\0' };  // direction letter

			char command = dataR[0];

			int leftSpeed = (command & 0x70) >> 4;
			int leftDir = (command & 0x80) >> 7;
			int rightSpeed = (command & 0x07);
			int rightDir = (command & 0x08) >> 3;

			const char *direction = "S";  // default Stop

			if (leftSpeed == 0 && rightSpeed == 0) {
				direction = "S";  // Stop
			} else if (leftDir == 0 && rightDir == 0) {
				direction = "F";  // Forward
			} else if (leftDir == 1 && rightDir == 1) {
				direction = "B";  // Backward
			} else if (leftDir == 1 && rightDir == 0) {
				direction = "L";  // Turn Left
			} else if (leftDir == 0 && rightDir == 1) {
				direction = "R";  // Turn Right
			}
			ST7735_WriteString(0, 0, direction, Font_11x18, ST7735_BLACK,
			ST7735_YELLOW);

			// Display raw hex value (second line)
			char debugHex[8];
			snprintf(debugHex, sizeof(debugHex), "0x%02X", (uint8_t) dataR[0]);
			ST7735_WriteString(0, 18, debugHex, Font_11x18, ST7735_BLACK,
			ST7735_YELLOW);

			ST7735_WriteString(0, 18 * 2, dataR, Font_11x18, ST7735_BLACK,
			ST7735_YELLOW);

			printf(debugHex);
			printf("\n");
			memset(dataR, 0x00, 32);  // optional cleanup
		}
//		nrf24_listen();
//
//		if (nrf24_data_available()) {
//			nrf24_receive(dataR, sizeof(dataR));
//			ST7735_WriteString(0, 0, dataR, Font_11x18, ST7735_BLACK, ST7735_YELLOW);
//			memset(dataR, 0x00, 32);
//		}

		if (TX_DataRdy) {
			sprintf(RxData, "Hello World!");

			printf("TX :%s \r\n", RxData);

			TX_DataRdy = false;
			memset(RxData, 0x00, 32);
		}
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
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI
			| RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void) {

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef DateToUpdate = { 0 };

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
	hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = 0x0;
	sTime.Minutes = 0x0;
	sTime.Seconds = 0x0;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
	DateToUpdate.Month = RTC_MONTH_JANUARY;
	DateToUpdate.Date = 0x1;
	DateToUpdate.Year = 0x0;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

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
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_1LINE;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 72 - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

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
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, FLASH_CS_Pin | NRF_CE_Pin | LED0_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, NRF_CS_Pin | DISPLAY_DC_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(DISPLAY_A0_GPIO_Port, DISPLAY_A0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : BUTTON1_Pin */
	GPIO_InitStruct.Pin = BUTTON1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BUTTON1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : FLASH_CS_Pin LED0_Pin */
	GPIO_InitStruct.Pin = FLASH_CS_Pin | LED0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : NRF_CE_Pin */
	GPIO_InitStruct.Pin = NRF_CE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(NRF_CE_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : NRF_CS_Pin DISPLAY_DC_Pin */
	GPIO_InitStruct.Pin = NRF_CS_Pin | DISPLAY_DC_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : NRF_IRQ_Pin */
	GPIO_InitStruct.Pin = NRF_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(NRF_IRQ_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : DISPLAY_A0_Pin */
	GPIO_InitStruct.Pin = DISPLAY_A0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DISPLAY_A0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LED1_Pin */
	GPIO_InitStruct.Pin = LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* Send a char through ITM */
int _write(int file, char *ptr, int len) {
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
