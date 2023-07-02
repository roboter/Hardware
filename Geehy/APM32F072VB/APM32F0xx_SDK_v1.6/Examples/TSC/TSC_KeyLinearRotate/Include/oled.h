/*!
 * @file        oled.h
 *
 * @brief       This file contains external declarations of the oled.c file.
 *
 * @version     V1.0.0
 *
 * @date        2022-02-21
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __OLED_H
#define __OLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup OLED_Driver OLED Driver
  @{
*/

/** @addtogroup OLED_Macros Macros
  @{
*/

/** Write CMD and Data */
#define OLED_CMD    0
#define OLED_DATA   1

/** I2C Clock pin and Data pin */
#define OLED_SCL_Clr() GPIO_ClearBit(GPIOB,GPIO_PIN_6)
#define OLED_SCL_Set() GPIO_SetBit(GPIOB,GPIO_PIN_6)

#define OLED_SDA_Clr() GPIO_ClearBit(GPIOB,GPIO_PIN_7)
#define OLED_SDA_Set() GPIO_SetBit(GPIOB,GPIO_PIN_7)

/**@} end of group LED_Macros*/

/** @addtogroup LED_Fuctions Fuctions
  @{
*/

void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(uint8_t data);
void OLED_Write_Byte(uint8_t data,uint8_t mode);
void OLED_Config(void);
void OLED_TurnColor(uint8_t i);
void OLED_TurnDisplay(uint8_t i);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_ClearChar(uint8_t x, uint8_t y);
void OLED_DrawPoint(uint8_t x,uint8_t y);
void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_DrawLine(int x1, int y1, int x2, int y2);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,char *chr,uint8_t size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size);
void OLED_ScrollDisplay(uint8_t num,uint8_t space);
void OLED_Write_BP(uint8_t x,uint8_t y);
void OLED_ShowPicture(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint16_t *p);

/**@} end of group LED_Fuctions */
/**@} end of group LED_Driver */
/**@} end of group Peripherals_Library */

#ifdef __cplusplus
}
#endif

#endif /* __OLED_H */
