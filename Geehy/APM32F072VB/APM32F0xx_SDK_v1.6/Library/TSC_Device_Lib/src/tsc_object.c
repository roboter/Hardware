/*!
 * @file        tsc_object.c
 *
 * @brief       This file contains all functions to manage the sensors in general.
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

#include "tsc.h"
#include "tsc_object.h"

/** @addtogroup TSC_Library TSC Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/

/*!
 * @brief       Config a group of Objects
 *
 * @param       objgrp: Pointer to the group of objects
 *
 * @retval      None
 */
void TSC_Obj_ConfigGroup(TSC_ObjectGroup_T *objgrp)
{
    TSC_tIndex_T idxObj;
    CONST TSC_Object_T *pObj;
    TSC_tNum_T stateMask = 0;

    pObj = objgrp->p_Obj;
    objgrp->Change = TSC_STATE_NOT_CHANGED;

    /** Process all objects */
    for (idxObj = 0; idxObj < objgrp->NbObjects; idxObj++)
    {
        TSC_Obj_ConfigGlobalObj(pObj);

        if(pObj->Type == TSC_OBJ_TOUCHKEY)
        {
            #if TOUCH_TOTAL_TOUCHKEYS > 0
            TSC_Globals.For_Key->p_Methods->Config();

            if (TSC_Globals.For_Key->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }
            stateMask |= TSC_Globals.For_Key->p_SM[TSC_Globals.For_Key->p_Data->StateId].StateMask;
            #endif
        }
        else if(pObj->Type == TSC_OBJ_TOUCHKEYB)
        {
            #if TOUCH_TOTAL_TOUCHKEYS_B > 0
            TSC_Params.p_KeyMet->Config();

            if (TSC_Globals.For_Key->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Params.p_KeySta[TSC_Globals.For_Key->p_Data->StateId].StateMask;
            #endif
        }
        else if((pObj->Type == TSC_OBJ_LINEAR)||(pObj->Type == TSC_OBJ_ROTARY))
        {
            #if TOUCH_TOTAL_LINROTS > 0
            TSC_Globals.For_LinRot->p_Methods->Config();

            if (TSC_Globals.For_LinRot->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Globals.For_LinRot->p_SM[TSC_Globals.For_LinRot->p_Data->StateId].StateMask;
            #endif
        }
        else if((pObj->Type == TSC_OBJ_LINEARB)||(pObj->Type == TSC_OBJ_ROTARYB))
        {
            #if TOUCH_TOTAL_LINROTS_B > 0
            TSC_Params.p_LinRotMet->Config();

            if (TSC_Globals.For_LinRot->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }
            stateMask |= TSC_Params.p_LinRotSta[TSC_Globals.For_LinRot->p_Data->StateId].StateMask;
            #endif
        }
        pObj++;
    }
    /** Update the object group state mask */
    objgrp->StateMask = stateMask;
}

/*!
 * @brief       Process the state machine on a group of Objects
 *
 * @param       objgrp: Pointer to the group of objects to process
 *
 * @retval      None
 */
void TSC_Obj_ProcessGroup(TSC_ObjectGroup_T *objgrp)
{
    TSC_tIndex_T idxObj;
    CONST TSC_Object_T *pObj;
    TSC_tNum_T stateMask = 0;

    pObj = objgrp->p_Obj;
    objgrp->Change = TSC_STATE_NOT_CHANGED;

    /** Process all objects */
    for (idxObj = 0; idxObj < objgrp->NbObjects; idxObj++)
    {
        TSC_Obj_ConfigGlobalObj(pObj);

        if(pObj->Type == TSC_OBJ_TOUCHKEY)
        {
            #if TOUCH_TOTAL_TOUCHKEYS > 0
            TSC_Globals.For_Key->p_Methods->Process();

            if (TSC_Globals.For_Key->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Globals.For_Key->p_SM[TSC_Globals.For_Key->p_Data->StateId].StateMask;
            #endif
        }
        else if(pObj->Type == TSC_OBJ_TOUCHKEYB)
        {
            #if TOUCH_TOTAL_TOUCHKEYS_B > 0
            TSC_Params.p_KeyMet->Process();

            if (TSC_Globals.For_Key->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Params.p_KeySta[TSC_Globals.For_Key->p_Data->StateId].StateMask;
            #endif
        }
        else if((pObj->Type == TSC_OBJ_LINEAR)||(pObj->Type == TSC_OBJ_ROTARY))
        {
            #if TOUCH_TOTAL_LINROTS > 0
            TSC_Globals.For_LinRot->p_Methods->Process();

            if (TSC_Globals.For_LinRot->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Globals.For_LinRot->p_SM[TSC_Globals.For_LinRot->p_Data->StateId].StateMask;
            #endif
        }
        else if((pObj->Type == TSC_OBJ_LINEARB)||(pObj->Type == TSC_OBJ_ROTARYB))
        {
            #if TOUCH_TOTAL_LINROTS_B > 0
            TSC_Params.p_LinRotMet->Process();

            if (TSC_Globals.For_LinRot->p_Data->Change)
            {
                objgrp->Change = TSC_STATE_CHANGED;
            }

            stateMask |= TSC_Params.p_LinRotSta[TSC_Globals.For_LinRot->p_Data->StateId].StateMask;
            #endif
        }
        pObj++;
    }
    /** Update the object group state mask */
    objgrp->StateMask = stateMask;
}

/*!
 * @brief       Set the global object variable
 *
 * @param       pObj: Pointer to the object to process
 *
 * @retval      None
 */
void TSC_Obj_ConfigGlobalObj(CONST TSC_Object_T *pObj)
{
    TSC_Globals.For_Obj = pObj;

    if((pObj->Type == TSC_OBJ_TOUCHKEY)||(pObj->Type == TSC_OBJ_TOUCHKEYB))
    {
        #if TOUCH_TOTAL_KEYS > 0
        TSC_Globals.For_Key = (TSC_TouchKey_T *)pObj->MyObj;
        #endif
    }
    else if((pObj->Type == TSC_OBJ_LINEAR)||(pObj->Type == TSC_OBJ_LINEARB) ||
            (pObj->Type == TSC_OBJ_ROTARY)||(pObj->Type == TSC_OBJ_ROTARYB))
    {
        #if TOUCH_TOTAL_LNRTS > 0
        TSC_Globals.For_LinRot = (TSC_LinRot_T *)pObj->MyObj;
        #endif
    }
}

/**@} end of group TSC_Fuctions*/
/**@} end of group TSC_Driver*/
/**@} end of group TSC_Library*/
