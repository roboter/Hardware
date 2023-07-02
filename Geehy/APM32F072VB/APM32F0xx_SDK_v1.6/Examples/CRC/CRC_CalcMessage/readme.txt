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

Write the calculated data to CRC DATA register and get the calculated result.

The computer of serial debugging assistant can display the corresponding
information for ComputedCRC.

set up ExpectedCRC.

The phenomenon of ComputedCRC compases ExpectedCRC. If ComputedCRC is equal to
ExpectedCRC, LED2 on. If ComputedCRC is not equal to ExpectedCRC, LED3 on.

&par Hardware Description

using USART2(TX:PA2、RX:PA3).
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Software Description

Configure the LED2 and LED3 initialization structures, Configure the USART1
initialization structures,quote calculated CRC program,As the same time,The
computer of serial debugging assistant can display information of ComputedCRC.
ComputedCRC compases ExpectedCRC. Then LED(LED2/LED3)on.

&par Directory contents

  - CRC/CRC_CalcMessage/Source/apm32f0xx_int.c     Interrupt handlers
  - CRC/CRC_CalcMessage/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
