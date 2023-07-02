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

This example shows how to configure external interrupt lines.
In this example, 2 EINT lines (KEY1、KEY2) when using the APM32F030 or
APM32F072 MINI BOARD are configured to generate an interrupt on each
falling edge. In the interrupt routine a led connected to a specific GPIO pin
is toggled.

In this example
    - EINT0  is mapped to PA0(KEY2)
    - EINT1  is mapped to PA1(KEY1)

After EINT configuration
  when falling edge is detected on EINT0 , LED2 toggles
  when falling edge is detected on EINT1 , LED3 toggles

&par Directory contents

  - EINT/EINT/Source/apm32f0xx_int.c     Interrupt handlers
  - EINT/EINT/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.
