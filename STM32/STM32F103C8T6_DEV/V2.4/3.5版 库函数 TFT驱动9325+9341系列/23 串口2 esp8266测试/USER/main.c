

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

/*
ESP8266 AP+Station������ģʽ����


UART2 PA2 PA3  ������ģ��ESP����ͨ��

UART1 PA9 PA10 �������ݸ���



STM32C8ϵ�� ����û�д���оƬ  ���������ʵ�� Ҫ�õ�����ģ��




*/



  



#include  "delay.h"
#include  "led.h"
#include  "usart.h"

#include  "string.h"


extern  u8 RX_buffer[tbuf];
extern u8 RX_num;				 //���ռ�������


 u8  esp_at[]="AT\r\n";                  // ��������ָ�����"OK"
 u8  esp_cwmode[]="AT+CWMODE=3\r\n";     // ����ESP8266�Ĺ���ģʽ3 AP+Station������"OK"����"no change"
 u8  esp_cifsr[]="AT+CIFSR\r\n";         // ����IP��ַ��ѯָ��
 u8  esp_cipsend[]="AT+CIPSEND=6\r\n";   // ���÷������ݳ���
 u8  esp_test[]="sunny\r\n";   			//  ��������
 u8  esp_cipserver[]="AT+CIPSERVER=1,5000\r\n";  //����TCP�����������Ŷ˿�5000							
 u8  esp_cipmux[]="AT+CIPMUX=1\r\n";   			//�򿪶�����	
 u8  esp_rst[]="AT+RST\r\n"; 					// �����λ



//ָ���ַ����뻺���������ݽ������ݱȽ�
//*p Ҫ�Ƚϵ�ָ���ַ���ָ������
//���أ�1 ����һ��  0 ���ݲ�һ�� 
u8 Data_compare(u8 *p)
{ 
	if(strstr(RX_buffer,p)!=NULL)
	    return 1;
	else
		return 0;
}


int main(void)
   {	


   	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�


	delay_ms(500);

	memset(RX_buffer, 0, tbuf);//�建������
	RX_num=0;				   //���ռ���������0


	//����AT ��������
    while(1)
	{
	 Uart2SendStr(esp_at);	   //����2��wifiģ�鷢������ָ�� ��AT
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR1,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,mcu connection success with ESP8266! \r\n");
	 memset(RX_buffer, 0, tbuf);//�建������
	 RX_num=0;				   //���ռ���������0


	//����wifi����ģʽΪap+staģʽ
    while(1)
	{
	 Uart2SendStr(esp_cwmode);	   //����2��wifiģ�鹤��ģʽ��������  
	 if(Data_compare("OK")||Data_compare("no change"))break;
	 else  Uart1SendStr("ERROR2,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,set mode as AP+Station with ESP8266! \r\n");	 
	 memset(RX_buffer, 0, tbuf);//�建������	
	 RX_num=0;				   //���ռ���������0



	//����wifiΪ��·������ģʽ
    while(1)
	{
	 Uart2SendStr(esp_cipmux);	   //����2��wifiģ�� ���ö����� ����·����ģʽ��
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR3,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//�建������
	RX_num=0;				   //���ռ���������0




	//����wifiΪ������ģʽ ���ö˿ں�Ϊ5000
    while(1)
	{
	 Uart2SendStr(esp_cipserver);	   //����2����wifiģ�� ΪTCP������ģʽ�������ö˿�Ϊ5000 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR4,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//�建������
	RX_num=0;				   //���ռ���������0



	//��ѯģ��ip
    while(1)
	{
	 Uart2SendStr(esp_cifsr);	   //����2��ѯwifiģ�� ��ǰip��ַ 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR5,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	Uart1SendStr(RX_buffer);
	memset(RX_buffer, 0, tbuf);//�建������
	RX_num=0;				   //���ռ���������0


	while(1)
	{	
		if(Data_compare("LEDK"))               //���������˵�led
		{	
            led(1);	
			memset(RX_buffer, 0, tbuf);//�建������
			RX_num=0;				   //���ռ��������0
			Uart1SendStr("led is open��\r\n");							
		}
	    else if(Data_compare("LEDG")) 		   //�رհ����˵�led
		{
            led(0);		
			memset(RX_buffer, 0, tbuf);//�建������
			RX_num=0;				   //���ռ��������0
			Uart1SendStr("led is close��\r\n");									
		}	
	}


   }

