/**
  ******************************************************************************
  * @file    DAC\DAC_EXAMPLE\Program.cs
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
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;

namespace DAC_Example
{
    public class Program
    {
        static AnalogOutput DAC_CH0, DAC_CH1;

        public static void Main()
        {
            UInt16 SinePtsNbr = 512;
            UInt16[] SineWave = new UInt16[SinePtsNbr];
            

            /* Sine wave construction (512 samples per period) */
            for (int i = 0; i < SinePtsNbr; i++)
                SineWave[i] = (UInt16)((Microsoft.SPOT.Math.Sin((int)(360 * i / 512.0)) + 1000) * 4.095 / 2);

            /* Create an instance of AnalogOutput class and initialize the DAC:
             * DAC Channel 1 : PA.04
             * DAC Channel 2 : PA.05
             */
            DAC_CH0 = new AnalogOutput(DAC.Channel0_PA4);
            DAC_CH1 = new AnalogOutput(DAC.Channel1_PA5);

            Debug.Print("\r\nDAC example.\r\n");

            /* Generates 2 sine waves in qudrautre phase on DAC channels */
            int CH1_Phase = SinePtsNbr / 4;
            int j; 
            while (true)
            {
                for (int i = 0; i < SinePtsNbr; i++)
                {
                    /* Send Sine wave samples to DAC channel 0 (PA4) */
                    DAC_CH0.WriteRaw(SineWave[i]);

                    j = i + CH1_Phase;
                    if (j >= SinePtsNbr)
                        j -= SinePtsNbr;

                    /* Send Sine wave samples to DAC channel 1 (PA5) */
                    DAC_CH1.WriteRaw(SineWave[j]);
                }
            }
        }
    }
}
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/