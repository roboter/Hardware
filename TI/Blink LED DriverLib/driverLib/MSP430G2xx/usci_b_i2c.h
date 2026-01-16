//*****************************************************************************
//
// usci_b_i2c.h - Driver for the USCI_B_I2C Module for MSP430G2xx family.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_B_I2C_H__
#define __MSP430WARE_USCI_B_I2C_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_USCI_Bx__

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \brief Used in the USCI_B_I2C_initMaster() function as the param parameter.
//
//*****************************************************************************
typedef struct USCI_B_I2C_initMasterParam {
    uint8_t selectClockSource;
    uint32_t i2cClk;
    uint32_t dataRate;
} USCI_B_I2C_initMasterParam;

//*****************************************************************************
//
// Clock sources
//
//*****************************************************************************
#define USCI_B_I2C_CLOCKSOURCE_UCKLCLK                            UCSSEL_0
#define USCI_B_I2C_CLOCKSOURCE_ACLK                                UCSSEL_1
#define USCI_B_I2C_CLOCKSOURCE_SMCLK                               UCSSEL_2

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern void USCI_B_I2C_initMaster(uint16_t baseAddress,
                                   USCI_B_I2C_initMasterParam *param);
extern void USCI_B_I2C_setSlaveAddress(uint16_t baseAddress,
                                       uint8_t slaveAddress);
extern void USCI_B_I2C_setMode(uint16_t baseAddress, uint8_t mode);
extern void USCI_B_I2C_transmitData(uint16_t baseAddress, uint8_t transmitData);
extern uint8_t USCI_B_I2C_receiveData(uint16_t baseAddress);
extern void USCI_B_I2C_masterSendStart(uint16_t baseAddress);
extern void USCI_B_I2C_masterSendStop(uint16_t baseAddress);
extern void USCI_B_I2C_enable(uint16_t baseAddress);
extern void USCI_B_I2C_disable(uint16_t baseAddress);
extern bool USCI_B_I2C_isBusy(uint16_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif // __MSP430_HAS_USCI_Bx__

#endif // __MSP430WARE_USCI_B_I2C_H__
