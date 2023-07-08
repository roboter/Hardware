/**
  ******************************************************************************
  * @file    External Interrupt\External Interrupt\Program.cs
  * @author  MCD
  * @version V1.0.0
  * @date    19-August-2013
  * @brief   Main program body
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
  */

/* References ------------------------------------------------------------------*/

using System;
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;

namespace EXTI
{
    public class Program
    {
        public static void Main()
        {
            /* Init LED GPIOs */
            LED.LEDInit(); 

            /* Configure PA.0 as external interrupt for High edge.
             * The User button is connected to PA.0 pin with a pulldown resistor.
             */
            InterruptPort USER_Button = new InterruptPort((Cpu.Pin)0,
                                         false, 
                                         Port.ResistorMode.PullDown,
                                         Port.InterruptMode.InterruptEdgeHigh);

            /* Register the external interrupt handler */
            USER_Button.OnInterrupt += new NativeEventHandler(port_OnInterrupt);

            /* wait forever */
            Thread.Sleep(Timeout.Infinite);
        }

        /* InterruptPort interrupt handler */
        static void port_OnInterrupt(UInt32 port, UInt32 state, DateTime time)
        {
            Debug.Print("USER Button pressed\n");
            LED.GreenLedToggle();
        }
    }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/