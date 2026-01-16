//*****************************************************************************
//
// usci_a_uart.h - Driver for the USCI_A_UART Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_A_UART_H__
#define __MSP430WARE_USCI_A_UART_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_USCI_Ax__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \brief Used in the USCI_A_UART_init() function as the param parameter.
//
//*****************************************************************************
typedef struct USCI_A_UART_initParam {
    uint8_t selectClockSource;
    uint16_t clockPrescalar;
    uint8_t firstModReg;
    uint8_t secondModReg;
    uint8_t parity;
    uint8_t msborLsbFirst;
    uint8_t numberofStopBits;
    uint8_t uartMode;
    uint8_t overSampling;
} USCI_A_UART_initParam;

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define USCI_A_UART_CLOCKSOURCE_UCKLCLK                            UCSSEL_0
#define USCI_A_UART_CLOCKSOURCE_ACLK                               UCSSEL_1
#define USCI_A_UART_CLOCKSOURCE_SMCLK                              UCSSEL_2

//*****************************************************************************
//
// Parity settings
//
//*****************************************************************************
#define USCI_A_UART_NO_PARITY                                              0x00
#define USCI_A_UART_ODD_PARITY                                             0x01
#define USCI_A_UART_EVEN_PARITY                                            0x02

//*****************************************************************************
//
// Stop bits
//
//*****************************************************************************
#define USCI_A_UART_ONE_STOP_BIT                                           0x00
#define USCI_A_UART_TWO_STOP_BITS                                         0x01

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void USCI_A_UART_init(uint16_t baseAddress,
                              USCI_A_UART_initParam *param);
extern void USCI_A_UART_transmitData(uint16_t baseAddress, uint8_t transmitData);
extern uint8_t USCI_A_UART_receiveData(uint16_t baseAddress);
extern void USCI_A_UART_enable(uint16_t baseAddress);
extern void USCI_A_UART_disable(uint16_t baseAddress);
extern bool USCI_A_UART_queryStatusFlags(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_clearInterruptFlag(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_enableInterrupt(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_disableInterrupt(uint16_t baseAddress, uint8_t mask);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_USCI_Ax__

#endif // __MSP430WARE_USCI_A_UART_H__
