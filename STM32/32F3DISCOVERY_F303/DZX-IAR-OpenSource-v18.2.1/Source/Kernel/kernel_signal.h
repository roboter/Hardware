/*******************************************************************************************************************************************

    DZX | KERNEL | SIGNAL                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for signal sets. A signal set contains 32 individual signal states, SIGNAL_0
    thru SIGNAL_31.

    A signal can be set from any context, thread or interrupt service routine (ISR). A thread can block and wait for a single signal,
    or multiple signals to be set. Upon a releasing a thread, a signal is automatically reset to the cleared state.

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
#ifndef KERNEL_SIGNAL_H__
#define KERNEL_SIGNAL_H__

#include "kernel_thread.h"

/*******************************************************************************************************************************************
    DEFINITIONS
*******************************************************************************************************************************************/
#define OPT_WAITANY             0               /* Option to wait for ANY of the specified signals */
#define OPT_WAITALL             1               /* Option to wait for ALL of the specified signals */

#define SIGNAL_NONE			    0               /**< Represents no signals */
#define SIGNAL_ALL			    0xFFFFFFFF      /**< Represents all possible signals */
#define SIGNAL_0			    (1UL << 0)      /**< Signal number 0 */
#define SIGNAL_1			    (1UL << 1)      /**< Signal number 1 */
#define SIGNAL_2			    (1UL << 2)      /**< Signal number 2 */
#define SIGNAL_3			    (1UL << 3)      /**< Signal number 3 */
#define SIGNAL_4			    (1UL << 4)      /**< Signal number 4 */
#define SIGNAL_5			    (1UL << 5)      /**< Signal number 5 */    
#define SIGNAL_6			    (1UL << 6)      /**< Signal number 6 */
#define SIGNAL_7			    (1UL << 7)      /**< Signal number 7 */
#define SIGNAL_8			    (1UL << 8)      /**< Signal number 8 */
#define SIGNAL_9			    (1UL << 9)      /**< Signal number 9 */
#define SIGNAL_10			    (1UL << 10)     /**< Signal number 10 */
#define SIGNAL_11			    (1UL << 11)     /**< Signal number 11 */
#define SIGNAL_12			    (1UL << 12)     /**< Signal number 12 */
#define SIGNAL_13			    (1UL << 13)     /**< Signal number 13 */
#define SIGNAL_14			    (1UL << 14)     /**< Signal number 14 */
#define SIGNAL_15			    (1UL << 15)     /**< Signal number 15 */
#define SIGNAL_16			    (1UL << 16)     /**< Signal number 16 */
#define SIGNAL_17			    (1UL << 17)     /**< Signal number 17 */
#define SIGNAL_18			    (1UL << 18)     /**< Signal number 18 */
#define SIGNAL_19			    (1UL << 19)     /**< Signal number 19 */
#define SIGNAL_20			    (1UL << 20)     /**< Signal number 20 */
#define SIGNAL_21			    (1UL << 21)     /**< Signal number 21 */
#define SIGNAL_22			    (1UL << 22)     /**< Signal number 22 */
#define SIGNAL_23			    (1UL << 23)     /**< Signal number 23 */
#define SIGNAL_24			    (1UL << 24)     /**< Signal number 24 */
#define SIGNAL_25			    (1UL << 25)     /**< Signal number 25 */
#define SIGNAL_26			    (1UL << 26)     /**< Signal number 26 */
#define SIGNAL_27			    (1UL << 27)     /**< Signal number 27 */
#define SIGNAL_28			    (1UL << 28)     /**< Signal number 28 */
#define SIGNAL_29			    (1UL << 29)     /**< Signal number 29 */
#define SIGNAL_30			    (1UL << 30)     /**< Signal number 30 */
#define SIGNAL_31			    (1UL << 31)     /**< Signal number 31 */

/***************************************************************************************************************************************//**

    Represents a signal set.
    @module     kernel-signal

*******************************************************************************************************************************************/
typedef struct SIGNALSET {
    UINT32 signals;         /**< The 32 individual signal states */
    THREAD* thread;         /**< A pointer to the thread, if any, currently blocked waiting for a signal(s) */
} SIGNALSET;

/***************************************************************************************************************************************//**

    Initializes a signal set.

    @param[in]  set    	    A pointer to the signal set to be initialized.

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The given signal set has been initialized.
     ERR_NULLREFERENCE      | The argument 'set' was found to be NULL.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_Init(SIGNALSET* set);

/***************************************************************************************************************************************//**

    Returns the state of the signals for a signal set. The signals are returned as a bit-field of signals where each bit number
    corresponds to the signal number. A bit value of '0' indicates the particular signal is cleared; while a bit value of '1' indicates 
    the signal is currently pending.

    @param[in]  set    	    A pointer to the signal set that contains the signals to be queried.
    @param[out] signals     A pointer to a caller allocated value to receive the state of the signals.

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The state of the signals have been returned.
     ERR_NULLREFERENCE      | The argument 'set' or 'signals' was found to be NULL.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_Query(const SIGNALSET* set, UINT32* signals);

/***************************************************************************************************************************************//**

    Sets one or more signals within a signal set. If a thread happens to be waiting for the signal(s), the signal(s) will be consumed and
    reset back to the cleared state and the waiting thread will be released. If no thread is waiting for the signal(s), the signal(s) 
    will go into the pending state.

    @param[in]  set    	    A pointer to the signal set to receive the signal(s).
    @param[in]  signals     One or more signals to be sent to the signal set. Use a bitwise OR to send multiple signals, e.g. 
                            (SIGNAL_0 | SIGNAL_1).

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The signals were successfully set within the signal set.
     ERR_NULLREFERENCE      | The argument 'set' was found to be a NULL reference.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_Set(SIGNALSET* set, UINT32 signals);

/***************************************************************************************************************************************//**

    Clears one or more signals within a signal set.

    @param[in]  set         A pointer to the signal set that contains the signals to be cleared.
    @param[in]  signals     The signal(s) to be cleared. Use a bitwise OR to clear multiple signals. e.g. (SIGNAL_0 | SIGNAL_1) to clear 
                            both signal number 0 and signal number 1.

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified signals have been cleared.
     ERR_NULLREFERENCE      | The argument 'set' was found to be a NULL reference.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_Clear(SIGNALSET* set, UINT32 signals);

/***************************************************************************************************************************************//**

    Waits for multiple signals to be received by a signal set. If the specified signal(s) are already in the pending state, this 
    will return immediately without blocking. If the signal(s) are successfully received, the signal(s) are consumed and reset back to 
    the cleared state.

    @param[in]  set         A pointer to the signal set to wait upon to receive the signals.
    @param[in]  opt         Use OPT_WAITANY to wait for ANY of the specified signals to arrive, or use OPT_WAITALL to wait for ALL of 
                            the specified signals to arrive.
    @param[in]  mask        The signal(s) to wait on to be received. Use bitwise OR for multiple signals, e.g. (SIGNAL_0 | SIGNAL_1).
    @param[out] signals     A pointer to a caller allocated value to receive the state of the signals when the wait operation completed. 
                            Can be NULL if don't care.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for any of the specified signals to be received. Use '0' 
                            to return immediately without blocking and use INFINITE to wait indefinitely.

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | If OPT_WAITANY, at least one, otherwise all signal(s) have been received.
     ERR_NULLREFERENCE      | The argument 'set' was found to be a NULL reference.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_TIMEOUT            | The maximum allowable time has elapsed prior to the specified signals being received.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_Wait(SIGNALSET* set, UINT32 opt, UINT32 mask, UINT32* signals, UINT32 timeout);

/***************************************************************************************************************************************//**

    Waits for a single signal to be received by a signal set. If the specified signal is already in the pending state, this will 
    return immediately without blocking. If the signal is successfully received, the signal is consumed and reset back to the cleared 
    state.

    @param[in]  set         A pointer to the signal set to wait upon to receive the signal.
    @param[in]  signal      The signal to wait on to be received.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to wait for the signal to be received. Use '0' to return 
                            immediately without blocking and use INFINITE to wait indefinitely.

    @return     

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The specified signal has been received.
     ERR_NULLREFERENCE      | The argument 'set' was found to be a NULL reference.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | An invalid argument was found. Only a single signal can be specified.
     ERR_TIMEOUT            | The maximum allowable time has elapsed prior to the specified signal being received.

    @module     kernel-signal

*******************************************************************************************************************************************/
extern STATUS SIGNAL_WaitOne(SIGNALSET* set, UINT32 signal, UINT32 timeout);
                          
#endif /* KERNEL_SIGNAL_H__ */
