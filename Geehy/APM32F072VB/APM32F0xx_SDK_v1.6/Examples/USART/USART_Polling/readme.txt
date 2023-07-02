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

The program aims to show how to send or received data by using USART, in this case,
USART1 and USART2 send or receiveddata to each other. Verification will occur after transmission,
if pass , LED2 will be on.

The phenomenon of data interaction process can be displayed using serial assistant.

&par Hardware Description

USART1_TX(PA9) ----> USART2_RT(PA3)
USART1_RX(PA10)----> USART2_TX(PA2)

  - USART1 and USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - USART/USART_Polling/Source/apm32f0xx_int.c     Interrupt handlers
  - USART/USART_Polling/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.