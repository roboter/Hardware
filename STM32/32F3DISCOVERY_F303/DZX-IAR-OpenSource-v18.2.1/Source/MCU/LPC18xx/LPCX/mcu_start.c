//*****************************************************************************
// LPC18xx Microcontroller Startup code for use with LPCXpresso IDE
//
// Version : 150706
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2013-2015
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will 
// automatically take precedence over these weak definitions
//
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

// Kernel functions
extern void KERNEL_Boot(void);
extern void KERNEL_SignalTick(void);
extern void IRQ_Handler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take 
// precedence over these weak definitions
//
//*****************************************************************************
void DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_EEPROM_IRQHandler(void) ALIAS(IntDefaultHandler);
void ETH_IRQHandler(void) ALIAS(IntDefaultHandler);
void SDIO_IRQHandler(void) ALIAS(IntDefaultHandler);
void LCD_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER1_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER2_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIMER3_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCPWM_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2S1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPIFI_IRQHandler(void) ALIAS(IntDefaultHandler);
void SGPIO_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO1_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO2_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO3_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO4_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO5_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO6_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO7_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void EVRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ATIMER_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void) ALIAS(IntDefaultHandler);
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
//
// External declaration for LPC MCU vector table checksum from  Linker Script
//
//*****************************************************************************
WEAK extern void __valid_user_code_checksum();

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM3
    &_vStackTop, // The initial stack pointer
    ResetISR,                               // The reset handler
    NMI_Handler,                            // The NMI handler
    HardFault_Handler,                      // The hard fault handler
    MemManage_Handler,                      // The MPU fault handler
    BusFault_Handler,                       // The bus fault handler
    UsageFault_Handler,                     // The usage fault handler
    __valid_user_code_checksum,             // LPC MCU Checksum
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    DebugMon_Handler,                       // Debug monitor handler
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    KERNEL_SignalTick,                      // The SysTick handler

    // Chip Level - LPC18
    IRQ_Handler,             // 16
    0,                          // 17
    IRQ_Handler,             // 18
    0,                          // 19
    IRQ_Handler,    // 20 ORed flash Bank A, flash Bank B, EEPROM interrupts
    IRQ_Handler,             // 21
    IRQ_Handler,            // 22
    IRQ_Handler,             // 23
    IRQ_Handler,            // 24
    IRQ_Handler,            // 25
    IRQ_Handler,             // 26
    IRQ_Handler,             // 27
    IRQ_Handler,          // 28
    IRQ_Handler,          // 29
    IRQ_Handler,          // 30
    IRQ_Handler,          // 31
    IRQ_Handler,           // 32
    IRQ_Handler,            // 33
    IRQ_Handler,            // 34
    IRQ_Handler,            // 35
    0,                          // 36
    IRQ_Handler,            // 37
    IRQ_Handler,            // 38
    IRQ_Handler,            // 39
    IRQ_Handler,           // 40
    IRQ_Handler,           // 41
    IRQ_Handler,           // 42
    IRQ_Handler,           // 43
    IRQ_Handler,            // 44
    IRQ_Handler,            // 45
    IRQ_Handler,           // 46
    IRQ_Handler,           // 47
    IRQ_Handler,           // 48
    IRQ_Handler,           // 49
    IRQ_Handler,           // 50
    IRQ_Handler,           // 51
    IRQ_Handler,           // 52
    IRQ_Handler,           // 53
    IRQ_Handler,           // 54
    IRQ_Handler,           // 55
    IRQ_Handler,           // 56
    IRQ_Handler,           // 57
    IRQ_Handler,            // 58
    IRQ_Handler,            // 59
    0,                          // 60
    0,                          // 61
    IRQ_Handler,          // 62
    IRQ_Handler,             // 63
    0,                          // 64
    IRQ_Handler,             // 65
    0,                          // 66
    IRQ_Handler,            // 67
    IRQ_Handler,             // 68
};

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//
//*****************************************************************************
void
ResetISR(void) {

// *************************************************************
// The following conditional block of code manually resets as
// much of the peripheral set of the LPC18 as possible. This is
// done because the LPC18 does not provide a means of triggering
// a full system reset under debugger control, which can cause
// problems in certain circumstances when debugging.
//
// You can prevent this code block being included if you require
// (for example when creating a final executable which you will
// not debug) by setting the define 'DONT_RESET_ON_RESTART'.
//
#ifndef DONT_RESET_ON_RESTART

    // Disable interrupts
    __asm volatile ("cpsid i");
    // equivalent to CMSIS '__disable_irq()' function

    unsigned int *RESET_CONTROL = (unsigned int *) 0x40053100;
    // LPC_RGU->RESET_CTRL0 @ 0x40053100
    // LPC_RGU->RESET_CTRL1 @ 0x40053104
    // Note that we do not use the CMSIS register access mechanism,
    // as there is no guarantee that the project has been configured
    // to use CMSIS.

    // Write to LPC_RGU->RESET_CTRL0
    *(RESET_CONTROL+0) = 0x10DF0000;
    // GPIO_RST|AES_RST|ETHERNET_RST|SDIO_RST|DMA_RST|
    // USB1_RST|USB0_RST|LCD_RST

    // Write to LPC_RGU->RESET_CTRL1
    *(RESET_CONTROL+1) = 0x00DFF7FF;
    // CAN0_RST|CAN1_RST|I2S_RST|SSP1_RST|SSP0_RST|
    // I2C1_RST|I2C0_RST|UART3_RST|UART1_RST|UART1_RST|UART0_RST|
    // DAC_RST|ADC1_RST|ADC0_RST|QEI_RST|MOTOCONPWM_RST|SCT_RST|
    // RITIMER_RST|TIMER3_RST|TIMER2_RST|TIMER1_RST|TIMER0_RST

    // Clear all pending interrupts in the NVIC
    volatile unsigned int *NVIC_ICPR = (unsigned int *) 0xE000E280;
    unsigned int irqpendloop;
    for (irqpendloop = 0; irqpendloop < 8; irqpendloop++) {
        *(NVIC_ICPR+irqpendloop)= 0xFFFFFFFF;
    }

    // Reenable interrupts
    __asm volatile ("cpsie i");
    // equivalent to CMSIS '__enable_irq()' function

#endif  // ifndef DONT_RESET_ON_RESTART
// *************************************************************

    // Initialize the kernel
	KERNEL_Boot();

#if defined (__USE_LPCOPEN)
    SystemInit();
#endif

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

    // ******************************
    // Check to see if we are running the code from a non-zero
        // address (eg RAM, external flash), in which case we need
        // to modify the VTOR register to tell the CPU that the
        // vector table is located at a non-0x0 address.

    // Note that we do not use the CMSIS register access mechanism,
    // as there is no guarantee that the project has been configured
    // to use CMSIS.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        // CMSIS : SCB->VTOR = <address of vector table>
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }

#if defined (__USE_CMSIS)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop 
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void) {
    while (1) {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void) {
    while (1) {
    }
}
