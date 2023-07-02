/*!
 * @file        ubsd_descriptor.h
 *
 * @brief       HID descriptor head file
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

#ifndef USBD_DESCRIPTOR_H_
#define USBD_DESCRIPTOR_H_

#include "usbd_core.h"

#define HID_MOUSE_DEVICE_DESCRIPTOR_SIZE        (18)
#define HID_MOUSE_CONFIG_DESCRIPTOR_SIZE        (34)
#define HID_MOUSE_LANGID_STRING_SIZE            (4)
#define HID_MOUSE_VENDOR_STRING_SIZE            (16)
#define HID_MOUSE_PRODUCT_STRING_SIZE           (32)
#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE        (74)
#define HID_MOUSE_SERIAL_STRING_SIZE            (12)
#define SRTING_DESC_NUM                         (4)

extern USBD_Descriptor_T g_deviceDescriptor;
extern USBD_Descriptor_T g_configDescriptor;
extern USBD_Descriptor_T g_stringDescriptor[SRTING_DESC_NUM];
extern USBD_Descriptor_T g_ReportDescriptor;

#endif
