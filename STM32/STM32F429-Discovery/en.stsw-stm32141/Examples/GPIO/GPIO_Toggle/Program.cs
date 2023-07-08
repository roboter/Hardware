/**
  ******************************************************************************
  * @file    GPIO\GPIO_Toggle\Program.cs
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
  ******************************************************************************
  */

/* References ------------------------------------------------------------------*/
using System.Threading;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;


public class BlinkingLed
{
    public static void Main()
    {
        LED.LEDInit(); // Init LED GPIOs

        while (true)
        {
            LED.GreenLedToggle();  // Tooggle green led
            Thread.Sleep(250);   // wait 250 ms

            LED.RedLedToggle();    // Tooggle red led
            Thread.Sleep(250);   // wait 250 ms
        }
    }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/