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

This example shows how to:
  - Configure the PLL (clocked by HSE as System clock source）
  - Configure HSI as System clock source
  - Configure HSE as System clock source
  - Output the System clock on MCO pin

 Through two buttons(KEY1、KEY2), switch the system clock.
 phenomenon :
  - If press KEY1(PLL as clock source): LED2 flashing quickly
  - If press KEY2(HSI as clock source): LED2 flashing normally
  - You can monitor the system clock on MCO pin (PA.8) or on serial assisatant.

&par Hardware Description

using USART1(TX:PA9、RX:PA10).
  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - RCM/RCM_ClockSwitch/Source/apm32f0xx_int.c     Interrupt handlers
  - RCM/RCM_ClockSwitch/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
