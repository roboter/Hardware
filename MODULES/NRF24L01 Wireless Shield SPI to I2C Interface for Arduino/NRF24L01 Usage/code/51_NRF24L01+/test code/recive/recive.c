/**************************************************
���ܣ�����������nRF24L01+�Ľ���,����ʾ�����ַ�����
ʱ�䣺2012��7��12��
/**************************************************/

#include <reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;

// Define interface to nRF24L01

// Define SPI pins
sbit CE   = P1^0;  // Chip Enable pin signal (output)
sbit CSN  = P1^1;  // Slave Select pin, (output to CSN, nRF24L01)
sbit SCK  = P1^2;  // Master Out, Slave In pin (output)
sbit MOSI = P1^3;  // Serial Clock pin, (output)
sbit MISO = P1^4;  // Master In, Slave Out pin (input)
sbit IRQ  = P1^5;  // Interrupt signal, from nRF24L01 (input)

// SPI(nRF24L01) commands
#define READ_REG    0x00  // Define read command to register
#define WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

// SPI(nRF24L01) registers(addresses)
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address


/***************************************************/
#define TX_ADR_WIDTH   5  // 5�ֽڿ�ȵķ���/���յ�ַ
#define TX_PLOAD_WIDTH 16  // ����ͨ����Ч���ݿ��
uchar code TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  // ����һ����̬���͵�ַ
uchar string[]="Trans_Direction:";
uchar RX_BUF[TX_PLOAD_WIDTH];
uchar TX_BUF[TX_PLOAD_WIDTH];
uchar flag;
uchar k;
uchar bdata sta;
sbit  RX_DR	 = sta^6;
sbit  TX_DS	 = sta^5;
sbit  MAX_RT = sta^4;
/**************************************************/
/**************************************************/

//LCD1602

/**************************************************
����: delay()

����:
    ��ʱ100us
/**************************************************/
void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<110;j++);
}
/**************************************************
����: Write_Command()

����:
    LCD1602дָ��
/**************************************************/

void Write_Command(uchar command)//дָ��
{
	E=0;
	RS=0;
	RW=0;	
	P0=command;
	_nop_();	
	E=1;	
	delay(2);
	E=0;
}
/**************************************************
����: Write_Data()

����:
    LCD1602д����
/**************************************************/
void Write_Data(uchar dat)//д����
{
	E=0;
	RS=1;
	RW=0;
	P0=dat;
	_nop_();
	E=1;
	delay(2);
	E=0;
}
/**************************************************
����: init()

����:
    ��ʼ��LCD1602
/**************************************************/
void init(void)//LCD1602��ʼ��
{
	delay(150);
	Write_Command(0x38);
	delay(50);
	Write_Command(0x38);
	delay(50);
	Write_Command(0x38);
	Write_Command(0x38);
	Write_Command(0x08);
	Write_Command(0x01);
	Write_Command(0x06);
	Write_Command(0x0c);		
}
/**************************************************
����: init_io()

����:
    ��ʼ��IO
/**************************************************/
void init_io(void)
{
	CE  = 0;        // ����
	CSN = 1;        // SPI��ֹ
	SCK = 0;        // SPIʱ���õ�
	IRQ = 1;        // �жϸ�λ
	//P0 = 0xff;		// �ر�ָʾ��
}
/**************************************************/

/**************************************************
������delay_ms()

������
    �ӳ�x����
/**************************************************/
void delay_ms(uchar x)
{
    uchar i, j;
    i = 0;
    for(i=0; i<x; i++)
    {
       j = 250;
       while(--j);
	   j = 250;
       while(--j);
    }
}
/**************************************************/

/**************************************************
������SPI_RW()

������
    ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01
	����һ�ֽ�
/**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar i;
   	for(i=0; i<8; i++)          // ѭ��8��
   	{
   		MOSI = (byte & 0x80);   // byte���λ�����MOSI
   		byte <<= 1;             // ��һλ��λ�����λ
   		SCK = 1;                // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   		byte |= MISO;       	// ��MISO��byte���λ
   		SCK = 0;            	// SCK�õ�
   	}
    return(byte);           	// ���ض�����һ�ֽ�
}
/**************************************************/

/**************************************************
������SPI_RW_Reg()

������
    д����value��reg�Ĵ���
/**************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;
  	CSN = 0;                   // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
  	SPI_RW(value);             // Ȼ��д���ݵ��üĴ���
  	CSN = 1;                   // CSN���ߣ��������ݴ���
  	return(status);            // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Read()

������
    ��reg�Ĵ�����һ�ֽ�
/**************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	SPI_RW(reg);                // ѡ��Ĵ���
  	reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(reg_val);            // ���ؼĴ�������
}
/**************************************************/

/**************************************************
������SPI_Read_Buf()

������
    ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ��
	���ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Write_Buf()

������
    ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢
	��ͨ�����ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	SPI_RW(pBuf[i]);        // ����ֽ�д��nRF24L01
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������RX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ���ȴ����շ����豸�����ݰ�
/**************************************************/
void RX_Mode(void)
{
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
  	CE = 1;                                            // ����CE���������豸
}
/**************************************************/

/**************************************************
������TX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ����CE=1��������10us����
	130us���������䣬���ݷ��ͽ����󣬷���ģ���Զ�ת�����
	ģʽ�ȴ�Ӧ���źš�
/**************************************************
void TX_Mode(uchar * BUF)
{
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
  	SPI_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);         // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	CE = 1;
}

/**************************************************
������main()

������
    ������
/**************************************************/
void main(void)
{
	init_io();		              //��ʼ��NRF24L01+
	init();						  //��ʼ��LCD1602

	while(1)
	{	
		RX_Mode();		              //����Ϊ����ģʽ
		sta = SPI_Read(STATUS);	  // ��״̬�Ĵ���
	    if(RX_DR)				  // �ж��Ƿ���ܵ�����
		{
			SPI_Read_Buf(RD_RX_PLOAD, RX_BUF, TX_PLOAD_WIDTH);  // ��RX FIFO��������
			flag = 1;
		}
		SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���RX_DS�жϱ�־
		if(flag)		           // �������
		{
			uchar i;
			flag = 0;		       // ���־
			Write_Command(0x80+0x00);
			for(i=0;i<16;i++)
			{
				Write_Data(string[i]);
				//delay(1);
			}
			
			Write_Command(0x80+0x40);
			for(i=0;i<16;i++)
			{
				Write_Data(RX_BUF[i]);
				//delay(1);
			}
			delay_ms(1);
			/*delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);*/					  		
		}
	}
}
/**************************************************/