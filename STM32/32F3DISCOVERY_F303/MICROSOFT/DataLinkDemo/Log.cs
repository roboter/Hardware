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
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataLinkDemo
{
    public static class Log
    {
        public static TextBox TextBox { get; set; }


        /// <summary>
        /// Clears the log.
        /// </summary>
        public static void Clear()
        {
            if (TextBox == null)
                return;

            TextBox.Text = "";
        }

        /// <summary>
        /// Writes a new line to the log.
        /// </summary>
        public static void WriteLine()
        {
            WriteLine(string.Empty);
        }

        /// <summary>
        /// Writes a message and a new line to the log.
        /// </summary>
        /// <param name="message">The message to be written to the log.</param>
        public static void WriteLine(string message)
        {
            if (TextBox == null)
                return;

            TextBox.AppendText(message + Environment.NewLine);
        }
    }
}
