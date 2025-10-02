/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "stm32h7xx_hal.h"
#include "usart.h"

#include "lcd_fonts.h"	// ͼƬ���ֿ��ļ����Ǳ��룬�û�������ɾ��
#include	"lcd_image.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */


/*----------------------------------------------- ������ -------------------------------------------*/
#define LCD_Width     240		// LCD�����س���
#define LCD_Height    280		// LCD�����ؿ���

#define RADIAN(angle)  ((angle==0)?0:(3.14159*angle/180))   //�Ƕ�ת��
#define MAX(x,y)  		((x)>(y)? (x):(y))
#define MIN(x,y)  		((x)<(y)? (x):(y))
#define SWAP(x, y) \
	(y) = (x) + (y); \
	(x) = (y) - (x); \
	(y) = (y) - (x);
#define ABS(X)  ((X) > 0 ? (X) : -(X))   //����������ֵ�ľ���ֵ

//��ά����ṹ�壬���������� x �������� y
typedef struct COORDINATE
{
    int x;  // ������
    int y;  // ������
} TypeXY;

#define point TypeXY

//��ת�ṹ�壬������ת���� center����ת�Ƕ� angle ����ת���� direct
typedef struct ROATE
{
    TypeXY center;   // ��ת��������
    float angle;     // ��ת�Ƕ�
    int direct;      // ��ת����
} TypeRoate;

// ��ʾ�������
// ʹ��ʾ����LCD_DisplayDirection(Direction_H) ������Ļ������ʾ
#define	Direction_H				0					//LCD������ʾ
#define	Direction_H_Flip	   1					//LCD������ʾ,���·�ת
#define	Direction_V				2					//LCD������ʾ
#define	Direction_V_Flip	   3					//LCD������ʾ,���·�ת

// ���ñ�����ʾʱ����λ��0���ǲ��ո�
// ֻ�� LCD_DisplayNumber() ��ʾ���� �� LCD_DisplayDecimals()��ʾС�� �����������õ�
// ʹ��ʾ���� LCD_ShowNumMode(Fill_Zero) ���ö���λ���0������ 123 ������ʾΪ 000123
#define  Fill_Zero  0		//���0
#define  Fill_Space 1		//���ո�


/*---------------------------------------- ������ɫ ------------------------------------------------------

 1. ����Ϊ�˷����û�ʹ�ã��������24λ RGB888��ɫ��Ȼ����ͨ�������Զ�ת���� 16λ RGB565 ����ɫ
 2. 24λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ R��G��B  3����ɫͨ��
 3. �û������ڵ����õ�ɫ���ȡ24λRGB��ɫ���ٽ���ɫ����LCD_SetColor()��LCD_SetBackColor()�Ϳ�����ʾ����Ӧ����ɫ
 */
#define 	LCD_WHITE       0xFFFFFF	 // ����ɫ
#define 	LCD_BLACK       0x000000    // ����ɫ

#define 	LCD_BLUE        0x0000FF	 //	����ɫ
#define 	LCD_GREEN       0x00FF00    //	����ɫ
#define 	LCD_RED         0xFF0000    //	����ɫ
#define 	LCD_CYAN        0x00FFFF    //	����ɫ
#define 	LCD_MAGENTA     0xFF00FF    //	�Ϻ�ɫ
#define 	LCD_YELLOW      0xFFFF00    //	��ɫ
#define 	LCD_GREY        0x2C2C2C    //	��ɫ

#define 	LIGHT_BLUE      0x8080FF    //	����ɫ
#define 	LIGHT_GREEN     0x80FF80    //	����ɫ
#define 	LIGHT_RED       0xFF8080    //	����ɫ
#define 	LIGHT_CYAN      0x80FFFF    //	������ɫ
#define 	LIGHT_MAGENTA   0xFF80FF    //	���Ϻ�ɫ
#define 	LIGHT_YELLOW    0xFFFF80    //	����ɫ
#define 	LIGHT_GREY      0xA3A3A3    //	����ɫ

#define 	DARK_BLUE       0x000080    //	����ɫ
#define 	DARK_GREEN      0x008000    //	����ɫ
#define 	DARK_RED        0x800000    //	����ɫ
#define 	DARK_CYAN       0x008080    //	������ɫ
#define 	DARK_MAGENTA    0x800080    //	���Ϻ�ɫ
#define 	DARK_YELLOW     0x808000    //	����ɫ
#define 	DARK_GREY       0x404040    //	����ɫ

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


void  MX_SPI4_Init(void);
void  SPI_LCD_Init(void);      // Һ�����Լ�SPI��ʼ��
void  LCD_Clear(void);			 // ��������
void  LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// �ֲ���������

void  LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);	// ��������
void  LCD_SetColor(uint32_t Color); 				   //	���û�����ɫ
void  LCD_SetBackColor(uint32_t Color);  				//	���ñ�����ɫ
void  LCD_SetDirection(uint8_t direction);  	      //	������ʾ����

//>>>>>	��ʾASCII�ַ�
void  LCD_SetAsciiFont(pFONT *fonts);										//	����ASCII����
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	��ʾ����ASCII�ַ�
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	��ʾASCII�ַ���

//>>>>>	��ʾ�����ַ�������ASCII��
void 	LCD_SetTextFont(pFONT *fonts);										// �����ı����壬�������ĺ�ASCII����
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// ��ʾ��������
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// ��ʾ�ַ������������ĺ�ASCII�ַ�

//>>>>>	��ʾ������С��
void  LCD_ShowNumMode(uint8_t mode);		// ���ñ�����ʾģʽ������λ���ո������0
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// ��ʾ����
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// ��ʾС��

//>>>>>	2Dͼ�κ���
void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   	//����

void  LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // ����ֱ��
void  LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // ��ˮƽ��
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	// ����֮�仭��

void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//������
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									//��Բ
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											//����Բ

//>>>>>	������亯��
void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//������
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									//���Բ

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pImage); // ��ͼ��
void DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // ��Բ�Ǿ��α߿�
void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r); // ���Բ�Ǿ���
void DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername); // ��Բ�Ǹ�������
void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta); // ���Բ�Ǹ�������
void DrawFillEllipse(int x0, int y0, int rx, int ry);         // �����Բ

void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2); // ��������
void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2); // ���������
void DrawArc(int x, int y, unsigned char r, int angle_start, int angle_end); // ��Բ��
TypeXY GetXY(void);   // ��ȡ��ǰ����
void SetRotateCenter(int x0, int y0);  // ������ת����
void SetAngleDir(int direction);       // ������ת����
void SetAngle(float angle);             // ������ת�Ƕ�

float mySqrt(float x);  // ����ƽ����
TypeXY GetRotateXY(int x, int y);  // ��ȡ��ת�������
void MoveTo(int x, int y);  // �ƶ���ָ������
void LineTo(int x, int y);  // ���ߵ�ָ������
void SetRotateValue(int x, int y, float angle, int direct); // ������תֵ

//>>>>>	���Ƶ�ɫͼƬ
void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)  ;

//>>>>>	�������ƺ�����ֱ�ӽ����ݸ��Ƶ���Ļ���Դ�
void	LCD_CopyBuffer(uint16_t x, uint16_t y,uint16_t width,uint16_t height,uint16_t *DataBuff);

 /*--------------------------------------------- LCD�������� -----------------------------------------------*/

#define  LCD_Backlight_PIN								GPIO_PIN_15				         // ����  ����
#define	LCD_Backlight_PORT							GPIOD									// ���� GPIO�˿�
#define 	GPIO_LDC_Backlight_CLK_ENABLE        	__HAL_RCC_GPIOD_CLK_ENABLE()	// ���� GPIOʱ��

#define	LCD_Backlight_OFF		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);	// �͵�ƽ���رձ���
#define 	LCD_Backlight_ON		HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);		// �ߵ�ƽ����������

#define  LCD_DC_PIN						GPIO_PIN_15				         // ����ָ��ѡ��  ����
#define	LCD_DC_PORT						GPIOE									// ����ָ��ѡ��  GPIO�˿�
#define 	GPIO_LDC_DC_CLK_ENABLE     __HAL_RCC_GPIOE_CLK_ENABLE()	// ����ָ��ѡ��  GPIOʱ��

#define	LCD_DC_Command		   HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	   // �͵�ƽ��ָ���
#define 	LCD_DC_Data		      HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);		// �ߵ�ƽ�����ݴ���

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

