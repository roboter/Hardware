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
    /// Represents a function that will handle an event raised upon each completed block being
    /// downloaded to a device.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="BlockDownloadedEventArgs"/> instance containing the event data.</param>
    public delegate void BlockDownloadedEventHandler(object sender, BlockDownloadedEventArgs e);

    /// <summary>
    /// The data for an event raised upon each completed block being downloaded to a device.
    /// </summary>
    public class BlockDownloadedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of bytes that have been downloaded.
        /// </summary>
        public int BytesDownloaded { get; private set; }

        /// <summary>
        /// Gets the total number of bytes that will be downloaded.
        /// </summary>
        public int TotalBytes { get; private set; }

        /// <summary>
        /// Gets the percentage (0-100) of number of bytes that have been completed.
        /// </summary>
        public double PercentComplete
        {
            get
            {
                if (TotalBytes > 0)
                    return ((double)BytesDownloaded * 100.0) / (double)TotalBytes;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BlockDownloadedEventArgs"/> class.
        /// </summary>
        /// <param name="bytesComplete">The number of bytes that have been downloaded.</param>
        /// <param name="totalBytes">The total number of bytes to be downloaded.</param>
        public BlockDownloadedEventArgs(int bytesComplete, int totalBytes)
        {
            BytesDownloaded = bytesComplete;
            TotalBytes = totalBytes;
        }
    }

    /// <summary>
    /// Represents a function that will handle an event raised upon each completed block being
    /// uploaded from a device.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="BlockUploadedEventArgs"/> instance containing the event data.</param>
    public delegate void BlockUploadedEventHandler(object sender, BlockUploadedEventArgs e);

    /// <summary>
    /// The data for an event raised upon each completed block being uploaded from a device.
    /// </summary>
    public class BlockUploadedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of bytes that have been uploaded.
        /// </summary>
        public int BytesUploaded { get; private set; }

        /// <summary>
        /// Gets the total number of bytes that will be uploaded.
        /// </summary>
        public int TotalBytes { get; private set; }

        /// <summary>
        /// Gets the percentage (0-100) of number of bytes that have been completed.
        /// </summary>
        public double PercentComplete
        {
            get
            {
                if (TotalBytes > 0)
                    return ((double)BytesUploaded * 100.0) / (double)TotalBytes;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BlockUploadedEventArgs"/> class.
        /// </summary>
        /// <param name="bytesComplete">The number of bytes that have been uploaded.</param>
        /// <param name="totalBytes">The total number of bytes to be uploaded.</param>
        public BlockUploadedEventArgs(int bytesComplete, int totalBytes)
        {
            BytesUploaded = bytesComplete;
            TotalBytes = totalBytes;
        }
    }

    /// <summary>
    /// Represents a function that will handle an event raised upon each completed block being
    /// verified on a device.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="BlockVerifiedEventArgs"/> instance containing the event data.</param>
    public delegate void BlockVerifiedEventHandler(object sender, BlockVerifiedEventArgs e);

    /// <summary>
    /// The data for an event raised upon each completed block being verified on a device.
    /// </summary>
    public class BlockVerifiedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the number of bytes that have been verified.
        /// </summary>
        public int BytesVerified { get; private set; }

        /// <summary>
        /// Gets the total number of bytes that will be verified.
        /// </summary>
        public int TotalBytes { get; private set; }

        /// <summary>
        /// Gets the percentage (0-100) of number of bytes that have completed verification.
        /// </summary>
        public double PercentComplete
        {
            get
            {
                if (TotalBytes > 0)
                    return ((double)BytesVerified * 100.0) / (double)TotalBytes;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BlockVerifiedEventArgs"/> class.
        /// </summary>
        /// <param name="bytesComplete">The number of bytes that have been verified.</param>
        /// <param name="totalBytes">The total number of bytes to be verified.</param>
        public BlockVerifiedEventArgs(int bytesComplete, int totalBytes)
        {
            BytesVerified = bytesComplete;
            TotalBytes = totalBytes;
        }
    }
}
