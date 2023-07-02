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

This example describes how to use the ADC1 to convert continuously the voltage
applied to the APM32F030 or APM32F072 MINI ADC1_Channel0 input.
The converted voltage is displayed on serial assistant through USART1.

&par Hardware Description

using ADC1_Channel0(PA0)
using USART1(TX:PA9、RX:PA10).
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

  - ADC/ContinuousConversion/Source/apm32f0xx_int.c     Interrupt handlers
  - ADC/ContinuousConversion/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
