

/* http://zq281598585.taobao.com/  
Æô¹âµç×Ó	  ELH    enlighten  sunny
STM32 ¿ª·¢°å ¿âº¯Êı²¿·Ö	  */

/*
ESP8266 AP+Station·şÎñÆ÷Ä£Ê½²âÊÔ


UART2 PA2 PA3  ÓëÍøÂçÄ£¿éESP½øĞĞÍ¨ĞÅ

UART1 PA9 PA10 ½øĞĞÊı¾İ¸ú×Ù



STM32C8ÏµÁĞ °åÉÏÃ»ÓĞ´®¿ÚĞ¾Æ¬  Èç¹ûÏë×ö´ËÊµÑé ÒªÓÃµ½´®¿ÚÄ£¿é




*/



  



#include  "delay.h"
#include  "led.h"
#include  "usart.h"

#include  "string.h"


extern  u8 RX_buffer[tbuf];
extern u8 RX_num;				 //½ÓÊÕ¼ÆÊı±äÁ¿


 u8  esp_at[]="AT\r\n";                  // ÎÕÊÖÁ¬½ÓÖ¸Áî£¬·µ»Ø"OK"
 u8  esp_cwmode[]="AT+CWMODE=3\r\n";     // ÉèÖÃESP8266µÄ¹¤×÷Ä£Ê½3 AP+Station£¬·µ»Ø"OK"»òÕß"no change"
 u8  esp_cifsr[]="AT+CIFSR\r\n";         // ±¾»úIPµØÖ·²éÑ¯Ö¸Áî
 u8  esp_cipsend[]="AT+CIPSEND=6\r\n";   // ÉèÖÃ·¢ËÍÊı¾İ³¤¶È
 u8  esp_test[]="sunny\r\n";   			//  Êı¾İÄÚÈİ
 u8  esp_cipserver[]="AT+CIPSERVER=1,5000\r\n";  //½¨Á¢TCP·şÎñÆ÷£¬¿ª·Å¶Ë¿Ú5000							
 u8  esp_cipmux[]="AT+CIPMUX=1\r\n";   			//´ò¿ª¶àÁ¬½Ó	
 u8  esp_rst[]="AT+RST\r\n"; 					// Èí¼ş¸´Î»



//Ö¸¶¨×Ö·û´®Óë»º´æÊı×éÊı¾İ½øĞĞÊı¾İ±È½Ï
//*p Òª±È½ÏµÄÖ¸¶¨×Ö·û´®Ö¸ÕëÊı¾İ
//·µ»Ø£º1 Êı¾İÒ»ÖÂ  0 Êı¾İ²»Ò»ÖÂ 
u8 Data_compare(u8 *p)
{ 
	if(strstr(RX_buffer,p)!=NULL)
	    return 1;
	else
		return 0;
}


int main(void)
   {	


   	delay_init();	    	 //ÑÓÊ±º¯Êı³õÊ¼»¯
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart_init(115200);	 //´®¿Ú³õÊ¼»¯Îª9600  
	LED_Init();		  	//³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú


	delay_ms(500);

	memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
	RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0


	//·¢ËÍAT ½øĞĞÎÕÊÖ
    while(1)
	{
	 Uart2SendStr(esp_at);	   //´®¿Ú2¶ÔwifiÄ£¿é·¢ËÍÎÕÊÖÖ¸Áî ¼´AT
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR1,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,mcu connection success with ESP8266! \r\n");
	 memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
	 RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0


	//ÅäÖÃwifi¹¤×÷Ä£Ê½Îªap+staÄ£Ê½
    while(1)
	{
	 Uart2SendStr(esp_cwmode);	   //´®¿Ú2¶ÔwifiÄ£¿é¹¤×÷Ä£Ê½½øĞĞÉèÖÃ  
	 if(Data_compare("OK")||Data_compare("no change"))break;
	 else  Uart1SendStr("ERROR2,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,set mode as AP+Station with ESP8266! \r\n");	 
	 memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ	
	 RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0



	//ÅäÖÃwifiÎª¶àÂ·¿ÉÁ¬½ÓÄ£Ê½
    while(1)
	{
	 Uart2SendStr(esp_cipmux);	   //´®¿Ú2¶ÔwifiÄ£¿é ÉèÖÃ¶àÁ¬½Ó £¨¶àÂ·Á¬½ÓÄ£Ê½£©
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR3,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
	RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0




	//ÅäÖÃwifiÎª·şÎñÆ÷Ä£Ê½ ÅäÖÃ¶Ë¿ÚºÅÎª5000
    while(1)
	{
	 Uart2SendStr(esp_cipserver);	   //´®¿Ú2ÉèÖÃwifiÄ£¿é ÎªTCP·şÎñÆ÷Ä£Ê½£¬²¢ÅäÖÃ¶Ë¿ÚÎª5000 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR4,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
	RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0



	//²éÑ¯Ä£¿éip
    while(1)
	{
	 Uart2SendStr(esp_cifsr);	   //´®¿Ú2²éÑ¯wifiÄ£¿é µ±Ç°ipµØÖ· 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR5,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	Uart1SendStr(RX_buffer);
	memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
	RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿Çå0


	while(1)
	{	
		if(Data_compare("LEDK"))               //µãÁÁ°åÉÏÁËµÄled
		{	
            led(1);	
			memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
			RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿å0
			Uart1SendStr("led is open£¡\r\n");							
		}
	    else if(Data_compare("LEDG")) 		   //¹Ø±Õ°åÉÏÁËµÄled
		{
            led(0);		
			memset(RX_buffer, 0, tbuf);//Çå»º´æÊı¾İ
			RX_num=0;				   //½ÓÊÕ¼ÆÊı±äÁ¿å0
			Uart1SendStr("led is close£¡\r\n");									
		}	
	}


   }

