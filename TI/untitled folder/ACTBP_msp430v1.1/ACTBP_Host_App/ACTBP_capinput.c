/*******************************************************************************
 *
 *  ACTBP_capinput.c
 *     - Function to sense user input from the capacitance touch scroll wheel
 *       and to meaure baseline threshold of the sensors
 *      
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
 * SDK
 * Texas Instruments, Inc.
 * Ver 1.0 Feb 2012
 ******************************************************************************/ 
#include "CTS_Layer.h"
#include "ACTBP_HostVars.h"

unsigned int wheel_position=ILLEGAL_SLIDER_WHEEL_POSITION;
unsigned int last_wheel_position=ILLEGAL_SLIDER_WHEEL_POSITION;
unsigned char eventCounter = 0, centerButtonTouched = 0;
unsigned int delayCounter;
extern struct ContextABP context;
extern unsigned char eventFlag;
extern const unsigned char LedWheelPosition[16];

/* ----------------MeasureCapBaseLine--------------------------------------
 * Re-measure the baseline capacitance of the wheel elements & the center  
 * button. To be called after each wake up event.                          
 * D.Dang
 * Texas Instruments, Inc.
 * Ver 0.9 Feb 2011
 * ------------------------------------------------------------------------*/
void MeasureCapBaseLine(void)
{
  /* Set DCO to 8MHz */
  /* SMCLK = 8MHz/8 = 1MHz */
  TI_CAPT_Init_Baseline(&wheel);
  TI_CAPT_Update_Baseline(&wheel,2);
  TI_CAPT_Init_Baseline(&middle_button);
  TI_CAPT_Update_Baseline(&middle_button,2);  
}

/* ----------------GetGesture----------------------------------------------
 * Determine immediate gesture based on current & previous wheel position
 * D.Dang
 * Texas Instruments, Inc.
 * Ver 0.9 Feb 2011
 * ------------------------------------------------------------------------*/
unsigned char GetGesture(unsigned char wheel_position)
{
  unsigned char gesture = INVALID_GESTURE, direction, ccw_check, cw_check; 
/* Gesturing
// determine if a direction/swipe is occuring
// the difference between the initial position and
// the current wheel position should not exceed 8
// 0-1-2-3-4-5-6-7-8-9-A-B-C-D-E-F-0...
//
// E-F-0-1-2:  cw, 4
// 2-1-0-F-E: ccw, 4
// A-B-C-D-E-F
*/
  if(last_wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION) // no else
  {
    if(last_wheel_position  > wheel_position)
    {
      /* E-D-C-B-A:  ccw, 4
      // counter clockwise: 0 < (init_wheel_position - wheel_position) < 8
      //                    gesture = init_wheel_position - wheel_position
      //
      // E-F-0-1-2:  cw, 4
      // clockwise:        0 < (init_wheel_position+wheel_position)-16 <8
      */                    
      ccw_check = last_wheel_position  - wheel_position;
      if(ccw_check < 8)
      {
        gesture = ccw_check;
        direction = COUNTER_CLOCKWISE;
      }
      else
      {
        // E-F-0-1-2:  cw, 4
        // 16 - 14 + 2 = 4
        cw_check = 16 - last_wheel_position  + wheel_position ;
        if(cw_check < 8)
        {
            gesture = cw_check;
            direction = CLOCKWISE;
        }
      }
    }
    else 
    {
      /* initial_wheel_position <= wheel_position
      // 2-1-0-F-E: ccw, 4
      // counter clockwise: 
      //                    0 < (init_wheel_position+wheel_position)-16 <8
      //                    gesture = init_wheel_position - wheel_position
      //
      // 0-1-2-3-4:  cw, 4
      // clockwise:        0 < (wheel_position - init_wheel_position) < 8
      */    
      cw_check = wheel_position - last_wheel_position ;
      if(cw_check < 8)
      {
        gesture = cw_check;
        direction = CLOCKWISE;
      }
      else
      {
        // 2-1-0-F-E: ccw, 4
        // 16 + 2 - 14 = 4
        ccw_check = 16 + last_wheel_position  - wheel_position ;
        if(ccw_check < 8)
        {
          gesture = ccw_check;
          direction = COUNTER_CLOCKWISE;
        }
      }
    }
  } 
  if (gesture == INVALID_GESTURE)
  	return gesture;
  if (direction == COUNTER_CLOCKWISE)
    return (gesture + 16);
  else
    return gesture;
}

/* ----------------GetCapTouchInput-------------------------------------------
 * Determine immediate gesture based on current & previous wheel position
 * ---------------------------------------------------------------------------*/
void GetCapTouchInput(void)
{
  unsigned char idleCounter;
  unsigned char gesture, last_gesture;
  unsigned int wheelTouchCounter = WHEEL_TOUCH_DELAY - 1;

  gesture = INVALID_GESTURE;            // Wipes out gesture history
  context.current_event = INVALID_EVNT;
  idleCounter = 0;      
  eventFlag = 0;
  
  while ((idleCounter++ < MAX_IDLE_TIME) && (eventFlag == 0))
  {
  	/* Make sure DCO is set to 8MHz & SMCLK = 8MHz/8 = 1MHz */
    TACCTL0 &= ~CCIE;   
    
    wheel_position = ILLEGAL_SLIDER_WHEEL_POSITION;       
    if (centerButtonTouched == 0)
    {
      wheel_position = TI_CAPT_Wheel(&wheel);
    }
    
    /* Process wheel touch/position/gesture  if a wheel touch is registered*/
    /* Wheel processing has higher priority than center button*/
    if(wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION)
    {
      /* Adjust wheel position based: rotate CCW by 2 positions */
      if (wheel_position < 0x08)
      {
         wheel_position += 0x40 - 0x08;
      }
      else
      {
         wheel_position -= 0x08;
         /* Adjust wheel position based: rotate CCW by 2 positions */
      }
      
      wheel_position = wheel_position >>2;  // divide by four
               
      if (context.last_event != MHOLD_ON)
      {
      	gesture = GetGesture(wheel_position);
      }            
      
      /* Add hysteresis to reduce toggling between wheel positions if no gesture 
       * has been TRULY detected. */  
      if ( (context.last_event!=SCROLL_ON) && ((gesture<=1) || (gesture==0x11) || (gesture==0x10)))
      {
        if (last_wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION)
            wheel_position = last_wheel_position;
        gesture = 0;
      }
      
      /* Turn on corresponding LED(s) */
      P1OUT = (P1OUT & BIT0) | LedWheelPosition[wheel_position];
     
      if ((gesture != 0) && (gesture != 16) && (gesture != INVALID_GESTURE) && (context.last_event != THOLD_ON) && (context.last_event != MHOLD_ON))           
      { /* A gesture has been detected */ 
        if (context.last_event!=SCROLL_ON)
        { /* Starting of a new gesture sequence */
		  /* Set Event as scroll begin */
          context.last_event = SCROLL_ON;
          last_gesture = gesture;
        } 
        /* Set Event as scroll up or down based on gesture*/
        if ((last_gesture <= 0xF && gesture <= 0xF) || (last_gesture > 0xF && gesture > 0xF))
        {
	      if (gesture <= 0xF)
	      {
	      	//Scroll Down
	      	context.current_event = SCROLL_RIGHT;
	      	// Set flag to indicate event detected
	      	eventFlag = 1;
	      }
	      else
	      {
	       	//Scroll Up
	       	context.current_event = SCROLL_LEFT;
	      	// Set flag to indicate event detected
	      	eventFlag = 1;
	      }
        }
        last_gesture = gesture;
      }      
      else
        if (context.last_event!=SCROLL_ON)
        { /* If no gesture was detected, this is constituted as a touch/tap */
          if (++wheelTouchCounter >= WHEEL_TOUCH_DELAY)
          {
          	/* Transmit wheel position  */
          	wheelTouchCounter = 0;
	        if ((wheel_position == last_wheel_position) && (context.last_event != SCROLL_ON) && (context.last_event != MHOLD_ON))
	        {
		      context.last_event = THOLD_ON;
		      switch (wheel_position)
		      {
				//UP
				case 0x0: //case 0xF: case 0x1:
				  ++eventCounter;
				  if (eventCounter == 6)
				  {
				    context.current_event = UP_HOLD; 
				    // Set flag to indicate event detected
				    eventFlag = 1;
				  }
				  break;
				//RIGHT
				case 0x4: //case 0x3: case 0x5: 
				  ++eventCounter;
				  if (eventCounter == 2)
				  {
				    context.current_event = RIGHT_HOLD; 
				    // Set flag to indicate event detected
				    eventFlag = 1;
				  }
				  break;
				//DOWN
				case 0x8: //case 0x7: case 0x9:
				  ++eventCounter;
				  if (eventCounter == 4)
				  {
				    context.current_event = DOWN_HOLD;
				    // Set flag to indicate event detected
				    eventFlag = 1;
				  }
				  break;
				//LEFT
				case 0xC: //case 0xB: case 0xD:
				  ++eventCounter;
				  if (eventCounter == 2)
				  {
				    context.current_event = LEFT_HOLD; 
				    // Set flag to indicate event detected
				    eventFlag = 1;
				  }
				  break;
				//
				default :
				  context.current_event = INVALID_EVNT;
				  context.last_event = NO_HOLD;
				  break;
		      } // end of switch (wheel_position)
	        }
          }
        }
       	else
        {
          wheelTouchCounter = WHEEL_TOUCH_DELAY - 1;
        }      	
        idleCounter = 0;                      // Reset idle counter
        last_wheel_position = wheel_position;
    } // if(wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION)
    else //else of if(wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION)  
    { /* no wheel position was detected */
      if((context.last_event != SCROLL_ON) && (context.last_event != THOLD_ON) && TI_CAPT_Button(&middle_button))
      { /* Middle button was touched */   
	    centerButtonTouched = 1;
	    P1OUT = BIT0;
	    ++eventCounter;
	    if (eventCounter == 50)
	    {
	      context.current_event = MID_HOLD;
	      context.last_event = MHOLD_ON;
	      // Set flag to indicate event detected
	      eventFlag = 1;
	      idleCounter = MAX_IDLE_TIME-2;
	    }
        delayCounter = 0x6FFF;
        while(--delayCounter != 0);
      } //if(TI_CAPT_Button(&middle_button))
      else //else of if(TI_CAPT_Button(&middle_button))   
      { /* No touch on wheel or center button was registered */
        P1OUT &= BIT0;
        if ((gesture == INVALID_GESTURE) || (context.last_event!=SCROLL_ON))
        { /* No gesture was registered previously */
          if (centerButtonTouched == 1)
          {
          	P1OUT &= ~BIT0;
          	centerButtonTouched = 0;
          	eventCounter = 0;
          	if (context.current_event != MID_HOLD)
          	{
          	  // MIDDLE button touched
          	  context.current_event = MID;
          	  // Set flag to indicate event detected
          	  eventFlag = 1;
          	}
          	else
          	{
          	  // MID HOLD END
          	  context.current_event = INVALID_EVNT;
          	}
          	context.last_event = NO_HOLD;
          	delayCounter = 0xFFFF;
          	while(--delayCounter != 0);
          }
		  if ((last_wheel_position  != ILLEGAL_SLIDER_WHEEL_POSITION) && (context.last_event != SCROLL_ON) && (context.last_event != MHOLD_ON)) 
          {
	        switch (last_wheel_position)
	        {
			  //UP
			  case 0x0 :
			    context.current_event = UP;
			    context.last_event = NO_HOLD;	        
				eventCounter = 0;
				// Set flag to indicate event detected
				eventFlag = 1;
				break;
			  //RIGHT
			  case 0x4 :
			    context.current_event = RIGHT;
			    context.last_event = NO_HOLD;
			    eventCounter = 0;
				// Set flag to indicate event detected
				eventFlag = 1;
				break;
			  //DOWN
			  case 0x8 :
			    if ((context.current_event == DOWN) && context.last_event != THOLD_ON)			    
			    {
			      context.current_event = DOWNx2;
			      context.last_event = NO_HOLD;
			      // Set flag to indicate event detected
			      eventFlag = 1;
				  eventCounter = 0;
			    }
			    else 
			    {
			      	context.current_event = DOWN;
			    }
				break;
			  //LEFT
			  case 0xC :
			    if ((context.current_event == LEFT) && context.last_event != THOLD_ON)			    
			    {
			      context.current_event = LEFTx2;
			      context.last_event = NO_HOLD;
			      // Set flag to indicate event detected
			      eventFlag = 1;
				  eventCounter = 0;
			    }
			    else 
			    {
			      	context.current_event = LEFT;
			    }
				break;
			  // All other positions
			  default :
			    context.current_event = INVALID_EVNT;
				context.last_event = NO_HOLD;
				eventCounter = 0;
				eventFlag = 1;
				break;
	        } // end of switch (wheel_position)
            wheelTouchCounter = WHEEL_TOUCH_DELAY - 1;
          } //end of if (last_wheel_position  != ILLEGAL_SLIDER_WHEEL_POSITION)
          delayCounter = 0x600F;
	      while(--delayCounter != 0);
        } //end if ((gesture == INVALID_GESTURE) || (gestureDetected ==0))
        if (context.last_event == SCROLL_ON)
        { /* End of gesture pattern */
          context.last_event = NO_HOLD;
            //use 430 timer for delay, go to lpm3 while we wait
			  TA0CCR0 = 3600; //0.3 second delay
			  TA0CCTL0 |= CCIE; //enable timer interrupt
			  TA0CCTL0 &= ~CCIFG; //make sure flag is clear
			  TA0CTL = TASSEL_1 + MC_1 + TACLR; //TACLK = ACLK = 12kHz, Up Mode, Clear TAR, start timer
			  __bis_SR_register(LPM3_bits + GIE); //go to LPM3 until woken by the timer
			  TA0CTL &= ~MC_3; //stop the timer
			  TA0CCTL0 &= ~(CCIE + CCIFG); //disable timer interrupts
        } //end if (gestureDetected == 1)
	  } //end else of if(TI_CAPT_Button(&middle_button))
      //if we do not detect a double tap and to register a hold release
      if (((context.current_event == LEFT) || (context.current_event == LEFT_HOLD)) && (++eventCounter > 4))
      {
      	context.current_event = LEFT;
      	context.last_event = NO_HOLD;
      	// Set flag to indicate event detected
      	eventFlag = 1;
      	eventCounter = 0;
      }
      //if we do not detect a double tap (we do not want to register a hold release here)
      if (((context.current_event == DOWN)) && (++eventCounter > 4))
      {
      	context.current_event = DOWN;
      	context.last_event = NO_HOLD;
      	// Set flag to indicate event detected
      	eventFlag = 1;
      	eventCounter = 0;
      }
	  // Reset all touch conditions, turn off LEDs, 
	  last_wheel_position= ILLEGAL_SLIDER_WHEEL_POSITION;      
      gesture = INVALID_GESTURE;
    } //end else of if(wheel_position != ILLEGAL_SLIDER_WHEEL_POSITION)

   /* ------------------------------------------------------------------------
   * Option:
   * Add delay/sleep cycle here to reduce active duty cycle. This lowers power
   * consumption but sacrifices wheel responsiveness. Additional timing 
   * refinement must be taken into consideration when interfacing with PC
   * applications GUI to retain proper communication protocol.
   * -----------------------------------------------------------------------*/
  } //end while (idleCounter++ < MAX_IDLE_TIME)
} //end function 
