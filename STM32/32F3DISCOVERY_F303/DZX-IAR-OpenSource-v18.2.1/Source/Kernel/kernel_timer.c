/*******************************************************************************************************************************************

    DZX | KERNEL | TIMER                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides support for timers. A timer provides the ability to execute an application-defined 
    function upon expiration of a time interval. A timer can be reset, started, stopped, or restarted at any time from any code context, 
    including from an interrupt service routine (ISR).

    Use CFG_TIMERLISTS to configure the number of running lists are maintained for sorting the timers. More lists will reduce the time
    it takes to sort the timers at the expense of memory.

    Use CFG_TIMERTHREADS to configure the number of dedicated threads that are used for calling the expiry functions. Note that if only 
    a single thread is used (CFG_TIMERTHREADS = 1) and the expiry function makes a blocking call, it is also blocking all the other 
    timer's expiry functions. Use more than one thread if making blocking calls within expiry functions.

    A timer has the resolution of the kernel tick rate. When specifying a time interval, the accuracy is +1/-0 kernel ticks as the tick 
    time is not synchronized with the starting time of a timer.

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
#include "kernel_timer.h"
#include "kernel_core.h"

/*******************************************************************************************************************************************
    PRIVATE TYPES
*******************************************************************************************************************************************/
typedef struct KERNELTIMERS {
    LIST        list;                               /**< A list of all created timers */
    LIST        pending;                            /**< A list of timers that are pending insertion or removal action */
    LIST        running[CFG_TIMERLISTS];            /**< An array of running timer lists (wheel) */
    LIST        expired;                            /**< A list of timers that have expired and are pending a callback */
    MUTEX       mutex;                              /**< A mutex to synchronize access to the timers */
    SIGNALSET   signals[CFG_TIMERTHREADS];          /**< An array of signal sets to trigger timer threads */
    THREAD      thread[CFG_TIMERTHREADS];           /**< An array of threads to process expired timers */
} KERNELTIMERS;

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static KERNELTIMERS kernel_timers;

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS TIMER_AcquireLock(void);
static STATUS TIMER_ReleaseLock(void);
static void TIMER_Insert(TIMER* timer);
static void TIMER_Thread(void* arg);

/***************************************************************************************************************************************//**

    Initializes support for kernel timers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timers have been successfully initialized.

    @remark     Not to be called directly from user code.
    @module     internal

*******************************************************************************************************************************************/
STATUS TIMER_Initialize(void)
{
    ALIGNED(8) static BYTE TimerStack[CFG_TIMERTHREADS][CFG_TIMERSTACKSIZE];    /* Allocate stack memory for the timer threads */
    STATUS status;
    UINT32 k;

    
    LIST_Init(&kernel_timers.list);                             /* Initialize the list of created timers */
    LIST_Init(&kernel_timers.pending);
    
    for (k = 0; k < CFG_TIMERLISTS; k++) {
        LIST_Init(&kernel_timers.running[k]);                   /* Initialize the lists of running timers */
    }
    
    
    status = MUTEX_Create(&kernel_timers.mutex,                 /* Create underlying mutex for locking timer lists */
                          "Timer Lock",
                          FALSE);
    
    if (status != SUCCESS) {
        return status;
    }


    LIST_Init(&kernel_timers.expired);                          /* Initialize the list of expired timers */
    
    for (k = 0; k < CFG_TIMERTHREADS; k++) {                    /* Create each of the threads for calling timer callbacks */
        
        SIGNAL_Init(&kernel_timers.signals[k]);
        
        status = THREAD_Create(&kernel_timers.thread[k],        /* Create a timer thread */
                               "Kernel Timer",
                               &TimerStack[k][0],               /* A pointer to the timer thread's stack memory */
                               CFG_TIMERSTACKSIZE,              /* The stack memory size for the thread */
                               CFG_TIMERPRIORITY);              /* The priority for the timer thread */
        
        if (status != SUCCESS) {
            return status;                                      /* Failed to create a thread. Bubble up the error. */
        }
        
        status = THREAD_Start(&kernel_timers.thread[k],         /* Start the timer thread */
                              TIMER_Thread,                     /* Timer thread entry point */
                              (void*)k);                        /* Timer thread argument (thread number) */
        
        if (status != SUCCESS) {
            return status;                                      /* Failed to execute the thread */
        }
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Creates and initializes a timer.

    @param[in]  timer       A pointer to a caller allocated timer instance to be initialized.
    @param[in]  name        A pointer to a NULL terminated string that represents the name for the timer.
    @param[in]  callback    A function that will receive a callback when the timer has expired.
    @param[in]  arg         (optional) A user defined argument object that is passed as the callback function argument. Can be NULL.
    @param[in]  interval    The amount of time, in kernel ticks, between the timer's expiration events.
    @param[in]  opt         Additional options to be applied to the timer.
     
     opt                    | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     OPT_NONE               | No options. Create without starting and one-shot mode.
     OPT_START              | Use to have the timer started.
     OPT_AUTORESET          | Use to have the timer automatically reset after each expiration.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'timer' or 'callback' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_INVALIDARGUMENT    | The specified interval must be larger than zero.
     ERR_ALREADYINITIALIZED | The specified timer has already been created and initialized.

    @module     internal

*******************************************************************************************************************************************/
STATUS TIMER_Create(TIMER* timer, const CHAR* name, TIMERCALLBACK callback, void* arg, UINT32 interval, UINT32 opt)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_ACCESSCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (callback == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (interval == 0) {
        return ERR_INVALIDARGUMENT;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (timer->node.list == &kernel_timers.list) {              /* Has the specified timer already been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_ALREADYINITIALIZED;
    }
    
    RELEASEINTERRUPTLOCK();
    
    LIST_InitNode(&timer->runnode);                             /* Initialize a node for placing the timer into a running list */
    LIST_InitNode(&timer->pendnode);
    
#if (CFG_TIMERTHREADS > 0)
    LIST_InitNode(&timer->expnode);                             /* Initialize a node for placing the timer into a list of expired timers */
#endif
    
    timer->name = name;
    timer->callback = callback;                                 /* Initialize the timer expired handler */
    timer->arg = arg;
    timer->thread = NULL;
    timer->interval = interval;                                 /* Set initial timing interval */
    timer->remainder = timer->interval;
    timer->opt = opt;                                           /* Apply caller options */
    timer->running = FALSE;
    timer->exptime = 0;                                         /* Initialize the expiration time */ 
    
#if (CFG_STATISTICS)
    timer->expcnt = 0;                                          /* Initialize runtime statistics */
    STOPWATCH_Create(&timer->watch, OPT_NONE);
    timer->latency = 0;
    timer->maxlatency = 0;
#endif
    
    TIMER_AcquireLock();

    LIST_AddLast(&kernel_timers.list, &timer->node, timer);     /* Register the timer with the kernel */

    if (opt & OPT_START) {                                      /* Should the timer be started? */
        
        ACQUIREINTERRUPTLOCK();
        timer->exptime = kernel.ticks + timer->remainder;       /* Calculate the time of expiration */
        RELEASEINTERRUPTLOCK();
        
        timer->running = TRUE;
        TIMER_Insert(timer);                                    /* Since list is guarded, insert now */
    }
    
    TIMER_ReleaseLock();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Destroys and removes a timer from the kernel.

    @param[in]  timer       A pointer to the timer to be destroyed and removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been destroyed and removed from the kernel.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_INVALIDCONTEXT     | The operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.
     ERR_ACCESSDENIED       | The specified timer is currently executing it's callback function.

    @module     kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_Destroy(TIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_ACCESSCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
    
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    
    TIMER_AcquireLock();
    
    if (timer->node.list != &kernel_timers.list) {              /* Has the specified timer been initialized? */
        TIMER_ReleaseLock();
        return ERR_NOTINITIALIZED;
    }
    
    if (timer->thread) {                                        /* Is the timer currently in a callback? */
        TIMER_ReleaseLock();
        return ERR_ACCESSDENIED;                                /* Cannot destroy a timer while it's busy in a callback */
    }
    
    timer->running = FALSE;
    
    if (timer->runnode.list) {
        LIST_Remove(timer->runnode.list, &timer->runnode);      /* Remove from the list of running timers */
    }
    
    LIST_Remove(&kernel_timers.list, &timer->node);             /* Remove from the list of created timers */
    
    ACQUIREINTERRUPTLOCK();
    LIST_Remove(&kernel_timers.pending, &timer->pendnode);      /* Remove from the pending start list */
    LIST_Remove(&kernel_timers.expired, &timer->expnode);       /* Remove from the pending expiry callback list */
    RELEASEINTERRUPTLOCK();
    
    TIMER_ReleaseLock();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets a new timing interval, in kernel ticks, for a timer.

    @param[in]  timer           A pointer to the timer to receive the new interval value.
    @param[in]  interval        The new interval value for the timer. Must be greater than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been updated with the new interval value.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_INVALIDARGUMENT    | The argument 'interval' was invalid. Must be greater than zero.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_SetInterval(TIMER* timer, UINT32 interval)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (interval == 0) {
        return ERR_INVALIDARGUMENT;
    }

    ACQUIREINTERRUPTLOCK();

    if (timer->node.list != &kernel_timers.list) {              /* Has the specified timer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    timer->interval = interval;                                 /* Assign the new timing interval value */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Acquires a synchronization lock upon the timers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been acquired.

    @module     internal

*******************************************************************************************************************************************/
static STATUS TIMER_AcquireLock(void)
{
    return MUTEX_Acquire(&kernel_timers.mutex, INFINITE);
}

/***************************************************************************************************************************************//**

    Releases a previously acquired synchronization lock upon the timers.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The lock has been released.

    @module     internal

*******************************************************************************************************************************************/
static STATUS TIMER_ReleaseLock(void)
{
    return MUTEX_Release(&kernel_timers.mutex);
}

/***************************************************************************************************************************************//**

    Starts a timer.

    @param[in]  timer       A pointer to the timer to be started.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been started.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @remark     If the timer is not expired, it will resume where it has last been stopped. Use TIMER_Restart() if starting the timer
                over with a fresh complete timing period is the desired operation.
    @module     kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_Start(TIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (timer->node.list != &kernel_timers.list) {                   
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    if (timer->running) {
        RELEASEINTERRUPTLOCK();
        return SUCCESS;                                         /* Timer is already running, nothing to do */
    }
    
    timer->running = TRUE;      
    LIST_AddLast(&kernel_timers.pending,                        /* Mark timer pending to start */
                 &timer->pendnode, 
                 timer);
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Stops a timer.

    @param[in]  timer       A pointer to the timer to be stopped.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been stopped.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @remark     The timer's remaining time interval is left unchanged.
    @module      kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_Stop(TIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (timer->node.list != &kernel_timers.list) {              /* Has the specified timer been initialized? */           
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    timer->running = FALSE;
    
    LIST_Remove(&kernel_timers.pending, &timer->pendnode);      /* Remove any pending start of the timer */
    LIST_Remove(&kernel_timers.expired, &timer->expnode);       /* Remove any pending callback for the timer */

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets a timer by giving the timer a new full time interval. This will leave the timer in it's current state.

    @param[in]  timer       A pointer to the timer to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer was reset with a full interval.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_Reset(TIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (timer->node.list != &kernel_timers.list) {              /* Has the specified timer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    timer->remainder = timer->interval;                         /* Reset the remaining time until expiration */
    LIST_Remove(&kernel_timers.expired, &timer->expnode);       /* Also remove any pending callbacks */
    
    if (timer->running) {                                       /* Was the timer previously running? */
        if (timer->pendnode.list == NULL) {
            LIST_AddLast(&kernel_timers.pending,                /* Start again by placing into pending state */
                         &timer->pendnode, 
                         timer);
        }
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets and starts a timer.

    @param[in]  timer       A pointer to the timer to be restarted.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The timer has been reset with a full interval and started.
     ERR_NULLREFERENCE      | The argument 'timer' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified timer has not been created and initialized.

    @module     kernel-timer

*******************************************************************************************************************************************/
STATUS TIMER_Restart(TIMER* timer)
{
    INTERRUPTLOCK lock;


#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (timer->node.list != &kernel_timers.list) {              /* Has the specified timer been initialized? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }

    LIST_Remove(&kernel_timers.expired, &timer->expnode);       /* Also remove any pending callbacks */
    
    timer->remainder = timer->interval;                         /* Reset the remaining time until expiration */
    timer->running = TRUE;
    
    if (timer->pendnode.list == NULL) {
        LIST_AddLast(&kernel_timers.pending,                    /* Start by placing into pending state */
                     &timer->pendnode, 
                     timer);
    }

    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a timer is currently running.

    @param[in]  timer       A pointer to the timer to be checked for running status.

    @return     TRUE if the timer is currently running; otherwise FALSE.
    @module     kernel-timer

*******************************************************************************************************************************************/
BOOLEAN TIMER_IsRunning(TIMER* timer)
{
    INTERRUPTLOCK lock;

    
#if (CFG_NULLCHECKING)
    if (timer == NULL) {
        return FALSE;
    }
#endif
    
    ACQUIREINTERRUPTLOCK();
    
    if (timer->running) {
        RELEASEINTERRUPTLOCK();
        return TRUE;
    }

    RELEASEINTERRUPTLOCK();
    return FALSE;      
}

/***************************************************************************************************************************************//**

    Inserts a timer into the list of running timers in order of expiration time.

    @param[in]  timer           A pointer to the timer to be inserted.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void TIMER_Insert(TIMER* timer)
{
    NODE* node;
    TIMER* cur;
    UINT32 ticks;
    UINT32 idx;


    if (timer->runnode.list) {
        LIST_Remove(timer->runnode.list, &timer->runnode);
    }
    
    idx = timer->exptime % CFG_TIMERLISTS;
    ticks = kernel.ticks;                                           /* Capture the current time, in kernel ticks */
    
    LIST_Foreach(node, &kernel_timers.running[idx]) {               /* Find location for the timer in order of expiration */
        cur = node->value;
        
        if ((timer->exptime - ticks) < (cur->exptime - ticks)) {    /* Will the specified timer expire prior? */
            LIST_AddBefore(&kernel_timers.running[idx],             /* Insert the timer into the list at the current location */
                           node, 
                           &timer->runnode, 
                           timer);
            return;
        } 
    }
    
    LIST_AddLast(&kernel_timers.running[idx],                       /* The timer is the furthest from expiration */
                 &timer->runnode, 
                 timer);   
}

/***************************************************************************************************************************************//**

    Performs the processing for all timers for a new system time tick.

    @return     None
    @remarks    Not to be called by user code. Called from kernel on a new system tick.
    @module     internal

*******************************************************************************************************************************************/
void TIMER_Process(void)
{
    INTERRUPTLOCK lock;
    NODE* node;
    TIMER* timer;
    UINT32 idx;
    UINT32 k;
    
    
    idx = kernel.ticks % CFG_TIMERLISTS;
    
    TIMER_AcquireLock();
    
    /* Process each of the timers that are pending to be 
    inserted into a running list (wheel). */
    
    ACQUIREINTERRUPTLOCK();
    node = LIST_RemoveFirst(&kernel_timers.pending);                /* Attempt to pop a timer pending to be started */
    RELEASEINTERRUPTLOCK();
        
    while (node) {
        timer = (TIMER*)node->value;
        
        timer->exptime = kernel.ticks + timer->remainder;           /* Calculate the expiration time */
        TIMER_Insert(timer);                                        /* Insert the timer into the running lists */

        ACQUIREINTERRUPTLOCK();
        node = LIST_RemoveFirst(&kernel_timers.pending);            /* Pop another timer pending start */
        RELEASEINTERRUPTLOCK();
    }

    
    /* Process each of the running timers */
  
    node = kernel_timers.running[idx].first;                            /* Get the next timer to expire */
    
    while (node) {
        timer = node->value;
        
        if (timer->running) {
            if (timer->exptime == kernel.ticks) {                       /* Did the timer just expire? */
                
#if (CFG_STATISTICS)
                timer->expcnt++;                                        /* Keep record of how many times this timer has expired */
#endif      
                LIST_Remove(timer->runnode.list, &timer->runnode);      /* Stop timer by removing from the running list */
                
                if (timer->opt & OPT_AUTORESET) {                       /* Automatically reset the timer? */
                    timer->exptime = kernel.ticks + timer->interval;    /* Recalculate the next expiration time */
                    TIMER_Insert(timer);                                /* Restart the timer */
                } else {
                    timer->running = FALSE;
                }
                
                ACQUIREINTERRUPTLOCK();
                
                if (timer->expnode.list == NULL && 
                    timer->thread == NULL) {                            /* Is the timer already pending a callback? */
                                           
                    LIST_AddLast(&kernel_timers.expired,                /* Enqueue the callback to be executed by the timer thread */
                                 &timer->expnode, 
                                 timer);     
#if (CFG_STATISTICS)
                    STOPWATCH_Restart(&timer->watch);                   /* Start a stopwatch to measure latency to the callback */
#endif
                }
                
                RELEASEINTERRUPTLOCK();
                
                node = kernel_timers.running[idx].first;                /* Get the next timer that is about to expire */
            } else {
                break;                                                  /* No more timers about to expire */
            }
        } else {
            LIST_Remove(&kernel_timers.running[idx],                    /* The timer has been stopped, safe to remove from list now */
                        &timer->runnode);  
            
            node = kernel_timers.running[idx].first;                    /* Get the next timer that is about to expire */
        }
    }

    if (kernel_timers.expired.first) {                                  /* Are there any expired timers to be processed? */
        for (k = 0; k < CFG_TIMERTHREADS; k++) {                        /* Go through all of the timer threads */
            SIGNAL_Set(&kernel_timers.signals[k], CFG_TIMERSIGNAL);     /* Signal the timer thread */
        }
    }
    
    TIMER_ReleaseLock();
}

/***************************************************************************************************************************************//**

    A thread function for calling timer callbacks within the context of a thread.

    @param[in]  arg         A pointer to an argument provided when the thread was created. Not used here.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void TIMER_Thread(void* arg)
{
    INTERRUPTLOCK lock;
    STATUS status;
    TIMER* timer;
    NODE* node;
    UINT32 idx;

    idx = (UINT32)arg;
    
    for (;;) {                                                          /* Forever loop */              
        
        status = SIGNAL_WaitOne(&kernel_timers.signals[idx],            /* Wait for a timer to expire */
                                CFG_TIMERSIGNAL, 
                                INFINITE);
        
        if (status == SUCCESS) {
            
            ACQUIREINTERRUPTLOCK();
            
            node = LIST_RemoveFirst(&kernel_timers.expired);            /* Attempt to retrieve an expired timer */
            
            while (node) {
                timer = node->value;                                    /* Get the timer within the node */
                timer->thread = kernel.thread;                          /* Mark the timer as busy in callback */
                RELEASEINTERRUPTLOCK();
                
#if (CFG_STATISTICS)
                timer->latency = STOPWATCH_Elapsed(&timer->watch);      /* Capture latency for getting to this timer */                
                if (timer->latency > timer->maxlatency) {
                    timer->maxlatency = timer->latency;                 /* Capture the maximum latency */
                }
#endif
                if (timer->callback) {
                    timer->callback(timer, timer->arg);                 /* Call the timer's expiry callback function */
                }
                
                ACQUIREINTERRUPTLOCK();
                timer->thread = NULL;                                   /* Indicate the callback is over */
                node = LIST_RemoveFirst(&kernel_timers.expired);        /* Attempt to get another expired timer */
            }
            
            RELEASEINTERRUPTLOCK();
        }
    }
}
