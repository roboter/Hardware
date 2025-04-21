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

namespace DZX.Devices.USB
{
    /// <summary>
    /// Represents the possible transfer types for a pipe.
    /// </summary>
    public enum TransferType
    {
        /// <summary>
        /// Represents a control endpoint transfer.
        /// </summary>
        Control,

        /// <summary>
        /// Represents an isochronous transfer.
        /// </summary>
        Isochronous,

        /// <summary>
        /// Represents a bulk transfer.
        /// </summary>
        Bulk,

        /// <summary>
        /// Represents an interrupt transfer.
        /// </summary>
        Interrupt
    }

    /// <summary>
    /// Represents information about a pipe implemented by a <see cref="USBDevice"/>.
    /// </summary>
    public class PipeInfo
    {
        /// <summary>
        /// Gets or sets the identifier number for the pipe.
        /// </summary>
        public byte ID { get; set; }

        /// <summary>
        /// Gets or sets the type of transfers implemented by the pipe.
        /// </summary>
        public TransferType TransferType { get; set; }

        /// <summary>
        /// Gets or sets the interval period for the pipe.
        /// </summary>
        public byte Interval { get; set; }

        /// <summary>
        /// Gets or sets the maximum size of packets supported by the pipe.
        /// </summary>
        public ushort MaxPacketSize { get; set; }
    }
}
