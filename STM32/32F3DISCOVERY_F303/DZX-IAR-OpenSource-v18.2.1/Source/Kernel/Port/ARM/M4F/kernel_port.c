/*******************************************************************************************************************************************

    DZX | KERNEL PORT | ARM CORTEX M4F                                                                                    VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides specific functionality for the ARM Cortex-M4F (hardware floating point) architecture.

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
#include "Kernel/kernel_core.h"
#include "mcu_kernel.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
void KERNEL_HardFault(UINT32 stk);
void HardFault_Handler(void);
       
/***************************************************************************************************************************************//**

    Performs low-level initialization required for boot-up of the kernel. This is called before static memory initialization and therefore 
    should not depend upon any initial values.

    Optionally calls an application-defined hook function if configured using 'CFG_HOOKBOOT'.

    @return     None.
    @remark     Not to be called from user code.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
void KERNEL_Boot(void)
{
    MCU_Boot();                                                 /* Call MCU peripheral driver boot-up function */
    
    REGBITS_CPACR.CP10 = 3;                                     /* Enable FPU */
    REGBITS_CPACR.CP11 = 3;

    REG_VTOR = CFG_RESETVECTORADDRESS;                          /* Set the location of the vector table */     
    
    REGBITS_SHPR2.PRI14 = 0xFF;                                 /* Set the PendSV interrupt as the lowest possible priority */
    REGBITS_SHPR2.PRI15 = 0xFF;                                 /* Set the SysTick interrupt as the lowest possible priority */
    
    REG_DEMCR |= (1 << 24);                                     /* Enable the trace clock (used for high resolution timestamping) */
    REG_DWTCYCCNT = 0;
    REG_DWTCTRL |= 1;

#if (CFG_HOOKBOOT)
    HOOK_Boot();                                                /* Call an application-defined hook function */
#endif
}

/***************************************************************************************************************************************//**

    Starts execution of the kernel by launching the first thread process.
        
    @param[in]  proc        The process function for the first thread to be executed.
    @param[in]  arg         An optional argument to be passed to the process function. Can be NULL.

    @return     None.
    @remark     Not to be called from user code.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
void KERNEL_ExecutePort(THREADSTART proc, void* arg)
{
    ALIGNED(8) static BYTE ISRStack[CFG_ISRSTACKSIZE];                     /**< Stack memory for interrupt service routines (ISR) */
    UINT32 msp;
    UINT32 psp;
    
    
    
    REG_STRELOAD = (MCU_ClockHz() / CFG_TICKSPERSECOND);        /* Set the rate for the SysTick interrupt. Once per time tick */
    REG_STCTRL = 0x7;                                           /* Start the timer, enable interrupt, and use system clock for input */
    
#if (CFG_STACKFILLING)
    memset(ISRStack, CFG_STACKFILLVALUE, CFG_ISRSTACKSIZE);     /* Initialize the ISR stack if performing usage checks */
#endif

    msp = (UINT32)STACKEND(ISRStack, CFG_ISRSTACKSIZE);         /* Calculate the main stack pointer (kernel and interrupts) */
    psp = (UINT32)kernel.thread->ctx.SP + 0x40;                 /* Calculate the process stack pointer (threads) */
    
#ifdef __CC_ARM
    __asm { MSR MSP, msp };                                     /* Initialize the main stack pointer */
    __asm { ISB };
    
    __asm { MSR PSP, psp };                                     /* Initialize the process stack pointer */
    __asm { ISB };
    
    __asm { MSR CONTROL, #2 };                                  /* Configure to use the main stack pointer */
    __asm { ISB };
#else
    __asm volatile("MSR MSP, %0" :: "r" (msp));                 /* Initialize the main stack pointer */
    __asm volatile("ISB");
    
    __asm volatile("MSR PSP, %0" :: "r" (psp));                 /* Initialize the process stack pointer */
    __asm volatile("ISB");
    
    __asm volatile("MSR CONTROL, %0" :: "r" (0x2));             /* Configure to use the process stack pointer */
    __asm volatile("ISB");
#endif
    
    proc(arg);
}

/***************************************************************************************************************************************//**

    Assigns stack memory for a new thread within the kernel.

    @param[in]  thread      A pointer to the new thread to receive the specified stack memory.
    @param[in]  stk         A pointer to the stack memory to be assigned to the given thread.
    @param[in]  stksize     The size in bytes of the specified stack memory.

    @return

    Status Code             | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The stack memory was successfully assigned and initialized.

    @remark     Not to be called directly from user code.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
STATUS THREAD_AssignStack(THREAD* thread, void* stk, UINT32 stksize)
{
    thread->stk = stk;                                                  /* Assign thread stack memory */
    thread->stksize = stksize;
    
    if (thread->stksize % STACKALIGNMENT) {                             /* Is the size for the stack properly aligned? */
        thread->stksize -= (thread->stksize % STACKALIGNMENT);          /* Shrink the stack to force desired alignment */
    }
    
    if ((UINT32)thread->stk % STACKALIGNMENT) {                         /* Is the stack address properly aligned? */
        thread->stk = (void*)((UINT32)thread->stk +                     /* Move the stack to force alignment */
            (STACKALIGNMENT - ((UINT32)thread->stk % STACKALIGNMENT)));
        
        thread->stksize -= STACKALIGNMENT;                              /* Give up some of the stack since alignment had to be fixed */
    }
    
#if (CFG_STACKFILLING)
    memset(thread->stk, CFG_STACKFILLVALUE, thread->stksize);           /* Initialize with known values for depth checking purposes */
#endif
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the maximum amount of space, in bytes, that has been used within the stack memory of a thread.

    @param[in]  thread      A pointer to the target thread.

    @return     The maximum number of bytes of stack memory that has been used by the given thread.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
#if (CFG_STACKFILLING)
UINT32 THREAD_StackUsage(THREAD* thread)
{
    UINT32 k;
    
    
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return 0;
    }
#endif
    
    for (k = 0; k < (thread->stksize >> 2); k++) {                  /* Go through each 32-bit word of the stack */
        if (((UINT32*)thread->stk)[k] != CFG_STACKFILLVALUE) {      /* Look for the fill value being changed */
            return (thread->stksize - (k * sizeof(UINT32)));        /* Found first entry that has been touched, report level */
        }
    }
    
    return 0;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether a thread has overflowed its stack memory.

    @param[in]  thread      A pointer to the target thread.

    @return     TRUE if the thread has accessed beyond its configured stack memory; otherwise FALSE.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
BOOLEAN THREAD_StackOverflow(THREAD* thread)
{
#if (CFG_NULLCHECKING)
    if (thread == NULL) {
        return FALSE;
    }
#endif
  
    if (((UINT32*)thread->stk)[0] != CFG_STACKFILLVALUE) {      /* Check if the last location has been touched */
        return TRUE;
    }
       
    return FALSE;
}
#endif /* CFG_STACKFILLING */

/***************************************************************************************************************************************//**

    Creates and initializes the platform specific context for a thread.

    @param[in]  thread      A pointer to the thread to be initialized.
    @param[in]  proc        The process function for the thread.
    @param[in]  arg         An optional argument to be passed to the process function. Can be NULL.

    @return

    Status Code             | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The thread's context was successfully initialized.

    @remark     Not to be called directly from user code.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
STATUS THREAD_InitContext(THREAD* thread, THREADSTART proc, void* arg)
{
    STACKFRAME* frame;
    UINT32 base;
    
    
    base = (UINT32)thread->stk + thread->stksize - sizeof(UINT32);  /* Calc the base address for the thread stack */
    
    
    /* Initialize the stack pointer for the thread.
    (stack pointer = the end of the thread's stack minus the total amount of stack used when switching the thread) */
    
    thread->ctx.SP = (void*)(base - 0x40);

    /* Get a stack frame reference within the stack memory to initialize the thread's stack */
    
    frame = (STACKFRAME*)((UINT32)thread->stk + thread->stksize - sizeof(STACKFRAME));

    frame->EXCR = 0xFFFFFFFD;                                       /* Initialize the registers for the thread */
    frame->R0 = (UINT32)arg;                                
    frame->R1 = 0;
    frame->R2 = 0;
    frame->R3 = 0;
    frame->R12 = 0;
    frame->PC = (UINT32)proc;                                       /* Assign the start (entry) function for the thread */
    frame->LR = (UINT32)KERNEL_OnThreadExit;                        /* Assign the function to be called upon exit of the thread */
    frame->PSR = 0x01000000;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Acquires an interrupt lock by disabling all maskable interrupts.

    @return     The lock that was acquired.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
INTERRUPTLOCK KERNEL_AcquireInterruptLock(void)
{
    INTERRUPTLOCK lock;

    
#ifdef __CC_ARM
    __asm { MRS lock, PRIMASK };                                /* Capture the state of the interrupt mask */ 
    __asm { CPSID I };                                          /* Mask interrupts */
#else
    __asm volatile("MRS %0, PRIMASK" : "=r" (lock));            /* Capture the state of the interrupt mask */
    __asm volatile("CPSID I");                                  /* Mask interrupts */
#endif
    
#if (CFG_LOCKSTATISTICS) 
    if (lock_stats.isr.nesting == 0) {                          /* Is the lock just now being acquired (no nesting)? */
        STOPWATCH_Restart(&lock_stats.isr.watch);               /* Yes, start the time measurement */
    }
    lock_stats.isr.nesting++;                                   /* Keep track of lock nesting */
#endif
    
    return lock;
}

/***************************************************************************************************************************************//**

    Releases an interrupt lock by restoring the interrupt mask state.

    @param[in]  lock        The lock to be released.

    @return     None.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
void KERNEL_ReleaseInterruptLock(INTERRUPTLOCK lock)
{
#if (CFG_STATISTICS) && (CFG_LOCKSTATISTICS) 
    UINT32 elapsed;
#endif
    
    
    (void)lock;                                                         /* Avoid unused warning */
    
#if (CFG_LOCKSTATISTICS) 
    lock_stats.isr.nesting--;                                           /* Exiting the lock */
    if (lock_stats.isr.nesting == 0) {                                  /* No further nesting to unwind? */
        elapsed = STOPWATCH_Elapsed(&lock_stats.isr.watch);             /* Calculate how long the lock was active */
        if (elapsed > lock_stats.isr.max) {                             /* Was this instance the longest yet? */
            lock_stats.isr.max = elapsed;                               /* Keep record of the longest */
        }
    }
#endif
    
#ifdef __CC_ARM
    __asm { MSR PRIMASK, lock };                                        /* Restore the interrupt mask */
    __asm { ISB };
#else
    __asm volatile("MSR PRIMASK, %0" :: "r" (lock));                    /* Restore the interrupt mask */
    __asm volatile("ISB");
#endif
}

/***************************************************************************************************************************************//**

    Handler for the HardFault exception.

    @return     None.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
#ifdef __CC_ARM
__asm void HardFault_Handler(void)
{
    IMPORT KERNEL_HardFault
    PRESERVE8
    
    TST LR, #4                                                  /* Check which stack was in-use when the exception occurred */
    ITE EQ
    MRSEQ R0, MSP                                               /* Capture the main stack pointer */
    MRSNE R0, PSP                                               /* Capture the process stack pointer */
    
    BL KERNEL_HardFault                                         /* Call the c-handler for the fault */
}
#else
void HardFault_Handler(void)
{
    volatile UINT32 stk = 0;
    
    
    /* Capture the stack of when the fault occurred */
    __asm volatile("TST LR, #4 \n"
                   "ITE EQ \n"
                   "MRSEQ %0, MSP \n"
                   "MRSNE %0, PSP \n" : "=r" (stk));  

    KERNEL_HardFault(stk);
}
#endif

/***************************************************************************************************************************************//**

    An additional handler for the HardFault exception.

    @param[in]  stk         The address of the stack pointer when the exception occurred.

    @return     None.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
void KERNEL_HardFault(UINT32 stk)
{
    static volatile HARDFAULTINFO HardFault;

    
    (void)HardFault;

    HardFault.registers = (STACKFRAME*)stk;                     /* Capture the register dump */
    HardFault.cfsr = REGBITS_CFSR;                              /* Capture the state of the CFSR */
    
#if 0
    printf("Hard Fault Exception\n");
    
    if (kernel.thread) {
        printf("At address 0x%08X on thread '%s' (0x%08X) \n", HardFault.registers->PC, kernel.thread->name, kernel.thread);
    } else {
        printf("At address 0x%08X\n", HardFault.registers->PC);
    }
    
    printf("\nRegister Dump\n");
    printf("R0  = 0x%08X \n", HardFault.registers->R0);
    printf("R1  = 0x%08X \n", HardFault.registers->R1);
    printf("R2  = 0x%08X \n", HardFault.registers->R2);
    printf("R3  = 0x%08X \n", HardFault.registers->R3);
    printf("R12 = 0x%08X \n", HardFault.registers->R12);
    printf("LR  = 0x%08X \n", HardFault.registers->LR);
    printf("PC  = 0x%08X \n", HardFault.registers->PC);
    printf("PSR = 0x%08X \n", HardFault.registers->PSR);
#endif
    
    __asm volatile("BKPT #0");
}

/***************************************************************************************************************************************//**

    Executes a thread by invoking the context switch using the PendSV exception.

    @param[in]  thread      A pointer to the thread to begin execution.

    @return     None
    @remark     Not to be called direct from user code.
    @remark     Must be called from within a critical section.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
INLINE void THREAD_Execute(THREAD* thread)
{ 
    kernel.next = thread;                                       /* Assign the next thread (used by PendSV) to be executed */
    REG_ICSR = BIT(28);                                         /* Invoke a context switch by raising the PendSV exception */
}

/***************************************************************************************************************************************//**

    Executes an application at the specified address.

    @param[in]  address     The starting address for the application to be executed.

    @return     Does not return as it launches the specified application.
    @module     kernel-port-cm4f

*******************************************************************************************************************************************/
#ifdef __CC_ARM
__asm void KERNEL_ExecuteApp(UINT32 address)
{
    LDR SP, [R0, #0]
    ISB
    LDR PC, [R0, #4]
}
#else
void KERNEL_ExecuteApp(UINT32 address)
{
    __asm volatile("LDR SP, [%0, #0]" :: "r" (address));
    __asm volatile("ISB");
    __asm volatile("LDR PC, [%0, #4]" :: "r" (address));
}
#endif
