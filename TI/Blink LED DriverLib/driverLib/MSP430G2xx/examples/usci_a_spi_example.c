/**
 * @file usci_a_spi_example.c
 * @brief USCI_A SPI peripheral example for MSP430G2xx
 *
 * This example demonstrates SPI master communication:
 * - Configure SPI in master mode
 * - Send and receive data bytes
 * - Demonstrate SPI transaction
 */

#include <msp430g2553.h>
#include "driverlib.h"

#define SPI_BUFFER_SIZE 16

void main(void)
{
    uint8_t txData[SPI_BUFFER_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                       0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                       0x0C, 0x0D, 0x0E, 0x0F};
    uint8_t rxData[SPI_BUFFER_SIZE];
    uint8_t i;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure SPI pins
    // P1.5 = SCLK, P1.6 = MISO, P1.7 = MOSI
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
        GPIO_PIN5 | GPIO_PIN7); // SCLK and MOSI
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN6); // MISO

    // Configure SPI parameters
    USCI_A_SPI_initParam spiParam = {
        USCI_A_SPI_CLOCKSOURCE_SMCLK,      // Clock source
        1000000,                          // SMCLK frequency (1MHz)
        500000,                           // Desired SPI clock (500kHz)
        USCI_A_SPI_MSB_FIRST,             // MSB first
        USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, // Clock phase
        USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW, // Clock polarity
        USCI_A_SPI_3PIN,                  // 3-pin SPI
    };

    // Initialize SPI
    USCI_A_SPI_init(USCI_A0_BASE, &spiParam);
    USCI_A_SPI_enable(USCI_A0_BASE);

    // Configure P1.0 as output (LED indicator)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    while(1)
    {
        // Indicate start of transaction
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Perform SPI transaction
        for(i = 0; i < SPI_BUFFER_SIZE; i++)
        {
            // Wait for TX buffer to be ready
            while(USCI_A_SPI_isBusy(USCI_A0_BASE));

            // Send data
            USCI_A_SPI_transmitData(USCI_A0_BASE, txData[i]);

            // Wait for RX data
            while(USCI_A_SPI_isBusy(USCI_A0_BASE));

            // Read received data
            rxData[i] = USCI_A_SPI_receiveData(USCI_A0_BASE);
        }

        // Indicate end of transaction
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Delay before next transaction
        __delay_cycles(1000000); // ~1 second at 1MHz
    }
}