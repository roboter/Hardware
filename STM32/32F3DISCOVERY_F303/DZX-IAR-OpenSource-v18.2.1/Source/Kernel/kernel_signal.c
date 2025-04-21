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
#include "kernel_signal.h"
#include "kernel_core.h"

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
STATUS SIGNAL_Init(SIGNALSET* set)
{
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    set->signals = SIGNAL_NONE;
    set->thread = NULL;
    return SUCCESS;
}

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
STATUS SIGNAL_Query(const SIGNALSET* set, UINT32* signals)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (signals == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    ACQUIREINTERRUPTLOCK();
    
    *signals = set->signals;
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
STATUS SIGNAL_Set(SIGNALSET* set, UINT32 signals)
{
    INTERRUPTLOCK lock;
    UINT32 mask;
    
    
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    set->signals |= signals;									    /* Set the specified signals as pending */

    if (set->thread == NULL) {
        RELEASEINTERRUPTLOCK();
        return SUCCESS;                                             /* No thread waiting, done */
    }

    mask = ((UINT32)set->thread->args[1]);                          /* Capture the signals the thread is waiting upon */

    if (((UINT32)set->thread->args[0]) == OPT_WAITANY) {            /* Is the thread waiting for ANY masked signal? */
        if (set->signals & mask) {                                  /* Are any of the masked signals pending? */
            
            set->thread->args[1] = (void*)(set->signals & mask);    /* Store the consumed signals (returned from SIGNAL_Wait()) */ 
            set->signals &= ~mask;					                /* Automatically reset the masked signals */ 

            set->thread->bobj = NULL;                               /* No longer waiting for signals */
            set->thread->status = SUCCESS;                          /* Indicate the signals were received */			
            KERNEL_SetState(set->thread, STATE_READY);              /* Release the waiting thread */
            
            set->thread = NULL;
            RELEASEINTERRUPTLOCK();
            KERNEL_ContextSwitch();
            return SUCCESS;
        }
        
    } else if ((set->signals & mask) == mask) {                     /* Are ALL of the masked signals pending? */

        set->signals &= ~mask;			                            /* Automatically reset the masked signals */
        
        set->thread->bobj = NULL;                                   /* No longer waiting for signals */
        set->thread->status = SUCCESS;                              /* Indicate the signals were received */			
        KERNEL_SetState(set->thread, STATE_READY);                  /* Release the waiting thread */
        
        set->thread = NULL;
        RELEASEINTERRUPTLOCK();
        KERNEL_ContextSwitch();
        return SUCCESS;
    }
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
STATUS SIGNAL_Clear(SIGNALSET* set, UINT32 signals)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    set->signals &= ~signals;
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

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
STATUS SIGNAL_Wait(SIGNALSET* set, UINT32 opt, UINT32 mask, UINT32* signals, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif  
    
    ACQUIREINTERRUPTLOCK();

    if (opt == OPT_WAITANY) {                                       /* Waiting for ANY of the specified signals? */
        if ((set->signals & mask)) {                                /* Are the signal(s) already pending? */
            if (signals) {
                *signals = (set->signals & mask);                   /* Return the signal(s) that were consumed */
            }
            set->signals &= ~mask;                                  /* Automatically reset the signals */
            RELEASEINTERRUPTLOCK();
            return SUCCESS;	                                        /* Return without blocking */
        }
    } else if ((set->signals & mask) == mask) {                     /* Are the signals already ALL pending? */
        if (signals) {
            *signals = (set->signals & mask);			            /* Return the signals that were consumed */
        }
        set->signals &= ~mask;						                /* Automatically reset the signals */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;											    /* Return without blocking */
    }

	if (timeout == 0) {                                             /* Did the caller specify not to block? */
        if (signals) {
            *signals = (set->signals & mask);                       /* Return the current state of the signals */
        }
		RELEASEINTERRUPTLOCK();
		return ERR_TIMEOUT;                                         /* Return without blocking */
	}
	
	KERNEL_Block(set, NULL, timeout);				                /* Block the calling thread */
    
    kernel.thread->args[0] = (void*)opt;                            /* Indicate the wait type for the masked signals */
    kernel.thread->args[1] = (void*)mask;					        /* Keep a reference of the signals the thread is blocked upon */
    
    set->thread = kernel.thread;
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                         /* Caller blocked, switch threads */
    
    if (signals) {
        *signals = (UINT32)kernel.thread->args[1];                  /* Return the signals that were consumed */
    }
    
    return kernel.thread->status;                                   /* Caller released, return result */
}

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
STATUS SIGNAL_WaitOne(SIGNALSET* set, UINT32 signal, UINT32 timeout)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (set == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
    if (signal == SIGNAL_NONE) {                                /* Was a signal specified? */
        return ERR_INVALIDARGUMENT;                             /* Invalid, must specify a signal */
    }

    if ((signal & (signal - 1))) {                              /* Is more than one signal specified? */
        return ERR_INVALIDARGUMENT;                             /* Invalid, can only specify one signal */
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (set->thread) {
         RELEASEINTERRUPTLOCK();
         return ERR_INVALIDOPERATION;                           /* Only one thread at a time can block upon a signal set */
    }
    
    if (set->signals & signal) {                                /* Is the signal already pending? */
        set->signals &= ~signal;					            /* Yes, automatically reset the signal */
        RELEASEINTERRUPTLOCK();
        return SUCCESS;
    }
    
    if (timeout == 0) {
		RELEASEINTERRUPTLOCK();
		return ERR_TIMEOUT;                                     /* Return without blocking */
	}
    
    KERNEL_Block(set, NULL, timeout);				            /* Block the calling thread */
    
    kernel.thread->args[0] = (void*)OPT_WAITALL;                /* Indicate to wait for any masked signals */
    kernel.thread->args[1] = (void*)signal;				        /* Keep a reference of the signal the thread is blocked upon */

    set->thread = kernel.thread;
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                                     /* Caller blocked, switch threads */
    return kernel.thread->status;                               /* Caller was released, return status code */
}
