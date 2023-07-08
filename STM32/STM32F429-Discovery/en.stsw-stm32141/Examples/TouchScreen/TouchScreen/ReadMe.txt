/**
  @page TouchScreen TouchScreen
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    TouchScreen\TouchScreen\readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the TouchScreen Example.
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

This example describes how to use the NETMF TouchScreen feature.
The LCD Touch panel is connected to the STMPE811QTR IO expnader which is connected
to the STM32F429 by I2C3. The driver of STMPE811QTR is implemented in HAL level and its
data is delivered to the NETMF TouchScreen library.

When touching the Touch panel, two events occurs: Touch Down and then Touch Up.
In this example the coordinates of the touch is displayed on LCD and a butterfly image is
drawn at the touch position. When Touch down event occurs, a butterfly with partially closed
wings is displayed and in the touch up event, a butterfly with open wings is displayed.       
For more information about TouchScreen features, see MSDN documentation.

@par Directory contents 

  - GPIO_Toggle.csproj          Project file.
  - GPIO_Toggle.csproj.user     Project options file.
  - Properties/AssemblyInfo.cs  Application metadata.
  - Program.cs                  Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY
   boards.

  - STM32F429I-DISCOVERY Set-up 
    - None

  - Required assemblies files:
    - System;
    - Microsoft.SPOT;
    - Microsoft.SPOT.Input;
    - Microsoft.SPOT.Presentation;
    - Microsoft.SPOT.Presentation.Controls;
    - Microsoft.SPOT.Presentation.Media;
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open GPIO_Toggle.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)

 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
