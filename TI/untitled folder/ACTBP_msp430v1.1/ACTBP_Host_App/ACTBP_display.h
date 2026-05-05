/*******************************************************************************
 *
 *  ACTBP_display.h - Definition file for functions related to printing 
 *                      operation information on OLED screen on the C55 Audio
 *                      Booster pack.
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
#ifndef _ACTBP_DISPLAY_H_
#define _ACTBP_DISPLAY_H_

void DisplayOff(void);
void DisplayOn(void);
void HScrollSet(unsigned int scroll_dir, unsigned int scroll_rate, unsigned int first_line, unsigned int last_line);
void HScrollOn(void);
void HScrollOff(void);
void SetScreen(unsigned int line_from, unsigned int line_to, unsigned int vpixel_incr, unsigned int do_vscroll, unsigned int vscroll_delay);
void InitDisplayScreen(void);
void UpdateDisplay_Dir(void);
void UpdateDisplay_File(void);
void Print_USBErr(void);
void Print_USBMSC_Wait(void);
void Print_USBMSC(void);
void Print_ClearLine(unsigned int cursor_location);
void Print_DirNav(unsigned int cursor_location);
void Print_Sleep(void);
void Print_WakeUp(void);
void Print_PwrOff(void);
void Print_RecInit(void);
void Print_RecErr(void);
void Print_CommErr(void);
#endif
