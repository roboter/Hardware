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

This example describes how to use WFI event to enter sleep mode and wake up
using external interrupt.
At startup, press KEY2(PA0) to occur Wait For Interrupt(WFI) event, and device
will enter sleep mode. The device will wake up if press KEY2 again.
The status of device is displayed on serial assistant through USART1.

&par Hardware Description

EINT0  is connected to PA0(KEY2)

using USART1(TX:PA9¡¢RX:PA10).
  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled


&par Software Description

After Initialization, ADC1 start to transform and show volatage information to USART1

&par Directory contents

  - NVIC\NVIC_WFI/Source/apm32f0xx_int.c     Interrupt handlers
  - NVIC\NVIC_WFI/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
