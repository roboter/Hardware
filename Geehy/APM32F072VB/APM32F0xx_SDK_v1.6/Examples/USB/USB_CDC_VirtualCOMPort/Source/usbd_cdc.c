/*!
 * @file        usbd_cdc.c
 *
 * @brief       CDC source file
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

#include "usbd_cdc.h"
#include "usbd_descriptor.h"
#include "usbd_class_cdc.h"

static uint8_t dataBuf[256] = {0};

static void USBD_VCP_SetConfigCallBack(void);

/** Standard Request handler */
USBD_StdReqCallback_T stdReqCallback =
{
    NULL,      //!< getConfigurationHandler;
    NULL,      //!< getDescriptorHandler;
    NULL,      //!< getInterfaceHandler;
    NULL,      //!< getStatusHandler;
    NULL,      //!< setAddressHandler;
    USBD_VCP_SetConfigCallBack, //!< setConfigurationHandler;
    NULL,      //!< setDescriptorHandler;
    NULL,      //!< setFeatureHandler;
    NULL,      //!< setInterfaceHandler;
    NULL       //!< clearFeatureHandler;
};

/*!
 * @brief       Reset
 *
 * @param       None
 *
 * @retval      None
 */
void VCP_Reset(void)
{
    USBD_EPConfig_T epConfig;

    /** Endpoint 1 IN */
    epConfig.epNum = USBD_EP_1;
    epConfig.epType = USBD_EP_TYPE_BULK;
    epConfig.epBufAddr = USB_EP1_TX_ADDR;
    epConfig.maxPackSize = 64;
    epConfig.epStatus = USBD_EP_STATUS_NAK;
    USBD_OpenInEP(&epConfig);

    epConfig.epBufAddr = USB_EP1_RX_ADDR;
    USBD_OpenOutEP(&epConfig);

    epConfig.epNum = USBD_EP_2;
    epConfig.epType = USBD_EP_TYPE_INTERRUPT;
    epConfig.epBufAddr = USB_EP2_TX_ADDR;
    epConfig.maxPackSize = 8;
    USBD_OpenInEP(&epConfig);
}

/*!
 * @brief       Standard request set configuration call back
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_VCP_SetConfigCallBack(void)
{
    USBD_RxData(USBD_EP_1, dataBuf, g_usbDev.outBuf[USBD_EP_1].maxPackSize);
}

/*!
 * @brief       OUT endpoint transfer done handler(except EP0)
 *
 * @param       ep : OUT endpoint
 *
 * @retval      None
 */
void USBD_VCP_OutEpCallback(uint8_t ep)
{
    uint32_t dataCnt;

    if (ep == USBD_EP_1)
    {
        dataCnt = g_usbDev.outBuf[USBD_EP_1].xferCnt;

        USBD_TxData(USBD_EP_1, dataBuf, dataCnt);
    }
}

/*!
 * @brief       IN endpoint transfer done handler(except EP0)
 *
 * @param       ep : IN endpoint
 *
 * @retval      None
 */
void USBD_VCP_InEpCallback(uint8_t ep)
{
    if (ep == USBD_EP_1)
    {
        USBD_RxData(USBD_EP_1, dataBuf, g_usbDev.outBuf[USBD_EP_1].maxPackSize);
    }
}

/*!
 * @brief       USB cdc init
 *
 * @param       None
 *
 * @retval      None
 */
void CDC_Init(void)
{
    USBD_InitParam_T usbParam;

    USBD_InitParamStructInit(&usbParam);

    usbParam.classReqHandler = USBD_ClassHandler;
    usbParam.resetHandler = VCP_Reset;
    usbParam.inEpHandler = USBD_VCP_InEpCallback;
    usbParam.outEpHandler = USBD_VCP_OutEpCallback;
    usbParam.pDeviceDesc = (USBD_Descriptor_T *)&g_deviceDescriptor;
    usbParam.pConfigurationDesc = (USBD_Descriptor_T *)&g_configDescriptor;
    usbParam.pStringDesc = (USBD_Descriptor_T *)g_stringDescriptor;
    usbParam.pStdReqCallback = &stdReqCallback;

    USBD_Init(&usbParam);
}
