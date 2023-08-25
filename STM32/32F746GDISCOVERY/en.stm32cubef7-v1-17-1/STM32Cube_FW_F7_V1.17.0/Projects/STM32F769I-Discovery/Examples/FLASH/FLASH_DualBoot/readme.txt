/**
  @page FLASH_DualBoot  FLASH Dual Boot example

  @verbatim
  ******************************************************************************
  * @file    FLASH/FLASH_DualBoot/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the FLASH Dual boot example.
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

Guide through the configuration steps to program internal Flash memory bank 1
and bank 2, and to swap between both of them by mean of the FLASH HAL API.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock (SYSCLK)
to run at 200 MHz.

Below are the steps to run this example:
1- Choose the FLASH_DualBoot_Bank2 project and generate its binary (ie: FLASH_DualBoot.bin)

2- Configure the FLASH memory at Dual Bank mode using STM32 ST-LINK Utilities (Target -> Options Bytes) ( "nDBANK" should be unchecked).
   Load this binary at the bank2 of the flash(at the address 0x08100000) using
   STM32 ST-LINK Utilities(www.st.com) or any similar tool.
@note:
 - You can avoid step 1 by directly loading the binary file provided with the example
 - You have to configure your preferred toolchain in order to generate the binary
   file after compiling the project.

3- Choose the FLASH_DualBoot_Bank1 project and run it, this project will be loaded
   in the bank1 of the flash: at the address 0x08000000

4- Click the BUTTON_USER button to swap between the two banks

- If program in bank1 is selected, a message with a blue text back color will be
  displayed on LCD and LED1 will remain toggling while LED2 is turn on.

- If program in bank2 is selected, a message with a red text back color will be
  displayed on LCD and LED2 will remain toggling while LED1 is turn on.

- If any error occurs, only LED1 turns on.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Memory, Flash, Dual boot, Dual Bank, Execute, Binary, Option bytes

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

  - FLASH/FLASH_DualBoot/Inc/stm32f7xx_hal_conf.h        HAL Configuration file
  - FLASH/FLASH_DualBoot/Inc/stm32f7xx_it.h              Header for stm32f7xx_it.c
  - FLASH/FLASH_DualBoot/Inc/main.h                      Header for main.c module
  - FLASH/FLASH_DualBoot/Src/stm32f7xx_it.c              Interrupt handlers
  - FLASH/FLASH_DualBoot/Src/main.c                      Main program
  - FLASH/FLASH_DualBoot/Src/system_stm32f7xx.c          STM32F7xx system clock configuration file
  - FLASH/FLASH_DualBoot/Binary/FLASH_DualBoot.bin       Binary file to load at bank2

@par Hardware and Software environment

  - This example runs on STM32F767xx/STM32F769xx/STM32F777xx/STM32F779xx devices.

  - This example has been tested with STM32F769I-Discovery board and can be
    easily tailored to any other supported device and development board.

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

In order to generate the .bin file with MDK-ARM, you must do the following:
 - Open the Project.uvproj project
 - Rebuild all files: Project->Rebuild all target files
 - Go to "/FLASH_DualBoot\MDK-ARM" directory and run "axftobin.bat"
   (Fromelf Exe path might have to be updated in "axftobin.bat" file, according to your Keil setup).
 - A binary file "FLASH_DualBoot_Bank2.bin" will be generated under "FLASH_DualBoot_Bank2" folder.



 */
