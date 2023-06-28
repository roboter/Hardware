#include "main.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "st7735.h"
#include "uart.h"

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

static uint8_t fb[LCD_LEN];          // screen buffer

bool isPower=false;

void st7735_send(uint8_t dc, uint8_t data);


void st7789_init() {
    // hardware reset
    gpio_reset(GPIOC,RST);
    delay_ms(10);
    gpio_set(GPIOC,RST);
    delay_ms(100);
    // init routine
    gpio_set(GPIOB,DC);
#ifndef HW_SPI
    gpio_set(GPIOA,CLK);
#endif
    // init routine

    st7735_send(LCD_C,ST77XX_SWRESET);
    delay_ms(150);
    st7735_send(LCD_C,ST77XX_SLPOUT);
    delay_ms(10);

    st7735_send(LCD_C,ST77XX_COLMOD);
    st7735_send(LCD_D,0x55);            // 16-bit color mode
    delay_ms(10);

    st7735_send(LCD_C,ST77XX_MADCTL);
    st7735_send(LCD_D,0x08);

    st7735_send(LCD_C,ST77XX_CASET);
    st7735_send(LCD_D,0);
    st7735_send(LCD_D,0);
    st7735_send(LCD_D,0);
    st7735_send(LCD_D,0xf0);


    st7735_send(LCD_C,ST77XX_RASET);
    st7735_send(LCD_D,0);
    st7735_send(LCD_D,0);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x40);

    st7735_send(LCD_C,ST77XX_INVON);
    delay_ms(10);
    st7735_send(LCD_C,ST77XX_NORON);
    delay_ms(10);
    st7735_send(LCD_C,ST77XX_DISPON);
    delay_ms(10);

    isPower=true;
}

void st7735_init() {
    // hardware reset
    // hardware reset
    gpio_reset(GPIOB,RST);
    delay_ms(10);
    gpio_set(GPIOB,RST);
    delay_ms(10);
    gpio_set(GPIOB,DC);
#ifndef HW_SPI
    gpio_set(GPIOA,CLK);
#endif
    // init routine

    //chip_select_enable();
    st7735_send(LCD_C,ST77XX_SWRESET);
    delay_ms(150);
    st7735_send(LCD_C,ST77XX_SLPOUT);
    delay_ms(150);

    st7735_send(LCD_C,ST7735_FRMCTR1);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x2C);
    st7735_send(LCD_D,0x2D);

    st7735_send(LCD_C,ST7735_FRMCTR2);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x2C);
    st7735_send(LCD_D,0x2D);

    st7735_send(LCD_C,ST7735_FRMCTR3);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x2C);
    st7735_send(LCD_D,0x2D);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x2C);
    st7735_send(LCD_D,0x2D);


    st7735_send(LCD_C,ST7735_INVCTR);
    st7735_send(LCD_D,0x07);

    st7735_send(LCD_C,ST7735_PWCTR1);
    st7735_send(LCD_D,0xA2);
    st7735_send(LCD_D,0x02);
    st7735_send(LCD_D,0x84);

    st7735_send(LCD_C,ST7735_PWCTR2);
    st7735_send(LCD_D,0xC5);

    st7735_send(LCD_C,ST7735_PWCTR3);
    st7735_send(LCD_D,0x0A);
    st7735_send(LCD_D,0x00);

    st7735_send(LCD_C,ST7735_PWCTR4);
    st7735_send(LCD_D,0x8A);
    st7735_send(LCD_D,0x2A);

    st7735_send(LCD_C,ST7735_PWCTR5);
    st7735_send(LCD_D,0x8A);
    st7735_send(LCD_D,0xEE);

    st7735_send(LCD_C,ST7735_VMCTR1);
    st7735_send(LCD_D,0x0E);

    st7735_send(LCD_C,ST77XX_INVOFF);

    st7735_send(LCD_C,ST77XX_MADCTL);
    st7735_send(LCD_D,0xC0);

    st7735_send(LCD_C,ST77XX_COLMOD);
    st7735_send(LCD_D,0x05);

    st7735_send(LCD_C,ST7735_GMCTRP1);
    st7735_send(LCD_D,0x02);
    st7735_send(LCD_D,0x1C);
    st7735_send(LCD_D,0x07);
    st7735_send(LCD_D,0x12);
    st7735_send(LCD_D,0x37);
    st7735_send(LCD_D,0x32);
    st7735_send(LCD_D,0x29);
    st7735_send(LCD_D,0x2D);
    st7735_send(LCD_D,0x29);
    st7735_send(LCD_D,0x25);
    st7735_send(LCD_D,0x2B);
    st7735_send(LCD_D,0x39);
    st7735_send(LCD_D,0x00);
    st7735_send(LCD_D,0x01);
    st7735_send(LCD_D,0x03);
    st7735_send(LCD_D,0x10);

    st7735_send(LCD_C,ST7735_GMCTRN1);
    st7735_send(LCD_D,0x03);
    st7735_send(LCD_D,0x1D);
    st7735_send(LCD_D,0x07);
    st7735_send(LCD_D,0x06);
    st7735_send(LCD_D,0x2E);
    st7735_send(LCD_D,0x2C);
    st7735_send(LCD_D,0x29);
    st7735_send(LCD_D,0x2D);
    st7735_send(LCD_D,0x2E);
    st7735_send(LCD_D,0x2E);
    st7735_send(LCD_D,0x37);
    st7735_send(LCD_D,0x3F);
    st7735_send(LCD_D,0x00);
    st7735_send(LCD_D,0x00);
    st7735_send(LCD_D,0x02);
    st7735_send(LCD_D,0x10);

    st7735_send(LCD_C,ST77XX_NORON);
    delay_ms(10);

    st7735_send(LCD_C,ST77XX_DISPON);
    delay_ms(100);

    //chip_select_disable();

    isPower=true;
}

void st7735_send(uint8_t dc, uint8_t data)
{
    chip_select_enable();

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

      gpio_set(GPIOA,CLK);
      data=(data<<1);
      // Set Clock Signal
      gpio_reset(GPIOA,CLK);
   }
#endif
   chip_select_disable();
}

void st7735_fill(uint16_t value)
{
  // chip_select_enable();

   st7735_send(LCD_C,ST77XX_CASET);
   st7735_send(LCD_D,0);
   st7735_send(LCD_D,0);
   st7735_send(LCD_D,0);
#ifdef ST7789_320
   st7735_send(LCD_D,0xEF);         // 240 horizontal
#else
   st7735_send(LCD_D,0x7F);         // 128 horizontal
#endif
   st7735_send(LCD_C,ST77XX_RASET);
   st7735_send(LCD_D,0);
   st7735_send(LCD_D,0);
#ifdef ST7789_320
   st7735_send(LCD_D,1);
   st7735_send(LCD_D,0x3F);         // 320 vertical
#else
   st7735_send(LCD_D,0);
   st7735_send(LCD_D,0x9f);         // 160  vertical
#endif

   st7735_send(LCD_C,ST77XX_RAMWR);

#ifdef HW_SPI

   gpio_set(GPIOB,DC);
   SPI1->CR1 &= CR1_SPE_Reset;      // disable SPI for setup
   SPI1->CR1  = (SPI_Mode_Master|SPI_DataSize_16b|SPI_NSS_Soft|SPI_BaudRatePrescaler_2);
   SPI1->CR1 |= CR1_SPE_Set;        // enable SPI
   chip_select_enable();
#ifdef ST7789_320
   for (int i=0; i < 76800; i++)
#else
   for (uint16_t i=0; i < (uint16_t)20480; i++)
#endif

   {
       while (!(SPI1->SR & SPI_I2S_FLAG_TXE));
       SPI1->DR=value;
   }

   chip_select_disable();

   SPI1->CR1 &= CR1_SPE_Reset;      // disable SPI for setup
   SPI1->CR1  = (SPI_Mode_Master|SPI_DataSize_8b|SPI_NSS_Soft|SPI_BaudRatePrescaler_4);
   SPI1->CR1 |= CR1_SPE_Set;        // enable SPI
#else
   uint8_t c1=value>>8;
   uint8_t c2=(uint8_t)value;

   gpio_set(GPIOB,DC);
#ifdef ST7789_320
   for (int i=0; i < 76800; i++)
#else
   for (uint16_t i=0; i < (uint16_t)20480; i++)
#endif

   {
      st7735_send(LCD_D,c1);
      st7735_send(LCD_D,c2);
   }

   //chip_select_disable();
#endif

}


