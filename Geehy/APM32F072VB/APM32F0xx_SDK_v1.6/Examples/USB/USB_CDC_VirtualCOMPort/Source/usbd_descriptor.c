/*!
 * @file        usbd_descriptor.c
 *
 * @brief       CDC descriptor
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

#include "usbd_descriptor.h"
#include "usbd_core.h"

extern const uint8_t g_usbDeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE];
extern const uint8_t g_usbConfigDescriptor[USB_CONFIG_DESCRIPTOR_SIZE];
extern const uint8_t g_usbLandIDString[USB_LANGID_STRING_SIZE];
extern const uint8_t g_usbVendorString[USB_VENDOR_STRING_SIZE];
extern const uint8_t g_usbProductString[USB_PRODUCT_STRING_SIZE];
extern uint8_t g_usbSerialString[USB_SERIAL_STRING_SIZE];

/** Device descriptor */
USBD_Descriptor_T g_deviceDescriptor = {g_usbDeviceDescriptor, USB_DEVICE_DESCRIPTOR_SIZE};
/** Config descriptor */
USBD_Descriptor_T g_configDescriptor = {g_usbConfigDescriptor, USB_CONFIG_DESCRIPTOR_SIZE};
/** String descriptor */
USBD_Descriptor_T g_stringDescriptor[SRTING_DESC_NUM] =
{
    {g_usbLandIDString, USB_LANGID_STRING_SIZE},
    {g_usbVendorString, USB_VENDOR_STRING_SIZE},
    {g_usbProductString, USB_PRODUCT_STRING_SIZE},
    {g_usbSerialString, USB_SERIAL_STRING_SIZE}
};

/**
 * @brief   Device descriptor
 */
const uint8_t g_usbDeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE] =
{
    /** bLength */
    0x12,

    /** bDescriptorType */
    USBD_DESC_DEVICE,

    /** bcdUSB */
    0x00, 0x02,

    /** bDeviceClass */
    0x02,
    /** bDeviceSubClass */
    0x00,
    /** bDeviceProtocol */
    0x00,
    /** bMaxPacketSize = 64 */
    USB_EP0_PACKET_SIZE,
    /** idVendor =  314b*/
    0x4B, 0x31,
    /** idProduct = 0108 */
    0x08, 0x01,
    /** bcdDevice = 2.00 */
    0x00, 0x02,

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
const uint8_t g_usbConfigDescriptor[USB_CONFIG_DESCRIPTOR_SIZE] =
{
    /** bLength */
    0x09,
    /** bDescriptorType */
    USBD_DESC_CONFIGURATION,
    /** wTotalLength */
    USB_CONFIG_DESCRIPTOR_SIZE & 0xFF, USB_CONFIG_DESCRIPTOR_SIZE >> 8,

    /** bNumInterfaces */
    0x02,
    /** bConfigurationValue */
    0x01,
    /** iConfiguration */
    0x00,
    /** bmAttributes */
    0xC0,
    /** MaxPower */
    0x32,

    /** bLength */
    0x09,
    /** bDescriptorType */
    USBD_DESC_INTERFACE,
    /** bInterfaceNumber */
    0x00,
    /** bAlternateSetting */
    0x00,
    /** bNumEndpoints */
    0x01,
    /** bInterfaceClass */
    0x02,
    /** bInterfaceSubClass */
    0x02,
    /** bInterfaceProtocol */
    0x01,
    /** iInterface */
    0x00,

    /** bLength: Endpoint Descriptor size */
    0x05,
    /** bDescriptorType: CS_INTERFACE */
    0x24,
    /** bDescriptorSubtype: Header Func Desc */
    0x00,
    /** bcdCDC: spec release number */
    0x00, 0x02,

    /** bFunctionLength */
    0x05,
    /** bDescriptorType: CS_INTERFACE */
    0x24,
    /** bDescriptorSubtype: Call Management Func Desc */
    0x01,
    /** bmCapabilities: D0+D1 */
    0x00,
    /** bDataInterface: 1 */
    0x01,

    /** bFunctionLength */
    0x04,
    /** bDescriptorType: CS_INTERFACE */
    0x24,
    /** bDescriptorSubtype: Abstract Control Management desc */
    0x02,
    /** bmCapabilities */
    0x02,

    /** bFunctionLength */
    0x05,
    /** bDescriptorType: CS_INTERFACE */
    0x24,
    /** bDescriptorSubtype: Union func desc */
    0x06,
    /** bMasterInterface: Communication class interface */
    0x00,
    /** bSlaveInterface0: Data Class Interface */
    0x01,

    /** bLength: Endpoint Descriptor size */
    0x07,
    /** bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /** bEndpointAddress */
    0x82,
    /** bmAttributes: Interrupt */
    0x03,
     /** wMaxPacketSize: */
    0x08,0x00,
    /** bInterval: */
    0xFF,


    /** bLength: Endpoint Descriptor size */
    0x09,
    /** bDescriptorType: */
    USBD_DESC_INTERFACE,
    /** bInterfaceNumber: Number of Interface */
    0x01,
    /** bAlternateSetting: Alternate setting */
    0x00,
    /** bNumEndpoints: Two endpoints used */
    0x02,
    /** bInterfaceClass: CDC */
    0x0A,
    /** bInterfaceSubClass: */
    0x00,
    /** bInterfaceProtocol: */
    0x00,
    /** iInterface: */
    0x00,

    /** bLength: Endpoint Descriptor size */
    0x07,
    /** bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /** bEndpointAddress */
    0x01,
    /** bmAttributes: Bulk */
    0x02,
    /** wMaxPacketSize: */
    0x40,0x00,
    /** bInterval: ignore for Bulk transfer */
    0x00,

    /** bLength: Endpoint Descriptor size */
    0x07,
    /** bDescriptorType: Endpoint */
    USBD_DESC_ENDPOINT,
    /** bEndpointAddress */
    0x81,
    /** bmAttributes: Bulk */
    0x02,
    /** wMaxPacketSize: */
    0x40,0x00,
    /** bInterval: ignore for Bulk transfer */
    0x00
};

/**
 * @brief   language ID string
 */
const uint8_t g_usbLandIDString[USB_LANGID_STRING_SIZE] =
{
    /** Size */
    USB_LANGID_STRING_SIZE,
    /** bDescriptorType */
    USBD_DESC_STRING,
    0X09,0X04
};

/**
 * @brief   Vendor string
 */
const uint8_t g_usbVendorString[USB_VENDOR_STRING_SIZE] =
{
    /** Size */
    USB_VENDOR_STRING_SIZE,
    /** bDescriptorType */
    USBD_DESC_STRING,
    'G', 0, 'e', 0, 'e', 0, 'h', 0, 'y', 0
};

/**
 * @brief   Product string
 */
const uint8_t g_usbProductString[USB_PRODUCT_STRING_SIZE] =
{
    USB_PRODUCT_STRING_SIZE,
    USBD_DESC_STRING,
    'A', 0, 'P', 0, 'M', 0, '3', 0, '2', 0,
    ' ', 0, 'F', 0, 'S', 0, ' ', 0, 'V', 0,
    'C', 0, 'P', 0
};

/**
 * @brief   Serial string
 */
uint8_t g_usbSerialString[USB_SERIAL_STRING_SIZE] =
{
    USB_SERIAL_STRING_SIZE,
    USBD_DESC_STRING,

    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0
};
