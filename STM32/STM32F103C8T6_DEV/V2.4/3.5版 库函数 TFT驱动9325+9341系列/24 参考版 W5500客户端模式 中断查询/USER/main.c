

/*
 http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny

w5500����ģ��  �ο�����

���в���MCU STM32


TCP�ͻ���ģʽ 

�ж��жϷ�ʽ
TCP�ͻ����ǽ�ģ���Լ�����Ϊ�ͻ���Ȼ��ͷ������˽�������ͨѶ
��˴�ģʽҪȷ��ģ���Լ���IP���˿ں�Ŀ���������IP���˿�


W5500�������Ŷ�Ӧ���£� 
sck PA5  miso PA6  mosi PA7  rst PA2  int PA3  cs PA0



����·�ɸ�����ֵ

���أ�192.168.0.1		   ����Ϊ���ǲ���·�ɣ�һ���ͥ���õ�·��Ϊ192.168.1.1��
�������룺255.255.255.0	   �������������һ���ģ�
�����ַMAC��0C.29.AB.7C.00.02         (���뱣֤��һ���ֽ�Ϊż���������ֽ�����ֵ���)
����IP��W5500ģ��IP����192.168.0.246   ��ֻҪ��Ŀ��IP����ͻ���ɣ�
�����˿ڣ�5000  ��һ��Ĭ�ϣ�
Ŀ��IP��192.168.0.149	    ����ģ��Ҫ��ͬһ�����£�
Ŀ��˿ڣ�6000  ��һ��Ĭ�ϣ�

*/



#include  "delay.h"
#include  "led.h"
#include  "usart.h"
#include  "spi.h"
#include  "w5500.h"
#include  "string.h"

u32 W5500_Send_Delay=0; //W5500������ʱ��������(ms)


//װ���������
//˵��: ���ء��������롢�����ַ������IP��ַ�������˿ںš�Ŀ��IP��ַ��Ŀ�Ķ˿ںš��˿ڹ���ģʽ
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;//�������ز���
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 0;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//������������
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;//���������ַ
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x02;

	IP_Addr[0]=192;//���ر���IP��ַ
	IP_Addr[1]=168;
	IP_Addr[2]=0;
	IP_Addr[3]=246;

	S0_Port[0] = 0x13;//���ض˿�0�Ķ˿ں�5000 
	S0_Port[1] = 0x88;

	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
	S0_DIP[1]=168;
	S0_DIP[2]=0;
	S0_DIP[3]=149;
	
	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
	S0_DPort[1] = 0x70;

	S0_Mode=TCP_CLIENT;//���ض˿�0�Ĺ���ģʽ,TCP�ͻ���ģʽ
}




//W5500��ʼ������
void W5500_Initialization(void)
{
	W5500_Init();		//��ʼ��W5500�Ĵ���
	Detect_Gateway();	//������ط����� 
	Socket_Init(0);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�0
}




//����    : W5500�˿ڳ�ʼ������
//˵�� : �ֱ�����4���˿�,���ݶ˿ڹ���ģʽ,���˿�����TCP��������TCP�ͻ��˻�UDPģʽ.
//		 �Ӷ˿�״̬�ֽ�Socket_State�����ж϶˿ڵĹ������
void W5500_Socket_Set(void)
{
	if(S0_State==0)//�˿�0��ʼ������
	{
		if(S0_Mode==TCP_SERVER)//TCP������ģʽ 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode==TCP_CLIENT)//TCP�ͻ���ģʽ 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDPģʽ 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
}




//W5500���ղ����ͽ��յ�������
//s:�˿ں�
//˵�� : �������ȵ���S_rx_process()��W5500�Ķ˿ڽ������ݻ�������ȡ����,
//		 Ȼ�󽫶�ȡ�����ݴ�Rx_Buffer������Temp_Buffer���������д���
//		 ������ϣ������ݴ�Temp_Buffer������Tx_Buffer������������S_tx_process()
//		 �������ݡ�
void Process_Socket_Data(SOCKET s)
{
	u16 size;
	size=Read_SOCK_Data_Buffer(s, Rx_Buffer);
	memcpy(Tx_Buffer, Rx_Buffer, size);			
	Write_SOCK_Data_Buffer(s, Tx_Buffer, size);
}





int main(void)
   {

   	delay_init();	    	 //��ʱ������ʼ��

	//uart_init(9600);	 //���ڳ�ʼ��Ϊ9600  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	SPI1_Init();	 //��ʼ��SPI1  PA5 PA6 PA7 IOΪSPIģʽ
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);	 //����SPI1�ٶ�Ϊ���

	W5500_GPIO_Init();//��ʼ��W5500  RST INT SCS��ӦGPIO״̬ ������INT�ж�ģʽ

	Load_Net_Parameters();		//װ���������	
	W5500_Hardware_Reset();		//Ӳ����λW5500
	W5500_Initialization();		//W5500��ʼ������

 
 	while(1)
	{

		W5500_Socket_Set();//W5500�˿ڳ�ʼ������

		if(W5500_Interrupt)//����W5500�ж�		
		{
			W5500_Interrupt_Process();//W5500�жϴ��������
		}
		if((S0_Data & S_RECEIVE) == S_RECEIVE)//���Socket0���յ�����
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500���ղ����ͽ��յ�������
		}		
		else if(W5500_Send_Delay>=720000)//��ʱ�����ַ���
		{
			if(S0_State == (S_INIT|S_CONN))
			{
				S0_Data&=~S_TRANSMITOK;
				memcpy(Tx_Buffer, "\r\n����Ƽ� W5500�ͻ���TEST\r\n", 30);	
				Write_SOCK_Data_Buffer(0, Tx_Buffer, 30);//ָ��Socket(0~7)�������ݴ���,�˿�0����30�ֽ�����
			}
			W5500_Send_Delay=0;
		}	

		W5500_Send_Delay++;

	}

   }

