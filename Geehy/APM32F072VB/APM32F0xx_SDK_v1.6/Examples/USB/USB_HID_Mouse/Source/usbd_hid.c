/*!
 * @file        usbd_hid.c
 *
 * @brief       HID source file
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

#include "usbd_hid.h"
#include "usbd_descriptor.h"
#include "usbd_class_hid.h"

/** Endpoint status */
static uint8_t s_statusEP = 1;
/** USB configuration status */
static uint8_t s_usbConfigStatus = 0;

USBD_StdReqCallback_T s_stdCallback =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    HidMouse_SetConfigCallBack,
    NULL,
    NULL,
    NULL,
    NULL,
};

/*!
 * @brief       Reset
 *
 * @param       None
 *
 * @retval      None
 */
void HidMouse_Reset(void)
{
    USBD_EPConfig_T epConfig;

    s_usbConfigStatus = 0;

    /** Endpoint 1 IN */
    epConfig.epNum = USBD_EP_1;
    epConfig.epType = USBD_EP_TYPE_INTERRUPT;
    epConfig.epBufAddr = USB_EP1_TX_ADDR;
    epConfig.maxPackSize = 4;
    epConfig.epStatus = USBD_EP_STATUS_NAK;
    USBD_OpenInEP(&epConfig);

    USBD_SetEPRxStatus(USBD_EP_1, USBD_EP_STATUS_DISABLE);
}

/*!
 * @brief       Endpoint handler
 *
 * @param       ep:     Endpoint number
 *
 * @param       dir:    Direction.0: Out; 1: In
 *
 * @retval      None
 */
void HidMouse_EPHandler(uint8_t ep)
{
    s_statusEP = 1;
}

/*!
 * @brief       Standard request set configuration call back
 *
 * @param       None
 *
 * @retval      None
 */
void HidMouse_SetConfigCallBack(void)
{
    s_usbConfigStatus = 1;
}

/*!
 * @brief       GPIO init
 *
 * @param       None
 *
 * @retval      None
 */
void HidMouse_GPIOInit(void)
{
    GPIO_Config_T gpioConfigStruct;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);

    gpioConfigStruct.mode = GPIO_MODE_IN;
    gpioConfigStruct.pupd = GPIO_PUPD_PU;
    gpioConfigStruct.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;

    GPIO_Config(GPIOA, &gpioConfigStruct);
}

/*!
 * @brief       Mouse write
 *
 * @param       key:    Mouse key
 *
 * @retval      None
 */
void HidMouse_Write(uint8_t key)
{
    int8_t x = 0;
    int8_t y = 0;
    uint8_t buffer[4] = {0, 0, 0, 0};

    switch (key)
    {
        case HID_MOUSE_KEY_LEFT:
            x -= 10;
        break;

        case HID_MOUSE_KEY_RIGHT:
            x += 10;
        break;

        case HID_MOUSE_KEY_UP:
            y -= 10;
        break;

        case HID_MOUSE_KEY_DOWN:
            y += 10;
        break;

        default:
            return;
    }

    buffer[1] = x;
    buffer[2] = y;

    s_statusEP = 0;

    USBD_TxData(USBD_EP_1, buffer, sizeof(buffer));
}

/*!
 * @brief       Standard request Report HID Descriptor
 *
 * @param       reqData:    Standard request data
 *
 * @retval      None
 */
void HidMouse_ReportDescriptor(USBD_DevReqData_T *reqData)
{
    uint8_t len;

    if((reqData->byte.bRequest == USBD_GET_DESCRIPTOR) &&
        (reqData->byte.bmRequestType.bit.recipient == USBD_RECIPIENT_INTERFACE) &&
        (reqData->byte.bmRequestType.bit.type == USBD_REQ_TYPE_STANDARD))
    {
        if(reqData->byte.wValue[1] == 0x21)
        {
            len = USB_MIN(reqData->byte.wLength[0], 9);
            USBD_CtrlInData((uint8_t *)&g_configDescriptor.pDesc[0x12], len);
        }
        else if(reqData->byte.wValue[1] == 0x22)
        {
            len = USB_MIN(reqData->byte.wLength[0], g_ReportDescriptor.size);
            USBD_CtrlInData((uint8_t *)g_ReportDescriptor.pDesc, len);
        }
    }
    else
    {
        USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
    }
}

/*!
 * @brief       Read key
 *
 * @param       None
 *
 * @retval      None
 */
uint8_t HidMouse_ReadKey(void)
{
    /** Right key */
    if(!GPIO_ReadInputBit(GPIOA, GPIO_PIN_0))
    {
        return HID_MOUSE_KEY_RIGHT;
    }

    /** Left key */
    if(!GPIO_ReadInputBit(GPIOA, GPIO_PIN_1))
    {
        return HID_MOUSE_KEY_LEFT;
    }

    return HID_MOUSE_KEY_NULL;
}

/*!
 * @brief       Mouse process
 *
 * @param       None
 *
 * @retval      None
 */
void HidMouse_Proc(void)
{
    uint8_t key = HID_MOUSE_KEY_NULL;

    if(!s_usbConfigStatus)
    {
        return;
    }

    key = HidMouse_ReadKey();
    if(key != HID_MOUSE_KEY_NULL)
    {
        if(s_statusEP)
        {
            HidMouse_Write(key);
        }
    }
}

/*!
 * @brief       HID mouse init
 *
 * @param       None
 *
 * @retval      None
 */
void HidMouse_Init(void)
{
    USBD_InitParam_T usbParam;

    USBD_InitParamStructInit(&usbParam);

    usbParam.classReqHandler = USBD_ClassHandler;
    usbParam.stdReqExceptionHandler = HidMouse_ReportDescriptor;

    usbParam.resetHandler = HidMouse_Reset;
    usbParam.inEpHandler = HidMouse_EPHandler;
    usbParam.pDeviceDesc = (USBD_Descriptor_T *)&g_deviceDescriptor;
    usbParam.pConfigurationDesc = (USBD_Descriptor_T *)&g_configDescriptor;
    usbParam.pStringDesc = (USBD_Descriptor_T *)g_stringDescriptor;
    usbParam.pStdReqCallback = &s_stdCallback;

    USBD_Init(&usbParam);

    HidMouse_GPIOInit();
}
