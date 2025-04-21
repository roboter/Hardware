/*******************************************************************************************************************************************

    DZX | LPC13x1x2x3 | START                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides start up code for the IAR (EWARM) toolchain.

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

        MODULE  ?cstartup

        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  KERNEL_SignalTick
        EXTERN  KERNEL_Boot
        EXTERN  IRQ_Handler
        EXTERN  PendSV_Handler
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c

        DATA
__vector_table
        DCD     sfe(CSTACK)             ; Top of Stack
        DCD     Reset_Handler           ; Reset Handler
        DCD     NMI_Handler             ; NMI Handler
        DCD     HardFault_Handler       ; Hard Fault Handler
        DCD     MemManage_Handler       ; MPU Fault Handler
        DCD     BusFault_Handler        ; Bus Fault Handler
        DCD     UsageFault_Handler      ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                       ; Reserved
        DCD     0                       ; Reserved
        DCD     0                       ; Reserved
        DCD     0                       ; Reserved
        DCD     SVC_Handler			    ; SVCall Handler
        DCD     DebugMon_Handler		; Debug Monitor Handler
        DCD     0						; Reserved
        DCD     PendSV_Handler			; PendSV Handler
        DCD     KERNEL_SignalTick       ; SysTick Handler
        DCD     IRQ_Handler             ; WAKE_UP0 Handler
        DCD     IRQ_Handler             ; WAKE_UP1 Handler
        DCD     IRQ_Handler         ; WAKE_UP2 Handler
        DCD     IRQ_Handler         ; WAKE_UP3 Handler
        DCD     IRQ_Handler         ; WAKE_UP4 Handler
        DCD     IRQ_Handler         ; WAKE_UP5 Handler
        DCD     IRQ_Handler         ; WAKE_UP6 Handler
        DCD     IRQ_Handler         ; WAKE_UP7 Handler
        DCD     IRQ_Handler         ; WAKE_UP8 Handler
        DCD     IRQ_Handler         ; WAKE_UP9 Handler
        DCD     IRQ_Handler        ; WAKE_UP10 Handler
        DCD     IRQ_Handler        ; WAKE_UP11 Handler
        DCD     IRQ_Handler        ; WAKE_UP12 Handler
        DCD     IRQ_Handler        ; WAKE_UP13 Handler
        DCD     IRQ_Handler        ; WAKE_UP14 Handler
        DCD     IRQ_Handler        ; WAKE_UP15 Handler
        DCD     IRQ_Handler        ; WAKE_UP16 Handler
        DCD     IRQ_Handler        ; WAKE_UP17 Handler
        DCD     IRQ_Handler        ; WAKE_UP18 Handler
        DCD     IRQ_Handler        ; WAKE_UP19 Handler
        DCD     IRQ_Handler        ; WAKE_UP20 Handler
        DCD     IRQ_Handler        ; WAKE_UP21 Handler
        DCD     IRQ_Handler        ; WAKE_UP22 Handler
        DCD     IRQ_Handler        ; WAKE_UP23 Handler
        DCD     IRQ_Handler        ; WAKE_UP24 Handler
        DCD     IRQ_Handler        ; WAKE_UP25 Handler
        DCD     IRQ_Handler        ; WAKE_UP26 Handler
        DCD     IRQ_Handler        ; WAKE_UP27 Handler
        DCD     IRQ_Handler        ; WAKE_UP28 Handler
        DCD     IRQ_Handler        ; WAKE_UP29 Handler
        DCD     IRQ_Handler        ; WAKE_UP30 Handler
        DCD     IRQ_Handler        ; WAKE_UP31 Handler
        DCD     IRQ_Handler        ; WAKE_UP32 Handler
        DCD     IRQ_Handler        ; WAKE_UP33 Handler
        DCD     IRQ_Handler        ; WAKE_UP34 Handler
        DCD     IRQ_Handler        ; WAKE_UP35 Handler
        DCD     IRQ_Handler        ; WAKE_UP36 Handler
        DCD     IRQ_Handler        ; WAKE_UP37 Handler
        DCD     IRQ_Handler        ; WAKE_UP38 Handler
        DCD     IRQ_Handler        ; WAKE_UP39 Handler
        DCD     IRQ_Handler             ; I2C0 Handler        
        DCD     IRQ_Handler           ; CT16B0 Handler
        DCD     IRQ_Handler           ; CT16B1 Handler
        DCD     IRQ_Handler           ; CT32B0 Handler
        DCD     IRQ_Handler           ; CT32B1 Handler
        DCD     IRQ_Handler             ; SSP0 Handler
        DCD     IRQ_Handler            ; UART0 Handler
        DCD     IRQ_Handler           ; USB IRQ Handler
        DCD     IRQ_Handler           ; USB FIQ Handler
        DCD     IRQ_Handler              ; ADC Handler
        DCD     IRQ_Handler              ; WDT Handler
        DCD     IRQ_Handler              ; BOD Handler
        DCD     0                           ; Reserved
        DCD     IRQ_Handler             ; PIO3 Interupt Handler
        DCD     IRQ_Handler             ; PIO2 Interupt Handler
        DCD     IRQ_Handler             ; PIO1 Interupt Handler
        DCD     IRQ_Handler             ; PIO0 Interupt Handler
        DCD     IRQ_Handler             ; SSP1 Handler


        /* Default interrupt handlers */
        PUBWEAK NMI_Handler       
        PUBWEAK HardFault_Handler 
        PUBWEAK MemManage_Handler 
        PUBWEAK BusFault_Handler  
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler       
        PUBWEAK DebugMon_Handler  
        PUBWEAK SysTick_Handler          

        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
        
NMI_Handler       
HardFault_Handler 
MemManage_Handler 
BusFault_Handler  
UsageFault_Handler
SVC_Handler       
DebugMon_Handler    
SysTick_Handler   
Default_Handler          
        B Default_Handler 
        
Reset_Handler

        BL KERNEL_Boot                                          /* Perform low level initialization of the kernel */
        BL __iar_program_start                                  /* Launch the application */
        B  Reset_Handler
        
        BX      LR
        
        END
