/*!
 * @file        delay.h
 *
 * @brief       This file contains external declarations of the delay.c file.
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

#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"
#include "apm32f0xx_misc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup DELAY_Driver DELAY Driver
  @{
*/

/** @addtogroup DELAY_Fuctions Fuctions
  @{
*/

void Delay_Config(void);
void Delay_us(int32_t us);
void Delay_ms(int16_t ms);

/**@} end of group DELAY_Fuctions */
/**@} end of group DELAY_Driver */
/**@} end of group Peripherals_Library */

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H */
