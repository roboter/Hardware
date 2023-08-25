/**
  @page JPEG_DecodingUsingFs_DMA : JPEG example : JPEG decoding using Fatfs and with DMA example
  
  @verbatim
  ******************************************************************************
  * @file    JPEG/JPEG_DecodingUsingFs_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the JPEG decoding using Fatfs and with DMA example.
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

This example demonstrates how to read jpeg file from SDCard memory using Fatfs, decode it 
using the JPEG HW decoder in DMA mode and display the final ARGB8888 image KoD LCD 
mounted on board or a HDMI monitor Connected through the DSI-HDMI bridge board MB1232.A.

The example can automatically detect if the KoD LCD is connected or if the DSI-HDMI 
bridge is connected to the DSI connector (CN1), if no DSI slave is connected LED1 will turn On
to indicate an error.

The example performs the following actions :
  - Link the uSD disk I/O driver.
  - Register the file system object (mount) to the FatFs module for the uSD drive.
  - Open the jpg file "image.jpg" in read access.
  - Call the function "JPEG_Decode_DMA" to start decoding the jpg file with DMA (Non blocking method).
    Function "JPEG_Decode_DMA" is implemented in a separate module decode_dma.c.
    This module is a wrapper on top of the JPEG HAL driver
  
  - Once the decoding ends, 
    - Call HAL routine "HAL_JPEG_GetInfo" to retrieve the image parameters :
      image width, image height, image quality (from 1% to 100%) color space and Chroma sampling.      
    - copy the ARGB8888 result buffer to the LCD Frame buffer for display:
        Using the DMA2D and positioning the image in the center of the LCD screen.
    - Close the jpg file.
	
@note This example supports only images with dimensions (width and Height) multiple of 16 pixels examples 
      (320x240, 160x80, 640x480).

@note To run this example , you can use an JPEG �.jpg� file from\Utilities\Media\Pictures\JPG
      or use your own .jpg image.
      
@note The jpeg HW decoder outputs are organized in YCbCr blocks. 
      The jpeg utilities functions implemented in "jpeg_utils.c" file are used to convert these YCbCr blocks 
      to RGB pixels to the destination JPEG output buffer.
      The JPEG utilities files allowing to convert YCbCr blocks to RGB pixels are available under \Utilities\JPEG

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note The STM32F7xx devices can reach a maximum clock frequency of 216MHz but as this example uses SDRAM,
      the system clock is limited to 200MHz. Indeed proper functioning of the SDRAM is only guaranteed 
      at a maximum system clock frequency of 200MHz.

@note The compiler optimizations level could be set to High/Balanced giving a good tradeoff between the code size and the performance (decode time).


@par Keywords

Display, Graphic, JPEG, Decoding, Flash memory, DMA, ARGB8888, Hardware decoding, LCD, HDMI, YCbCr, RGB,
FatFS, File system, SD Card, SDRAM

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

  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/stm32f7xx_hal_conf.h          HAL configuration file
  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/stm32f7xx_it.h                Interrupt handlers header file
  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/ffconf.h                      FAT file system module configuration file
  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/main.h                        Header for main.c module  
  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/decode_dma.h                  Header for decode_dma.c module   
  - JPEG/JPEG_DecodingUsingFs_DMA/Inc/jpeg_utils_conf.h             JPEG utilties module configuration file
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/sd_diskio.h                   SD diskio header file  
  
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/stm32f7xx_it.c                Interrupt handlers
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/main.c                        Main program
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/decode_dma.c                  JPEG Decoding with DMA module
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/stm32f7xx_hal_msp.c           HAL MSP module 
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/system_stm32f7xx.c            STM32F7xx system source file  
  - JPEG/JPEG_DecodingUsingFs_DMA/Src/sd_diskio.c                   SD diskio source file  

@par Hardware and Software environment

  - This example runs on STM32F769xx/STM32F779xx.
    
  - This example has been tested with STMicroelectronics STM32F769I_Discovery
    boards and can be easily tailored to any other supported device 
    and development board. 
    
  - STM32F769I_Discovery Set-up
  - Copy a jpg image to a uSD card (under the root)
      The image must have the following properties:
        - named as "image.jpg"
        - dimensions : less or equal to the LCD-DSI screen (i.e 800x480 for the STM32F769I_Discovery board)
        - Witdh  : <= 800
        - Height : <= 480     
  - Connect the uSD Card to the uSD connector (CN5).
    
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Mount either the KoD LCD pannel (Board MB1166 rev.A) or the DSI-HDMI bridge(Board MB1232 Rev.A)
   to the DSI connector (CN1). 
 - if using the DSI-HDMI bridge then connect a HDMI monitor using a HDMI cable to the 
   MB1232 board. 
 - Run the example


 */