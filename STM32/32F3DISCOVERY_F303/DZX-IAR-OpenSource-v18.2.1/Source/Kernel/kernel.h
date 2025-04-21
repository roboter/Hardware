/*******************************************************************************************************************************************

    DZX | KERNEL                                                                                                          VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file provides the core interface for the real-time kernel.

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
#ifndef KERNEL_H__
#define KERNEL_H__

#include "Kernel/kernel_toolchain.h"
#include "kernel_cfg.h"
#include "kernel_version.h"

/*******************************************************************************************************************************************
    OPTIONS
*******************************************************************************************************************************************/
#define OPT_DEFAULT                 0                   /**< Default options */
#define OPT_NONE                    0                   /**< No options */
#define OPT_START                   (1UL << 0)          /**< Indicates an option to start */
#define OPT_AUTORESET               (1UL << 1)          /**< Indicates an option to automatically reset */

/***************************************************************************************************************************************//**

    Represents an infinite timeout value. (Wait indefinitely)
    @module     kernel-core

*******************************************************************************************************************************************/
#define INFINITE                    0xFFFFFFFF

/***************************************************************************************************************************************//**

    Calculates the number of kernel ticks for the specified number of milliseconds.
    @module     kernel-core

*******************************************************************************************************************************************/
#define MILLISECOND_TICKS(ms)       ((ms * 1000) / CFG_TICKSPERSECOND)

/***************************************************************************************************************************************//**

    Represents an instance in time expressed as a date and time of day.
    @module     kernel-core

*******************************************************************************************************************************************/
typedef struct DATETIME {
	WORD year;                      /**< The year component */
	BYTE month;                     /**< The month component (1-12) */
	BYTE day;                       /**< The day component (1-31) */
	BYTE hour;                      /**< The hour component (0-23) */
	BYTE minute;                    /**< The minutes component (0-59) */
	BYTE second;                    /**< The seconds component (0-59) */
    WORD millisecond;               /**< The millisecond component (0-999) */
} DATETIME;

/***************************************************************************************************************************************//**

    A block of information that describes the version and configuration applied during the build of the SDK.
    @module     kernel-core

*******************************************************************************************************************************************/
typedef struct KERNELINFO {
    VERSION version;                /**< The release version of the kernel */
    UINT32  datetime;               /**< The build date and time for kernel */
    UINT32  tickspersecond;         /**< The number of kernel ticks that occur per second */
    UINT32  timestamppersecond;     /**< The number of timestamp ticks that occur per second */
} KERNELINFO;

/***************************************************************************************************************************************//**

    An application-defined function that serves as the entry point for a thread.

    @param[in]  arg         A pointer to an application-defined argument.

    @return     None
    @module     kernel-core

*******************************************************************************************************************************************/
typedef void (*THREADSTART)(void* arg);

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes and begins execution of the kernel.

    @param[in]  proc        The process (entry) function for the main application thread.
    @param[in]  arg         An optional argument to be passed to the process function. Can be NULL.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     ERR_KERNELFAILED       | The kernel failed to execute.
     ERR_NULLREFERENCE      | The argument 'proc' was found to be NULL.

    @remark     Must be called before making any other calls into the kernel.
    @remark     Does not return as execution is transferred to the threads within the kernel.
    @module     kernel-core

*******************************************************************************************************************************************/
extern STATUS KERNEL_Execute(THREADSTART proc, void* arg);

/***************************************************************************************************************************************//**

    Returns the current time, in kernel ticks, from within the kernel.

    @return     The current kernel time.
    @module     kernel-core

*******************************************************************************************************************************************/
extern UINT32 KERNEL_Ticks(void);

/***************************************************************************************************************************************//**

    Returns information about the kernel.

    @return     A pointer to a block of information describing the kernel.
    @module     kernel-core

*******************************************************************************************************************************************/
extern const KERNELINFO* KERNEL_Info(void);

/*******************************************************************************************************************************************
    HOOK FUNCTIONS
*******************************************************************************************************************************************/
#if (CFG_HOOKBOOT)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when the kernel has booted. Called from the KERNEL_Boot() function.

    @return     None.
    @module     kernel-hook

*******************************************************************************************************************************************/
extern void HOOK_Boot(void);
#endif

#if (CFG_HOOKIDLE)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called from the kernel idle process.

    @return     None.
    @module     kernel-hook

*******************************************************************************************************************************************/
extern void HOOK_Idle(void);
#endif

#if (CFG_HOOKCONTEXTSWITCH)
/***************************************************************************************************************************************//**

    An application-defined hook function that is called when a context switch occurs.

    @param[in]  prev        A pointer to the thread that had previously been executing.
    @param[in]  next        A pointer to the thread that is next to execute.

    @return     None.
    @module     kernel-hook

*******************************************************************************************************************************************/
extern void HOOK_ContextSwitch(THREAD* prev, THREAD* next);
#endif

#endif /* KERNEL_H__ */
