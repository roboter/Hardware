#include "main.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "pcd8544.h"
#include "fonts.h"

// Port B
#define RST  GPIO_Pin_4
#define BL   GPIO_Pin_5
#define DC   GPIO_Pin_6
// Port A
#define CS   GPIO_Pin_4
#define CLK  GPIO_Pin_5
#define DIN  GPIO_Pin_7

#define LCD_C     0x00
#define LCD_D     0x01

#define LCD_X     84
#define LCD_Y     48
#define LCD_LEN   (uint16_t)((LCD_X * LCD_Y) / 8)

#define chip_select_enable() gpio_reset(GPIOA,CS)
#define chip_select_disable() gpio_set(GPIOA,CS)

#define FONT_SIZE_1 (uint8_t)0x01
#define FONT_SIZE_2 (uint8_t)0x02
#define FONT_SIZE_3 (uint8_t)0x03

static const uint8_t lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

static uint8_t fb[LCD_LEN];          // screen buffer
uint16_t pos;

bool isPower=false;

void pcd8544_send(uint8_t dc, uint8_t data);

void pcd8544_init() {
    // hardware reset
    gpio_reset(GPIOB,RST);
    gpio_set(GPIOB,RST);
    // init routine
    chip_select_enable();
    pcd8544_send(LCD_C, 0x21);  // LCD Extended Commands.
    pcd8544_send(LCD_C, 0x14);  // LCD bias mode 1:48. //0x13
    pcd8544_send(LCD_C, 0xB6);  // Set LCD Vop (Contrast).
    pcd8544_send(LCD_C, 0x04);  // Set Temp coefficent. //0x04
    pcd8544_send(LCD_C, 0x20);  // LCD Basic Commands
    pcd8544_send(LCD_C, 0x0C);  // LCD in normal mode.
    //pcd8544_send(LCD_C, 0x0d);  // inverse mode
    chip_select_disable();
    gpio_reset(GPIOB,BL);           // enable blacklight
    isPower=true;
    pcd8544_fill_fb(0x0);
    pcd8544_display_fb();
}

void pcd8544_send(uint8_t dc, uint8_t data)
{

   if (dc == LCD_D)
      gpio_set(GPIOB,DC);
   else
      gpio_reset(GPIOB,DC);

#ifdef HW_SPI
   SPI1->DR=data;
   while (!(SPI1->SR & SPI_I2S_FLAG_TXE) || (SPI1->SR & SPI_I2S_FLAG_BSY));
#else

   for (uint8_t i=0; i<8; i++)
   {
      if (data & 0x80)
          gpio_set(GPIOA,DIN);
      else
          gpio_reset(GPIOA,DIN);

      data=(data<<1);
      // Set Clock Signal
      gpio_set(GPIOA,CLK);
      gpio_reset(GPIOA,CLK);
   }
#endif
}

//  work with buffer
void pcd8544_fill_fb(uint8_t value)
{
    for(int i=0;i<LCD_LEN; i++)
        fb[i]=value;
}

void pcd8544_display_fb() {
    chip_select_enable();
	// set curson at {0,0}
    pcd8544_send(LCD_C, 0x40);
    pcd8544_send(LCD_C, 0x80);

    for(uint16_t i=0;i<LCD_LEN; i++)
        pcd8544_send(LCD_D,fb[i]);
    chip_select_disable();
}


void pcd8544_fill(uint8_t value)
{
   chip_select_enable();
   for (int i=0; i < LCD_LEN; i++)
   {
      pcd8544_send(LCD_D, value);
   }
   chip_select_disable();
}

void pcd8544_off() {
    pcd8544_fill(0);
    // hardware reset
    gpio_reset(GPIOB,RST);
    delay_ms(10);
    gpio_set(GPIOB,RST);
    delay_ms(10);
    // blacklight off
    gpio_set(GPIOB,BL);
    isPower=false;
}


void pcd8544_mirror() {
    for (uint16_t i=0;i<LCD_LEN;i++) {
        uint8_t b=fb[i];
        fb[i]=(lookup[b&0b1111] << 4) | lookup[b>>4];
    }
    for (uint16_t i=0,j=(LCD_LEN-1);i<(LCD_LEN>>1);i++,j--) {
        uint8_t b=fb[i];
        fb[i]=fb[LCD_LEN-1-i];
        fb[j]=b;
    }
}

void pcd8544_print_string_invert_fb(char *str, uint8_t x, uint8_t y)
{
    pos=y*LCD_X + x;
    while (*str)
    {
        pcd8544_send_char(*str++,true);
    }
}

void pcd8544_print_string(char *str, uint8_t x, uint8_t y)
{
    pos=y*LCD_X + x;
    while (*str)
    {
      pcd8544_send_char(*str++,false);
    }
}

void pcd8544_send_char(uint8_t ch,bool inverse)
{
    if (ch >= 0x20 && ch <= 0xf0 && pos <= (LCD_LEN-7))
    {
        for (uint8_t i=0; i < 5; i++)
        {
            uint8_t c=(ch<0xe0) ? ch - 0x20 : ch - 0x50;
            c=ASCII_5x7[c][i];
            if (inverse)
                fb[pos+i]|=~c;
            else
                fb[pos+i]|=c;

        }
        if (inverse) {
            fb[pos+6]=0xff;
            fb[pos+5]=0xff;
        } else {
            fb[pos+6]=0x0;
            fb[pos+5]=0x0;
        }
        pos+=7;
    }
}

void pcd8544_send_char_size2_fb(uint8_t ch, uint8_t x, uint8_t y) {
    uint8_t s[5]; // source
    uint8_t r[20]; // result
    uint8_t i,j;
   // get littera
    if (ch >= 0x20 && ch <= 0xf0)
    {
        for (i=0; i < 5; i++)
        {
              uint8_t c=(ch<0xe0) ? ch - 0x20 : ch - 0x50;
              s[i]=ASCII_5x7[c][i];
        }
    }
    // scale
    for(i=0;i<5;i++)
    {
        uint8_t a=0;
        for(j=0;j<4;j++)
        {
            uint8_t b=(s[i]>>j) & 0x01;
            a|=(b<<(j<<1)) | (b<<((j<<1)+1));
        }
        r[(i<<1)]=a;
        r[(i<<1)+1]=a;
    }

    for(i=0;i<5;i++)
    {
        uint8_t a=0;
        for(j=0;j<4;j++)
        {
            uint8_t b=(s[i]>>(j+4)) & 0x01;
            a|=(b<<(j<<1)) | (b<<((j<<1)+1));
        }
        r[(i<<1)+10]=a;
        r[(i<<1)+11]=a;
    }
    // print
    pos=y*LCD_X+x;
    if (pos<(LCD_LEN-14))
    {
        fb[pos++]=0x00; fb[pos++]=0x00;
        for(i=0;i<10;i++)
            fb[pos++]=r[i];

        fb[pos++]=0x00; fb[pos++]=0x00;
    };

    pos=(y+1)*LCD_X+x;
    if(pos<(LCD_LEN-14))
    {
        fb[pos++]=0x00; fb[pos++]=0x00;
        for(i=10;i<20;i++)
            fb[pos++]=r[i];
        fb[pos++]=0x00; fb[pos++]=0x00;
    }
}

void pcd8544_send_char_size3_fb(uint8_t ch, uint8_t x, uint8_t y) {
    uint8_t s[5]; // source
    uint8_t r[45]; // result
    uint8_t i;
    // get littera
    if (ch >= 0x20 && ch <= 0xf0)
    {
        for (i=0; i < 5; i++)
        {
              uint8_t c=(ch<0xe0) ? ch - 0x20 : ch - 0x50;
              s[i]=ASCII_5x7[c][i];
        }
    }
    // scale
    for(i=0;i<5;i++)
    {
        uint8_t b,a;
        b=(s[i] & 0x01);
        a=(b) ? 0x7 : 0;
        b=(s[i]>>1) & 0x01;
        if (b) a|=0x38;
        b=(s[i]>>2) & 0x01;
        a|=(b<<6)|(b<<7);

        r[i*3]=a;
        r[i*3+1]=a;
        r[i*3+2]=a;

        r[i*3+15]=b;
        r[i*3+16]=b;
        r[i*3+17]=b;
    }

    for(i=0;i<5;i++)
    {
        uint8_t b,a;
        b=(s[i]>>3) & 0x01;
        a=(b) ? 0x0e : 0;
        b=(s[i]>>4) & 0x01;
        if (b) a|=0x70;
        b=(s[i]>>5) & 0x01;
        a|=(b<<7);

        r[i*3+15]|=a;
        r[i*3+16]|=a;
        r[i*3+17]|=a;
     }

    for(i=0;i<5;i++)
    {
        uint8_t b,a;
        b=(s[i]>>5) & 0x01;
        a=(b) ? 0x3 : 0;
        b=(s[i]>>6) & 0x01;
        if (b) a|=0x1c;
        b=(s[i]>>7) & 0x01;
        if (b) a|=0xe0;

        r[i*3+30]=a;
        r[i*3+31]=a;
        r[i*3+32]=a;
     }

    // print
    pos=y*LCD_X+x;
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;
    for(i=0;i<15;i++) fb[pos++]=r[i];
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;

    pos=(y+1)*LCD_X+x;
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;
    for(i=15;i<30;i++) fb[pos++]=r[i];
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;

    pos=(y+2)*LCD_X+x;
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;
    for(i=30;i<45;i++) fb[pos++]=r[i];
    fb[pos++]=0;fb[pos++]=0; fb[pos++]=0;
}

void pcd8544_print_uint8_at(uint8_t num, uint8_t size, uint8_t x, uint8_t y){
    uint8_t sym[3];
    int8_t i=2;
    do  {
      if (num == 0 && i<2)
        sym[i]=0x20; // space
      else
        sym[i]=0x30+num%10;

      num=num/10;
      i--;

    } while (i>=0);

    uint8_t j=0;
    for (i=0;i<3;i++)
    {
        if (!(i<2 && sym[i] == 0x20))
        {
            switch(size) {
            case 3:
                pcd8544_send_char_size3_fb(sym[i],x+j*6*size,y);
                break;
            case 2:
                pcd8544_send_char_size2_fb(sym[i],x+j*6*size,y);
                break;
            default:
                pcd8544_send_char(sym[i],false);
                break;
            }
            j++;
        }
    }
}
