/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
 *
 * $Revision: 28 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  KERNEL_SignalTick
        EXTERN  KERNEL_Boot
        EXTERN  IRQ_Handler
        EXTERN  PendSV_Handler
        EXTERN  __iar_program_start

        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     Reset_Handler               ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     KERNEL_SignalTick           ; SysTick Handler


        ; External Interrupts
        DCD     IRQ_Handler                 ; Watchdog timer
        DCD     IRQ_Handler                 ; Brown Out Detect
        DCD     IRQ_Handler                 ; NVMC Flash Controller
        DCD     IRQ_Handler                 ; NVMC EE Controller
        DCD     IRQ_Handler                 ; DMA Controller
        DCD     IRQ_Handler                         
        DCD     IRQ_Handler                 ; PIO0 (0:7)   
        DCD     IRQ_Handler                 ; All GPIO pin can be routed to PIN_INTx
        DCD     IRQ_Handler            
        DCD     IRQ_Handler                       
        DCD     IRQ_Handler                         
        DCD     IRQ_Handler                        
        DCD     IRQ_Handler
        DCD     IRQ_Handler
        DCD     IRQ_Handler                       
        DCD     IRQ_Handler                 ; RIT Timer
        DCD     IRQ_Handler                 ; SCT Timer0
        DCD     IRQ_Handler                 ; SCT Timer1
        DCD     IRQ_Handler                 ; SCT Timer2
        DCD     IRQ_Handler                 ; SCT Timer3
        
        DCD     IRQ_Handler                 ; MRT timer
        DCD     IRQ_Handler                 ; MIN UART0
        DCD     IRQ_Handler                 ; MIN UART1
        DCD     IRQ_Handler                 ; MIN UART2
        DCD     IRQ_Handler                 ; BI2C
        DCD     IRQ_Handler                 ; LSPI0 
        DCD     IRQ_Handler                 ; LSPI1 
        DCD     IRQ_Handler                 ; CAN 
        DCD     IRQ_Handler                 ; USB IRQ
        DCD     IRQ_Handler                 ; USB FIQ
        DCD     IRQ_Handler                 ; USB wake up
        DCD     IRQ_Handler                 ; ADC0 SEQA
        DCD     IRQ_Handler                 ; ADC0 SEQB
        DCD     IRQ_Handler                 ; ADC0 THCMP
        DCD     IRQ_Handler                 ; ADC0 OVR
        DCD     IRQ_Handler                 ; ADC1 SEQA
        DCD     IRQ_Handler                 ; ADC1 SEQB
        DCD     IRQ_Handler                 ; ADC1 THCMP
        DCD     IRQ_Handler                 ; ADC1 OVR
        DCD     IRQ_Handler                 ; D/A Converter
        
        DCD     IRQ_Handler                 ; Comparator 0
        DCD     IRQ_Handler                 ; Comparator 1
        DCD     IRQ_Handler                 ; Comparator 2
        DCD     IRQ_Handler                 ; Comparator 3
        DCD     IRQ_Handler                 ; QEI 
        DCD     IRQ_Handler                 ; RTC Alarm 
        DCD     IRQ_Handler                 ; RTC Wake
		DCD     IRQ_Handler	                ; EZH_ARCH_B

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        SECTION .text:CODE:REORDER:NOROOT(1)

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler       

NMI_Handler:
HardFault_Handler:
SVC_Handler:
DebugMon_Handler:
Default_Handler:
        B Default_Handler
        
        
Reset_Handler

        BL KERNEL_Boot                                          /* Perform low level initialization of the kernel */
        BL __iar_program_start                                  /* Launch the application */
        B  Reset_Handler

        END
