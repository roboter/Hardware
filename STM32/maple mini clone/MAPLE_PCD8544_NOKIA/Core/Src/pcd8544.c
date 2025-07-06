/**
 ******************************************************************************
 * @file           : pcd8544.c
 * @brief          : PCD8544 Nokia 5110 LCD display library implementation
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

/* Includes ------------------------------------------------------------------*/
#include "pcd8544.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Shift out a byte to the display
 * @param  val: Byte to shift out
 * @retval None
 */
void shiftOut(uint8_t val) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, (val & 128) != 0);
		val <<= 1;

		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
	}
}

/**
 * @brief  Write data to the display
 * @param  dat: Data to write
 * @retval None
 */
void LcdWriteData(uint8_t dat) {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
	shiftOut(dat);
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

/**
 * @brief  Write a command to the display
 * @param  cmd: Command to write
 * @retval None
 */
void LcdWriteCmd(byte cmd) {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
	shiftOut(cmd);
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

/**
 * @brief  Set cursor position
 * @param  x: X coordinate (0-83)
 * @param  y: Y coordinate (0-5)
 * @retval None
 */
void LcdXY(int x, int y) {
	LcdWriteCmd(0x80 | x);  // Column
	LcdWriteCmd(0x40 | y);  // Row
}

/**
 * @brief  Write a character to the display
 * @param  character: Character to write
 * @retval None
 */
void LcdWriteCharacter(char character) {
	for (int i = 0; i < 5; i++) {
		// Write each font row twice to make text thicker
		LcdWriteData(ASCII[character - 0x20][i]);
		LcdWriteData(ASCII[character - 0x20][i]); // Duplicate for thickness
	}
	LcdWriteData(0x00);
	LcdWriteData(0x00); // Extra spacing
}

/**
 * @brief  Write a string to the display
 * @param  characters: String to write
 * @retval None
 */
void LcdWriteString(char *characters) {
	while (*characters)
		LcdWriteCharacter(*characters++);
}

/**
 * @brief  Initialize PCD8544 display
 * @retval None
 */
void pcd8544_init(void) {
	HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);

	LcdWriteCmd(0x21);  // LCD extended commands
	LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
	LcdWriteCmd(0x04);  // set temp coefficient
	LcdWriteCmd(0x14);  // LCD bias mode 1:40
	LcdWriteCmd(0x20);  // LCD basic commands
	LcdWriteCmd(0x0C);  // LCD normal video
}

/**
 * @brief  Clear the display
 * @retval None
 */
void pcd8544_clear(void) {
	for (int i = 0; i < 504; i++)
		LcdWriteData(0x00);
}

/**
 * @brief  Set display contrast
 * @param  contrast: Contrast value (0-127)
 * @retval None
 */
void pcd8544_set_contrast(uint8_t contrast) {
	if (contrast > 127) contrast = 127;
	
	LcdWriteCmd(0x21);  // LCD extended commands
	LcdWriteCmd(0x80 | contrast);  // Set Vop
	LcdWriteCmd(0x20);  // LCD basic commands
}

/**
 * @brief  Set display power state
 * @param  power_on: 1 for power on, 0 for power off
 * @retval None
 */
void pcd8544_set_power(uint8_t power_on) {
	if (power_on) {
		LcdWriteCmd(PCD8544_SETDISPLAYNORMAL);
	} else {
		LcdWriteCmd(PCD8544_SETDISPLAYBLANK);
	}
}

/**
 * @brief  Set display mode (normal, inverse, all on, all off)
 * @param  mode: Display mode (PCD8544_SETDISPLAYNORMAL, etc.)
 * @retval None
 */
void pcd8544_set_display_mode(uint8_t mode) {
	LcdWriteCmd(mode);
} 