/**
  ******************************************************************************
  * @file    USART\USART\Program.cs
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
using System.Text;
using Microsoft.SPOT;
using Microsoft.SPOT.Input;
using Microsoft.SPOT.Presentation;
using Microsoft.SPOT.Presentation.Controls;
using Microsoft.SPOT.Presentation.Media;
using Microsoft.SPOT.Hardware;
using System.IO.Ports;
using STM32F429I_Discovery.Netmf.Hardware;

namespace USARTExample
{
    /// <summary>
    /// Touch screen example.
    /// </summary>
    public class MyUSARTExample : Microsoft.SPOT.Application
    {
        /// <summary>
        /// Main window
        /// </summary>
        public class MainWindow : Window
        {
            SolidColorBrush brush = new SolidColorBrush(Color.White);
            Text text1 = new Text();
            Text text2 = new Text();
            Text help = new Text();
            Panel panel = new Panel();

            static SerialPort serialPort;
            const int GyroThreshold = 10;
            static int NbrReceivedBytes = 0;
            static byte[] outBuffer = Encoding.UTF8.GetBytes("RS232 communication using COM1(USART1)\r\n");
            static byte[] inBuffer = new byte[outBuffer.Length];
            static bool isDataReceived = false;

            public MainWindow()
            {
                text1.TextContent = "RS232 communication example";
                text1.TextWrap = true;
                text1.Font = Resources.GetFont(Resources.FontResources.small);
                text1.HorizontalAlignment = HorizontalAlignment.Center;
                text1.VerticalAlignment = VerticalAlignment.Top;

                text2.TextContent = "No data received!";
                text2.TextWrap = true;
                text2.Font = Resources.GetFont(Resources.FontResources.small);
                text2.ForeColor = Colors.Blue;
                text2.Width = SystemMetrics.ScreenWidth;
                text2.HorizontalAlignment = HorizontalAlignment.Left;
                text2.VerticalAlignment = VerticalAlignment.Center;

                help.TextContent = "Connect the RX pin (PA10) and Tx pin (PA9) for loopback communication.";
                help.TextWrap = true;
                help.Font = Resources.GetFont(Resources.FontResources.small);
                help.ForeColor = Colors.Black;
                help.Width = SystemMetrics.ScreenWidth;
                help.HorizontalAlignment = HorizontalAlignment.Left;
                help.VerticalAlignment = VerticalAlignment.Bottom;

                /* Add text control to the main window.*/
                this.Child = panel;
                panel.Children.Add(text1);
                panel.Children.Add(text2);
                panel.Children.Add(help);

                /* Configure LEDs. */
                LED.LEDInit();

                /* Configure the USART1 (COM1):
                 * BaudRate = 9600 baud  
                 * Word Length = 8 Bits (default settings)
                 * One Stop Bit         (default settings)
                 * Parity none          (default settings)
                 * Hardware flow control disabled (default settings)
                 */
                serialPort = new SerialPort(SerialPorts.SerialCOM1, 9600);

                /* Register the DataReceived interrupt handler*/
                serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceived_Interrupt);

                /* Open USART1 (COM1) */
                serialPort.Open();

                /* Send a message via COM1 */
                serialPort.Write(outBuffer, 0, outBuffer.Length);

            }
                    
            /* Data reception interrupt handler */
            internal void DataReceived_Interrupt(object com, SerialDataReceivedEventArgs arg)
            {
                /*Read received data */
                NbrReceivedBytes += serialPort.Read(inBuffer, NbrReceivedBytes, inBuffer.Length - NbrReceivedBytes);

                /* Display the received data */
                text2.Dispatcher.BeginInvoke(new DispatcherOperationCallback(delegate
                {
                    text2.TextContent = "Data received:\n";
                    for(int i=0;i<NbrReceivedBytes;i++)
                    text2.TextContent += (char)inBuffer[i];
                    return null;
                }), text2);
                
                /* if we didn't receive the whole outBuffer exit the interrupt handler */
                if (NbrReceivedBytes < outBuffer.Length)
                    return;

                /* Compare the inBuffer and outBuffer */
                if (CmpBuffers(inBuffer,outBuffer,inBuffer.Length))
                {
                    /* Toggle green LED */
                    LED.GreenLedOn();
                }
                else
                {
                    /* Toggle red LED */
                    LED.RedLedOn();
                }
            }

            /// <summary>
            /// Compare two byte buffers.
            /// </summary>
            /// <param name="Buf1">1st buffer</param>
            /// <param name="Buf2">2nd buffer</param>
            /// <param name="Length">Data length (in bytes) to be compared</param>
            static bool CmpBuffers(byte[] Buf1, byte[] Buf2,int Length )
            {
                for (int i = 0; i < Length; i++)
                {
                    if (Buf1[i] != Buf2[i])
                        return false;
                }
                return true;
            }
        

            /// <summary>
            /// Handles the render event.
            /// </summary>
            /// <param name="dc"></param>
            public override void OnRender(DrawingContext dc)
            {
                base.OnRender(dc);
            }
        }

        static MyUSARTExample myApplication;
        /// <summary>
        /// Main function(entry point).
        /// </summary>
        public static void Main()
        {
            myApplication = new MyUSARTExample();

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