unsigned char ur_data=0;	//The storage serial port receives data
//Serial port initialization
void Usart_Init(unsigned int BAUD)
{
	UBRRH=(F_CPU /BAUD/16-1)/256;			//Set the baud rate:fosc/(16*(UBRR+1))
	UBRRL=(F_CPU /BAUD/16-1)%256;
	UCSRB|=(1<<RXEN)|(1<<TXEN);				//Enable receive, send
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);//Z1Z0:00-11,5-8 bit data
} 
//send data
void Usart_Transmit(unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));				//Waiting to be sent register empty
	UDR=data;								//Data into buffer, sends
}
//Receive interrupt
/*SIGNAL(SIG_UART_RECV)
{
	unsigned char data=0;
	data=UDR;
	Usart_Transmit(data);
	ur_data=data;
}*/
