/*******************************************************************************************************************************************

    DZX | LPC15xx | SYSTEM CONFIGURATION                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for system configuration.

    ------------------------------------------------------------------------------------------------------------------------------------
    COPYRIGHT (C) 2016 | DZX DESIGNS | ALL RIGHTS RESERVED                                                  PROPRIETARY AND CONFIDENTIAL 

*******************************************************************************************************************************************/
#ifndef MCU_SYSCON_H__
#define MCU_SYSCON_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define BASE_SYSCON             0x40074000

/*******************************************************************************************************************************************

    SYSMEMREMAP: System memory remap

*******************************************************************************************************************************************/
typedef struct SYSCONSYSMEMREMAPBITFIELD {
    UINT32 MAP                  :2;                             /* tbd */
    UINT32                      :30;                            /* RESERVED */
} SYSCONSYSMEMREMAPBITFIELD;

#define REG_SYSMEMREMAP         REG_32(BASE_SYSCON + 0x000)
#define REGBITS_SYSMEMREMAP     REGBITS_32(BASE_SYSCON + 0x000, SYSCONSYSMEMREMAPBITFIELD)

/*******************************************************************************************************************************************

    SYSTCKCAL: System tick counter calibration

*******************************************************************************************************************************************/
typedef struct SYSCONSYSTCKCALBITFIELD {
    UINT32 CAL                  :26;                            /* System tick timer calibration value */
    UINT32                      :6;                             /* Reserved */
} SYSCONSYSTCKCALBITFIELD;

#define REG_SYSTCKCAL           REG_32(BASE_SYSCON + 0x014)
#define REGBITS_SYSTCKCAL       REGBITS_32(BASE_SYSCON + 0x014, SYSCONSYSTCKCALBITFIELD)

/*******************************************************************************************************************************************

    NMISRC: NMI Source Control

*******************************************************************************************************************************************/
typedef struct SYSCONNMISRCBITFIELD {
    UINT32 IRQNO                :5;                             /* The IRQ number of the interrupt that acts as the Non-Maskable Interrupt (NMI) if bit 31 is 1. See Table 3 for the list of interrupt sources and their IRQ numbers. */
    UINT32                      :26;                            /* Reserved */
    UINT32 NMIEN                :1;                             /* Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by bits 4:0. */
} SYSCONNMISRCBITFIELD;

#define REG_NMISRC              REG_32(BASE_SYSCON + 0x01C)
#define REGBITS_NMISRC          REGBITS_32(BASE_SYSCON + 0x01C, SYSCONNMISRCBITFIELD)

/*******************************************************************************************************************************************

    SYSRSTSTAT: System reset status register

*******************************************************************************************************************************************/
typedef struct SYSCONSYSRSTSTATBITFIELD {
    UINT32 POR                  :1;                             /* POR reset status */
    UINT32 EXTRST               :1;                             /* Status of the external RESET pin. External reset status. */
    UINT32 WDT                  :1;                             /* Status of the Watchdog reset */
    UINT32 BOD                  :1;                             /* Status of the Brown-out detect reset */
    UINT32 SYSRST               :1;                             /* Status of the software system reset */
    UINT32                      :27;                            /* Reserved */
} SYSCONSYSRSTSTATBITFIELD;

#define REG_SYSRSTSTAT          REG_32(BASE_SYSCON + 0x040)
#define REGBITS_SYSRSTSTAT      REGBITS_32(BASE_SYSCON + 0x040, SYSCONSYSRSTSTATBITFIELD)

/*******************************************************************************************************************************************

    PRESETCTRL0: Peripheral reset control 0

*******************************************************************************************************************************************/
typedef struct SYSCONPRESETCTRL0BITFIELD {
    UINT32                      :7;                             /* Reserved */
    UINT32 FLASH_RST            :1;                             /* Flash reset control */
    UINT32 FMC_RST              :1;                             /* FMC reset control FMC? Is this the flash controller? */
    UINT32 EEPROM_RST           :1;                             /* EEPROM reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 PMUX_RST             :1;                             /* Pin mux reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 IOCON_RST            :1;                             /* IOCON reset control */
    UINT32 GPIO0_RST            :1;                             /* GPIO0 reset control */
    UINT32 GPIO1_RST            :1;                             /* GPIO1 reset control */
    UINT32 GPIO2_RST            :1;                             /* GPIO2 reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 PINT_RST             :1;                             /* Pin interrupt (PINT) reset control */
    UINT32 GINT_RST             :1;                             /* Grouped interrupt (GINT) reset control */
    UINT32 DMA_RST              :1;                             /* DMA reset control */
    UINT32 CRC_RST              :1;                             /* CRC generator reset control */
    UINT32                      :5;                             /* Reserved */
    UINT32 ADC0_RST             :1;                             /* ADC0 reset control */
    UINT32 ADC1_RST             :1;                             /* ADC1 reset control */
    UINT32 DAC_RST              :1;                             /* DAC reset control */
    UINT32 ACMP_RST             :1;                             /* Analog Comparator (ACMP) reset control for all four 4 comparators in the analog comparator block. */
    UINT32                      :1;                             /* Reserved */
} SYSCONPRESETCTRL0BITFIELD;

#define REG_PRESETCTRL0         REG_32(BASE_SYSCON + 0x044)
#define REGBITS_PRESETCTRL0     REGBITS_32(BASE_SYSCON + 0x044, SYSCONPRESETCTRL0BITFIELD)

/*******************************************************************************************************************************************

    PRESETCTRL1: Peripheral reset control 1

*******************************************************************************************************************************************/
typedef struct SYSCONPRESETCTRL1BITFIELD {
    UINT32 MRT_RST              :1;                             /* Multi-rate timer (MRT) reset control */
    UINT32 RIT_RST              :1;                             /* Repetitive interrupt timer (RIT) reset control */
    UINT32 SCT0_RST             :1;                             /* State configurable timer 0 (SCT0) reset control */
    UINT32 SCT1_RST             :1;                             /* State configurable timer 1 (SCT1) reset control */
    UINT32 SCT2_RST             :1;                             /* State configurable timer 2 (SCT2) reset control */
    UINT32 SCT3_RST             :1;                             /* State configurable timer 3 (SCT3) reset control */
    UINT32 SCTIPU_RST           :1;                             /* State configurable timer IPU (SCTIPU) reset control */
    UINT32 CCAN_RST             :1;                             /* CCAN reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 SPI0_RST             :1;                             /* SPI0 reset control */
    UINT32 SPI1_RST             :1;                             /* SPI1 reset control */
    UINT32                      :2;                             /* Reserved */
    UINT32 I2C0_RST             :1;                             /* I2C0 reset control */
    UINT32                      :3;                             /* Reserved */
    UINT32 UART0_RST            :1;                             /* UART0 reset control */
    UINT32 UART1_RST            :1;                             /* UART1 reset control */
    UINT32 UART2_RST            :1;                             /* UART2 reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 QEI0_RST             :1;                             /* QEI0 reset control */
    UINT32                      :1;                             /* Reserved */
    UINT32 USB_RST              :1;                             /* USB reset control */
    UINT32                      :8;                             /* Reserved */
} SYSCONPRESETCTRL1BITFIELD;

#define REG_PRESETCTRL1         REG_32(BASE_SYSCON + 0x048)
#define REGBITS_PRESETCTRL1     REGBITS_32(BASE_SYSCON + 0x048, SYSCONPRESETCTRL1BITFIELD)

/*******************************************************************************************************************************************

    PIOPORCAP0: POR captured PIO status 0

*******************************************************************************************************************************************/
typedef struct SYSCONPIOPORCAP0BITFIELD {
    UINT32 PIOSTAT              :32;                            /* State of PIO0_31 through PIO0_0 at power-on reset */
} SYSCONPIOPORCAP0BITFIELD;

#define REG_PIOPORCAP0          REG_32(BASE_SYSCON + 0x04C)
#define REGBITS_PIOPORCAP0      REGBITS_32(BASE_SYSCON + 0x04C, SYSCONPIOPORCAP0BITFIELD)

/*******************************************************************************************************************************************

    PIOPORCAP1: POR captured PIO status 1

*******************************************************************************************************************************************/
typedef struct SYSCONPIOPORCAP1BITFIELD {
    UINT32 PIOSTAT              :32;                            /* State of PIO1_31 through PIO1_0 at power-on reset */
} SYSCONPIOPORCAP1BITFIELD;

#define REG_PIOPORCAP1          REG_32(BASE_SYSCON + 0x050)
#define REGBITS_PIOPORCAP1      REGBITS_32(BASE_SYSCON + 0x050, SYSCONPIOPORCAP1BITFIELD)

/*******************************************************************************************************************************************

    PIOPORCAP2: POR captured PIO status 2

*******************************************************************************************************************************************/
typedef struct SYSCONPIOPORCAP2BITFIELD {
    UINT32 PIOSTAT              :12;                            /* State of PIO2_11 through PIO2_0 at power-on reset */
    UINT32                      :20;                            /* Reserved. */
} SYSCONPIOPORCAP2BITFIELD;

#define REG_PIOPORCAP2          REG_32(BASE_SYSCON + 0x054)
#define REGBITS_PIOPORCAP2      REGBITS_32(BASE_SYSCON + 0x054, SYSCONPIOPORCAP2BITFIELD)

/*******************************************************************************************************************************************

    MAINCLKSELA: Main clock source select A

*******************************************************************************************************************************************/
typedef struct SYSCONMAINCLKSELABITFIELD {
    UINT32 SEL                  :2;                             /* Clock source for main clock source selector A */
    UINT32                      :30;                            /* Reserved */
} SYSCONMAINCLKSELABITFIELD;

#define REG_MAINCLKSELA         REG_32(BASE_SYSCON + 0x080)
#define REGBITS_MAINCLKSELA     REGBITS_32(BASE_SYSCON + 0x080, SYSCONMAINCLKSELABITFIELD)

/*******************************************************************************************************************************************

    MAINCLKSELB: Main clock source select B

*******************************************************************************************************************************************/
typedef struct SYSCONMAINCLKSELBBITFIELD {
    UINT32 SEL                  :2;                             /* Clock source for main clock source selector B. Selects the clock source for the main clock. */
    UINT32                      :30;                            /* Reserved */
} SYSCONMAINCLKSELBBITFIELD;

#define REG_MAINCLKSELB         REG_32(BASE_SYSCON + 0x084)
#define REGBITS_MAINCLKSELB     REGBITS_32(BASE_SYSCON + 0x084, SYSCONMAINCLKSELBBITFIELD)

/*******************************************************************************************************************************************

    USBCLKSEL: USB clock source select

*******************************************************************************************************************************************/
typedef struct SYSCONUSBCLKSELBITFIELD {
    UINT32 SEL                  :2;                             /* USB clock source. */
    UINT32                      :30;                            /* Reserved */
} SYSCONUSBCLKSELBITFIELD;

#define REG_USBCLKSEL           REG_32(BASE_SYSCON + 0x088)
#define REGBITS_USBCLKSEL       REGBITS_32(BASE_SYSCON + 0x088, SYSCONUSBCLKSELBITFIELD)

/*******************************************************************************************************************************************

    ADCASYNCCLKSEL: ADC asynchronous clock source select

*******************************************************************************************************************************************/
typedef struct SYSCONADCASYNCCLKSELBITFIELD {
    UINT32 SEL                  :2;                             /* USB clock source. */
    UINT32                      :30;                            /* Reserved */
} SYSCONADCASYNCCLKSELBITFIELD;

#define REG_ADCASYNCCLKSEL      REG_32(BASE_SYSCON + 0x08C)
#define REGBITS_ADCASYNCCLKSEL  REGBITS_32(BASE_SYSCON + 0x08C, SYSCONADCASYNCCLKSELBITFIELD)

/*******************************************************************************************************************************************

    CLKOUTSELA: CLKOUT clock source select A

*******************************************************************************************************************************************/
typedef struct SYSCONCLKOUTSELABITFIELD {
    UINT32 SEL                  :2;                             /* CLKOUT clock source */
    UINT32                      :30;                            /* Reserved */
} SYSCONCLKOUTSELABITFIELD;

#define REG_CLKOUTSELA          REG_32(BASE_SYSCON + 0x094)
#define REGBITS_CLKOUTSELA      REGBITS_32(BASE_SYSCON + 0x094, SYSCONCLKOUTSELABITFIELD)

/*******************************************************************************************************************************************

    CLKOUTSELB: CLKOUT clock source select B

*******************************************************************************************************************************************/
typedef struct SYSCONCLKOUTSELBBITFIELD {
    UINT32 SEL                  :2;                             /* CLKOUT clock source */
    UINT32                      :30;                            /* Reserved */
} SYSCONCLKOUTSELBBITFIELD;

#define REG_CLKOUTSELB          REG_32(BASE_SYSCON + 0x098)
#define REGBITS_CLKOUTSELB      REGBITS_32(BASE_SYSCON + 0x098, SYSCONCLKOUTSELBBITFIELD)

/*******************************************************************************************************************************************

    SYSPLLCLKSEL: System PLL clock source select

*******************************************************************************************************************************************/
typedef struct SYSCONSYSPLLCLKSELBITFIELD {
    UINT32 SEL                  :2;                             /* System PLL clock source */
    UINT32                      :30;                            /* Reserved */
} SYSCONSYSPLLCLKSELBITFIELD;

#define REG_SYSPLLCLKSEL        REG_32(BASE_SYSCON + 0x0A0)
#define REGBITS_SYSPLLCLKSEL    REGBITS_32(BASE_SYSCON + 0x0A0, SYSCONSYSPLLCLKSELBITFIELD)

/*******************************************************************************************************************************************

    USBPLLCLKSEL: USB PLL clock source select

*******************************************************************************************************************************************/
typedef struct SYSCONUSBPLLCLKSELBITFIELD {
    UINT32 SEL                  :2;                             /* USB PLL clock source */
    UINT32                      :30;                            /* Reserved */
} SYSCONUSBPLLCLKSELBITFIELD;

#define REG_USBPLLCLKSEL        REG_32(BASE_SYSCON + 0x0A4)
#define REGBITS_USBPLLCLKSEL    REGBITS_32(BASE_SYSCON + 0x0A4, SYSCONUSBPLLCLKSELBITFIELD)

/*******************************************************************************************************************************************

    SCTPLLCLKSEL: SCT PLL clock source select

*******************************************************************************************************************************************/
typedef struct SYSCONSCTPLLCLKSELBITFIELD {
    UINT32 SEL                  :2;                             /* SCT PLL clock source */
    UINT32                      :30;                            /* Reserved */
} SYSCONSCTPLLCLKSELBITFIELD;

#define REG_SCTPLLCLKSEL        REG_32(BASE_SYSCON + 0x0A8)
#define REGBITS_SCTPLLCLKSEL    REGBITS_32(BASE_SYSCON + 0x0A8, SYSCONSCTPLLCLKSELBITFIELD)

/*******************************************************************************************************************************************

    SYSAHBCLKDIV: System clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONSYSAHBCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* System AHB clock divider values 0: System clock disabled. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONSYSAHBCLKDIVBITFIELD;

#define REG_SYSAHBCLKDIV        REG_32(BASE_SYSCON + 0x0C0)
#define REGBITS_SYSAHBCLKDIV    REGBITS_32(BASE_SYSCON + 0x0C0, SYSCONSYSAHBCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    SYSAHBCLKCTRL0: System clock control 0

*******************************************************************************************************************************************/
typedef struct SYSCONSYSAHBCLKCTRL0BITFIELD {
    UINT32 SYS                  :1;                             /* Enables the clock for the AHB, the APB bridges, the Cortex-M3 core clocks, SYSCON, reset control, SRAM0, and the PMU. This bit is read-only and always reads as 1. */
    UINT32 ROM                  :1;                             /* Enables clock for ROM. */
    UINT32                      :1;                             /* Reserved */
    UINT32 SRAM1                :1;                             /* Enables clock for SRAM1. */
    UINT32 SRAM2                :1;                             /* Enables clock for SRAM2. */
    UINT32                      :2;                             /* Reserved */
    UINT32 FLASH                :1;                             /* Enables clock for flash memory. */
    UINT32 FMC                  :1;                             /* Enables clock for flash controller. */
    UINT32 EEPROM               :1;                             /* Enables clock for EEPROM. */
    UINT32                      :1;                             /* Reserved */
    UINT32 PMUX                 :1;                             /* Enables clock for pin mux. */
    UINT32 SWM                  :1;                             /* Enables clock for switch matrix. */
    UINT32 IOCON                :1;                             /* Enables clock for IOCON block. */
    UINT32 GPIO0                :1;                             /* Enables clock for GPIO0 port registers. */
    UINT32 GPIO1                :1;                             /* Enables clock for GPIO1 port registers. */
    UINT32 GPIO2                :1;                             /* Enables clock for GPIO2 port registers. */
    UINT32                      :1;                             /* Reserved */
    UINT32 PINT                 :1;                             /* Enables clock for pin interrupt block. */
    UINT32 GINT                 :1;                             /* Enables clock for grouped pin interrupt block. */
    UINT32 DMA                  :1;                             /* Enables clock for DMA. */
    UINT32 CRC                  :1;                             /* Enables clock for CRC. */
    UINT32 WWDT                 :1;                             /* Enables clock for WWDT. */
    UINT32 RTC                  :1;                             /* Enables clock for RTC. */
    UINT32                      :3;                             /* Reserved */
    UINT32 ADC0                 :1;                             /* Enables clock for ADC0 register interface. */
    UINT32 ADC1                 :1;                             /* Enables clock for ADC1 register interface. */
    UINT32 DAC                  :1;                             /* Enables clock for DAC. */
    UINT32 CMP                  :1;                             /* Enables clock to analog comparator block. This is the clock to the register interface for all 4 comparators. */
    UINT32                      :1;                             /* Reserved */
} SYSCONSYSAHBCLKCTRL0BITFIELD;

#define REG_SYSAHBCLKCTRL0      REG_32(BASE_SYSCON + 0x0C4)
#define REGBITS_SYSAHBCLKCTRL0  REGBITS_32(BASE_SYSCON + 0x0C4, SYSCONSYSAHBCLKCTRL0BITFIELD)

/*******************************************************************************************************************************************

    SYSAHBCLKCTRL1: System clock control 1

*******************************************************************************************************************************************/
typedef struct SYSCONSYSAHBCLKCTRL1BITFIELD {
    UINT32 MRT                  :1;                             /* Enables clock for multi-rate timer. */
    UINT32 RIT                  :1;                             /* Enables clock for repetitive interrupt timer. */
    UINT32 SCT0                 :1;                             /* Enables clock for SCT0. */
    UINT32 SCT1                 :1;                             /* Enables clock for SCT1. */
    UINT32 SCT2                 :1;                             /* Enables clock for SCT2. */
    UINT32 SCT3                 :1;                             /* Enables clock for SCT3. */
    UINT32 SCTIPU               :1;                             /* Enables clock for SCTIPU. */
    UINT32 CCAN                 :1;                             /* Enables clock for CCAN. */
    UINT32                      :1;                             /* Reserved */
    UINT32 SPI0                 :1;                             /* Enables clock for SPI0. */
    UINT32 SPI1                 :1;                             /* Enables clock for SPI1. */
    UINT32                      :2;                             /* Reserved */
    UINT32 I2C0                 :1;                             /* Enables clock for I2C0. */
    UINT32 I2C1                 :1;                             /* Enables clock for I2C1. */
    UINT32                      :2;                             /* Reserved */
    UINT32 UART0                :1;                             /* Enables clock for USART0. */
    UINT32 UART1                :1;                             /* Enables clock for USART1. */
    UINT32 UART2                :1;                             /* Enables clock for USART2. */
    UINT32                      :1;                             /* Reserved */
    UINT32 QEI                  :1;                             /* Enables clock for QEI. */
    UINT32                      :1;                             /* Reserved */
    UINT32 USB                  :1;                             /* Enables clock for USB register interface. */
    UINT32                      :8;                             /* Reserved */
} SYSCONSYSAHBCLKCTRL1BITFIELD;

#define REG_SYSAHBCLKCTRL1      REG_32(BASE_SYSCON + 0x0C8)
#define REGBITS_SYSAHBCLKCTRL1  REGBITS_32(BASE_SYSCON + 0x0C8, SYSCONSYSAHBCLKCTRL1BITFIELD)

/*******************************************************************************************************************************************

    SYSTICKCLKDIV: SYSTICK clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONSYSTICKCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* SYSTICK clock divider values. 0: Disable SYSTICK timer clock. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONSYSTICKCLKDIVBITFIELD;

#define REG_SYSTICKCLKDIV       REG_32(BASE_SYSCON + 0x0CC)
#define REGBITS_SYSTICKCLKDIV   REGBITS_32(BASE_SYSCON + 0x0CC, SYSCONSYSTICKCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    UARTCLKDIV: USART clock divider. Clock divider for the USART fractional baud rate generator.

*******************************************************************************************************************************************/
typedef struct SYSCONUARTCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* USART fractional baud rate generator clock divider values. 0: Clock disabled. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONUARTCLKDIVBITFIELD;

#define REG_UARTCLKDIV          REG_32(BASE_SYSCON + 0x0D0)
#define REGBITS_UARTCLKDIV      REGBITS_32(BASE_SYSCON + 0x0D0, SYSCONUARTCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    IOCONCLKDIV: Peripheral clock to the IOCON block for programmable glitch filter

*******************************************************************************************************************************************/
typedef struct SYSCONIOCONCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONIOCONCLKDIVBITFIELD;

#define REG_IOCONCLKDIV         REG_32(BASE_SYSCON + 0x0D4)
#define REGBITS_IOCONCLKDIV     REGBITS_32(BASE_SYSCON + 0x0D4, SYSCONIOCONCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    TRACECLKDIV: ARM trace clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONTRACECLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* ARM trace clock divider values. 0: Disable TRACE_CLK. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONTRACECLKDIVBITFIELD;

#define REG_TRACECLKDIV         REG_32(BASE_SYSCON + 0x0D8)
#define REGBITS_TRACECLKDIV     REGBITS_32(BASE_SYSCON + 0x0D8, SYSCONTRACECLKDIVBITFIELD)

/*******************************************************************************************************************************************

    USBCLKDIV: USB clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONUSBCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* USB clock divider values 0: Disable USB clock. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONUSBCLKDIVBITFIELD;

#define REG_USBCLKDIV           REG_32(BASE_SYSCON + 0x0EC)
#define REGBITS_USBCLKDIV       REGBITS_32(BASE_SYSCON + 0x0EC, SYSCONUSBCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    ADCASYNCCLKDIV: Asynchronous ADC clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONADCASYNCCLKDIVBITFIELD {
    UINT32 DIV                  :8;                             /* USB clock divider values 0: Disable USB clock. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONADCASYNCCLKDIVBITFIELD;

#define REG_ADCASYNCCLKDIV      REG_32(BASE_SYSCON + 0x0F0)
#define REGBITS_ADCASYNCCLKDIV  REGBITS_32(BASE_SYSCON + 0x0F0, SYSCONADCASYNCCLKDIVBITFIELD)

/*******************************************************************************************************************************************

    CLKOUTDIV: CLKOUT clock divider

*******************************************************************************************************************************************/
typedef struct SYSCONCLKOUTDIVBITFIELD {
    UINT32 DIV                  :8;                             /* CLKOUT clock divider values 0: Disable CLKOUT clock divider. 1: Divide by 1. to 255: Divide by 255. */
    UINT32                      :24;                            /* Reserved */
} SYSCONCLKOUTDIVBITFIELD;

#define REG_CLKOUTDIV           REG_32(BASE_SYSCON + 0x0F8)
#define REGBITS_CLKOUTDIV       REGBITS_32(BASE_SYSCON + 0x0F8, SYSCONCLKOUTDIVBITFIELD)

/*******************************************************************************************************************************************

    FLASHCFG: Flash configuration register

*******************************************************************************************************************************************/
typedef struct FLASHCFGBITFIELD {
    UINT32                      :12;
    UINT32 FLASHTIM             :2;                             /* Flash memory access time. FLASHTIM + 1 is equal to the number of system clocks used for flash access. */
    UINT32                      :18;
} FLASHCFGBITFIELD;

#define REG_FLASHCFG            REG_32(BASE_SYSCON + 0x124)
#define REGBITS_FLASHCFG        REGBITS_32(BASE_SYSCON + 0x124, FLASHCFGBITFIELD)

/*******************************************************************************************************************************************

    FRGCTRL: USART fractional baud rate generator control

*******************************************************************************************************************************************/
typedef struct SYSCONFRGCTRLBITFIELD {
    UINT32 DIV                  :8;                             /* Denominator of the fractional divider. DIV is equal to the programmed value +1. Always set to 0xFF to use with the fractional baud rate generator. */
    UINT32 MULT                 :8;                             /* Numerator of the fractional divider. MULT is equal to the programmed value. */
    UINT32                      :16;                            /* Reserved */
} SYSCONFRGCTRLBITFIELD;

#define REG_FRGCTRL             REG_32(BASE_SYSCON + 0x128)
#define REGBITS_FRGCTRL         REGBITS_32(BASE_SYSCON + 0x128, SYSCONFRGCTRLBITFIELD)

/*******************************************************************************************************************************************

    USBCLKCTRL: USB clock control

*******************************************************************************************************************************************/
typedef struct SYSCONUSBCLKCTRLBITFIELD {
    UINT32 AP_CLK               :1;                             /* USB need_clock signal control */
    UINT32 POL_CLK              :1;                             /* USB need_clock polarity for triggering the USB wake-up interrupt */
    UINT32                      :30;                            /* Reserved */
} SYSCONUSBCLKCTRLBITFIELD;

#define REG_USBCLKCTRL          REG_32(BASE_SYSCON + 0x12C)
#define REGBITS_USBCLKCTRL      REGBITS_32(BASE_SYSCON + 0x12C, SYSCONUSBCLKCTRLBITFIELD)

/*******************************************************************************************************************************************

    USBCLKST: USB clock status

*******************************************************************************************************************************************/
typedef struct SYSCONUSBCLKSTBITFIELD {
    UINT32 NEED_CLKST           :1;                             /* USB need_clock signal status */
    UINT32                      :31;                            /* Reserved */
} SYSCONUSBCLKSTBITFIELD;

#define REG_USBCLKST            REG_32(BASE_SYSCON + 0x130)
#define REGBITS_USBCLKST        REGBITS_32(BASE_SYSCON + 0x130, SYSCONUSBCLKSTBITFIELD)

/*******************************************************************************************************************************************

    BODCTRL: Brown-Out Detect

*******************************************************************************************************************************************/
typedef struct SYSCONBODCTRLBITFIELD {
    UINT32 BODRSTLEV            :2;                             /* BOD reset level */
    UINT32 BODINTVAL            :2;                             /* BOD interrupt level */
    UINT32 BODRSTENA            :1;                             /* BOD reset enable */
    UINT32                      :27;                            /* Reserved */
} SYSCONBODCTRLBITFIELD;

#define REG_BODCTRL             REG_32(BASE_SYSCON + 0x180)
#define REGBITS_BODCTRL         REGBITS_32(BASE_SYSCON + 0x180, SYSCONBODCTRLBITFIELD)

/*******************************************************************************************************************************************

    SYSOSCCTRL: System oscillator control

*******************************************************************************************************************************************/
typedef struct SYSCONSYSOSCCTRLBITFIELD {
    UINT32 BYPASS               :1;                             /* Bypass system oscillator */
    UINT32 FREQRANGE            :1;                             /* Determines frequency range for Low-power oscillator. */
    UINT32                      :30;                            /* Reserved */
} SYSCONSYSOSCCTRLBITFIELD;

#define REG_SYSOSCCTRL          REG_32(BASE_SYSCON + 0x188)
#define REGBITS_SYSOSCCTRL      REGBITS_32(BASE_SYSCON + 0x188, SYSCONSYSOSCCTRLBITFIELD)

/*******************************************************************************************************************************************

    RTCOSCCTRL: RTC oscillator control

*******************************************************************************************************************************************/
typedef struct SYSCONRTCOSCCTRLBITFIELD {
    UINT32 EN                   :1;                             /* RTC 32 kHz clock enable. */
    UINT32                      :31;                            /* Reserved */
} SYSCONRTCOSCCTRLBITFIELD;

#define REG_RTCOSCCTRL          REG_32(BASE_SYSCON + 0x190)
#define REGBITS_RTCOSCCTRL      REGBITS_32(BASE_SYSCON + 0x190, SYSCONRTCOSCCTRLBITFIELD)

/*******************************************************************************************************************************************

    SYSPLLCTRL: System PLL control

*******************************************************************************************************************************************/
typedef struct SYSCONSYSPLLCTRLBITFIELD {
    UINT32 MSEL                 :6;                             /* Feedback divider value. The division value M is the programmed MSEL value + 1. 00000: Division ratio M = 1 to 111111: Division ratio M = 64 */
    UINT32 PSEL                 :2;                             /* Post divider ratio P. The division ratio is 2 x P. */
    UINT32                      :24;                            /* Reserved. Do not write ones to reserved bits. */
} SYSCONSYSPLLCTRLBITFIELD;

#define REG_SYSPLLCTRL          REG_32(BASE_SYSCON + 0x198)
#define REGBITS_SYSPLLCTRL      REGBITS_32(BASE_SYSCON + 0x198, SYSCONSYSPLLCTRLBITFIELD)

/*******************************************************************************************************************************************

    SYSPLLSTAT: System PLL status

*******************************************************************************************************************************************/
typedef struct SYSCONSYSPLLSTATBITFIELD {
    UINT32 LOCK                 :1;                             /* PLL lock status */
    UINT32                      :31;                            /* Reserved */
} SYSCONSYSPLLSTATBITFIELD;

#define REG_SYSPLLSTAT          REG_32(BASE_SYSCON + 0x19C)
#define REGBITS_SYSPLLSTAT      REGBITS_32(BASE_SYSCON + 0x19C, SYSCONSYSPLLSTATBITFIELD)

/*******************************************************************************************************************************************

    USBPLLCTRL: USB PLL control

*******************************************************************************************************************************************/
typedef struct SYSCONUSBPLLCTRLBITFIELD {
    UINT32 MSEL                 :6;                             /* Feedback divider value. The division value M is the programmed MSEL value + 1. 00000: Division ratio M = 1 to 111111: Division ratio M = 64. */
    UINT32 PSEL                 :2;                             /* Post divider ratio P. The division ratio is 2 x P. */
    UINT32                      :24;                            /* Reserved. Do not write ones to reserved bits. */
} SYSCONUSBPLLCTRLBITFIELD;

#define REG_USBPLLCTRL          REG_32(BASE_SYSCON + 0x1A0)
#define REGBITS_USBPLLCTRL      REGBITS_32(BASE_SYSCON + 0x1A0, SYSCONUSBPLLCTRLBITFIELD)

/*******************************************************************************************************************************************

    USBPLLSTAT: USB PLL status

*******************************************************************************************************************************************/
typedef struct SYSCONUSBPLLSTATBITFIELD {
    UINT32 LOCK                 :1;                             /* PLL lock status */
    UINT32                      :31;                            /* Reserved */
} SYSCONUSBPLLSTATBITFIELD;

#define REG_USBPLLSTAT          REG_32(BASE_SYSCON + 0x1A4)
#define REGBITS_USBPLLSTAT      REGBITS_32(BASE_SYSCON + 0x1A4, SYSCONUSBPLLSTATBITFIELD)

/*******************************************************************************************************************************************

    SCTPLLCTRL: SCT PLL control

*******************************************************************************************************************************************/
typedef struct SYSCONSCTPLLCTRLBITFIELD {
    UINT32 MSEL                 :6;                             /* Feedback divider value. The division value M is the programmed MSEL value + 1. 00000: Division ratio M = 1 to 111111: Division ratio M = 64. */
    UINT32 PSEL                 :2;                             /* Post divider ratio P. The division ratio is 2 x P. */
    UINT32                      :24;                            /* Reserved. Do not write ones to reserved bits. */
} SYSCONSCTPLLCTRLBITFIELD;

#define REG_SCTPLLCTRL          REG_32(BASE_SYSCON + 0x1A8)
#define REGBITS_SCTPLLCTRL      REGBITS_32(BASE_SYSCON + 0x1A8, SYSCONSCTPLLCTRLBITFIELD)

/*******************************************************************************************************************************************

    SCTPLLSTAT: SCT PLL status

*******************************************************************************************************************************************/
typedef struct SYSCONSCTPLLSTATBITFIELD {
    UINT32 LOCK                 :1;                             /* PLL lock status */
    UINT32                      :31;                            /* Reserved */
} SYSCONSCTPLLSTATBITFIELD;

#define REG_SCTPLLSTAT          REG_32(BASE_SYSCON + 0x1AC)
#define REGBITS_SCTPLLSTAT      REGBITS_32(BASE_SYSCON + 0x1AC, SYSCONSCTPLLSTATBITFIELD)

/*******************************************************************************************************************************************

    PDAWAKECFG: Power-down states for wake-up from deep-sleep

*******************************************************************************************************************************************/
typedef struct SYSCONPDAWAKECFGBITFIELD {
    UINT32                      :3;                             /* Reserved. */
    UINT32 IRCOUT_PD            :1;                             /* IRC oscillator output wake-up configuration */
    UINT32 IRC                  :1;                             /* IRC oscillator wake-up configuration */
    UINT32 FLASH                :1;                             /* Flash memory wake-up configuration */
    UINT32 EEPROM               :1;                             /* EEPROM wake-up configuration */
    UINT32                      :1;                             /* Reserved */
    UINT32 BOD_PD               :1;                             /* BOD wake-up configuration */
    UINT32 USBPHY_PD            :1;                             /* USB PHY wake-up configuration */
    UINT32 ADC0_PD              :1;                             /* ADC0 wake-up configuration */
    UINT32 ADC1_PD              :1;                             /* ADC1 wake-up configuration */
    UINT32 DAC_PD               :1;                             /* DAC wake-up configuration */
    UINT32 ACMP0_PD             :1;                             /* Analog comparator 0 wake-up configuration */
    UINT32 ACMP1_PD             :1;                             /* Analog comparator 1 wake-up configuration */
    UINT32 ACMP2_PD             :1;                             /* Analog comparator 2 wake-up configuration */
    UINT32 ACMP3_PD             :1;                             /* Analog comparator 3 wake-up configuration */
    UINT32 IREF_PD              :1;                             /* Internal voltage reference wake-up configuration */
    UINT32 TS_PD                :1;                             /* Temperature sensor wake-up configuration */
    UINT32 VDDADIV_PD           :1;                             /* VDDA divider what is this for? wake-up configuration */
    UINT32 WDTOSC_PD            :1;                             /* Watchdog oscillator wake-up configuration. */
    UINT32 SYSOSC_PD            :1;                             /* System oscillator wake-up configuration */
    UINT32 SYSPLL_PD            :1;                             /* System PLL wake-up configuration */
    UINT32 USBPLL_PD            :1;                             /* USB PLL wake-up configuration */
    UINT32 SCTPLL_PD            :1;                             /* USB PLL wake-up configuration */
    UINT32                      :7;                             /* Reserved */
} SYSCONPDAWAKECFGBITFIELD;

#define REG_PDAWAKECFG          REG_32(BASE_SYSCON + 0x204)
#define REGBITS_PDAWAKECFG      REGBITS_32(BASE_SYSCON + 0x204, SYSCONPDAWAKECFGBITFIELD)

/*******************************************************************************************************************************************

    PDRUNCFG: Power configuration register

*******************************************************************************************************************************************/
typedef struct SYSCONPDRUNCFGBITFIELD {
    UINT32                      :3;                             /* Reserved. */
    UINT32 IRCOUT_PD            :1;                             /* IRC oscillator output */
    UINT32 IRC                  :1;                             /* IRC oscillator */
    UINT32 FLASH                :1;                             /* Flash memory */
    UINT32 EEPROM               :1;                             /* EEPROM */
    UINT32                      :1;                             /* Reserved */
    UINT32 BOD_PD               :1;                             /* BOD power-down */
    UINT32 USBPHY_PD            :1;                             /* USB PHY power-down */
    UINT32 ADC0_PD              :1;                             /* ADC0 power-down */
    UINT32 ADC1_PD              :1;                             /* ADC1 power-down */
    UINT32 DAC_PD               :1;                             /* DAC power-down */
    UINT32 ACMP0_PD             :1;                             /* Analog comparator 0 power-down */
    UINT32 ACMP1_PD             :1;                             /* Analog comparator 1 power-down */
    UINT32 ACMP2_PD             :1;                             /* Analog comparator 2 power-down */
    UINT32 ACMP3_PD             :1;                             /* Analog comparator 3 power-down */
    UINT32 IREF_PD              :1;                             /* Internal voltage reference power-down */
    UINT32 TS_PD                :1;                             /* Temperature sensor power-down */
    UINT32 VDDADIV_PD           :1;                             /* VDDA divider what is this for? */
    UINT32 WDTOSC_PD            :1;                             /* Watchdog oscillator power-down . */
    UINT32 SYSOSC_PD            :1;                             /* System oscillator power-down */
    UINT32 SYSPLL_PD            :1;                             /* System PLL power-down */
    UINT32 USBPLL_PD            :1;                             /* USB PLL power-down */
    UINT32 SCTPLL_PD            :1;                             /* USB PLL power-down */
    UINT32                      :7;                             /* Reserved */
} SYSCONPDRUNCFGBITFIELD;

#define REG_PDRUNCFG            REG_32(BASE_SYSCON + 0x208)
#define REGBITS_PDRUNCFG        REGBITS_32(BASE_SYSCON + 0x208, SYSCONPDRUNCFGBITFIELD)

/*******************************************************************************************************************************************

    STARTERP0: Start logic 0 wake-up enable register

*******************************************************************************************************************************************/
typedef struct SYSCONSTARTERP0BITFIELD {
    UINT32 WWDT                 :1;                             /* WWDT interrupt wake-up. */
    UINT32 BOD                  :1;                             /* BOD interrupt wake-up. */
    UINT32                      :3;                             /* Reserved. */
    UINT32 GINT0                :1;                             /* Group interrupt 0 wake-up. */
    UINT32 GINT1                :1;                             /* Group interrupt 1 wake-up. */
    UINT32 PINT0                :1;                             /* GPIO pin interrupt 0 wake-up */
    UINT32 PINT1                :1;                             /* GPIO pin interrupt 1 wake-up */
    UINT32 PINT2                :1;                             /* GPIO pin interrupt 2 wake-up */
    UINT32 PINT3                :1;                             /* GPIO pin interrupt 3 wake-up */
    UINT32 PINT4                :1;                             /* GPIO pin interrupt 4 wake-up */
    UINT32 PINT5                :1;                             /* GPIO pin interrupt 5 wake-up */
    UINT32 PINT6                :1;                             /* GPIO pin interrupt 6 wake-up */
    UINT32 PINT7                :1;                             /* GPIO pin interrupt 7 wake-up */
    UINT32                      :6;                             /* Reserved. */
    UINT32 USART0               :1;                             /* USART0 interrupt wake-up. Configure USART in synchronous slave mode or in 32 kHz mode.. */
    UINT32 USART1               :1;                             /* USART1 interrupt wake-up. Configure USART in synchronous slave mode or in 32 kHz mode... */
    UINT32 USART2               :1;                             /* USART2 interrupt wake-up. Configure USART in synchronous slave mode or in 32 kHz mode... */
    UINT32 I2C                  :1;                             /* I2C interrupt wake-up. */
    UINT32 SPI0                 :1;                             /* SPI0 interrupt wake-up */
    UINT32 SPI1                 :1;                             /* SPI1 interrupt wake-up */
    UINT32                      :3;                             /* Reserved */
    UINT32 USB_WAKEUP           :1;                             /* USB need_clock signal wake-up */
    UINT32                      :1;                             /* Reserved */
} SYSCONSTARTERP0BITFIELD;

#define REG_STARTERP0           REG_32(BASE_SYSCON + 0x218)
#define REGBITS_STARTERP0       REGBITS_32(BASE_SYSCON + 0x218, SYSCONSTARTERP0BITFIELD)

/*******************************************************************************************************************************************

    STARTERP1: Start logic 1 wake-up enable register

*******************************************************************************************************************************************/
typedef struct SYSCONSTARTERP1BITFIELD {
    UINT32                      :8;                             /* Reserved */
    UINT32 ACMP0                :1;                             /* Analog comparator 0 interrupt wake-up */
    UINT32 ACMP1                :1;                             /* Analog comparator 1 interrupt wake-up */
    UINT32 ACMP2                :1;                             /* Analog comparator 2 interrupt wake-up */
    UINT32 ACMP3                :1;                             /* Analog comparator 3 interrupt wake-up */
    UINT32                      :1;                             /* Reserved */
    UINT32 RTCALARM             :1;                             /* RTC alarm interrupt wake-up */
    UINT32 RTCWAKE              :1;                             /* RTC wake-up interrupt wake-up */
    UINT32                      :17;                            /* Reserved. */
} SYSCONSTARTERP1BITFIELD;

#define REG_STARTERP1           REG_32(BASE_SYSCON + 0x21C)
#define REGBITS_STARTERP1       REGBITS_32(BASE_SYSCON + 0x21C, SYSCONSTARTERP1BITFIELD)

#endif /* MCU_SYSCON_H__ */
