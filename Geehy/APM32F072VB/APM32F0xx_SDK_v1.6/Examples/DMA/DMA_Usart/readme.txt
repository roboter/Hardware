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

This example provides a basic communication between USART1 and USART2 using DMA1
capability.

After system reset, USART2 Transmit data from DMA_USART_TxBuf to USART1.
Data received by USART1 is transferred by DMA and stored in DMA_USART_RxBuf.
If the data of DMA_USART_TxBuf and DMA_USART_RxBuf are the same,
LED2 and LED3 will constantly flicker alternately, or flicker together.

USART2_TX (PA2)  --->   USART1_RX (PA10)

&par Directory contents

  - DMA/DMA_USART/Source/apm32f0xx_int.c          Interrupt handlers
  - DMA/DMA_USART/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
