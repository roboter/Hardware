

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

/*
ESP8266 AP+Station服务器模式测试


UART2 PA2 PA3  与网络模块ESP进行通信

UART1 PA9 PA10 进行数据跟踪



STM32C8系列 板上没有串口芯片  如果想做此实验 要用到串口模块




*/



  



#include  "delay.h"
#include  "led.h"
#include  "usart.h"

#include  "string.h"


extern  u8 RX_buffer[tbuf];
extern u8 RX_num;				 //接收计数变量


 u8  esp_at[]="AT\r\n";                  // 握手连接指令，返回"OK"
 u8  esp_cwmode[]="AT+CWMODE=3\r\n";     // 设置ESP8266的工作模式3 AP+Station，返回"OK"或者"no change"
 u8  esp_cifsr[]="AT+CIFSR\r\n";         // 本机IP地址查询指令
 u8  esp_cipsend[]="AT+CIPSEND=6\r\n";   // 设置发送数据长度
 u8  esp_test[]="sunny\r\n";   			//  数据内容
 u8  esp_cipserver[]="AT+CIPSERVER=1,5000\r\n";  //建立TCP服务器，开放端口5000							
 u8  esp_cipmux[]="AT+CIPMUX=1\r\n";   			//打开多连接	
 u8  esp_rst[]="AT+RST\r\n"; 					// 软件复位



//指定字符串与缓存数组数据进行数据比较
//*p 要比较的指定字符串指针数据
//返回：1 数据一致  0 数据不一致 
u8 Data_compare(u8 *p)
{ 
	if(strstr(RX_buffer,p)!=NULL)
	    return 1;
	else
		return 0;
}


int main(void)
   {	


   	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为9600  
	LED_Init();		  	//初始化与LED连接的硬件接口


	delay_ms(500);

	memset(RX_buffer, 0, tbuf);//清缓存数据
	RX_num=0;				   //接收计数变量清0


	//发送AT 进行握手
    while(1)
	{
	 Uart2SendStr(esp_at);	   //串口2对wifi模块发送握手指令 即AT
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR1,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,mcu connection success with ESP8266! \r\n");
	 memset(RX_buffer, 0, tbuf);//清缓存数据
	 RX_num=0;				   //接收计数变量清0


	//配置wifi工作模式为ap+sta模式
    while(1)
	{
	 Uart2SendStr(esp_cwmode);	   //串口2对wifi模块工作模式进行设置  
	 if(Data_compare("OK")||Data_compare("no change"))break;
	 else  Uart1SendStr("ERROR2,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	 Uart1SendStr("OK,set mode as AP+Station with ESP8266! \r\n");	 
	 memset(RX_buffer, 0, tbuf);//清缓存数据	
	 RX_num=0;				   //接收计数变量清0



	//配置wifi为多路可连接模式
    while(1)
	{
	 Uart2SendStr(esp_cipmux);	   //串口2对wifi模块 设置多连接 （多路连接模式）
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR3,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//清缓存数据
	RX_num=0;				   //接收计数变量清0




	//配置wifi为服务器模式 配置端口号为5000
    while(1)
	{
	 Uart2SendStr(esp_cipserver);	   //串口2设置wifi模块 为TCP服务器模式，并配置端口为5000 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR4,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	memset(RX_buffer, 0, tbuf);//清缓存数据
	RX_num=0;				   //接收计数变量清0



	//查询模块ip
    while(1)
	{
	 Uart2SendStr(esp_cifsr);	   //串口2查询wifi模块 当前ip地址 
	 if(Data_compare("OK"))break;
	 else  Uart1SendStr("ERROR5,some problems with ESP8266 \r\n");
	 delay_ms(600);
	}
	Uart1SendStr(RX_buffer);
	memset(RX_buffer, 0, tbuf);//清缓存数据
	RX_num=0;				   //接收计数变量清0


	while(1)
	{	
		if(Data_compare("LEDK"))               //点亮板上了的led
		{	
            led(1);	
			memset(RX_buffer, 0, tbuf);//清缓存数据
			RX_num=0;				   //接收计数变量�0
			Uart1SendStr("led is open！\r\n");							
		}
	    else if(Data_compare("LEDG")) 		   //关闭板上了的led
		{
            led(0);		
			memset(RX_buffer, 0, tbuf);//清缓存数据
			RX_num=0;				   //接收计数变量�0
			Uart1SendStr("led is close！\r\n");									
		}	
	}


   }

