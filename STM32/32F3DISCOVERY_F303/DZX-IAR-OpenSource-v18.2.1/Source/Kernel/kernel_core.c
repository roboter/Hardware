/*******************************************************************************************************************************************

    DZX | KERNEL | CORE                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file provides core functionality for the real-time kernel.

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
#include "kernel_core.h"
#include "kernel_stat.h"

/*******************************************************************************************************************************************
    CONSTANT VARIABLES
*******************************************************************************************************************************************/
const KERNELINFO kernel_info = {
    { KERNEL_MAJORVERSION, KERNEL_MINORVERSION, KERNEL_REVISION },      /* Kernel version */
    BUILD_DATETIME,                                                     /* Build date/time */
    CFG_TICKSPERSECOND,                                                 /* Configured kernel ticks per second */
    CFG_TSTICKSPERSECOND,                                               /* Configured kernel timestamp ticks per second */
};

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
KERNEL kernel;

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void KERNEL_Idle(void* arg);
static void KERNEL_Tick(void);
static void KERNEL_TickProc(void* arg);
static void KERNEL_InsertBlockedThread(THREAD* thread);

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
STATUS KERNEL_Execute(THREADSTART proc, void* arg)
{
    ALIGNED(8) static BYTE IdleStack[CFG_IDLESTACKSIZE];        /* Allocate the idle thread stack memory */
    ALIGNED(8) static BYTE MainStack[CFG_MAINSTACKSIZE];        /* Allocate the main thread stack memory */
    ALIGNED(8) static BYTE TickStack[CFG_TICKSTACKSIZE];        
    INTERRUPTLOCK lock;
    STATUS status;
    UINT32 k;
    
    
    
#if (CFG_NULLCHECKING)
    if (proc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    
    status = MCU_Initialize();                                  /* Initialize the on-chip peripheral drivers */
    if (status != SUCCESS) {
        return status;
    }
    
    kernel.info = &kernel_info;                                 /* Assign constant kernel information */
    kernel.thread = NULL;                                       /* Initialize with no current thread */
    kernel.prio = PRIO_IDLE;

    LIST_Init(&kernel.threads);                                 /* Initialize the threading lists */
    LIST_Init(&kernel.pending);
    
    for (k = 0; k < PRIO_MAX; k++) {                            /* Initialize the ready lists */
        LIST_Init(&kernel.ready[k]);
    }
    
    for (k = 0; k < CFG_BLOCKLISTS; k++) {                      /* Initialize the blocked lists */
        LIST_Init(&kernel.blocked[k]);
    }
    
    SIGNAL_Init(&kernel.signals);
    
    status = MUTEX_Create(&kernel.mutex,                        /* Create underlying mutex to synchronize access to thread lists */
                          "Kernel Lock", 
                          FALSE);
    
    if (status != SUCCESS) {
        return status;
    }

    status = THREAD_Create(&kernel.idle,                        /* Create the idle thread */
                           "Kernel Idle",
                           IdleStack,
                           CFG_IDLESTACKSIZE,
                           PRIO_IDLE);
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Start(&kernel.idle,                         /* Start the idle thread */
                          KERNEL_Idle,                          /* Idle thread entry point */
                          NULL);                                /* Idle thread argument */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = TIMER_Initialize();                                /* Initialize system timers */
    if (status != SUCCESS) {
        return status;                                          /* Failed to initialize the timers; bubble up the error. */
    }
    
    status = THREAD_Create(&kernel.tick,                        /* Create the tick thread */
                           "Kernel Tick",
                           TickStack,
                           CFG_TICKSTACKSIZE,
                           CFG_TICKPRIORITY);
    
    if (status != SUCCESS) {
        return status;                                          /* Failed to create idle thread; bubble up the error. */
    }
    
    status = THREAD_Start(&kernel.tick,                         /* Start the idle thread */
                          KERNEL_TickProc,                      /* Idle thread entry point */
                          NULL);                                /* Idle thread argument */
    
    if (status != SUCCESS) {
        return status;                                          /* Failed to start the idle thread */
    }

#if (CFG_STATISTICS)
    status = KERNEL_InitializeStats();                          /* Initialize statistics keeping */
    if (status != SUCCESS) {
        return status;                                          /* Failed to initialize the statistics; bubble up the error. */
    }
#endif
    
    status = THREAD_Create(&kernel.main,                        /* Create the application's main thread */
                           "Application",
                           MainStack,                           /* The main thread stack memory */
                           CFG_MAINSTACKSIZE,                   /* Size in bytes of the main thread's stack memory */
                           PRIO_NORMAL);                        /* Default normal priority */

    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Start(&kernel.main,                         /* Start the application's main thread */
                          proc,                                 /* The entry function */
                          arg);                                 /* An optional argument */
    
    if (status != SUCCESS) {
        return status;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    kernel.thread = &kernel.main;                               /* Use the application thread as the first thread to be executed */
    
    RELEASEINTERRUPTLOCK();

    KERNEL_ExecutePort(proc, arg);                              /* Start execution of the kernel within the port layer */
    return ERR_KERNELFAILED;                                    /* The kernel has failed to execute */
}

/***************************************************************************************************************************************//**

    Returns information about the kernel.

    @return     A pointer to a block of information describing the kernel.
    @module     kernel-core

*******************************************************************************************************************************************/
const KERNELINFO* KERNEL_Info(void)
{
    return kernel.info;
}

/*******************************************************************************************************************************************

    The idle thread process for the kernel.

    @param[in]  arg         A pointer to an argument provided when the thread was created. Not used here.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void KERNEL_Idle(void* arg)
{
    for (;;) {                                                  /* Keep idle thread from exiting */

#if (CFG_HOOKIDLE)
        HOOK_Idle();
#endif
    }
}

/*******************************************************************************************************************************************

    Inserts a thread into the blocked lists based upon its expiry time.

    @param[in]  thread      A pointer to the thread to be inserted into a block list.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void KERNEL_InsertBlockedThread(THREAD* thread)
{
    INTERRUPTLOCK lock;
    UINT32 ticks;
    UINT32 idx;
    NODE* node;
    THREAD* cur;

    
    ticks = kernel.ticks;
    
    if (thread->time > 0) {
        thread->timeout = thread->time + ticks - 1;
    } else {
        thread->timeout = ticks;
    }
    
    idx = thread->timeout % CFG_BLOCKLISTS;
    
    ACQUIREINTERRUPTLOCK();
    if (thread->pnode.list) {
        LIST_Remove(thread->pnode.list, &thread->pnode);
    }
    RELEASEINTERRUPTLOCK();
    
    LIST_Foreach(node, &kernel.blocked[idx]) {                      /* Search the blocked list to keep sort by expiration time */
        cur = node->value;
      
        if ((thread->timeout - ticks) < (cur->timeout - ticks)) {   /* Does this block expire before? */   
            LIST_AddBefore(&kernel.blocked[idx],                    /* Yes, insert the thread here */
                           node,
                           &thread->pnode,
                           thread);
            return;
        }     
    }

    LIST_AddLast(&kernel.blocked[idx],                          /* No insertion point found, append to the end */
                 &thread->pnode, 
                 thread); 
}

/*******************************************************************************************************************************************

    Signals the kernel to process the next time tick.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_SignalTick(void)
{
    SIGNAL_Set(&kernel.signals, CFG_TICKSIGNAL);
}

/*******************************************************************************************************************************************

    A thread function for processing each kernel time tick.

    @param[in]  arg         Unused argument.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void KERNEL_TickProc(void* arg)
{
    STATUS status;
    
    
    (void)arg;
    
    for (;;) {
        
        status = SIGNAL_WaitOne(&kernel.signals,                        /* Wait for the next tick */
                                CFG_TICKSIGNAL, 
                                INFINITE);          
        
        if (status == SUCCESS) {
            KERNEL_Tick();                                              /* Perform tick processing */
        }
    }
}

/*******************************************************************************************************************************************

    Performs the processing for each kernel time tick.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
static void KERNEL_Tick(void)
{
    INTERRUPTLOCK lock;
    NODE* node;
    THREAD* thread;
    UINT32 k;
    
    
    ACQUIREINTERRUPTLOCK();
    ++kernel.ticks;                                             /* Update kernel tick time */
    RELEASEINTERRUPTLOCK();

    if (kernel.thread == NULL) {                                /* Kernel running yet? */
        return;                                                 /* No, nothing to do */
    }
                
    TIMER_Process();                                            /* Process the system timers */
            
    KERNEL_AcquireLock();
            
    /* Process each of the threads that are blocked, but
    pending to be sorted within the block lists */
   
    ACQUIREINTERRUPTLOCK();
    node = LIST_RemoveFirst(&kernel.pending);                   /* Attempt to get a pending thread */
    RELEASEINTERRUPTLOCK();
    
    while (node) {
        thread = node->value;
        
        if (thread->state == STATE_BLOCKED ||                   /* Is the thread still needing to be blocked? */
            thread->state == STATE_SLEEPING) {
            
            KERNEL_InsertBlockedThread(thread);                 /* Insert the thread in order of expiry time */
        }
        
        ACQUIREINTERRUPTLOCK();
        node = LIST_RemoveFirst(&kernel.pending);               /* Get the next pending thread */
        RELEASEINTERRUPTLOCK();
    }
       
    /* Process each of the blocked threads by checking
    for any timeouts. The threads are sorted in-order
    of expiry time. */
    
    k = (kernel.ticks % CFG_BLOCKLISTS);
    
    ACQUIREINTERRUPTLOCK();
    
    node = kernel.blocked[k].first;                                         /* Get the first thread to timeout */
                
    while (node) {
        thread = node->value;
        
        if (thread->state == STATE_BLOCKED ||
            thread->state == STATE_SLEEPING) {
                
            if (thread->timeout == kernel.ticks) {                          /* Did the blocked thread timeout? */    
                
                KERNEL_SetState(thread, STATE_READY);                       /* Release the thread */
                thread->status = ERR_TIMEOUT;                               /* Indicate the thread was released from a timeout */
                thread->bobj = NULL;                                        /* Remove reference to object the thread is blocked upon */
                
                if (thread->bnode.list) {                                   /* Is the thread within a blocked thread list? */
                    LIST_Remove(thread->bnode.list, &thread->bnode);        /* Remove the thread from the blocked thread list */
                }                           
            } else {
                break;                                                      /* No more threads to check for timeout */
            }    
        } else {
            LIST_Remove(thread->pnode.list, &thread->pnode);
        }
        
        RELEASEINTERRUPTLOCK();
        ACQUIREINTERRUPTLOCK();
                
        node = kernel.blocked[k].first;                                   /* Get the next blocked thread to be processed */
    }
            
    RELEASEINTERRUPTLOCK();
    
    
    /* Process the time slices for round robin scheduling
    by checking for expiry at each priority level. */
    
    ACQUIREINTERRUPTLOCK();
    
    for (k = 1; k < PRIO_MAX; k++) {
        if (kernel.ready[k].first) {                            /* Any thread at this priority level? */
            thread = kernel.ready[k].first->value;
            
            if (thread->slice != INFINITE) {                    /* Does the running thread have a time slice? */
                if (thread->time == kernel.ticks) {             /* Is the running threads slice over? */
                    KERNEL_SetState(thread, STATE_READY);       /* Reschedule the thread to yield to other threads */
                    
                    RELEASEINTERRUPTLOCK();
                    ACQUIREINTERRUPTLOCK();
                }
            }
        }
    }
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ReleaseLock();
    KERNEL_ContextSwitch();                                     /* Possibly switch threads after all the changes */
}

/***************************************************************************************************************************************//**

    Returns the current time, in kernel ticks, from within the kernel.

    @return     The current kernel time.
    @module     kernel-core

*******************************************************************************************************************************************/
INLINE UINT32 KERNEL_Ticks(void)
{
    return kernel.ticks;
}

/*******************************************************************************************************************************************

    Places a thread into the specified state.

    @param[in]  thread      A pointer to the thread to change state.
    @param[in]  state       The new state for the given thread.

    @return     None
    @remark     Not thread or interrupt safe, must be called within active interrupt lock.
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_SetState(THREAD* thread, THREADSTATE state)
{
    THREAD* cur;
    
    
    if (thread->snode.list) {
        if (&thread->snode == kernel.ready[thread->prio].first) {           /* Check if a thread is being removed from a ready list */
            LIST_Remove(thread->snode.list, &thread->snode);                /* It is, remove it first */
            
            if (kernel.ready[thread->prio].first) {                         /* Is there a new ready thread? */
                cur = kernel.ready[thread->prio].first->value;              /* Yes, get the thread */
                cur->time = kernel.ticks + cur->slice;                      /* Calculate the end of the thread's slice */
            }
        } else {
            LIST_Remove(thread->snode.list, &thread->snode);                /* Just remove the thread from its current state list */
        }
    }
    
    thread->state = state;                                                  /* Update the thread's state */
    
    switch (thread->state) {                                                /* Place into the appropriate state list */
        case STATE_READY:
            if (kernel.ready[thread->prio].count == 0) {                    /* Is this the first ready thread for its priority? */
                thread->time = kernel.ticks + thread->slice;                /* Yes, calculate its end of slice time */
            }
            
            LIST_AddLast(&kernel.ready[thread->prio],                       /* Make the thread ready to execute */
                         &thread->snode,
                         thread);
           
            if (thread->prio > kernel.prio) {                               /* Is the new thread causing a switch to a higher priority? */
                kernel.prio = thread->prio;                                 /* Yes, update the cached priority level */
            }
            break;
            
        case STATE_SLEEPING:
        case STATE_BLOCKED:
            LIST_AddLast(&kernel.pending,                                   /* Thread is being blocked, place into pending block state */
                         &thread->snode,
                         thread);
            break;
            
        case STATE_STOPPED:
        case STATE_BLOCKEDINDEFINITE:
        case STATE_MAX:
        default:                                                            /* Nothing to do for these states */
            break;
    }
}

/*******************************************************************************************************************************************

    Invokes a context switch by performing a search for the highest priority or next ready to run thread that should be executing. If a
    thread is found that is different than the current, a context switch is performed.

    @return     None
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_ContextSwitch(void)
{
    INTERRUPTLOCK lock;
    THREAD* thread;
    UINT32 k;
    
    
    ACQUIREINTERRUPTLOCK();

    if (kernel.thread == NULL) {                                /* Is the kernel running? (check for the executing thread) */
        RELEASEINTERRUPTLOCK();
        return;                                                 /* Not executing, must exit */
    }
    
    if (kernel.lock) {                                          /* Is the kernel locked from switching threads? */
        RELEASEINTERRUPTLOCK();
        return;                                                 /* Yes, unable to switch threads */
    }

    if (kernel.ready[kernel.prio].first) {                      /* Is there a thread for the cached priority level? */
        thread = kernel.ready[kernel.prio].first->value;        /* Yes, get the next ready thread */
    } else {
        for (k = kernel.thread->prio - 1; k > 0; k--) {         /* No, search for a lower priority thread */
            if (kernel.ready[k].count > 0) {
                kernel.prio = k;                                /* Found one */
                break;
            }
        }
        
        if (k == 0) {
            kernel.prio = 0;                                    /* Didn't find one, idle priority */
        }
        
        thread = kernel.ready[kernel.prio].first->value;
    }
    
    if (thread != kernel.thread) {                              /* Is the highest priority thread already running? */
        THREAD_Execute(thread);                                 /* Switch to the newly found thread */
    }

    RELEASEINTERRUPTLOCK();
}

/*******************************************************************************************************************************************

    A handler called upon when a thread completes execution and returns from its process function. This handler terminates the thread to
    ensure clean-up of the thread.

    @return     None
    @remark     NOT to be called directly from code.
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_OnThreadExit(void)
{
    THREAD_Terminate(kernel.thread);                            /* Perform any clean-up */
}

/***************************************************************************************************************************************//**

    Acquires a lock that is used to guard the thread lists.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been acquired.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been initialized (created). 
     ERR_TIMEOUT            | The specified amount of time has elapsed prior to acquiring lock.
     ERR_DESTROYED          | The operation failed because the mutex has been destroyed.
     ERR_ABORTED            | The caller is unable to block because it has been aborted.

    @module     internal

*******************************************************************************************************************************************/
STATUS KERNEL_AcquireLock(void)
{
    return MUTEX_Acquire(&kernel.mutex, INFINITE);
}

/***************************************************************************************************************************************//**

    Releases a previously acquired lock on the thread lists.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been released.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).   
     ERR_NOTINITIALIZED     | The specified mutex has not been initialized (created).
     ERR_NOTOWNER           | The caller is not the owner, but only the owner is allowed to release the mutex.

    @module     internal

*******************************************************************************************************************************************/
STATUS KERNEL_ReleaseLock(void)
{
    return MUTEX_Release(&kernel.mutex);
}

/***************************************************************************************************************************************//**

    Blocks the calling thread upon a specified object.

    @param[in]  obj         A pointer to the object that the thread is blocking upon.
    @param[in]  list        A pointer to a list of blocked threads that the calling thread will be added in.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, that the calling thread should be blocked. Must not be zero. Use 
                            INFINITE to block indefinitely without a timeout.

    @return     None.
    @remark     Not thread safe. Must be called within an interrupt lock.
    @module     internal

*******************************************************************************************************************************************/
STATUS KERNEL_Block(void* obj, LIST* list, UINT32 timeout)
{
    if (kernel.thread->flags & FLAG_THREADABORTED) {                    /* Has the calling thread been aborted? */
        kernel.thread->status = ERR_ABORTED;                            /* Yes, cannot block an aborted thread */
        return ERR_ABORTED;
    }

    kernel.thread->bobj = obj;                                          /* Keep a reference to the object the thread is blocked upon */
    
    if (timeout == INFINITE) {
        KERNEL_SetState(kernel.thread, STATE_BLOCKEDINDEFINITE);        /* Place thread into a wait indefinitely list */
    } else { 
        kernel.thread->time = timeout;                                  /* Set the timeout for the blocked thread */
        KERNEL_SetState(kernel.thread, STATE_BLOCKED);                  /* Move thread to waiting list */
    }
    
    kernel.thread->status = ERR_BLOCKFAILED;                            /* Provide a default return value */
    
    if (list == NULL) {
        return SUCCESS;
    }
    
    if (list->first) {                                                  /* Is there already a thread blocked upon this object? */
        if (kernel.thread->prio >                                       /* Yes, is this thread higher priority? */
            ((THREAD*)list->first->value)->prio) {
            LIST_AddFirst(list,                                         /* Yes, put this thread in line ahead of previous thread */
                          &kernel.thread->bnode,
                          kernel.thread);
            return SUCCESS;
        }
    }

    LIST_AddLast(list,                                                  /* Just put in as first come first serve order */
                 &kernel.thread->bnode,
                 kernel.thread);
    
    return SUCCESS;
}
                                   
/***************************************************************************************************************************************//**

    Removes and releases the first thread from a list of blocked threads.

    @param[in]  waiters     A pointer to the list of waiters.
    @param[in]  result      The result code to be given to the released thread.

    @return     A pointer to the thread that has been released, if any, or NULL if no thread was released.
    @remark     Not thread safe. Must be called within a critical section.
    @module     internal

*******************************************************************************************************************************************/
THREAD* KERNEL_ReleaseOne(LIST* threads, STATUS result)
{
    INTERRUPTLOCK lock;
    NODE* node;
  	THREAD* thread;


    ACQUIREINTERRUPTLOCK();
    
    node = LIST_RemoveFirst(threads);                       /* Attempt to remove the first thread from the given list */
    if (node) {                                             /* Was a node removed? */
        thread = node->value;                               /* Get the thread that represents the node */
        
        KERNEL_SetState(thread, STATE_READY);               /* Make the removed thread ready to execute */
  
        thread->bobj = NULL;                                /* Clear the object the thread is blocked upon */
        thread->status = result;                            /* Provide the waiting result code */
        
        RELEASEINTERRUPTLOCK();
        return thread;                                      /* Provide a reference to the released thread */
    }
    
    RELEASEINTERRUPTLOCK();
    return NULL;                                            /* No waiting thread to be released */
}

/***************************************************************************************************************************************//**

    Removes and releases all threads from a specified list of blocked threads.

    @param[in]  threads     A pointer to the list of blocked threads.
    @param[in]  result      The result code to be given to each of the released threads.

    @return     None.
    @remark     Not thread safe. Must be called within a critical section.
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_ReleaseAll(LIST* threads, STATUS result)
{
    INTERRUPTLOCK lock;
    NODE* node;
    THREAD* thread;
    
    
    ACQUIREINTERRUPTLOCK();
    
    LIST_Foreach(node, threads) {                       /* Go through each of the blocked threads */
        thread = (THREAD*)node->value;
        
        KERNEL_SetState(thread, STATE_READY);           /* Change thread to the ready state */
        thread->bobj = NULL;                            /* Clear the reference to the object being blocked upon */
        thread->status = result;                        /* Provide the blocking result code */
    }
  	
    LIST_Clear(threads);                                /* All threads were released, clear the entire list */
    
    RELEASEINTERRUPTLOCK();
    KERNEL_ContextSwitch();                             /* Possibly switch threads */
}

/***************************************************************************************************************************************//**

    Handler for a callback that occurs upon each context switch within the kernel.

    @param[in]  prev        A pointer to the thread that was previously executing.
    @param[in]  next        A pointer to the thread that is next to execute.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
void KERNEL_OnContextSwitch(void)
{
#if (CFG_STATISTICS)
    STOPWATCH_Stop(&kernel.thread->stats.runsw);        /* Stop accumulating execution time for the previous running thread */
    STOPWATCH_Start(&kernel.next->stats.runsw);         /* Start/continue accumulating execution time for the next thread */

    ++kernel_stats.ctxcnt;                              /* Keep a count of total number of thread context switches performed */
#endif

#if (CFG_HOOKCONTEXTSWITCH)
    HOOK_ContextSwitch(kernel.thread, kernel.next);     /* Call an application-defined hook function for the context switch event */
#endif
}
