/**
  @page External_Interrupt
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    External Interrupt/External Interrupt/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the External Interrupt Example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
   @endverbatim

@par Example Description 

This example demonstrates how to use the InterruptPort class to configure 
an external interrupt line.
In this example, an EXTI line is configured to generate an interrupt on rising 
edge on pin PA0 which is connected to the USER button.
In the interrupt routine, the green led connected to GPIO pin PG13 is toggled
and the message "USER Button pressed\n" is displayed in the output window
of Visual Stutio.
For more information about InterruptPort class, see MSDN documentation.

@par Directory contents 

  - EXTI.csproj                 VS2012 Project file.
  - EXTI.csproj.user            Project options file.
  - Properties/AssemblyInfo.cs  Application metadata.
  - Program.cs                  Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use green LED connected to PG13 pin 
    - Use the USER button connected to pin PA0. 

  - Required assemblies files:
    - System
    - System.Threading
    - Microsoft.SPOT
    - Microsoft.SPOT.Hardware
    - STM32F429I_Discovery.Netmf.Hardware.cs
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open EXTI.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
