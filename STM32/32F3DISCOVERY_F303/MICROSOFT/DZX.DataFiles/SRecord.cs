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
using System.IO;
using System.Linq;
using System.Text;

namespace DZX.DataFiles.SRecord
{
    /// <summary>
    /// Represents a single line within an S-Record file.
    /// </summary>
    internal class SRecordLine
    {
        /// <summary>
        /// Creates and initializes a new instance of the <see cref="SRecordLine"/> class.
        /// </summary>
        public SRecordLine() { }

        /// <summary>
        /// Creates and initializes a new instance of the <see cref="SRecordLine"/> class from
        /// the specified text.
        /// </summary>
        /// <param name="text">The initial text for the line.</param>
        public SRecordLine(string text)
            : this()
        {
            Text = text;
        }

        /// <summary>
        /// Gets and sets the starting address for the line.
        /// </summary>
        public int Address { get; set; }

        /// <summary>
        /// Gets and sets the data for the line.
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// Gets the total length in bytes of data for the line.
        /// </summary>
        public int DataLength { get { return GetDataLength(); } }

        /// <summary>
        /// Gets and sets the size of the address field for the line.
        /// </summary>
        public AddressSize AddressSize { get; set; }

        /// <summary>
        /// Gets and sets the type field for the line.
        /// </summary>
        public LineType Type { get; set; }

        /// <summary>
        /// Gets an indication the CRC was valid when the line was parsed from it's text
        /// representation.
        /// </summary>
        /// <remarks>Only valid after setting the <see cref="Text" /> field for the line.</remarks>
        public bool IsCRCValid { get; private set; }

        /// <summary>
        /// Gets and sets the text representation for the line.
        /// </summary>
        public string Text
        {
            get { return GetText(); }
            set { SetText(value); }
        }

        /// <summary>
        /// Builds and returns the text representation for the s-record line.
        /// </summary>
        /// <returns>The current instance line's text representation.</returns>
        private string GetText()
        {
            StringBuilder line = new StringBuilder("S");

            // Apply the type and address size of line
            switch (Type)
            {
                case LineType.Header:
                    line.Append("0");
                    break;
                case LineType.DataSequence:
                    switch (AddressSize)
                    {
                        case AddressSize.As16bit:
                            line.Append("1");
                            break;
                        case AddressSize.As24bit:
                            line.Append("2");
                            break;
                        case AddressSize.As32bit:
                            line.Append("3");
                            break;
                    }
                    break;
                case LineType.RecordCount:
                    line.Append("5");
                    break;
                case LineType.EndOfBlock:
                    switch (AddressSize)
                    {
                        case AddressSize.As32bit:
                            line.Append("7");
                            break;
                        case AddressSize.As24bit:
                            line.Append("8");
                            break;
                        case AddressSize.As16bit:
                            line.Append("9");
                            break;
                    }
                    break;
            }

            // Apply the data length
            int datalength = GetAddressSize();
            if (Data != default(byte[]))
            {
                datalength += Data.Length;
            }

            // Account for crc in length
            datalength++;

            line.Append(string.Format("{0:X2}", datalength));

            // Apply the address
            switch (AddressSize)
            {
                case AddressSize.As16bit:
                    line.Append(string.Format("{0:X4}", Address));
                    break;
                case AddressSize.As24bit:
                    line.Append(string.Format("{0:X6}", Address));
                    break;
                case AddressSize.As32bit:
                    line.Append(string.Format("{0:X8}", Address));
                    break;
            }

            // Apply the data
            if (Data != default(byte[]))
            {
                foreach (byte data in Data)
                {
                    line.Append(string.Format("{0:X2}", data));
                }
            }

            // Apply the crc
            line.Append(string.Format("{0:X2}", CalcCRC()));

            return line.ToString();
        }

        /// <summary>
        /// Sets the line's values from the specified text representation for the s-record line.
        /// </summary>
        /// <param name="text">The text representation for the line.</param>
        private void SetText(string text)
        {
            // Find the 'S' within the text
            int index = text.IndexOf('S');
            if (index >= 0)
            {
                // Move to the next character
                index++;

                // Assign the type of line
                switch (text[index])
                {
                    case '0':
                        Type = LineType.Header;
                        break;
                    case '1':
                        Type = LineType.DataSequence;
                        AddressSize = AddressSize.As16bit;
                        break;
                    case '2':
                        Type = LineType.DataSequence;
                        AddressSize = AddressSize.As24bit;
                        break;
                    case '3':
                        Type = LineType.DataSequence;
                        AddressSize = AddressSize.As32bit;
                        break;
                    case '5':
                        Type = LineType.RecordCount;
                        break;
                    case '7':
                        Type = LineType.EndOfBlock;
                        AddressSize = AddressSize.As32bit;
                        break;
                    case '8':
                        Type = LineType.EndOfBlock;
                        AddressSize = AddressSize.As24bit;
                        break;
                    case '9':
                        Type = LineType.EndOfBlock;
                        AddressSize = AddressSize.As16bit;
                        break;
                }

                // Move to the next character
                index++;

                // Assign the data
                switch (Type)
                {
                    case LineType.Header:
                    case LineType.DataSequence:
                    case LineType.EndOfBlock:
                        // Get the data length
                        unchecked
                        {
                            byte dataLength = (byte)(Convert.ToByte(text.Substring(index, 2), 16) - GetAddressSize() - 1);

                            index += 2;

                            // Get the address field
                            switch (AddressSize)
                            {
                                case AddressSize.As16bit:
                                    Address = Convert.ToInt32(text.Substring(index, 4), 16);
                                    index += 4;
                                    break;
                                case AddressSize.As24bit:
                                    Address = Convert.ToInt32(text.Substring(index, 6), 16);
                                    index += 6;
                                    break;
                                case AddressSize.As32bit:
                                    Address = Convert.ToInt32(text.Substring(index, 8), 16);
                                    index += 8;
                                    break;
                            }

                            // Create and read the data
                            Data = new byte[dataLength];

                            for (int i = 0; i < dataLength; i++)
                            {
                                Data[i] = Convert.ToByte(text.Substring(index, 2), 16);

                                index += 2;
                            }

                            // Verify the crc
                            byte providedCrc = Convert.ToByte(text.Substring(index, 2), 16);

                            if (providedCrc == CalcCRC())
                            {
                                IsCRCValid = true;
                            }
                            else
                            {
                                IsCRCValid = false;
                            }
                        }
                        break;
                }
            }
        }

        /// <summary>
        /// Gets the total number of bytes of data contained within the line.
        /// </summary>
        /// <returns>The number of bytes of data within the line.</returns>
        private int GetDataLength()
        {
            if (Data != default(byte[]))
            {
                return Data.Length;
            }

            return 0;
        }

        /// <summary>
        /// Gets the size in bytes for the address field.
        /// </summary>
        /// <returns>The size of the address field in bytes.</returns>
        private int GetAddressSize()
        {
            switch (AddressSize)
            {
                case AddressSize.As16bit:
                    return 2;
                case AddressSize.As24bit:
                    return 3;
                case AddressSize.As32bit:
                    return 4;
                default:
                    return 0;
            }
        }

        /// <summary>
        /// Calculates the crc for the current line data.
        /// </summary>
        /// <returns>The crc for the current line data.</returns>
        private byte CalcCRC()
        {
            unchecked
            {
                byte value = (byte)(GetAddressSize() + GetDataLength() + 1);

                // Accumulate the address field
                for (int i = 0; i < GetAddressSize(); i++)
                {
                    value += (byte)(Address >> (8 * i));
                }

                // Accumulate the data fields
                if (Data != default(byte[]))
                {
                    foreach (byte data in Data)
                    {
                        value += data;
                    }
                }

                return (byte)(~value);
            }
        }

        /// <summary>
        /// Gets the text representation for the s-record line.
        /// </summary>
        /// <returns>The s-record line's text representation.</returns>
        public override string ToString() { return Text; }

        /// <summary>
        /// Creates and initializes a new instance of the <see cref="SRecordLine"/> class from
        /// the specified text.
        /// </summary>
        /// <param name="text">The text to be used to initialize the line.</param>
        public static SRecordLine Parse(string text) { return new SRecordLine(text); }
    }

    /// <summary>
    /// Represents a type of line within an S-Record file.
    /// </summary>
    internal enum LineType
    {
        /// <summary>
        /// Represents an unknown line type.
        /// </summary>
        Unknown,

        /// <summary>
        /// Represents a header line.
        /// </summary>
        Header,

        /// <summary>
        /// Represents a line of data.
        /// </summary>
        DataSequence,

        /// <summary>
        /// Represents a line that contains a count of records.
        /// </summary>
        RecordCount,

        /// <summary>
        /// Represents a line that is the end of a block.
        /// </summary>
        EndOfBlock,
    };

    /// <summary>
    /// Represents the size of the address field within an S-Record line.
    /// </summary>
    internal enum AddressSize
    {
        /// <summary>
        /// An unknown address size.
        /// </summary>
        Unknown,

        /// <summary>
        /// An address field that is 16-bits in size.
        /// </summary>
        As16bit,

        /// <summary>
        /// An address field that is 24-bits in size.
        /// </summary>
        As24bit,

        /// <summary>
        /// An address field that is 32-bits in size.
        /// </summary>
        As32bit,
    };
}
