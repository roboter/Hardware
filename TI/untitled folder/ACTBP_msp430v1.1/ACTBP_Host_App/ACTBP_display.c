/*******************************************************************************
 *
 *  ACTBP_display.c - c file for C55 booster pack display commands  
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
 * SDK
 * Texas Instruments, Inc.
 * Ver 1.0 Feb 2012
 ******************************************************************************/ 
#include "ACTBP_HostVars.h"
#include "C55_APRF_UIF.h"
#include "ACTBP_uart.h"
#include "ACTBP_filesys.h"

extern UifRegNames RegAddr;
extern UifCommand OperationVal;
extern const struct StringsDisplay displayStrings;
extern const struct StringsDirNav dirnavStrings;
extern struct ContextABP context;

//------------------------------------------------------------------------------
// Function to turn display off 
//------------------------------------------------------------------------------
void DisplayOff(void)
{
	Status status = FAILURE;

	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_DPOFF;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to turn display on 
//------------------------------------------------------------------------------
void DisplayOn(void)
{
	Status status = FAILURE;

	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_DPON;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set lines for horizontal scroll 
//------------------------------------------------------------------------------
void HScrollSet(unsigned int scroll_dir, unsigned int scroll_rate, unsigned int first_line, unsigned int last_line)
{
	unsigned int i;
	Status status = FAILURE;

	//Set scrolling parameters
	RegAddr = UIF_CMD_PARAM;
	i = ((scroll_dir<<11) + (scroll_rate<<8) + (first_line<<4) + ((last_line))); 
	status = uif_writeScalar( RegAddr, (unsigned long) i, (unsigned int) ACK_EXPECT);
	
	// Setup Scroll
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETSC;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to turn horizontal scroll on 
//------------------------------------------------------------------------------
void HScrollOn(void)
{
	Status status = FAILURE;

	// Start Scrolling
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SCON;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to turn all horizontal scroll off 
//------------------------------------------------------------------------------
void HScrollOff(void)
{
	Status status = FAILURE;

	// Stop all Scrolling
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SCOFF;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set display to a particular line to display 2 lines on screen
//------------------------------------------------------------------------------
void SetScreen(unsigned int line_from, unsigned int line_to, unsigned int vpixel_incr, unsigned int do_vscroll, unsigned int vscroll_delay)
{
	unsigned int i;
	volatile int j=0;
	Status status = FAILURE;

	OperationVal = UIF_CMD_SETVP;
	if (do_vscroll == 1)
	{
		if (line_from <= line_to)
		{
			// Scroll display up
			for (i=(line_from<<11); i<(line_to<<11); i=i+(vpixel_incr<<8))
			{
				// Write virtual plane location in PARAM virtual register in Raga
				RegAddr = UIF_CMD_PARAM;
				status = uif_writeScalar( RegAddr, (unsigned long) (i+(vpixel_incr<<8)), (unsigned int) ACK_EXPECT);
				
				// Display virtual plane on screen
				RegAddr = UIF_CMD_OPERATION;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				
				while (j<vscroll_delay)
				{
					j++;
					//__delay_cycles(0xFF);
				}
				j=0;
			}
		}
		else
		{
			// Scroll display down
			for (i=(line_from<<11); i>(line_to<<11); i=i-(vpixel_incr<<8))
			{
				// Write virtual plane location in PARAM virtual register in Raga
				RegAddr = UIF_CMD_PARAM;
				status = uif_writeScalar( RegAddr, (unsigned long) (i-(vpixel_incr<<8)), (unsigned int) ACK_EXPECT);
				
				// Display virtual plane on screen
				RegAddr = UIF_CMD_OPERATION;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);

				while (j<vscroll_delay)
				{
					j++;
					//__delay_cycles(0xFF);
				}
				j=0;
			}
		}
	}
	else
	{
		// Display screen without scroll
		// Write virtual plane location in PARAM virtual register in Raga
		RegAddr = UIF_CMD_PARAM;
		status = uif_writeScalar( RegAddr, (unsigned long) (line_to<<11), (unsigned int) ACK_EXPECT);
		
		// Display virtual plane on screen
		RegAddr = UIF_CMD_OPERATION;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	}	
}

//------------------------------------------------------------------------------
// Function to clear a line in the display
//------------------------------------------------------------------------------
void Print_ClearLine(unsigned int cursor_location)
{
	Status status = FAILURE;

	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) cursor_location, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_CLEAR_LINE;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to print "Scroll or Select" message during Directory browsing
//------------------------------------------------------------------------------
void Print_DirNav(unsigned int cursor_location)
{
	Status status = FAILURE;

	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) cursor_location, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_DIR_NAV;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to update display in Navigation mode with directory information
// OLED display is already displaying Navigation screen
//------------------------------------------------------------------------------
void UpdateDisplay_Dir(void)
{
	Status status = FAILURE;

	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_DIR, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_DIR_FIXED;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	/* Display contents of SYS_FILE using SID0 */
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_DIRNAME, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_SYS_FILE;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to update display in Navigation mode with file information
// OLED display is already displaying Navigation screen
//------------------------------------------------------------------------------
void UpdateDisplay_File(void)
{
	Status status = FAILURE;

	// Clear display line
	Print_ClearLine((unsigned long) CURSOR_FILENAME); 

	/* Display contents of SYS_FILE using SID0 */
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_FILENAME, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	RegAddr = UIF_CMD_OPERATION;
	if (context.curr_file_count != 0)
	{
		// Send command to print string in ID at the programmed location to
		// virtual screen (Send SETVP command to display on screen)
		OperationVal = PRT_SYS_FILE;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	}
	else
	{
		RegAddr = UIF_CMD_STR;
		status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.EMPTYDIR);
		
		// Assign ID to string for display
		RegAddr = UIF_CMD_OPERATION;
		OperationVal = SID_TMP;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
		// Send command to print string in ID at the programmed location to
		// virtual screen (Send SETVP command to display on screen)
		OperationVal = PRT_TMP;
		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	}
}

//------------------------------------------------------------------------------
// Function to initialize display buffers and dissplay Navigation screen 
//------------------------------------------------------------------------------
void InitDisplayScreen(void)
{
	Status status = FAILURE;

	/***********************************************/
	/* Init SID with "Scroll or Select" message */
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.DIRNAV);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_DIR_NAV;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	/* End Init SID with Scroll or Select message */
	/***********************************************/
	
	/***********************************************/
	/* Init SID with empty characters to clear line of display */
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.CLEARLINE);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_CLEAR_LINE;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	/* End Init SID with empty characters to clear line of display */
	/***********************************************/
	
	/***********************************************/
	/* Init Navigation display screen */
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.DIRFIX);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_DIR_FIXED;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	UpdateDisplay_Dir();
	Print_DirNav((unsigned long) CURSOR_DIRNAV);
	//SetScreen_Nav();
	SetScreen((unsigned int) LINE_MSG0, (unsigned int) LINE_DIRNAV, (unsigned int) 1, (unsigned int) 0, (unsigned int) 0);
	/* End Init Navigation display screen */
	/***********************************************/
	Print_ClearLine((unsigned long) 0x0000);
	Print_ClearLine((unsigned long) 0x0100);
	Print_ClearLine((unsigned long) 0x0200);
	Print_ClearLine((unsigned long) 0x0300);
}

//------------------------------------------------------------------------------
// Function to set screen to display ERROR screen if USB cable is not detected
//------------------------------------------------------------------------------
void Print_USBErr(void)
{
	Status status = FAILURE;

	/* Display USB cable not inserted error message on screen from temp SID */
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBERR1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBERR2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display USB MSC connection wait message
//------------------------------------------------------------------------------
void Print_USBMSC_Wait(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBMSC1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_MSC1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBMSC2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_MSC2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}  

//------------------------------------------------------------------------------
// Function to set screen to display USB MSC connection  message
//------------------------------------------------------------------------------
void Print_USBMSC(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBMSC3);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_MSC1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.USBMSC4);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_MSC2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}  

//------------------------------------------------------------------------------
// Function to set screen to display Sleep message
//------------------------------------------------------------------------------
void Print_Sleep(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.SLEEP1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_SLEEP1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.SLEEP2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_SLEEP2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display Wakeup message
//------------------------------------------------------------------------------
void Print_WakeUp(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.WAKEUP1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_SLEEP1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.WAKEUP2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_SLEEP2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display Power-off message
//------------------------------------------------------------------------------
void Print_PwrOff(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.PWROFF1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_PWROFF1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.PWROFF2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_PWROFF2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.PWROFF3);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_PWROFF3, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put rest of string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.PWROFF4);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_PWROFF4, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG0, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display RECORD init message
//------------------------------------------------------------------------------
void Print_RecInit(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.RECINIT1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_FILENAME, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.RECINIT2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_OPERATION, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_PLAY, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display RECORD error message
//------------------------------------------------------------------------------
void Print_RecErr(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.RECERR1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.RECERR2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to set screen to display communication error message
//------------------------------------------------------------------------------
void Print_CommErr(void)
{
	Status status = FAILURE;

	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.COMMERR1);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR1, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Put string for display into STR virtual register in Raga
	RegAddr = UIF_CMD_STR;
	status = uif_writeArray( RegAddr, (unsigned int) 21, (char *) displayStrings.COMMERR2);
	
	// Assign ID to string for display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = SID_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write cursor location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) CURSOR_USB_ERR2, (unsigned int) ACK_EXPECT);
	
	// Send command to set the cursor location from PARAM register to display
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETCUR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Send command to print string in ID at the programmed location to
	// virtual screen (Send SETVP command to display on screen)
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = PRT_TMP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	
	// Write virtual plane location in PARAM virtual register in Raga
	RegAddr = UIF_CMD_PARAM;
	status = uif_writeScalar( RegAddr, (unsigned long) VP_MSG1, (unsigned int) ACK_EXPECT);
	
	// Display virtual plane on screen
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_SETVP;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}
