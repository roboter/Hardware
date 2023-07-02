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

This example shows how to configure the TMR1 peripheral to capture the internal clock source from pin MCO.
The result will be displayed on serial assistant through USART2.

&par Directory contents

  - TMR/TMR1/TMR1_InputCapture/apm32f0xx_int.c           Interrupt handlers
  - TMR/TMR1/TMR1_InputCapture/Source/main.c              Main program

&par Hardware Description

using MCO(PA8) as TMR1 Input Channel 3(PA10)

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