//*****************************************************************************
//
// usci_a_spi.h - Driver for the USCI_A SPI Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_A_SPI_H__
#define __MSP430WARE_USCI_A_SPI_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

// USCI SPI constants
#define USCI_A_SPI_MODE_0                              (0x00)
#define USCI_A_SPI_MODE_1                              (0x04)
#define USCI_A_SPI_MODE_2                              (0x08)
#define USCI_A_SPI_MODE_3                              (0x0C)

#define USCI_A_SPI_MSB_FIRST                           (0x00)
#define USCI_A_SPI_LSB_FIRST                           (0x02)

#define USCI_A_SPI_CLOCKSOURCE_SMCLK                   (0x0080)
#define USCI_A_SPI_CLOCKSOURCE_ACLK                    (0x0000)

#define USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW        (0x00)
#define USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH       (0x10)

#define USCI_A_SPI_3PIN                                (0x00)
#define USCI_A_SPI_4PIN_UCxSTE_ACTIVE_HIGH             (0x01)
#define USCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW              (0x02)

// Function prototypes
extern void USCI_A_SPI_init(uint16_t baseAddress, uint8_t selectClockSource,
                          uint16_t clockSourceFrequency, uint16_t desiredSpiClock,
                          uint8_t msbFirst, uint8_t clockPhase, uint8_t clockPolarity);
extern void USCI_A_SPI_enable(uint16_t baseAddress);
extern void USCI_A_SPI_disable(uint16_t baseAddress);
extern uint8_t USCI_A_SPI_queryStatusFlags(uint16_t baseAddress, uint8_t mask);

#endif // __MSP430WARE_USCI_A_SPI_H__