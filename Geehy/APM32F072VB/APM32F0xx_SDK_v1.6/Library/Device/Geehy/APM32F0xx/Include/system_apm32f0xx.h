/*!
 * @file        system_apm32f0xx.h
 *
 * @brief      CMSIS Cortex-M0 Device Peripheral Access Layer System Source File
 *
 * @details     This file contains the system clock configuration for APM32F0xx devices.
 *
 * @version     V1.0.2
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

#ifndef __SYSTEM_APM32F0XX_H
#define __SYSTEM_APM32F0XX_H

#ifdef __cplusplus
extern "C" {
#endif

/** System Clock Frequency (Core Clock) */
extern uint32_t SystemCoreClock;

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32F0XX_H */
