/**
  @page LCD_DSI_CmdMode_DoubleBuffering : LCD DSI example : LCD DSI example in DSI Command mode.

  @verbatim
  ******************************************************************************
  * @file    LCD_DSI/LCD_DSI_CmdMode_DoubleBuffering/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the LCD DSI in command mode example.
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
  @endverbatim

@par Example Description

How to use the embedded LCD DSI controller (using the LTDC and DSI Host IPs) to
drive the KoD LCD mounted on-board.

The goal of this example is to display a QVGA landscape (320x240) images on LCD glass
in Command mode using two buffers one for the display and the other for the drawing.

Layer0 is initialized to display a brief description of the example. It will be
used for images display also.

End of Refresh callback (LTDC) is used to swap image to be draw to display buffer.
Each image is displayed for two secondes. A first image is prepared in the back
buffer while a second image is displayed.

The LED1 is ON when an error occurs during initialization of the LCD.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Graphic, Display, LCD, DSI, MIPI Alliance, Command mode, Double Buffering, LTDC, QVGA, ARGB8888

@Note�If the user code size exceeds the DTCM-RAM size or starts from internal cacheable memories (SRAM1 and SRAM2),that is shared between several processors,
 �����then it is highly recommended to enable the CPU cache and maintain its coherence at application level.
������The address and the size of cacheable buffers (shared between CPU and other masters)  must be properly updated to be aligned to cache line size (32 bytes).

@Note It is recommended to enable the cache and maintain its coherence, but depending on the use case
����� It is also possible to configure the MPU as "Write through", to guarantee the write access coherence.
������In that case, the MPU must be configured as Cacheable/Bufferable/Not Shareable.
������Even though the user must manage the cache coherence for read accesses.
������Please refer to the AN4838 �Managing memory protection unit (MPU) in STM32 MCUs�
������Please refer to the AN4839 �Level 1 cache on STM32F7 Series�

@par Directory contents

  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Inc/stm32f7xx_hal_conf.h          HAL configuration file
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Inc/stm32f7xx_it.h                Interrupt handlers header file
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Inc/main.h                        Header for main.c module
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Inc/life_augmented_argb8888.h     Image 320x240 in ARGB8888 to display on LCD
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Inc/image_320x240_argb8888.h      Image 320x240 in ARGB8888 to display on LCD  
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Src/stm32f7xx_it.c                Interrupt handlers
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Src/main.c                        Main program
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Src/stm32f7xx_hal_msp.c           HAL MSP file
  - LCD_DSI/LCD_DSI_CmdMode_DoubleBuffer/Src/system_stm32f7xx.c            STM32F7xx system source file

@par Hardware and Software environment

  - This example runs on STM32F769xx/STM32F779xx devices.

  - This example has been tested with STMicroelectronics STM32F769I-DISCOVERY
    board and can be easily tailored to any other supported device
    and development board.

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example



 */
