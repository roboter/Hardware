
#ifndef   MP3PLAYER_H
#define   MP3PLAYER_H

#include "stm32f10x.h"
#define Int_vol		200	 //������ֵ

//Ƶ������
#define FFT_BANDS   14   //14��Ƶ��

#define fft_col_width   5  //�������
#define fft_col_high    64 //�����߶�
#define fft_col_away    8  //����֮��ľ���
#define fft_col_x		32 //fft��ʼ����x
#define fft_col_y       60//fft��ʼ����y
#define fft_bcolor      window //Ƶ�ױ�����ɫ
#define fft_ycolor		Red   //������ɫ
#define fft_fcolor		Black //��ֵ��ɫ

//fft��������
typedef struct
{
   u8 fft_top[FFT_BANDS];	 //Ƶ�׶�ֵ��
   u8 fft_cur[FFT_BANDS];	 //Ƶ�׵�ǰֵ��
   u8 fft_time[FFT_BANDS];	 //��ֵͣ��ʱ���
} _f_fftdev;


u8 Mp3Player_Init(void);

void SetBands(void);
void Show_fft(void);
void play_mp3(void);

void mp3_button(u8 class,u8 status);  //MP3���ܰ�������

#endif


