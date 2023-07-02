/*!
 * @file        apm32f0xx_ob.h
 *
 * @brief       This file contains all the functions prototypes for the OB firmware library
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
#ifndef __APM32F0XX_OB_H
#define __APM32F0XX_OB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup OB_Driver OB Driver
  @{
*/

/** @addtogroup OB_Enumerations Enumerations
  @{
*/

/**
 * @brief   Read protection option byte
 */
typedef enum
{
    OB_READ_PRO_LEVEL0  = 0xAA,
    OB_READ_PRO_LEVEL1  = 0xBB,
} OB_READ_PRO_T;

/**
 * @brief Option Bytes Watchdog
 */
typedef enum
{
    OB_WDG_HW = ((uint8_t)0),
    OB_WDG_SW = ((uint8_t)1),
} OB_WDT_T;

/**
 * @brief Option Bytes nRST STOP
 */
typedef enum
{
    OB_STOP_RESET = ((uint8_t)0),
    OB_STOP_SET = ((uint8_t)1),
} OB_STOP_T;

/**
 * @brief Option Bytes nRST Standby
 */
typedef enum
{
    OB_STANDBY_RST = ((uint8_t)0),
    OB_STANDBY_SET = ((uint8_t)1),
} OB_STANDBY_T;

/**
 * @brief Option Bytes nBOOT1
 */
typedef enum
{
    OB_BOOT1_RST = ((uint8_t)0),
    OB_BOOT1_SET = ((uint8_t)1),
} OB_BOOT1_T;

/**
 * @brief Option Bytes VDDA_Analog_Monitoring
 */
typedef enum
{
    OB_VDDA_OFF = ((uint8_t)0),
    OB_VDDA_ON  = ((uint8_t)1),
} OB_VDDA_T;

/**
 * @brief Option Bytes RAM PARITY CHECK
 */
typedef enum
{
    OB_RAM_PARITY_CHECK_ENABLE  = ((uint8_t)0),
    OB_RAM_PARITY_CHECK_DISABLE = ((uint8_t)1),
} OB_RAM_PARITY_CHECK_T;

/**@} end of group OB_Enumerations*/

/** @addtogroup OB_Structure Data Structure
  @{
*/

/**
 * @brief   User Option byte config struct definition
 */
typedef struct
{
    OB_READ_PRO_T  readProtection;      //!< Read protection option byte
    OB_WDT_T       wdt;                 //!< Watch dog activation
    OB_STOP_T      stop;                //!< Option Bytes nRST STOP
    OB_STANDBY_T   stdby;               //!< Option Bytes nRST STDBY
    OB_BOOT1_T     boot;                //!< Option Bytes nBOOT1
    OB_VDDA_T      vdda;                //!< Option Bytes nRST STOP
    OB_RAM_PARITY_CHECK_T  ramParityCheck; //!< Option Bytes RAM PARITY CHECK
} OB_UserConfig_T;

/**@} end of group OB_Structure*/

/** @addtogroup OB_Fuctions Fuctions
  @{
*/

/** Read protection option byte */
void OB_ReadProtectionOptionByte(OB_READ_PRO_T readProtection);

/** Option Bytes Watchdog */
void OB_OptionBytesWatchdog(OB_WDT_T wdt);

/** Option Bytes nRST STOP */
void OB_OptionBytesStop(OB_STOP_T stop);

/** Option Bytes nRST STDBY */
void OB_OptionBytesStandby(OB_STANDBY_T standby);

/** Option Bytes nBOOT1 */
void OB_OptionBytesBoot1(OB_BOOT1_T boot);

/** Option Bytes VDDA_Analog_Monitoring */
void OB_OptionBytesVddaAnalog(OB_VDDA_T vdda);

/** Option Bytes RAM PARITY CHECK  */
void OB_OptionBytesRamParity(OB_RAM_PARITY_CHECK_T ramParityCheck);

/**@} end of group OB_Fuctions*/
/**@} end of group OB_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_OB_H */
