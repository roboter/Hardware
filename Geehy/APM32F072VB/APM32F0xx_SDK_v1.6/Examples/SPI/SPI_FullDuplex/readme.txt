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

This demo is based on the APM32F030 or APM32F072 board, it shows how to use SPI peripheral.
by making a master/slave full duplex communication between the SPI and the UART1.
The phenomenon of serial assistant can display information from USART2.

Connect UART1 and SPI pins as follows:
UART1 TX   (PA9)    to SPI MOSI (PA7)
UART1 RX   (PA10)  to SPI MISO (PA6)
UART1 CLK  (PA8)   to SPI SCK   (PA5)

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

  - SPI/SPI_FullDuplex/Source/apm32f0xx_int.c       Interrupt handlers
  - SPI/SPI_FullDuplex/Source/main.c                     Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
