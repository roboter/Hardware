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

Is example shows how to  control CEC devices and communicate between two different boards.

To use this example, you need to load the same software into two APM32 boards
(let's call them  Master and  Slave) then connect these two boards through CEC lines .

The example software perform the following actions:
 -  At startup, Master transmit data for Slave , Slave return receive data for Master.
 -  When Master  the RESET is pressed, the Master start transmit data.
    Master LED2 Toggle, USART1 print " Master transmit data..."
 -  Slave receive data，in the meantime ruturn data for Master.
    Selve LED2 Toggle, USART1 print "Slave receive data...."
 -  If communicate break off the LED2 don't toggle，you can first RESET Slave and then RESET Master .
 -  If communicate fail the LED3 on.

   CEC:    Board_Master         Board_Slave
                    PB10    ---------   PB10
  (External Pull up resistance)

  - USART1configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - CEC/CEC_Communication/CEC_Communication_Master/Source/apm32f0xx_int.c     Interrupt handlers
  - CEC/CEC_Communication/CEC_Communication_Master/Source/main.c                    Main program
  - CEC/CEC_Communication/CEC_Communication_Master/Source/apm32f0xx_int.c      Interrupt handlers
  - CEC/CEC_Communication/CEC_Communication_Master/Source/main.c                    Main program

&par Hardware and Software environment

  - This example runs on APM32F072 MINI Devices.
