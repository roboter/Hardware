/*!
 * @file        tsc.h
 *
 * @brief       This file contains external declarations of the tsc.c file.
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

#ifndef __TSC_H
#define __TSC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsc_acq.h"
#include "tsc_time.h"
#include "tsc_touchkey.h"
#include "tsc_linrot.h"
#include "tsc_object.h"
#include "tsc_dxs.h"
#include "tsc_ecs.h"
#include "tsc_filter.h"

/** @addtogroup TSC_Library TSC Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Structure Data Structure
  @{
*/

/**
 * @brief   Store all global variables shared between the Touch Driver and the Application.
 */
typedef struct
{
    TSC_tTick_ms_T       Tick_ms;        //!< Incremented each 0.5ms by timing interrupt routine
    TSC_tTick_sec_T      Tick_sec;       //!< Incremented each second by timing interrupt routine
    CONST TSC_Block_T    *Block_Array;   //!< Pointer to the array containing all Blocks
    TSC_tIndex_T         For_Block;      //!< Pointer to the current Block
    CONST TSC_Object_T   *For_Obj;       //!< Pointer to the current Object
#if TOUCH_USE_ZONE > 0
    CONST TSC_Zone_T     *For_Zone;      //!< Pointer to the current Zone
    TSC_tIndex_T         Index_For_Zone; //!< Index in the current Zone
#endif
#if TOUCH_TOTAL_KEYS > 0
    CONST TSC_TouchKey_T *For_Key;    //!< Pointer to the current Touch Key
#endif
#if TOUCH_TOTAL_LNRTS > 0
    CONST TSC_LinRot_T   *For_LinRot; //!< Pointer to the current Linear or Rotary sensor
#endif
} TSC_Globals_T;

/**
 * @brief   Store all global parametersshared between the Touch Driver and the Application.
 * @warning Only one variable of this structure type must be created and be placed in RAM only.
 */
typedef struct
{
    TSC_tMeas_T       AcqMin;         //!< Acquisition minimum limit
    TSC_tMeas_T       AcqMax;         //!< Acquisition maximum limit
    TSC_tNum_T        NumCalibSample; //!< Number of Calibration samples
    TSC_tTick_sec_T   DTO;            //!< Detection Time Out
#if TOUCH_TOTAL_KEYS > 0
    CONST TSC_State_T           *p_KeySta; //!< Default state machine for TouchKey sensors
    CONST TSC_TouchKeyMethods_T *p_KeyMet; //!< Default methods for TouchKey sensors
#endif
#if TOUCH_TOTAL_LNRTS > 0
    CONST TSC_State_T         *p_LinRotSta; //!< Default state machine for Linear/Rotary sensors
    CONST TSC_LinRotMethods_T *p_LinRotMet; //!< Default methods for Linear/Rotary sensors
#endif
}TSC_Params_T;

/**@} end of group TSC_Structure*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/
extern TSC_Globals_T  TSC_Globals;
extern TSC_Params_T   TSC_Params;

TSC_STATUS_T TSC_Config(CONST TSC_Block_T *block);

/**@} end of group TSC_Fuctions */
/**@} end of group TSC_Driver */
/**@} end of group TSC_Library */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_H */
