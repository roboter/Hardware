// https://www.fypsolutions.com/stm8-cosmic-c/stm8s-uart-example-code/
// https://www.electronics-lab.com/project/getting-started-with-stm8s-using-stvd-and-cosmic-c-compiler/

// CPU SSTM8S3P6

#include <iostm8s103.h>

#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))
#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define FLIP_BIT(p,n) ((p) ^= ((1)<<(n)))
#define READ_BIT(p,n) (!!((p)&((1)<<(n))))

void CLK_Init(void);
void UART_Init(void);
void delay (int ms);

void CLK_Init()
{
	CLK_CKDIVR = 0x00; // Set Clock 16MHz
	CLK_PCKENR1 = 0xFF; // Enable peripherals
}

void UART_Init()
{	
	//	Procedure:
	// 1. Program the M bit in UART_CR1 to define the word length.
	// 2. Program the number of stop bits in UART_CR3.
	UART1_CR3 &= ~((1<<4)| (1<<4)); //1 stop bit
	// 3. Select the desired baud rate by programming the baud rate registers in the following order:
	// a) UART_BRR2
	UART1_BRR1 = 0x68;
	// b) UART_BRR1
	UART1_BRR2 = 0x03;
	// 4. Set the TEN bit in UART_CR2 to enable transmitter mode.
	UART1_CR2 |= (1<<2) | (1 << 3); // Enable RX and TX
	// 5. Write the data to send in the UART_DR register (this clears the TXE bit). Repeat this for each data to be transmitted in case of single buffer.
	// 6. Once the last data is written to the UART_DR register, wait until TC is set to ‘1’, which indicates that the last data transmission is complete. This last step is required, for instance, to avoid last data transmission corruption when disabling the UART or entering Halt mode
}

void UART_TX(unsigned char send)
{
	UART1_DR = send;
	while(!(UART1_SR & (1<<6)));
}

unsigned char UART_RX(void)
{
		while(!(UART1_SR & (1<<5)));
		return UART1_DR;
}

void main()
{
	CLK_Init();
	UART_Init();
	delay (100);
	while (1){
		unsigned char inChar = 0;
		if(UART1_SR & (1<<5))
		{
			inChar = UART_RX();
			//inChar++;
			UART_TX(inChar);
		}
	}
}

void delay (int ms) //create delay function
{
	int i = 0;
	int j = 0;
	for (i=0; i<=ms; i++)
	{
		for (j=0; j<120; j++) // Nop = Fosc/4
			_asm("nop"); //Perform no operation //assembly code <span style="white-space:pre"> </span>
	}
}

