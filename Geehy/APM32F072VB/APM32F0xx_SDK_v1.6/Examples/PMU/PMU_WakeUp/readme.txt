/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.1
 *
 * @date        2021-07-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

&par Example Description

This example shows how to enter the system by external interrupt to
  - STANDBY mode and wake-up from this mode either with the RESET or give PC13 a falling edge to recover.
  - SLEEP       mode and wake-up from this mode either with the RESET or give PA6   a falling edge to recover.
  - STOP        mode and wake-up from this mode with the RESET.

phenomenon :
  -If press KEY1(SLEEP       mode):  LED2 is on ,while LED3 LED3 remain in  the previous state. After giving PA6 a falling edge ,system running from reset state.
  -If press KET2(STANDBY  mode): LED2 and LED3  are off. After giving PC13 a rising edge,system continue running.
  -If low down PA7(STOP  mode):  LED2 and LED3 remain in  the previous state. After reset, system recover to normal state.

&par Directory contents

  - PMU/PMU/Source/apm32f0xx_int.c        Interrupt handlers
  - PMU/PMU/Source/main.c                      Main program

&par Hardware Description

using USART2(TX:PA2、RX:PA3).
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
