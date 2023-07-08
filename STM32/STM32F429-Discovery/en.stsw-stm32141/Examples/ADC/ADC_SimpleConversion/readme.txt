/**
  @page ADC_SimpleConversion ADC_SimpleConversion
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    ADC/ADC_SimpleConversion/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the ADC_SimpleConversion Example.
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

This example describes how to use the AnalogInput class for analog-to-digital
conversion.
In this example, 4 instance of AnalogInput class that uses the 4 ADC channels on 
pin PA6, PA7, PC1 et PC3 are created and the conversion is started immediately.
The convertion results of these channels are displayed on the output window of VS2012
every one second with the green LED toggling.
You need to connect these ADC channels to external signals.  
For more information about AnalogInput class, see online MSDN documentation.

@par Directory contents 

  - ADC_SimpleConversion.csproj          Project file.
  - ADC_SimpleConversion.csproj.user     Project options file.
  - Properties/AssemblyInfo.cs			 Application metadata.
  - Program.cs							 Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY
   boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use green LED connected to PG13 pin 
	- Connect pins PA6, PA7, PC1 et PC3 to external signals

  - Required assemblies files:
    - System
    - System.Threading
    - Microsoft.SPOT
    - Microsoft.SPOT.Hardware
    - STM32F429I_Discovery.Netmf.Hardware.cs
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open ADC_SimpleConversion.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
