/**
  @page SPI_L3GD20 SPI_L3GD20
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    SPI_L3GD20\SPI_L3GD20\readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the SPI_L3GD20 Example.
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

This example describes how to use the NETMF SPI interface allowing the STM32F429 to
communicate with an external device.
The SPI5 perihperal of the STM32F429 is connected to the L3GD20 gyroscope.
the STM32F429I_Discovery.Netmf.Hardware namespace contains an L3GD20_SPI class that 
provides needed methods to configure, calibrate and to read the gyroscope data.
In this example, the L3GD20 is used to retrieve the board rotation rate on the three 
axes(X, Y and Z) and to move a butterfly image accordingly. 
The TouchScreen feature is used to reinitialize the butterfly image position.
The board should be in an horizontal position during gyroscope calibration.
For more information about SPI and TouchScreen features, see MSDN documentation.

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
