/**
  ******************************************************************************
  * @file    TouchScreen\TouchScreen\Program.cs
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

namespace TouchScreenExample
{
    /// <summary>
    /// Touch screen example.
    /// </summary>
    public class MyTouchScreen : Microsoft.SPOT.Application
    {
        /// <summary>
        /// Main window
        /// </summary>
        public class MainWindow : Window
        {
            SolidColorBrush brush = new SolidColorBrush(Color.Black);
            Text text1 = new Text();
            Text text2 = new Text();
            Panel panel = new Panel();        

            public MainWindow()
            {
                text1.TextContent = "    Touch screen   ";
                text1.TextWrap = true;
                text1.Font = Resources.GetFont(Resources.FontResources.small);
                text1.HorizontalAlignment = HorizontalAlignment.Center;
                text1.VerticalAlignment = VerticalAlignment.Bottom;

                text2.TextContent = "    Click Anywhere   ";
                text2.TextWrap = true;
                text2.Font = Resources.GetFont(Resources.FontResources.small);
                text2.HorizontalAlignment = HorizontalAlignment.Center;
                text2.VerticalAlignment = VerticalAlignment.Top;

                /* Add text control to the main window.*/
                this.Child = panel;
                panel.Children.Add(text1);
                panel.Children.Add(text2);
            }

            /* 2 images to be displayed for TouchUp and TouchDown events */
            Bitmap Img01 = Resources.GetBitmap(Resources.BitmapResources.Img1);
            Bitmap Img02 = Resources.GetBitmap(Resources.BitmapResources.Img2);

            int cx = 0;
            int cy = 0;

            bool isTouchUp = false;
            bool isTouchDown = false;

            /// <summary>
            /// Handles the touch down event.
            /// </summary>
            /// <param name="e"></param>
            protected override void OnTouchDown(TouchEventArgs e)
            {
                base.OnTouchDown(e);
                
                isTouchUp = false;
                isTouchDown = true;

                int x;
                int y;

                /* Get touch position */
                e.GetPosition((UIElement)this, 0, out x, out y);

                cx = x;
                cy = y;

                /* Update the text to show touch location */
                text1.TextContent = "Touch down detected.\nCoordinates: " + x.ToString() + "," + 
                    y.ToString();

                /* Clear the entire screen */
                Invalidate();

                e.Handled = true;
            }

            /// <summary>
            /// Handles the touch up event.
            /// </summary>
            /// <param name="e"></param>
            protected override void OnTouchUp(TouchEventArgs e)
            {
                base.OnTouchUp(e);

                /* Set the flags */
                isTouchUp = true;
                isTouchDown = false;

                int x;
                int y;

                /* Get touch position */
                e.GetPosition((UIElement)this, 0, out x, out y);
                
                cx = x;
                cy = y;

                /* Update the text to show touch location */
                text1.TextContent = "Touch up detected.\nCoordinates: " + x.ToString() + "," + 
                    y.ToString();

                e.Handled = true;
            }

            /// <summary>
            /// Handles the render event.
            /// </summary>
            /// <param name="dc"></param>
            public override void OnRender(DrawingContext dc)
            {
                base.OnRender(dc);

                /* If TouchUp flag is set, draw Img01 */
                if (isTouchUp)
                {
                    dc.DrawImage(Img01, cx - Img01.Width/2, cy - Img01.Height/2);
                }

                /* If TouchDown flag is set, draw Img02 */
                if (isTouchDown)
                {
                    dc.DrawImage(Img02, cx - Img02.Width / 2, cy - Img02.Height / 2);
                }
            }
        }

        static MyTouchScreen myApplication;

        /// <summary>
        /// Main function(entry point).
        /// </summary>
        public static void Main()
        {
            myApplication = new MyTouchScreen();

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