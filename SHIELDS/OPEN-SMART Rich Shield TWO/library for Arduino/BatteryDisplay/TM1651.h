//  Author:Fred.Chu
//  Date:14 August, 2014
//
//  Applicable Module:
//                     Battery Display v1.0
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/

#ifndef TM1651_H
#define TM1651_H
#include <inttypes.h>
#include <Arduino.h>
	//************definitions for TM1651*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
	
#define STARTADDR  0xc0 
	/**** definitions for the frame of the battery display *******/
#define FRAME_ON   1
#define FRAME_OFF  0
	/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class TM1651
{
  public:
	uint8_t Cmd_SetData;
	uint8_t Cmd_SetAddr;
	uint8_t Cmd_DispCtrl;
	TM1651(uint8_t, uint8_t);
	void init();
	void writeByte(int8_t wr_data);//write 8bit data to tm1651
	void start(void);//send start bits
	void stop(void); //send stop bits
	void displayLevel(uint8_t Level);
	void frame(boolean FrameFlag);
	void clearDisplay(void);
	void set(uint8_t = BRIGHT_TYPICAL,uint8_t = 0x40,uint8_t = 0xc0);//To take effect the next time it displays.
  private:
	uint8_t Clkpin;
	uint8_t Datapin;
	void bitDelay();
};
#endif
