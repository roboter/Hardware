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

 This example provides a short description of how to use the RTC peripheral and
the Time Stamp feature.

The associated firmware performs the following:
1.It configures the RTC TimeStamp pin to be falling edge and enables the TimeStamp detection.
2.When RTC_TimeStamp pin is on the air, a interrupt will be generated and print TimeStamp information to serial assistant.

 phenomenon :
  - TimeStamp information are displayed in serial assistant.

  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - RTC/TimeStamp/Source/apm32f0xx_int.c     Interrupt handlers
  - RTC/TimeStamp/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
