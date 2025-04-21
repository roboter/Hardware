/*******************************************************************************************************************************************

    DZX | KERNEL | DATA TYPES                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the kernel and provides a definition for a version field. This also provides a method for automatically generating
    a build date and time.

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
#ifndef KERNEL_VERSION_H__
#define KERNEL_VERSION_H__

#include "kernel_types.h"

/***************************************************************************************************************************************//**

    Represents a version number with a major, minor and revision component within a 32-bit field.
    @module     kernel-core

*******************************************************************************************************************************************/
typedef struct VERSION {
    UINT8   major;                  /**< The major version component */
    UINT8   minor;                  /**< The minor version component */
    UINT16  revision;               /**< The revision component */
} VERSION;

/*******************************************************************************************************************************************
    BUILD DATE/TIME
*******************************************************************************************************************************************/
#if defined(__DATE__) && defined(__TIME__)

/* Construct the year and day digits */
#define BUILD_YEAR              ((__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + __DATE__[10] - '0')
#define BUILD_DAY_TWO_DIGITS    (__DATE__[4] >= '0')
#define BUILD_DAY               (BUILD_DAY_TWO_DIGITS) ? ((__DATE__[4] - '0') * 10 + __DATE__[5] - '0') : (__DATE__[5] - '0')

/* Construct the time digits */
#define BUILD_HOUR              ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define BUILD_MIN               ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define BUILD_SEC               ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

/* Construct the month digits */
#define BUILD_MONTH_IS_JAN      (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB      (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR      (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR      (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY      (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN      (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL      (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG      (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP      (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT      (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV      (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC      (__DATE__[0] == 'D')
#define BUILD_MONTH \
    ( \
        (BUILD_MONTH_IS_JAN) ?  1 : \
        (BUILD_MONTH_IS_FEB) ?  2 : \
        (BUILD_MONTH_IS_MAR) ?  3 : \
        (BUILD_MONTH_IS_APR) ?  4 : \
        (BUILD_MONTH_IS_MAY) ?  5 : \
        (BUILD_MONTH_IS_JUN) ?  6 : \
        (BUILD_MONTH_IS_JUL) ?  7 : \
        (BUILD_MONTH_IS_AUG) ?  8 : \
        (BUILD_MONTH_IS_SEP) ?  9 : \
        (BUILD_MONTH_IS_OCT) ? 10 : \
        (BUILD_MONTH_IS_NOV) ? 11 : \
        (BUILD_MONTH_IS_DEC) ? 12 : \
        /* error default */  0 \
    )

#define BUILD_TIME              ((BUILD_HOUR << 11) | (BUILD_MIN << 5) | (BUILD_SEC >> 1))          /* Build Time in 16-bit format */
#define BUILD_DATE              ((((BUILD_YEAR - 1980) << 9) | (BUILD_MONTH << 5)) | (BUILD_DAY))   /* Build Date in 16-bit format */
        
#else   
        
#define BUILD_TIME              0                                                                   /* No support for build date/time */
#define BUILD_DATE              0
        
#endif /* defined(__DATE__) && defined(__TIME__) */
       
/***************************************************************************************************************************************//**

    Defines the build date and time as a single unsigned 32-bit value. The upper 16-bits describe the date while the lower 16-bits
    describe the time of day.
        
    The bit definitions are as follows:
        
        31-25: Years since 1980
        24-21: Month (1-12)
        20-16: Day (1-31)
        15-11: Hours (0-23)
        10- 5: Minutes (0-59)
         4- 0: Seconds (0-29 in 2 second intervals)
        
    @module     kernel-core

*******************************************************************************************************************************************/  
#if defined(__GNUC__)
#define BUILD_DATETIME          0
#else
#define BUILD_DATETIME          ((BUILD_DATE << 16) | (BUILD_TIME))                             /* Build Date & Time in 32-bit format */
#endif
        
#endif /* KERNEL_VERSION_H__ */
