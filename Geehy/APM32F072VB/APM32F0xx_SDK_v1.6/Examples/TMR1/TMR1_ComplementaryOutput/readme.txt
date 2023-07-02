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

This example shows how to configure the TMR1 peripheral to generate complementary
TMR1 signals, to insert a defined dead time value.

The phenomenon of observe whether the output waveform is correct through
the oscilloscope. Becides LED2 and LED3 constantly flashing.

using TMR1 CH1  PA7 to output PWM
using TMR1 CH1N PA8 to output PWM

&par Directory contents

  - TMR/TMR1/TMR1_ComplementaryOutput/apm32f0xx_int.c     Interrupt handlers
  - TMR/TMR1/TMR1_ComplementaryOutput/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F030 or APM32F072 MINI Devices.