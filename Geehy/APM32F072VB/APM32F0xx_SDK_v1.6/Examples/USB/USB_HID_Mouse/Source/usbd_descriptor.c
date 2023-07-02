/*!
 * @file        usbd_descriptor.c
 *
 * @brief       HID descriptor
 *
 * @version     V1.0.0
 *
 * @date        2021-12-06
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

#include "usbd_descriptor.h"
#include "usbd_core.h"

extern const uint8_t s_hidMouseDeviceDescriptor[HID_MOUSE_DEVICE_DESCRIPTOR_SIZE];
extern const uint8_t s_hidMouseConfigDescriptor[HID_MOUSE_CONFIG_DESCRIPTOR_SIZE];
extern const uint8_t s_hidMouseReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE];
extern const uint8_t s_hidMouseLandIDString[HID_MOUSE_LANGID_STRING_SIZE];
extern const uint8_t s_hidMouseVendorString[HID_MOUSE_VENDOR_STRING_SIZE];
extern const uint8_t s_hidMouseProductString[HID_MOUSE_PRODUCT_STRING_SIZE];
extern const uint8_t s_hidMouseSerialString[HID_MOUSE_SERIAL_STRING_SIZE];

/** Device descriptor */
USBD_Descriptor_T g_deviceDescriptor = {s_hidMouseDeviceDescriptor, HID_MOUSE_DEVICE_DESCRIPTOR_SIZE};
/** Config descriptor */
USBD_Descriptor_T g_configDescriptor = {s_hidMouseConfigDescriptor, HID_MOUSE_CONFIG_DESCRIPTOR_SIZE};
/** String descriptor */
USBD_Descriptor_T g_stringDescriptor[SRTING_DESC_NUM] =
{
    {s_hidMouseLandIDString, HID_MOUSE_LANGID_STRING_SIZE},
    {s_hidMouseVendorString, HID_MOUSE_VENDOR_STRING_SIZE},
    {s_hidMouseProductString, HID_MOUSE_PRODUCT_STRING_SIZE},
    {s_hidMouseSerialString, HID_MOUSE_SERIAL_STRING_SIZE}
};
USBD_Descriptor_T g_ReportDescriptor = {s_hidMouseReportDescriptor, HID_MOUSE_REPORT_DESCRIPTOR_SIZE};

/**
 * @brief   Device descriptor
 */
const uint8_t s_hidMouseDeviceDescriptor[HID_MOUSE_DEVICE_DESCRIPTOR_SIZE] =
{
    /** bLength */
    0x12,

    /** bDescriptorType */
    USBD_DESC_DEVICE,

    /** bcdUSB */
    0x00, 0x02,

    /** bDeviceClass */
    0x00,
    /** bDeviceSubClass */
    0x00,
    /** bDeviceProtocol */
    0x00,
    /** bMaxPacketSize */
    0x40,
    /** idVendor =  314b*/
    0x4b, 0x31,
    /** idProduct = 0107 */
    0x07, 0x01,
    /** bcdDevice = 1.00 */
    0x00, 0x01,

    /** Index of string descriptor describing manufacturer */
    1,
    /** Index of string descriptor describing product */
    2,
    /** Index of string descriptor describing the device serial number */
    3,
    /** bNumConfigurations */
    1,
};

/**
 * @brief   Configuration descriptor
 */
const uint8_t s_hidMouseConfigDescriptor[HID_MOUSE_CONFIG_DESCRIPTOR_SIZE] =
{
    /** bLength */
    0x09,
    /** bDescriptorType */
    USBD_DESC_CONFIGURATION,
    /** wTotalLength */
    HID_MOUSE_CONFIG_DESCRIPTOR_SIZE & 0XFF, HID_MOUSE_CONFIG_DESCRIPTOR_SIZE >> 8,

    /** bNumInterfaces */
    0X01,
    /** bConfigurationValue */
    0X01,
    /** iConfiguration */
    0X00,
    /** bmAttributes */
    0XE0,
    /** MaxPower */
    0X32,

    /** bLength */
    0X09,
    /** bDescriptorType */
    USBD_DESC_INTERFACE,
    /** bInterfaceNumber */
    0X00,
    /** bAlternateSetting */
    0X00,
    /** bNumEndpoints */
    0X01,
    /** bInterfaceClass */
    0X03,
    /** bInterfaceSubClass */
    0X01,
    /** nInterfaceProtocol */
    0X02,
    /** iInterface */
    0X00,

    /** bLength */
    0X09,
    /** bDescriptorType = HID */
    0x21,
    /** bcdHID */
    0X00, 0X01,
    /** bCountryCode */
    0X00,
    /** bNumDescriptors */
    0X01,
    /** bDescriptorType */
    0X22,
    /** wItemLength */
    HID_MOUSE_REPORT_DESCRIPTOR_SIZE & 0XFF, HID_MOUSE_REPORT_DESCRIPTOR_SIZE >> 8,

    /** bLength */
    0X07,
    /** bDescriptorType */
    USBD_DESC_ENDPOINT,
    /** bEndpointAddress */
    0X81,
    /** bmAttributes */
    0X03,
    /** wMaxPacketSize */
    0X04, 0X00,
    /** bInterval */
    0X20
};

/**
 * @brief   HID report descriptor
 */
const uint8_t s_hidMouseReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE] =
{
    0x05,
    0x01,
    0x09,
    0x02,
    0xA1,
    0x01,
    0x09,
    0x01,

    0xA1,
    0x00,
    0x05,
    0x09,
    0x19,
    0x01,
    0x29,
    0x03,

    0x15,
    0x00,
    0x25,
    0x01,
    0x95,
    0x03,
    0x75,
    0x01,

    0x81,
    0x02,
    0x95,
    0x01,
    0x75,
    0x05,
    0x81,
    0x01,

    0x05,
    0x01,
    0x09,
    0x30,
    0x09,
    0x31,
    0x09,
    0x38,

    0x15,
    0x81,
    0x25,
    0x7F,
    0x75,
    0x08,
    0x95,
    0x03,

    0x81,
    0x06,
    0xC0,
    0x09,
    0x3c,
    0x05,
    0xff,
    0x09,

    0x01,
    0x15,
    0x00,
    0x25,
    0x01,
    0x75,
    0x01,
    0x95,

    0x02,
    0xb1,
    0x22,
    0x75,
    0x06,
    0x95,
    0x01,
    0xb1,

    0x01,
    0xc0
};

/**
 * @brief   language ID string
 */
const uint8_t s_hidMouseLandIDString[HID_MOUSE_LANGID_STRING_SIZE] =
{
    /** Size */
    HID_MOUSE_LANGID_STRING_SIZE,
    /** bDescriptorType */
    USBD_DESC_STRING,
    0X09,0X04
};

/**
 * @brief   Vendor string
 */
const uint8_t s_hidMouseVendorString[HID_MOUSE_VENDOR_STRING_SIZE] =
{
    /** Size */
    HID_MOUSE_VENDOR_STRING_SIZE,
    /** bDescriptorType */
    USBD_DESC_STRING,
    'A', 0, 'P', 0, 'E', 0, 'X', 0, 'M', 0, 'I', 0, 'C', 0
};

/**
 * @brief   Product string
 */
const uint8_t s_hidMouseProductString[HID_MOUSE_PRODUCT_STRING_SIZE] =
{
    HID_MOUSE_PRODUCT_STRING_SIZE,
    USBD_DESC_STRING,
    'A', 0, 'P', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'H', 0,
    'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0
};

/**
 * @brief   Serial string
 */
const uint8_t s_hidMouseSerialString[HID_MOUSE_SERIAL_STRING_SIZE] =
{
    HID_MOUSE_SERIAL_STRING_SIZE,
    USBD_DESC_STRING,

    'A', 0, 'P', 0, 'M', 0, '3', 0, '2', 0
};
