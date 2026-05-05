/*******************************************************************************
 *
 *  ACTBP_test.c
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
 *
 ******************************************************************************/
 
/******************************************************************************
 * SDK
 * Texas Instruments, Inc.
 * Ver 1.0 Feb 2012
 ******************************************************************************/ 
#include "CTS_Layer.h"
#include <msp430g2553.h>
#include "ACTBP_uart.h"
#include "ACTBP_HostVars.h"
#include "ACTBP_display.h"
#include "ACTBP_filesys.h"
#include "ACTBP_capinput.h"

struct TMSG
{
	char String[16];
	unsigned int Cursor;
	unsigned int Length;
};

const struct TMSG msg[] = 
{
	{"Touch Center LED", 0x0000, 16},
	{" To Agree To Be ", 0x0100, 16},
	{"  Bound By The  ", 0x0200, 16},
	{" ACTBP License  ", 0x0300, 16},
};	

#pragma DATA_SECTION(tresult, ".infoD");
unsigned int tresult;

extern UifRegNames RegAddr;
extern UifCommand OperationVal;
extern struct ContextABP context;
extern unsigned char eventFlag;
 
void Test_ACTBP(void)
{
	char *Flash_ptr;
	unsigned int i=0, j=0;
	char val;
    Status status = FAILURE;
    	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG0, (unsigned int) ACK_EXPECT);
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	for (i=0; i<4; i++)
	{
		// Put string for display into STR virtual register in Raga
		RegAddr = UIF_CMD_STR;
		status = uif_writeArray( RegAddr, (unsigned int) msg[i].Length, (char *) msg[i].String);
		// Assign ID to string for display
		RegAddr = UIF_CMD_OPERATION;
		OperationVal = SID_TMP;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		// Write cursor location in PARAM virtual register in Raga
		RegAddr = UIF_CMD_PARAM;
		status = uif_writeScalar( RegAddr, (unsigned long) msg[i].Cursor, (unsigned int) ACK_EXPECT);
		// Send command to set the cursor location from PARAM register to display
		RegAddr = UIF_CMD_OPERATION;
		OperationVal = UIF_CMD_SETCUR;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		// Send command to print string in ID at the programmed location to
		// virtual screen (Send SETVP command to display on screen)
		RegAddr = UIF_CMD_OPERATION;
		OperationVal = PRT_TMP;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	}

	OperationVal = UIF_CMD_SETVP;
	Flash_ptr = (char *) &tresult;
    //while (eventFlag == 0)
    while (!j)
    {
		// Write virtual plane location in PARAM virtual register in Raga
		RegAddr = UIF_CMD_PARAM;
		status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG0, (unsigned int) ACK_EXPECT);
		// Display virtual plane on screen
		RegAddr = UIF_CMD_OPERATION;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
   		__delay_cycles(8000000);
   		P1OUT = P1OUT | BIT0; //Center LED turns on
    	for (i=VP_MSG0; i<=VP_MSG1; i=i+0x0100)
    	{
    		// Write virtual plane location in PARAM virtual register in Raga
    		RegAddr = UIF_CMD_PARAM;
    		status = uif_writeScalar( RegAddr, (unsigned long) i, (unsigned int) ACK_EXPECT);
    		// Display virtual plane on screen
    		RegAddr = UIF_CMD_OPERATION;
    		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
     		j = TI_CAPT_Button(&middle_button);
     		if (j)
     		{
     			break;
     		}
     		__delay_cycles(0xFFFFF);     		
    	}
    	__delay_cycles(8000000);    	
    }
    
    P1OUT = P1OUT & ~BIT0; //Turn off Center LED
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
	DCOCTL = CALDCO_1MHZ;
	FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
	FCTL3 = FWKEY;
	FCTL1 = FWKEY + WRT;
	val = T_SUCCESS & 0xFF;
	*Flash_ptr++ = val;
	val = (T_SUCCESS>>8) & 0xFF;
	*Flash_ptr-- = val;
	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;
	BCSCTL2 |= DIVS_3;
 }
