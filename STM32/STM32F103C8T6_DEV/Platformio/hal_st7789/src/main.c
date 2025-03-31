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
#include "st7789.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
SPI_HandleTypeDef hspi1;
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
void myDelay(uint32_t ms)
{
  uint32_t start = HAL_GetTick();
  while ((HAL_GetTick() - start) < ms)
  {
    __NOP(); // Optional: Prevents compiler optimization
  }
}
// Usage: myDelay(1000); // 1 second delay
void SPI_Init_AltPins(void)
{
  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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

void LCD_Demo(void)
{
  // Initialize display
  ST7789_Init();

  // 1. Color fill demo
  ST7789_Fill_Color(BLACK);
  HAL_Delay(500);

  const uint16_t colors[] = {
      RED, GREEN, BLUE, WHITE, BLACK,
      YELLOW, CYAN, MAGENTA, BROWN, DARKBLUE};

  for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
  {
    ST7789_Fill_Color(colors[i]);
    HAL_Delay(300);
  }

  // 2. Text rendering demo
  ST7789_Fill_Color(BLACK);
  ST7789_WriteString(10, 10, "ST7789 Demo", Font_16x26, WHITE, BLACK);
  ST7789_WriteString(10, 40, "Font Test:", Font_11x18, YELLOW, BLACK);

  ST7789_WriteString(10, 70, "Small 7x10", Font_7x10, GREEN, BLACK);
  ST7789_WriteString(10, 90, "Medium 11x18", Font_11x18, CYAN, BLACK);
  ST7789_WriteString(10, 120, "Large 16x26", Font_16x26, MAGENTA, BLACK);

  HAL_Delay(3000);

  // 3. Shape drawing demo
  ST7789_Fill_Color(BLACK);
  ST7789_WriteString(10, 10, "Drawing Shapes", Font_16x26, WHITE, BLACK);

  // Draw lines
  for (int i = 0; i < 5; i++)
  {
    ST7789_DrawLine(20, 50 + i * 10, 200, 50 + i * 10, colors[i]);
  }

  // Draw rectangles
  ST7789_DrawRectangle(30, 100, 80, 150, GREEN);
  ST7789_DrawFilledRectangle(100, 100, 150, 150, BLUE);

  HAL_Delay(2000);

  // Draw circles
  ST7789_Fill_Color(BLACK);
  ST7789_DrawCircle(60, 60, 30, RED);
  ST7789_DrawFilledCircle(160, 60, 30, YELLOW);

  HAL_Delay(2000);

  // Draw triangles
  ST7789_Fill_Color(BLACK);
  ST7789_DrawTriangle(30, 30, 10, 70, 60, 70, GREEN);
  ST7789_DrawFilledTriangle(100, 30, 80, 70, 130, 70, CYAN);

  HAL_Delay(2000);

  // 4. Pixel manipulation
  ST7789_Fill_Color(BLACK);
  for (int x = 0; x < ST7789_WIDTH; x += 5)
  {
    for (int y = 0; y < ST7789_HEIGHT; y += 5)
    {
      ST7789_DrawPixel(x, y, WHITE);
    }
  }

  HAL_Delay(1000);

  // Draw 4px pixels
  for (int i = 0; i < 20; i++)
  {
    // ST7789_DrawPixel_4px(rand() % ST7789_WIDTH, rand() % ST7789_HEIGHT, colors[rand() % 10]);
    HAL_Delay(50);
  }

  HAL_Delay(1000);

  // 5. Image display (if you have image data)
  ST7789_Fill_Color(BLACK);
  ST7789_WriteString(10, 10, "Image Display", Font_16x26, WHITE, BLACK);
  HAL_Delay(1000);

  // Replace with your actual image display
  // ST7789_DrawImage(0, 30, 128, 128, demo_image);
  // HAL_Delay(3000);

  // 6. Special effects
  ST7789_Fill_Color(BLACK);
  ST7789_WriteString(10, 10, "Special Effects", Font_16x26, WHITE, BLACK);

  // Color inversion
  for (int i = 0; i < 3; i++)
  {
    ST7789_InvertColors(1);
    HAL_Delay(300);
    ST7789_InvertColors(0);
    HAL_Delay(300);
  }

  // Tearing effect (if supported)
  ST7789_TearEffect(1);
  HAL_Delay(500);
  ST7789_TearEffect(0);

  // Final message
  ST7789_Fill_Color(BLACK);
  ST7789_WriteString(10, 50, "Demo Complete!", Font_16x26, GREEN, BLACK);
  ST7789_WriteString(10, 90, "Restarting...", Font_11x18, YELLOW, BLACK);
  HAL_Delay(2000);
}
/* USER CODE END 0 */

void GPIO_Init(void)
{
  // Enable GPIOB clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

  // Configure control pins as output (PB5, PB7, PB9)
  GPIOB->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF7);
  GPIOB->CRL |= GPIO_CRL_MODE5 | GPIO_CRL_MODE7;

  GPIOB->CRH &= ~(GPIO_CRH_CNF9);
  GPIOB->CRH |= GPIO_CRH_MODE9;

  // Initialize all control pins
  ST7789_RST_Set();
  ST7789_DC_Set();
  ST7789_BLK_On();
}
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
  //HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
 // SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
   MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  // SPI_Init_AltPins();
  // LCD_Demo();
  /* USER CODE END 2 */

  // Initialize peripherals
  //GPIO_Init();
  // SPI_Init_AltPins();

  // // Initialize display
  // ST7789_Init();

  // // Test display
  // ST7789_Fill_Color(BLACK);
  // ST7789_WriteString(10, 10, "PB1/PB3 SPI", Font_11x18, WHITE, BLACK);
  // ST7789_WriteString(10, 30, "RES=PB5", Font_11x18, GREEN, BLACK);
  // ST7789_WriteString(10, 50, "DC=PB7", Font_11x18, YELLOW, BLACK);
  // ST7789_WriteString(10, 70, "BLK=PB9", Font_11x18, CYAN, BLACK);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    myDelay(1000);
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
// 1. Enable FPU (if available)
#if (__FPU_PRESENT == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif

  // 2. Critical debug configuration
  DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;

  // 3. Reset all peripherals
  RCC->APB1RSTR = 0xFFFFFFFF;
  RCC->APB2RSTR = 0xFFFFFFFF;
  RCC->APB1RSTR = 0;
  RCC->APB2RSTR = 0;

  // 4. Safe clock initialization
  RCC->CR |= RCC_CR_HSION;
  while ((RCC->CR & RCC_CR_HSIRDY) == 0)
    ;

  // 5. Configure vector table offset
  SCB->VTOR = FLASH_BASE | 0x0;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

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
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
