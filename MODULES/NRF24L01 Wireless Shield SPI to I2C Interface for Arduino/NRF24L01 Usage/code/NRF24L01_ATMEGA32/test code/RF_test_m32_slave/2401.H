///***************************
///***************************
//NRF24L01£¬The basic function
///***************************
//Basic command definition
#define R_REGSITER	  0X00	//Read registers directly address bitwise
#define W_REGSITER	  0X20	//write registers      Bitwise OR with address
#define R_RX_PAYLOAD  0X61	//read data 1-32 byte  From the beginning of 0 bytes
#define W_TX_PAYLOAD  0XA0	//write data 1-32 byte  From the beginning of 0 bytes
#define FLUSH_TX	  0xe1	//clear TX FIFO regsiters
#define FLUSH_RX      0XE2	//clear RX FIFO regsiters  This command should not be used when the transfer acknowledge signal
#define RESUSE_TX_PL  0XE3	//Re-use on a packet of valid data when CE is high, the data packets continually re-launch
#define NOP			  0XFF	//Empty command is used to retrieve data

//Flag in the status register
#define RX_DR	6	//Receive interrupt
#define	TX_DS	5	//Send completed interrupt
#define MAX_RT	4	//Retransmission interrupt

#define RECE_DATA_NUM	32	//The maximum amount of receive data
#define TRAN_DATA_NUM	32	//The maximum amount of sending data
#define TxAddNum		5	//Send address width
#define RxAddNum		5	//recive address width

unsigned char TxData[TRAN_DATA_NUM];		//To send data	
unsigned char String[TRAN_DATA_NUM]="Welcome to chip_partner store   ";	//To recive data
unsigned char RxData[TRAN_DATA_NUM];	//To recive data
unsigned char TxAdd[TxAddNum]={0XE7,0XE7,0XE7,0XE7,0XE7};
///*********************
//2401 initialization
///*********************
void RF2401_Init(void)
{
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN)|(1<<CE));	//Set MOSI, SCK, CSN output, the remaining input
	DDR_SPI&=~((1<<MISO)|(1<<IRQ));	
	PORT_SPI|=(1<<CSN);
}
///*********************
//send mode
///*********************
void Tx_Mode(void)
{
	PORT_SPI&=~(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);			//write regsiters 0
	SpiRW(0x12);		//Enable all interrupts, crc, 8 crc power-transmission mode
	PORT_SPI|=(1<<CSN);
	PORT_SPI|=(1<<CE);
	_delay_ms(1);
}
///*********************
//recive mode
///*********************
void Rx_Mode(void)
{
	PORT_SPI|=(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);		
	SpiRW(0x13);		//Enable all interrupts, crc, 8 crc power-receiving mode
	PORT_SPI|=(1<<CSN);
	_delay_ms(2);
}
///*********************
//Standby mode 1
///*********************
void Sleep1_Mode(void)
{
	PORT_SPI&=~(1<<CE);
}
///*********************
//Write to send data
///*********************
void W_Send_Data(unsigned char send_data_num)
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_TX);	//Clear TX fifo register
	PORT_SPI|=(1<<CSN);
	PORT_SPI&=~(1<<CSN);
	SpiRW(W_TX_PAYLOAD);//write command
	unsigned char i;
	for(i=0;i<send_data_num;i++)
	{
		SpiRW(TxData[i]);
	}
	PORT_SPI|=(1<<CSN);
}
///*********************
//Read the received valid data
///*********************
void Read_Rx(unsigned char rece_data_num)//Enter the number of data to be read
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(R_RX_PAYLOAD);
	unsigned char i;
	for(i=0;i<rece_data_num;i++)
	{
		RxData[i]=SpiRW(NOP);
	}
	PORT_SPI|=(1<<CSN);

	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_RX);	//
	PORT_SPI|=(1<<CSN);
}
///*********************
//Read interrupt flag
///*********************
unsigned char Read_IRQ(void)
{
	PORT_SPI&=~(1<<CSN);
	unsigned char sta;
	sta=SpiRW(0X07);					//Read the status register 
	PORT_SPI|=(1<<CSN);
	return sta;
}
///*********************
//Clear the flag
///*********************
void Clr_IRQ(unsigned char note)	//Example£ºCle_IRQ(((1<<tx_dr)|(1<<max_rt)))
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(0X07|W_REGSITER);		//Write status register
	SpiRW(note);
	PORT_SPI|=(1<<CSN);
}
