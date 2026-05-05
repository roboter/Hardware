/*******************************************************************************
 *
 *  ACTBP_timer.c - c file for MSP430 timer peripheral
 *
 *  Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/ 
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
#include "ACTBP_timer.h"

extern unsigned int timeout_count;

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
	unsigned char i, j;
	if(timeout_count == 0)
	{
      __bic_SR_register_on_exit(LPM3_bits+GIE); 
	}
	else //timed out due to communication hang-up
	{
		P1OUT = 0;
		for (i=0; i<30; i++)
		{
			for (j=0; j<100; j++)
			{
				P1OUT = BIT4+BIT5+BIT6+BIT7;
				__delay_cycles(10000);
				P1OUT = BIT3;
				__delay_cycles(10000);
			}
			P1OUT = 0;
			__delay_cycles(200000);
		}
		P2OUT &= ~BIT7; // make sure DSP is powered down    
	    __delay_cycles(16000000);
		WDTCTL = 0; //reset the part by writing bad watchdog password
	}
}

// Timer A1 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
{
	//stop the timer
	TA1CTL &= ~MC_3;
	//come out of LPM on exit
	__bic_SR_register_on_exit(LPM3_bits+GIE);
}
