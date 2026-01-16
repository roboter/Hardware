//*****************************************************************************
//
// usci_a_spi.h - Driver for the USCI_A_SPI Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_A_SPI_H__
#define __MSP430WARE_USCI_A_SPI_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_USCI_Ax__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \brief Used in the USCI_A_SPI_init() function as the param parameter.
//
//*****************************************************************************
typedef struct USCI_A_SPI_initParam {
    uint8_t selectClockSource;
    uint16_t clockSourceFrequency;
    uint16_t desiredSpiClock;
    uint8_t msbOrLsbFirst;
    uint8_t clockPhase;
    uint8_t clockPolarity;
    uint8_t spiMode;
} USCI_A_SPI_initParam;

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define USCI_A_SPI_CLOCKSOURCE_UCKLCLK                            UCSSEL_0
#define USCI_A_SPI_CLOCKSOURCE_ACLK                                UCSSEL_1
#define USCI_A_SPI_CLOCKSOURCE_SMCLK                               UCSSEL_2

//*****************************************************************************
//
// SPI modes
//
//*****************************************************************************
#define USCI_A_SPI_3PIN                                            0x0000
#define USCI_A_SPI_4PIN_UCxSTE_ACTIVE_HIGH                         0x0001
#define USCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW                          0x0002

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void USCI_A_SPI_init(uint16_t baseAddress,
                            USCI_A_SPI_initParam *param);
extern void USCI_A_SPI_transmitData(uint16_t baseAddress, uint8_t transmitData);
extern uint8_t USCI_A_SPI_receiveData(uint16_t baseAddress);
extern void USCI_A_SPI_enable(uint16_t baseAddress);
extern void USCI_A_SPI_disable(uint16_t baseAddress);
extern bool USCI_A_SPI_isBusy(uint16_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_USCI_Ax__

#endif // __MSP430WARE_USCI_A_SPI_H__
