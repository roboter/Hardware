/*******************************************************************************************************************************************

    DZX | KERNEL PORT | ARM CORTEX M3                                                                                     VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides specific functionality for the ARM Cortex-M3 architecture.

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
#ifndef KERNEL_PORT_H__
#define KERNEL_PORT_H__

#include "Kernel/kernel_types.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_8(addr)						(*(volatile UINT8*)(addr))          /* A generic 8-bit register */
#define REG_16(addr)					(*(volatile UINT16*)(addr))         /* A generic 16-bit register */        
#define REG_32(addr)					(*(volatile UINT32*)(addr))         /* A generic 32-bit register */
#define REGBITS_8(addr, bits)			(*(volatile bits*)(addr))           /* A generic 8-bit register bitfield */
#define REGBITS_16(addr, bits)			(*(volatile bits*)(addr))           /* A generic 16-bit register bitfield */
#define REGBITS_32(addr, bits)			(*(volatile bits*)(addr))           /* A generic 32-bit register bitfield */


/*******************************************************************************************************************************************
    PERIPHERAL REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#if defined(__ICCARM__)                                                 /* Enable support for anonymous unions */
    #pragma language=extended
#elif defined(__CC_ARM)
    #pragma anon_unions
#elif defined(__TASKING__)
    #pragma warning 586
#endif

#define PREG_RSRVD32(NAME)              volatile const UINT32 NAME      /**< A reserved 32-bit peripheral register */
#define PREG_8(NAME)                    volatile UINT8 NAME
#define PREG_16(NAME)                   volatile UINT16 NAME
#define PREG_32(NAME)                   volatile UINT32 NAME            /**< A 32-bit read/write peripheral register */
#define PREG_BITS32(NAME, BITFIELD)     volatile union\
                                        {\
                                            BITFIELD BITS;\
                                            UINT32 VALUE;\
                                        } NAME                          /**< A 32-bit read/write peripheral bitfield register */

                                            
typedef struct VTORBITFIELD {
    UINT32                         :7;
    UINT32 TBLOFF                  :22;
    UINT32 TBLBASE                 :1;
    UINT32                         :2;
} VTORBITFIELD;

typedef struct CFSRBITFIELD {
    UINT32 IACCVIOL                :1;
    UINT32 DACCVIOL                :1;
    UINT32                         :1;
    UINT32 MUNSTKERR               :1;
    UINT32 MSTKERR                 :1;
    UINT32                         :2;
    UINT32 MMARVALID               :1;
    UINT32 IBUSERR                 :1;
    UINT32 PRECISERR               :1;
    UINT32 IMPRECISERR             :1;
    UINT32 UNSTKERR                :1;
    UINT32 STKERR                  :1;
    UINT32                         :2;
    UINT32 BFARVALID               :1;
    UINT32 UNDEFINSTR              :1;
    UINT32 INVSTATE                :1;
    UINT32 INVPC                   :1;
    UINT32 NOCP                    :1;
    UINT32                         :4;
    UINT32 UNALIGNED               :1;
    UINT32 DIVBYZERO               :1;
    UINT32                         :6;
} CFSRBITFIELD;

typedef struct ICSRBITFIELD {
    UINT32 VECTACTIVE              :10;
    UINT32                         :1;
    UINT32 RETTOBASE               :1;
    UINT32 VECTPENDING             :10;
    UINT32 ISRPENDING              :1;
    UINT32 ISRPREEMPT              :1;
    UINT32                         :1;
    UINT32 PENDSTCLR               :1;
    UINT32 PENDSTSET               :1;
    UINT32 PENDSVCLR               :1;
    UINT32 PENDSVSET               :1;
    UINT32                         :2;
    UINT32 NMIPENDSET              :1;
} ICSRBITFIELD;

typedef struct SHPR0BITFIELD {
    UINT32 PRI4                    :8;
    UINT32 PRI5                    :8;
    UINT32 PRI6                    :8;
    UINT32 PRI7                    :8;
} SHPR0BITFIELD;

typedef struct SHPR1BITFIELD {
    UINT32 PRI8                    :8;
    UINT32 PRI9                    :8;
    UINT32 PRI10                   :8;
    UINT32 PRI11                   :8;
} SHPR1BITFIELD;

typedef struct SHPR2BITFIELD {
    UINT32 PRI12                   :8;
    UINT32 PRI13                   :8;
    UINT32 PRI14                   :8;
    UINT32 PRI15                   :8;
} SHPR2BITFIELD;

typedef struct CPACRBITFIELD {
    UINT32                         :20;
    UINT32 CP10                    :2;
    UINT32 CP11                    :2;
    UINT32                         :8;
} CPACRBITFIELD;

#define BASE_IPR                                  0xE000E400

#define REG_CFSR                                  REG_32(0xE000ED28)
#define REGBITS_CFSR                              REGBITS_32(0xE000ED28, CFSRBITFIELD)

#define REG_CLRENA1                               REG_32(0xE000E184)
#define REG_DEMCR                                 REG_32(0xE000EDFC)
#define REG_DWTCTRL                               REG_32(0xE0001000)
#define REG_DWTCYCCNT                             REG_32(0xE0001004)
#define REG_DWTEXCCNT                             REG_32(0xE000100C)
#define REG_ICSR                                  REG_32(0xE000ED04)
#define REGBITS_ICSR                              REGBITS_32(0xE000ED04, ICSRBITFIELD)
  
#define BASE_ISER                                 0xE000E100
#define REG_ISER                                  REG_32(0xE000E100)
#define REG_ISER0                                 REG_32(0xE000E100)
#define REG_ISER1                                 REG_32(0xE000E104)
#define REG_ISER2                                 REG_32(0xE000E108)
#define REG_ISER3                                 REG_32(0xE000E10C)
#define REG_ISER4                                 REG_32(0xE000E110)
#define REG_ISER5                                 REG_32(0xE000E114)
#define REG_ISER6                                 REG_32(0xE000E118)
#define REG_ISER7                                 REG_32(0xE000E11C)

#define BASE_ICER                                 0xE000E180
#define REG_ICER0                                 REG_32(0xE000E180)
#define REG_ICER1                                 REG_32(0xE000E184)
#define REG_ICER2                                 REG_32(0xE000E188)
#define REG_ICER3                                 REG_32(0xE000E18C)
#define REG_ICER4                                 REG_32(0xE000E190)
#define REG_ICER5                                 REG_32(0xE000E194)
#define REG_ICER6                                 REG_32(0xE000E198)
#define REG_ICER7                                 REG_32(0xE000E19C)

#define REG_IP0                                   REG_32(0xE000E400)
#define REG_IP1                                   REG_32(0xE000E404)
#define REG_IP2                                   REG_32(0xE000E408)
#define REG_IP3                                   REG_32(0xE000E40C)
#define REG_IP4                                   REG_32(0xE000E410)
#define REG_IP5                                   REG_32(0xE000E414)
#define REG_IP6                                   REG_32(0xE000E418)
#define REG_IP7                                   REG_32(0xE000E41C)

#define REG_SHPR0                                 REG_32(0xE000ED18)
#define REGBITS_SHPR0                             REGBITS_32(0xE000ED18, SHPR0BITFIELD)
#define REG_SHPR1                                 REG_32(0xE000ED1C)
#define REGBITS_SHPR1                             REGBITS_32(0xE000ED1C, SHPR1BITFIELD)
#define REG_SHPR2                                 REG_32(0xE000ED20)
#define REGBITS_SHPR2                             REGBITS_32(0xE000ED20, SHPR2BITFIELD)
#define REG_STCALIB                               REG_32(0xE000E01C)
#define REG_STCTRL                                REG_32(0xE000E010)
#define REG_STCURR                                REG_32(0xE000E018)
#define REG_STIR                                  REG_32(0xE000EF00)
#define REG_STRELOAD                              REG_32(0xE000E014)
#define REG_VTOR                                  REG_32(0xE000ED08)
#define REGBITS_VTOR                              REGBITS_32(0xE000ED08, VTORBITFIELD)
#define REG_CPACR                                 REG_32(0xE000ED88)
#define REGBITS_CPACR                             REGBITS_32(0xE000ED88, CPACRBITFIELD)
#define REG_AIRCR                                 REG_32(0xE000ED0C)

/*******************************************************************************************************************************************

    STACKALIGNMENT                  Specifies the alignment that is maintained when initializing stack memory for a thread.

*******************************************************************************************************************************************/
#define STACKALIGNMENT              8

/*******************************************************************************************************************************************

    STACKALIGNMENT                  Specifies the alignment that is maintained for a block of memory allocated from a heap.

*******************************************************************************************************************************************/
#define HEAPBLKALIGNMENT            8

/***************************************************************************************************************************************//**

    Represents the platform specific thread context information.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct THREADCONTEXT {
	void* SP;           /**< The current stack location for the thread */
} THREADCONTEXT;

/***************************************************************************************************************************************//**

    Represents a register stack frame that is managed by the CPU.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct STACKFRAME {
	UINT32 R0;          /**< Register 0 */
	UINT32 R1;          /**< Register 1 */
	UINT32 R2;          /**< Register 2 */
	UINT32 R3;          /**< Register 3 */
	UINT32 R12;         /**< Register 12 */
	UINT32 LR;          /**< Link Register */
	UINT32 PC;          /**< Program Counter */
	UINT32 PSR;         /**< Program Status Register */
} STACKFRAME;

/***************************************************************************************************************************************//**

    Represents information about a HardFault exception.
    @module     INTERNAL

*******************************************************************************************************************************************/
typedef struct HARDFAULTINFO {
	const STACKFRAME* registers;        /**< A dump of the registers as they were when the hard fault occurred */
	CFSRBITFIELD cfsr;                  /**< A copy of the CFSR register when the hard fault occurred */
} HARDFAULTINFO;

/***************************************************************************************************************************************//**

    Returns the last address for a thread stack.

    @param[in]  stk         The start of the thread stack memory.
    @param[in]  size        The size in bytes of the stack memory.

    @return     The last address of the specified thread stack memory.
    @module     INTERNAL

*******************************************************************************************************************************************/
#define STACKEND(stk, size)      ((void*)((UINT32)stk + size - sizeof(UINT32)))

/***************************************************************************************************************************************//**

    Returns a high resolution timestamp value.

    @return     The current timestamp value.
    @remark     Use CFG_TSTICKSPERSECOND to determine the resolution of the timestamp ticks.
    @module     KERNEL-CORE

*******************************************************************************************************************************************/
#define KERNEL_Timestamp()      ((UINT32)REG_DWTCYCCNT)

/***************************************************************************************************************************************//**

    Returns an indication of whether the caller is from the context of an interrupt service routine (ISR).

    @return     TRUE if the caller is executing from within an ISR context; otherwise FALSE.
    @module     KERNEL-CORE

*******************************************************************************************************************************************/
#define KERNEL_IsISR()          ((REG_ICSR & 0x000000FF) > 0)

/*******************************************************************************************************************************************

    Represents a lock that masks interrupts while acquired.
    @module     kernel-lock

*******************************************************************************************************************************************/
typedef UINT32 INTERRUPTLOCK;

/*******************************************************************************************************************************************

    Represents a lock that disables thread preemption while acquired.
    @module     kernel-lock

*******************************************************************************************************************************************/
typedef UINT32 THREADLOCK;

/***************************************************************************************************************************************//**

    Acquires a synchronization lock by disabling interrupts for the current CPU.

    @return     None.
    @remark     Requires an INTERRUPTLOCK named 'lock' to be allocated locally on the stack prior to calling.
    @module     kernel-lock

*******************************************************************************************************************************************/
#define ACQUIREINTERRUPTLOCK()      do { \
                                        lock = KERNEL_AcquireInterruptLock(); \
                                    } while (0)

/***************************************************************************************************************************************//**

    Releases a previously acquired synchronization lock and restores the interrupt state.

    @return     None.
    @module     kernel-lock

*******************************************************************************************************************************************/                                        
#define RELEASEINTERRUPTLOCK()      do { \
                                        KERNEL_ReleaseInterruptLock(lock); \
                                    } while (0)


/*******************************************************************************************************************************************
    RESET VECTOR LOCATION           
*******************************************************************************************************************************************/
#ifndef CFG_RESETVECTORADDRESS

/* IAR */
#if defined(__ICCARM__)
extern UINT32 __vector_table;
#define CFG_RESETVECTORADDRESS      ((UINT32)&__vector_table)

/* Keil */
#elif defined(__CC_ARM)
extern UINT32 __Vectors;
#define CFG_RESETVECTORADDRESS      ((UINT32)&__Vectors)

/* CrossWorks */
#elif defined(__CROSSWORKS_ARM)
extern UINT32 _vectors;
#define CFG_RESETVECTORADDRESS      ((UINT32)&_vectors)

/* LPCXpresso */
#elif defined(__GNUC__)
extern void(*const g_pfnVectors[])(void);
#define CFG_RESETVECTORADDRESS		((UINT32)g_pfnVectors)

#endif
#endif

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Acquires an interrupt lock by disabling all maskable interrupts.

    @return     The lock that was acquired.
    @module     kernel-port-cm3

*******************************************************************************************************************************************/
extern INTERRUPTLOCK KERNEL_AcquireInterruptLock(void);

/***************************************************************************************************************************************//**

    Releases an interrupt lock by restoring the interrupt mask state.

    @param[in]  lock        The lock to be released.

    @return     None.
    @module     kernel-port-cm3

*******************************************************************************************************************************************/
extern void KERNEL_ReleaseInterruptLock(INTERRUPTLOCK lock);

/***************************************************************************************************************************************//**

    Executes an application at the specified address.

    @param[in]  address     The starting address for the application to be executed.

    @return     Does not return as it launches the specified application.
    @module     kernel-port-cm3

*******************************************************************************************************************************************/
extern void KERNEL_ExecuteApp(UINT32 address);

#endif /* KERNEL_PORT_H__ */
