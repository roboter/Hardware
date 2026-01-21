/**
 * @file usci_a_uart_example.c
 * @brief USCI_A UART peripheral example for MSP430G2xx
 *
 * This example demonstrates UART communication:
 * - Configure UART for 9600 baud
 * - Transmit "Hello World!" message
 * - Echo received characters back
 */

#include <msp430g2553.h>
#include <string.h>
#include "driverlib.h"

// UART interrupt service routine
#pragma vector=USCIAB0TX_VECTOR
__interrupt void UART_TX_ISR(void)
{
    // TX interrupt - can be used for buffered transmission
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_RX_ISR(void)
{
    // Echo received character back
    uint8_t receivedData = USCI_A_UART_receiveData(USCI_A0_BASE);
    USCI_A_UART_transmitData(USCI_A0_BASE, receivedData);

    // Clear interrupt flag
    USCI_A_UART_clearInterruptFlag(USCI_A0_BASE, USCI_A_UART_RECEIVE_INTERRUPT);
}

void main(void)
{
    const char *message = "Hello World!\r\n";

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure P1.1 (TX) and P1.2 (RX) as UART pins
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN1); // TX
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2);  // RX

    // Configure UART parameters
    // Assuming 1MHz SMCLK, target 9600 baud
    USCI_A_UART_initParam uartParam = {
        USCI_A_UART_CLOCKSOURCE_SMCLK,     // Clock source
        104,                              // Clock prescalar (1MHz/9600 ≈ 104)
        0,                                // First modulation register
        1,                                // Second modulation register
        USCI_A_UART_NO_PARITY,            // No parity
        USCI_A_UART_LSB_FIRST,            // LSB first
        USCI_A_UART_ONE_STOP_BIT,         // One stop bit
        USCI_A_UART_MODE,                 // UART mode
        USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
    };

    // Initialize UART
    USCI_A_UART_init(USCI_A0_BASE, &uartParam);
    USCI_A_UART_enable(USCI_A0_BASE);

    // Enable UART receive interrupt
    USCI_A_UART_enableInterrupt(USCI_A0_BASE, USCI_A_UART_RECEIVE_INTERRUPT);

    // Enable global interrupts
    __bis_SR_register(GIE);

    // Send initial message
    while(*message)
    {
        while(!USCI_A_UART_queryStatusFlags(USCI_A0_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG));
        USCI_A_UART_transmitData(USCI_A0_BASE, *message++);
    }

    // Enter low power mode 0 (CPU on, all clocks on)
    // UART interrupts will wake CPU as needed
    PMM_enterLPM0();

    while(1);
}