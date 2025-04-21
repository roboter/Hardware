/*******************************************************************************************************************************************

    DZX | LPC18xx | EVENT ROUNTER                                                                                         VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the event router.

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
#ifndef MCU_ER_H__
#define MCU_ER_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
typedef struct ERHILOBITFIELD {
    UINT32 WAKEUP0L                :1;
    UINT32 WAKEUP1L                :1;
    UINT32 WAKEUP2L                :1;
    UINT32 WAKEUP3L                :1;
    UINT32 ATIMERL                 :1;
    UINT32 RTCL                    :1;
    UINT32 BODL                    :1;
    UINT32 WWDTL                   :1;
    UINT32 ETHL                    :1;
    UINT32 USB0L                   :1;
    UINT32 USB1L                   :1;
    UINT32                         :1;
    UINT32 CANL                    :1;
    UINT32 TIM2L                   :1;
    UINT32 TIM6L                   :1;
    UINT32 QEIL                    :1;
    UINT32 TIM14L                  :1;
    UINT32                         :2;
    UINT32 RESETL                  :1;
    UINT32                         :12;
} ERHILOBITFIELD;

typedef struct EREDGEBITFIELD {
    UINT32 WAKEUP0E                :1;
    UINT32 WAKEUP1E                :1;
    UINT32 WAKEUP2E                :1;
    UINT32 WAKEUP3E                :1;
    UINT32 ATIMERE                 :1;
    UINT32 RTCE                    :1;
    UINT32 BODE                    :1;
    UINT32 WWDTE                   :1;
    UINT32 ETHE                    :1;
    UINT32 USB0E                   :1;
    UINT32 USB1E                   :1;
    UINT32                         :1;
    UINT32 CANE                    :1;
    UINT32 TIM2E                   :1;
    UINT32 TIM6E                   :1;
    UINT32 QEIE                    :1;
    UINT32 TIM14E                  :1;
    UINT32                         :2;
    UINT32 RESETE                  :1;
    UINT32                         :12;
} EREDGEBITFIELD;

typedef struct ERCLRENBITFIELD {
    UINT32 WAKEUP0CLREN            :1;
    UINT32 WAKEUP1CLREN            :1;
    UINT32 WAKEUP2CLREN            :1;
    UINT32 WAKEUP3CLREN            :1;
    UINT32 ATIMERCLREN             :1;
    UINT32 RTCCLREN                :1;
    UINT32 BODCLREN                :1;
    UINT32 WWDTCLREN               :1;
    UINT32 ETHCLREN                :1;
    UINT32 USB0CLREN               :1;
    UINT32 USB1CLREN               :1;
    UINT32                         :1;
    UINT32 CANCLREN                :1;
    UINT32 TIM2CLREN               :1;
    UINT32 TIM6CLREN               :1;
    UINT32 QEICLREN                :1;
    UINT32 TIM14CLREN              :1;
    UINT32                         :2;
    UINT32 RESETCLREN              :1;
    UINT32                         :12;
} ERCLRENBITFIELD;

typedef struct ERSETENBITFIELD {
    UINT32 WAKEUP0SETEN            :1;
    UINT32 WAKEUP1SETEN            :1;
    UINT32 WAKEUP2SETEN            :1;
    UINT32 WAKEUP3SETEN            :1;
    UINT32 ATIMERSETEN             :1;
    UINT32 RTCSETEN                :1;
    UINT32 BODSETEN                :1;
    UINT32 WWDTSETEN               :1;
    UINT32 ETHSETEN                :1;
    UINT32 USB0SETEN               :1;
    UINT32 USB1SETEN               :1;
    UINT32                         :1;
    UINT32 CANSETEN                :1;
    UINT32 TIM2SETEN               :1;
    UINT32 TIM6SETEN               :1;
    UINT32 QEISETEN                :1;
    UINT32 TIM14SETEN              :1;
    UINT32                         :2;
    UINT32 RESETSETEN              :1;
    UINT32                         :12;
} ERSETENBITFIELD;

typedef struct ERSTATUSBITFIELD {
    UINT32 WAKEUP0ST               :1;
    UINT32 WAKEUP1ST               :1;
    UINT32 WAKEUP2ST               :1;
    UINT32 WAKEUP3ST               :1;
    UINT32 ATIMERST                :1;
    UINT32 RTCST                   :1;
    UINT32 BODST                   :1;
    UINT32 WWDTST                  :1;
    UINT32 ETHST                   :1;
    UINT32 USB0ST                  :1;
    UINT32 USB1ST                  :1;
    UINT32                         :1;
    UINT32 CANST                   :1;
    UINT32 TIM2ST                  :1;
    UINT32 TIM6ST                  :1;
    UINT32 QEIST                   :1;
    UINT32 TIM14ST                 :1;
    UINT32                         :2;
    UINT32 RESETST                 :1;
    UINT32                         :12;
} ERSTATUSBITFIELD;

typedef struct ERENABLEBITFIELD {
    UINT32 WAKEUP0EN               :1;
    UINT32 WAKEUP1EN               :1;
    UINT32 WAKEUP2EN               :1;
    UINT32 WAKEUP3EN               :1;
    UINT32 ATIMEREN                :1;
    UINT32 RTCEN                   :1;
    UINT32 BODEN                   :1;
    UINT32 WWDTEN                  :1;
    UINT32 ETHEN                   :1;
    UINT32 USB0EN                  :1;
    UINT32 USB1EN                  :1;
    UINT32                         :1;
    UINT32 CANEN                   :1;
    UINT32 TIM2EN                  :1;
    UINT32 TIM6EN                  :1;
    UINT32 QEIEN                   :1;
    UINT32 TIM14EN                 :1;
    UINT32                         :2;
    UINT32 RESETEN                 :1;
    UINT32                         :12;
} ERENABLEBITFIELD;

typedef struct ERCLRSTATBITFIELD {
    UINT32 WAKEUP0CLRST            :1;
    UINT32 WAKEUP1CLRST            :1;
    UINT32 WAKEUP2CLRST            :1;
    UINT32 WAKEUP3CLRST            :1;
    UINT32 ATIMERCLRST             :1;
    UINT32 RTCCLRST                :1;
    UINT32 BODCLRST                :1;
    UINT32 WWDTCLRST               :1;
    UINT32 ETHCLRST                :1;
    UINT32 USB0CLRST               :1;
    UINT32 USB1CLRST               :1;
    UINT32                         :1;
    UINT32 CANCLRST                :1;
    UINT32 TIM2CLRST               :1;
    UINT32 TIM6CLRST               :1;
    UINT32 QEICLRST                :1;
    UINT32 TIM14CLRST              :1;
    UINT32                         :2;
    UINT32 RESETCLRST              :1;
    UINT32                         :12;
} ERCLRSTATBITFIELD;

typedef struct ERSETSTATBITFIELD {
    UINT32 WAKEUP0SETST            :1;
    UINT32 WAKEUP1SETST            :1;
    UINT32 WAKEUP2SETST            :1;
    UINT32 WAKEUP3SETST            :1;
    UINT32 ATIMERSETST             :1;
    UINT32 RTCSETST                :1;
    UINT32 BODSETST                :1;
    UINT32 WWDTSETST               :1;
    UINT32 ETHSETST                :1;
    UINT32 USB0SETST               :1;
    UINT32 USB1SETST               :1;
    UINT32                         :1;
    UINT32 CANSETST                :1;
    UINT32 TIM2SETST               :1;
    UINT32 TIM6SETST               :1;
    UINT32 QEISETST                :1;
    UINT32 TIM14SETST              :1;
    UINT32                         :2;
    UINT32 RESETSETST              :1;
    UINT32                         :12;
} ERSETSTATBITFIELD;

#define REG_ERCLREN                               REG_32(0x40044FD8)
#define REGBITS_ERCLREN                           REGBITS_32(0x40044FD8, ERCLRENBITFIELD)
#define REG_ERCLRSTAT                             REG_32(0x40044FE8)
#define REGBITS_ERCLRSTAT                         REGBITS_32(0x40044FE8, ERCLRSTATBITFIELD)
#define REG_EREDGE                                REG_32(0x40044004)
#define REGBITS_EREDGE                            REGBITS_32(0x40044004, EREDGEBITFIELD)
#define REG_ERENABLE                              REG_32(0x40044FE4)
#define REGBITS_ERENABLE                          REGBITS_32(0x40044FE4, ERENABLEBITFIELD)
#define REG_ERHILO                                REG_32(0x40044000)
#define REGBITS_ERHILO                            REGBITS_32(0x40044000, ERHILOBITFIELD)
#define REG_ERSETEN                               REG_32(0x40044FDC)
#define REGBITS_ERSETEN                           REGBITS_32(0x40044FDC, ERSETENBITFIELD)
#define REG_ERSETSTAT                             REG_32(0x40044FEC)
#define REGBITS_ERSETSTAT                         REGBITS_32(0x40044FEC, ERSETSTATBITFIELD)
#define REG_ERSTATUS                              REG_32(0x40044FE0)
#define REGBITS_ERSTATUS                          REGBITS_32(0x40044FE0, ERSTATUSBITFIELD)

#endif /* MCU_ER_H__ */
