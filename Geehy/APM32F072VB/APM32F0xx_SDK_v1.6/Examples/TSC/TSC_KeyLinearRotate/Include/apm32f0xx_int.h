/*!
 * @file        apm32f0xx_int.h
 *
 * @brief       This file contains the headers of the interrupt handlers
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

#ifndef __APM32F0XX_INT_H
#define __APM32F0XX_INT_H

#ifdef __cplusplus
  extern "C" {
#endif

#include "apm32f0xx.h"
#include "tsc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup INT_Driver INT Driver
  @{
*/

/** @addtogroup INT_Fuctions Fuctions
  @{
*/

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void TSC_IRQHandler(void);

/**@} end of group INT_Fuctions*/
/**@} end of group INT_Driver*/
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /*__APM32F0XX_INT_H */
