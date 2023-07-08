/**
  ******************************************************************************
  * @file    SPI_L3GD20\SPI_L3GD20\Program.cs
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
using Microsoft.SPOT.Input;
using Microsoft.SPOT.Presentation;
using Microsoft.SPOT.Presentation.Controls;
using Microsoft.SPOT.Presentation.Media;
using Microsoft.SPOT.Hardware;
using STM32F429I_Discovery.Netmf.Hardware;

namespace L3GD20Example
{
    /// <summary>
    /// Touch screen example.
    /// </summary>
    public class MyL3GD20Example : Microsoft.SPOT.Application
    {
        /// <summary>
        /// Main window
        /// </summary>
        public class MainWindow : Window
        {
            SolidColorBrush brush = new SolidColorBrush(Color.White);
            Text text1 = new Text();
            Text text2 = new Text();
            Panel panel = new Panel();
            private DispatcherTimer clockTimer;
            
            const int GyroThreshold = 10;

            public MainWindow()
            {
                text1.TextContent = "    L3GD20 MEMS   ";
                text1.TextWrap = true;
                text1.Font = Resources.GetFont(Resources.FontResources.small);
                text1.HorizontalAlignment = HorizontalAlignment.Center;
                text1.VerticalAlignment = VerticalAlignment.Top;

                text2.TextContent = "    L3GD20 MEMS   ";
                text2.TextWrap = true;
                text2.Font = Resources.GetFont(Resources.FontResources.small);
                text2.ForeColor = Colors.Blue;
                text2.HorizontalAlignment = HorizontalAlignment.Center;
                text2.VerticalAlignment = VerticalAlignment.Bottom;
                
                /* Add text control to the main window.*/
                this.Child = panel;
                panel.Children.Add(text1);
                panel.Children.Add(text2);
               
                /* Gyroscope initialization */
                L3GD20 = new L3GD20_SPI();
                L3GD20.Init();
                /* The board should be in an horizontal position during calibration */
                L3GD20.SimpleCalibration();

                /* Enable Timer interrput every 100ms */
                clockTimer = new DispatcherTimer(this.Dispatcher);
                clockTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
                clockTimer.Tick += new EventHandler(TimerTick);
                clockTimer.Start();

            }

            /// <summary>
            /// TimerTick: Handles clockTimer interrupt 
            /// </summary>
            void TimerTick(object sender, EventArgs e)
            {
                int XAbs = (int)System.Math.Abs(Gyro.x);
                int YAbs = (int)System.Math.Abs(Gyro.y);
                int ZAbs = (int)System.Math.Abs(Gyro.z);

                L3GD20.ReadAngRate(out Gyro);
                text2.TextContent = ("Angular rates of rotation:\n           X = " + (int)Gyro.x + " dps\n           Y = " + (int)Gyro.y + " dps\n           Z = " + (int)Gyro.z + " dps");
  
                if ((XAbs > GyroThreshold) && (XAbs > YAbs ) && (XAbs > ZAbs ))
                {
                     text1.TextContent = "  Rotating around X  ";
                }
                else if ((YAbs > GyroThreshold) && (YAbs > XAbs) && (YAbs > ZAbs)) 
                {
                    text1.TextContent = "  Rotating around Y  ";
                }
                else if ((ZAbs > GyroThreshold) && (ZAbs > XAbs ) && (ZAbs > YAbs ))
                {
                    text1.TextContent = "  Rotating around Z  ";
                }
                else
                    text1.TextContent = "Rotate the board to move the butterfly";

                /* Use the Gyro data to update the butterfly image position */
                cx = cx + (int)(Gyro.y/5);
                if (cx > SystemMetrics.ScreenWidth)
                    cx = SystemMetrics.ScreenWidth;
                cy = cy + (int)(Gyro.x/5);
                if (cy > SystemMetrics.ScreenHeight)
                    cy = SystemMetrics.ScreenHeight;

                /* Use the Gyro data to rotate the butterfly image */
                cz = cz + (int)(Gyro.z/10);
                Invalidate();
            }      

            
            /* 2 images to be displayed for TouchUp and TouchDown events */
            Bitmap Img01 = Resources.GetBitmap(Resources.BitmapResources.Img1);

            int cx = SystemMetrics.ScreenWidth/2;
            int cy = SystemMetrics.ScreenHeight/2;
            int cz = 0;

            bool isTouchDown = false;

            /// <summary>
            /// Handles the touch down event.
            /// </summary>
            /// <param name="e"></param>
            protected override void OnTouchDown(TouchEventArgs e)
            {
                base.OnTouchDown(e);
                
                isTouchDown = true;

                int x;
                int y;

                /* Get touch position */
                e.GetPosition((UIElement)this, 0, out x, out y);

                cx = x;
                cy = y;
                cz = 0;

                 /* Clear the entire screen */
                Invalidate();

                e.Handled = true;
            }

            /// <summary>
            /// Handles the render event.
            /// </summary>
            /// <param name="dc"></param>
            public override void OnRender(DrawingContext dc)
            {
                base.OnRender(dc);
                int x_Img, y_Img;

                /* Adjust image coordinates: Avoid getting out of screen */
                x_Img = (cx > (Img01.Width / 2)) ? cx - (Img01.Width / 2) : (Img01.Width / 2);
                y_Img = (cy > (Img01.Height / 2)) ? cy - (Img01.Height / 2) : (Img01.Height / 2);
                if (x_Img + (Img01.Width) > dc.Width)
                    x_Img = dc.Width - (Img01.Width);

                if (y_Img + (Img01.Height) > dc.Height)
                    y_Img = dc.Height - (Img01.Height);

                /* If TouchDown flag is set, draw Img01 at touch position */
                if (isTouchDown)
                {
                    dc.DrawImage(Img01, x_Img , y_Img);
                    isTouchDown = false;
                }

                if (cz != 0)
                {
                    /* Rotation around Z axe */
                    dc.RotateImage(cz, x_Img, y_Img, Img01, 0, 0, Img01.Width, Img01.Height, 255);
                }
                else
                {
                    dc.DrawImage(Img01, x_Img, y_Img);
                }
            }
        }

        static MyL3GD20Example myApplication;
        static L3GD20_SPI L3GD20;
        static AngDPS Gyro = new AngDPS();
        /// <summary>
        /// Main function(entry point).
        /// </summary>
        public static void Main()
        {
            myApplication = new MyL3GD20Example();

            /* Enable Touch engine */
            Microsoft.SPOT.Touch.Touch.Initialize(myApplication);

            /* Create window object */
            Window mainWindow = myApplication.CreateWindow();

            /* Start the application */
            myApplication.Run(mainWindow);
        }

        
        private MainWindow mainWindow;

        /// <summary>
        /// Create window object with button focus.
        /// </summary>
        /// <returns></returns>
        public Window CreateWindow()
        {
            /* Create window object */
            mainWindow = new MainWindow();
            mainWindow.Height = SystemMetrics.ScreenHeight;
            mainWindow.Width = SystemMetrics.ScreenWidth;
            mainWindow.Visibility = Visibility.Visible;
            Buttons.Focus(mainWindow);

            return mainWindow;
        }
    }
}
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/