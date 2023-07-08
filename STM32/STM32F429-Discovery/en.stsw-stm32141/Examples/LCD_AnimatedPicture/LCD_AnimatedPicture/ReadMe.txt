/**
  @page LCD_AnimatedPicture LCD_AnimatedPicture
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    LCD_AnimatedPicture\LCD_AnimatedPicture\readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the LCD_AnimatedPicture Example.
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

This example describes how to use the NETMF graphic library to display BMP files
on the LCD.
The example loads and displays 22 BMP images with a 100ms delay between them.These 
22 images will be diplayed in loop to display a flying butterfly on the LCD.   
For more information about NETMF graphic library, see MSDN documentation.

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
    - System.Threading;
    - Microsoft.SPOT;
    - Microsoft.SPOT.Input;
    - Microsoft.SPOT.Presentation;
    - Microsoft.SPOT.Presentation.Media;
    - Microsoft.SPOT.Presentation.Shapes;
    - Microsoft.SPOT.Presentation.Controls;
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open GPIO_Toggle.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)

 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
