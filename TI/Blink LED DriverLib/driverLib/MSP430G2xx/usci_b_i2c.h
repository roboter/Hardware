//*****************************************************************************
//
// usci_b_i2c.h - Driver for the USCI_B I2C Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_B_I2C_H__
#define __MSP430WARE_USCI_B_I2C_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

// USCI I2C constants
#define USCI_B_I2C_TRANSMIT_MODE                       (0x00)
#define USCI_B_I2C_RECEIVE_MODE                        (0x01)

#define USCI_B_I2C_CLOCKSOURCE_SMCLK                   (0x0080)
#define USCI_B_I2C_CLOCKSOURCE_ACLK                    (0x0000)

#define USCI_B_I2C_SET_DATA_RATE_400KBPS               (0x0001)
#define USCI_B_I2C_SET_DATA_RATE_100KBPS               (0x0000)

// Function prototypes
extern void USCI_B_I2C_init(uint16_t baseAddress, uint8_t selectClockSource,
                          uint16_t clockSourceFrequency, uint16_t dataRate);
extern void USCI_B_I2C_enable(uint16_t baseAddress);
extern void USCI_B_I2C_disable(uint16_t baseAddress);
extern void USCI_B_I2C_setSlaveAddress(uint16_t baseAddress, uint8_t slaveAddress);
extern uint8_t USCI_B_I2C_getInterruptStatus(uint16_t baseAddress, uint8_t mask);

#endif // __MSP430WARE_USCI_B_I2C_H__