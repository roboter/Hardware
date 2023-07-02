/*!
 * @file        tsc_time.h
 *
 * @brief       This file contains external declarations of the tsc_time.c file.
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

#ifndef __TOUCH_TIME_H
#define __TOUCH_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"
#include "tsc_types.h"
#include "tsc_acq.h"

/** @addtogroup TSC_Library TSC Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Structure Data Structure
  @{
*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/
TSC_STATUS_T TSC_Time_Config(void);
void TSC_Time_ProcessInterrupt(void);
TSC_STATUS_T TSC_Time_Delay_ms(TSC_tTick_ms_T delay_ms, __IO TSC_tTick_ms_T *last_tick);
TSC_STATUS_T TSC_Time_Delay_sec(TSC_tTick_sec_T delay_sec, __IO TSC_tTick_sec_T *last_tick);
void TSC_CallBack_TimerTick(void);

/**@} end of group TSC_Fuctions */
/**@} end of group TSC_Driver */
/**@} end of group TSC_Library */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_TIME_H */
