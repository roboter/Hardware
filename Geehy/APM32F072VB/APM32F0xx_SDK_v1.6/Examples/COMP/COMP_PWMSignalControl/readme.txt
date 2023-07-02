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

This example shows how to use the comparator. COMP2  non-inverting intput connect
to PA3. And COMP2 inverting input is internally connected to VREFINT(1.22V) which is
used to compare with PA3 input.

  - External voltage should be connected to PA3.

  - Connect an oscilloscope to TMR1 channel PA8 to display waveform.

  - While PA3 is lower than VREFINT (1.22V), PWM signal is displayed on PA8.
   -While PA3 is higher than VREFINT, PA8 is in high level.

&par Directory contents

  - COMP/COMP/Source/apm32f0xx_int.c     Interrupt handlers
  - COMP/COMP/Source/main.c              Main program

&par Hardware and Software environment

  - This example runs on APM32F072 MINI Devices.
