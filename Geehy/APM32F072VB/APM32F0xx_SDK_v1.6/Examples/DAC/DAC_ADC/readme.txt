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

This example provides a example of how to use DAC channel 1(PA4) to output
voltage to ADC channel 10(PC0). The converted voltage of PA4 is detected by
ADC  channel 10 and displayed on serial assistant through USART1.

 -DAC generates voltage from 0V to 3.3V

 -when the voltage is greater than 3.1V, then LED2 turns on and LED3 turns off.
 -when the voltage is less than 0.8V, then LED2 turns off and LED3 turns on.
 -when the voltage is greater than 0.8V but less than 3.1V, then LED2 and LED3 turn on.

&par Hardware Description

connect DAC Channel1 (PA4) to ADC Channel10 (PC0)

using USART1(TX:PA9¡¢RX:PA10).
  - USART2 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - DAC/DAC_ADC/Source/apm32f0xx_int.c     Interrupt handlers
  - DAC/DAC_ADC/Source/main.c                   Main program

&par Hardware and Software environment

  - This example runs on APM32F072 MINI Devices.
