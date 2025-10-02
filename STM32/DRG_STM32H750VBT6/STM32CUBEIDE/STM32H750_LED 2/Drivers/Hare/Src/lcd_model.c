/***
	************************************************************************************************
	*	@file					lcd_model.c
	*	@version			V1.0
	*	@date					2023-11-28
	*	@author				Makerbase	
	*	@brief				LCD����ʾ���ܺ���
  ************************************************************************************************
  * @description
	*
	*	ʵ��ƽ̨��DRG ST-5 STM32H750VBT6 + 1.69��Һ��ģ�飨�ͺţ�SPI169M1-240*280��
	* @contact:  ΢�Ź��ں� - [GenBotter]������������
  *            QQȺ�� - [366182133]�����߼���֧��
  *            �Ա����� - [https://genbotter.taobao.com]���ṩ����Ӳ����Ʒ
	************************************************************************************************
***/	
#include "lcd_model.h"
#include "lcd_image.h"



/*************************************************************************************************
*	�� �� ��:	LCD_Test_Clear
*
*	��������:	��������
*************************************************************************************************/
void LCD_Test_Clear1(void)
{
	uint8_t	i = 0;			// ��������
	
	LCD_SetDirection(Direction_V);		
	LCD_SetTextFont(&CH_Font24);			// ����2424��������,ASCII�����ӦΪ2412
	LCD_SetColor(LCD_BLACK);				// ���û�����ɫ

	for(i=0;i<8;i++)
	{
		switch (i)		// �л�����ɫ
		{
			case 0: LCD_SetBackColor(LIGHT_RED); 		break;	
			case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;				
			case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
			case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
			case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
			case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
			case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
			case 7: LCD_SetBackColor(LCD_WHITE); 		break;			
			default:	break;			
		}
		LCD_Clear();		// ����
		LCD_DisplayText(13, 70,"STM32H7 ˢ������");
		LCD_DisplayText(13,106,"��Ļ�ֱ���:240*280");
		LCD_DisplayText(13,142,"������:ST7789");	
		HAL_Delay(1000);	// ��ʱ
	}
}

/*****************************************************************************************
*	�� �� ��: LCD_Test
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: �ı���ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Test(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ 	
	
	LCD_SetAsciiFont(&ASCII_Font12);		
	LCD_DisplayString(20,25,"Makerbase");
	HAL_Delay(200);
	
	LCD_SetAsciiFont(&ASCII_Font16);			
	LCD_DisplayString(20,42,"Makerbase");
	HAL_Delay(200);
	
	LCD_SetAsciiFont(&ASCII_Font20);			
	LCD_DisplayString(20,65,"Makerbase");
	HAL_Delay(200);
	
	LCD_SetAsciiFont(&ASCII_Font24);		
	LCD_DisplayString(20,95,"Makerbase");
	HAL_Delay(200);
	
	LCD_SetAsciiFont(&ASCII_Font32);			
	LCD_DisplayString(20,130,"Makerbase");
	HAL_Delay(200);
	
	LCD_SetTextFont(&CH_Font32);			
	LCD_DisplayText(20,180,"����");
	LCD_DisplayText(20,225,"����");
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_Line
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ������ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Line(void)
{
	int i;
	LCD_Clear();										// ����
	LCD_SetColor(LIGHT_BLUE);				// ���û�����ɫ
	
	for(i=0;i<=48;i++)
	{
		LCD_DrawLine(12,14,i*5,280);
		HAL_Delay(10);
	}
	
	LCD_SetColor(LIGHT_GREEN);	
	for(i=0;i<=48;i++)
	{
		LCD_DrawLine(228,14,240-i*5,280);
		HAL_Delay(10);
	}
	
	LCD_SetColor(LIGHT_RED);	
	for(i=0;i<=48;i++)
	{
		LCD_DrawLine(120,139,240-i*5,280);
		HAL_Delay(10);
	}
	
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_Rectangle
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ���ζ�̬��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Rectangle(void)
{
	int i;
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	for(i=2;i<20;i++)
	{
		LCD_DrawRect(i*6,i*7,240-12*i,280-14*i);
		HAL_Delay(30);
	}
	HAL_Delay(200);
	
	for(i=19;i>=2;i--)
	{
		LCD_FillRect(i*6,i*7,240-12*i,280-14*i);
		HAL_Delay(30);
	}
	HAL_Delay(200);
	
	LCD_SetColor(LCD_BLACK);
	for(i=2;i<20;i++)
	{
		LCD_DrawRect(i*6,i*7,240-12*i,280-14*i);
		LCD_DrawRect(i*6+1,i*7+1,240-12*i-2,280-14*i-2);
		LCD_DrawRect(i*6+2,i*7+2,240-12*i-4,280-14*i-4);
		LCD_DrawRect(i*6+3,i*7+3,240-12*i-6,280-14*i-6);
		LCD_DrawRect(i*6+4,i*7+4,240-12*i-8,280-14*i-8);
		LCD_DrawRect(i*6+4,i*7+5,240-12*i-8,280-14*i-10);
		HAL_Delay(30);
	}
	HAL_Delay(200);
	
	LCD_SetColor(LCD_BLACK);
	for(i=19;i>=2;i--)
	{
		LCD_FillRect(i*6,i*7,240-12*i,280-14*i);
		HAL_Delay(30);
	}
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_RouRectangle
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: Բ�Ǿ��ζ�̬��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_RouRectangle(void)
{
	int i;
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	for(i=2;i<19;i++)
	{
		DrawRoundRect(i*6,i*7,240-12*i,280-14*i,12);
		HAL_Delay(30);
	}
	HAL_Delay(200);
	
	for(i=18;i>=2;i--)
	{
		DrawfillRoundRect(i*6,i*7,240-12*i,280-14*i,12);
		HAL_Delay(30);
	}
	HAL_Delay(500);
}
/*****************************************************************************************
*	�� �� ��: LCD_Ellipse
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��Բ��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Ellipse(void)
{
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	LCD_DrawEllipse(120,140,60,90);
	HAL_Delay(200);
	DrawFillEllipse(120,140,60,90);
	HAL_Delay(200);
	
	LCD_Clear();
	LCD_SetColor(LIGHT_YELLOW);
	
	LCD_DrawEllipse(120,140,80,50);
	HAL_Delay(200);
	DrawFillEllipse(120,140,80,50);
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_Circle
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: Բ��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Circle(void)
{
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	LCD_DrawCircle(120,140,100);
	HAL_Delay(200);
	LCD_FillCircle(120,140,100);
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_Triangle
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��������ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Triangle(void)
{
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	DrawTriangle(12,14,228,14,228,255);
	HAL_Delay(200);
	DrawFillTriangle(12,14,228,14,228,255);
	HAL_Delay(200);
	
	LCD_SetColor(LIGHT_YELLOW);
	DrawTriangle(12,14,12,255,228,255);
	HAL_Delay(200);
	DrawFillTriangle(12,14,12,255,228,255);
	HAL_Delay(500);
}

/*****************************************************************************************
*	�� �� ��: LCD_Picture
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ͼƬ��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/

void LCD_Picture(void)
{
	LCD_Clear();
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	LCD_DrawImage( 0, 20, 239, 239, Image_2_239x239);
	HAL_Delay(1000);
	LCD_DrawImage( 0, 20, 239, 239, Image_1_239x239);
	HAL_Delay(1000);
}


/*****************************************************************************************
*	�� �� ��: LCD_Arc
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: Բ����̬��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Arc(void)
{
	int i;
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	//����
	for(i=0;i<360;i++)
	{
		TypeXY temp;
		SetAngle(i);
		SetRotateCenter(120,140);
		temp=GetRotateXY(120,140+90);
		LCD_DrawPoint(temp.x,temp.y,LCD_GREEN);
		HAL_Delay(5);
	}
	LCD_DrawCircle(120,140,90);
	HAL_Delay(200);
	
	//����Բ�Ŵ�
	for(i=1;i<30;i++)
	{
		LCD_FillCircle(120,140,i);
		HAL_Delay(30);
	}
	HAL_Delay(200);
	
	//�Ƶ�
	for(i=0;i<360;i++)
	{
		TypeXY temp;
		SetAngle(i);
		SetRotateCenter(120,140);
		temp=GetRotateXY(120,230);
		LCD_SetColor(LCD_GREEN);
		LCD_FillCircle(temp.x,temp.y,10);
		HAL_Delay(50);
		LCD_SetColor(LCD_BLACK);
		LCD_FillCircle(temp.x,temp.y,10);
	}
	HAL_Delay(500);
}


/*****************************************************************************************
*	�� �� ��: LCD_Polygon
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ����λ滭��ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Polygon(void)
{
	int x0=120,y0=140;
	unsigned char i =0,j;
	int n=1,r=80,v=1,count=0;
	int x[30],y[30];
	
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	while(1)
	{
		LCD_Clear();
		for(i=0;i<n;i++)
		{
			x[i]=r*cos(2*3.1415926*i/n)+x0;
			y[i]=r*sin(2*3.1415926*i/n)+y0;
		}
		for(i=0;i<=n-2;i++)
		{
			for(j=i+1;j<=n-1;j++)
			{
				LCD_DrawLine(x[i],y[i],x[j],y[j]);
				HAL_Delay(2);
			}
		}
		n+=v;
		if(n==15||n==0)
			v=-v;
		HAL_Delay(50);
		if(++count==30)
		{
			count=0;
			return ;
		}
		HAL_Delay(50);
	}
}
	

/*****************************************************************************************
*	�� �� ��: LCD_Clock
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ʱ����ʾ���ܺ���
*	˵    ��: ��
******************************************************************************************/
void LCD_Clock(void)
{
	int i,j,z;
	
	LCD_Clear(); 											// ����
	LCD_SetColor(LIGHT_GREEN);				// ���û�����ɫ
	
	LCD_DrawCircle(120,140,90);
	for(i=0;i<1;i++)
	{
		Clock_Needle(i,40);
		for(j=0;j<3;j++)
		{
			if(j == i)
			{
				Clock_Needle(i,40);
			}
			for(z=0;z<60;z++)
			{
					Clock_Sec(z,80);
					if(z ==j )
					{
						Clock_Needle(j,60);
						Clock_Needle(i,40);
					}
					if(z == i)
					{
						Clock_Needle(i,40);
					}
			}
		}
	}
}


//ʱ�ӡ������ƶ��켣
void Clock_Needle(int t,int l)
{
	TypeXY secpoint;
	LCD_SetColor(LCD_BLACK);
	
	if(t!=0)
	{
		SetRotateValue(120,140,(t-1)*6,1);
		secpoint=GetRotateXY(120-l,140);
		LCD_DrawLine(120,140,secpoint.x,secpoint.y);
	}
	else
	{
		SetRotateValue(120,140,0,1);
		secpoint=GetRotateXY(120-l,140);
		LCD_DrawLine(120,140,secpoint.x,secpoint.y);
		SetRotateValue(120,140,59*6,1);
		secpoint=GetRotateXY(120-l,140);
		LCD_DrawLine(120,140,secpoint.x,secpoint.y);
	}
	SetRotateValue(120,140,t*6,1);
	secpoint=GetRotateXY(120-l,140);
	LCD_SetColor(LCD_GREEN);
	LCD_DrawLine(120,140,secpoint.x,secpoint.y);
}

//�����ƶ��켣�ͱ���
void Clock_Sec(int t,int l)
{
	
	unsigned char i=0;
	TypeXY secpoint,tmp1,tmp2;
	
	SetRotateValue(120,140,t*6,1);
	secpoint=GetRotateXY(120-l,140);
	LCD_SetColor(LCD_GREEN);
	LCD_DrawLine(120,140,secpoint.x,secpoint.y);
	HAL_Delay(50);
	LCD_SetColor(LCD_BLACK);
	LCD_DrawLine(120,140,secpoint.x,secpoint.y);
	
	//����
	LCD_SetColor(LCD_GREEN);
	for(i=0;i<12;i++)
	{
		SetRotateValue(120,140,i*30,1);
		tmp1=GetRotateXY(120-90,140);
		tmp2=GetRotateXY(120-80,140);
		LCD_DrawLine(tmp1.x,tmp1.y,tmp2.x,tmp2.y);
	}
}

