/*******************************************************************************
 *
 *  C55_ABP_uart.c - c file for UART communication using MSP430 USCIA peripheral
 *                   in UART mode  
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
/******************************************************************************
 * SDK & KE
 * Texas Instruments, Inc.
 * Ver 1.0 Feb 2012
 ******************************************************************************/ 
#include "ACTBP_uart.h"

unsigned char *txData;
unsigned char numofbytes;
unsigned int i=0, j=0;
char ScalarBuff[21];
char WriteAckBuff[LEN_OF_ACK_PACKET];
unsigned int WriteCount = 0, ReadCount=0;
unsigned char write_flag = 0, read_flag = 0;
extern unsigned int timeout_count;

//------------------------------------------------------------------------------
// Function configures UART for full-duplex operation at 9600 bps
//------------------------------------------------------------------------------
void UART_init(void)
{
	UCA0CTL1 |= UCSWRST;                    // **Put USCI in to reset**
	UCA0CTL1 |= UCSSEL_2;                   // CLK = SMCLK (1MHz)
	UCA0BR0 = 0x68;                         // 1MHz/9600 = INT(104.16) = 0x68
	UCA0BR1 = 0x00;                         //
	UCA0MCTL = UCBRS0;                      // Modulation UCBRSx = 2(tried 1 = round((8*(104.16-104))) does not work)
	P1DIR |= UART_TXD;                      // TXD
	P1DIR &= ~UART_RXD;
	P1SEL |= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1SEL2|= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
}

//------------------------------------------------------------------------------
// Function configures UART for full-duplex operation at 19200 bps
//------------------------------------------------------------------------------
void UART_reinit(void)
{
	UCA0CTL1 |= UCSWRST;                    // **Put USCI in to reset**
	UCA0CTL1 |= UCSSEL_2;                   // CLK = SMCLK (1MHz)
	UCA0BR0 = 0x34;                         // 1MHz/19200 = INT(52.08) = 0x34
	UCA0MCTL = 0;                           // Modulation UCBRSx = 0 = round((8*(52.08-52)))
	UCA0BR1 = 0x00;                         //
	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
	if (i == WriteCount)                      // TX over?
	{
		IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
		write_flag = 0;
		i=0;
		__bic_SR_register_on_exit(LPM0_bits+GIE);
	}
	else
	{
		UCA0TXBUF = ScalarBuff[i++];
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	ScalarBuff[j++] = UCA0RXBUF;
	if (j == ReadCount)                     // RX expected number of bytes?
	{
		IE2 &= ~UCA0RXIE;                     // Disable USCI_A0 RX interrupt
		read_flag = 0;
		j=0;
		__bic_SR_register_on_exit(LPM0_bits+GIE);
	}
}

/**
 *  \brief Write method for scalar instructions
 *
 *  This function writes the scalar values to the port by encoding in the required format
 *
 *  @param uif [IN] Resource handle
 *  @param virtualRegisterAddr [IN] virtual address of the instruction to write
 *  @param value [IN] The value to write for the register
 *  @param timeout [IN] Appropriate timeout value for writing
 *
 *  @return Status is success or failure
 */
Status uif_writeScalar(unsigned int virtualRegisterAddr, unsigned long value, unsigned int ignore_ack)
{
	i=0;
	int ackData = SUCCESS;
	volatile Status status = 2;
	write_flag = 1;
	
	P1SEL |= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1SEL2|= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1DIR |= UART_TXD;                      // TXD
	P1DIR &= ~UART_RXD;
	IE2 |= (UCA0TXIE + UCA0RXIE);           // Enable USCI_A0 TX & RX interrupt
	
	/* Form the scalar write buffer content to be written */
	ScalarBuff[0] = UIF_WRITE_SCALAR_DATA;
	ScalarBuff[1] = virtualRegisterAddr;
	ScalarBuff[2] = (char)((value >> 24) & 0xff);
	ScalarBuff[3] = (char)((value >> 16) & 0xff);
	ScalarBuff[4] = (char)((value >> 8) & 0xff);
	ScalarBuff[5] = (char)((value & 0xff));
	
	/* Write value to port */
	WriteCount = UIF_SCALAR_CMD_PKT_SIZE;
	UCA0TXBUF = ScalarBuff[i++];                // TX character
	timeout_count = 1;
	TA0CCR0 = 34500; // 23s delay
	TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
	TA0CCTL0 &= ~CCIFG;
	TA0CCTL0 |= CCIE; //enable timer interrupt
	__bis_SR_register( LPM0_bits + GIE);
	while (write_flag) ;
	TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	TA0CTL &= ~MC_3; //stop the timer
	timeout_count = 0;


	if (!ignore_ack)
	{
		j=0;
		read_flag = 1;
		ReadCount = LEN_OF_ACK_PACKET;
		timeout_count = 1;
		TA0CCR0 = 34500; // 23s delay
		TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
		TA0CCTL0 &= ~CCIFG;
		TA0CCTL0 |= CCIE; //enable timer interrupt
		__bis_SR_register( LPM0_bits + GIE);
		TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
		TA0CTL &= ~MC_3; //stop the timer
		timeout_count = 0;
		
		ackData = ScalarBuff[4] & 0xff;
		ackData <<= 8;
		ackData |= ScalarBuff[5] & 0xff;
		/* If only the ack packet is appropriate flag success */
//		if ((UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])&&(SUCCESS==ackData))
		if (UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])
		{
			status = ackData;
		}
		else
		{
			/* Write request was not decoded appropriately at Raga. */
			status = FAILURE;
		}
	}
	else
	{
		IE2 &= ~UCA0RXIE;                      // Disable USCI_A0 RX interrupt
		status = SUCCESS;
	}
	return status;
}

/**
 *  \brief Write method for array instructions
 *
 *  This function writes the array values to the port by encoding in the required format
 *
 *  @param uif [IN] Resource handle
 *  @param virtualRegisterAddr [IN] Virtual address of the instruction to write
 *  @param length [IN] The length of array to write
 *  @param arrayToWrite [IN] The array content to be written
 *
 *  \return Status is success or failure
 */
Status uif_writeArray(unsigned int virtualRegisterAddr, unsigned int length, char* arrayToWrite)
{
	/* Local variables */
	int ackData = SUCCESS;
	volatile Status status = 2;
	
	i=0;
	j=0;
	write_flag = 1;
	read_flag = 1;
	ReadCount = LEN_OF_ACK_PACKET;
	
	P1SEL |= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1SEL2|= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1DIR |= UART_TXD;                      // TXD
	P1DIR &= ~UART_RXD;
	IE2 |= (UCA0TXIE + UCA0RXIE);           // Enable USCI_A0 TX & RX interrupt
	
	/* Formalize the data packet to send indicating the length of array to expect */
	ScalarBuff[0] = UIF_WRITE_ARRAY_DATA;
	ScalarBuff[1] = virtualRegisterAddr;
	ScalarBuff[2] = 0;
	ScalarBuff[3] = 0;
	ScalarBuff[4] = (char)((length >> 8) & 0xff);
	ScalarBuff[5] = (char)(length & 0xff);
	
	/* Write value to port */
	WriteCount = UIF_SCALAR_CMD_PKT_SIZE;
	UCA0TXBUF = ScalarBuff[i++];            // TX character
	timeout_count = 1;
	TA0CCR0 = 34500; // 23s delay
	TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
	TA0CCTL0 &= ~CCIFG;
	TA0CCTL0 |= CCIE; //enable timer interrupt
	__bis_SR_register( LPM0_bits + GIE);
	while (write_flag) ;
	TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	TA0CTL &= ~MC_3; //stop the timer
	timeout_count = 0;
	 
	 /* Read Ack from Raga that it has read the packet correctly */
	timeout_count = 1;
	TA0CCR0 = 34500; // 23s delay
	TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
	TA0CCTL0 &= ~CCIFG;
	TA0CCTL0 |= CCIE; //enable timer interrupt
	__bis_SR_register( LPM0_bits + GIE);
	while (read_flag) ;
	TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	TA0CTL &= ~MC_3; //stop the timer
	timeout_count = 0;
	 
	ackData = ScalarBuff[4] & 0xff;
	ackData <<= 8;
	ackData |= ScalarBuff[5] & 0xff;
	 
	/* If only the ack packet is appropriate flag success */
//	if ((UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])&&(SUCCESS==ackData))
	if (UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])
	{
		status = ackData;
	}
	else
	{
	 	/* Write request was not decoded appropriately at Raga. */
	 	status = FAILURE;
	}
 
	for (i=0; i<length; i++)
	{
	 	ScalarBuff[i] = arrayToWrite[i];
	}
	 
//	if (status == SUCCESS)
//	{
		/* Write value to port */
		IE2 |= (UCA0TXIE + UCA0RXIE);           // Enable USCI_A0 TX & RX interrupt
		write_flag = 1;
		WriteCount = length;
		i=0;
		UCA0TXBUF = ScalarBuff[i++];            // TX character
		timeout_count = 1;
		TA0CCR0 = 34500; // 23s delay
		TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
		TA0CCTL0 &= ~CCIFG;
		TA0CCTL0 |= CCIE; //enable timer interrupt
		__bis_SR_register( LPM0_bits + GIE);
		while (write_flag) ;
		TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
		TA0CTL &= ~MC_3; //stop the timer
		timeout_count = 0;
		
		/* Read Ack from Raga that it has read the packet correctly */
		j=0;
		IE2 |= UCA0RXIE;           // Enable USCI_A0 RX interrupt
		ReadCount = LEN_OF_ACK_PACKET;
		read_flag = 1;
		timeout_count = 1;
		TA0CCR0 = 34500; // 23s delay
		TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
		TA0CCTL0 &= ~CCIFG;
		TA0CCTL0 |= CCIE; //enable timer interrupt
		__bis_SR_register( LPM0_bits + GIE);
		while (read_flag) ;
		TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
		TA0CTL &= ~MC_3; //stop the timer
		timeout_count = 0;
		
		ackData = (ScalarBuff[4]) & 0xff;
		ackData <<= 8;
		ackData |= (ScalarBuff[5]) & 0xff;
		
		/* If only the ack packet is appropriate flag success */
//		if ((UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])&&(SUCCESS==ackData))
		if (UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])
		{
		 	status = ackData;
		}
		else
		{
		 	/* Write request was not decoded appropriately at Raga. */
		 	status = FAILURE;
		}
//	}
	return status;
}

/**
 *  \brief Read method for scalar instructions
 *
 *  This function reads the scalar values to the port by encoding in the required format
 *
 *  @param hPortHandle [IN] Resource handle
 *  @param virtualRegisterAddr [IN] virtual address of the instruction to write
 *  @param value [OUT] The scalar content read
 *
 *  @return Status if success or failure
 */

Status uif_readScalar(unsigned int virtualRegisterAddr, unsigned long *value)
{
	/* Local variables */
	int ackData = SUCCESS;
	volatile Status status = 2;
	
	i=0;
	write_flag = 1;
	
	P1SEL |= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1SEL2|= UART_TXD + UART_RXD;           // Timer function for TXD/RXD pins
	P1DIR |= UART_TXD;                      // TXD
	P1DIR &= ~UART_RXD;
	IE2 |= (UCA0TXIE + UCA0RXIE);           // Enable USCI_A0 TX & RX interrupt
	
	/* Send request packet */
	ScalarBuff[0] = UIF_READ_SCALAR_DATA;
	ScalarBuff[1] = virtualRegisterAddr;
	ScalarBuff[2] = RSV0;
	ScalarBuff[3] = RSV1;
	ScalarBuff[4] = RSV2;
	ScalarBuff[5] = RSV3;
	
	/* Write value to port */
	WriteCount = UIF_SCALAR_CMD_PKT_SIZE;
	UCA0TXBUF = ScalarBuff[i++];            // TX character
	timeout_count = 1;
	TA0CCR0 = 34500; // 23s delay
	TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
	TA0CCTL0 &= ~CCIFG;
	TA0CCTL0 |= CCIE; //enable timer interrupt
	__bis_SR_register( LPM0_bits + GIE);
	while (write_flag) ;
	TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	TA0CTL &= ~MC_3; //stop the timer
	timeout_count = 0;
	
	j=0;
	read_flag = 1;
	ReadCount = LEN_OF_ACK_PACKET;
	timeout_count = 1;
	TA0CCR0 = 34500; // 23s delay
	TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
	TA0CCTL0 &= ~CCIFG;
	TA0CCTL0 |= CCIE; //enable timer interrupt
	__bis_SR_register( LPM0_bits + GIE);
	while (read_flag) ;
	TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	TA0CTL &= ~MC_3; //stop the timer
	timeout_count = 0;
	  
	ackData = ScalarBuff[4] & 0xff;
	ackData <<= 8;
	ackData |= ScalarBuff[5] & 0xff;
	
	/* If only the ack packet is appropriate flag success */
//	if ((UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])&&(SUCCESS==ackData))
	if (UIF_WRITE_COMPLETION_ACK==ScalarBuff[0])
	{
		status = ackData;
	}
	else
	{
		/* Write request was not decoded appropriately at Raga. */
		status = FAILURE;
	}
	
//	if (status == SUCCESS)
//	{
		j=0;
		IE2 |= UCA0RXIE;           // Enable USCI_A0 RX interrupt
		ReadCount = LEN_OF_RESPONSEPACKET;
		read_flag = 1;
		timeout_count = 1;
		TA0CCR0 = 34500; // 23s delay
		TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
		TA0CCTL0 &= ~CCIFG;
		TA0CCTL0 |= CCIE; //enable timer interrupt
		__bis_SR_register( LPM0_bits + GIE);
		while (read_flag) ;
		TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
		TA0CTL &= ~MC_3; //stop the timer
		timeout_count = 0;
		
		/* Read the encoded content to the port */
		*value  = ((long)ScalarBuff[0] & 0xFF) << 24;
		*value |= ((long)ScalarBuff[1] & 0xFF) << 16;
		*value |= ((long)ScalarBuff[2] & 0xFF) << 8;
		*value |= (long)ScalarBuff[3] & 0xFF;
		
		/* Send ack that the array content has been read */
		IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
		ScalarBuff[0] = UIF_READ_COMPLETION_ACK;
		ScalarBuff[1] = virtualRegisterAddr;
		ScalarBuff[2] = RSV0;
		ScalarBuff[3] = RSV1;
		ScalarBuff[4] = RSV2;
		ScalarBuff[5] = RSV3;
		
		/* Write request */
		/* Write value to port */
		write_flag = 1;
		WriteCount = UIF_SCALAR_CMD_PKT_SIZE;
		UCA0TXBUF = ScalarBuff[i++];            // TX character
		timeout_count = 1;
		TA0CCR0 = 34500; // 23s delay
		TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 12kHz/8 = 1.5kHz, Up Mode, Clear TAR, start timer*/
		TA0CCTL0 &= ~CCIFG;
		TA0CCTL0 |= CCIE; //enable timer interrupt
		__bis_SR_register( LPM0_bits + GIE);
		while (write_flag) ;
		TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
		TA0CTL &= ~MC_3; //stop the timer
		timeout_count = 0;
//	}
	return status;
}
