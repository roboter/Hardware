
//Function:This procedure applies to nRF24L01 receive mode, and Serial display data received
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

#include "spi.h"
#include "usart.h"
#include "2401.h"		//Internal pin connection

int main()
{
	Usart_Init(9600);
	SPI_Init();
	sei();


	RF2401_Init();			//initialization NRF2401
 	Rx_Mode();				//recive mode

	PORT_SPI&=~(1<<CSN);
	SpiRW(1|W_REGSITER);	//write regsiter 1
	SpiRW(0x0);				//Prohibit automatic answering
	PORT_SPI|=(1<<CSN);

	PORTB&=~(1<<CSN);   
	SpiRW(0x31);			
	SpiRW(0X20);			//Channel 0 data width of 32
	PORTB|=(1<<CSN);
	_delay_ms(1);



	unsigned int  counter=0;
	unsigned char send_data=1,right=0;
	while(1) 
	{
		if(!(PINB&(1<<IRQ)))
		{  
			unsigned char irq_sta;
			irq_sta=Read_IRQ();
			if(irq_sta&(1<<RX_DR))
			{
				Clr_IRQ(1<<RX_DR);
				Read_Rx(32);
				_delay_ms(1);
				unsigned char i;
				for(i=0;i<32;i++)			
					Usart_Transmit(RxData[i]);
				Usart_Transmit('\n\t');
			}
		}
	}
}
