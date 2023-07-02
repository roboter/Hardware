/*!
 * @file        tsc_filter.h
 *
 * @brief       This file contains external declarations of the tsc_filter.c file.
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

#ifndef __TSC_FILTER_H
#define __TSC_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsc_acq.h"

/** @addtogroup TSC_Library TSC Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Macros Macros
  @{
*/

 /** Can be[0..5] - Warning: all thresholds must be shifted if different from 0 */
#define ACQ_FILTER_RANGE (0)

/** Can be[1..255] - First order filter coefficient (k = ACQ_FILTER_COEFF/256) */
#define ACQ_FILTER_COEFF (128)

/**@} end of group TSC_Macros*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/
TSC_tMeas_T TSC_Filt_MeasFilter(TSC_tMeas_T preMeasn, TSC_tMeas_T curMeasn);
TSC_tDelta_T TSC_Filt_DeltaFilter(TSC_tDelta_T delta);

/**@} end of group TSC_Fuctions*/
/**@} end of group TSC_Driver */
/**@} end of group TSC_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __TSC_FILTER_H */
