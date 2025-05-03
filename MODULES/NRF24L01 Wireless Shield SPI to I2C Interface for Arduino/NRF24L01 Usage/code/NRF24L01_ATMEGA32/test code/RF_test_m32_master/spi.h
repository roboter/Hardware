///SPI Macro definition
#define DDR_SPI		DDRB
#define PORT_SPI	PORTB
#define CSN 		PB4	
#define MOSI 		PB5
#define MISO 		PB6
#define SCK 		PB7
#define CE			PB3
#define IRQ			PB2

//SPI initialization
void SPI_Init(void)
{
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN)|(1<<CE));	//Set MOSI, SCK, CSN output, the remaining input
	DDR_SPI&=~((1<<MISO)|(1<<IRQ));					//Has been the host mode
	SPCR|=((1<<SPE)|(1<<MSTR));						//enable SPI¡¢Host computer£¬set clock rate fck/4
			
										//
}
// SPIBasic literacy function
uint8_t SpiRW(uint8_t val)  	
{
	uint8_t temp; 
    SPDR=val; 
	while (!(SPSR&(1<<SPIF)))
		; 
	temp=SPDR; 
    return temp; 
} 
