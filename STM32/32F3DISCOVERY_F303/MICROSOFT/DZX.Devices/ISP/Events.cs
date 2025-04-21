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

namespace DZX.Devices.ISP
{
    /// <summary>
    /// Represents a function that handle an event that is raised for a specific sector.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
    public delegate void SectorEventHandler(object sender, SectorEventArgs e);

    /// <summary>
    /// The data for an event raised for a specific sector.
    /// </summary>
    public class SectorEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of the target sector for the event.
        /// </summary>
        public uint SectorNumber { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="SectorEventArgs"/> class.
        /// </summary>
        /// <param name="sectorNumber">The number of the target sector for the event.</param>
        public SectorEventArgs(uint sectorNumber)
        {
            this.SectorNumber = sectorNumber;
        }
    }

    /// <summary>
    /// Represents a function that will handle an event raised upon progress reports of an operation
    /// upon sectors.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="SectorProgressEventArgs"/> instance containing the event data.</param>
    public delegate void SectorProgressEventHandler(object sender, SectorProgressEventArgs e);

    /// <summary>
    /// The data for an event to report the progress of an operation upon sectors.
    /// </summary>
    public class SectorProgressEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of sectors that have completed the operation.
        /// </summary>
        public uint SectorsCompleted { get; private set; }

        /// <summary>
        /// Gets the total number of sectors that will be processed.
        /// </summary>
        public uint TotalSectors { get; private set; }

        /// <summary>
        /// Gets the percentage (0-100) of number of sectors that have been completed.
        /// </summary>
        public double PercentComplete
        {
            get
            {
                if (TotalSectors > 0)
                    return ((double)SectorsCompleted * 100.0) / (double)TotalSectors;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SectorProgressEventArgs"/> class.
        /// </summary>
        /// <param name="sectorsCompleted">The number of sectors that have completed the operation.</param>
        /// <param name="totalSectors">The total number of sectors to be processed.</param>
        public SectorProgressEventArgs(uint sectorsCompleted, uint totalSectors)
        {
            this.SectorsCompleted = sectorsCompleted;
            this.TotalSectors = totalSectors;
        }
    }

    /// <summary>
    /// Represents a function that will handle an event raised upon progress reports of a data operation.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="DataProgressEventArgs"/> instance containing the event data.</param>
    public delegate void DataProgressEventHandler(object sender, DataProgressEventArgs e);

    /// <summary>
    /// The data for an event to report the progress of a data operation.
    /// </summary>
    public class DataProgressEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of bytes that have completed the operation.
        /// </summary>
        public uint BytesCompleted { get; private set; }

        /// <summary>
        /// Gets the total number of bytes that will be processed.
        /// </summary>
        public uint TotalBytes { get; private set; }

        /// <summary>
        /// Gets the percentage (0-100) of number of data bytes that have been completed.
        /// </summary>
        public double PercentComplete
        {
            get
            {
                if (TotalBytes > 0)
                    return ((double)BytesCompleted * 100.0) / (double)TotalBytes;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataProgressEventArgs"/> class.
        /// </summary>
        /// <param name="bytesCompleted">The number of bytes that have completed the operation.</param>
        /// <param name="totalBytes">The total number of bytes to be processed.</param>
        public DataProgressEventArgs(uint bytesCompleted, uint totalBytes)
        {
            this.BytesCompleted = bytesCompleted;
            this.TotalBytes = totalBytes;
        }
    }
}
