/*******************************************************************************
 *
 *  ACTBP_HostVars.h - Definition file for variables and state machines used
 *                       in the MSP430 host application to control the Raga 
 *                       software running on a C55x DSP using the UART interface
 *                       on the Audio Capacitive Touch Booster Pack for LaunchPad 
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

/** To avoid redefinition for variables declared in this header */
#ifndef _ACTBP_HOSTVARS_H
#define _ACTBP_HOSTVARS_H

#include "C55_APRF_UIF.h"

#define UIF_SUCCESS               (0)
/**< Macro to indicate that the UIF operation is successful                  */
#define UIF_FAILURE               (1u)
/**< Macro to indicate Failure                                               */
#define UIF_CMD_NOT_SUPPORTED     (2u)
/**< Macro to indicate that the command is not supported                     */
#define UIF_CMD_INVALID           (3u)
/**< Macro to indicate that the command is invalid                           */
#define UIF_CMD_INVALID_OPERATION (4u)
/**< Macro to indicate that the command operation invalid                    */
#define UIF_BUFFER_OVERFLOW       (5u)
/**< Macro to indicate that the UIF RX buffer overflow                       */
#define UIF_CMD_INVALID_FOR_SYSTEM_STATE       (6u)
/**< Macro to indicate that command is invalid for the current system state  */
#define T_SUCCESS                0xA82F

/**< Parameters for Capacitive Touch Scroll Wheel and Buttons                */
#define INVALID_GESTURE         0xFD
#define COUNTER_CLOCKWISE       1
#define CLOCKWISE               2
#define GESTURE_POSITION_OFFSET 0x30
#define WHEEL_POSITION_OFFSET   0x30
#define WHEEL_TOUCH_DELAY		12	   //Delay between re-sendings of touches
#define MAX_IDLE_TIME           20
#define PROXIMITY_THRESHOLD     50

/**< Delays in application operation                                         */
#define DELAY_C55ABP_INIT       30000000
#define DIR_CHANGE_DELAY        3
#define UART_TIMEOUT_COUNT      10 // 10*(1/[12000/32768]) = 27.3seconds
#define ACK_EXPECT  0
#define ACK_IGNORE  1
 
enum event {UP, UP_HOLD, RIGHT, RIGHT_HOLD, DOWN, DOWNx2, DOWN_HOLD, LEFT, LEFTx2, LEFT_HOLD, MID, MID_HOLD, HOLD_END, SCROLL_RIGHT, SCROLL_LEFT, INVALID_EVNT} ;
enum event_hold {THOLD_ON, MHOLD_ON, SCROLL_ON, NO_HOLD};
enum state {BROWSE_DIR, BROWSE_FILE, PLAY, FF, RWD, USB_MSC, SLEEP, PWR_OFF, RECORD, VOL_UP, VOL_DOWN, NXT_DIR, PRV_DIR, NXT_FILE, PRV_FILE, PAUSE, SKIP_F, SKIP_B, SKIP_START, REC_PAUSE, REC_STOP, CYCLE, SHUFFLE};

/** Structure to store working context */
struct ContextABP 
{
  enum event current_event;
  enum event_hold last_event;
  enum state current_state;
  enum state last_state;
  int curr_dir_num;
  int curr_file_num;
  int curr_dir_count;
  int root_dir_count;
  int curr_file_count;
  unsigned char curr_volume;
  unsigned char curr_play_status;
  unsigned char curr_record_status;
  unsigned shuffle_status:1;
  unsigned cycle_status:1;
  unsigned USB_cableinsert:1;
  unsigned disable_command:1;
};

/** Structure for directory structure navigation strings*/
struct StringsDirNav
{
	char ROOT_DIR[1];     // "\"
	char CURRENT_DIR[1];  // "."
	char RECORD_DIR[6];   // "RecDir"
};

/** Structure for display strings */
struct StringsDisplay
{
	char CLEARLINE[22];  // "                     "
	char DIRNAV[22];     // "Scroll or Select     "
	char DIRFIX[22];     // "DIR:                 "
	char EMPTYDIR[22];   // "   < Empty >         "
	char RECINIT1[22];   // "Entering Record      "
	char RECINIT2[22];   // "Please Wait....      "
	char RECERR1[22];    // " Delete Files        "
	char RECERR2[22];    // "And Try Again..      "
	char USBMSC1[22];    // "Enabling USB Mass    "
	char USBMSC2[22];    // "Storage Device...    "
	char USBMSC3[22];    // "USB Mass Storage     "
	char USBMSC4[22];    // " Device Enabled      "
	char USBERR1[22];    // "Attach USB Cable     "
	char USBERR2[22];    // " And Try Again       "
	char SLEEP1[22];     // "Feeling Sleepy..     "
	char SLEEP2[22];     // "	ZZZzzzz           "
	char WAKEUP1[22];    // "Ah...You're Back     "
	char WAKEUP2[22];    // "Now Let's Rock!!     "
	char PWROFF1[22];    // "Hui Tou Jian...      "
	char PWROFF2[22];    // "Hasta La Vista..     "
	char PWROFF3[22];    // "   Ciao...           "
	char PWROFF4[22];    // " And Goodbye!        "
	char COMMERR1[22];   // " Communication       "
	char COMMERR2[22];   // "     Error           "
};

/**< Parameters for Booster Pack OLED Virtual Planes                         */
/**< The OLED has 64 vertical pixels which can be scrolled up and down       */
/**< one pixel at a time                                                     */
/**< 8 pixels are required to display one line of characters                 */
/**< giving 64/8=8 lines of display                                          */
/**< Screen can display 2 lines (16 pixels) at a time                        */
/**< Lines 0 & 1 (Pixels 0  to 15) display other messages                    */
/**< Lines 2 & 3 (Pixels 16 to 31) display other messages                    */
/**< Lines 4 & 5 (Pixels 32 to 47) display Navigation screen                 */
/**< Lines 6 & 7 (Pixels 48 to 63) display Play/Record Operation display     */
/**<                                                                         */
/**< The OLED has 128 horizontal pixels which can be scrolled right to left  */
/**< one pixel at a time                                                     */
/**< Six pixels are required to display one characters                       */
/**< Screen can display 16 characters (96 pixels) without scrolling          */
/**< or 20 characters (128 pixels) with scrolling enabled                    */
#define VP_MSG0         (0x0000)    // in vertical pixels
#define VP_MSG1         (0x1000)    // in vertical pixels
#define VP_DIRNAV       (0x2000)    // in vertical pixels
#define VP_FILENAV      (0x2800)    // in vertical pixels
#define VP_PLAY         (0x3000)    // in vertical pixels
#define LINE_MSG0       (VP_MSG0 >> 11)    // in line number
#define LINE_MSG1       (VP_MSG1 >> 11)    // in line number
#define LINE_DIRNAV     (VP_DIRNAV >> 11)  // in line number
#define LINE_FILENAV    (VP_FILENAV >> 11) // in line number
#define LINE_PLAY       (VP_PLAY >> 11)    // in line number

/*****************************************************************************/
/**< In Dir Nav window, display is as follows (starting from pixel #0:       */
/**< Scroll or Select                                                        */
/**< DIR:<directory name (16 characters)>                                    */
/*****************************************************************************/
/**< In Play window, display is as follows (starting from pixel #0:          */
/**< <filename (20 characters)>                                              */
/**< OPERATION        VOLxx                                                  */
/*****************************************************************************/
#define CURSOR_DIRNAV    (0x0400)    // Starts at Line 4 Pixel 0
#define CURSOR_DIR       (0x0500)    // Starts at Line 5 Pixel 0
#define CURSOR_DIRNAME   (0x0504)    // Starts at Line 5 Pixel 4
#define CURSOR_FILENAME  (0x0600)    // Starts at Line 6 Pixel 0
#define CURSOR_OPERATION (0x0700)    // Starts at Line 7 Pixel 0
/**< For USB window >                                                        */
#define CURSOR_USB_MSC1  (0x0200)    // Starts at Line 2 Pixel 0
#define CURSOR_USB_MSC2  (0x0300)    // Starts at Line 3 Pixel 0
/**< For Error window >                                                      */
#define CURSOR_USB_ERR1  (0x0200)    // Starts at Line 2 Pixel 0
#define CURSOR_USB_ERR2  (0x0300)    // Starts at Line 3 Pixel 0
/**< For Sleep window >                                                      */
#define CURSOR_SLEEP1    (0x0200)    // Starts at Line 2 Pixel 0
#define CURSOR_SLEEP2    (0x0300)    // Starts at Line 3 Pixel 0
/**< For Power off window >                                                      */
#define CURSOR_PWROFF1   (0x0000)    // Starts at Line 0 Pixel 0
#define CURSOR_PWROFF2   (0x0100)    // Starts at Line 1 Pixel 0
#define CURSOR_PWROFF3   (0x0200)    // Starts at Line 2 Pixel 0
#define CURSOR_PWROFF4   (0x0300)    // Starts at Line 3 Pixel 0

/**< Pre-assigned string IDs and print command for operations                */
/**< Only string IDs 0 to 5 are currenlty supported                          */
/**< IDs 0 and 1 are reserved for Raga use                                   */
/**< ID 2 is assigned for "DIR:           " display line                     */
/**< ID 3 is assigned to empty characters to clear a line of display         */
/**< ID 4 is assigned for "Scroll or Select" message                         */
/**< ID 5 is used for temporary ID for error or temp messages                */
#define SID_SYS_FILE     UIF_CMD_SID_00
#define PRT_SYS_FILE     UIF_CMD_PRTS_00
#define SID_DIR_FIXED    UIF_CMD_SID_02
#define PRT_DIR_FIXED    UIF_CMD_PRTS_02
#define SID_CLEAR_LINE   UIF_CMD_SID_03
#define PRT_CLEAR_LINE   UIF_CMD_PRTS_03
#define SID_DIR_NAV      UIF_CMD_SID_04
#define PRT_DIR_NAV      UIF_CMD_PRTS_04
#define SID_TMP          UIF_CMD_SID_05
#define PRT_TMP          UIF_CMD_PRTS_05
/*****************************************************************************/
/* Scrolling                                                                 */
/*****************************************************************************/
#define SCROLL_H_LEFT    0
#define SCROLL_H_RIGHT   1
#define SCROLL_H_RATE1   1          // ? frames
#define SCROLL_H_RATE2   2          // ? frames
#define SCROLL_H_RATE3   3          // ? frames
#define SCROLL_H_RATE4   4          // ? frames

#endif
