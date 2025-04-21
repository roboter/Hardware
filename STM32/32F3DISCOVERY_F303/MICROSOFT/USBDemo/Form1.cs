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
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DZX.DataFiles;
using DZX.Devices.USB;

namespace USBDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshAttachedDevices();
        }

        private void ClearLog()
        {
            textBoxLog.Text = "";
        }

        private void AppendLog(string message)
        {
            textBoxLog.AppendText(message + Environment.NewLine);
        }

        private void RefreshAttachedDevices()
        {
            comboBoxDevices.Items.Clear();

            string[] paths = USBDevice.GetAttached();
            foreach (string path in paths)
            {
                try
                {
                    using (USBDevice device = new USBDevice())
                    {
                        device.Connect(path);

                        DeviceInfo info = new DeviceInfo()
                        {
                            Path = path,
                            ID = device.ID,
                            Name = string.Format("{0} - {1}", device.ManufacturerName, device.ProductName),
                        };

                        comboBoxDevices.Items.Add(info);
                    }
                }
                catch (USBException)
                {
                    // Failed to retrieve info about the device
                }
            }

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

        private string GetSelectedDevicePath()
        {
            DeviceInfo info = comboBoxDevices.SelectedItem as DeviceInfo;
            if (info != null)
                return info.Path;

            return "";
        }

        #region Test Connection Methods
        private void buttonTestConnection_Click(object sender, EventArgs e)
        {
            ClearLog();

            try
            {
                string path = GetSelectedDevicePath();
                if (!string.IsNullOrEmpty(path))
                {
                    using (USBDevice device = new USBDevice())
                    {
                        // Connect to the device
                        device.Connect(path);

                        AppendLog("Device connected");

                        // Create a random message
                        byte[] msg = new byte[10];

                        Random rand = new Random();
                        rand.NextBytes(msg);


                        // Send the message to the device
                        device.Write(msg, 1000);

                        AppendLog(string.Format("Random message '{0}' sent to device", BitConverter.ToString(msg)));

                        // Expecting the device to echo the message, so attempt to read it's response
                        byte[] response = device.Read(1000);
                        if (response != null)
                        {
                            if (msg.SequenceEqual(response))
                            {
                                // The device responded with exactly the same message that was sent
                                AppendLog(string.Format("The device responded with '{0}'", BitConverter.ToString(response)));
                                AppendLog("Successful connection");
                            }
                            else
                            {
                                // The device responded with a different message than was sent
                                AppendLog(string.Format("The device responded with '{0}'", BitConverter.ToString(response)));
                                AppendLog("Incorrect response");
                            }
                        }
                        else
                        {
                            // The device did not send back a message
                            AppendLog("The device failed to respond");
                        }
                    }
                }
                else
                {
                    AppendLog("No device selected");
                }
            }
            catch (USBException ex)
            {
                AppendLog(string.Format("USB Error: {0}", ex.Message));
            }
        }
        #endregion

        #region Download Methods
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

        private void buttonDownload_Click(object sender, EventArgs e)
        {
            ClearLog();

            if (System.IO.File.Exists(textBoxDownloadFile.Text))
            {
                try
                {
                    string path = GetSelectedDevicePath();
                    if (!string.IsNullOrEmpty(path))
                    {
                        // Open the data file
                        DataFile file = DataFile.FromFile(textBoxDownloadFile.Text);

                        using (USBDevice device = new USBDevice())
                        {
                            // Connect to the device
                            device.Connect(path);

                            // Hook events to receive updates about the download progress
                            device.DetachRequested += device_DetachRequested;
                            device.DetachCompleted += device_DetachCompleted;
                            device.Downloading += device_Downloading;

                            device.Download(file.GetBytes());

                            AppendLog("Download complete");
                        }

                        RefreshAttachedDevices();
                    }
                    else
                    {
                        AppendLog("No device selected");
                    }
                }
                catch (USBException uex)
                {
                    AppendLog(string.Format("USB Error: {0}", uex.Message));
                }
                catch (Exception ex)
                {
                    AppendLog(string.Format("Error: {0}", ex.Message));
                }
            }
            else
            {
                MessageBox.Show(this, "The specified file does not exist", "Select a File", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        void device_DetachCompleted(object sender, DFUDetachEventArgs e)
        {
            AppendLog(string.Format("Device is in {0} mode", e.Mode == DFUMode.Bootloader ? "bootloader" : "runtime"));
            Application.DoEvents();
        }

        void device_DetachRequested(object sender, DFUDetachEventArgs e)
        {
            AppendLog(string.Format("Requesting device to enter {0} mode", e.Mode == DFUMode.Bootloader ? "bootloader" : "runtime"));
            Application.DoEvents();
        }

        void device_Downloading(object sender, BlockDownloadedEventArgs e)
        {
            AppendLog(string.Format("Downloading... {0:0}% Complete", e.PercentComplete));
            Application.DoEvents();
        }
        #endregion

        private void textBoxDownloadFile_TextChanged(object sender, EventArgs e)
        {
            buttonDownload.Enabled = System.IO.File.Exists((sender as TextBox).Text);
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            RefreshAttachedDevices();
        }
    }

    public class DeviceInfo
    {
        public string Path { get; set; }
        public DeviceID ID { get; set; }
        public string Name { get; set; }

        public override string ToString()
        {
            return string.Format("[{0}] {1}", ID, Name);
        }
    }
}
