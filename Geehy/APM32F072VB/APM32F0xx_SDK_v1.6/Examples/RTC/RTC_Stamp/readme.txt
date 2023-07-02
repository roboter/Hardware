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

This example shows how to write/read data to/from RTC Backup data registers and
demonstrates the Tamper detection feature.

The associated firmware performs the following:
1. It configures the Tamper pin to be falling edge, and enables the Tamper interrupt.
2. It writes the data to all RTC Backup data registers
3. On applying a low level on the RTC_AF1 pin (PC.13, connected to Tamper button),
   the RTC backup data registers are reset and the Tamper interrupt is generated.

 phenomenon :
  - If Tamper1 interrupt happen, LED2 is on
  - If Tamper2 interrupt happen, LED3 is on
  - Time and Backup data are displayed in serial assistant.

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
