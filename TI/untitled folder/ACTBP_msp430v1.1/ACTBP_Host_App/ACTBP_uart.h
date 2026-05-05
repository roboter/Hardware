/*******************************************************************************
 *
 *  ACTBP_uart.h - Definition file for UART communication using MSP430 USCIA 
 *                 peripheral in UART mode  
 *
 *  Copyright (C) 2011-2012 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
/** To avoid redefinition for variables declared in this header */
#ifndef _ACTBP_UART_H_
#define _ACTBP_UART_H_

#include "msp430g2553.h"
#include "C55_APRF_UIF.h"

//------------------------------------------------------------------------------
// Hardware UART definitions
//------------------------------------------------------------------------------
#define UART_RXD   0x02                     // RXD on P1.1 (UCA0RXD)
#define UART_TXD   0x04                     // TXD on P1.2 (UCA0TXD)

//------------------------------------------------------------------------------
// Conditions for 9600 Baud SW UART, SMCLK = 125kHz
//------------------------------------------------------------------------------
void UART_init(void);
void UART_reinit(void);
Status uif_writeScalar(unsigned int virtualRegisterAddr, unsigned long value, unsigned int ignore_ack);
Status uif_writeArray(unsigned int virtualRegisterAddr, unsigned int length, char* arrayToWrite);
Status uif_readScalar(unsigned int virtualRegisterAddr, unsigned long *value);

#endif
