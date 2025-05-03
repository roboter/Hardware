
//Function: This procedure applies to drive NRF24L01 send data
//Platform£ºATMEGA32A-PU
//Fuse bytes£º
//		  Low byte£º0xc1
//		  High byte£º0xd9
//		  Extend£º0x00
//		  Lock byte£º0xff;
//Crystal : Internal RC oscillator 1MHz
//Time: September 5, 2012
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "spi.h"			//2401 Internal pin connection
#include "2401.h"		

void delay_ms(int x)//1ms
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<44;j++);
}
int main()
{

	SPI_Init();
	sei();

//***********************************************************
	RF2401_Init();			//initialization NRF2401
 	Tx_Mode();				//send mode

	PORT_SPI&=~(1<<CSN);
	SpiRW(1|W_REGSITER);	//write regsiter 1
	SpiRW(0x0);				//Prohibit automatic answering
	PORT_SPI|=(1<<CSN);

	PORTB&=~(1<<CSN);   
	SpiRW(0x31);			
	SpiRW(0X20);			//Channel 0 data width of 32
	PORTB|=(1<<CSN);
	_delay_ms(1);

	while(1) 
	{
		unsigned char irq_sta;
		irq_sta=Read_IRQ();
		unsigned char i;
		for(i=0;i<32;i++)			//
			TxData[i]=String[i];
		Tx_Mode();  
		W_Send_Data(32);
			
		if(irq_sta&(1<<TX_DS))
		{
			Clr_IRQ(1<<TX_DS);
		}
		delay_ms(1000);
	}
}
