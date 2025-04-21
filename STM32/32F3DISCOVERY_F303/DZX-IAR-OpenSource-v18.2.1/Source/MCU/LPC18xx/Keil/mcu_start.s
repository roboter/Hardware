;/***********************************************************************
; * $Id: startup_LPC18xx.s 6471 2011-02-16 17:13:35Z nxp27266 $
; *
; * Project: LPC18xx CMSIS Package
; *
; * Description: Cortex-M3 Core Device Startup File for the NXP LPC18xx
; *              Device Series.
; *
; * Copyright(C) 2011, NXP Semiconductor
; * All rights reserved.
; *
; *                                                      modified by KEIL
; *                                       further modified by DZX Designs
; ***********************************************************************
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * products. This software is supplied "AS IS" without any warranties.
; * NXP Semiconductors assumes no responsibility or liability for the
; * use of the software, conveys no license or title under any patent,
; * copyright, or mask work right to the product. NXP Semiconductors
; * reserves the right to make changes in the software without
; * notification. NXP Semiconductors also make no representation or
; * warranty that such application will be suitable for the specified
; * use without further testing or modification.
; **********************************************************************/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

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

Sign_Value      EQU     0x5A5A5A5A

__Vectors       DCD     __initial_sp              ; 0 Top of Stack
                DCD     Reset_Handler             ; 1 Reset Handler
                DCD     NMI_Handler               ; 2 NMI Handler
                DCD     HardFault_Handler         ; 3 Hard Fault Handler
                DCD     MemManage_Handler         ; 4 MPU Fault Handler
                DCD     BusFault_Handler          ; 5 Bus Fault Handler
                DCD     UsageFault_Handler        ; 6 Usage Fault Handler
                DCD     Sign_Value                ; 7 Reserved
                DCD     0                         ; 8 Reserved
                DCD     0                         ; 9 Reserved
                DCD     0                         ; 10 Reserved
                DCD     SVC_Handler               ; 11 SVCall Handler
                DCD     DebugMon_Handler          ; 12 Debug Monitor Handler
                DCD     0                         ; 13 Reserved
                DCD     PendSV_Handler            ; 14 PendSV Handler
                DCD     KERNEL_SignalTick           ; 15 SysTick Handler

                ; External Interrupts
                DCD     IRQ_Handler            ; 16 D/A Converter
                DCD     0                         ; 17 Reserved
                DCD     IRQ_Handler            ; 18 General Purpose DMA
                DCD     0                         ; 19 Reserved
                DCD     IRQ_Handler    ; 20 ORed flash bank A, flash bank B, EEPROM interrupt
                DCD     IRQ_Handler            ; 21 Ethernet
                DCD     IRQ_Handler           ; 22 SD/MMC
                DCD     IRQ_Handler            ; 23 LCD
                DCD     IRQ_Handler           ; 24 USB0
                DCD     IRQ_Handler           ; 25 USB1
                DCD     IRQ_Handler            ; 26 State Configurable Timer
                DCD     IRQ_Handler            ; 27 Repetitive Interrupt Timer
                DCD     IRQ_Handler         ; 28 Timer0
                DCD     IRQ_Handler         ; 29 Timer1
                DCD     IRQ_Handler         ; 30 Timer2
                DCD     IRQ_Handler         ; 31 Timer3
                DCD     IRQ_Handler          ; 32 Motor Control PWM
                DCD     IRQ_Handler           ; 33 A/D Converter 0
                DCD     IRQ_Handler           ; 34 I2C0
                DCD     IRQ_Handler           ; 35 I2C1
                DCD     0                         ; 36 Reserved
                DCD     IRQ_Handler           ; 37 A/D Converter 1
                DCD     IRQ_Handler           ; 38 SSP0
                DCD     IRQ_Handler           ; 39 SSP1
                DCD     IRQ_Handler          ; 40 UART0
                DCD     IRQ_Handler          ; 41 UART1
                DCD     IRQ_Handler          ; 42 UART2
                DCD     IRQ_Handler          ; 43 UART3
                DCD     IRQ_Handler           ; 44 I2S0
                DCD     IRQ_Handler           ; 45 I2S1
                DCD     0                         ; 46 Reserved
                DCD     0                         ; 47 Reserved
                DCD     IRQ_Handler          ; 48 GPIO0
                DCD     IRQ_Handler          ; 49 GPIO1
                DCD     IRQ_Handler          ; 50 GPIO2
                DCD     IRQ_Handler          ; 51 GPIO3
                DCD     IRQ_Handler          ; 52 GPIO4
                DCD     IRQ_Handler          ; 53 GPIO5
                DCD     IRQ_Handler          ; 54 GPIO6
                DCD     IRQ_Handler          ; 55 GPIO7
                DCD     IRQ_Handler          ; 56 GINT0
                DCD     IRQ_Handler          ; 57 GINT1
                DCD     IRQ_Handler           ; 58 Event Router
                DCD     IRQ_Handler           ; 59 C_CAN1
                DCD     0                         ; 60 Reserved
                DCD     0                         ; 61 Reserved
                DCD     IRQ_Handler         ; 62 ATIMER
                DCD     IRQ_Handler            ; 63 RTC
                DCD     0                         ; 64 Reserved
                DCD     IRQ_Handler            ; 65 WDT
                DCD     0                         ; 66 Reserved
                DCD     IRQ_Handler           ; 67 C_CAN0
                DCD     IRQ_Handler            ; 68 QEI


;CRP address at offset 0x2FC relative to the BOOT Bank address
                IF      :LNOT::DEF:NO_CRP
                SPACE   (0x2FC - (. - __Vectors))
;                EXPORT  CRP_Key
CRP_Key         DCD     0xFFFFFFFF
;                       0xFFFFFFFF => CRP Disabled
;                       0x12345678 => CRP Level 1
;                       0x87654321 => CRP Level 2
;                       0x43218765 => CRP Level 3 (ARE YOU SURE?)
;                       0x4E697370 => NO ISP      (ARE YOU SURE?)
                ENDIF

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
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler       [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler       [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler        [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler      [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler             [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler        [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
				

Default_Handler PROC

                EXPORT  DAC_IRQHandler          [WEAK]
                EXPORT  DMA_IRQHandler          [WEAK]
                EXPORT  FLASHEEPROM_IRQHandler  [WEAK]
                EXPORT  ETH_IRQHandler          [WEAK]
                EXPORT  SDIO_IRQHandler         [WEAK]
                EXPORT  LCD_IRQHandler          [WEAK]
                EXPORT  USB0_IRQHandler         [WEAK]
                EXPORT  USB1_IRQHandler         [WEAK]
                EXPORT  SCT_IRQHandler          [WEAK]
                EXPORT  RIT_IRQHandler          [WEAK]
                EXPORT  TIMER0_IRQHandler       [WEAK]
                EXPORT  TIMER1_IRQHandler       [WEAK]
                EXPORT  TIMER2_IRQHandler       [WEAK]
                EXPORT  TIMER3_IRQHandler       [WEAK]
                EXPORT  MCPWM_IRQHandler        [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]
                EXPORT  I2C0_IRQHandler         [WEAK]
                EXPORT  I2C1_IRQHandler         [WEAK]
                EXPORT  ADC1_IRQHandler         [WEAK]
                EXPORT  SSP0_IRQHandler         [WEAK]
                EXPORT  SSP1_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler        [WEAK]
                EXPORT  UART1_IRQHandler        [WEAK]
                EXPORT  UART2_IRQHandler        [WEAK]
                EXPORT  UART3_IRQHandler        [WEAK]
                EXPORT  I2S0_IRQHandler         [WEAK]
                EXPORT  I2S1_IRQHandler         [WEAK]
                EXPORT  GPIO0_IRQHandler        [WEAK]
                EXPORT  GPIO1_IRQHandler        [WEAK]
                EXPORT  GPIO2_IRQHandler        [WEAK]
                EXPORT  GPIO3_IRQHandler        [WEAK]
                EXPORT  GPIO4_IRQHandler        [WEAK]
                EXPORT  GPIO5_IRQHandler        [WEAK]
                EXPORT  GPIO6_IRQHandler        [WEAK]
                EXPORT  GPIO7_IRQHandler        [WEAK]
                EXPORT  GINT0_IRQHandler        [WEAK]
                EXPORT  GINT1_IRQHandler        [WEAK]
                EXPORT  EVRT_IRQHandler         [WEAK]
                EXPORT  CAN1_IRQHandler         [WEAK]
                EXPORT  ATIMER_IRQHandler       [WEAK]
                EXPORT  RTC_IRQHandler          [WEAK]
                EXPORT  WDT_IRQHandler          [WEAK]
                EXPORT  CAN0_IRQHandler         [WEAK]
                EXPORT  QEI_IRQHandler          [WEAK]

DAC_IRQHandler
DMA_IRQHandler
FLASHEEPROM_IRQHandler
ETH_IRQHandler
SDIO_IRQHandler
LCD_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
ADC1_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
I2S0_IRQHandler
I2S1_IRQHandler
GPIO0_IRQHandler
GPIO1_IRQHandler
GPIO2_IRQHandler
GPIO3_IRQHandler
GPIO4_IRQHandler
GPIO5_IRQHandler
GPIO6_IRQHandler
GPIO7_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
EVRT_IRQHandler
CAN1_IRQHandler
ATIMER_IRQHandler
RTC_IRQHandler
WDT_IRQHandler
CAN0_IRQHandler
QEI_IRQHandler

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
