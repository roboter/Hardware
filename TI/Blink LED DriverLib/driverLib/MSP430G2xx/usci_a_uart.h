//*****************************************************************************
//
// usci_a_uart.h - Driver for the USCI_A UART Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_A_UART_H__
#define __MSP430WARE_USCI_A_UART_H__

#include <msp430g2553.h>

// Define standard integer types if not already defined
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

//*****************************************************************************
//
//! \brief Used in the USCI_A_UART_init() function as the param parameter.
//
//*****************************************************************************
typedef struct USCI_A_UART_initParam {
    uint8_t selectClockSource;
    uint16_t clockPrescalar;
    uint8_t firstModReg;
    uint8_t secondModReg;
    uint8_t parity;
    uint8_t msborLsbFirst;
    uint8_t numberofStopBits;
    uint8_t uartMode;
    uint8_t overSampling;
} USCI_A_UART_initParam;

// USCI UART constants
#define USCI_A_UART_MODE                             (0x00)
#define USCI_A_UART_IDLE_LINE_MULTI_PROCESSOR_MODE    (0x40)
#define USCI_A_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE  (0x80)
#define USCI_A_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE (0xC0)

#define USCI_A_UART_CLOCKSOURCE_SMCLK                 (UCSSEL_2)
#define USCI_A_UART_CLOCKSOURCE_ACLK                  (UCSSEL_1)

#define USCI_A_UART_NO_PARITY                         (0x00)
#define USCI_A_UART_ODD_PARITY                        (UCPEN)
#define USCI_A_UART_EVEN_PARITY                       (UCPEN | UCPAR)

#define USCI_A_UART_LSB_FIRST                         (0x00)
#define USCI_A_UART_MSB_FIRST                         (UCMSB)

#define USCI_A_UART_ONE_STOP_BIT                      (0x00)
#define USCI_A_UART_TWO_STOP_BITS                     (UCSPB)

#define USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  (0x01)
#define USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION (0x00)

// Function prototypes
extern void USCI_A_UART_init(uint16_t baseAddress, USCI_A_UART_initParam *param);
extern void USCI_A_UART_transmitData(uint16_t baseAddress, uint8_t transmitData);
extern uint8_t USCI_A_UART_receiveData(uint16_t baseAddress);
extern void USCI_A_UART_enable(uint16_t baseAddress);
extern void USCI_A_UART_disable(uint16_t baseAddress);
extern bool USCI_A_UART_queryStatusFlags(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_clearInterruptFlag(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_enableInterrupt(uint16_t baseAddress, uint8_t mask);
extern void USCI_A_UART_disableInterrupt(uint16_t baseAddress, uint8_t mask);

#endif // __MSP430WARE_USCI_A_UART_H__