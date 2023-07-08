/**
  @page PWM_Output PWM_Output
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    PWM/PWM_Output/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the PWM_Output Example.
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

This example shows how to configure a Pulse Width Modulation (PWM) line.
In this example, 7 PWM signals are generated with 25KHz frequency and different duty 
cycles.
The duty cycle and the pin number is displayed on the output window for each channel.
The PWM waveform can be displayed using an oscilloscope.
For more information about PWM class, see MSDN documentation.

@par Directory contents 

  - PWM_Output.csproj			 Project file.
  - PWM_Output.csproj.user		 Project options file.
  - Properties/AssemblyInfo.cs	 Application metadata.
  - Program.cs					 Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY
   boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use PWM channels PA8, PA9, PA10, PA11, PB7, PB8 and PB9
	
  - Required assemblies files:
    - System
    - System.Threading
    - Microsoft.SPOT
    - Microsoft.SPOT.Hardware
    - STM32F429I_Discovery.Netmf.Hardware.cs
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open PWM_Output.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
