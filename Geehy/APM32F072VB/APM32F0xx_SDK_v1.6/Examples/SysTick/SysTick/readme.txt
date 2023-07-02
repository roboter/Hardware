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

This example shows how to configure the SysTick to generate a time base equal to
1 ms. The system clock is set to 8 MHz, the SysTick is clocked by the HSE clock.

A "Delay" function is implemented based on the SysTick end-of-count event.
For LEDs are toggled with a timing defined by the Delay function.

&par Hardware Description

SysTick delays exactly one second, and the LED's on-off state changes.

&par Directory contents

  - SysTick/SysTick/Source/apm32f0xx_int.c     Interrupt handlers
  - SysTick/SysTick/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
