/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.0
 *
 * @date        2021-10-13
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

This example provides a small application in which system sends and receives data by polling
though using I2S firmware library. All received information will be displayed by serial assistant.

To use this example, you need to load it on two APM32F072 boards (let's call them Board master
and Board slave). Then connect these two boards through I2S lines and must master and slave connect
to the same GND.

After the program is downloaded, please reset the motherboard and then reset the slave.When compare
buffer is the same, the Board slave LED2 is on.The phenomenon of data interaction process can be
displayed using serial assistant.

           Master      Slave
 WS        PA4         PA4
 CK        PA5         PA5
 SD        PA7         PA7

&par Hardware Description

using USART2(TX:PA2、RX:PA3) to Master.
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - I2S/I2S_TwoBoards/slave/Source/apm32f0xx_int.c          Interrupt handlers
  - I2S/I2S_TwoBoards/slave/Source/main.c                   Main program
  - I2S/I2S_TwoBoards/master/Source/apm32f0xx_int.c         Interrupt handlers
  - I2S/I2S_TwoBoards/master/Source/main.c                  Main program

&par Hardware and Software environment

  - This example runs on APM32F072 MINI Devices.
