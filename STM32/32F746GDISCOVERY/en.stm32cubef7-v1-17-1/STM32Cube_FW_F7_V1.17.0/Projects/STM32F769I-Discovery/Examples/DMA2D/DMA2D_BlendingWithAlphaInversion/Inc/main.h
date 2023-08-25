/**
  ******************************************************************************
  * @file    DMA2D/DMA2D_BlendingWithAlphaInversion/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery_sdram.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#define ARGB8888_BYTE_PER_PIXEL  4
#define RGB565_BYTE_PER_PIXEL    2

#define LAYER_SIZE_X          240
#define LAYER_SIZE_Y          130
#define LAYER_BYTE_PER_PIXEL  RGB565_BYTE_PER_PIXEL

#define LCD_FRAME_BUFFER  0xC0000000

#define WVGA_RES_X  800
#define WVGA_RES_Y  480

#endif /* __MAIN_H */

