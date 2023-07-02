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

This example describes how to config a communication the CAN in loopback mode.
CAN transmit a message to self. Then compare the received message with transmitted
message. The LED2 turns on while the message is consistent, otherwise LED3 turns on.
The communication status will displayed on serial assistant through USART1.

  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - CAN/CAN_LoopBack/Include/apm32f0xx_int.h     Interrupt handlers header file
  - CAN/CAN_LoopBack/Source/apm32f0xx_int.c      Interrupt handlers
  - CAN/CAN_LoopBack/Include/main.h                 Main program header file
  - CAN/CAN_LoopBack/Source/main.c                  Main program

&par Hardware and Software environment

  - This example runs on APM32F072 MINI Devices.
