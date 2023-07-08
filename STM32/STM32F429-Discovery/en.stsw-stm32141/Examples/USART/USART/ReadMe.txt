/**
  @page USART
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    USART/USART/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the USART Example.
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

This example demonstrates how to use the SerialPort class to carry out a 
serial communication.
In this example, the Serial port used is COM1 which uses the STM32F429 USART1 
peripheral ( Rx pin: PA10 ,Tx pin: PA9).

To run this example you can load the program on tow boards and connects their 
Rx pins to the Tx Pins , or you can use one board and connect RX pin to Tx pin for 
loopback mode communication.
First, a message is sent stored in the outBuffer[] array via Tx pin. The interrupt 
routine "DataReceived_Interrupt" is called when the serial port receive data on 
the Rx pin. The data receievd is stored in the inBuffer[] then compared to the outBuffer.
If data matches, the green led is toggled On. Otherwise, the red LED is switched On.  
For more information about SerialPort class, see MSDN documentation.

@par Directory contents 

  - EXTI.csproj                 VS2012 Project file.
  - EXTI.csproj.user            Project options file.
  - Properties/AssemblyInfo.cs  Application metadata.
  - Program.cs                  Main program

@par Hardware and Software environment 

  - This example has been tested with STMicroelectronics STM32F429I-DISCOVERY boards.

  - STM32F429I-DISCOVERY Set-up 
    - Use green LED connected to PG13 pin 
	- Use red LED connected to PG14 pin 
    - Connect USART1 Rx Pin PA10 to Tx pin PA9 for loopback communication

  - Required assemblies files:
    - System;
    - System.Text;
    - Microsoft.SPOT;
    - Microsoft.SPOT.Input;
    - Microsoft.SPOT.Presentation;
    - Microsoft.SPOT.Presentation.Controls;
    - Microsoft.SPOT.Presentation.Media;
    - Microsoft.SPOT.Hardware;
    - System.IO.Ports;
    - STM32F429I_Discovery.Netmf.Hardware;
    
@par How to use it ? 

In order to make the program work, you should do the following:
 - Open EXTI.csproj project.
 - Rebuild all files: Build->Build Solution
 - Load and Run program: Debug->Run(F5)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
