/*****************************************************************************
 * Copyright (c) 2009 Rowley Associates Limited.                             *
 *                                                                           *
 * This file may be distributed under the terms of the License Agreement     *
 * provided with this software.                                              *
 *                                                                           *
 * THIS FILE IS PROVIDED AS IS WITH NO WARRANTY OF ANY KIND, INCLUDING THE   *
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. *
 *****************************************************************************/

/*****************************************************************************
 *                           Preprocessor Definitions
 *                           ------------------------
 *
 * STARTUP_FROM_RESET
 *
 *   If defined, the program will startup from power-on/reset. If not defined
 *   the program will just loop endlessly from power-on/reset.
 *
 *   This definition is not defined by default on this target because the
 *   debugger is unable to reset this target and maintain control of it over the
 *   JTAG interface. The advantage of doing this is that it allows the debugger
 *   to reset the CPU and run programs from a known reset CPU state on each run.
 *   It also acts as a safety net if you accidently download a program in FLASH
 *   that crashes and prevents the debugger from taking control over JTAG
 *   rendering the target unusable over JTAG. The obvious disadvantage of doing
 *   this is that your application will not startup without the debugger.
 *
 *   We advise that on this target you keep STARTUP_FROM_RESET undefined whilst
 *   you are developing and only define STARTUP_FROM_RESET when development is
 *   complete.
 *
 * NO_SYSTEM_INIT
 *
 *   If defined, the SystemInit() function will NOT be called. By default 
 *   SystemInit() is called after reset to enable the clocks and memories to
 *   be initialised prior to any C startup initialisation.
 *
 *
 *****************************************************************************/

    .global reset_handler
    .extern KERNEL_Boot
    .extern KERNEL_SignalTick
    .extern IRQ_Handler
    .extern PendSV_Handler

    .syntax unified

    .section .vectors, "ax"
    .code 16
    .align 0
    .global _vectors

.macro DEFAULT_ISR_HANDLER name=
    .thumb_func
    .weak \name
\name:
1: b 1b /* endless loop */
.endm

_vectors:
    .word __stack_end__
#ifdef STARTUP_FROM_RESET
    .word reset_handler
#else
    .word reset_wait
#endif /* STARTUP_FROM_RESET */
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .word BusFault_Handler
    .word UsageFault_Handler
    .word 0 // Reserved
    .word 0 // Reserved
    .word 0 // Reserved
    .word 0 // Reserved
    .word SVC_Handler
    .word DebugMon_Handler
    .word 0 // Reserved
    .word PendSV_Handler
    .word KERNEL_SignalTick 
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler
    .word IRQ_Handler

    .section .init, "ax"
    .thumb_func

reset_handler:
    ldr sp, =__RAM_segment_end__
    ldr r0, =KERNEL_Boot
    blx r0

    b _start

    .section .text
    .thumb_func

DEFAULT_ISR_HANDLER NMI_Handler
DEFAULT_ISR_HANDLER HardFault_Handler
DEFAULT_ISR_HANDLER MemManage_Handler
DEFAULT_ISR_HANDLER BusFault_Handler
DEFAULT_ISR_HANDLER UsageFault_Handler
DEFAULT_ISR_HANDLER SVC_Handler 
DEFAULT_ISR_HANDLER DebugMon_Handler

#ifndef STARTUP_FROM_RESET
DEFAULT_ISR_HANDLER reset_wait
#endif /* STARTUP_FROM_RESET */

