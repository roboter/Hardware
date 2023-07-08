/**
  @page GPIO_Toggle GPIO_Toggle
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    GPIO/GPIO_Toggle/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the GPIO_Toggle Example.
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

This example describes how to use the OutputPort class for GPIO toggling.
The OutputPort class allow you to configure GPIO pin as output and change its state.
The LED class defined in the STM32F429I_Discovery.Netmf.Hardware namespace is used to 
drive the boards LEDs. The LED.LEDInit() function is used to configure the GPIO pin 
as output push-Pull and the two LEDs (green and red LEDs) will be toggling every 500ms 
in an infinite loop.
For more information about OutputPort class, see MSDN 
documentation.


@par Directory contents 

  - GPIO_Toggle.csproj          Project file.
  - GPIO_Toggle.csproj.user     Project options file.
  - Properties/AssemblyInfo.cs  Application metadata.
  - Program.cs                  Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY
   boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use green LED connected to PG13 pin
	- Use red LED connected to PG14 pin  

  - Required assemblies files:
    - System
    - System.Threading
    - Microsoft.SPOT.Hardware
    - STM32F429I_Discovery.Netmf.Hardware.cs
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open GPIO_Toggle.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)

 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
