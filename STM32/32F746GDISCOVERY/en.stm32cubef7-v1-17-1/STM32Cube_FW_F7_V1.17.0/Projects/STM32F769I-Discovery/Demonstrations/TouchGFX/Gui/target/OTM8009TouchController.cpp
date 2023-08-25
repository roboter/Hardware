/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  


#include <OTM8009TouchController.hpp>

#ifdef USE_STM32769I_DISCO
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"
#else
#include "stm32f769i_eval.h"
#include "stm32f769i_eval_ts.h"
#endif

uint32_t LCD_GetXSize();
uint32_t LCD_GetYSize();

void OTM8009TouchController::init()
{
    BSP_TS_Init(LCD_GetXSize(), LCD_GetYSize());
}

bool OTM8009TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    TS_StateTypeDef state;
    BSP_TS_GetState(&state);
    if (state.touchDetected)
    {
        x = state.touchX[0];
        y = state.touchY[0];
        return true;
    }
    return false;
}
