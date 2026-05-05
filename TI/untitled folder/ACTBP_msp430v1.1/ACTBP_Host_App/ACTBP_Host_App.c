/*******************************************************************************
 *
 *  ACTBP_Host_App.c
 *     - MSP430 firmware application for the LaunchPad Audio Capacitive Touch 
 *       Booster Pack
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
 *
 ******************************************************************************/
 
/******************************************************************************
 *         C5000 Audio Capacitive Touch Booster Pack Host Application
 * 
 * SDK, KE & DD
 * Texas Instruments, Inc.
 * Ver 1.1 Feb 2012
 ******************************************************************************/ 
#include "CTS_Layer.h"
#include "ACTBP_uart.h"
#include "ACTBP_capinput.h"
#include "ACTBP_timer.h"
#include "ACTBP_HostVars.h"
#include "ACTBP_display.h"
#include "ACTBP_filesys.h"

unsigned int deltaCnts[1];
unsigned int timeout_count=0;
unsigned char eventFlag = 0;
extern unsigned int tresult;
void Test_ACTBP(void);
struct ContextABP context = {
	INVALID_EVNT, //current_event
	NO_HOLD,      //last_event
	BROWSE_DIR,   //current_state
	PWR_OFF,      //last_state
	0,            //curr_dir_num
	0,            //curr_file_num
	0,            //curr_dir_count
	0,            //root_dir_count
	0,            //curr_file_count
	0,            //curr_volume
	0,            //curr_play_status
	0,            //curr_record_status
	OFF,          //shuffle_status
	OFF,          //cycle_status
	OFF,          //USB_cableinsert
	OFF           //disable_command
};
const struct StringsDirNav dirnavStrings = {
	"\\",         //dirnavStrings.ROOT_DIR 
	".",          //dirnavStrings.CURRENT_DIR
	"RecDir",     //dirnavStrings.RECORD_DIR
};
const struct StringsDisplay displayStrings = {
	"                     ",    //displayStrings.CLEARLINE
	"Scroll or Select     ",    //displayStrings.DIRNAV 
	"DIR:                 ",    //displayStrings.DIRFIX
	"   < Empty >         ",    //displayStrings.EMPTYDIR
	"Entering Record      ",    //displayStrings.RECINIT1
	"Please Wait....      ",    //displayStrings.RECINIT2
	" Delete Files        ",    //displayStrings.RECERR1
	"And Try Again..      ",    //displayStrings.RECERR2
	"  Enabling USB       ",    //displayStrings.USBMSC1
	"Mass Storage....     ",    //displayStrings.USBMSC2
	"USB Mass Storage     ",    //displayStrings.USBMSC3
	" Device Enabled      ",    //displayStrings.USBMSC4
	"Attach USB Cable     ",    //displayStrings.USBERR1
	" And Try Again       ",    //displayStrings.USBERR2
	"Feeling Sleepy..     ",    //displayStrings.SLEEP1
	"	ZZZzzzz           ",    //displayStrings.SLEEP2
	"Ah...You're Back     ",    //displayStrings.WAKEUP1	
	"  Let's Rock!!       ",    //displayStrings.WAKEUP2	
	"Hui Tou Jian...      ",    //displayStrings.PWROFF1 
	"Hasta La Vista..     ",    //displayStrings.PWROFF2 
	"   Ciao...           ",    //displayStrings.PWROFF3 
	" And Goodbye!        ",    //displayStrings.PWROFF4 
	" Communication       ",    //displayStrings.COMMERR1 
	"     Error           ",    //displayStrings.COMMERR2 
};

UifRegNames RegAddr;
UifCommand OperationVal;    
UifPlayStatus PlayStatusVal;
UifUsbStatus USBMSCControl;

/*----------------- LED definition---------------------------------------------
 * There are 8 LEDs to represent different positions around the wheel. They are 
 * controlled by 5 pins of Port 1 using a muxing scheme.
 * --------------------------------------------------------------------
 *    Diode  LED        GPO Bit Setting     Position (degrees, clockwise)
 * --------------------------------------------------------------------
 * --RIGHT SIDE (looking on the underside of the ACTBP)--
 *       D8             BIT3,(BIT5,6,7)    45
 *       D12            BIT4,!BIT3         80
 *       D9             BIT3,(BIT4,6,7)    100
 *       D10            BIT5,!BIT3         135
 * --LEFT SIDE (looking on the underside of the ACTBP)--
 *       D7             BIT3,(BIT4,5,7)    225
 *       D11            BIT6,!BIT3         260
 *       D6             BIT3,(BIT4,5,6)    280
 *       D13            BIT7,!BIT3         315
 *----------------------------------------------------------------------------*/
#define MASK45                  (BIT3+BIT5+BIT6+BIT7)
#define MASK80                  BIT4
#define MASK100                 (BIT3+BIT4+BIT6+BIT7)
#define MASK135                 BIT5
#define MASK225                 (BIT3+BIT4+BIT5+BIT7)
#define MASK260                 BIT6
#define MASK280                 (BIT3+BIT4+BIT5+BIT6)
#define MASK315                 BIT7

const unsigned char LedWheelPosition[16] = 
                                {
                                  MASK45, MASK315, MASK315, MASK280,
                                  MASK280, MASK260, MASK260, MASK225,
                                  MASK225, MASK135, MASK135, MASK100, 
                                  MASK100, MASK80, MASK80, MASK45 
                                };

const unsigned char startSequence[8] = 
                                {
								    MASK315,
								    MASK280,
								    MASK260,
								    MASK225,
								    MASK135,
								    MASK100,
								    MASK80,
								    MASK45
								};
/*----------------- LED definition------------------------------*/

/*----------------- LaunchPad MSP430 Initialization-----------------------------
 * Configure Clock, USCI peripheral and IO ports on the MSP430 
 *----------------------------------------------------------------------------*/
void InitLaunchPadCore(void)
{
	BCSCTL1 |= DIVA_0;                    // ACLK/(0:1,1:2,2:4,3:8)
	BCSCTL3 |= LFXT1S_2;                  // LFXT1 = VLO
	
	// Port init
	P2SEL = 0x00;                         // No XTAL
	P2DIR |= (BIT0+BIT4+BIT2+BIT3+BIT1+BIT5+BIT6+BIT7);
	P2OUT &= ~(BIT0+BIT4+BIT2+BIT3+BIT1+BIT5+BIT6+BIT7);
	P2OUT &= ~BIT7;                       // make sure DSP is powered down    
	P1OUT &= ~(BIT3+BIT4+BIT5+BIT6+BIT7+BIT0);
	P1DIR |= BIT3+BIT4+BIT5+BIT6+BIT7+BIT0;
	// Initialize USCI peripheral to UART mode with 9600 bps baurd rate
	UART_init();
	// Turn on DSP
	P2OUT |= BIT7;
}
/*----------------- LaunchPad MSP430 Initialization----------------------------*/

/*--Initialize Audio Player Recorder Framework and OLED display on the ACTBP----
 * Configures the initial state of the APRF software running on the  
 *----------------------------------------------------------------------------*/
void InitC55ABP(void)
{
	Status status = FAILURE;
	
	// Use 430 timer for delay, go to lpm3 while we wait for the DSP to initialize
	// the APRF software 
	TA1CCR0 = 24000; //4 second delay
	TA1CCTL0 |= CCIE; //enable timer interrupt
	TA1CCTL0 &= ~CCIFG; //make sure flag is clear
	TA1CTL = TASSEL_1 + ID_1 + MC_1 + TACLR; //TACLK = ACLK/2 = 6kHz, Up Mode, Clear TAR, start timer
	__bis_SR_register(LPM3_bits + GIE); //go to LPM3 until woken by the timer
	TA1CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts

	// Scroll horizontally the default welcome message displayed by the APRF
	HScrollSet((unsigned int) SCROLL_H_LEFT, (unsigned int) SCROLL_H_RATE1, (unsigned int) 0x00, (unsigned int) 0x01);
	HScrollOn();
	__delay_cycles(4000000);	
	HScrollOff();
	__delay_cycles(12000000);	
	
	// Send command to chang baud rate of UART communication to APRF from 
	// default value of 9600 bps to 19200bps for faster response
	RegAddr = UIF_CMD_BAUDRATE;
	status = uif_writeScalar( RegAddr, (unsigned long)19200, (unsigned int) ACK_EXPECT);
	__delay_cycles(800000);
	// Reinitialize MSP430 UART to match new baud rate 
	UART_reinit();
	
	if (tresult != T_SUCCESS)
	{
		Test_ACTBP();
	}

    // Initialze file system context information
	Go_RootDir();
	UpdateFileSys_Dir();
	UpdateContext_Count();
	context.root_dir_count = context.curr_dir_count;

    // Initialze display screen
	InitDisplayScreen();  

	// Put APRF in CYCLE mode
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_CYCLE;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);

	// Initialze context information
	context.cycle_status = 1;
	context.last_state = PWR_OFF;
	context.current_state = BROWSE_DIR;
	context.curr_dir_num = 0;
	context.curr_file_num = 0;
	context.shuffle_status = OFF;
	
	// Counter for SLEEP and Low-Power Playback
	timeout_count = 0;
}

/* ----------------LedStartUpSequence--------------------------------------
 * Display an LED lighting sequence to indicate power on
 * ------------------------------------------------------------------------*/
void LedStartUpSequence(void)
{
	unsigned char i;
	TACCTL0 = CCIE;                           // CCR0 interrupt enabled
	TACTL |= TACLR;
	TACCR0 = TAR + 500;                       // 50ms
	TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode
	
	/* Slow clockwise sequence */
	for(i=0; i<8; i++)
	{
		P1OUT = startSequence[i];
		__bis_SR_register(LPM3_bits+GIE);
		
		__delay_cycles(1000000);
		TACCR0 = TAR + 500;   // 50ms
	}
	P1OUT = BIT0;
	
	/* Fast counter-clockwise sequence */
	while(i)
	{
		i--;
		P1OUT = startSequence[i];
		__bis_SR_register(LPM3_bits+GIE);
		TACCR0 = TAR + 500;                   // 50ms
	}
	TACCTL0 &= ~CCIE;                         // CCR0 interrupt disabled
	P1OUT = 0;                                // Turn off all LEDs
}

/* ----------------UpdateOperation-------------------------------------------
 * Update state machine and send UART commands based on detected event
 * ---------------------------------------------------------------------------*/
void UpdateState()
{
	static unsigned int nxtdir_count = 0;
	static unsigned int prvdir_count = 0;
	Status status = FAILURE;
	int volume_diff = 0, i;
	
	unsigned long read_data = 0;
	switch (context.current_state)
	{
		case BROWSE_DIR:
		switch (context.current_event)
		{
	        case SCROLL_RIGHT: // Display next directory
	        nxtdir_count++;
	        if (nxtdir_count == DIR_CHANGE_DELAY)
	        {
	        	Go_NextDir();
	        	UpdateDisplay_Dir();
		        context.last_state = NXT_DIR;
		        /* context.current_state = BROWSE_DIR; */
		        nxtdir_count = 0;
	        }
	        prvdir_count = 0;
	        break;
	
	        case SCROLL_LEFT: // Display previous directory
	        prvdir_count++;
	        if (prvdir_count == DIR_CHANGE_DELAY)
	        {
		        Go_PrevDir();
		        UpdateDisplay_Dir();
		        context.last_state = PRV_DIR;
		        /* context.current_state = BROWSE_DIR; */
		        prvdir_count = 0;
	        }
	        nxtdir_count = 0;
	        break;

	        case MID: // Select directory
        	if ((context.last_state != BROWSE_FILE))
        	{
	        	//Send CD (Change Directory) command
	        	RegAddr = UIF_CMD_OPERATION;
	        	OperationVal = UIF_CMD_CD;
	        	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	        	
	        	//Put '.' for current dir into $play_file
	        	RegAddr = UIF_CMD_PLAY_FILE;
	        	status = uif_writeArray( RegAddr, (unsigned int) 1, (char *) dirnavStrings.CURRENT_DIR);
	        	
	        	//Read directory information
	        	UpdateFileSys_Dir();
	        	//Update context with file and directory count in selected directory
	        	UpdateContext_Count();
	        	 
	        	if (context.curr_file_count !=0)
	        	{
	        		// If selected directory has MP3 files, update SYS_FILE register with name of first file
	        		// and update context to point to first file indirectory
	        		Go_FirstFile();
			        context.curr_file_num = 1;
				    RegAddr = UIF_CMD_PLAY_NUMBER;
				    status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
	        	}
	        	else
	        	{
			        context.curr_file_num = 0;	        		
	        	}
	        	// Update display with name of first file or empty directory message
	        	UpdateDisplay_File();
        	}
	        //Move view port of screen (vertical scroll) to show directory and file names 
	        SetScreen((unsigned int) LINE_DIRNAV, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
	        /* context.last_state = current.last_state; */
        	// Change state machine to BROWSE_FILE
        	context.current_state = BROWSE_FILE;
        	break;
        	
			case UP_HOLD: //Power down
			// Print message on screen
			Print_PwrOff();
			__delay_cycles(16000000);
			// Vertical scroll
			SetScreen((unsigned int) LINE_MSG0, (unsigned int) LINE_MSG1, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0xFFFF);
			__delay_cycles(16000000);
			// Power down DSP 
			P2OUT &= ~BIT7;
			/* context.last_state = current.last_state; */
			// Change state machine PWR_OFF
			context.current_state = PWR_OFF;
			break;
			
	        case DOWNx2: // USB MSC if USB cable is connected
	      	//Get USB Cable Insert Status
	      	RegAddr = UIF_CMD_USB_STATUS;
	      	read_data = 0;
	      	status = uif_readScalar( RegAddr, &read_data);
	      	context.USB_cableinsert = read_data  & BIT0;
	      	/* context.last_state = current.last_state; */
	      	if (context.USB_cableinsert)
	      	{
	      		// If USB cable has been connected to ACTBP enable USB MSC  
	      		Print_USBMSC_Wait();
	      		RegAddr = UIF_CMD_USB_CTRL;
	      		USBMSCControl = UIF_USB_ENABLED;
	      		status = uif_writeScalar( RegAddr, USBMSCControl, (unsigned int) ACK_EXPECT);
	      		context.current_state = USB_MSC;
	      		// APRF ignores commands for 15 seconds after USB MSC has been enabled
				// Update context to disable state machine update during this time
	      		context.disable_command = ON;
	      	}
	      	else
	      	{
	      		// If USB cable is not connected, print error message
	      		Print_USBErr();
	      		// Return to Browse_Dir screen
	      		__delay_cycles(18000000);
	      		SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_DIRNAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
				//Clear printed message on temporary view port
				Print_ClearLine((unsigned long) CURSOR_USB_ERR1);
				Print_ClearLine((unsigned long) CURSOR_USB_ERR2);
	      	}
	      	break;
	      	
			default:
			break;
		}
		break;
		
		case BROWSE_FILE:
		switch (context.current_event)
		{
	        case SCROLL_RIGHT: // Next file
	        Go_NextFile();
	        UpdateDisplay_File();
	        context.last_state = NXT_FILE;
	        /* context.current_state = BROWSE_FILE; */
	        break;
        
	        case SCROLL_LEFT: // Previous file
	        Go_PrevFile();
	        UpdateDisplay_File();
	        context.last_state = PRV_FILE;
	        /* context.current_state = BROWSE_FILE; */
	        break;
	        
	        case MID: // Play
        	if ((context.curr_file_count !=0) && (context.last_state != BROWSE_DIR) && (context.last_state != PLAY) && (context.last_state != PAUSE) && (context.last_state != RECORD) && (context.last_state != REC_PAUSE))
        	{
        		RegAddr = UIF_CMD_OPERATION;
        		OperationVal = UIF_CMD_PLAY_LIST;
        		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
        		SetScreen((unsigned int) LINE_FILENAV, (unsigned int) LINE_PLAY, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
        		UpdateContext_FileNum();
        		context.last_state = BROWSE_FILE;
        		context.current_state = PLAY;
        	}
        	else //MID button press sends two events
        	{
        		context.last_state = BROWSE_FILE;
        	}
	        break;
	
	        case DOWN_HOLD: // Record
	      	// During Record output volume level is reset to 81 and revert back 
	      	// to user-set value when record is stopped  
	      	
	      	// Read and update context with current volume level 
	      	RegAddr = UIF_CMD_VOLUME;
	      	read_data = 0;
	      	status = uif_readScalar( RegAddr, &read_data);
	      	context.curr_volume = read_data & 0xFF;
	        
	        // Reset volume level to default value
	        RegAddr = UIF_CMD_OPERATION; 
	        OperationVal = UIF_CMD_VOLUME_RESET;
	      	status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	        
	        // Print record initialization message while APRF prepares record file
	        // This screen is updated by APRF recording starts 
	        Print_RecInit();
	      	SetScreen((unsigned int) LINE_FILENAV, (unsigned int) LINE_PLAY, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
	        __delay_cycles(1000000);
	        RegAddr = UIF_CMD_OPERATION;
	        OperationVal = UIF_CMD_RECORD;
	        status=uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	        
	        // Check error code returned by DSP to record command 
	        switch (status)
	        {
	        	case SUCCESS:
	        	// If command has been accepted, change state machine
	        	context.last_state = BROWSE_FILE;
		        context.current_state = RECORD;
		        break;
		        
		        case FAILURE:
		        // If command failed, revert volume level back to user-set value
		      	if (context.curr_volume >= 81)
		      	{
		      		volume_diff = context.curr_volume - 81;
	      			RegAddr = UIF_CMD_OPERATION;
	      			OperationVal = UIF_CMD_VOLUME_UP_02;
		      		for (i=0; i<(volume_diff-1); i++)
		      		{
		      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		      		}
		      	}
		      	else
		      	{
		      		volume_diff = 81 - context.curr_volume;
	      			RegAddr = UIF_CMD_OPERATION;
	      			OperationVal = UIF_CMD_VOLUME_DOWN_02;
		      		for (i=0; i<(volume_diff-3); i++)
		      		{
		      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		      		}
		      		
		      	}
		        break;
		        
		        case MAX_FC_ERR:
		        // If RecDir directory has max number of file allowed display message and 
		        // revert back to user-set volume level 
      			RegAddr = UIF_CMD_OPERATION;
      			OperationVal = UIF_CMD_NOP;
      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	        	Print_RecErr();
		      	if (context.curr_volume >= 81)
		      	{
		      		volume_diff = context.curr_volume - 81;
	      			RegAddr = UIF_CMD_OPERATION;
	      			OperationVal = UIF_CMD_VOLUME_UP_02;
		      		for (i=0; i<(volume_diff-1); i++)
		      		{
		      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		      		}
		      	}
		      	else
		      	{
		      		volume_diff = 81 - context.curr_volume;
	      			RegAddr = UIF_CMD_OPERATION;
	      			OperationVal = UIF_CMD_VOLUME_DOWN_02;
		      		for (i=0; i<(volume_diff-3); i++)
		      		{
		      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		      		}
		      		
		      	}
	      		
	      		// Return to BROWSE_FILE screen
	      		__delay_cycles(24000000);
				Go_RecDir();
				UpdateDisplay_Dir();
				UpdateFileSys_Dir();
				UpdateContext_Count();
				Go_LastFile();
				UpdateDisplay_File();
	      		
	      		SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
				Print_ClearLine((unsigned long) CURSOR_USB_ERR1);
				Print_ClearLine((unsigned long) CURSOR_USB_ERR2);
				break;
				
				default:
				break;				
	        }
	        break;
	
	        case DOWNx2: // USB MSC if USB cable is connected
	      	//Get USB Cable Insert Status
	      	RegAddr = UIF_CMD_USB_STATUS;
	      	read_data = 0;
	      	status = uif_readScalar( RegAddr, &read_data);
	      	context.USB_cableinsert = read_data  & BIT0;
	      	/*context.last_state = current.last_state; */
	      	if (context.USB_cableinsert)
	      	{
	      		// If USB cable has been connected to ACTBP enable USB MSC
	      		Print_USBMSC_Wait();
	      		RegAddr = UIF_CMD_USB_CTRL;
	      		USBMSCControl = UIF_USB_ENABLED;
	      		status = uif_writeScalar( RegAddr, USBMSCControl, (unsigned int) ACK_EXPECT);
	      		context.current_state = USB_MSC;
	      		// APRF ignores commands for 15 seconds after USB MSC has been enabled
				// Update context to disable state machine update during this time
	      		context.disable_command = ON;
	      	}
	      	else
	      	{
	      		// If USB cable is not connected, print error message
	      		Print_USBErr();
	      		// Return to Browse_File screen
	      		__delay_cycles(18000000);
	      		SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
				Print_ClearLine((unsigned long) CURSOR_USB_ERR1);
				Print_ClearLine((unsigned long) CURSOR_USB_ERR2);
	      	}
	      	break;
	      	
			case UP_HOLD: //Power down
			Print_PwrOff();
			__delay_cycles(16000000);
			SetScreen((unsigned int) LINE_MSG0, (unsigned int) LINE_MSG1, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0xFFFF);
			__delay_cycles(16000000);
			P2OUT &= ~BIT7;
			/* context.last_state = current.last_state; */
			context.current_state = PWR_OFF;
			break;
			
	      	case UP: // Go to BROWSE_DIR
	        SetScreen((unsigned int) LINE_FILENAV, (unsigned int) LINE_DIRNAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
	      	context.last_state = BROWSE_FILE;
			context.current_state = BROWSE_DIR;
	      	break;
	      	
	      	default:
	      	break;
		}
		break;
		
		case PLAY: case PAUSE: // Playback or Pause 
		switch (context.current_event)
		{
			case SCROLL_RIGHT: // Volume up
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_VOLUME_UP_02;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = VOL_UP;
			break;
			
			case SCROLL_LEFT: // Volume down
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_VOLUME_DOWN_02;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = VOL_DOWN;
			break;
			
			case RIGHT: // Skip forward one file
			//If current file is last file in directory, stop play
			//If not last file or if CYCLE is ON (default), skip to next file
			UpdateContext_FileNum();
			if ((context.curr_file_num < context.curr_file_count) || (context.cycle_status == ON))
			{
				// if CYCLE==ON or if skipping file from PLAY- use PLAY_NEXT command
				if ((context.current_state != PAUSE) && (context.cycle_status == ON))
				{
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_PLAY_NEXT;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				}
				else //if from PAUSE, STOP play and use PLAY_NUMBER and PLAY_LIST
				{
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_STOP_PLAY;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
					
					RegAddr = UIF_CMD_PLAY_NUMBER;
					status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num+1), (unsigned int) ACK_EXPECT);
					
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_PLAY_LIST;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				}
				context.current_state = PLAY;
			}
			else
			{
				// Stop play
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_STOP_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.current_state = BROWSE_FILE;
			}
			context.last_state = SKIP_F;
			break;
			
			case RIGHT_HOLD: // Fast forward
			if (context.current_state == PAUSE)
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_RESUME_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			}
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_FF_NORMAL;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = PLAY;
			context.current_state = FF;
			break;
			
			case LEFT: // Skip to start of current file
			UpdateContext_FileNum();
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_STOP_PLAY;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			
			RegAddr = UIF_CMD_PLAY_NUMBER;
			status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
			
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_PLAY_LIST;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = SKIP_START;
			context.current_state = PLAY;
			break;
			
			case LEFTx2: // Skip back one file
			//If current file is first file in directory, stop play
			//If not first file or if CYCLE is ON, skip to previous file
			UpdateContext_FileNum();
			if ((context.curr_file_num > 1) || (context.cycle_status == ON))
			{
				// if CYCLE==ON or if skipping file from PLAY- use PLAY_PREV command
				if ((context.current_state != PAUSE) && (context.cycle_status == ON))
				{
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_PLAY_PREV;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				}
				else //if from PAUSE, STOP play and use PLAY_NUMBER and PLAY_LIST
				{
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_STOP_PLAY;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
					
					RegAddr = UIF_CMD_PLAY_NUMBER;
					status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num-1), (unsigned int) ACK_EXPECT);
					
					RegAddr = UIF_CMD_OPERATION;
					OperationVal = UIF_CMD_PLAY_LIST;
					status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				}
				context.current_state = PLAY;
			}
			else
			{
				// Stop play
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_STOP_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.current_state = BROWSE_FILE;
			}
			context.last_state = SKIP_B;
			break;
			
			case LEFT_HOLD: // Rewind
			if (context.current_state == PAUSE)
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_RESUME_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			}
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_REWIND_NORMAL;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = PLAY;
			context.current_state = RWD;
			break;
			
			case MID: // Pause
			if (context.current_state == PLAY)
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_PAUSE_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.last_state = PLAY;
				context.current_state = PAUSE;
			}
			else //Resume play
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_RESUME_PLAY;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.last_state = PAUSE;
				context.current_state = PLAY;
			}
			break;
			
			case MID_HOLD: // Stop play
			UpdateContext_FileNum();
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_STOP_PLAY;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			
			RegAddr = UIF_CMD_PLAY_NUMBER;
			status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
			
			context.last_state = context.current_state;
			context.current_state = BROWSE_FILE;
			__delay_cycles(500000);
	        SetScreen((unsigned int) LINE_PLAY, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
			break;
			
			case UP: // Shuffle ON/OFF
			if (context.last_state != PWR_OFF)
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_SHUFFLE;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.shuffle_status = ~context.shuffle_status;
				context.last_state = SHUFFLE;
			}
			break;

			case UP_HOLD: //Power down
			// Print message on screen
			Print_PwrOff();
			__delay_cycles(16000000);
			SetScreen((unsigned int) LINE_MSG0, (unsigned int) LINE_MSG1, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0xFFFF);
			__delay_cycles(16000000);
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_STOP_PLAY;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			P2OUT &= ~BIT7;
			/*context.last_state = current.last_state; */
			context.current_state = PWR_OFF;
			break;

			default:
			break;
		}
		break;
		
		case FF: // Fast Forward
		// During FF if end of file is reached, APRF resumes normal playback of next file
		// Check Playstatus and update context to send RWD command to end RWD operation 
		// only if APRF is currenlty in FF 
		UpdateContext_PlayStatus();
		if (context.curr_play_status == UIF_STATUS_FF_RUN)
		{
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_FF_NORMAL;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		}
		context.last_state = FF;
		context.current_state = PLAY;
		break;
		
		case RWD: //Rewind
		// During RWD if start of file is reached, APRF resumes normal playback of current file
		// Check Playstatus and update context to send RWD command to end RWD operation 
		// only if APRF is currenlty in RWD 
		UpdateContext_PlayStatus();
		if (context.curr_play_status == UIF_STATUS_REWIND_RUN)
		{
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_REWIND_NORMAL;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		}
		context.last_state = RWD;
		context.current_state = PLAY;
		break;
		
		case RECORD: case REC_PAUSE: //Record or Record Pause
		switch (context.current_event)
		{
			case MID: // Record pause
			if (context.current_state == RECORD)
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_PAUSE_RECORD;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.last_state = RECORD;
				context.current_state = REC_PAUSE;
			}
			else //Resume record
			{
				RegAddr = UIF_CMD_OPERATION;
				OperationVal = UIF_CMD_RESUME_RECORD;
				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
				context.last_state = REC_PAUSE;
				context.current_state = RECORD;
			}
			break;
			
			case MID_HOLD: // Stop record
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_STOP_RECORD;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			context.last_state = context.current_state;
			context.current_state = BROWSE_FILE;
			P1OUT &= ~BIT0; // Center LED off
			
			// Once Record is stopped, update file system state of APRF to point to and display the 
			// the last recorded file - at this point the current directory number is saved context
			// is incorrect, but syncs up again when user next browses directories 
			Go_RecDir();
			UpdateDisplay_Dir();
			UpdateFileSys_Dir();
			UpdateContext_Count();
			Go_LastFile();
			UpdateDisplay_File();
			__delay_cycles(500000);
	        SetScreen((unsigned int) LINE_PLAY, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
	      	
	      	// Revert volume level back to user-set value
	      	if (context.curr_volume >= 81)
	      	{
	      		volume_diff = context.curr_volume - 81;
      			RegAddr = UIF_CMD_OPERATION;
      			OperationVal = UIF_CMD_VOLUME_UP_02;
	      		for (i=0; i<(volume_diff-1); i++)
	      		{
	      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	      		}
	      	}
	      	else
	      	{
	      		volume_diff = 81 - context.curr_volume;
      			RegAddr = UIF_CMD_OPERATION;
      			OperationVal = UIF_CMD_VOLUME_DOWN_02;
	      		for (i=0; i<(volume_diff-3); i++)
	      		{
	      			status = uif_writeScalar(  RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	      		}
	      		
	      	}
			break;
			
			case UP_HOLD: //Power down
			// Print message on screen
			Print_PwrOff();
			__delay_cycles(16000000);
			SetScreen((unsigned int) LINE_MSG0, (unsigned int) LINE_MSG1, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0xFFFF);
			__delay_cycles(16000000);
			// Strop record operation
			RegAddr = UIF_CMD_OPERATION;
			OperationVal = UIF_CMD_STOP_RECORD;
			status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
			// Power down DSP
			P2OUT &= ~BIT7;
			/* context.last_state = current.last_state; */
			context.current_state = PWR_OFF;
			break;

			default:
			break;
		}
		break;

		case USB_MSC: //USB MSC mode
		switch (context.current_event)
		{
			case DOWNx2: // Disable USB MSC mode
			RegAddr = UIF_CMD_USB_CTRL;
			USBMSCControl = UIF_USB_DISABLED;
			status = 2;
			while (status!=SUCCESS)
			{
				status=uif_writeScalar( RegAddr, USBMSCControl, (unsigned int) ACK_EXPECT);
			}
			context.last_state = USB_MSC;
			context.current_state = BROWSE_DIR;
			//Reset to root directory
            __delay_cycles(8000000);
			Go_RootDir();
			UpdateFileSys_Dir();
			UpdateDisplay_Dir();
			UpdateContext_Count();
			context.root_dir_count = context.curr_dir_count;
	        SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_DIRNAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
			Print_ClearLine((unsigned long) CURSOR_USB_ERR1);
			Print_ClearLine((unsigned long) CURSOR_USB_ERR2);

			context.last_state = USB_MSC;
			context.current_state = BROWSE_DIR;
	        context.curr_file_num = 0;
	        context.curr_dir_num = 0;
			break;
			
			default:
			break;
		}
		break;
		
		case PWR_OFF:
		switch (context.current_event)
		{
			case UP_HOLD: // Power up
		    InitLaunchPadCore();
			MeasureCapBaseLine();
			TI_CAPT_Init_Baseline(&proximity_sensor);
			TI_CAPT_Update_Baseline(&proximity_sensor,5);
			LedStartUpSequence();
		    InitC55ABP();
			
		    // Start the timer for time out
		    TA1CCR0 = 22500; //15 second timeout
		    TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 1.5kHz, Up Mode, Clear TAR, start timer
			context.last_state = PWR_OFF;
			context.current_state = BROWSE_DIR;
			break;
			
			default:
			break;
		}
		break;
		
		default: 
		break;
  }
}


void main(void)
{
	unsigned int timer1_counter=0;
	unsigned int centerLED_counter=0;
	Status status = FAILURE;
	
	WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
	/* Set DCO to 8MHz - CPU runs at 8 MHz */
	/* Set SMCLK to 8MHz / 8 = 1MHz */
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;
	BCSCTL2 |= DIVS_3;

	// Initialize MSP430
	InitLaunchPadCore();
	// Establish baseline for scroll wheel and center button capacitance touch elements 
	MeasureCapBaseLine();
	// Establish baseline for the proximity sensor
	TI_CAPT_Init_Baseline(&proximity_sensor);
	TI_CAPT_Update_Baseline(&proximity_sensor,5);
	// Show LED startup sequence
	LedStartUpSequence();
	// Initialize ABP
    InitC55ABP();

    // Start the timer for time out
    // If no user activity is detected for 1-minute (timer1_counter==4)in BROWSE_DIR 
    // and BROWSE_FILE mode application puts DSP in low-power RAM retention standby mode
    // Timer is set for 15-second timeout  
    TA1CCR0 = 22500; //15 second timeout
    TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 1.5kHz, Up Mode, Clear TAR, start timer
        
    // Infinte loop
    while (1)
    {
    	// Detect gestures / events
    	GetCapTouchInput();
    	
    	// If valid event has been detected and APRF is not blocking commands,
    	// update state machine and send UART commands
    	if ((eventFlag == 1) && (context.disable_command == OFF))
    	{
    		//User input detected, so do not timeout
    		TA1CTL &= ~MC_3; //stop the timer
    		TA1CCTL0 &= ~CCIFG; //Clear the flag if set
    		UpdateState();
    		
    		// Restart timer for timeout 
    		if ((context.current_state == BROWSE_DIR) || (context.current_state == BROWSE_FILE)  || (context.current_state == PLAY)  || (context.current_state == USB_MSC))
    		{
    			//Restart timer to enable timeout
    			TA1CTL |= ID_3 + MC_1 + TACLR; //clear timer count and restart it
    		}
    		timer1_counter = 0;
    	}
    	else // No events detected
    	{
 			// Blink LEDs in Record state or put MSP3430 into LPM3 mode if DSP has been powered off
 			switch (context.current_state)
			{
				case RECORD:
    			UpdateContext_RecordStatus();
    			if (context.curr_record_status == 1)
    			{
    				P1OUT = P1OUT^BIT0; // Blink Center LED
    			}
    			break;
    			
    			case PWR_OFF:
				//go to LPM3, wake up periodically to check for touch
				TA1CCR0 = 750; //wake every 500ms
				TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 1.5kHz, Up Mode, Clear TAR, start timer
				TA1CCTL0 |= CCIE; //compare interrupt enabled
				//TA1CTL = TASSEL_1 + MC_1 + TACLR; //TACLK = ACLK = 12kHz, Up Mode, Clear TAR, start timer
				__bis_SR_register(LPM3_bits + GIE); //go to low-power mode until woken by timer
    			break;
    			
    			default:
    			break;
    		}

    		//Put MSP430 or DSP and MSP430 in low-power standby mode 
    		if(TA1CCTL0 & CCIFG) //check if we've hit our timeout (15sec)
    		{
    			TA1CTL &= ~MC_3; //stop the timer
    			TA1CCTL0 &= ~CCIFG; //Clear the flag
    			timer1_counter++;  // Increment timer
    			switch (context.current_state)
    			{
    				case USB_MSC:
    				// 15-second timeout
    				// APRF ignores commands for 15 seconds after USB MSC has been enabled
    				// Print USB MSC enabled message and update context to enable state update 
    				// if valid event is detected 
    				Print_USBMSC();
    				context.disable_command = OFF;    // enable user input
	    			timer1_counter = 0;
    				break;
    				
    				case PLAY:
	    			//Put MSP430 in low-power playback mode when playing back music 
	    			//after 1-minute of inactivity  
	    			if (timer1_counter == 4) // 1 minute timeout
	    			{
		    			P1OUT |= BIT0; //Center LED turns on while MSP430 is in LPM3
	    				// Establish baseline for the proximity sensor
	    				TI_CAPT_Init_Baseline(&proximity_sensor);
	    				TI_CAPT_Update_Baseline(&proximity_sensor,5);	    				
	    				
	    				//go to LPM1, wake up periodically to check for touch
		    			TA1CCR0 = 750; //wake every 500ms
		    			TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 1.5kHz, Up Mode, Clear TAR, start timer
		    			TA1CCTL0 |= CCIE; //compare interrupt enabled
		    			do
		    			{
		    				centerLED_counter++;
		    				if (centerLED_counter==3)
		    				{
		    					P1OUT = P1OUT^BIT0; //Toggle Center LED
		    					centerLED_counter = 0;
		    				}
		    				
		    				deltaCnts[0] = 0;
		    				TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK = 1.5kHz, Up Mode, Clear TAR, start timer
		    				__bis_SR_register(LPM3_bits + GIE); //go to low-power mode until woken by timer
		    				// Check proximity sensor to wake up
		    				TI_CAPT_Custom(&proximity_sensor,deltaCnts);
		    				// Establish baseline for the proximity sensor
		    				TI_CAPT_Init_Baseline(&proximity_sensor);
		    				TI_CAPT_Update_Baseline(&proximity_sensor,5);	    				
		    			}
		    			while (deltaCnts[0] <= PROXIMITY_THRESHOLD);
	                    // Wake up!
	                    // Establish baseline for scroll wheel and center button capacitance touch elements 
		    			MeasureCapBaseLine();
		    			P1OUT &= ~BIT0; //turn Center LED off
		    			timer1_counter = 0;
		    			centerLED_counter = 0;
	    			}
	    			//After wake-up, re-start the timer for low-power playback mode
	    			TA1CCR0 = 22500; //15 second timeout
	    			TA1CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	    			TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR;
	    			break;
	    			
	    			case BROWSE_DIR: case BROWSE_FILE:
	     		    //Put DSP and MSP430 in low-power standby mode after 1 minute of no user input
	    			if (timer1_counter == 4) // 1 minute timeout
	    			{
	    				Print_Sleep();
	    				__delay_cycles(24000000);
	    				// Turn off OLED display
		    			DisplayOff();
		    			P1OUT |= BIT0; //Center LED turns on during SLEEP
		    			//Send "Sleep" command to DSP - ACK is not sentby DSP so ignore ACK
		    			RegAddr = UIF_CMD_OPERATION;
		    			OperationVal = UIF_CMD_SLEEP; // put DSP in STANDBY RAM Retention mode
		    			status = uif_writeScalar(RegAddr, OperationVal, (unsigned int) ACK_IGNORE);
		    			__delay_cycles(500000);
		    			//DSP is in low-power RAM retention standby mode
		    			//Establish baseline for the proximity sensor
	    				TI_CAPT_Init_Baseline(&proximity_sensor);
	    				TI_CAPT_Update_Baseline(&proximity_sensor,5);	    				
		    			//Put MSP430 in LPM3 low-power mode, wake up every 500 ms to check proximity sensor 
		    			TA1CCR0 = 750; //wake every 500ms
		    			TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK/8 = 1.5kHz, Up Mode, Clear TAR, start timer
		    			TA1CCTL0 |= CCIE; //compare interrupt enabled
		    			do
		    			{
		    				deltaCnts[0] = 0;
		    				TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR; //TACLK = ACLK = 1.5kHz, Up Mode, Clear TAR, start timer
		    				__bis_SR_register(LPM3_bits + GIE); //go to low-power mode until woken by timer
		    				// Check proximity sensor to wake up
		    				TI_CAPT_Custom(&proximity_sensor,deltaCnts);
		    				// Establish baseline for the proximity sensor
		    				TI_CAPT_Init_Baseline(&proximity_sensor);
		    				TI_CAPT_Update_Baseline(&proximity_sensor,5);	    				
		    			}
		    			while (deltaCnts[0] <= PROXIMITY_THRESHOLD);

		    			//wake DSP - P2.6 is connected to INT0 on the DSP
		    			P2OUT |= BIT6; // pull line high
		    			P2OUT &= ~BIT6; //pull line low to wake DSP on falling edge
		    			P1OUT &= ~BIT0;
		    			__delay_cycles(8000000);
		    			Print_WakeUp();
		    			// Turn on OLED display
		    			DisplayOn();
		    			__delay_cycles(24000000);
		    			//Scroll OLED display view port
		    			if(context.current_state == BROWSE_DIR)
		    			{
		    				SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_DIRNAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
		    			}
		    			else
		    			{
		    				SetScreen((unsigned int) LINE_MSG1, (unsigned int) LINE_FILENAV, (unsigned int) 1, (unsigned int) 1, (unsigned int) 0);
		    			}
		    			MeasureCapBaseLine();
		    			timer1_counter = 0;
	    			}
	    			//After wake-up, re-start the timer
	    			TA1CCR0 = 22500; //15 second timeout
	    			TA1CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
	    			TA1CTL = TASSEL_1 + ID_3 + MC_1 + TACLR;
	    			break;
	    			
	    			default:
	    			break;
    			}
    		}
    	}
    }
}
