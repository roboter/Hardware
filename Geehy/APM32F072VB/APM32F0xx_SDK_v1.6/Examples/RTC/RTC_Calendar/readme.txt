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
  - Using RTC to set the system time and date.
  - recover system time from reset state by using RTC_WriteBackup and RTC_ReadBackup function.

 phenomenon :
  - Time and date information are displayed through serial assistant.
  - If reset(Power is on) , system will read data from the backup area and display it.
  - If reset(System Power from off to on), sytem will reinitialize the RTC.

&par Hardware Description

using USART2(TX:PA2、RX:PA3).
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - RTC/Calendar/Source/apm32f0xx_int.c     Interrupt handlers
  - RTC/Calendar//Source/main.c                  Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
