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
#include "TM1651.h"
#include <Arduino.h>
static int8_t LevelTab[] = {0x00,0x40,0x60,0x70,0x78,0x7c,0x7e,0x7f};//Level 0~7
	
TM1651::TM1651(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}

void TM1651::init()
{
  set(BRIGHT_TYPICAL);
  clearDisplay();
}

void TM1651::writeByte(int8_t wr_data)
{
 	uint8_t data = wr_data;
	
	 // 8 Data Bits
	 for(uint8_t i = 0; i < 8; i++) {
	   // CLK low
	   pinMode(Clkpin, OUTPUT);
	   bitDelay();
	
	   // Set data bit
	   if (data & 0x01)
		 pinMode(Datapin, INPUT);
	   else
		 pinMode(Datapin, OUTPUT);
	
	   bitDelay();
	
	   // CLK high
	   pinMode(Clkpin, INPUT);
	   bitDelay();
	   data = data >> 1;
	 }
	
	 // Wait for acknowledge
	 // CLK to zero
	 pinMode(Clkpin, OUTPUT);
	 pinMode(Datapin, INPUT);
	 bitDelay();
	
	 // CLK to high
	 pinMode(Clkpin, INPUT);
	 bitDelay();
	 uint8_t ack = digitalRead(Datapin);
	 if (ack == 0)
	   pinMode(Datapin, OUTPUT);
	
	
	 bitDelay();
	 pinMode(Clkpin, OUTPUT);
	 bitDelay();
  
}
//send start signal to TM1651
void TM1651::start(void)
{
	pinMode(Datapin, OUTPUT);
	 bitDelay();
} 
//End of transmission
void TM1651::stop(void)
{
  pinMode(Datapin, OUTPUT);
  bitDelay();
  pinMode(Clkpin, INPUT);
  bitDelay();
  pinMode(Datapin, INPUT);
  bitDelay(); 


}
//******************************************
void TM1651::displayLevel(uint8_t Level)
{
  if(Level > 7)return;//Level should be 0~7
  start();          //start signal sent to TM1651 from MCU
  writeByte(ADDR_FIXED);//
  stop();           //
  start();          //
  writeByte(0xc0);//
  writeByte(LevelTab[Level]);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void TM1651::frame(boolean FrameFlag)
{
  int8_t SegData;
  if (FrameFlag == 1) SegData = 0x40;
  else SegData = 0x00;
  start();          //start signal sent to TM1651 from MCU
  writeByte(ADDR_AUTO);//
  stop();           //
  start();          //
  writeByte(0xc1);//
  for(uint8_t i=0;i < 3;i ++)
  {
    writeByte(SegData);        //
  }
  stop();           //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void TM1651::clearDisplay(void)
{
  displayLevel(0);
  frame(FRAME_OFF);
}
//To take effect the next time it displays.
void TM1651::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

void TM1651::bitDelay()
{
	delayMicroseconds(50);
}

