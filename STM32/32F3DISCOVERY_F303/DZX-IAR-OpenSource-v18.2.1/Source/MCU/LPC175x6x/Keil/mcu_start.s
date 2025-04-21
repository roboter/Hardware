;*******************************************************************************************************************************************
;
;   DZX | LPC15x6x | START                                                                                                VERSION 18.2.1
;   ------------------------------------------------------------------------------------------------------------------------------------
;
;   This is part of the MCU peripheral drivers and provides start up code for the Keil toolchain.
;
;   ------------------------------------------------------------------------------------------------------------------------------------
;
;   GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)
;
;    This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
;    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
;
;    This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
;    following information to ensure all requirements of the license will be met:  
;    <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.
;
;   ------------------------------------------------------------------------------------------------------------------------------------
;   COPYRIGHT (C) 2018 DZX DESIGNS 
;
;******************************************************************************************************************************************/

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
			    IMPORT  KERNEL_SignalTick
				IMPORT  IRQ_Handler
				IMPORT	PendSV_Handler

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     KERNEL_SignalTick         ; SysTick Handler

                ; External Interrupts
                DCD     IRQ_Handler				; 16: Watchdog Timer
                DCD     IRQ_Handler				; 17: Timer0
                DCD     IRQ_Handler				; 18: Timer1
                DCD     IRQ_Handler				; 19: Timer2
                DCD     IRQ_Handler				; 20: Timer3
                DCD     IRQ_Handler				; 21: UART0
                DCD     IRQ_Handler				; 22: UART1
                DCD     IRQ_Handler          	; 23: UART2
                DCD     IRQ_Handler          	; 24: UART3
                DCD     IRQ_Handler           	; 25: PWM1
                DCD     IRQ_Handler           	; 26: I2C0
                DCD     IRQ_Handler           	; 27: I2C1
                DCD     IRQ_Handler           	; 28: I2C2
                DCD     IRQ_Handler          	; 29: SPIFI
                DCD     IRQ_Handler           	; 30: SSP0
                DCD     IRQ_Handler           	; 31: SSP1
                DCD     IRQ_Handler           	; 32: PLL0 Lock (Main PLL)
                DCD     IRQ_Handler            	; 33: Real Time Clock
                DCD     IRQ_Handler          	; 34: External Interrupt 0
                DCD     IRQ_Handler          	; 35: External Interrupt 1
                DCD     IRQ_Handler          	; 36: External Interrupt 2
                DCD     IRQ_Handler          	; 37: External Interrupt 3
                DCD     IRQ_Handler            	; 38: A/D Converter
                DCD     IRQ_Handler            	; 39: Brown-Out Detect
                DCD     IRQ_Handler            	; 40: USB
                DCD     IRQ_Handler            	; 41: CAN
                DCD     IRQ_Handler            	; 42: General Purpose DMA
                DCD     IRQ_Handler            	; 43: I2S
                DCD     IRQ_Handler           	; 44: Ethernet
                DCD     IRQ_Handler            	; 45: SD/MMC card I/F
                DCD     IRQ_Handler          	; 46: Motor Control PWM
                DCD     IRQ_Handler            	; 47: Quadrature Encoder Interface
                DCD     IRQ_Handler           	; 48: PLL1 Lock (USB PLL)
				DCD		IRQ_Handler    			; 49: USB Activity interrupt to wakeup
				DCD		IRQ_Handler    			; 50: CAN Activity interrupt to wakeup


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
				IMPORT  KERNEL_Boot
                IMPORT  __main
				LDR     R0, =KERNEL_Boot
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
