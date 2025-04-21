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

namespace ISPDemo
{
    public partial class FormPortSettings : Form
    {
        private PortSettings settings = new PortSettings();

        public PortSettings PortSettings
        {
            get
            {
                int baud = 0;

                if (int.TryParse(textBoxBaud.Text, out baud))
                    settings.Baud = baud;
                else
                    settings.Baud = 9600;


                settings.DataBits = (int)comboBoxDataBits.SelectedItem;
                settings.StopBits = (StopBits)comboBoxStopBits.SelectedItem;
                settings.Parity = (Parity)comboBoxParity.SelectedItem;
                settings.Handshake = (Handshake)comboBoxHandshake.SelectedItem;

                return settings;
            }

            set
            {
                settings = value;
                textBoxBaud.Text = value.Baud.ToString();
                comboBoxDataBits.Select<int>(value.DataBits);
                comboBoxStopBits.Select<StopBits>(value.StopBits);
                comboBoxParity.Select<Parity>(value.Parity);
                comboBoxHandshake.Select<Handshake>(value.Handshake);
            }
        }

        public FormPortSettings()
        {
            InitializeComponent();

            // Load possible values in drop downs

            comboBoxDataBits.Items.Add(8);
            comboBoxDataBits.Items.Add(7);
            comboBoxDataBits.Items.Add(6);
            comboBoxDataBits.Items.Add(5);

            comboBoxStopBits.Items.Add(StopBits.None);
            comboBoxStopBits.Items.Add(StopBits.One);
            comboBoxStopBits.Items.Add(StopBits.OnePointFive);
            comboBoxStopBits.Items.Add(StopBits.Two);

            comboBoxParity.Items.Add(Parity.None);
            comboBoxParity.Items.Add(Parity.Even);
            comboBoxParity.Items.Add(Parity.Mark);
            comboBoxParity.Items.Add(Parity.Odd);
            comboBoxParity.Items.Add(Parity.Space);

            comboBoxHandshake.Items.Add(Handshake.None);
            comboBoxHandshake.Items.Add(Handshake.RequestToSend);
            comboBoxHandshake.Items.Add(Handshake.RequestToSendXOnXOff);
            comboBoxHandshake.Items.Add(Handshake.XOnXOff);
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            settings = PortSettings;
            DialogResult = System.Windows.Forms.DialogResult.OK;
            Close();
        }
    }

    internal static class ComboBoxSelector
    {
        public static void Select<T>(this ComboBox comboBox, T value)
        {
            foreach (T item in comboBox.Items)
            {
                if (item.Equals(value))
                {
                    comboBox.SelectedItem = value;
                    return;
                }
            }

            if (comboBox.Items.Count > 0)
                comboBox.SelectedIndex = 0;
        }
    }
}
