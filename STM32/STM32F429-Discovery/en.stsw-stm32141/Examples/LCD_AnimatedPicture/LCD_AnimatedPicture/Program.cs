/**
  ******************************************************************************
  * @file    LCD_AnimatedPicture\LCD_AnimatedPicture\Program.cs
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
using Microsoft.SPOT.Input;
using Microsoft.SPOT.Presentation;
using Microsoft.SPOT.Presentation.Media;
using Microsoft.SPOT.Presentation.Shapes;
using Microsoft.SPOT.Presentation.Controls;

namespace Microsoft.SPOT.Sample.LCD
{
    public class LCD
    {
        public static void Main()
        {
            Bitmap bitmap1 = new Bitmap(SystemMetrics.ScreenWidth, SystemMetrics.ScreenHeight);

            /* Delay between each image display*/
            int Delayms = 100;
            Bitmap Img = Resources.GetBitmap(Resources.BitmapResources.Image01);

            /* Calculate the starting X and Y coordinates for images*/
            int X_Start = (SystemMetrics.ScreenWidth - Img.Width) / 2;
            int Y_Start = (SystemMetrics.ScreenHeight - Img.Height) / 2;

            /* Display 22 images in loop with a predefined delay between them */
            while (true)
            {
                Img = Resources.GetBitmap(Resources.BitmapResources.Image01);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image02);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image03);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image04);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image05);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image06);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image07);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image08);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image09);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image10);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image11);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image12);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image13);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image14);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image15);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image16);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image17);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image18);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image19);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image20);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image21);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
                Img = Resources.GetBitmap(Resources.BitmapResources.Image22);
                bitmap1.DrawImage(X_Start, Y_Start, Img, 0, 0, Img.Width, Img.Height);
                bitmap1.Flush();
                Thread.Sleep(Delayms);
            }
        }
    }
}
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/