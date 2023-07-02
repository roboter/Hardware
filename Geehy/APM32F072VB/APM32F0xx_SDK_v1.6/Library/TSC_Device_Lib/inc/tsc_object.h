/*!
 * @file        tsc_object.h
 *
 * @brief       This file contains external declarations of the tsc_object.c file.
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

#ifndef __TOUCH_OBJECT_H
#define __TOUCH_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsc_touchkey.h"
#include "tsc_linrot.h"

/** @addtogroup TSC_Library TSC Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Macros Macros
  @{
*/

#define TSC_OBJ_TYPE_KEY_MASK     (0x10)  //!< TouchKey object mask
#define TSC_OBJ_TYPE_LINROT_MASK   (0x20) //!< Linear and Rotary objects mask
#define TSC_OBJ_TYPE_TRACKNAV_MASK (0x40) //!< TrackPad and NaviPad objects mask

/**@} end of group TSC_Macros*/

/** @addtogroup TSC_Enumerations Enumerations
  @{
*/

/**
 * @brief   Contains all different kinds of sensors
 */
typedef enum
{
    TSC_OBJ_TOUCHKEY   = (TSC_OBJ_TYPE_KEY_MASK + 0),      //!< Normal TouchKey
    TSC_OBJ_TOUCHKEYB  = (TSC_OBJ_TYPE_KEY_MASK + 1),      //!< Basic TouchKey
    TSC_OBJ_LINEAR     = (TSC_OBJ_TYPE_LINROT_MASK + 0),   //!< Normal Linear sensor
    TSC_OBJ_LINEARB    = (TSC_OBJ_TYPE_LINROT_MASK + 1),   //!< Basic Linear sensor
    TSC_OBJ_ROTARY     = (TSC_OBJ_TYPE_LINROT_MASK + 2),   //!< Normal Rotary sensor
    TSC_OBJ_ROTARYB    = (TSC_OBJ_TYPE_LINROT_MASK + 3),   //!< Basic Rotary sensor
    TSC_OBJ_TRACKPAD   = (TSC_OBJ_TYPE_TRACKNAV_MASK + 0), //!< TrackPad sensor
    TSC_OBJ_NAVIPAD    = (TSC_OBJ_TYPE_TRACKNAV_MASK + 1)  //!< NaviPad sensor
} TSC_OBJECT_T;

/**@} end of group TSC_Enumerations*/

/** @addtogroup TSC_Structure Data Structure
  @{
*/

/**
 * @brief   Contains the definition of an Object.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    TSC_OBJECT_T       Type;   //!< Object type
    void               *MyObj; //!< Pointer to the object
} TSC_Object_T;

/**
 * @brief   Contains the definition of a Group of Objects.
 *          Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    CONST TSC_Object_T     *p_Obj;     //!< Pointer to the first object
    TSC_tNum_T             NbObjects;  //!< Number of objects in the group
    TSC_tNum_T             StateMask;  //!< "OR" of all objects state mask
    TSC_STATE_T            Change;     //!< The State is different from the previous one
    TSC_tIndex_T           execution;  //!< Flag for the ECS execution
#if TOUCH_ECS_DELAY > 0
    TSC_tIndex_T           wait;       //!< Flag for the ECS delay
    TSC_tTick_ms_T         time;       //!< Keep the time for the ECS delay
#endif
} TSC_ObjectGroup_T;

/**@} end of group TSC_Structure*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/

void TSC_Obj_ConfigGroup(TSC_ObjectGroup_T *objgrp);
void TSC_Obj_ProcessGroup(TSC_ObjectGroup_T *objgrp);
void TSC_Obj_ConfigGlobalObj(CONST TSC_Object_T *pObj);

/**@} end of group TSC_Fuctions */
/**@} end of group TSC_Driver */
/**@} end of group TSC_Library */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_OBJECT_H */
