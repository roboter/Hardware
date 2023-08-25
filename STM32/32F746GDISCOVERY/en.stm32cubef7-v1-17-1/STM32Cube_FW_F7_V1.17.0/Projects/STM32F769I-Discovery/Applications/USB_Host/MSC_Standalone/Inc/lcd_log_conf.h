/**
  ******************************************************************************
  * @file    USB_Host/MSC_Standalone/Inc/lcd_log_conf.h
  * @author  MCD Application Team
  * @brief   LCD Log configuration file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef  __LCD_LOG_CONF_H__
#define  __LCD_LOG_CONF_H__

/* Includes ----------------------------------------------------------------- */
#include "stm32f769i_discovery_lcd.h"
#include <stdio.h>


/* Exported types ----------------------------------------------------------- */
/* Exported constants ------------------------------------------------------- */
/* Define the LCD default text color */
#define     LCD_LOG_DEFAULT_COLOR                LCD_COLOR_WHITE

/* Comment the line below to disable the scroll back and forward features */
#define     LCD_SCROLL_ENABLED      1

/* Define the Fonts */
#define     LCD_LOG_HEADER_FONT                   Font16
#define     LCD_LOG_FOOTER_FONT                   Font12
#define     LCD_LOG_TEXT_FONT                     Font12

/* Define the LCD LOG Color */
#define     LCD_LOG_BACKGROUND_COLOR              LCD_COLOR_BLACK
#define     LCD_LOG_TEXT_COLOR                    LCD_COLOR_WHITE

#define     LCD_LOG_SOLID_BACKGROUND_COLOR        LCD_COLOR_BLUE
#define     LCD_LOG_SOLID_TEXT_COLOR              LCD_COLOR_WHITE

/* Define the cache depth */
#define     CACHE_SIZE              100
#define     YWINDOW_SIZE            13

#if (YWINDOW_SIZE > 13)
#error "Wrong YWINDOW SIZE"
#endif

/* Redirect the printf to the LCD */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 * set to 'Yes') calls __io_putchar() */
#define LCD_LOG_PUTCHAR int __io_putchar(int ch)
#else
#define LCD_LOG_PUTCHAR int fputc(int ch, FILE *f)
#endif                          /* __GNUC__ */

/* Exported macro ----------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif                          /* __LCD_LOG_CONF_H */

