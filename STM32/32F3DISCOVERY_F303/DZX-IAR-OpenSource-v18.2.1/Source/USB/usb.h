/*******************************************************************************************************************************************

    DZX | USB                                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides common definitions for USB.

    ------------------------------------------------------------------------------------------------------------------------------------

    GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)

    This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
    following information to ensure all requirements of the license will be met:  
    <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.

    ------------------------------------------------------------------------------------------------------------------------------------
    COPYRIGHT (C) 2018 DZX DESIGNS 

*******************************************************************************************************************************************/
#ifndef USB_H__
#define USB_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    USB REQUEST TYPES
*******************************************************************************************************************************************/
#define USBSTANDARD                     0
#define USBCLASS                        1
#define USBVENDOR                       2

/*******************************************************************************************************************************************
    USB REQUEST RECIPIENTS
*******************************************************************************************************************************************/
#define USBRECIPIENTDEVICE              0
#define USBRECIPIENTINTERFACE           1
#define USBRECIPIENTENDPOINT            2

/*******************************************************************************************************************************************
    USB REQUESTS
*******************************************************************************************************************************************/
#define USBGETSTATUS                    0
#define USBCLEARFEATURE                 1
#define USBGETMSDESCRIPTOR              1
#define USBSETFEATURE                   3
#define USBSETADDRESS                   5
#define USBGETDESCRIPTOR                6
#define USBSETDESCRIPTOR                7
#define USBGETCONFIGURATION             8
#define USBSETCONFIGURATION             9
#define USBGETINTERFACE                 10
#define USBSETINTERFACE                 11
#define USBSYNCHFRAME                   12
#define USBGETEXTENDEDCOMPATID          4
#define USBGETEXTENDEDPROPERTIES        5

/*******************************************************************************************************************************************
    USB DESCRIPTOR TYPES
*******************************************************************************************************************************************/
#define USBDESTYPEDEVICE                1
#define USBDESTYPECONFIGURATION         2
#define USBDESTYPESTRING                3
#define USBDESTYPEINTERFACE             4
#define USBDESTYPEENDPOINT              5
#define USBDESTYPEDEVICEQUALIFIER       6
#define USBDESTYPEOTHERSPEED            7
#define USBDESTYPEINTERFACEPOWER        8
#define USBDESTTYPEOTG                  9
#define USBDESTYPEDEBUG                 10
#define USBDESTYPEINTERFACEASSOCIATION  11
#define USBDESTYPEHID                   0x21
#define USBDESTYPEHIDREPORT             0x22
#define USBDESTYPEDFUFUNCTIONAL         0x21

/*******************************************************************************************************************************************
    USB DEVICE CLASSES
*******************************************************************************************************************************************/
#define USBDEVCLASSINTFDEFINED          0x0
#define USBDEVCLASSCDC                  0x2
#define USBDEVCLASSHUB                  0x9
#define USBDEVCLASSBILLBOARD            0x11
#define USBDEVCLASSDIAGNOSTIC           0xDC
#define USBDEVCLASSMISC                 0xEF
#define USBDEVCLASSVENDOR               0xFF

/*******************************************************************************************************************************************
    USB INTERFACE CLASSES
*******************************************************************************************************************************************/
#define USBINTFCLASSAUDIO               0x1
#define USBINTFCLASSCDC                 0x2
#define USBINTFCLASSHID                 0x3
#define USBINTFCLASSPHYSICAL            0x5
#define USBINTFCLASSIMAGE               0x6
#define USBINTFCLASSPRINTER             0x7
#define USBINTFCLASSMASSSTORAGE         0x8
#define USBINTFCLASSHUB                 0x9
#define USBINTFCLASSCDCDATA             0xA
#define USBINTFCLASSSMARTCARD           0xB
#define USBINTFCLASSCONTENTSECURITY     0xD
#define USBINTFCLASSVIDEO               0xE
#define USBINTFCLASSHEALTHCARE          0xF
#define USBINTFCLASSAUDIOVIDEO          0x10
#define USBINTFCLASSDIAGNOSTIC          0xDC
#define USBINTFCLASSWIRELESS            0xE0
#define USBINTFCLASSMISC                0xEF
#define USBINTFCLASSAPPLICATION         0xFE
#define USBINTFCLASSVENDOR              0xFF

#define USBINTFSUBCLASSCONTROLDEVICE    0x1
#define USBINTFSUBCLASSSTREAMING        0x2
#define USBINTFSUBCLASSMIDISTREAMING    0x3
#define USBINTFSUBCLASSACM              0x2
#define USBINTFSUBCLASSSCSI             0x6
#define USBINTFSUBCLASSVENDOR           0xFF
#define USBINTFPROTOCOLV25TER           0x2
#define USBINTFPROTOCOLBULKONLY         0x50
#define USBINTFPROTOCOLVENDOR           0xFF


/*******************************************************************************************************************************************
    USB STANDARD FEATURES
*******************************************************************************************************************************************/
#define USBDENDPOINTHALT               0
#define USBDDEVICEREMOTEWAKEUP         1
#define USBDTESTMODE                   2

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum USBTRANSFERTYPE USBTRANSFERTYPE;
typedef enum USBSPEED USBSPEED;
typedef struct USBREQUEST USBREQUEST;
typedef union USBDEVICESTATUS USBDEVICESTATUS;
typedef struct USBDEVICEID USBDEVICEID;
typedef struct USBCLASSCODE USBCLASSCODE;
typedef struct USBDESCRIPTOR USBDESCRIPTOR;
typedef union USBENDPOINTSTATUS USBENDPOINTSTATUS;

typedef struct USBDEVICEDESCRIPTOR USBDEVICEDESCRIPTOR;
typedef struct USBCONFIGURATIONDESCRIPTOR USBCONFIGURATIONDESCRIPTOR;
typedef struct USBINTERFACEDESCRIPTOR USBINTERFACEDESCRIPTOR;
typedef struct USBINTERFACEASSOCIATIONDESCRIPTOR USBINTERFACEASSOCIATIONDESCRIPTOR;
typedef struct USBENDPOINTDESCRIPTOR USBENDPOINTDESCRIPTOR;
typedef struct USBOTHERSPEEDDESCRIPTOR USBOTHERSPEEDDESCRIPTOR;
typedef struct USBSTRINGDESCRIPTOR USBSTRINGDESCRIPTOR;
typedef struct USBDEVICEQUALIFIERDESCRIPTOR USBDEVICEQUALIFIERDESCRIPTOR;

/***************************************************************************************************************************************//**

    Represents a type of USB transfer.
    @module     usb

*******************************************************************************************************************************************/
enum USBTRANSFERTYPE {
    USBTRANSFERCONTROL          = 0,            /**< A control endpoint transfer */
    USBTRANSFERISOCHRONOUS      = 1,            /**< An isochronous endpoint transfer */
    USBTRANSFERBULK             = 2,            /**< A bulk endpoint transfer */
    USBTRANSFERINTERRUPT        = 3,            /**< An interrupt endpoint transfer */
};

/***************************************************************************************************************************************//**

    Represents a USB transfer speed.
    @module     usb

*******************************************************************************************************************************************/
enum USBSPEED {
    USBSPEED_UNKNOWN = 0,                       /**< An unknown transfer speed */
    USBSPEED_LOW,                               /**< A low speed (1.5 Mbit/s) connection */
    USBSPEED_FULL,                              /**< A full speed (12 Mbit/s) connection */
    USBSPEED_HIGH                               /**< A high speed (480 Mbit/s) connection */
};

/***************************************************************************************************************************************//**

    Represents a USB request.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBREQUEST {
    union {
        struct {
            BYTE recipient  : 5;            /**< Recipient (0=Device, 1=Interface, 2=Endpoint, 3=Other) */
            BYTE type       : 2;            /**< Type (0=Standard, 1=Class, 2=Vendor, 3=Reserved) */
            BYTE dir        : 1;            /**< Data transfer direction (0=Host-to-Device, 1=Device-to-Host) */
        } POSTPACKED;
        BYTE value;
    } POSTPACKED bmRequestType;             /**< Characteristics of request */
    
	BYTE    bRequest;                       /**< Specific request */
	UINT16  wValue;                         /**< 16-bit sized field that varies according to the request */
	UINT16  wIndex;                         /**< 16-bit sized field that varies according to the request */
	UINT16  wLength;                        /**< Number of bytes to transfer if there is a data stage */
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents the status of a USB device.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED union USBDEVICESTATUS {
	struct {
		UINT16 SELFPOWERED  :1;             /**< Indicates whether the device is currently self powered */
		UINT16 REMOTEWAKEUP :1;             /**< Indicates whether the device is enabled to request remote wakeup */
		UINT16              :14;
	} POSTPACKED BITS;

	UINT16 VALUE;
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents the status of a USB endpoint.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED union USBENDPOINTSTATUS {
	struct {
		UINT16 HALT  :1;                    /**< Indicator of whether the endpoint is currently halted */
		UINT16       :15;
	} POSTPACKED BITS;

	UINT16 VALUE;
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents an identifier for a USB device.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBDEVICEID {
    UINT16 idVendor;                            /**< The vendor identifier code */
    UINT16 idProduct;                           /**< The product identifier code */
} POSTPACKED;   

/***************************************************************************************************************************************//**

    Represents codes that describe a USB class.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBCLASSCODE {
    BYTE bClass;                                /**< The class code */
    BYTE bSubClass;                             /**< The subclass code */
    BYTE bProtocol;                             /**< The protocol code */
    BYTE pad;
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBDESCRIPTOR {
    BYTE bLength;                               /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;                       /**< Indicates the type of descriptor */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB device descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBDEVICEDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;           /**< DEVICE descriptor type (USBDESTYPEDEVICE = 1) */
	UINT16 bcdUSB;                  /**< USB specification release number in binary-coded decimal (i.e. 2.10 is 210H) */
	BYTE bDeviceClass;              /**< Class code (assigned by the USB-IF) */
	BYTE bDeviceSubClass;           /**< Subclass code (assigned by the USB-IF) */
	BYTE bDeviceProtocol;           /**< Protocol code (assigned by the USB-IF) */
	BYTE bMaxPacketSize;            /**< Maximum packet size for endpoint zero (only 8, 16, 32, or 64 are valid) */
	UINT16 idVendor;                /**< Vendor ID (assigned by the USB-IF) */
	UINT16 idProduct;               /**< Product ID (assigned by the manufacturer) */
	UINT16 bcdDevice;               /**< Device release number in binary-coded decimal */
	BYTE iManufacturer;             /**< Index of string descriptor describing the manufacturer */
	BYTE iProduct;                  /**< Index of string descriptor describing the product */
	BYTE iSerialNumber;             /**< Index of string descriptor describing the device's serial number */
	BYTE bNumConfigurations;        /**< Number of possible configurations */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB configuration descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBCONFIGURATIONDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;           /**< CONFIGURATION descriptor type (USBDESTYPECONFIGURATION = 2) */
	UINT16 wTotalLength;            /**< Total length in bytes returned for this configuration */
	BYTE bNumInterfaces;            /**< Number of interfaces supported by this configuration */
	BYTE bConfigurationValue;       /**< Value to use as an argument to the SetConfiguration request to select this configuration */
	BYTE iConfiguration;            /**< Index of string descriptor describing this configuration */
	BYTE bmAttributes;              /**< Configuration characteristics */
	BYTE bMaxPower;                 /**< Maximum power consumption expressed in 2mA units (i.e. 50 = 100mA) */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB interface descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBINTERFACEDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;           /**< INTERFACE descriptor type. (USBDESTYPEINTERFACE = 4) */
	BYTE bInterfaceNumber;          /**< Number of this interface (zero based). */
	BYTE bAlternateSetting;         /**< Value used to select this alternate setting for the interface identified in the previous field. */
	BYTE bNumEndpoints;             /**< Number of endpoints used by this interface. */
	BYTE bInterfaceClass;           /**< Class code (assigned by the USB-IF). */
	BYTE bInterfaceSubClass;        /**< Subclass code (assigned by the USB-IF). */
	BYTE bInterfaceProtocol;        /**< Protocol code (assigend by the USB-IF). */
	BYTE iInterface;                /**< Index of string descriptor describing this interface. */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB interface association descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBINTERFACEASSOCIATIONDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor. */
	BYTE bDescriptorType;           /**< INTERFACE ASSOCIATION descriptor type (USBDESTYPEINTERFACEASSOCIATION = 11). */
	BYTE bFirstInterface;           /**< Interface number of the first interface that is associated with this function. */
	BYTE bInterfaceCount;           /**< Number of contiguous interfaces that are associated with this function. */
	BYTE bFunctionClass;            /**< Class code (assigned by USB-IF). */
	BYTE bFunctionSubClass;         /**< Subclass code (assigned by USB-IF). */
	BYTE bFunctionProtocol;         /**< Protocol code (assigned by USB-IF). */
	BYTE iInterface;                /**< Index of string descriptor describing this function. */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB endpoint descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBENDPOINTDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor. */
	BYTE bDescriptorType;           /**< ENDPOINT descriptor type (USBDESTYPEENDPOINT = 5) */
	BYTE bEndpointAddress;          /**< The address for the endpoint */
	BYTE bmAttributes;              /**< Attributes for the endpoint */
	UINT16 wMaxPacketSize;          /**< The maximum transfer size in bytes for the endpoint */
	BYTE bInterval;                 /**< The interval rate for the endpoint */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB other speed descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBOTHERSPEEDDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;           /**< CONFIGURATION descriptor type (USBDESTYPECONFIGURATION = 2) */
	UINT16 wTotalLength;            /**< Total length in bytes returned for this configuration */
	BYTE bNumInterfaces;            /**< Number of interfaces supported by this configuration */
	BYTE bConfigurationValue;       /**< Value to use as an argument to the SetConfiguration request to select this configuration */
	BYTE iConfiguration;            /**< Index of string descriptor describing this configuration */
	BYTE bmAttributes;              /**< Configuration characteristics */
	BYTE bMaxPower;                 /**< Maximum power consumption expressed in 2mA units (i.e. 50 = 100mA) */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB string descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBSTRINGDESCRIPTOR {
    BYTE bLength;                   /**< The size in bytes of the descriptor. */
	BYTE bDescriptorType;           /**< STRING descriptor type. (USBDESTYPESTRING = 3) */
    UINT16 wChar[1];                /**< The individual unicode characters within string descriptor */
} POSTPACKED;

/***************************************************************************************************************************************//**

    A USB device qualifier descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBDEVICEQUALIFIERDESCRIPTOR {
	BYTE bLength;                   /**< The size in bytes of the descriptor. */
	BYTE bDescriptorType;           /**< DEVICE QUALIFIER descriptor type. (USBDESTYPEDEVICEQUALIFIER = 6) */
	UINT16 bcdUSB;
	BYTE bDeviceClass;
	BYTE bDeviceSubClass;
	BYTE bDeviceProtocol;
	BYTE bMaxPacketSize;
	BYTE bNumConfigurations;
    BYTE reserved;
} POSTPACKED;


/*******************************************************************************************************************************************
    MICROSOFT OS DESCRIPTORS
*******************************************************************************************************************************************/
typedef struct USBMSFTOSDESCRIPTOR USBMSFTOSDESCRIPTOR;
typedef struct MSFTCOMPATFEATUREDESCRIPTOR MSFTCOMPATFEATUREDESCRIPTOR;
typedef struct MSFTWINUSBEXTENDEDFEATURESDESCRIPTOR MSFTWINUSBEXTENDEDFEATURESDESCRIPTOR;

/***************************************************************************************************************************************//**

    A Microsoft OS descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct USBMSFTOSDESCRIPTOR {
    BYTE bLength;
	BYTE bDescriptorType;
    UINT16 qwSignature[7];
    BYTE bMS_VendorCode;
    BYTE bPad;
} POSTPACKED;

/***************************************************************************************************************************************//**

    A Microsoft OS compatible feature descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct MSFTCOMPATFEATUREDESCRIPTOR {
    UINT32 dwLength;
	UINT16 bcdVersion;
    UINT16 wIndex;
    BYTE bCount;
    BYTE reserved[7];
    BYTE bFirstInterfaceNumber;
    BYTE reserved2;
    BYTE compatibleID[8];
    BYTE subCompatibleID[8];
    BYTE reserved3[6];
} POSTPACKED;

/***************************************************************************************************************************************//**

    A Microsoft OS extended feature descriptor for WinUSB.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct MSFTWINUSBEXTENDEDFEATURESDESCRIPTOR {
    UINT32 dwLength;
	UINT16 bcdVersion;
    UINT16 wIndex;
    UINT16 wCount;
    UINT32 dwSize;
	UINT32 dwPropertyDataType;
    UINT16 wPropertyNameLength;
    UINT16 bPropertyName[20];
    UINT32 dwPropertyDataLength;
    UINT16 bPropertyData[39];
} POSTPACKED;

/*******************************************************************************************************************************************
    HUMAN INTERFACE DEVICE CLASS (HID)
*******************************************************************************************************************************************/
#define HIDSUBCLASSNONE                 0x0
#define HIDSUBCLASSBOOT                 0x1
#define HIDPROTOCOLNONE                 0x0
#define HIDPROTOCOLKEYBOARD             0x1
#define HIDPROTOCOLMOUSE                0x2

#define HIDGETREPORT                    1
#define HIDGETIDLE                      2
#define HIDGETPROTOCOL                  3
#define HIDSETREPORT                    9
#define HIDSETIDLE                      10
#define HIDSETPROTOCOL                  11

#define HIDINPUTREPORT                  1
#define HIDOUTPUTREPORT                 2
#define HIDFEATUREREPORT                3

#define HIDPHYSICAL                     0x0
#define HIDAPPLICATION                  0x1
#define HIDLOGICAL                      0x2
#define HIDREPORT                       0x3
#define HIDNAMEDARRAY                   0x4
#define HIDUSAGESWITCH                  0x5
#define HIDUSAGEMODIFIER                0x6

#define HIDUSAGEPAGEUNDEFINED           0x0
#define HIDUSAGEPAGEGENERIC             0x1
#define HIDUSAGEPAGESIMULATION          0x2
#define HIDUSAGEPAGEVR                  0x3
#define HIDUSAGEPAGESPORT               0x4
#define HIDUSAGEPAGEGAME                0x5
#define HIDUSAGEPAGEDEVCONTROLS         0x6
#define HIDUSAGEPAGEKEYBOARD            0x7
#define HIDUSAGEPAGELED                 0x8
#define HIDUSAGEPAGEBUTTON              0x9

#define HIDUSAGEUNDEFINED               0x0
#define HIDUSAGEGENERICPOINTER          0x1
#define HIDUSAGEGENERICMOUSE            0x2
#define HIDUSAGEGENERICJOYSTICK         0x4
#define HIDUSAGEGENERICGAMEPAD          0x5
#define HIDUSAGEGENERICKEYBOARD         0x6
#define HIDUSAGEGENERICKEYPAD           0x7
#define HIDUSAGEGENERICX                0x30
#define HIDUSAGEGENERICY                0x31
#define HIDUSAGEGENERICZ                0x32
#define HIDUSAGEGENERICRX               0x33
#define HIDUSAGEGENERICRY               0x34
#define HIDUSAGEGENERICRZ               0x35
#define HIDUSAGEGENERICSLIDER           0x36
#define HIDUSAGEGENERICDIAL             0x37
#define HIDUSAGEGENERICWHEEL            0x38
#define HIDUSAGEGENERICHATSWITCH        0x39
#define HIDUSAGEGENERICCOUNTEDBUFFER    0x3A
#define HIDUSAGEGENERICBYTECOUNT        0x3B
#define HIDUSAGEGENERICMOTIONWAKEUP     0x3C
#define HIDUSAGEGENERICVX               0x40
#define HIDUSAGEGENERICVY               0x41
#define HIDUSAGEGENERICVZ               0x42
#define HIDUSAGEGENERICVBRX             0x43
#define HIDUSAGEGENERICVBRY             0x44
#define HIDUSAGEGENERICVBRZ             0x45
#define HIDUSAGEGENERICVNO              0x46
#define HIDUSAGEGENERICSYSTEMCTL        0x80
#define HIDUSAGEGENERICSYSCTLPOWER      0x81
#define HIDUSAGEGENERICSYSCTLSLEEP      0x82
#define HIDUSAGEGENERICSYSCTLWAKE       0x83
#define HIDUSAGEGENERICSYSCTLCTXTMENU   0x84
#define HIDUSAGEGENERICSYSCTLMAINMENU   0x85
#define HIDUSAGEGENERICSYSCTLAPPMENU    0x86
#define HIDUSAGEGENERICSYSCTLHELPMENU   0x87
#define HIDUSAGEGENERICSYSCTLMENUEXIT   0x88
#define HIDUSAGEGENERICSYSCTLMENUSELECT 0x89
#define HIDUSAGEGENERICSYSCTLMENURIGHT  0x8A
#define HIDUSAGEGENERICSYSCTLMENULEFT   0x8B
#define HIDUSAGEGENERICSYSCTLMENUUP     0x8C
#define HIDUSAGEGENERICSYSCTLMENUDOWN   0x8D

#define HIDUSAGEPAGE(value)             0x05, value
#define HIDUSAGEPAGEVENDOR(value)       0x06, value, 0xFF
#define HIDUSAGE(value)                 0x09, value
#define HIDUSAGEMIN(value)              0x19, value
#define HIDUSAGEMAX(value)              0x29, value
#define HIDINPUT(value)                 0x81, value
#define HIDOUTPUT(value)                0x91, value
#define HIDFEATURE(value)               0xB1, value
#define HIDCOLLECTION(value)            0xA1, value
#define HIDENDCOLLECTION()              0xC0
#define HIDLOGICALMIN(value)            0x15, value
#define HIDLOGICALMIN16(value)          0x16, (value & 0xFF), ((value >> 8) & 0xFF)
#define HIDLOGICALMIN32(value)          0x17, (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF)
#define HIDLOGICALMAX(value)            0x25, value
#define HIDLOGICALMAX16(value)          0x26, (value & 0xFF), ((value >> 8) & 0xFF)
#define HIDLOGICALMAX32(value)          0x27, (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF)
#define HIDPHYSICALMIN(value)           0x35, value
#define HIDPHYSICALMIN16(value)         0x36, (value & 0xFF), ((value >> 8) & 0xFF)
#define HIDPHYSICALMIN32(value)         0x37, (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF)
#define HIDPHYSICALMAX(value)           0x45, value
#define HIDPHYSICALMAX16(value)         0x46, (value & 0xFF), ((value >> 8) & 0xFF)
#define HIDPHYSICALMAX32(value)         0x47, (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF)
#define HIDUNIT(value)                  0x65, value
#define HIDUNIT16(value)                0x66, (value & 0xFF), ((value >> 8) & 0xFF)
#define HIDUNIT32(value)                0x67, (value & 0xFF), ((value >> 8) & 0xFF), ((value >> 16) & 0xFF), ((value >> 24) & 0xFF)
#define HIDUNITEXPONENT(value)          0x55, value
#define HIDREPORTSIZE(value)            0x75, value
#define HIDREPORTID(value)              0x85, value
#define HIDREPORTCOUNT(value)           0x95, value
#define HIDPUSH()                       0xA0
#define HIDPOP()                        0xB0

#define HIDDATA                         (0 << 0)
#define HIDCONSTANT                     (1 << 0)
#define HIDARRAY                        (0 << 1)
#define HIDVARIABLE                     (1 << 1)
#define HIDABSOLUTE                     (0 << 2)
#define HIDRELATIVE                     (1 << 2)
#define HIDNOWRAP                       (0 << 3)
#define HIDWRAP                         (1 << 3)
#define HIDLINEAR                       (0 << 4)
#define HIDNONLINEAR                    (1 << 4)
#define HIDPREFERREDSTATE               (0 << 5)
#define HIDNOPREFERRED                  (1 << 5)
#define HIDNONULLPOSITION               (0 << 6)
#define HIDNULLSTATE                    (1 << 6)
#define HIDNONVOLATILE                  (0 << 7)
#define HIDVOLATILE                     (1 << 7)

typedef PREPACKED struct USBHIDDESCRIPTOR {
	BYTE bLength;
	BYTE bDescriptorType;
	UINT16 bcdHID;
	BYTE bCountryCode;
	BYTE bNumDescriptors;
	BYTE bDescriptorType2;
	UINT16 wDescriptorLength;
} POSTPACKED USBHIDDESCRIPTOR;



/*******************************************************************************************************************************************
    DEVICE FIRMWARE UPDATE (DFU)
*******************************************************************************************************************************************/
typedef enum DFUERROR DFUERROR;
typedef struct DFUFUNCTIONALDESCRIPTOR DFUFUNCTIONALDESCRIPTOR;
typedef struct DFUSTATUS DFUSTATUS;

#define USBDFUDETACH                    0
#define USBDFUDNLOAD                    1
#define USBDFUUPLOAD                    2
#define USBDFUGETSTATUS                 3
#define USBDFUCLRSTATUS                 4
#define USBDFUGETSTATE                  5
#define USBDFUABORT                     6

#define MODE_RUNTIME                    1                       /**< Indicates the DFU application mode */
#define MODE_DFU                        2                       /**< Indicates the DFU runtime mode */

#define appIDLE                         0
#define appDETACH                       1
#define dfuIDLE                         2
#define dfuDNLOADSYNC                   3
#define dfuDNBUSY                       4
#define dfuDNLOADIDLE                   5
#define dfuMANIFESTSYNC                 6
#define dfuMANIFEST                     7
#define dfuMANIFESTWAITRESET            8
#define dfuUPLOADIDLE                   9
#define dfuERROR                        10

/***************************************************************************************************************************************//**

    Represents the support DFU status codes.
    @module     usb

*******************************************************************************************************************************************/
enum DFUERROR {
    DFUERROR_OK = 0,                /**< No error condition is present. */
    DFUERROR_TARGET,                /**< File is not targeted for use by this device. */
    DFUERROR_FILE,                  /**< File is for this device, but fails some vendor-specific verification test. */
    DFUERROR_WRITE,                 /**< Device is unable to write memory. */
    DFUERROR_ERASE,                 /**< Memory erase function failed. */
    DFUERROR_CHECK_ERASED,          /**< Memory erase check failed. */
    DFUERROR_PROG,                  /**< Program memory function failed. */
    DFUERROR_VERIFY,                /**< Programmed memory failed verification. */
    DFUERROR_ADDRESS,               /**< Cannot program memory due to received adddress that is out of range. */
    DFUERROR_NOTDONE,               /**< Received DFU_DNLOAD with wLength=0, but device does not this it has all of the data yet. */
    DFUERROR_FIRMWARE,              /**< Device's firmware is corrupt. It cannot return to run-time (non-DFU) operations. */
    DFUERROR_VENDOR,                /**< iString indicates a vendor-specific error. */
    DFUERROR_USBR,                  /**< Device detected unexpected USB reset signaling. */
    DFUERROR_POR,                   /**< Device detected unexpected power on reset. */
    DFUERROR_UNKNOWN,               /**< Something went wrong, but the device does not know what it was. */
    DFUERROR_STALLEDPKT,            /**< Device stalled an unexpected request. */
};

/***************************************************************************************************************************************//**

    A DFU functional descriptor.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct DFUFUNCTIONALDESCRIPTOR {
    BYTE bLength;                   /**< The size in bytes of the descriptor */
	BYTE bDescriptorType;           /**< DFU FUNCTIONAL descriptor type (USBDESTYPEDFUFUNCTIONAL = 0x21) */         
    BYTE bmAttributes;              /**< Bit mask attributes */
    UINT16 wDetachTimeOut;          /**< The time, in milliseconds, the device will wait before performing a DETACH event */
    UINT16 wTransferSize;           /**< Maximum number of bytes that the device can accept per write transaction */
    UINT16 bcdDFUVersion;           /**< The DFU version */
} POSTPACKED;

/***************************************************************************************************************************************//**

    Represents the status of a Device Firmware Update (DFU) interface.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct DFUSTATUS {
    struct {
        UINT32 bStatus          :8;     /**< The current status of the interface */   
        UINT32 bwPollTimeout    :24;    /**< The time, in milliseconds, between polling the status information */
    } POSTPACKED;
    
    BYTE bState;                        /**< The current state of the interface */
    BYTE iString;                       /**< The index of a string that describes the current status of the interface */
} POSTPACKED;


/*******************************************************************************************************************************************
    MASS STORAGE CLASS (MSC)
*******************************************************************************************************************************************/
typedef struct CBW CBW;
typedef struct CSW CSW;

#define MSCGETMAXLUN                    0xFE            /* Mass storage class interface requests */
#define MSCRESET                        0xFF

#define CBW_SIGNATURE					0x43425355      /**< A valid command block wrapper signature value */
#define CSW_SIGNATURE					0x53425355      /**< A valid command status wrapper signature value */

#define CSW_PASSED                      0			    /**< Indicates the command executed successfully */
#define CSW_FAILED                      1			    /**< Indicates the command failed */
#define CSW_PHASEERROR                  2	            /**< Indicates a phase (state) error */

#define SENSEKEY_NONE                   0x0             /* Sense key value definitions */
#define SENSEKEY_SOFTERROR              0x1
#define SENSEKEY_NOTREADY               0x2
#define SENSEKEY_MEDIUMERROR            0x3
#define SENSEKEY_HARDWAREERROR          0x4
#define SENSEKEY_ILLEGALREQUEST         0x5
#define SENSEKEY_UNITATTENTION          0x6
#define SENSEKEY_WRITEPROTECT           0x7
#define SENSEKEY_ABORTEDCOMMAND         0xB
#define SENSEKEY_OTHER                  0xE

#define ASC_NONE                        0x0             /* Additional sense code (ASC) value definitions */
#define ASC_NOTREADY                    0x4
#define ASC_UNSUPPORTEDCOMMAND          0x20
#define ASC_LBAOUTOFRANGE               0x21
#define ASC_INVALIDFIELD                0x24
#define ASC_WRITEPROTECTED              0x27
#define ASC_MEDIUMNOTPRESET             0x3A

#define ASCQ_NONE                       0x0             /* Additional sense code qualifier (ASCQ) value definitions */
#define ASCQ_NEEDSTARTUNIT              0x2

#define SCSI_TESTUNITREADY              0x00            /* SCSI Commands */
#define SCSI_REQUESTSENSE               0x03
#define SCSI_FORMAT_UNIT                0x04
#define SCSI_INQUIRY                    0x12
#define SCSI_MODE_SELECT6               0x15
#define SCSI_MODESENSE6                 0x1A
#define SCSI_STARTSTOPUNIT              0x1B
#define SCSI_MEDIAREMOVAL               0x1E
#define SCSI_READFORMATCAPACITIES       0x23
#define SCSI_READCAPACITY10             0x25
#define SCSI_READ10                     0x28
#define SCSI_WRITE10                    0x2A
#define SCSI_VERIFY10                   0x2F

/***************************************************************************************************************************************//**

    A command block wrapper as used by the mass storage class.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct CBW {
    UINT32  dCBWSignature;
    UINT32  dCBWTag;
    UINT32  dCBWDataTransferLength;
    BYTE    bmCBWFlags;
    BYTE    bCBWLUN;
    BYTE    bCBWCBLength;
    BYTE    CBWCB[16];
} POSTPACKED;

/***************************************************************************************************************************************//**

    A command status wrapper as used by the mass storage class.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct CSW {
    UINT32  dCSWSignature;
    UINT32  dCSWTag;
    UINT32  dCSWDataResidue;
    BYTE    dCSWStatus;
} POSTPACKED;




/*******************************************************************************************************************************************
    VIRTUAL COM (VCOM)
*******************************************************************************************************************************************/
#define CDCSENDCOMMAND      0x0
#define CDCGETRESPONSE      0x1
#define CDCSETLINECODING    0x20
#define CDCGETLINECODING    0x21
#define CDCSETCONTROLLINE   0x22
#define CDCSENDBREAK        0x23

typedef struct LINECODING LINECODING;

/***************************************************************************************************************************************//**

    Represents the line coding information for a CDC ACM device.
    @module     usb

*******************************************************************************************************************************************/
PREPACKED struct LINECODING {
    UINT32  dwDTERate;          /**< Data terminal rate, in bits per second */
    BYTE    bCharFormat;        /**< Stop bits: 0=1 stop bit, 1=1.5 stop bits, 2=2 stop bits */
    BYTE    bParityType;        /**< Parity: 0=none, 1=odd, 2=even, 3=mark, 4=space */
    BYTE    bDataBits;          /**< Data bits (5, 6, 7, 8, or 16) */
} POSTPACKED;

#endif /* USB_H__ */
