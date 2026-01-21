/**
 * @file usci_b_i2c_example.c
 * @brief USCI_B I2C peripheral example for MSP430G2xx
 *
 * This example demonstrates I2C master communication:
 * - Configure I2C in master mode
 * - Write data to a slave device
 * - Read data from a slave device
 */

#include <msp430g2553.h>
#include "driverlib.h"

#define SLAVE_ADDRESS 0x48  // Example slave address
#define TX_BUFFER_SIZE 8
#define RX_BUFFER_SIZE 8

void main(void)
{
    uint8_t txData[TX_BUFFER_SIZE] = {0x00, 0x01, 0x02, 0x03,
                                      0x04, 0x05, 0x06, 0x07};
    uint8_t rxData[RX_BUFFER_SIZE];
    uint8_t i;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure I2C pins
    // P1.6 = SDA, P1.7 = SCL
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN6 | GPIO_PIN7);

    // Configure I2C parameters
    USCI_B_I2C_initMasterParam i2cParam = {
        USCI_B_I2C_CLOCKSOURCE_SMCLK,      // Clock source
        1000000,                          // SMCLK frequency (1MHz)
        100000,                           // Desired I2C clock (100kHz)
    };

    // Initialize I2C
    USCI_B_I2C_initMaster(USCI_B0_BASE, &i2cParam);

    // Set slave address
    USCI_B_I2C_setSlaveAddress(USCI_B0_BASE, SLAVE_ADDRESS);

    // Set to transmitter mode
    USCI_B_I2C_setMode(USCI_B0_BASE, USCI_B_I2C_TRANSMIT_MODE);

    // Enable I2C
    USCI_B_I2C_enable(USCI_B0_BASE);

    // Configure P1.0 as output (activity indicator)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    while(1)
    {
        // Indicate start of I2C transaction
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // I2C Write transaction
        USCI_B_I2C_masterSendStart(USCI_B0_BASE);

        for(i = 0; i < TX_BUFFER_SIZE; i++)
        {
            // Wait for TX buffer to be ready
            while(USCI_B_I2C_isBusy(USCI_B0_BASE));

            // Send data
            USCI_B_I2C_transmitData(USCI_B0_BASE, txData[i]);
        }

        // Send stop condition
        USCI_B_I2C_masterSendStop(USCI_B0_BASE);

        // Wait for stop condition to complete
        while(USCI_B_I2C_isBusy(USCI_B0_BASE));

        // Small delay
        __delay_cycles(50000);

        // I2C Read transaction
        USCI_B_I2C_setMode(USCI_B0_BASE, USCI_B_I2C_RECEIVE_MODE);
        USCI_B_I2C_masterSendStart(USCI_B0_BASE);

        for(i = 0; i < RX_BUFFER_SIZE; i++)
        {
            // Wait for RX data
            while(USCI_B_I2C_isBusy(USCI_B0_BASE));

            // Read data
            rxData[i] = USCI_B_I2C_receiveData(USCI_B0_BASE);
        }

        // Send stop condition
        USCI_B_I2C_masterSendStop(USCI_B0_BASE);

        // Wait for stop condition to complete
        while(USCI_B_I2C_isBusy(USCI_B0_BASE));

        // Set back to transmit mode for next transaction
        USCI_B_I2C_setMode(USCI_B0_BASE, USCI_B_I2C_TRANSMIT_MODE);

        // Indicate end of transaction
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Delay before next transaction
        __delay_cycles(1000000); // ~1 second at 1MHz
    }
}