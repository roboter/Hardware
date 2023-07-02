/*!
 * @file        tsc_user.h
 *
 * @brief       Touch-Sensing user configuration and api file.
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

#ifndef __TSC_USER_H
#define __TSC_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tsc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup TSC_Driver TSC Driver
  @{
*/

/** @addtogroup TSC_Macros Macros
  @{
*/

/** @addtogroup Channel_IOs_Definition
  @{
*/
#define CHANNEL_0_IO_MSK    (TSC_GROUP1_IO2)
#define CHANNEL_0_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_0_SRC       (0) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_0_DEST      (0) //!< Index in destination result array

#define CHANNEL_1_IO_MSK    (TSC_GROUP1_IO3)
#define CHANNEL_1_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_1_SRC       (0) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_1_DEST      (1) //!< Index in destination result array

#define CHANNEL_2_IO_MSK    (TSC_GROUP2_IO2)
#define CHANNEL_2_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_2_SRC       (1) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_2_DEST      (2) //!< Index in destination result array

#define CHANNEL_3_IO_MSK    (TSC_GROUP2_IO3)
#define CHANNEL_3_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_3_SRC       (1) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_3_DEST      (3) //!< Index in destination result array

#define CHANNEL_4_IO_MSK    (TSC_GROUP2_IO4)
#define CHANNEL_4_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_4_SRC       (1) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_4_DEST      (4) //!< Index in destination result array

#define CHANNEL_5_IO_MSK    (TSC_GROUP4_IO3)
#define CHANNEL_5_GRP_MSK   (TSC_GROUP4)
#define CHANNEL_5_SRC       (3) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_5_DEST      (5) //!< Index in destination result array

#define CHANNEL_6_IO_MSK    (TSC_GROUP3_IO3)
#define CHANNEL_6_GRP_MSK   (TSC_GROUP3)
#define CHANNEL_6_SRC       (2) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_6_DEST      (6) //!< Index in destination result array

#define CHANNEL_7_IO_MSK    (TSC_GROUP6_IO3)
#define CHANNEL_7_GRP_MSK   (TSC_GROUP6)
#define CHANNEL_7_SRC       (5) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_7_DEST      (7) //!< Index in destination result array

#define CHANNEL_8_IO_MSK    (TSC_GROUP6_IO4)
#define CHANNEL_8_GRP_MSK   (TSC_GROUP6)
#define CHANNEL_8_SRC       (5) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_8_DEST      (8) //!< Index in destination result array

#define CHANNEL_9_IO_MSK    (TSC_GROUP4_IO4)
#define CHANNEL_9_GRP_MSK   (TSC_GROUP4)
#define CHANNEL_9_SRC       (3) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_9_DEST      (9) //!< Index in destination result array

#define CHANNEL_10_IO_MSK   (TSC_GROUP3_IO4)
#define CHANNEL_10_GRP_MSK  (TSC_GROUP3)
#define CHANNEL_10_SRC      (2) //!< Index in source register (TSC->IOGXCR[])
#define CHANNEL_10_DEST     (10) //!< Index in destination result array

/**@} Channel_IOs_Definition */

/** @addtogroup Shield_IOs_Definition
  @{
*/
#define SHIELD_IO_MSK       (0)

/**@} Shield_IOs_Definition */

/** @addtogroup Blocks_Definition
  @{
*/
#define BLOCK_0_NUMCHANNELS    (2)
#define BLOCK_0_MSK_CHANNELS   (CHANNEL_0_IO_MSK | CHANNEL_2_IO_MSK | SHIELD_IO_MSK)
#define BLOCK_0_MSK_GROUPS     (CHANNEL_0_GRP_MSK | CHANNEL_2_GRP_MSK )

#define BLOCK_1_NUMCHANNELS    (5)
#define BLOCK_1_MSK_CHANNELS   (CHANNEL_1_IO_MSK | CHANNEL_3_IO_MSK | CHANNEL_6_IO_MSK | CHANNEL_5_IO_MSK | CHANNEL_7_IO_MSK | SHIELD_IO_MSK)
#define BLOCK_1_MSK_GROUPS     (CHANNEL_1_GRP_MSK |CHANNEL_3_GRP_MSK | CHANNEL_6_GRP_MSK | CHANNEL_5_GRP_MSK | CHANNEL_7_GRP_MSK)

#define BLOCK_2_NUMCHANNELS    (4)
#define BLOCK_2_MSK_CHANNELS   (CHANNEL_4_IO_MSK | CHANNEL_8_IO_MSK | CHANNEL_9_IO_MSK | CHANNEL_10_IO_MSK)
#define BLOCK_2_MSK_GROUPS     (CHANNEL_4_GRP_MSK | CHANNEL_8_GRP_MSK | CHANNEL_9_GRP_MSK | CHANNEL_10_GRP_MSK)

/**@} Blocks_Definition */

/** @addtogroup User_Parameters
  @{
*/
extern CONST TSC_Block_T MyBlocks[];
extern CONST TSC_TouchKey_T MyTouchKeys[];
extern CONST TSC_LinRot_T MyLinRots[];
extern CONST TSC_Object_T MyObjects[];
extern TSC_ObjectGroup_T MyObjGroup;
extern uint32_t Global_ProcessSensor;

/**@} User_Parameters */

/** @addtogroup TSC_Fuctions Fuctions
  @{
*/
void TSC_User_Config(void);
void TSC_User_Thresholds(void);
TSC_STATUS_T TSC_User_Action(void);

/**@} end of group TSC_Fuctions */
/**@} end of group TSC_Driver */
/**@} end of group Peripherals_Library */

#ifdef __cplusplus
}
#endif

#endif /* __TSC_USER_H */
