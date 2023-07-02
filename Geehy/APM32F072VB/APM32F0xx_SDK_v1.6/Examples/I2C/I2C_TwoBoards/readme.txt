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

This example shows how to control I2C devices and communicate between two different boards.

To use this example, you need to load the same software into two APM32F030 or  APM32F072
boards(let's call them  Board master and Board Slave) then connect these two boards through I2C lines
and GND.

 - At startup, Boards master and slave are both in slave receiver mode and wait for messages
   to be received.
 - When KEY1 is pressed on Board master, the master transmitter sents "Hello master" to Board slave.
   The message is displayed on serial assistant through USART2.
 - When KEY1 is pressed on Board slave, the slave transmitter sents "Hello master" to Board master.
   The message is displayed on serial assistant through USART2.

&par Hardware Description

   I2C     BOARD1    BOARD2
   SCL      PB8            PB8     (External Pull up resistance)
   SDA      PB9            PB9     (External Pull up resistance)

using USART2(TX:PA2¡¢RX:PA3).
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - I2C/TwoBoard/master/Source/apm32f0xx_int.c     Interrupt handlers
  - I2C/TwoBoard/master/Source/main.c                   Main program
  - I2C/TwoBoard/slave/Source/apm32f0xx_int.c       Interrupt handlers
  - I2C/TwoBoard/slave/Source/main.c                     Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
