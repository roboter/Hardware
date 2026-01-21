/**
 * @file flashctl_example.c
 * @brief FlashCtl peripheral example for MSP430G2xx
 *
 * This example demonstrates flash memory operations:
 * - Erase a flash segment
 * - Write data to flash
 * - Read and verify data
 * - Demonstrate flash wear with LED feedback
 */

#include <msp430g2553.h>
#include <string.h>
#include "driverlib.h"

#define FLASH_SEGMENT_SIZE 512
#define TEST_DATA_SIZE 32

// Define a flash segment for testing (use caution with actual flash addresses)
// This should be a writable flash segment, not the segment containing code
#pragma DATA_SECTION(testData, ".infoA")
uint8_t testData[TEST_DATA_SIZE];

const uint8_t originalData[TEST_DATA_SIZE] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
    0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87,
    0x98, 0xA9, 0xBA, 0xCB, 0xDC, 0xED, 0xFE, 0x0F
};

void main(void)
{
    uint8_t i;
    uint8_t verifyOk = 0;
    uint32_t writeCount = 0;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Configure LEDs
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Success indicator
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6); // Activity indicator

    // Setup flash timing for safe operation
    // Assuming 1MHz SMCLK, target ~200kHz flash clock
    FlashCtl_setupClock(200000, BCS_getSMCLKFrequency(), 0);

    while(1)
    {
        // Indicate start of flash operation
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);

        // Erase the flash segment
        FlashCtl_eraseSegment(testData);

        // Verify erase (should be all 0xFF)
        verifyOk = 1;
        for(i = 0; i < TEST_DATA_SIZE; i++)
        {
            if(testData[i] != 0xFF)
            {
                verifyOk = 0;
                break;
            }
        }

        if(verifyOk)
        {
            // Write data to flash
            FlashCtl_write8(originalData, testData, TEST_DATA_SIZE);

            // Verify write operation
            verifyOk = 1;
            for(i = 0; i < TEST_DATA_SIZE; i++)
            {
                if(testData[i] != originalData[i])
                {
                    verifyOk = 0;
                    break;
                }
            }

            if(verifyOk)
            {
                // Success - turn on green LED
                GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                writeCount++;
            }
            else
            {
                // Write failed - turn off green LED
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            }
        }
        else
        {
            // Erase failed - turn off green LED
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }

        // Indicate end of flash operation
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);

        // Delay before next operation (visual feedback)
        // Shorter delay for successful operations, longer for failures
        if(verifyOk)
        {
            __delay_cycles(500000); // ~0.5 seconds
        }
        else
        {
            __delay_cycles(2000000); // ~2 seconds
        }
    }
}