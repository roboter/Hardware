#region Copyright (c) 2017 DZX Designs
///	
/// GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)
///
/// This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
/// by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
///
/// This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
/// following information to ensure all requirements of the license will be met:  
/// <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.
///
#endregion Copyright (c) 2017 DZX Designs

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO.Ports;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DZX.Devices.DataLinks;
using DZX.Devices.FTDI;
using DZX.Devices.USB;

namespace DataLinkDemo
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// The connected USB device.
        /// </summary>
        private USBDevice _usbDevice;

        /// <summary>
        /// The connected FTDI device.
        /// </summary>
        private FTDIDevice _ftdiDevice;

        /// <summary>
        /// The connected serial port.
        /// </summary>
        private SerialPort _serialPort;

        /// <summary>
        /// The baud rate used for serial devices.
        /// </summary>
        private int _baudRate = 115200;

        /// <summary>
        /// The application specific data link (code generated from Data Link Editor)
        /// </summary>
        private DataLinkApp link = new DataLinkApp();

        /// <summary>
        /// Initializes a new instance of the <see cref="Form1"/> class.
        /// </summary>
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Handles the Load event of the Form1 control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void Form1_Load(object sender, EventArgs e)
        {
            Log.TextBox = textBoxLog;

            // Begin in the disconnected state
            Disconnect();

            // Start with a list of attached devices
            RefreshAttachedDevices();

            // Provide a reference of this form to have all events automatically synchronized to this thread
            link.ContainerControl = this;

            // Hook link events
            link.DeviceStatusReceived += link_DeviceStatusReceived;
        }

        /// <summary>
        /// Handles the FormClosed event of the Form1 control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="FormClosedEventArgs"/> instance containing the event data.</param>
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Disconnect();
        }

        /// <summary>
        /// Rescans for attached devices and displays them within the drop down list.
        /// </summary>
        private void RefreshAttachedDevices()
        {
            comboBoxDevices.Items.Clear();

            // Populate each type of device

            PopulateAttachedUSB();
            PopulateAttachedFTDI();
            PopulateAttachedSerial();

            if (comboBoxDevices.Items.Count > 0)
            {
                // Automatically select the first device, if any

                if (comboBoxDevices.SelectedIndex < 0)
                    comboBoxDevices.SelectedIndex = 0;
            }
            else
            {
                comboBoxDevices.Text = "None Available";
            }

            buttonConnect.Enabled = (comboBoxDevices.Items.Count > 0);
        }

        /// <summary>
        /// Searches for attached USB devices and adds them to the device drop down.
        /// </summary>
        private void PopulateAttachedUSB()
        {
            string[] paths = USBDevice.GetAttached();
            foreach (string path in paths)
            {
                using (USBDevice device = new USBDevice())
                {
                    try
                    {
                        device.Connect(path);

                        DeviceInfo info = new DeviceInfo()
                        {
                            Path = path,
                            InterfaceName = "USB",
                            Description = string.Format("[{0}] {1} {2}", device.ID, device.ManufacturerName, device.ProductName),
                        };

                        comboBoxDevices.Items.Add(info);
                    }
                    catch (USBException)
                    {
                        // Failed to connect.
                    }
                }
            }
        }

        /// <summary>
        /// Searches for attached FTDI devices and adds them to the device drop down.
        /// </summary>
        private void PopulateAttachedFTDI()
        {
            FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[] nodes = FTDIDevice.GetAttached();
            foreach (FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE node in nodes)
            {
                if (!string.IsNullOrEmpty(node.SerialNumber))
                {
                    DeviceInfo info = new DeviceInfo()
                    {
                        Node = node,
                        InterfaceName = "FTDI",
                        Description = string.Format("[{0}] {1}", node.SerialNumber, node.Description),
                    };

                    comboBoxDevices.Items.Add(info);
                }
            }
        }

        /// <summary>
        /// Searches for attached serial port devices and adds them to the device drop down.
        /// </summary>
        private void PopulateAttachedSerial()
        {
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                DeviceInfo info = new DeviceInfo()
                {
                    Port = port,
                    InterfaceName = "Serial",
                    Description = string.Format("{0}", port),
                };

                comboBoxDevices.Items.Add(info);
            }
        }

        /// <summary>
        /// Attempts to connect to the currently selected device.
        /// </summary>
        private void Connect()
        {
            Disconnect();

            // Get the information about the selected device
            DeviceInfo info = comboBoxDevices.SelectedItem as DeviceInfo;
            if (info == null)
                return;

            try
            {
                if (!string.IsNullOrEmpty(info.Path))
                {
                    _usbDevice = new USBDevice();
                    _usbDevice.Connect(info.Path);
                    link.USBDevice = _usbDevice;
                } 
                else if (info.Node != null)
                {
                    _ftdiDevice = new FTDIDevice();
                    _ftdiDevice.Connect(info.Node.SerialNumber);
                    _ftdiDevice.Baud = _baudRate;
                    link.FTDIDevice = _ftdiDevice;
                }
                else if (!string.IsNullOrEmpty(info.Port))
                {
                    _serialPort = new SerialPort(info.Port);
                    _serialPort.Open();
                    _serialPort.BaudRate = _baudRate;
                    link.SerialPort = _serialPort;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Connect Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Disconnect();
                return;
            }

            // Connected to the selected device, reflect on UI

            buttonConnect.Text = "Disconnect";

            comboBoxDevices.Enabled =
                buttonRefresh.Enabled = false;

            buttonEnableStream.Enabled =
                buttonDisableStream.Enabled =
                buttonReadMemory.Enabled = 
                buttonWriteMemory.Enabled = true;
        }

        /// <summary>
        /// Disconnects from the device
        /// </summary>
        private void Disconnect()
        {
            if (_usbDevice != null)
            {
                _usbDevice.Disconnect();
                _usbDevice.Dispose();
                _usbDevice = null;
            }

            if (_ftdiDevice != null)
            {
                _ftdiDevice.Disconnect();
                _ftdiDevice = null;
            }

            if (_serialPort != null)
            {
                if (_serialPort.IsOpen)
                    _serialPort.Close();

                _serialPort.Dispose();
                _serialPort = null;
            }

            link.USBDevice = null;
            link.FTDIDevice = null;
            link.SerialPort = null;

            buttonConnect.Text = "Connect";

            // Refresh the UI options
            comboBoxDevices.Enabled =
                    buttonRefresh.Enabled = true;

            buttonEnableStream.Enabled =
                buttonDisableStream.Enabled =
                buttonReadMemory.Enabled =
                buttonWriteMemory.Enabled = false;

            labelKernelTicks.Text = "----";
            labelKernelUtilization.Text = "----";
        }

        /// <summary>
        /// Handles the DeviceStatusReceived event of the data link component.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="DeviceStatusEventArgs"/> instance containing the event data.</param>
        private void link_DeviceStatusReceived(object sender, DeviceStatusEventArgs e)
        {
            // Display the latest values on screen

            labelKernelTicks.Text = e.KernelTicks.ToString();
            labelKernelUtilization.Text = string.Format("{0:0.00} %", (double)e.KernelUtilization / 100.0);
        }

        /// <summary>
        /// Converts and returns an integer that represents the specified text.
        /// </summary>
        /// <param name="text">The text to be converted.</param>
        /// <returns>The integer represented by the given text.</returns>
        private uint GetUserValue(string text)
        {
            if (string.IsNullOrEmpty(text))
                return 0;

            if (text.StartsWith("0x"))
                return uint.Parse(text.Replace("0x", ""), System.Globalization.NumberStyles.HexNumber);

            return uint.Parse(text);
        }

        /// <summary>
        /// Returns the write memory data bytes entered by the user.
        /// </summary>
        /// <returns></returns>
        private byte[] GetUserDataBytes()
        {
            string text = textBoxWriteData.Text;
            if (string.IsNullOrEmpty(text))
                return new byte[0];

            using (System.IO.MemoryStream stream = new System.IO.MemoryStream())
            {
                string[] values = text.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                foreach (string value in values)
                {
                    stream.WriteByte(Convert.ToByte(value, 16));
                }

                return stream.ToArray();
            }
        }


        #region Button Click Handlers

        /// <summary>
        /// Handles the Click event of the buttonReadMemory control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonReadMemory_Click(object sender, EventArgs e)
        {
            ReadMemory();
        }

        /// <summary>
        /// Handles the Click event of the buttonWriteMemory control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonWriteMemory_Click(object sender, EventArgs e)
        {
            WriteMemory();
        }

        /// <summary>
        /// Handles the Click event of the buttonEnableStream control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonEnableStream_Click(object sender, EventArgs e)
        {
            EnableStream(true);
        }

        /// <summary>
        /// Handles the Click event of the buttonDisableStream control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonDisableStream_Click(object sender, EventArgs e)
        {
            EnableStream(false);
        }

        /// <summary>
        /// Handles the Click event of the buttonRefresh control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            // Rescan and display attached devices
            RefreshAttachedDevices();
        }

        /// <summary>
        /// Handles the Click event of the buttonConnect control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if ((sender as Button).Text == "Connect")
                Connect();
            else
                Disconnect();
        }

        /// <summary>
        /// Handles the Click event of the buttonClearLog control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void buttonClearLog_Click(object sender, EventArgs e)
        {
            Log.Clear();
        }

        #endregion

        #region Device Commands

        /// <summary>
        /// Performs the EnableStatusStream command message upon the data link.
        /// </summary>
        /// <param name="enabled"><c>true</c> to enable the stream.</param>
        private void EnableStream(bool enabled)
        {
            Log.WriteLine(string.Format("EnableStatusStream({0})...", enabled));

            try
            {
                EnableStatusStreamArgs args = new EnableStatusStreamArgs();
                args.Enabled = enabled;

                link.EnableStatusStream(args);
            }
            catch (Exception ex)
            {
                Log.WriteLine(string.Format("Failed: {0}", ex.Message));
            }

            Log.WriteLine();
        }

        /// <summary>
        /// Performs the ReadMemory command message upon the data link.
        /// </summary>
        private void ReadMemory()
        {
            try
            {
                ReadMemoryRequest request = new ReadMemoryRequest();
                request.Address = GetUserValue(textBoxReadAddress.Text);
                request.Length = GetUserValue(textBoxReadLen.Text);

                Log.WriteLine(string.Format("ReadMemory(0x{0:X8}, {1})...", request.Address, request.Length));

                ReadMemoryResponse response = link.ReadMemory(request, 1000);
                if (response == null)
                {
                    Log.WriteLine("No device response");
                    Log.WriteLine();
                    return;
                }

                if (response.Result == 0)
                {
                    Log.WriteLine("Device ACK");
                    Log.WriteLine(string.Format("Received {0} bytes: {1}", response.Data.Length, BitConverter.ToString(response.Data)));
                }
                else
                {
                    Log.WriteLine(string.Format("Device NAK. Result Code: {0}", response.Result));
                }
            }
            catch (Exception ex)
            {
                Log.WriteLine(string.Format("Failed: {0}", ex.Message));
            }

            Log.WriteLine();
        }

        /// <summary>
        /// Performs the WriteMemory command message upon the data link.
        /// </summary>
        private void WriteMemory()
        {
            try
            {
                WriteMemoryRequest request = new WriteMemoryRequest();
                request.Address = GetUserValue(textBoxWriteAddress.Text);
                request.Data = GetUserDataBytes();

                Log.WriteLine(string.Format("WriteMemory(0x{0:X8}, {1})...", request.Address, request.Data.Length));

                WriteMemoryResponse response = link.WriteMemory(request, 1000);
                if (response == null)
                {
                    Log.WriteLine("No device response");
                    Log.WriteLine();
                    return;
                }

                if (response.Result == 0)
                {
                    Log.WriteLine("Device ACK");
                    Log.WriteLine(string.Format("Sent {0} bytes: {1}", request.Data.Length, BitConverter.ToString(request.Data)));
                }
                else
                {
                    Log.WriteLine(string.Format("Device NAK. Result Code: {0}", response.Result));
                }
            }
            catch (Exception ex)
            {
                Log.WriteLine(string.Format("Failed: {0}", ex.Message));
            }

            Log.WriteLine();
        }

        #endregion

    }

    /// <summary>
    /// Provides information about an attached device.
    /// </summary>
    public class DeviceInfo
    {
        public string Path { get; set; }
        public FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE Node { get; set; }
        public string Port { get; set; }

        public string InterfaceName { get; set; }
        public string Description { get; set; }

        public override string ToString()
        {
            return string.Format("[{0}] {1}", InterfaceName, Description);
        }
    }
}
