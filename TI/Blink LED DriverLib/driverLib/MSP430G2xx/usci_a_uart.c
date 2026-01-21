//*****************************************************************************
//
// usci_a_uart.c - Driver for the USCI_A UART Module for MSP430G2xx family.
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "usci_a_uart.h"

#ifdef __MSP430_HAS_USCI_Ax__

#include <assert.h>

void USCI_A_UART_init(uint16_t baseAddress, USCI_A_UART_initParam *param)
{
    // Disable USCI
    UCA0CTL1 |= UCSWRST;

    // Configure clock source
    UCA0CTL1 |= param->selectClockSource;

    // Set baud rate
    UCA0BR0 = (uint8_t)(param->clockPrescalar);
    UCA0BR1 = (uint8_t)(param->clockPrescalar >> 8);

    // Set modulation
    UCA0MCTL = (param->firstModReg & 0x0F) | ((param->secondModReg & 0x07) << 4);

    // Configure parity
    if(param->parity != USCI_A_UART_NO_PARITY) {
        UCA0CTL0 |= UCPEN;
        if(param->parity == USCI_A_UART_EVEN_PARITY) {
            UCA0CTL0 |= UCPAR;
        }
    }

    // Configure stop bits
    if(param->numberofStopBits == USCI_A_UART_TWO_STOP_BITS) {
        UCA0CTL0 |= UCSPB;
    }

    // Enable USCI
    UCA0CTL1 &= ~UCSWRST;
}

void USCI_A_UART_transmitData(uint16_t baseAddress, uint8_t transmitData)
{
    UCA0TXBUF = transmitData;
}

uint8_t USCI_A_UART_receiveData(uint16_t baseAddress)
{
    return UCA0RXBUF;
}

void USCI_A_UART_enable(uint16_t baseAddress)
{
    UCA0CTL1 &= ~UCSWRST;
}

void USCI_A_UART_disable(uint16_t baseAddress)
{
    UCA0CTL1 |= UCSWRST;
}

bool USCI_A_UART_queryStatusFlags(uint16_t baseAddress, uint8_t mask)
{
    return (UCA0STAT & mask) != 0;
}

void USCI_A_UART_clearInterruptFlag(uint16_t baseAddress, uint8_t mask)
{
    UCA0IFG &= ~mask;
}

void USCI_A_UART_enableInterrupt(uint16_t baseAddress, uint8_t mask)
{
    UCA0IE |= mask;
}

void USCI_A_UART_disableInterrupt(uint16_t baseAddress, uint8_t mask)
{
    UCA0IE &= ~mask;
}

#endif // __MSP430_HAS_USCI_Ax__