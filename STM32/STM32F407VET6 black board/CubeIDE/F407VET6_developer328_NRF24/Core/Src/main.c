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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//#define TANK
#define LIBRARY_EXAMPLE
#define PIPE 1
#if defined TANK
#define PAYLOAD_SIZE 4 //  radio.setPayloadSize(4);
#define MY_CHANNEL 2 // radio.setChannel(2);

#endif
#if defined LIBRARY_EXAMPLE
#define PAYLOAD_SIZE 32
#define MY_CHANNEL 2
uint8_t dataT[PAYLOAD_SIZE];
//uint8_t dataR[PAYLOAD_SIZE];
#endif
// arduino const uint64_t pipe = 0xE8E8F0F0E1LL; // Определяем адрес рабочей трубы;
//const uint64_t deviceID = 0xE8E8F0F0E1LL;  // Define the ID for this slave
//const uint64_t transmitterId = 0x544d52687CLL;
// Pipe and address matching
uint8_t tx_addr[5] = { 0x7C, 0x68, 0x52, 0x4D, 0x54 }; // transmitterId in little-endian
uint8_t rx_addr[5] = { 0xE1, 0xF0, 0xF0, 0xE8, 0xE8 }; // deviceID in little-endian
uint16_t data = 0;

typedef struct {
    uint8_t leftSpeed;
    uint8_t leftDir;
    uint8_t rightSpeed;
    uint8_t rightDir;
} DriveCommand;

// Array of commands: Forward, Backward, Spin Left, Spin Right
DriveCommand commands[] = {
    { 7, 0, 7, 0 },  // Forward
    { 7, 1, 7, 1 },  // Backward
    { 7, 1, 7, 0 },  // Spin Left
    { 7, 0, 7, 1 },  // Spin Right
    { 0, 0, 0, 0 }   // Stop
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(commands[0]))

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
	MX_SPI1_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	nrf24_init(); // Init SPI, internal state

	//nrf24_listen(); // Puts in RX mode
	nrf24_stop_listen();
#if defined TANK
	nrf24_auto_ack_all(disable);
	nrf24_en_ack_pld(disable);
	nrf24_dpl(disable);         // Dynamic payloads disabled (unless you want to enable)

	// Use 8-bit CRC
	nrf24_set_crc(enable, _1byte);

	// Power: 0dBm
	nrf24_tx_pwr(_0dbm);

	// Match Arduino: 250Kbps (but Arduino uses RF24_250KBPS = 250kbps!)
	nrf24_data_rate(_250kbps); // <<<<<<<<<<<<<< IMPORTANT!

	// Match channel 0x6E = 110
	nrf24_set_channel(MY_CHANNEL);

	// 5-byte addressing
	nrf24_set_addr_width(5);
#endif


#if defined LIBRARY_EXAMPLE
	nrf24_auto_ack_all(auto_ack);
	nrf24_en_ack_pld(disable);
	nrf24_dpl(disable);

	nrf24_set_crc(no_crc, _1byte);

	nrf24_tx_pwr(_0dbm);
	nrf24_data_rate(_1mbps);
	nrf24_set_channel(MY_CHANNEL);
	nrf24_set_addr_width(5);

	uint32_t count = 0;
#endif

	// No dynamic payloads on pipes
	for (int i = 0; i < 6; i++) {
	    nrf24_set_rx_dpl(i, disable);
	}

	nrf24_pipe_pld_size(PIPE, PAYLOAD_SIZE);

	nrf24_auto_retr_delay(4);
	nrf24_auto_retr_limit(10);

	nrf24_open_tx_pipe(tx_addr);
	nrf24_open_rx_pipe(PIPE, tx_addr);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	static int index = 0;
	while (1) {
#if defined LIBRARY_EXAMPLE
		sprintf(dataT, "%d Hello!", count++);
		uint8_t val = nrf24_transmit(dataT, sizeof(dataT));
//		printf(val);
#endif

//		uint8_t cmd = 0;
//
//		DriveCommand c = commands[index];
//		cmd = (c.leftDir << 7) |
//			  ((c.leftSpeed & 0x07) << 4) |
//			  (c.rightDir << 3) |
//			  (c.rightSpeed & 0x07);
//
//		nrf24_transmit(&cmd, 1);
//		printf("Sent[%d]: 0x%02X\n", index, cmd);
//
//		index = (index + 1) % NUM_COMMANDS;
#if defined TANK
		uint8_t cmd = 0;

		DriveCommand c = commands[index];
		cmd = (c.leftDir << 7) |
			  ((c.leftSpeed & 0x07) << 4) |
			  (c.rightDir << 3) |
			  (c.rightSpeed & 0x07);

		nrf24_transmit(&cmd, 1);
		printf("Sent[%d]: 0x%02X\n", index, cmd);

		index = (index + 1) % NUM_COMMANDS;
#endif
		HAL_Delay(1000);

		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
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
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
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
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LED0_Pin | LED1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, NRF_CE_Pin | NRF_CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : KEY0_Pin KEY1_Pin */
	GPIO_InitStruct.Pin = KEY0_Pin | KEY1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : LED0_Pin LED1_Pin */
	GPIO_InitStruct.Pin = LED0_Pin | LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : NRF_CE_Pin NRF_CS_Pin */
	GPIO_InitStruct.Pin = NRF_CE_Pin | NRF_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : NRF_IRQ_Pin */
	GPIO_InitStruct.Pin = NRF_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(NRF_IRQ_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
