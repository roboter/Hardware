/*******************************************************************************************************************************************

    DZX | LPC43xx | START                                                                                                 VERSION 18.2.1
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
        DCD     IRQ_Handler				; Watchdog Handler
        DCD     IRQ_Handler				; TIMER0 Handler
        DCD     IRQ_Handler				; TIMER1 Handler
        DCD     IRQ_Handler				; TIMER2 Handler
        DCD     IRQ_Handler				; TIMER3 Handler
        DCD     IRQ_Handler				; UART0 Handler
        DCD     IRQ_Handler				; UART1 Handler
        DCD     IRQ_Handler				; UART2 Handler
        DCD     IRQ_Handler				; UART3 Handler
        DCD     IRQ_Handler				; PWM1 Handler
        DCD     IRQ_Handler				; I2C0 Handler
        DCD     IRQ_Handler				; I2C1 Handler
        DCD     IRQ_Handler				; I2C2 Handler
        DCD     IRQ_Handler				; SPI Handler
        DCD     IRQ_Handler				; SSP0 Handler
        DCD     IRQ_Handler				; SSP1 Handler
        DCD     IRQ_Handler				; PLL0 Handler
        DCD     IRQ_Handler				; RTC Handler
        DCD     IRQ_Handler				; EXT Interupt 0 Handler
        DCD     IRQ_Handler				; EXT Interupt 1 Handler
        DCD     IRQ_Handler				; EXT Interupt 2 Handler
        DCD     IRQ_Handler				; EXT Interupt 3 Handler
        DCD     IRQ_Handler				; ADC Handler
        DCD     IRQ_Handler				; BOD Handler
        DCD     IRQ_Handler			    ; USB Handler
        DCD     IRQ_Handler				; CAN Handler
        DCD     IRQ_Handler				; General Purpose DMA Handler
        DCD     IRQ_Handler				; I2S Handler
        DCD     IRQ_Handler			    ; Ethernet Handler
        DCD     IRQ_Handler				; Repetitive Interrupt Timer Handler
        DCD     IRQ_Handler	            ; Motor Control PWM Handler
        DCD     IRQ_Handler			    ; Quadrature Encoder Handler
        DCD     IRQ_Handler				; PLL1 Handler
        DCD	    IRQ_Handler	  	        ; USB Activity Interrupt
        DCD     IRQ_Handler	  	        ; CAN Activity Interrupt

        PUBWEAK NMI_Handler       
        PUBWEAK HardFault_Handler 
        PUBWEAK MemManage_Handler 
        PUBWEAK BusFault_Handler  
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler       
        PUBWEAK DebugMon_Handler    

        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
        
NMI_Handler       
HardFault_Handler 
MemManage_Handler 
BusFault_Handler  
UsageFault_Handler
SVC_Handler       
DebugMon_Handler
Default_Handler          
        B Default_Handler 
        
Reset_Handler

        BL KERNEL_Boot                  ; Perform low level initialization of the kernel
        BL __iar_program_start          ; Launch the application (subsequently calls main)
        B  Reset_Handler
        
        END
