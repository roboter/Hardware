/**
  ******************************************************************************
  * @file    PWM\PWM_Output\Program.cs
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
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
  */

/* References ------------------------------------------------------------------*/
using System;
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;

namespace MFTest
{
    public class Program
    {
        public static void Main()
        {
            UInt32 Frequency = 25000; 

             /* Configure PWM lines */
             /* PWM0 pin       : PA8
              * PWM0 frequency : 25 KHz
              * PWM0 duty cycle: 25%
              */
            PWM PWM0 = new PWM(PWM_Channels.PWM0_PA8, Frequency, 0.25, false);
            /* PWM1 pin       : PA9
             * PWM1 frequency : 25 KHz
             * PWM1 duty cycle: 50%
             */
            PWM PWM1 = new PWM(PWM_Channels.PWM1_PA9, Frequency, 0.50, false);
            /* PWM2 pin       : PA10
             * PWM2 frequency : 25 KHz
             * PWM2 duty cycle: 75%
             */
            PWM PWM2 = new PWM(PWM_Channels.PWM2_PA10,Frequency, 0.75, false);
            /* PWM pins      : PA11, PB7, PB8 and PB9
             * PWM frequency : 25 KHz
             * PWM duty cycle: 95%
             */
            PWM PWM3 = new PWM(PWM_Channels.PWM3_PA11, Frequency, 0.95, false);
            PWM PWM4 = new PWM(PWM_Channels.PWM4_PB7, Frequency, 0.95, false);
            PWM PWM5 = new PWM(PWM_Channels.PWM5_PB8, Frequency, 0.95, false);
            PWM PWM6 = new PWM(PWM_Channels.PWM6_PB9, Frequency, 0.95, false);

            /* Start generating PWM signals */
            PWM0.Start();
            PWM1.Start();
            PWM2.Start();
            PWM3.Start();
            PWM4.Start();
            PWM5.Start();
            PWM6.Start();

            /* Display the current duty cycle */
            Debug.Print("PWM0 : Pin= " + PWM0.Pin + ", Duty cycle = " + PWM0.DutyCycle * 100 + "% ");
            Debug.Print("PWM1 : Pin= " + PWM1.Pin + ", Duty cycle = " + PWM1.DutyCycle * 100 + "% ");
            Debug.Print("PWM2 : Pin= " + PWM2.Pin + ", Duty cycle = " + PWM2.DutyCycle * 100 + "% ");
            Debug.Print("PWM3 : Pin= " + PWM3.Pin + ", Duty cycle = " + PWM3.DutyCycle * 100 + "% ");
            Debug.Print("PWM4 : Pin= " + PWM4.Pin + ", Duty cycle = " + PWM4.DutyCycle * 100 + "% ");
            Debug.Print("PWM5 : Pin= " + PWM5.Pin + ", Duty cycle = " + PWM5.DutyCycle * 100 + "% ");
            Debug.Print("PWM6 : Pin= " + PWM6.Pin + ", Duty cycle = " + PWM6.DutyCycle * 100 + "% ");
            Debug.Print("\r\n------------------------------------------\r\n\r\n");              

            /* Infinite loop */
            Thread.Sleep(Timeout.Infinite);      
        }
    }
}
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/