/**
  ******************************************************************************
  * @file    ADC\ADC_SimpleConversion\Program.cs
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
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  */

/* References ------------------------------------------------------------------*/
using System;
using Microsoft.SPOT;
using System.Threading;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;

namespace ADC_Example
{
    public class Program
    {
        public static void Main()
        {
            /* Initialize ADC channel 0 (PA6) */
            AnalogInput ADC0 = new AnalogInput(ADC.Channel0_PA6);

            /* Initialize ADC channel 1 (PA7) */
            AnalogInput ADC1 = new AnalogInput(ADC.Channel1_PA7);

            /* Initialize ADC channel 2 (PC1) */
            AnalogInput ADC2 = new AnalogInput(ADC.Channel2_PC1);

            /* Initialize ADC channel 3 (PC3) */
            AnalogInput ADC3 = new AnalogInput(ADC.Channel3_PC3);

            /* Initialize LEDs */
            LED.LEDInit();

            while (true)
            {  
                /* Display the ADC converted value */
                Debug.Print("Channel0 (pin " + ADC0.Pin + ") = " + (ADC0.Read() * 3.3).ToString("f2") + "V");
                Debug.Print("Channel1 (pin " + ADC1.Pin + ") = " + (ADC1.Read() * 3.3).ToString("f2") + "V");
                Debug.Print("Channel2 (pin " + ADC2.Pin + ") = " + (ADC2.Read() * 3.3).ToString("f2") + "V");
                Debug.Print("Channel3 (pin " + ADC3.Pin + ") = " + (ADC3.Read() * 3.3).ToString("f2") + "V");
                Debug.Print("\r\n--------------------------------\r\n");

                /* Wait for 1s */
                Thread.Sleep(1000);

                /* Toggle Green LED */
                LED.GreenLedToggle();
            }
        }
    }
}
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/