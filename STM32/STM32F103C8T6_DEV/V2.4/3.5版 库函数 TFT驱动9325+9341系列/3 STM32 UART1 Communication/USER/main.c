

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

//STM32串口1 PA9 PA10实验  串口会不停的自动发送出数据 到串口助手 
//当接收到串口传来的数据 串口1进入中断 并将接收到的数据显示到串口助手上

//STM32C8系列 板上没有串口芯片  如果想做此实验 要用到串口模块
  



#include  "delay.h"
#include  "led.h"
#include  "usart.h"


int main(void)
   {
 	u8 t;
	u8 len;	
	u16 times=0;
   	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600  
	LED_Init();		  	//初始化与LED连接的硬件接口
   
 	while(1)
	{
		if(USART_RX_STA&0x8000)	   //判断是否接收完数据
		{					   
			len=USART_RX_STA&0x3f;//得到此次接收到的数据长度   前两位为状态位 所以要与去
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)								  //通过长度进行循环
			{
				USART_SendData(USART1, USART_RX_BUF[t]);      //将数组采集好的数据 一次向串口1发送
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;			  //清零 虚拟寄存器		  为一下次采集做准备
		}else
		{
			times++;
			if(times%2000==0)
			{
				printf("\r\n启光电子 STM32紫电a 串口实验\r\n\r\n");
			}
			if(times%200==0)
			{
			printf("请输入数据,以回车键结束\n"); 
			GPIO_SetBits(GPIOA,GPIO_Pin_1); 					//给PA1置1			   LED2
			}
			if(times%400==0)
			{
			  GPIO_ResetBits(GPIOA,GPIO_Pin_1);				    //给PA1置0
			}	
			delay_ms(6);   
		}
	}

   }

