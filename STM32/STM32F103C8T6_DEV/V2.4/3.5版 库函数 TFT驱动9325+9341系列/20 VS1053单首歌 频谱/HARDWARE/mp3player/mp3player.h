
#ifndef   MP3PLAYER_H
#define   MP3PLAYER_H

#include "stm32f10x.h"
#define Int_vol		200	 //音量初值

//频谱数据
#define FFT_BANDS   14   //14个频段

#define fft_col_width   5  //音柱宽度
#define fft_col_high    64 //音柱高度
#define fft_col_away    8  //音柱之间的距离
#define fft_col_x		32 //fft初始坐标x
#define fft_col_y       60//fft初始坐标y
#define fft_bcolor      window //频谱背景颜色
#define fft_ycolor		Red   //音柱颜色
#define fft_fcolor		Black //峰值颜色

//fft变量管理
typedef struct
{
   u8 fft_top[FFT_BANDS];	 //频谱顶值表
   u8 fft_cur[FFT_BANDS];	 //频谱当前值表
   u8 fft_time[FFT_BANDS];	 //顶值停留时间表
} _f_fftdev;


u8 Mp3Player_Init(void);

void SetBands(void);
void Show_fft(void);
void play_mp3(void);

void mp3_button(u8 class,u8 status);  //MP3功能按键函数

#endif


