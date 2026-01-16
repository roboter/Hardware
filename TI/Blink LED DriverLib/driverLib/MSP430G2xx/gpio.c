//*****************************************************************************
//
// gpio.c - Driver for the GPIO Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup gpio_api gpio
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <msp430g2553.h>

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT2_R__) ||\
    defined(__MSP430_HAS_PORTA_R__)
#include "gpio.h"

#include <assert.h>

// HWREG16 macro definition for TI MSP430 compiler
#ifndef HWREG16
#define HWREG16(x)     (*((volatile uint16_t *)(x)))
#endif

// Base addresses for MSP430G2553 ports
#define GPIO_PORT1_BASE    ((uint16_t)0x0020)
#define GPIO_PORT2_BASE    ((uint16_t)0x0028)

static const uint16_t GPIO_PORT_TO_BASE[] = {
    0x00,
    GPIO_PORT1_BASE,        // GPIO_PORT_P1
    GPIO_PORT2_BASE         // GPIO_PORT_P2
};

// Register offsets for MSP430G2553
#define OFS_PAIN           (0x0000)
#define OFS_PAOUT          (0x0001)
#define OFS_PADIR          (0x0002)
#define OFS_PAIFG          (0x0003)
#define OFS_PAIES          (0x0004)
#define OFS_PAIE           (0x0005)
#define OFS_PASEL          (0x0006)
#define OFS_PAREN          (0x0007)

void GPIO_setAsOutputPin(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PASEL) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PADIR) |= selectedPins;
}

void GPIO_setAsInputPin(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PASEL) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PADIR) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PAREN) &= ~selectedPins;
}

void GPIO_setAsPeripheralModuleFunctionOutputPin(uint8_t selectedPort,
                                                      uint16_t selectedPins
                                                     ,uint8_t mode) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PADIR) |= selectedPins;
    // MSP430G2553 doesn't support multiple SEL modes - just set SEL
    HWREG16(baseAddress + OFS_PASEL) |= selectedPins;
}

void GPIO_setAsPeripheralModuleFunctionInputPin(uint8_t selectedPort,
                                                     uint16_t selectedPins
                                                     ,uint8_t mode) {
    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PADIR) &= ~selectedPins;
    // MSP430G2553 doesn't support multiple SEL modes - just set SEL
    HWREG16(baseAddress + OFS_PASEL) |= selectedPins;
}

void GPIO_setOutputHighOnPin (uint8_t selectedPort,
                                   uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAOUT) |= selectedPins;
}

void GPIO_setOutputLowOnPin (uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAOUT) &= ~selectedPins;
}

void GPIO_toggleOutputOnPin (uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAOUT) ^= selectedPins;
}

void GPIO_setAsInputPinWithPullDownResistor(uint8_t selectedPort,
                                                 uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PASEL) &= ~selectedPins;

    HWREG16(baseAddress + OFS_PADIR) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PAREN) |= selectedPins;
    HWREG16(baseAddress + OFS_PAOUT) &= ~selectedPins;
}

void GPIO_setAsInputPinWithPullUpResistor(uint8_t selectedPort,
                                                uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PASEL) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PADIR) &= ~selectedPins;
    HWREG16(baseAddress + OFS_PAREN) |= selectedPins;
    HWREG16(baseAddress + OFS_PAOUT) |= selectedPins;
}

uint8_t GPIO_getInputPinValue(uint8_t selectedPort,
                                   uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return GPIO_INPUT_PIN_LOW;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    uint16_t inputPinValue = HWREG16(baseAddress + OFS_PAIN) & (selectedPins);

    if(inputPinValue > 0){
        return (GPIO_INPUT_PIN_HIGH);
    }
    return (GPIO_INPUT_PIN_LOW);
}

void GPIO_enableInterrupt(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAIE) |= selectedPins;
}

void GPIO_disableInterrupt(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAIE) &= ~selectedPins;
}

uint16_t GPIO_getInterruptStatus(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return 0;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    return (HWREG16(baseAddress + OFS_PAIFG) & selectedPins);
}

void GPIO_clearInterrupt(uint8_t selectedPort, uint16_t selectedPins) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    HWREG16(baseAddress + OFS_PAIFG) &= ~selectedPins;
}

void GPIO_selectInterruptEdge(uint8_t selectedPort, uint16_t selectedPins,
                                   uint8_t edgeSelect) {

    uint16_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    #ifndef NDEBUG
    if(baseAddress == 0xFFFF) {
        return;
    }
    #endif

    // Shift by 8 if port is even (upper 8-bits)
    if((selectedPort & 1) ^ 1) {
        selectedPins <<= 8;
    }

    if (GPIO_LOW_TO_HIGH_TRANSITION == edgeSelect){
        HWREG16(baseAddress + OFS_PAIES) &= ~selectedPins;
    }
    else {
        HWREG16(baseAddress + OFS_PAIES) |= selectedPins;
    }
}


#endif
//*****************************************************************************
//
//! Close the doxygen group for gpio_api
//! @}
//
//*****************************************************************************