//*****************************************************************************
//
// driverlib.h - Main header file for MSP430G2xx Driver Library
//
// This header file includes all peripheral driver headers for the
// MSP430G2xx family. Include this single header file instead of
// individual peripheral headers.
//
//*****************************************************************************

#ifndef __MSP430WARE_DRIVERLIB_H__
#define __MSP430WARE_DRIVERLIB_H__

#include "inc/hw_memmap.h"

// Include all peripheral drivers
#include "gpio.h"
#include "wdt_a.h"
#include "timer_a.h"
#include "usci_a_uart.h"
#include "usci_a_spi.h"
#include "usci_b_i2c.h"
#include "adc10_a.h"
#include "bcs.h"
#include "pmm.h"
#include "flashctl.h"

#endif // __MSP430WARE_DRIVERLIB_H__
