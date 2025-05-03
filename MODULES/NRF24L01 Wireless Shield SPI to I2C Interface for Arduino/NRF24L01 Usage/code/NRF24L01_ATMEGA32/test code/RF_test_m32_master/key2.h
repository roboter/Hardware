//Set up a variable: record KEY () return value
#define		KEY_DDR		DDRC
#define		KEY_PORT   PORTC
#define 	KEY_PIN		PINC

// Description: 4 * 4 keyboard using line reversal method using PA mouth
// Key: the fourth column of the third column of the second row of the first column A3 A2 A1 A0
// A7 First line: 0x77 0x7b 0x7d 0x7e
// A6 second row: 0xb7 0xbb 0xbd 0xbe
// A5 Third row: 0xd7 0xdb 0xdd 0xde
// A4 Fourth row: 0xe7 0xeb 0xed 0xee
// Fast read status, do not delay
unsigned char KEY(void)
{
	KEY_PORT=0X0F;
	KEY_DDR=0XF0;				//Four high low, low four pulled
	unsigned char key_data=0;	//Preserving key state variables
	if(KEY_PIN!=0x0F)			//If button is pressed
	{
		_delay_ms(10);			//Prevent jitter
		key_data=KEY_PIN;		//Save the state of the low four

		KEY_PORT=0XF0;
		KEY_DDR=0X0F;			//High four pulled low 4 low
		key_data|=KEY_PIN;		//Save the state of the high four and merged with the low four

		while(KEY_PIN!=0xF0);	//Waiting for the button is released
		_delay_ms(10);			//Delay eliminate jitter
		while(KEY_PIN!=0xF0);	//Waiting for the button is released
		switch(key_data)		//Key value coding
		{
			case 0x77:key_data=1; break;	//The first line
			case 0x7b:key_data=2; break;
			case 0x7d:key_data=3; break;
			case 0x7e:key_data=4; break;
			case 0xb7:key_data=5; break;	//The second line
			case 0xbb:key_data=6; break;
			case 0xbd:key_data=7; break;
			case 0xbe:key_data=8; break;
			case 0xd7:key_data=9; break;	//The third line
			case 0xdb:key_data=10;break;
			case 0xdd:key_data=11;break;
			case 0xde:key_data=12;break;
			case 0xe7:key_data=13;break;	//The forth line
			case 0xeb:key_data=14;break;
			case 0xed:key_data=15;break;
			case 0xee:key_data=16;break;
			default:key_data=0;break;		//No valid keys
		}
	}
	return (key_data);						//Back key
}
