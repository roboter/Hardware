/**
 ******************************************************************************
 * @file           : pcd8544.h
 * @brief          : PCD8544 Nokia 5110 LCD display library header
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

#ifndef __PCD8544_H
#define __PCD8544_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "font.h"

/* Private typedef -----------------------------------------------------------*/
typedef uint8_t byte;

/* Exported defines ---------------------------------------------------------*/
#define PCD8544_WIDTH           84
#define PCD8544_HEIGHT          48
#define PCD8544_BUFFER_SIZE     (PCD8544_WIDTH * PCD8544_HEIGHT / 8)

/* PCD8544 Commands */
#define PCD8544_FUNCTIONSET     0x20
#define PCD8544_DISPLAYCONTROL  0x08
#define PCD8544_SETDISPLAYNORMAL 0x0C
#define PCD8544_SETDISPLAYALLON 0x09
#define PCD8544_SETDISPLAYBLANK 0x08
#define PCD8544_SETDISPLAYINVERSE 0x0D
#define PCD8544_SETBANKS        0x04
#define PCD8544_SETBIAS         0x10
#define PCD8544_SETVOP          0x80
#define PCD8544_SETXADDR        0x80
#define PCD8544_SETYADDR        0x40

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Shift out a byte to the display
 * @param  val: Byte to shift out
 * @retval None
 */
void shiftOut(uint8_t val);

/**
 * @brief  Write data to the display
 * @param  dat: Data to write
 * @retval None
 */
void LcdWriteData(uint8_t dat);

/**
 * @brief  Write a command to the display
 * @param  cmd: Command to write
 * @retval None
 */
void LcdWriteCmd(byte cmd);

/**
 * @brief  Set cursor position
 * @param  x: X coordinate (0-83)
 * @param  y: Y coordinate (0-5)
 * @retval None
 */
void LcdXY(int x, int y);

/**
 * @brief  Write a character to the display
 * @param  character: Character to write
 * @retval None
 */
void LcdWriteCharacter(char character);

/**
 * @brief  Write a string to the display
 * @param  characters: String to write
 * @retval None
 */
void LcdWriteString(char *characters);

/**
 * @brief  Initialize PCD8544 display
 * @retval None
 */
void pcd8544_init(void);

/**
 * @brief  Clear the display
 * @retval None
 */
void pcd8544_clear(void);

/**
 * @brief  Set display contrast
 * @param  contrast: Contrast value (0-127)
 * @retval None
 */
void pcd8544_set_contrast(uint8_t contrast);

/**
 * @brief  Set display power state
 * @param  power_on: 1 for power on, 0 for power off
 * @retval None
 */
void pcd8544_set_power(uint8_t power_on);

/**
 * @brief  Set display mode (normal, inverse, all on, all off)
 * @param  mode: Display mode (PCD8544_SETDISPLAYNORMAL, etc.)
 * @retval None
 */
void pcd8544_set_display_mode(uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif /* __PCD8544_H */ 