#include <Arduino.h>
// include library, include base class, make path known
#include <GxEPD.h>
#include "SD.h"
#include "SPI.h"
#include <Button2.h>
#include <GxGDEW027C44/GxGDEW027C44.h> // 2.7" b/w/r                 //H220

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO -1 // elink no use
#define SPI_CLK 18

#define SDCARD_SS 13
#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_CLK 14

#define BUTTON_1 37
#define BUTTON_2 38
#define BUTTON_3 39

#define SPEAKER_OUT 25
#define AMP_POWER_CTRL 19
#define CHANNEL_0 0
#define BUTTONS_MAP \
  {                 \
    37, 38, 39      \
  }

Button2 *pBtns = nullptr;
uint8_t g_btns[] = BUTTONS_MAP;

GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ELINK_DC, /*RST=*/ELINK_RESET); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ELINK_RESET, /*BUSY=*/ELINK_BUSY);           // arbitrary selection of (16), 4

#if defined(_GxGDEW0154Z04_H_) || defined(_GxGDEW0213Z16_H_) || defined(_GxGDEW029Z10_H_) || defined(_GxGDEW027C44_H_) || defined(_GxGDEW042Z15_H_) || defined(_GxGDEW075Z09_H_)
#define HAS_RED_COLOR
#endif

void button_callback(Button2 &b)
{
  for (int i = 0; i < sizeof(g_btns) / sizeof(g_btns[0]); ++i)
  {
    if (pBtns[i] == b)
    {
      Serial.printf("Button: %u Press\n", pBtns[i].getAttachPin());
      ledcWriteTone(CHANNEL_0, 1000);
      delay(200);
      ledcWriteTone(CHANNEL_0, 0);
    }
  }
}

void button_init()
{
  uint8_t args = sizeof(g_btns) / sizeof(g_btns[0]);
  pBtns = new Button2[args];
  for (int i = 0; i < args; ++i)
  {
    pBtns[i] = Button2(g_btns[i]);
    pBtns[i].setPressedHandler(button_callback);
  }
}

bool sdOK = false;

const char *skuNum = "SKU:H220";

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
  display.init(); // enable diagnostic output on Serial

  pinMode(AMP_POWER_CTRL, OUTPUT);
  digitalWrite(AMP_POWER_CTRL, HIGH);

  ledcSetup(CHANNEL_0, 1000, 8);
  ledcAttachPin(SPEAKER_OUT, CHANNEL_0);
  int i = 3;
  while (i--)
  {
    ledcWriteTone(CHANNEL_0, 1000);
    delay(200);
    ledcWriteTone(CHANNEL_0, 0);
  }

  button_init();

  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(0, 0);

  SPIClass sdSPI(VSPI);
  sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);

  if (!SD.begin(SDCARD_SS, sdSPI))
  {
    sdOK = false;
  }
  else
  {
    sdOK = true;
  }

  display.fillScreen(GxEPD_WHITE);

  // display.drawBitmap(lilygo, startX, startY, bmpWidth, bmpHeight, GxEPD_RED);

#if defined(_GxGDEW0154Z04_H_) || defined(_GxGDEW027W3_H_) || defined(_GxGDEW0213Z16_H_) || defined(_GxGDE0213B72_H_) || defined(_GxGDE0213B72B_H_)
  display.setCursor(display.width() - display.width() / 2, display.height() - 35);
#elif defined(_GxGDEP015OC1_H_)
  display.setCursor(display.width() - display.width() / 2 - 10, display.height() - 35);
#elif defined(_GxGDEW027C44_H_) || defined(_GxGDEH029A1_H_) || defined(_GxGDEW029Z10_H_)
  display.setCursor(display.width() - display.width() / 2 - 20, display.height() - 35);
#else
#error "Needs display selected"
#endif

#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println(skuNum);

  display.setTextColor(GxEPD_BLACK);

#if defined(_GxGDEW0154Z04_H_) || defined(_GxGDEW027W3_H_) || defined(_GxGDEW0213Z16_H_) || defined(_GxGDE0213B72_H_) || defined(_GxGDE0213B72B_H_) || defined(_GxGDEP015OC1_H_)
  display.setCursor(display.width() / 2 - 40, display.height() - 10);
#elif defined(_GxGDEW027C44_H_) || defined(_GxGDEH029A1_H_) || defined(_GxGDEW029Z10_H_)
  display.setCursor(display.width() / 2 - 60, display.height() - 10);
#else
#error "Needs display selected"
#endif

  if (sdOK)
  {
    uint32_t cardSize = SD.cardSize() / (1024 * 1024);
    display.println("SDCard:" + String(cardSize) + "MB");
  }
  else
  {
    display.println("SDCard None");
  }
  display.update();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
