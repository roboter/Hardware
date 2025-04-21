/*******************************************************************************************************************************************

    DZX | LPC18xx | SCU                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the system control unit (SCU).

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
#ifndef MCU_SCU_H__
#define MCU_SCU_H__

#include "Kernel/kernel.h"

typedef struct SFSP00BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP00BITFIELD;
typedef struct SFSP01BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP01BITFIELD;
typedef struct SFSP10BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP10BITFIELD;
typedef struct SFSP11BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP11BITFIELD;
typedef struct SFSP12BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP12BITFIELD;
typedef struct SFSP13BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP13BITFIELD;
typedef struct SFSP14BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP14BITFIELD;
typedef struct SFSP15BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP15BITFIELD;
typedef struct SFSP16BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP16BITFIELD;
typedef struct SFSP17BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP17BITFIELD;
typedef struct SFSP18BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP18BITFIELD;
typedef struct SFSP19BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP19BITFIELD;
typedef struct SFSP110BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP110BITFIELD;
typedef struct SFSP111BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP111BITFIELD;
typedef struct SFSP112BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP112BITFIELD;
typedef struct SFSP113BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP113BITFIELD;
typedef struct SFSP114BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP114BITFIELD;
typedef struct SFSP115BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP115BITFIELD;
typedef struct SFSP116BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP116BITFIELD;
typedef struct SFSP117BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP117BITFIELD;
typedef struct SFSP118BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP118BITFIELD;
typedef struct SFSP119BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP119BITFIELD;
typedef struct SFSP120BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP120BITFIELD;
typedef struct SFSP20BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP20BITFIELD;
typedef struct SFSP21BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP21BITFIELD;
typedef struct SFSP22BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP22BITFIELD;
typedef struct SFSP23BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP23BITFIELD;
typedef struct SFSP24BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP24BITFIELD;
typedef struct SFSP25BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP25BITFIELD;
typedef struct SFSP26BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP26BITFIELD;
typedef struct SFSP27BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP27BITFIELD;
typedef struct SFSP28BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP28BITFIELD;
typedef struct SFSP29BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP29BITFIELD;
typedef struct SFSP210BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP210BITFIELD;
typedef struct SFSP211BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP211BITFIELD;
typedef struct SFSP212BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP212BITFIELD;
typedef struct SFSP213BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP213BITFIELD;
typedef struct SFSP30BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP30BITFIELD;
typedef struct SFSP31BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP31BITFIELD;
typedef struct SFSP32BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP32BITFIELD;
typedef struct SFSP33BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP33BITFIELD;
typedef struct SFSP34BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP34BITFIELD;
typedef struct SFSP35BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP35BITFIELD;
typedef struct SFSP36BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP36BITFIELD;
typedef struct SFSP37BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP37BITFIELD;
typedef struct SFSP38BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP38BITFIELD;
typedef struct SFSP40BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP40BITFIELD;
typedef struct SFSP41BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP41BITFIELD;
typedef struct SFSP42BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP42BITFIELD;
typedef struct SFSP43BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP43BITFIELD;
typedef struct SFSP44BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP44BITFIELD;
typedef struct SFSP45BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP45BITFIELD;
typedef struct SFSP46BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP46BITFIELD;
typedef struct SFSP47BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP47BITFIELD;
typedef struct SFSP48BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP48BITFIELD;
typedef struct SFSP49BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP49BITFIELD;
typedef struct SFSP410BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP410BITFIELD;
typedef struct SFSP50BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP50BITFIELD;
typedef struct SFSP51BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP51BITFIELD;
typedef struct SFSP52BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP52BITFIELD;
typedef struct SFSP53BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP53BITFIELD;
typedef struct SFSP54BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP54BITFIELD;
typedef struct SFSP55BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP55BITFIELD;
typedef struct SFSP56BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP56BITFIELD;
typedef struct SFSP57BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP57BITFIELD;
typedef struct SFSP60BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP60BITFIELD;
typedef struct SFSP61BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP61BITFIELD;
typedef struct SFSP62BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP62BITFIELD;
typedef struct SFSP63BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP63BITFIELD;
typedef struct SFSP64BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP64BITFIELD;
typedef struct SFSP65BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP65BITFIELD;
typedef struct SFSP66BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP66BITFIELD;
typedef struct SFSP67BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP67BITFIELD;
typedef struct SFSP68BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP68BITFIELD;
typedef struct SFSP69BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP69BITFIELD;
typedef struct SFSP610BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP610BITFIELD;
typedef struct SFSP611BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP611BITFIELD;
typedef struct SFSP612BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP612BITFIELD;
typedef struct SFSP70BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP70BITFIELD;
typedef struct SFSP71BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP71BITFIELD;
typedef struct SFSP72BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP72BITFIELD;
typedef struct SFSP73BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP73BITFIELD;
typedef struct SFSP74BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP74BITFIELD;
typedef struct SFSP75BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP75BITFIELD;
typedef struct SFSP76BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP76BITFIELD;
typedef struct SFSP77BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP77BITFIELD;
typedef struct SFSP80BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP80BITFIELD;
typedef struct SFSP81BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP81BITFIELD;
typedef struct SFSP82BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSP82BITFIELD;
typedef struct SFSP83BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP83BITFIELD;
typedef struct SFSP84BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP84BITFIELD;
typedef struct SFSP85BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP85BITFIELD;
typedef struct SFSP86BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP86BITFIELD;
typedef struct SFSP87BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP87BITFIELD;
typedef struct SFSP88BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP88BITFIELD;
typedef struct SFSP90BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP90BITFIELD;
typedef struct SFSP91BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP91BITFIELD;
typedef struct SFSP92BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP92BITFIELD;
typedef struct SFSP93BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP93BITFIELD;
typedef struct SFSP94BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP94BITFIELD;
typedef struct SFSP95BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP95BITFIELD;
typedef struct SFSP96BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSP96BITFIELD;
typedef struct SFSPA0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPA0BITFIELD;
typedef struct SFSPA1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSPA1BITFIELD;
typedef struct SFSPA2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSPA2BITFIELD;
typedef struct SFSPA3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32                         :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32 EHD                     :2;
    UINT32                         :22;
} SFSPA3BITFIELD;
typedef struct SFSPA4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPA4BITFIELD;
typedef struct SFSPB0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB0BITFIELD;
typedef struct SFSPB1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB1BITFIELD;
typedef struct SFSPB2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB2BITFIELD;
typedef struct SFSPB3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB3BITFIELD;
typedef struct SFSPB4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB4BITFIELD;
typedef struct SFSPB5BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB5BITFIELD;
typedef struct SFSPB6BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPB6BITFIELD;
typedef struct SFSPC0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC0BITFIELD;
typedef struct SFSPC1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC1BITFIELD;
typedef struct SFSPC2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC2BITFIELD;
typedef struct SFSPC3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC3BITFIELD;
typedef struct SFSPC4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC4BITFIELD;
typedef struct SFSPC5BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC5BITFIELD;
typedef struct SFSPC6BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC6BITFIELD;
typedef struct SFSPC7BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC7BITFIELD;
typedef struct SFSPC8BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC8BITFIELD;
typedef struct SFSPC9BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC9BITFIELD;
typedef struct SFSPC10BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC10BITFIELD;
typedef struct SFSPC11BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC11BITFIELD;
typedef struct SFSPC12BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC12BITFIELD;
typedef struct SFSPC13BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC13BITFIELD;
typedef struct SFSPC14BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPC14BITFIELD;
typedef struct SFSPD0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD0BITFIELD;
typedef struct SFSPD1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD1BITFIELD;
typedef struct SFSPD2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD2BITFIELD;
typedef struct SFSPD3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD3BITFIELD;
typedef struct SFSPD4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD4BITFIELD;
typedef struct SFSPD5BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD5BITFIELD;
typedef struct SFSPD6BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD6BITFIELD;
typedef struct SFSPD7BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD7BITFIELD;
typedef struct SFSPD8BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD8BITFIELD;
typedef struct SFSPD9BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD9BITFIELD;
typedef struct SFSPD10BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD10BITFIELD;
typedef struct SFSPD11BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD11BITFIELD;
typedef struct SFSPD12BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD12BITFIELD;
typedef struct SFSPD13BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD13BITFIELD;
typedef struct SFSPD14BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD14BITFIELD;
typedef struct SFSPD15BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD15BITFIELD;
typedef struct SFSPD16BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPD16BITFIELD;
typedef struct SFSPE0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE0BITFIELD;
typedef struct SFSPE1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE1BITFIELD;
typedef struct SFSPE2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE2BITFIELD;
typedef struct SFSPE3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE3BITFIELD;
typedef struct SFSPE4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE4BITFIELD;
typedef struct SFSPE5BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE5BITFIELD;
typedef struct SFSPE6BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE6BITFIELD;
typedef struct SFSPE7BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE7BITFIELD;
typedef struct SFSPE8BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE8BITFIELD;
typedef struct SFSPE9BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE9BITFIELD;
typedef struct SFSPE10BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE10BITFIELD;
typedef struct SFSPE11BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE11BITFIELD;
typedef struct SFSPE12BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE12BITFIELD;
typedef struct SFSPE13BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE13BITFIELD;
typedef struct SFSPE14BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE14BITFIELD;
typedef struct SFSPE15BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPE15BITFIELD;
typedef struct SFSPF0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF0BITFIELD;
typedef struct SFSPF1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF1BITFIELD;
typedef struct SFSPF2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF2BITFIELD;
typedef struct SFSPF3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF3BITFIELD;
typedef struct SFSPF4BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF4BITFIELD;
typedef struct SFSPF5BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF5BITFIELD;
typedef struct SFSPF6BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF6BITFIELD;
typedef struct SFSPF7BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF7BITFIELD;
typedef struct SFSPF8BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF8BITFIELD;
typedef struct SFSPF9BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF9BITFIELD;
typedef struct SFSPF10BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF10BITFIELD;
typedef struct SFSPF11BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSPF11BITFIELD;
typedef struct SFSCLK0BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSCLK0BITFIELD;
typedef struct SFSCLK1BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSCLK1BITFIELD;
typedef struct SFSCLK2BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSCLK2BITFIELD;
typedef struct SFSCLK3BITFIELD
{
    UINT32 MODE                    :3;
    UINT32 EPD                     :1;
    UINT32 EPUN                    :1;
    UINT32 EHS                     :1;
    UINT32 EZI                     :1;
    UINT32 ZIF                     :1;
    UINT32                         :24;
} SFSCLK3BITFIELD;
typedef struct SFSUSBBITFIELD
{
    UINT32 USBAIM                  :1;
    UINT32 USBESEA                 :1;
    UINT32 USBEPD                  :1;
    UINT32                         :1;
    UINT32 USBEPWR                 :1;
    UINT32 USBVBUS                 :1;
    UINT32                         :26;
} SFSUSBBITFIELD;
typedef struct SFSI2C0BITFIELD
{
    UINT32 SCLEFP                  :1;
    UINT32                         :1;
    UINT32 SCLEHD                  :1;
    UINT32 SCLEZI                  :1;
    UINT32                         :3;
    UINT32 SCLZIF                  :1;
    UINT32 SDAEFP                  :1;
    UINT32                         :1;
    UINT32 SDAEHD                  :1;
    UINT32 SDAEZI                  :1;
    UINT32                         :3;
    UINT32 SDAZIF                  :1;
    UINT32                         :16;
} SFSI2C0BITFIELD;


#define REG_SFSCLK0                               REG_32(0x40086C00)
#define REGBITS_SFSCLK0                           REGBITS_32(0x40086C00, SFSCLK0BITFIELD)
#define REG_SFSCLK1                               REG_32(0x40086C04)
#define REGBITS_SFSCLK1                           REGBITS_32(0x40086C04, SFSCLK1BITFIELD)
#define REG_SFSCLK2                               REG_32(0x40086C08)
#define REGBITS_SFSCLK2                           REGBITS_32(0x40086C08, SFSCLK2BITFIELD)
#define REG_SFSCLK3                               REG_32(0x40086C0C)
#define REGBITS_SFSCLK3                           REGBITS_32(0x40086C0C, SFSCLK3BITFIELD)
#define REG_SFSI2C0                               REG_32(0x40086C84)
#define REGBITS_SFSI2C0                           REGBITS_32(0x40086C84, SFSI2C0BITFIELD)
#define REG_SFSP00                                REG_32(0x40086000)
#define REGBITS_SFSP00                            REGBITS_32(0x40086000, SFSP00BITFIELD)
#define REG_SFSP01                                REG_32(0x40086004)
#define REGBITS_SFSP01                            REGBITS_32(0x40086004, SFSP01BITFIELD)
#define REG_SFSP10                                REG_32(0x40086080)
#define REGBITS_SFSP10                            REGBITS_32(0x40086080, SFSP10BITFIELD)
#define REG_SFSP11                                REG_32(0x40086084)
#define REGBITS_SFSP11                            REGBITS_32(0x40086084, SFSP11BITFIELD)
#define REG_SFSP110                               REG_32(0x400860A8)
#define REGBITS_SFSP110                           REGBITS_32(0x400860A8, SFSP110BITFIELD)
#define REG_SFSP111                               REG_32(0x400860AC)
#define REGBITS_SFSP111                           REGBITS_32(0x400860AC, SFSP111BITFIELD)
#define REG_SFSP112                               REG_32(0x400860B0)
#define REGBITS_SFSP112                           REGBITS_32(0x400860B0, SFSP112BITFIELD)
#define REG_SFSP113                               REG_32(0x400860B4)
#define REGBITS_SFSP113                           REGBITS_32(0x400860B4, SFSP113BITFIELD)
#define REG_SFSP114                               REG_32(0x400860B8)
#define REGBITS_SFSP114                           REGBITS_32(0x400860B8, SFSP114BITFIELD)
#define REG_SFSP115                               REG_32(0x400860BC)
#define REGBITS_SFSP115                           REGBITS_32(0x400860BC, SFSP115BITFIELD)
#define REG_SFSP116                               REG_32(0x400860C0)
#define REGBITS_SFSP116                           REGBITS_32(0x400860C0, SFSP116BITFIELD)
#define REG_SFSP117                               REG_32(0x400860C4)
#define REGBITS_SFSP117                           REGBITS_32(0x400860C4, SFSP117BITFIELD)
#define REG_SFSP118                               REG_32(0x400860C8)
#define REGBITS_SFSP118                           REGBITS_32(0x400860C8, SFSP118BITFIELD)
#define REG_SFSP119                               REG_32(0x400860CC)
#define REGBITS_SFSP119                           REGBITS_32(0x400860CC, SFSP119BITFIELD)
#define REG_SFSP12                                REG_32(0x40086088)
#define REGBITS_SFSP12                            REGBITS_32(0x40086088, SFSP12BITFIELD)
#define REG_SFSP120                               REG_32(0x400860D0)
#define REGBITS_SFSP120                           REGBITS_32(0x400860D0, SFSP120BITFIELD)
#define REG_SFSP13                                REG_32(0x4008608C)
#define REGBITS_SFSP13                            REGBITS_32(0x4008608C, SFSP13BITFIELD)
#define REG_SFSP14                                REG_32(0x40086090)
#define REGBITS_SFSP14                            REGBITS_32(0x40086090, SFSP14BITFIELD)
#define REG_SFSP15                                REG_32(0x40086094)
#define REGBITS_SFSP15                            REGBITS_32(0x40086094, SFSP15BITFIELD)
#define REG_SFSP16                                REG_32(0x40086098)
#define REGBITS_SFSP16                            REGBITS_32(0x40086098, SFSP16BITFIELD)
#define REG_SFSP17                                REG_32(0x4008609C)
#define REGBITS_SFSP17                            REGBITS_32(0x4008609C, SFSP17BITFIELD)
#define REG_SFSP18                                REG_32(0x400860A0)
#define REGBITS_SFSP18                            REGBITS_32(0x400860A0, SFSP18BITFIELD)
#define REG_SFSP19                                REG_32(0x400860A4)
#define REGBITS_SFSP19                            REGBITS_32(0x400860A4, SFSP19BITFIELD)
#define REG_SFSP20                                REG_32(0x40086100)
#define REGBITS_SFSP20                            REGBITS_32(0x40086100, SFSP20BITFIELD)
#define REG_SFSP21                                REG_32(0x40086104)
#define REGBITS_SFSP21                            REGBITS_32(0x40086104, SFSP21BITFIELD)
#define REG_SFSP210                               REG_32(0x40086128)
#define REGBITS_SFSP210                           REGBITS_32(0x40086128, SFSP210BITFIELD)
#define REG_SFSP211                               REG_32(0x4008612C)
#define REGBITS_SFSP211                           REGBITS_32(0x4008612C, SFSP211BITFIELD)
#define REG_SFSP212                               REG_32(0x40086130)
#define REGBITS_SFSP212                           REGBITS_32(0x40086130, SFSP212BITFIELD)
#define REG_SFSP213                               REG_32(0x40086134)
#define REGBITS_SFSP213                           REGBITS_32(0x40086134, SFSP213BITFIELD)
#define REG_SFSP22                                REG_32(0x40086108)
#define REGBITS_SFSP22                            REGBITS_32(0x40086108, SFSP22BITFIELD)
#define REG_SFSP23                                REG_32(0x4008610C)
#define REGBITS_SFSP23                            REGBITS_32(0x4008610C, SFSP23BITFIELD)
#define REG_SFSP24                                REG_32(0x40086110)
#define REGBITS_SFSP24                            REGBITS_32(0x40086110, SFSP24BITFIELD)
#define REG_SFSP25                                REG_32(0x40086114)
#define REGBITS_SFSP25                            REGBITS_32(0x40086114, SFSP25BITFIELD)
#define REG_SFSP26                                REG_32(0x40086118)
#define REGBITS_SFSP26                            REGBITS_32(0x40086118, SFSP26BITFIELD)
#define REG_SFSP27                                REG_32(0x4008611C)
#define REGBITS_SFSP27                            REGBITS_32(0x4008611C, SFSP27BITFIELD)
#define REG_SFSP28                                REG_32(0x40086120)
#define REGBITS_SFSP28                            REGBITS_32(0x40086120, SFSP28BITFIELD)
#define REG_SFSP29                                REG_32(0x40086124)
#define REGBITS_SFSP29                            REGBITS_32(0x40086124, SFSP29BITFIELD)
#define REG_SFSP30                                REG_32(0x40086180)
#define REGBITS_SFSP30                            REGBITS_32(0x40086180, SFSP30BITFIELD)
#define REG_SFSP31                                REG_32(0x40086184)
#define REGBITS_SFSP31                            REGBITS_32(0x40086184, SFSP31BITFIELD)
#define REG_SFSP32                                REG_32(0x40086188)
#define REGBITS_SFSP32                            REGBITS_32(0x40086188, SFSP32BITFIELD)
#define REG_SFSP33                                REG_32(0x4008618C)
#define REGBITS_SFSP33                            REGBITS_32(0x4008618C, SFSP33BITFIELD)
#define REG_SFSP34                                REG_32(0x40086190)
#define REGBITS_SFSP34                            REGBITS_32(0x40086190, SFSP34BITFIELD)
#define REG_SFSP35                                REG_32(0x40086194)
#define REGBITS_SFSP35                            REGBITS_32(0x40086194, SFSP35BITFIELD)
#define REG_SFSP36                                REG_32(0x40086198)
#define REGBITS_SFSP36                            REGBITS_32(0x40086198, SFSP36BITFIELD)
#define REG_SFSP37                                REG_32(0x4008619C)
#define REGBITS_SFSP37                            REGBITS_32(0x4008619C, SFSP37BITFIELD)
#define REG_SFSP38                                REG_32(0x400861A0)
#define REGBITS_SFSP38                            REGBITS_32(0x400861A0, SFSP38BITFIELD)
#define REG_SFSP40                                REG_32(0x40086200)
#define REGBITS_SFSP40                            REGBITS_32(0x40086200, SFSP40BITFIELD)
#define REG_SFSP41                                REG_32(0x40086204)
#define REGBITS_SFSP41                            REGBITS_32(0x40086204, SFSP41BITFIELD)
#define REG_SFSP410                               REG_32(0x40086228)
#define REGBITS_SFSP410                           REGBITS_32(0x40086228, SFSP410BITFIELD)
#define REG_SFSP42                                REG_32(0x40086208)
#define REGBITS_SFSP42                            REGBITS_32(0x40086208, SFSP42BITFIELD)
#define REG_SFSP43                                REG_32(0x4008620C)
#define REGBITS_SFSP43                            REGBITS_32(0x4008620C, SFSP43BITFIELD)
#define REG_SFSP44                                REG_32(0x40086210)
#define REGBITS_SFSP44                            REGBITS_32(0x40086210, SFSP44BITFIELD)
#define REG_SFSP45                                REG_32(0x40086214)
#define REGBITS_SFSP45                            REGBITS_32(0x40086214, SFSP45BITFIELD)
#define REG_SFSP46                                REG_32(0x40086218)
#define REGBITS_SFSP46                            REGBITS_32(0x40086218, SFSP46BITFIELD)
#define REG_SFSP47                                REG_32(0x4008621C)
#define REGBITS_SFSP47                            REGBITS_32(0x4008621C, SFSP47BITFIELD)
#define REG_SFSP48                                REG_32(0x40086220)
#define REGBITS_SFSP48                            REGBITS_32(0x40086220, SFSP48BITFIELD)
#define REG_SFSP49                                REG_32(0x40086224)
#define REGBITS_SFSP49                            REGBITS_32(0x40086224, SFSP49BITFIELD)
#define REG_SFSP50                                REG_32(0x40086280)
#define REGBITS_SFSP50                            REGBITS_32(0x40086280, SFSP50BITFIELD)
#define REG_SFSP51                                REG_32(0x40086284)
#define REGBITS_SFSP51                            REGBITS_32(0x40086284, SFSP51BITFIELD)
#define REG_SFSP52                                REG_32(0x40086288)
#define REGBITS_SFSP52                            REGBITS_32(0x40086288, SFSP52BITFIELD)
#define REG_SFSP53                                REG_32(0x4008628C)
#define REGBITS_SFSP53                            REGBITS_32(0x4008628C, SFSP53BITFIELD)
#define REG_SFSP54                                REG_32(0x40086290)
#define REGBITS_SFSP54                            REGBITS_32(0x40086290, SFSP54BITFIELD)
#define REG_SFSP55                                REG_32(0x40086294)
#define REGBITS_SFSP55                            REGBITS_32(0x40086294, SFSP55BITFIELD)
#define REG_SFSP56                                REG_32(0x40086298)
#define REGBITS_SFSP56                            REGBITS_32(0x40086298, SFSP56BITFIELD)
#define REG_SFSP57                                REG_32(0x4008629C)
#define REGBITS_SFSP57                            REGBITS_32(0x4008629C, SFSP57BITFIELD)
#define REG_SFSP60                                REG_32(0x40086300)
#define REGBITS_SFSP60                            REGBITS_32(0x40086300, SFSP60BITFIELD)
#define REG_SFSP61                                REG_32(0x40086304)
#define REGBITS_SFSP61                            REGBITS_32(0x40086304, SFSP61BITFIELD)
#define REG_SFSP610                               REG_32(0x40086328)
#define REGBITS_SFSP610                           REGBITS_32(0x40086328, SFSP610BITFIELD)
#define REG_SFSP611                               REG_32(0x4008632C)
#define REGBITS_SFSP611                           REGBITS_32(0x4008632C, SFSP611BITFIELD)
#define REG_SFSP612                               REG_32(0x40086330)
#define REGBITS_SFSP612                           REGBITS_32(0x40086330, SFSP612BITFIELD)
#define REG_SFSP62                                REG_32(0x40086308)
#define REGBITS_SFSP62                            REGBITS_32(0x40086308, SFSP62BITFIELD)
#define REG_SFSP63                                REG_32(0x4008630C)
#define REGBITS_SFSP63                            REGBITS_32(0x4008630C, SFSP63BITFIELD)
#define REG_SFSP64                                REG_32(0x40086310)
#define REGBITS_SFSP64                            REGBITS_32(0x40086310, SFSP64BITFIELD)
#define REG_SFSP65                                REG_32(0x40086314)
#define REGBITS_SFSP65                            REGBITS_32(0x40086314, SFSP65BITFIELD)
#define REG_SFSP66                                REG_32(0x40086318)
#define REGBITS_SFSP66                            REGBITS_32(0x40086318, SFSP66BITFIELD)
#define REG_SFSP67                                REG_32(0x4008631C)
#define REGBITS_SFSP67                            REGBITS_32(0x4008631C, SFSP67BITFIELD)
#define REG_SFSP68                                REG_32(0x40086320)
#define REGBITS_SFSP68                            REGBITS_32(0x40086320, SFSP68BITFIELD)
#define REG_SFSP69                                REG_32(0x40086324)
#define REGBITS_SFSP69                            REGBITS_32(0x40086324, SFSP69BITFIELD)
#define REG_SFSP70                                REG_32(0x40086380)
#define REGBITS_SFSP70                            REGBITS_32(0x40086380, SFSP70BITFIELD)
#define REG_SFSP71                                REG_32(0x40086384)
#define REGBITS_SFSP71                            REGBITS_32(0x40086384, SFSP71BITFIELD)
#define REG_SFSP72                                REG_32(0x40086388)
#define REGBITS_SFSP72                            REGBITS_32(0x40086388, SFSP72BITFIELD)
#define REG_SFSP73                                REG_32(0x4008638C)
#define REGBITS_SFSP73                            REGBITS_32(0x4008638C, SFSP73BITFIELD)
#define REG_SFSP74                                REG_32(0x40086390)
#define REGBITS_SFSP74                            REGBITS_32(0x40086390, SFSP74BITFIELD)
#define REG_SFSP75                                REG_32(0x40086394)
#define REGBITS_SFSP75                            REGBITS_32(0x40086394, SFSP75BITFIELD)
#define REG_SFSP76                                REG_32(0x40086398)
#define REGBITS_SFSP76                            REGBITS_32(0x40086398, SFSP76BITFIELD)
#define REG_SFSP77                                REG_32(0x4008639C)
#define REGBITS_SFSP77                            REGBITS_32(0x4008639C, SFSP77BITFIELD)
#define REG_SFSP80                                REG_32(0x40086400)
#define REGBITS_SFSP80                            REGBITS_32(0x40086400, SFSP80BITFIELD)
#define REG_SFSP81                                REG_32(0x40086404)
#define REGBITS_SFSP81                            REGBITS_32(0x40086404, SFSP81BITFIELD)
#define REG_SFSP82                                REG_32(0x40086408)
#define REGBITS_SFSP82                            REGBITS_32(0x40086408, SFSP82BITFIELD)
#define REG_SFSP83                                REG_32(0x4008640C)
#define REGBITS_SFSP83                            REGBITS_32(0x4008640C, SFSP83BITFIELD)
#define REG_SFSP84                                REG_32(0x40086410)
#define REGBITS_SFSP84                            REGBITS_32(0x40086410, SFSP84BITFIELD)
#define REG_SFSP85                                REG_32(0x40086414)
#define REGBITS_SFSP85                            REGBITS_32(0x40086414, SFSP85BITFIELD)
#define REG_SFSP86                                REG_32(0x40086418)
#define REGBITS_SFSP86                            REGBITS_32(0x40086418, SFSP86BITFIELD)
#define REG_SFSP87                                REG_32(0x4008641C)
#define REGBITS_SFSP87                            REGBITS_32(0x4008641C, SFSP87BITFIELD)
#define REG_SFSP88                                REG_32(0x40086420)
#define REGBITS_SFSP88                            REGBITS_32(0x40086420, SFSP88BITFIELD)
#define REG_SFSP90                                REG_32(0x40086480)
#define REGBITS_SFSP90                            REGBITS_32(0x40086480, SFSP90BITFIELD)
#define REG_SFSP91                                REG_32(0x40086484)
#define REGBITS_SFSP91                            REGBITS_32(0x40086484, SFSP91BITFIELD)
#define REG_SFSP92                                REG_32(0x40086488)
#define REGBITS_SFSP92                            REGBITS_32(0x40086488, SFSP92BITFIELD)
#define REG_SFSP93                                REG_32(0x4008648C)
#define REGBITS_SFSP93                            REGBITS_32(0x4008648C, SFSP93BITFIELD)
#define REG_SFSP94                                REG_32(0x40086490)
#define REGBITS_SFSP94                            REGBITS_32(0x40086490, SFSP94BITFIELD)
#define REG_SFSP95                                REG_32(0x40086494)
#define REGBITS_SFSP95                            REGBITS_32(0x40086494, SFSP95BITFIELD)
#define REG_SFSP96                                REG_32(0x40086498)
#define REGBITS_SFSP96                            REGBITS_32(0x40086498, SFSP96BITFIELD)
#define REG_SFSPA0                                REG_32(0x40086500)
#define REGBITS_SFSPA0                            REGBITS_32(0x40086500, SFSPA0BITFIELD)
#define REG_SFSPA1                                REG_32(0x40086504)
#define REGBITS_SFSPA1                            REGBITS_32(0x40086504, SFSPA1BITFIELD)
#define REG_SFSPA2                                REG_32(0x40086508)
#define REGBITS_SFSPA2                            REGBITS_32(0x40086508, SFSPA2BITFIELD)
#define REG_SFSPA3                                REG_32(0x4008650C)
#define REGBITS_SFSPA3                            REGBITS_32(0x4008650C, SFSPA3BITFIELD)
#define REG_SFSPA4                                REG_32(0x40086510)
#define REGBITS_SFSPA4                            REGBITS_32(0x40086510, SFSPA4BITFIELD)
#define REG_SFSPB0                                REG_32(0x40086580)
#define REGBITS_SFSPB0                            REGBITS_32(0x40086580, SFSPB0BITFIELD)
#define REG_SFSPB1                                REG_32(0x40086584)
#define REGBITS_SFSPB1                            REGBITS_32(0x40086584, SFSPB1BITFIELD)
#define REG_SFSPB2                                REG_32(0x40086588)
#define REGBITS_SFSPB2                            REGBITS_32(0x40086588, SFSPB2BITFIELD)
#define REG_SFSPB3                                REG_32(0x4008658C)
#define REGBITS_SFSPB3                            REGBITS_32(0x4008658C, SFSPB3BITFIELD)
#define REG_SFSPB4                                REG_32(0x40086590)
#define REGBITS_SFSPB4                            REGBITS_32(0x40086590, SFSPB4BITFIELD)
#define REG_SFSPB5                                REG_32(0x40086594)
#define REGBITS_SFSPB5                            REGBITS_32(0x40086594, SFSPB5BITFIELD)
#define REG_SFSPB6                                REG_32(0x40086598)
#define REGBITS_SFSPB6                            REGBITS_32(0x40086598, SFSPB6BITFIELD)
#define REG_SFSPC0                                REG_32(0x40086600)
#define REGBITS_SFSPC0                            REGBITS_32(0x40086600, SFSPC0BITFIELD)
#define REG_SFSPC1                                REG_32(0x40086604)
#define REGBITS_SFSPC1                            REGBITS_32(0x40086604, SFSPC1BITFIELD)
#define REG_SFSPC10                               REG_32(0x40086628)
#define REGBITS_SFSPC10                           REGBITS_32(0x40086628, SFSPC10BITFIELD)
#define REG_SFSPC11                               REG_32(0x4008662C)
#define REGBITS_SFSPC11                           REGBITS_32(0x4008662C, SFSPC11BITFIELD)
#define REG_SFSPC12                               REG_32(0x40086630)
#define REGBITS_SFSPC12                           REGBITS_32(0x40086630, SFSPC12BITFIELD)
#define REG_SFSPC13                               REG_32(0x40086634)
#define REGBITS_SFSPC13                           REGBITS_32(0x40086634, SFSPC13BITFIELD)
#define REG_SFSPC14                               REG_32(0x40086638)
#define REGBITS_SFSPC14                           REGBITS_32(0x40086638, SFSPC14BITFIELD)
#define REG_SFSPC2                                REG_32(0x40086608)
#define REGBITS_SFSPC2                            REGBITS_32(0x40086608, SFSPC2BITFIELD)
#define REG_SFSPC3                                REG_32(0x4008660C)
#define REGBITS_SFSPC3                            REGBITS_32(0x4008660C, SFSPC3BITFIELD)
#define REG_SFSPC4                                REG_32(0x40086610)
#define REGBITS_SFSPC4                            REGBITS_32(0x40086610, SFSPC4BITFIELD)
#define REG_SFSPC5                                REG_32(0x40086614)
#define REGBITS_SFSPC5                            REGBITS_32(0x40086614, SFSPC5BITFIELD)
#define REG_SFSPC6                                REG_32(0x40086618)
#define REGBITS_SFSPC6                            REGBITS_32(0x40086618, SFSPC6BITFIELD)
#define REG_SFSPC7                                REG_32(0x4008661C)
#define REGBITS_SFSPC7                            REGBITS_32(0x4008661C, SFSPC7BITFIELD)
#define REG_SFSPC8                                REG_32(0x40086620)
#define REGBITS_SFSPC8                            REGBITS_32(0x40086620, SFSPC8BITFIELD)
#define REG_SFSPC9                                REG_32(0x40086624)
#define REGBITS_SFSPC9                            REGBITS_32(0x40086624, SFSPC9BITFIELD)
#define REG_SFSPD0                                REG_32(0x40086680)
#define REGBITS_SFSPD0                            REGBITS_32(0x40086680, SFSPD0BITFIELD)
#define REG_SFSPD1                                REG_32(0x40086684)
#define REGBITS_SFSPD1                            REGBITS_32(0x40086684, SFSPD1BITFIELD)
#define REG_SFSPD10                               REG_32(0x400866A8)
#define REGBITS_SFSPD10                           REGBITS_32(0x400866A8, SFSPD10BITFIELD)
#define REG_SFSPD11                               REG_32(0x400866AC)
#define REGBITS_SFSPD11                           REGBITS_32(0x400866AC, SFSPD11BITFIELD)
#define REG_SFSPD12                               REG_32(0x400866B0)
#define REGBITS_SFSPD12                           REGBITS_32(0x400866B0, SFSPD12BITFIELD)
#define REG_SFSPD13                               REG_32(0x400866B4)
#define REGBITS_SFSPD13                           REGBITS_32(0x400866B4, SFSPD13BITFIELD)
#define REG_SFSPD14                               REG_32(0x400866B8)
#define REGBITS_SFSPD14                           REGBITS_32(0x400866B8, SFSPD14BITFIELD)
#define REG_SFSPD15                               REG_32(0x400866BC)
#define REGBITS_SFSPD15                           REGBITS_32(0x400866BC, SFSPD15BITFIELD)
#define REG_SFSPD16                               REG_32(0x400866C0)
#define REGBITS_SFSPD16                           REGBITS_32(0x400866C0, SFSPD16BITFIELD)
#define REG_SFSPD2                                REG_32(0x40086688)
#define REGBITS_SFSPD2                            REGBITS_32(0x40086688, SFSPD2BITFIELD)
#define REG_SFSPD3                                REG_32(0x4008668C)
#define REGBITS_SFSPD3                            REGBITS_32(0x4008668C, SFSPD3BITFIELD)
#define REG_SFSPD4                                REG_32(0x40086690)
#define REGBITS_SFSPD4                            REGBITS_32(0x40086690, SFSPD4BITFIELD)
#define REG_SFSPD5                                REG_32(0x40086694)
#define REGBITS_SFSPD5                            REGBITS_32(0x40086694, SFSPD5BITFIELD)
#define REG_SFSPD6                                REG_32(0x40086698)
#define REGBITS_SFSPD6                            REGBITS_32(0x40086698, SFSPD6BITFIELD)
#define REG_SFSPD7                                REG_32(0x4008669C)
#define REGBITS_SFSPD7                            REGBITS_32(0x4008669C, SFSPD7BITFIELD)
#define REG_SFSPD8                                REG_32(0x400866A0)
#define REGBITS_SFSPD8                            REGBITS_32(0x400866A0, SFSPD8BITFIELD)
#define REG_SFSPD9                                REG_32(0x400866A4)
#define REGBITS_SFSPD9                            REGBITS_32(0x400866A4, SFSPD9BITFIELD)
#define REG_SFSPE0                                REG_32(0x40086700)
#define REGBITS_SFSPE0                            REGBITS_32(0x40086700, SFSPE0BITFIELD)
#define REG_SFSPE1                                REG_32(0x40086704)
#define REGBITS_SFSPE1                            REGBITS_32(0x40086704, SFSPE1BITFIELD)
#define REG_SFSPE10                               REG_32(0x40086728)
#define REGBITS_SFSPE10                           REGBITS_32(0x40086728, SFSPE10BITFIELD)
#define REG_SFSPE11                               REG_32(0x4008672C)
#define REGBITS_SFSPE11                           REGBITS_32(0x4008672C, SFSPE11BITFIELD)
#define REG_SFSPE12                               REG_32(0x40086730)
#define REGBITS_SFSPE12                           REGBITS_32(0x40086730, SFSPE12BITFIELD)
#define REG_SFSPE13                               REG_32(0x40086734)
#define REGBITS_SFSPE13                           REGBITS_32(0x40086734, SFSPE13BITFIELD)
#define REG_SFSPE14                               REG_32(0x40086738)
#define REGBITS_SFSPE14                           REGBITS_32(0x40086738, SFSPE14BITFIELD)
#define REG_SFSPE15                               REG_32(0x4008673C)
#define REGBITS_SFSPE15                           REGBITS_32(0x4008673C, SFSPE15BITFIELD)
#define REG_SFSPE2                                REG_32(0x40086708)
#define REGBITS_SFSPE2                            REGBITS_32(0x40086708, SFSPE2BITFIELD)
#define REG_SFSPE3                                REG_32(0x4008670C)
#define REGBITS_SFSPE3                            REGBITS_32(0x4008670C, SFSPE3BITFIELD)
#define REG_SFSPE4                                REG_32(0x40086710)
#define REGBITS_SFSPE4                            REGBITS_32(0x40086710, SFSPE4BITFIELD)
#define REG_SFSPE5                                REG_32(0x40086714)
#define REGBITS_SFSPE5                            REGBITS_32(0x40086714, SFSPE5BITFIELD)
#define REG_SFSPE6                                REG_32(0x40086718)
#define REGBITS_SFSPE6                            REGBITS_32(0x40086718, SFSPE6BITFIELD)
#define REG_SFSPE7                                REG_32(0x4008671C)
#define REGBITS_SFSPE7                            REGBITS_32(0x4008671C, SFSPE7BITFIELD)
#define REG_SFSPE8                                REG_32(0x40086720)
#define REGBITS_SFSPE8                            REGBITS_32(0x40086720, SFSPE8BITFIELD)
#define REG_SFSPE9                                REG_32(0x40086724)
#define REGBITS_SFSPE9                            REGBITS_32(0x40086724, SFSPE9BITFIELD)
#define REG_SFSPF0                                REG_32(0x40086780)
#define REGBITS_SFSPF0                            REGBITS_32(0x40086780, SFSPF0BITFIELD)
#define REG_SFSPF1                                REG_32(0x40086784)
#define REGBITS_SFSPF1                            REGBITS_32(0x40086784, SFSPF1BITFIELD)
#define REG_SFSPF10                               REG_32(0x400867A8)
#define REGBITS_SFSPF10                           REGBITS_32(0x400867A8, SFSPF10BITFIELD)
#define REG_SFSPF11                               REG_32(0x400867AC)
#define REGBITS_SFSPF11                           REGBITS_32(0x400867AC, SFSPF11BITFIELD)
#define REG_SFSPF2                                REG_32(0x40086788)
#define REGBITS_SFSPF2                            REGBITS_32(0x40086788, SFSPF2BITFIELD)
#define REG_SFSPF3                                REG_32(0x4008678C)
#define REGBITS_SFSPF3                            REGBITS_32(0x4008678C, SFSPF3BITFIELD)
#define REG_SFSPF4                                REG_32(0x40086790)
#define REGBITS_SFSPF4                            REGBITS_32(0x40086790, SFSPF4BITFIELD)
#define REG_SFSPF5                                REG_32(0x40086794)
#define REGBITS_SFSPF5                            REGBITS_32(0x40086794, SFSPF5BITFIELD)
#define REG_SFSPF6                                REG_32(0x40086798)
#define REGBITS_SFSPF6                            REGBITS_32(0x40086798, SFSPF6BITFIELD)
#define REG_SFSPF7                                REG_32(0x4008679C)
#define REGBITS_SFSPF7                            REGBITS_32(0x4008679C, SFSPF7BITFIELD)
#define REG_SFSPF8                                REG_32(0x400867A0)
#define REGBITS_SFSPF8                            REGBITS_32(0x400867A0, SFSPF8BITFIELD)
#define REG_SFSPF9                                REG_32(0x400867A4)
#define REGBITS_SFSPF9                            REGBITS_32(0x400867A4, SFSPF9BITFIELD)
#define REG_SFSUSB                                REG_32(0x40086C80)
#define REGBITS_SFSUSB                            REGBITS_32(0x40086C80, SFSUSBBITFIELD)

#endif /* MCU_SCU_H__ */
