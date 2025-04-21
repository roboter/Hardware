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
    /// Represents an identifier for a USB device.
    /// </summary>
    public class DeviceID : IComparable<DeviceID>
    {
        /// <summary>
        /// Gets or sets the vendor identifier.
        /// </summary>
        public ushort VendorID { get; set; }

        /// <summary>
        /// Gets or sets the product identifier.
        /// </summary>
        public ushort ProductID { get; set; }


        /// <summary>
        /// Gets or sets the serial number.
        /// </summary>
        public string SerialNumber { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceID"/> class.
        /// </summary>
        public DeviceID()
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceID"/> class.
        /// </summary>
        /// <param name="vendorID">The vendor identifier.</param>
        /// <param name="productID">The product identifier.</param>
        public DeviceID(ushort vendorID, ushort productID)
            : this()
        {
            this.VendorID = vendorID;
            this.ProductID = productID;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceID"/> class.
        /// </summary>
        /// <param name="vendorID">The vendor identifier.</param>
        /// <param name="productID">The product identifier.</param>
        /// <param name="serialNumber">The serial number.</param>
        public DeviceID(ushort vendorID, ushort productID, string serialNumber)
            : this(vendorID, productID)
        {
            this.SerialNumber = serialNumber;
        }

        /// <summary>
        /// Compares the current object with another object of the same type.
        /// </summary>
        /// <param name="other">An object to compare with this object.</param>
        /// <returns>
        /// A value that indicates the relative order of the objects being compared. The return value has the 
        /// following meanings: Value Meaning Less than zero This object is less than the <paramref name="other" /> 
        /// parameter. Zero This object is equal to <paramref name="other" />. Greater than zero This object is
        /// greater than <paramref name="other" />.
        /// </returns>
        public int CompareTo(DeviceID other)
        {
            if (other == null)
                return 1;

            // Compare vendor identifiers
            int result = VendorID.CompareTo(other.VendorID);
            if (result != 0)
                return result;

            // Compare product identifiers
            result = ProductID.CompareTo(other.ProductID);
            if (result != 0)
                return result;

            // Compare serial numbers?
            if (string.IsNullOrEmpty(other.SerialNumber))
                return 0;

            // Can't compare if this instance doesn't have a serial number
            if (string.IsNullOrEmpty(SerialNumber))
                return -1;

            // Both have serial numbers, compare them
            return SerialNumber.CompareTo(other.SerialNumber);
        }

        /// <summary>
        /// Returns a <see cref="System.String" /> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String" /> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            if (string.IsNullOrEmpty(SerialNumber))
                return string.Format("{0:X4}:{1:X4}", VendorID, ProductID); 

            return string.Format("{0:X4}:{1:X4}:{2}", VendorID, ProductID, SerialNumber);
        }

        /// <summary>
        /// Parses the identifier text into an unsigned short integer.
        /// </summary>
        /// <param name="text">The text.</param>
        /// <returns>The unsigned short that represented by the specified text.</returns>
        private static ushort ParseID(string text)
        {
            ushort value = 0;

            if (ushort.TryParse(text, System.Globalization.NumberStyles.HexNumber, null, out value))
                return value;

            return 0;
        }

        /// <summary>
        /// Creates and returns a new instance of the <see cref="DeviceID"/> class that has been
        /// initialized from the specified text representation for the identifier.
        /// </summary>
        /// <param name="text">The text representation for the identifier to be returned.</param>
        /// <returns>A <see cref="DeviceID"/> that represents the specified text.</returns>
        public static DeviceID FromText(string text)
        {
            // Valid input?
            if (!string.IsNullOrEmpty(text))
            {
                // Get the individual portions of the text (format is <vendorID>:<productID>:<serialNumber>)
                string[] ids = text.Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);

                switch (ids.Length)
                {
                    case 2:     // Only vendor and product IDs
                        return new DeviceID(ParseID(ids[0]), ParseID(ids[1]));

                    case 3:     // Includes a serial number
                        return new DeviceID(ParseID(ids[0]), ParseID(ids[1]), ids[2]);
                }
            }

            // Default identifier
            return new DeviceID();
        }
    }
}
