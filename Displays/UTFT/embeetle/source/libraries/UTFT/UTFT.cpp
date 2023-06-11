/*
  UTFT.cpp - Arduino/chipKit library support for Color TFT LCD Boards
  Copyright (C)2010-2012 Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino and chipKit boards. For a 
  full list of tested display modules and controllers, see the 
  document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can always find the latest version of the library at 
  http://electronics.henningkarlsen.com/

  If you make any modifications or improvements to the code, I would 
  appreciate that you share the code with me so that I might include 
  it in the next release. I can be contacted through 
  http://electronics.henningkarlsen.com/contact.php.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "UTFT.h"
#include <pins_arduino.h>
#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#include "HW_AVR.h" 
#else
	#include "HW_PIC32.h"
#endif
#include "memorysaver.h"

UTFT::UTFT()
{
}

UTFT::UTFT(byte model, int RS, int WR,int CS, int RST, int SER)
{ 
	switch (model)
	{
		case HX8347A:
			disp_x_size=239;
			disp_y_size=319;
			display_transfer_mode=16;
			break;
		case ILI9327:
			disp_x_size=239;
			disp_y_size=399;
			display_transfer_mode=8;
			break;
		case SSD1289:
			disp_x_size=239;
			disp_y_size=319;
			display_transfer_mode=16;
			break;
		
	}
	display_model=model;

	if (display_transfer_mode!=1)
	{
		_set_direction_registers(display_transfer_mode);
		P_RS	= portOutputRegister(digitalPinToPort(RS));
		B_RS	= digitalPinToBitMask(RS);
		P_WR	= portOutputRegister(digitalPinToPort(WR));
		B_WR	= digitalPinToBitMask(WR);
		P_CS	= portOutputRegister(digitalPinToPort(CS));
		B_CS	= digitalPinToBitMask(CS);
		P_RST	= portOutputRegister(digitalPinToPort(RST));
		B_RST	= digitalPinToBitMask(RST);
		pinMode(RS,OUTPUT);
		pinMode(WR,OUTPUT);
		pinMode(CS,OUTPUT);
		pinMode(RST,OUTPUT);
	}
	else
	{
		P_SDA	= portOutputRegister(digitalPinToPort(RS));
		B_SDA	= digitalPinToBitMask(RS);
		P_SCL	= portOutputRegister(digitalPinToPort(WR));
		B_SCL	= digitalPinToBitMask(WR);
		P_CS	= portOutputRegister(digitalPinToPort(CS));
		B_CS	= digitalPinToBitMask(CS);
		P_RST	= portOutputRegister(digitalPinToPort(RST));
		B_RST	= digitalPinToBitMask(RST);
		if (display_serial_mode!=SERIAL_4PIN)
		{
			P_RS	= portOutputRegister(digitalPinToPort(SER));
			B_RS	= digitalPinToBitMask(SER);
			pinMode(SER,OUTPUT);
		}
		pinMode(RS,OUTPUT);
		pinMode(WR,OUTPUT);
		pinMode(CS,OUTPUT);
		pinMode(RST,OUTPUT);
	}
}

void UTFT::LCD_Write_COM(char VL)  
{   
	if (display_transfer_mode!=1)
	{
		cbi(P_RS, B_RS);
		LCD_Writ_Bus(0x00,VL,display_transfer_mode);
	}
	else
		LCD_Writ_Bus(0x00,VL,display_transfer_mode);
}



void UTFT::LCD_Write_DATA(char VL)
{
	if (display_transfer_mode!=1)
	{
		sbi(P_RS, B_RS);
		LCD_Writ_Bus(0x00,VL,display_transfer_mode);
	}
	else
		LCD_Writ_Bus(0x01,VL,display_transfer_mode);
}

void UTFT::LCD_Write_COM_DATA(char com1,int dat1)
{
     LCD_Write_COM(com1);
     LCD_Write_DATA(dat1);
}

void UTFT::InitLCD(byte orientation)
{
	orient=orientation;

	sbi(P_RST, B_RST);
	delay(1); 
	cbi(P_RST, B_RST);
	delay(10);
	sbi(P_RST, B_RST);
	delay(50);

	cbi(P_CS, B_CS);

	switch(display_model)
	{

#ifndef DISABLE_ILI9327
	case ILI9327:
		LCD_Write_COM(0xE9);
		LCD_Write_DATA(0x20);
		LCD_Write_COM(0x11); //Exit Sleep
		delay(100);
	    LCD_Write_COM(0xD1);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x71);
		LCD_Write_DATA(0x19);
		LCD_Write_COM(0xD0);
		LCD_Write_DATA(0x07);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x8);
		LCD_Write_COM(0x36);
		LCD_Write_DATA(0x48);
	    LCD_Write_COM(0x3A);
		LCD_Write_DATA(0x05);
	    LCD_Write_COM(0xC1);
		LCD_Write_DATA(0x10);
		LCD_Write_DATA(0x10);
		LCD_Write_DATA(0x02);
		LCD_Write_DATA(0x02);
		LCD_Write_COM(0xC0); //Set Default Gamma
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x35);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x02);
		LCD_Write_COM(0xC5); //Set frame rate
		LCD_Write_DATA(0x04);
		LCD_Write_COM(0xD2); //power setting
		LCD_Write_DATA(0x01);
		LCD_Write_COM(0x44);
		LCD_Write_COM(0xC8); //Set Gamma
		LCD_Write_DATA(0x04);
		LCD_Write_DATA(0x67);
		LCD_Write_DATA(0x35);
		LCD_Write_DATA(0x04);
		LCD_Write_DATA(0x08);
		LCD_Write_DATA(0x06);
		LCD_Write_DATA(0x24);
		LCD_Write_DATA(0x1);
		LCD_Write_DATA(0x37);
		LCD_Write_DATA(0x40);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x10);
		LCD_Write_DATA(0x8);
		LCD_Write_DATA(0x80);
		LCD_Write_DATA(0x0);
		LCD_Write_COM(0x2A); 
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0xeF);
		LCD_Write_COM(0x2B); 
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x3F);
		LCD_Write_COM(0x29); //display on      
		LCD_Write_COM(0x2C); //display on 
       
		break;
#endif

	}

	sbi (P_CS, B_CS); 

	setColor(255, 255, 255);
	setBackColor(0, 0, 0);
	cfont.font=0;
}

void UTFT::setXY(word x1, word y1, word x2, word y2)
{
	int tmp;

	if (orient==LANDSCAPE)
	{
		swap(word, x1, y1);
		swap(word, x2, y2)
		y1=disp_y_size-y1;
		y2=disp_y_size-y2;
		swap(word, y1, y2)
	}

	
		LCD_Write_COM(0x2a);
  		LCD_Write_DATA(x1>>8);
  		LCD_Write_DATA(x1);
  		LCD_Write_DATA(x2>>8);
  		LCD_Write_DATA(x2);
  		LCD_Write_COM(0x2b);
  		LCD_Write_DATA(y1>>8);
  		LCD_Write_DATA(y1);
  		LCD_Write_DATA(y2>>8);
  		LCD_Write_DATA(y2);
  		LCD_Write_COM(0x2c); 							 
		

	
}

void UTFT::clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

void UTFT::drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void UTFT::drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void UTFT::fillRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if (orient==PORTRAIT)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			drawHLine(x1, y1+i, x2-x1);
			drawHLine(x1, y2-i, x2-x1);
		}
	}
	else
	{
		for (int i=0; i<((x2-x1)/2)+1; i++)
		{
			drawVLine(x1+i, y1, y2-y1);
			drawVLine(x2-i, y1, y2-y1);
		}
	}
}

void UTFT::fillRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
	}
}

void UTFT::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);
 
	cbi(P_CS, B_CS);
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(cl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(cl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(cl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(cl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(cl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(cl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(cl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(cl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(cl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(cl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(cl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(cl);
	}
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::fillCircle(int x, int y, int radius)
{
	cbi(P_CS, B_CS);
	for(int y1=-radius; y1<=radius; y1++) 
		for(int x1=-radius; x1<=radius; x1++) 
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				setXY(x+x1, y+y1, x+x1, y+y1);
				LCD_Write_DATA((fcolorr&248)|fcolorg>>5);
				LCD_Write_DATA((fcolorg&28)<<3|fcolorb>>3);
			}
	sbi(P_CS, B_CS);
	clrXY();
}
void UTFT::show_color_bar()
{
	unsigned long i,j;
	cbi(P_CS, B_CS);
	clrXY();

	
	
		
		for (i=0; i<(disp_y_size+1); i++)
			{
				for (j=0; j<(disp_x_size+1); j++)
				{			
	 				  if(i>350){LCD_Write_DATA(0xFF);LCD_Write_DATA(0xFF);}
 	 				  else if(i>300){LCD_Write_DATA(0x00);LCD_Write_DATA(0x1F);}
 	 				  else if(i>250){LCD_Write_DATA(0x07);LCD_Write_DATA(0xE0);}
 	 				  else if(i>200){LCD_Write_DATA(0x7F);LCD_Write_DATA(0xFF);}
 	 				  else if(i>150){LCD_Write_DATA(0xF8);LCD_Write_DATA(0x00);}
 	 				  else if(i>100){LCD_Write_DATA(0xF8);LCD_Write_DATA(0x1F);}
 	 				  else if(i>50){LCD_Write_DATA(0xFF);LCD_Write_DATA(0xE0);}
					else {LCD_Write_DATA(213);LCD_Write_DATA(156);}
				}	
			}
sbi(P_CS, B_CS);
}
void UTFT::clrScr()
{
	long i;
	
	cbi(P_CS, B_CS);
	clrXY();

	if (display_transfer_mode!=1)
		sbi(P_RS, B_RS);
	for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
	{
		//if (display_transfer_mode!=1)
			//LCD_Writ_Bus(0,0,display_transfer_mode);
		//else
		//{
			LCD_Writ_Bus(0,0,display_transfer_mode);
			LCD_Writ_Bus(1,0,display_transfer_mode);
		//}
	}
	sbi(P_CS, B_CS);
}

void UTFT::fillScr(byte r, byte g, byte b)
{
	long i;
	char ch, cl;
	
	ch=((r&248)|g>>5);
	cl=((g&28)<<3|b>>3);

	cbi(P_CS, B_CS);
	clrXY();
	if (display_transfer_mode!=1)
		sbi(P_RS, B_RS);
	for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
	{
		if (display_transfer_mode!=1)
			LCD_Writ_Bus(ch,cl,display_transfer_mode);
		else
		{
			LCD_Writ_Bus(1,ch,display_transfer_mode);
			LCD_Writ_Bus(1,cl,display_transfer_mode);
		}
	}
	sbi(P_CS, B_CS);
}

void UTFT::setColor(byte r, byte g, byte b)
{
	fcolorr=r;
	fcolorg=g;
	fcolorb=b;
}

void UTFT::setBackColor(byte r, byte g, byte b)
{
	bcolorr=r;
	bcolorg=g;
	bcolorb=b;
}

void UTFT::setPixel(byte r,byte g,byte b)
{
	LCD_Write_DATA(((g&28)<<3|b>>3));	// rrrrrggggggbbbbb
    LCD_Write_DATA((r&248)|g>>5); 
} 
void UTFT::drawPixel(int x, int y)
{
	cbi(P_CS, B_CS);
	setXY(x, y, x, y);
	setPixel(fcolorr, fcolorg, fcolorb);
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	if (((x2-x1)<0))
	{
		swap(int, x1, x2);
		swap(int, y1, y2);
	}
    if (((y2-y1)<0))
	{
		swap(int, x1, x2);
		swap(int, y1, y2);
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			swap(int, x1, x2);
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			swap(int, y1, y2);
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		cbi(P_CS, B_CS);
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(cl);
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(cl);
        		ty=ty+delta;
			}
		}
		sbi(P_CS, B_CS);
	}
	else
	{
		cbi(P_CS, B_CS);
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA( cl);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA( cl);
        		tx=tx+delta;
			}
        }
		sbi(P_CS, B_CS);
	}

	clrXY();
}

void UTFT::drawHLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	cbi(P_CS, B_CS);
	setXY(x, y, x+l, y);
	for (int i=0; i<l+1; i++)
	{
		LCD_Write_DATA( cl);
	}
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::drawVLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	cbi(P_CS, B_CS);
	setXY(x, y, x, y+l);
	for (int i=0; i<l; i++)
	{
		LCD_Write_DATA( cl);
	}
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::printChar(byte c, int x, int y)
{
	byte i,ch;
	word j;
	word temp; 

	cbi(P_CS, B_CS);
  
	if (orient==PORTRAIT)
	{
		setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
		{
			ch=pgm_read_byte(&cfont.font[temp]);
			for(i=0;i<8;i++)
			{   
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
			temp++;
		}
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;

		for(j=0;j<((cfont.x_size/8)*cfont.y_size);j+=(cfont.x_size/8))
		{
			setXY(x,y+(j/(cfont.x_size/8)),x+cfont.x_size-1,y+(j/(cfont.x_size/8)));
			for (int zz=(cfont.x_size/8)-1; zz>=0; zz--)
			{
				ch=pgm_read_byte(&cfont.font[temp+zz]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<i))!=0)   
					{
						setPixel(fcolorr, fcolorg, fcolorb);
					} 
					else
					{
						setPixel(bcolorr, bcolorg, bcolorb);
					}   
				}
			}
			temp+=(cfont.x_size/8);
		}
	}
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	cbi(P_CS, B_CS);

	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch=pgm_read_byte(&cfont.font[temp+zz]); 
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else  
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}
	sbi(P_CS, B_CS);
	clrXY();
}

void UTFT::print(char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void UTFT::print(String st, int x, int y, int deg)
{
	char buf[st.length()+1];

	st.toCharArray(buf, st.length()+1);
	print(buf, x, y, deg);
}

void UTFT::printNumI(long num, int x, int y, int length, char filler)
{
	char buf[25];
	char st[27];
	boolean neg=false;
	int c=0, f=0;
  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}

	print(st,x,y);
}

void UTFT::printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
{
	char buf[25];
	char st[27];
	boolean neg=false;
	int c=0, f=0;
	int c2, mult;
	unsigned long inum;
  
	if (dec<1)
	dec=1;
	if (dec>5)
	dec=5;
	  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-2-dec); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=divider;
			for (int i=0; i<dec; i++)
				st[c+2+i]=48;
			st[c+2+dec]=0;
		}
		else
		{
			st[0]=48;
			st[1]=divider;
			for (int i=0; i<dec; i++)
				st[2+i]=48;
			st[2+dec]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		mult = 1;
		for (int j = 0; j < dec; j++)
			mult = mult * 10;
		inum=long(num*mult + 0.5);
	  
		while (inum>0)
		{
			buf[c]=48+(inum % 10);
			c++;
			inum=(inum-(inum % 10))/10;
		}
		if ((num<1) and (num>0))
		{
			buf[c]=48;
			c++;
		}
		while (c<(dec+1))
		{
			buf[c]=48;
			c++;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg-1))
		{
			for (int i=0; i<(length-c-neg-1); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		c2=neg;
		for (int i=0; i<c; i++)
		{
			st[c2+f]=buf[c-i-1];
			c2++;
			if ((c-(c2-neg))==dec)
			{
				st[c2+f]=divider;
				c2++;
			}
		}
		st[c2+f]=0;
	}

	print(st,x,y);
}

void UTFT::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}

void UTFT::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;
	byte r, g, b;

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
			cbi(P_CS, B_CS);
			setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				col=pgm_read_word(&data[tc]);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
			sbi(P_CS, B_CS);
		}
		else
		{
			cbi(P_CS, B_CS);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx; tx>=0; tx--)
				{
					col=pgm_read_word(&data[(ty*sx)+tx]);
					LCD_Write_DATA(col>>8,col & 0xff);
				}
			}
			sbi(P_CS, B_CS);
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
			cbi(P_CS, B_CS);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
			}
			sbi(P_CS, B_CS);
		}
		else
		{
			cbi(P_CS, B_CS);
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx; tx>=0; tx--)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
				}
			}
			sbi(P_CS, B_CS);
		}
	}
	clrXY();
}

void UTFT::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	byte r, g, b;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{
		cbi(P_CS, B_CS);
		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
				col=pgm_read_word(&data[(ty*sx)+tx]);

				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
		sbi(P_CS, B_CS);
	}
	clrXY();
}

void UTFT::lcdOff()
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		LCD_Write_COM(0x28);
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::lcdOn()
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		LCD_Write_COM(0x29);
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::setContrast(char c)
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		if (c>64) c=64;
		LCD_Write_COM(0x25);
		LCD_Write_DATA(c);
		break;
	}
	sbi(P_CS, B_CS);
}

int UTFT::getDisplayXSize()
{
	if (orient==PORTRAIT)
		return disp_x_size+1;
	else
		return disp_y_size+1;
}

int UTFT::getDisplayYSize()
{
	if (orient==PORTRAIT)
		return disp_y_size+1;
	else
		return disp_x_size+1;
}
