/*******************************************************************************************************************************************

    DZX | STM32F3xx | START                                                                                               VERSION 18.2.1
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
        EXTERN  IRQ_Handler
        EXTERN  PendSV_Handler
        EXTERN  KERNEL_SignalTick
        EXTERN  KERNEL_Boot
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler               ; Reset Handler

        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     KERNEL_SignalTick           ; SysTick Handler

        DCD     IRQ_Handler                 ; Window WatchDog                                        
        DCD     IRQ_Handler                 ; PVD through EXTI Line detection                        
        DCD     IRQ_Handler                 ; Tamper and TimeStamps through the EXTI line            
        DCD     IRQ_Handler                 ; RTC Wakeup through the EXTI line                       
        DCD     IRQ_Handler                 ; FLASH                                           
        DCD     IRQ_Handler                 ; RCC                                             
        DCD     IRQ_Handler                 ; EXTI Line0                                             
        DCD     IRQ_Handler                 ; EXTI Line1                                             
        DCD     IRQ_Handler                 ; EXTI Line2                                             
        DCD     IRQ_Handler                 ; EXTI Line3                                             
        DCD     IRQ_Handler                 ; EXTI Line4                                             
        DCD     IRQ_Handler                 ; DMA1 Stream 0                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 1                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 2                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 3                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 4                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 5                                   
        DCD     IRQ_Handler                 ; DMA1 Stream 6                                   
        DCD     IRQ_Handler                 ; ADC1, ADC2 and ADC3s                            
        DCD     IRQ_Handler                 ; CAN1 TX                                                
        DCD     IRQ_Handler                 ; CAN1 RX0                                               
        DCD     IRQ_Handler                 ; CAN1 RX1                                               
        DCD     IRQ_Handler                 ; CAN1 SCE                                               
        DCD     IRQ_Handler                 ; External Line[9:5]s                                    
        DCD     IRQ_Handler                 ; TIM1 Break and TIM9                   
        DCD     IRQ_Handler                 ; TIM1 Update and TIM10                 
        DCD     IRQ_Handler                 ; TIM1 Trigger and Commutation and TIM11
        DCD     IRQ_Handler                 ; TIM1 Capture Compare                                   
        DCD     IRQ_Handler                 ; TIM2                                            
        DCD     IRQ_Handler                 ; TIM3                                            
        DCD     IRQ_Handler                 ; TIM4                                            
        DCD     IRQ_Handler                 ; I2C1 Event                                             
        DCD     IRQ_Handler                 ; I2C1 Error                                             
        DCD     IRQ_Handler                 ; I2C2 Event                                             
        DCD     IRQ_Handler                 ; I2C2 Error                                               
        DCD     IRQ_Handler                 ; SPI1                                            
        DCD     IRQ_Handler                 ; SPI2                                            
        DCD     IRQ_Handler                 ; USART1                                          
        DCD     IRQ_Handler                 ; USART2                                          
        DCD     IRQ_Handler                 ; USART3                                          
        DCD     IRQ_Handler                 ; External Line[15:10]s                                  
        DCD     IRQ_Handler                 ; RTC Alarm (A and B) through EXTI Line                  
        DCD     IRQ_Handler                 ; USB OTG FS Wakeup through EXTI line                        
        DCD     IRQ_Handler                 ; TIM8 Break and TIM12                  
        DCD     IRQ_Handler                 ; TIM8 Update and TIM13                 
        DCD     IRQ_Handler                 ; TIM8 Trigger and Commutation and TIM14
        DCD     IRQ_Handler                 ; TIM8 Capture Compare                                   
        DCD     IRQ_Handler                 ; DMA1 Stream7                                           
        DCD     IRQ_Handler                 ; FMC                                            
        DCD     IRQ_Handler                 ; SDIO                                            
        DCD     IRQ_Handler                 ; TIM5                                            
        DCD     IRQ_Handler                 ; SPI3                                            
        DCD     IRQ_Handler                 ; UART4                                           
        DCD     IRQ_Handler                 ; UART5                                           
        DCD     IRQ_Handler                 ; TIM6 and DAC1&2 underrun errors                   
        DCD     IRQ_Handler                 ; TIM7                   
        DCD     IRQ_Handler                 ; DMA2 Stream 0                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 1                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 2                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 3                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 4                                   
        DCD     IRQ_Handler                 ; Ethernet                                        
        DCD     IRQ_Handler                 ; Ethernet Wakeup through EXTI line                      
        DCD     IRQ_Handler                 ; CAN2 TX                                                
        DCD     IRQ_Handler                 ; CAN2 RX0                                               
        DCD     IRQ_Handler                 ; CAN2 RX1                                               
        DCD     IRQ_Handler                 ; CAN2 SCE                                               
        DCD     IRQ_Handler                 ; USB OTG FS                                      
        DCD     IRQ_Handler                 ; DMA2 Stream 5                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 6                                   
        DCD     IRQ_Handler                 ; DMA2 Stream 7                                   
        DCD     IRQ_Handler                 ; USART6                                           
        DCD     IRQ_Handler                 ; I2C3 event                                             
        DCD     IRQ_Handler                 ; I2C3 error                                             
        DCD     IRQ_Handler                 ; USB OTG HS End Point 1 Out                      
        DCD     IRQ_Handler                 ; USB OTG HS End Point 1 In                       
        DCD     IRQ_Handler                 ; USB OTG HS Wakeup through EXTI                         
        DCD     IRQ_Handler                 ; USB OTG HS                                      
        DCD     IRQ_Handler                 ; DCMI                                            
        DCD     IRQ_Handler                 ; CRYP crypto                                     
        DCD     IRQ_Handler                 ; Hash and Rng
        DCD     IRQ_Handler                 ; FPU
        DCD     IRQ_Handler                 ; UART7
        DCD     IRQ_Handler                 ; UART8
        DCD     IRQ_Handler                 ; SPI4
        DCD     IRQ_Handler                 ; SPI5
        DCD     IRQ_Handler                 ; SPI6
        DCD     IRQ_Handler                 ; SAI1
        DCD     IRQ_Handler                 ; LTDC
        DCD     IRQ_Handler                 ; LTDC error
        DCD     IRQ_Handler                 ; DMA2D
    
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

        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
        
Reset_Handler
        LDR     R0, =KERNEL_Boot                                
        BLX     R0                                              ; Execute kernel boot routine
        LDR     R0, =__iar_program_start                            
        BX      R0                                              ; Typical IAR start (which subsequently calls main)

        
        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB
        
        END
