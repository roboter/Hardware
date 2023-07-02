/*!
 * @file        usbd_hid.h
 *
 * @brief       HID head file
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

#ifndef USBD_HID_H_
#define USBD_HID_H_

#include "usbd_init.h"

/**
 * @brief   Key enumeration
 */
enum
{
    HID_MOUSE_KEY_NULL,
    HID_MOUSE_KEY_LEFT,
    HID_MOUSE_KEY_RIGHT,
    HID_MOUSE_KEY_UP,
    HID_MOUSE_KEY_DOWN,
};

void HidMouse_Init(void);
void HidMouse_Proc(void);
void HidMouse_SetConfigCallBack(void);

#endif
