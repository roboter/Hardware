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
using DZX.DataFiles;
using DZX.Devices;
using DZX.Devices.FTDI;
using DZX.Devices.ISP;

namespace ISPDemo
{
    public partial class Form1 : Form
    {
        private PortSettings portSettings = new PortSettings();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Default port settings
            portSettings.Baud = 57600;
            portSettings.DataBits = 8;
            portSettings.StopBits = StopBits.One;
            portSettings.Parity = Parity.None;
            portSettings.Handshake = Handshake.None;

            // Initialize list of supported device types
            foreach (ISPDeviceType type in Enum.GetValues(typeof(ISPDeviceType)))
                comboBoxTypes.Items.Add(type);

            if (comboBoxTypes.Items.Count > 0)
                comboBoxTypes.SelectedIndex = 0;

            // Initialize list of attached devices
            RefreshAttachedDevices();
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            RefreshAttachedDevices();
        }

        /// <summary>
        /// Refreshes the drop down of available devices
        /// </summary>
        private void RefreshAttachedDevices()
        {
            comboBoxDevices.Items.Clear();

            // Get the attached FTDI devices
            FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[] nodes = ISPDevice.GetAttachedAsFTDI();
            foreach (FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE node in nodes)
            {
                DeviceInfo info = new DeviceInfo() { Node = node };
                comboBoxDevices.Items.Add(info);
            }

            // Get the standard serial port devices
            string[] ports = ISPDevice.GetAttachedAsCOM();
            foreach (string port in ports)
            {
                DeviceInfo info = new DeviceInfo() { COM = port };
                comboBoxDevices.Items.Add(info);
            }

            // Automatically select the first device
            if (comboBoxDevices.Items.Count > 0)
            {
                if (comboBoxDevices.SelectedIndex < 0)
                    comboBoxDevices.SelectedIndex = 0;
            }
            else
            {
                comboBoxDevices.Text = "None Available";
            }
        }

        /// <summary>
        /// Clears the log.
        /// </summary>
        private void ClearLog()
        {
            textBoxLog.Text = "";
            Application.DoEvents();
        }

        /// <summary>
        /// Appends a message to the log.
        /// </summary>
        /// <param name="message">The message.</param>
        private void AppendLog(string message)
        {
            textBoxLog.AppendText(message);
        }

        /// <summary>
        /// Appends a message as a new line to the log.
        /// </summary>
        /// <param name="message">The message.</param>
        private void AppendLogLine(string message)
        {
            textBoxLog.AppendText(message + Environment.NewLine);
        }

        private void buttonDownload_Click(object sender, EventArgs e)
        {
            ClearLog();

            if (System.IO.File.Exists(textBoxDownloadFile.Text))
            {
                try
                {
                    DeviceInfo info = comboBoxDevices.SelectedItem as DeviceInfo;
                    if (info != null)
                    {
                        // Open the data file
                        DataFile file = DataFile.FromFile(textBoxDownloadFile.Text);

                        using (ISPDevice device = new ISPDevice())
                        {
                            // Configure the serial port settings
                            device.Baud = portSettings.Baud;
                            device.DataBits = portSettings.DataBits;
                            device.StopBits = portSettings.StopBits;
                            device.Parity = portSettings.Parity;
                            device.Handshake = portSettings.Handshake;

                            // Check if a specific device type has been specified
                            if (comboBoxTypes.SelectedItem is ISPDeviceType)
                            {
                                ISPDeviceType type = (ISPDeviceType)comboBoxTypes.SelectedItem;
                                if (type != ISPDeviceType.Unknown)
                                {
                                    // Assign the user specified target type
                                    device.Target = ISPTarget.FromDeviceType(type);
                                }
                            }

                            // Connect with FTDI or standard serial port
                            if (info.Node != null)
                                device.Connect(info.Node);
                            else
                                device.Connect(info.COM);

                            // Hook events to receive updates about the download progress
                            device.SectorErasing += device_SectorErasing;
                            device.SectorErased += device_SectorErased;
                            device.SectorProgramming += device_SectorProgramming;
                            device.SectorProgrammed += device_SectorProgrammed;

                            // Enter ISP mode
                            AppendLogLine("Invoking ISP mode...");
                            device.InvokeISP();
                            AppendLogLine("Device in ISP mode");


                            if (device.Target != null)
                            {
                                // Device type has been detected
                                AppendLogLine(string.Format("Device identified as '{0}'", device.Target.DeviceType));
                            }

                            device.Download((uint)file.Address, file.GetBytes());
                            AppendLogLine("Download complete");

                            RefreshAttachedDevices();
                        }
                    }
                    else
                    {
                        AppendLogLine("No device selected");
                    }
                }
                catch (ISPException uex)
                {
                    AppendLogLine(string.Format("ISP Error: {0}", uex.Message));
                }
                catch (Exception ex)
                {
                    AppendLogLine(string.Format("Error: {0}", ex.Message));
                }
            }
            else
            {
                MessageBox.Show(this, "The specified file does not exist", "Select a File", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        
        void device_SectorProgramming(object sender, SectorEventArgs e)
        {
            AppendLog(string.Format("Programming sector {0}... ", e.SectorNumber));
        }

        void device_SectorProgrammed(object sender, SectorEventArgs e)
        {
            AppendLogLine("Done.");
        }

        void device_SectorErasing(object sender, SectorEventArgs e)
        {
            AppendLog(string.Format("Erasing sector {0}... ", e.SectorNumber));
        }

        void device_SectorErased(object sender, SectorEventArgs e)
        {
            AppendLogLine("Done.");
        }

        private void buttonDownloadBrowse_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dialog = new OpenFileDialog())
            {
                dialog.Filter = "Data Files | *.bin;*.hex;*.srec";

                if (dialog.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                {
                    textBoxDownloadFile.Text = dialog.FileName;
                }
            }
        }

        private void buttonPortSettings_Click(object sender, EventArgs e)
        {
            using (FormPortSettings form = new FormPortSettings())
            {
                form.PortSettings = portSettings;
                form.ShowDialog(this);
            }
        }

        internal class DeviceInfo
        {
            public string COM { get; set; }
            public FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE Node { get; set; }

            public override string ToString()
            {
                if (Node != null)
                    return string.Format("FTDI: {0} - {1}", Node.Description, Node.SerialNumber);

                return string.Format("Serial Port: {0}", COM);
            }
        }
    }

    public class ISPDeviceTypeItem
    {
        public ISPDeviceTypeItem()
        {

        }

        public ISPDeviceType Type { get; set; }
        public string Text { get; set; }

        public ISPDeviceTypeItem(ISPDeviceType type, string text)
        {
            Type = type;
            Text = text;
        }
    }

    public class PortSettings
    {
        public int Baud { get; set; }
        public int DataBits { get; set; }
        public StopBits StopBits { get; set; }
        public Parity Parity { get; set; }
        public Handshake Handshake { get; set; }
    }
}
