/**
  @page DAC_EXAMPLE DAC_EXAMPLE
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    DAC/DAC_EXAMPLE/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the DAC_DualMode Example.
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

This example describes how to use the AnalogOutput class for signal generation.
In this example, the DAC generates two sine waves in qudrautre phase. The sine wave
is stored on 512 bytes buffer and sent to the two DAC channels with quarter periode 
delay between them.
To be able to see the sine waves, connect the pins PA4 and PA5 to an oscilloscope.
For more information about AnalogOutput class, see MSDN documentation.

@par Directory contents 

  - DAC_DualMode.csproj          Project file.
  - DAC_DualMode.csproj.user     Project options file.
  - Properties/AssemblyInfo.cs	 Application metadata.
  - Program.cs					 Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY
  boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use DAC Channel 1 connected to PA4 pin
	- Use DAC Channel 2 connected to PA5 pin
	
  - Required assemblies files:
    - System
    - System.Threading
    - Microsoft.SPOT
    - Microsoft.SPOT.Hardware
    - STM32F429I_Discovery.Netmf.Hardware.cs
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open DAC_Example.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
