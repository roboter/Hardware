/*!
 * @file        tsc.c
 *
 * @brief       This file contains the Touch Driver main functions.
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

/** Global variables used by main() and TSC modules */
    TSC_Globals_T  TSC_Globals;

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
 * @brief       Config the TSC GPIO interface
 *
 * @param       block: Array holding all the blocks
 *
 * @retval      pointer to a TSC_STATUS_T structure
 */
TSC_STATUS_T TSC_Config(CONST TSC_Block_T *block)
{
    TSC_STATUS_T retval;

    /** Read blocks array */
    TSC_Globals.Block_Array = block;

    retval = TSC_Time_Config();

    if (retval == TSC_STATUS_OK)
    {
        retval = TSC_Acq_Config();
    }

    return retval;
}

/**@} end of group TSC_Fuctions*/
/**@} end of group TSC_Driver*/
/**@} end of group TSC_Library*/
