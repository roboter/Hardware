/*!
 * @file        tsc_touchkey.h
 *
 * @brief       This file contains external declarations of the tsc_touchkey.c file.
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

#ifndef __TOUCH_TOUCHKEY_H
#define __TOUCH_TOUCHKEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsc_acq.h"
#include "tsc_time.h"

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
 * @brief   Contains all data related to TouchKey sensor.
 *          Variables of this structure type must be placed in RAM only.
 */
typedef struct
{
    TSC_STATEID_T      StateId;           //!< Current state identifier
    TSC_tCounter_T     CounterDebounce;   //!< Counter for debounce and calibration management
    unsigned int       CounterDTO : 6;    //!< Counter for DTO management (TSC_tCounter_T)
    unsigned int       Change     : 1;    //!< The State is different from the previous one (TSC_STATE_T)
    unsigned int       DxsLock    : 1;    //!< The State is locked by the DxS (TSC_BOOL_T)
} TSC_TouchKeyData_T;

/**
 * @brief   Contains all data related to TouchKey sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
#if TOUCH_USE_PROX > 0
    TSC_tThreshold_T  ProxInTh;           //!< Proximity in threshold
    TSC_tThreshold_T  ProxOutTh;          //!< Proximity out threshold
#endif
    TSC_tThreshold_T  DetectInTh;         //!< Detection in threshold
    TSC_tThreshold_T  DetectOutTh;        //!< Detection out threshold
    TSC_tThreshold_T  CalibTh;            //!< Calibration threshold
    TSC_tCounter_T    CounterDebCalib;    //!< Debounce counter to enter in Calibration state
#if TOUCH_USE_PROX > 0
    TSC_tCounter_T    CounterDebProx;     //!< Debounce counter to enter in Proximity state
#endif
    TSC_tCounter_T    CounterDebDetect;   //!< Debounce counter to enter in Detect state
    TSC_tCounter_T    CounterDebRelease;  //!< Debounce counter to enter in Release state
    TSC_tCounter_T    CounterDebError;    //!< Debounce counter to enter in Error state
} TSC_TouchKeyParam_T;

/**
 * @brief   Contains definition of a TouchKey sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    TSC_TouchKeyData_T          *p_Data;    //!< Data (state id, counter, flag, ...)
    TSC_TouchKeyParam_T         *p_Param;   //!< Parameters (thresholds, debounce, ...)
    TSC_Channel_Data_T          *p_ChD;     //!< Channel Data (Meas, Refer, Delta, ...)
    CONST TSC_State_T           *p_SM;      //!< State Machine
    CONST TSC_TouchKeyMethods_T *p_Methods; //!< Methods
} TSC_TouchKey_T;

/**
 * @brief   Contains definition of a Basic TouchKey sensor.
 *          Variables of this structure type can be placed in RAM or ROM.
 *          Basic sensor does not contain its own state machine and methods. It used
 *          default ones instead to gain memory space.
 */
typedef struct
{
    TSC_TouchKeyData_T          *p_Data;    //!< Data (state id, counters, flag, ...)
    TSC_TouchKeyParam_T         *p_Param;   //!< Parameters (thresholds, debounce, ...)
    TSC_Channel_Data_T          *p_ChD;     //!< Channel Data (Meas, Refer, Delta, ...)
} TSC_TouchKeyB_T;

/**@} end of group TSC_Structure*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/

/** "Object methods" functions */
void TSC_TouchKey_Config(void);
void TSC_TouchKey_Process(void);

/** Utility functions */
void TSC_TouchKey_ConfigCalibrationState(TSC_tCounter_T delay);
void TSC_TouchKey_ConfigOffState(void);
void TSC_TouchKey_ConfigBurstOnlyState(void);
TSC_STATEID_T TSC_TouchKey_ReadStateId(void);
TSC_STATEMASK_T TSC_TouchKey_ReadStateMask(void);
TSC_tNum_T TSC_TouchKey_ReadChangeFlag(void);

/** State machine functions */
void TSC_TouchKey_ProcessCalibrationState(void);
void TSC_TouchKey_ProcessDebCalibrationState(void);
void TSC_TouchKey_ProcessReleaseState(void);
void TSC_TouchKey_ProcessDebReleaseProxState(void);
void TSC_TouchKey_ProcessDebReleaseDetectState(void);
void TSC_TouchKey_ProcessDebReleaseTouchState(void);
void TSC_TouchKey_ProcessProxState(void);
void TSC_TouchKey_ProcessDebProxState(void);
void TSC_TouchKey_ProcessDebProxDetectState(void);
void TSC_TouchKey_ProcessDebProxTouchState(void);
void TSC_TouchKey_ProcessDetectState(void);
void TSC_TouchKey_ProcessDebDetectState(void);
void TSC_TouchKey_ProcessTouchState(void);
void TSC_TouchKey_ProcessDebErrorState(void);

/**@} end of group TSC_Fuctions */
/**@} end of group TSC_Driver */
/**@} end of group TSC_Library */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_TOUCHKEY_H */
