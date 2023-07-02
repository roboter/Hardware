

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

//STM32����1 PA9 PA10ʵ��  ���ڻ᲻ͣ���Զ����ͳ����� ���������� 
//�����յ����ڴ��������� ����1�����ж� �������յ���������ʾ������������

//STM32C8ϵ�� ����û�д���оƬ  ���������ʵ�� Ҫ�õ�����ģ��
  



#include  "delay.h"
#include  "led.h"
#include  "usart.h"


int main(void)
   {
 	u8 t;
	u8 len;	
	u16 times=0;
   	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
   
 	while(1)
	{
		if(USART_RX_STA&0x8000)	   //�ж��Ƿ����������
		{					   
			len=USART_RX_STA&0x3f;//�õ��˴ν��յ������ݳ���   ǰ��λΪ״̬λ ����Ҫ��ȥ
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)								  //ͨ�����Ƚ���ѭ��
			{
				USART_SendData(USART1, USART_RX_BUF[t]);      //������ɼ��õ����� һ���򴮿�1����
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;			  //���� ����Ĵ���		  Ϊһ�´βɼ���׼��
		}else
		{
			times++;
			if(times%2000==0)
			{
				printf("\r\n������� STM32�ϵ�a ����ʵ��\r\n\r\n");
			}
			if(times%200==0)
			{
			printf("����������,�Իس�������\n"); 
			GPIO_SetBits(GPIOA,GPIO_Pin_1); 					//��PA1��1			   LED2
			}
			if(times%400==0)
			{
			  GPIO_ResetBits(GPIOA,GPIO_Pin_1);				    //��PA1��0
			}	
			delay_ms(6);   
		}
	}

   }

