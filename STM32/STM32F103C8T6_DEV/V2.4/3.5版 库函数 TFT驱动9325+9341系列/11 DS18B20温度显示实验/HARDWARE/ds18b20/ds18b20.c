

#include "ds18b20.h"
#include "gui.h"



//����DS18B20��IO    �����DS�Ƿ����
//����1:������
//����0:����    
//ע�� ds18b20���õ�io ΪPA13  ��PA13λ SWD�ӿ� �����ð��ϵ�DS18B20�ӿ� �ͻ�Ӱ��SWD�ķ��湦��	 
u8 ds18b20_init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PORTG��ʱ�� 
		
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//PORTG.11 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//����Ϊ�������  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_13);    //����IO

	ow_reset();							//��λ����

	return ds18B20_check();
} 




//DS18B20��λ����
void ow_reset(void)
{
	DS18B20_IO_OUT();
    DQ_OUT=0;				   //����
    delay_us(750);             //	  �͵�ƽ��λ�ź�
    DQ_OUT=1;
    delay_us(16);              //>15us ��������	 15-60us�ߵ�ƽ��  ��60-240us ��Ӧ���ź�
}



//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 ds18B20_check(void) 	   
{   
	u8 retry=0;	 		//���������
	DS18B20_IO_IN();    //����IOΪ����ģʽ
    while (DQ_IN&&retry<50)
	{
		retry++;
		delay_us(4);		//���4us
	};
	if(retry>=50)return 1;
	else retry=0;	 
    while (!DQ_IN&&retry<60)		 //����240us����ʱ ��������ĸ�λ����
	{
		retry++;
		delay_us(4);		//���4us
	};

	if(retry>=60)return 1;	    //û�нӵ�DS18B20Ӧ��
	return 0;					//�ӵ�Ӧ��
}



//DS18B20д�����
//��1-WIRE ������д1���ֽ�
//u8 val Ҫд���ֽ�
//DS18B20�ֲ���������ʱ��ͼ
void write_byte(u8 val)
{
 u8 i,testb;
 DS18B20_IO_OUT();    //����IOΪ���ģʽ
 for(i=8;i>0;i--)
 { 
   testb=val&0x01;            //���λ�Ƴ�
   val=val>>1;
   if(testb)				  //д1
   {
   	 DQ_OUT=0;
	 delay_us(4);			  //4us
	 DQ_OUT=1;
	 delay_us(60);			  //60us
   }
   else						  //д0
   {
     DQ_OUT=0;
	 delay_us(60);			  //60us
	 DQ_OUT=1;
	 delay_us(4);			  //4us
   }
 }
}

//DS18B20��1�ֽں���
//��������ȡ1���ֽ�
//����ֵΪ��ȡ�ֽ�ֵ
//˵��  һ��1bit�Ķ�ȡ������Ҫ60us	  ���ζ�ȡ֮����Ҫ����1us�Ļָ�ʱ��
//    ���ζ�ȡ1bit  �������Ͳ��ܳ���15us Ȼ����������
u8 read_byte(void)
{
 u8 i;
 u8 value=0;
 
 for(i=8;i>0;i--)
 {
  DS18B20_IO_OUT();    //����IOΪ���ģʽ
  DQ_OUT=1;
  value>>=1;           //value=value>>1
  DQ_OUT=0;                                  
  delay_us(8);							 //����4us 
  DQ_OUT=1;                              //����
  DS18B20_IO_IN();     //����IOΪ����ģʽ
  delay_us(12);							 //����10us	 ׼���������ߵ�ǰ����
  if(DQ_IN)value|=0x80;				 //����ǰ����ֵ������ʱ����
  delay_us(50);                          //50 us��ʱ  ���һ�ζ�ȡ����ʱ��һ�ζ�ȡ����60us������1us�Ļָ�ʱ��
 }
 return(value);
}



//�����¶Ⱥ���
//����Ϊ�¶�ֵ  �¶�ֵΪshort���� ������
short read_temp(void)	  //short���Ա�ʾ-32768~+32767
{
  u8 TL,TH;
  u8 temp;
  short t;
  ow_reset();                  //���߸�λ
  ds18B20_check();			   //�ȴ�DSӦ��
  write_byte(0xcc);            //������
  write_byte(0x44);            //��ת������
  ow_reset();				   //��λ
  ds18B20_check();			   //�ȴ�DSӦ��
  write_byte(0xcc);            //������
  write_byte(0xbe);			   //���Ͷ��¶�����
  TL=read_byte();    //���¶�ֵ�ĵ��ֽ�
  TH=read_byte();    //���¶�ֵ�ĸ��ֽ�
  

  if(TH>7)
  {
    TH=~TH;
    TL=~TL; 
    temp=0;//�¶�Ϊ��   
  }else temp=1;

  t=TH;
  t<<=8;             
  t+=TL;             // ���ֽںϳ�һ�����ͱ�����

  if(temp==0)t+=1;	 //����Ǹ�����Ҫ��1  ����ת������ȡ�����1

  t=(float)t*0.625;  //0.0625Ϊ12λ�¶Ȳɼ��ķֱ���	   tΪ�ɼ�����ֵ  ��������10����ȡС�����һλ
  if(temp)return t;
  else return -t;
  }














