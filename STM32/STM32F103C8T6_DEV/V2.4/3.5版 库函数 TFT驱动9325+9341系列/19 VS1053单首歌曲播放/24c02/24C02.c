																																			   
 /*************************�˲���ΪAT2402����������ʹ��I2C��������*************************************/

#include  "delay.h"
#include  "gui.h"
#include  "i2c.h"
#include  "z24C02.h"
#include "stm32f10x.h"


//24c Ĭ�ϵ�Ӳ����ַ���� 0xa0  �� 1010   Ȼ��A2 A1 A0  ���һλ Ϊ��дλ  1�� 0д
//24c02  256x8 bit    
//24c04  512x8 bit
//���ӵ�ַ ֻ��8λ�� �����Ҳ��256���ֽ�  ��ô24c04 ��Ҫռ��2��256���ֽ� 
//����24c04Ӳ���ϲ��õ��� ��ҳ����  ����24c02����A0 A1 A2 ����24c04ʱ A0��Ϊ��ҳλ
//��A0Ϊ0 ��ʾ��һҳ д���һҳ256�ֽ�
//��A0Ϊ1 ��ʾ�ڶ�ҳ д��ڶ�ҳ256�ֽ�


//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	IIC_Init();
}

//��AT24CXXָ����ַ����һ������
//Addr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24C_Rcvone(u8 Addr)
{
   u8 temp=0;
   Start_I2c();                //��������
   SendByte(0xa0);             //����д����
   I2c_wait_ack();			   //�ȴ�Ӧ��
   SendByte(Addr);             //���͵�ַ
   I2c_wait_ack();			   //�ȴ�Ӧ��

   Start_I2c();                //������������
   SendByte(0xa1);		       //����Ϊ������
   I2c_wait_ack();			   //�ȴ�Ӧ��;

   temp=RcvByte(0);			   //���ֽ�	��Ӧ��

   Stop_I2c();                 //�������� 
   return temp;
}



//��AT24CXXָ����ַд��һ������	 �˺���ֻ���� c02-c16
//Addr:д�����ݵ�Ŀ�ĵ�ַ    
//Data:Ҫд�������
void AT24C_Sendone(u8 Addr,u8 Data)
{
   Start_I2c();               //��������

   SendByte(0xa0);            //����д����
   I2c_wait_ack();			  //�ȴ�Ӧ��
   SendByte(Addr);            //���͵�ַ
   I2c_wait_ack();			  //�ȴ�Ӧ��
   SendByte(Data);			  //�����ֽ�����
   I2c_wait_ack();			  //�ȴ�Ӧ��
   Stop_I2c();                //�������� 
   delay_ms(10);			  //��������������ֽڵ�ʱ�������ʱ����Ҫ ���򽫻ش���
}


//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//Addr  :��ʼд��ĵ�ַ  
//Data  :���������׵�ַ
//Len   :Ҫд�����ݵĳ���2,4
void AT24C_SendLenByte(u8 Addr,u8 *Data,u8 Len)
{  	
	while(Len--)
	{
		AT24C_Sendone(Addr,*Data);
		Addr++;
		Data++;
	}												    
}



//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//Addr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
void AT24C_RcvLenByte(u8 Addr,u8 *temp,u8 Len)
{  	

   while(Len)
   {
	 *temp++=AT24C_Rcvone(Addr++);
	 Len--;				   
	}
												    
}




////24c04 ��д����
////����  ��3.3 ��ĸ����+1  ��1.2���浱ǰ��ʾ������  ��5.0 ��ʾ24c�ﱣ�������
//void c02()
//{	 
//  struct TFT_Pointer Tp_pix;	   //���崥�������ṹ��
//
//  u8 Count1=65,Count2=65,   //��ĸ��ʼֵΪ��д��ĸA
//     pd; 				    //���� ��ȡ����
//
//  GUI_Clear(White);	       //����
//  tian(1);                 //���¿����
//																	
//	GUI_sprintf_hzstr16x(0,0,"24C02оƬ���ֽڴ������",White,1);    //��ʾ˵��
//	GUI_sprintf_hzstr16x(0,84 ,"��ȡֵ:   <<��ȡʱLED��",Blue,White);
//	GUI_sprintf_hzstr16x(0,100,"����ֵ:   <<����ʱLED��",Blue,White);
//
//	GUI_box(0,180,239,183,Blue1);
//	GUI_sprintf_hzstr16x(0,184,"����˵����",Red,White);
//	GUI_sprintf_hzstr16x(0,200,"����:P33",Black,White);
//	GUI_sprintf_hzstr16x(0,217,"��ȡ:P14",Black,White);
//    GUI_sprintf_hzstr16x(0,234,"��һ:���ⴥ��",Black,White);
//
// while(1)
//  {
//    Tp_pix=TFT_Cm();	                 // ɨ�败����
//
//    if(Tp_pix.flag==1)                   //�Ƿ��д����¼� ���� 
//    {      	
//	        
//      if(Tp_pix.y>=0&&Tp_pix.y<=299) 	 //ֻҪ��0-299������������λ���а��� ������Ӧ
//	  {
//		Count1++; 				         //Ԥ�洢ֵ����
//		delay1ms(100);	  				 //���ͱ仯�ٶ�
//	  }
//				   
// 	  if(Tp_pix.x>200&&Tp_pix.x<239&&Tp_pix.y>295&&Tp_pix.y<320){Return(); led=1; break;}	 //�������˵�
//  	}
//
//	  //=========================��ȡ
//    if(P14==0)	        //����������   ��ȡE2 0��ַλ ��һ���ֽ� ��pd��
//	 { 
//		led=1;	 		//ָʾ�� �� ��ʾ ��ȡ�ɹ�
//        pd=AT24C_Rcvone(0);    //ѡ��Ҫ��ȡ�ĵ�ַ  Ȼ�󽫶�ȡ�����ݴ������pd�� 1����1���ֽڵ������ָ������                                                                            
//		Count1=pd ;		//����ȡֵ������ʱ������
//		Count2=pd ;
//	 }
//
//	  //========================IIC ����
//	if(key33==0)    //���Ӳఴ�� С��
//     { 		
//		led=0;			//ָʾ�� �� ��ʾ ����ɹ�
//		pd=Count1;		//��Ԥ�洢Count1�е�ֵ������pd
//		AT24C_Sendone(0,pd);	//��pd��ֵ����  0��ַλ�� ������Ϊ1�ֽ�
//     }
//	//������ʾ
//    GUI_sprintf_char(60,84,Count1,0xf800,0xffff,0); //��ʾ��ȡ������ֵ																	   
//    GUI_sprintf_char(60,100,Count2,0xf800,0xffff,0);//��ʾ�����ȥ��ֵ
//
//  }
//}
//
//




