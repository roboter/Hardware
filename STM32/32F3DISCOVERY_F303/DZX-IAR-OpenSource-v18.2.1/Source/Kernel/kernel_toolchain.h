/*******************************************************************************************************************************************

    DZX | KERNEL | TOOLCHAIN SUPPORT                                                                                      VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides common attributes and definitions for toolchain specific functionality.

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
#ifndef KERNEL_TOOLCHAIN_H__
#define KERNEL_TOOLCHAIN_H__

#include "kernel_port.h"

#ifndef UNUSED
    #define UNUSED(x)               (void)(x)
#endif

/*******************************************************************************************************************************************
    ATTRIBUTES
*******************************************************************************************************************************************/

/* IAR */
#if defined(__ICCARM__)

#if (CFG_INLINING)
    #define INLINE inline
#else
	#define INLINE
#endif

#define PREPACKED                   __packed
#define POSTPACKED
#define PRAGMA_ALIGN_4096           _Pragma("data_alignment=4096")
#define PRAGMA_ALIGN_2048           _Pragma("data_alignment=2048")
#define PRAGMA_ALIGN_1024           _Pragma("data_alignment=1024")
#define PRAGMA_ALIGN_512            _Pragma("data_alignment=512")
#define PRAGMA_ALIGN_256            _Pragma("data_alignment=256")
#define PRAGMA_ALIGN_128            _Pragma("data_alignment=128")
#define PRAGMA_ALIGN_64             _Pragma("data_alignment=64")
#define PRAGMA_ALIGN_48             _Pragma("data_alignment=48")
#define PRAGMA_ALIGN_32             _Pragma("data_alignment=32")
#define PRAGMA_ALIGN_16             _Pragma("data_alignment=16")
#define PRAGMA_ALIGN_8              _Pragma("data_alignment=8")
#define PRAGMA_ALIGN_4              _Pragma("data_alignment=4")
#define ALIGNED(n)                  PRAGMA_ALIGN_##n


/* Keil */
#elif defined(__CC_ARM)

#if (CFG_INLINING)
#define INLINE __inline
#else
#define INLINE
#endif

#define PREPACKED
#define POSTPACKED              __attribute__ ((packed))
#define ALIGNED(n)              __align(n)

/* CrossWorks */
#elif defined(__CROSSWORKS_ARM)

#if (CFG_INLINING)
#define INLINE inline
#else
#define INLINE
#endif

#ifndef UNUSED
#define UNUSED(x)               (void)(x)
#endif

#define PREPACKED
#define POSTPACKED              __attribute__ ((packed))
#define ALIGNED(n)              __attribute__ ((aligned(n)))

/* LPCXpresso */
#elif defined(__GNUC__)

#if (CFG_INLINING)
#define INLINE inline
#else
#define INLINE
#endif

#ifndef UNUSED
#define UNUSED(x)               (void)(x)
#endif

#define PREPACKED
#define POSTPACKED              __attribute__ ((packed))
#define ALIGNED(n)			    __attribute__ ((aligned(n)))

#endif
#endif /* KERNEL_TOOLCHAIN_H__ */
