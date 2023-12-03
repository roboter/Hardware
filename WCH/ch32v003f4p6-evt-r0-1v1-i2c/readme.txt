microcontroller: ch32v003f4p6
board: ch32v003f4p6-evt-r0-1v1
microcontroller manufacturer: wch
board manufacturer: wch
icon: icons/folder/closed/blinky.png
link: https://embeetle.com/#supported-hardware/wch/boards/ch32v003f4p6-evt-r0-1v1


info:
This project was originally a WCH Eclipse sample project which we've slightly
modified to fit the typical Embeetle project structure.

The original resources can be found on:
http://www.wch-ic.com/products/CH32V003.html

After unzipping this ZIP-folder:
  - The general source code is copied from: 'CH32V003EVT/EVT/EXAM/SRC/'.
  - The sample projects can be found in folders like: 'CH32V003EVT/EVT/EXAM/GPIO/GPIO_Toggle/User/'.
  - The linkerscript is found at: 'CH32V003EVT/EVT/EXAM/SRC/Ld/Link.ld'.

SAMPLE PROJECTS
---------------

Samples
   |-- ADC
   |      |-- ADC_DMA: ADC DMA sampling routines
   |      |-- AnalogWatchdog: analog watchdog routine
   |      |-- Auto_Injection: automatic injection mode routine
   |      |-- Discontinuous_mode: discontinuous mode routine
   |      |-- ExtLines_Trigger: external lines trigger ADC conversion routine
   |-- DMA
   |      |-- DMA_MEM2MEM: Memory to memory mode routine
   |      |-- DMA_MEM2PERIP: Memory to peripheral mode, and peripheral to memory mode routine, see peripheral sub-routines
   |-- EXTI
   |      |-- EXTI0: external interrupt line routine
   |-- FLASH
   |      |-- FLASH_Program: FLASH erase/read/write, and fast programming  
   |-- GPIO 
   |      |-- GPIO_Toggle: GPIO routine 
   |-- I2C
   |      |-- I2C_7bit_Mode: 7-bit addressing mode, master/slave mode, transceiver routine
   |      |-- I2C_10bit_Mode: 10-bit addressing mode, master/slave mode transceiver routine
   |      |-- I2C_DMA: I2C DMA, master/slave mode transceiver routine
   |      |-- I2C_EEPROM: I2C interface routine to operate EEPROM peripheral 
   |      |-- I2C_PEC: PEC error check, master/slave mode transceiver routine 
   |-- IAP
   |      |-- V00x_APP: APP go to IAP routine  
   |-- IWDG
   |      |-- IWDG: independent watchdog routine
   |-- OPA 
   |      |-- OPA: OPA as voltage follower output routine 
   |-- PWR
   |      |-- Sleep_Mode: low power, sleep mode routine
   |      |-- Standby_Mode: low power, standby mode routine
   |-- RCC
   |      |-- Get_CLK: Get system-HCLK-AHB1-AHB2 clock routine   
   |      |-- MCO: MCO pin clock output routine      
   |-- SPI
   |      |-- 1Lines_half-duplex: single wire half duplex mode, master/slave mode, data transceiver
   |      |-- 2Lines_FullDuplex: two-wire full duplex mode, master/slave mode, data transceiver
   |      |-- FullDuplex_HardNSS: Hardware NSS mode, master/slave mode, data transceiver
   |      |-- SPI_CRC: CRC error check and master/slave mode transceiver routine
   |      |-- SPI_DMA: SPI DMA, master/slave mode transceiver routine
   |-- SYSTICK
   |      |-- SYSTICK_Interrupt: systick interrupt routine  
   |-- TIM
   |      |-- Clock_Select: clock source selection routine
   |      |-- ComplementaryOutput_DeadTime: complementary output and deadband insertion mode routines
   |      |-- ExtTrigger_Start_Two_Timer: external trigger routines to start two timers synchronously
   |      |-- Input_Capture: input capture routine
   |      |-- One_Pulse: single pulse output routine
   |      |-- Output_Compare_Mode: output comparison mode routine
   |      |-- PWM_Output: PWM output routine
   |      |-- Synchro_ExtTrigger: slave mode routine, including reset mode, gating mode and trigger mode
   |      |-- Synchro_Timer: timer synchronization mode
   |      |-- TIM_DMA: timer DMA routines
   |-- USART
   |      |-- USART_DMA: USART DMA, master/slave mode transceiver routine
   |      |-- USART_HalfDuplex: single wire half duplex mode, master/slave mode transceiver routine
   |      |-- USART_HardwareFlowControl: hardware flow control mode, master/slave mode, transceiver routine
   |      |-- USART_Interrupt: USART interrupt routine, master/slave mode transceiver routine
   |      |-- USART_MultiProcessorCommunication: multiprocessor communication mode routine
   |      |-- USART_Polling: polling transceiver mode, master/slave transceiver routine
   |      |-- USART_Printf: USART Print debugging routine
   |      |-- USART_SynchronousMode: synchronous mode, master/slave mode, transceiver routine    
   |-- USART-IAP: IAP Upgrade Routine - Built-in Hex to Bin Tool and IAP Upgrade Tool  
   |-- WWDG: 
          |-- WWDG: window watchdog routine