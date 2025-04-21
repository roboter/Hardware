/*******************************************************************************************************************************************

    DZX | KERNEL PORT | ARM CORTEX M4F                                                                                    VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the kernel and provides specific functionality for the ARM Cortex-M4F (hardware floating point) architecture 
    for use with the IAR (EWARM) toolchain.

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

        MODULE  kernelportasm
   
        PUBLIC  PendSV_Handler
        
        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
 
PendSV_Handler

        IMPORT  kernel
        IMPORT  KERNEL_OnContextSwitch

        CPSID   I					                            ; Disable maskable interrupts during the context switch

        MRS     R0, PSP				                            ; Get the current thread's stack pointer
        
        TST     R14, #0x10                                      ; Is the current thread using the FPU?
        BEQ     SAVE_FPU                                        ; Yes, save FPU context
        BNE     SAVE_NORMAL                                     ; No, thread not using FPU
        
SAVE_FPU:
        SUBS    R0, R0, #0x40   
        VSTM    R0, {S16-S31}                                   ; Store FPU context onto the thread's stack
        
SAVE_NORMAL:
        SUBS    R0, R0, #0x24
        STM     R0, {R4-R11, R14}                               ; Store the kernel managed registers onto the thread's stack

        LDR     R1, =kernel                                     ; Store the updated stack pointer to the current thread
        LDR     R1, [R1]
        STR     R0, [R1, #0]

        STMDB   SP!, {R3}
        BL      KERNEL_OnContextSwitch                          ; Call kernel context switch routine
        LDMIA   SP!, {R3}

        LDR     R0, =kernel                                     ; Retreive the stack pointer for the next thread to execute
        LDR     R0, [R0, #4]
        LDR     R0, [R0, #0]

        LDM     R0, {R4-R11, R14}		                        ; Restore the kernel managed registers from the thread's stack
        ADDS    R0, R0, #0x24

        TST     R14, #0x10                                      ; Is the next thread to execute using the FPU?
        BEQ     RESTORE_FPU                                     ; Yes, restore the FPU context
        BNE     RESTORE_NORMAL                                  ; No, skip restoring FPU context

RESTORE_FPU:
        VLDM    R0, {S16-S31}                                   ; Restore FPU context from the thread's stack
        ADDS    R0, R0, #0x40
        
RESTORE_NORMAL:
        MSR     PSP, R0                                         ; Restore the stack pointer for the next thread to execute

        LDR     R0, =kernel	                                    ; Update the reference for the currently executing thread
        LDR     R0, [R0, #4]
        LDR     R1, =kernel
        STR     R0, [R1]

        LDR     R0, =0xE000ED04	                                ; Manually clear the PendSV exception
        MOV     R1, #0x08000000
        STR     R1, [R0]

        CPSIE   I                                               ; Re-enable maskable interrupts
        ISB                                                     ; Allow interrupts to be recognized immediately
        BX      LR
        
        END
        
