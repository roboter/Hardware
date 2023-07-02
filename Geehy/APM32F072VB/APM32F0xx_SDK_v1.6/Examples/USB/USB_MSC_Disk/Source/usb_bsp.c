/*!
 * @file        usb_bsp.c
 *
 * @brief       Borad source file
 *
 * @version     V1.0.0
 *
 * @date        2021-12-30
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

#include "usb_bsp.h"

void USBD_HardWareInit(void)
{
    RCM_EnableHSI48();
    RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_HSI48);
    RCM_ConfigUSBCLK(RCM_USBCLK_HSI48);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USB);

    NVIC_EnableIRQRequest(USBD_IRQn, 2);
}
