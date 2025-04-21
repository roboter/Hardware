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

namespace DZX.DataFiles.Hex
{
    /// <summary>
    /// Represents a line within an Intel HEX file.
    /// </summary>
    internal class HexLine
    {
        /// <summary>
        /// Creates and initializes a new instance of the <see cref="HexLine"/> class.
        /// </summary>
        public HexLine() { }

        /// <summary>
        /// Creates and initializes a new instance of the <see cref="HexLine"/> class from
        /// the specified text.
        /// </summary>
        /// <param name="text">The text to be used to initialize the line.</param>
        public HexLine(string text)
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
        /// Gets and sets the type field for the line.
        /// </summary>
        public HexLineType Type { get; set; }

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
            StringBuilder line = new StringBuilder(":");

            unchecked
            {
                // Apply the type and address size of line
                line.AppendFormat("{0:X2}", (byte)GetDataLength());

                line.AppendFormat("{0:X4}", (ushort)Address);

                line.AppendFormat("{0:X2}", (byte)Type);

                if (GetDataLength() > 0)
                {
                    foreach (byte b in Data)
                    {
                        line.AppendFormat("{0:X2}", b);
                    }
                }

                line.AppendFormat("{0:X2}", CalcCRC());

            }

            return line.ToString();
        }

        /// <summary>
        /// Sets the line's values from the specified text representation for the s-record line.
        /// </summary>
        /// <param name="text">The text representation for the line.</param>
        private void SetText(string text)
        {
            // Find the ':' within the text
            int index = text.IndexOf(':');
            if (index >= 0)
            {
                // Move to the next character
                index++;

                // Next 2 bytes specify the length of data for the line
                int dataLength = Convert.ToByte(text.Substring(index, 2), 16);
                index += 2;

                // Next 4 bytes specified the 16-bit address
                Address = Convert.ToUInt16(text.Substring(index, 4), 16);
                index += 4;

                Type = (HexLineType)Convert.ToByte(text.Substring(index, 2), 16);
                index += 2;

                // Create and read the data
                Data = new byte[dataLength];

                for (int i = 0; i < dataLength; i++)
                {
                    Data[i] = Convert.ToByte(text.Substring(index, 2), 16);
                    index += 2;
                }

                // Verify the crc
                byte providedCrc = Convert.ToByte(text.Substring(index, 2), 16);
                IsCRCValid = (providedCrc == CalcCRC());
            }
        }

        /// <summary>
        /// Gets the total number of bytes of data contained within the line.
        /// </summary>
        /// <returns>The number of bytes of data within the line.</returns>
        private int GetDataLength()
        {
            if (Data != default(byte[]))
                return Data.Length;

            return 0;
        }

        /// <summary>
        /// Calculates the crc for the current line data.
        /// </summary>
        /// <returns>The crc for the current line data.</returns>
        private byte CalcCRC()
        {
            unchecked
            {
                byte value = (byte)GetDataLength();

                for (int i = 0; i < 4; i++)
                {
                    value += (byte)(Address >> (8 * i));
                }

                value += (byte)Type;

                if (GetDataLength() > 0)
                {
                    foreach (byte b in Data)
                    {
                        value += b;
                    }
                }

                return (byte)((~value) + 1);
            }
        }

        /// <summary>
        /// Gets the text representation for the Intel HEX line.
        /// </summary>
        /// <returns>The line's text representation.</returns>
        public override string ToString() { return Text; }

        /// <summary>
        /// Creates and initializes a new instance of the <see cref="HexLine"/> class from
        /// the specified text.
        /// </summary>
        /// <param name="text">The text to be used to initialize the line.</param>
        public static HexLine Parse(string text) { return new HexLine(text); }
    }

    /// <summary>
    /// Represents a type of line within an Intel HEX file.
    /// </summary>
    internal enum HexLineType : byte
    {
        /// <summary>
        /// Represents a data line.
        /// </summary>
        DataRecord = 0,

        /// <summary>
        /// Represents the end of the file.
        /// </summary>
        EndOfFile,

        /// <summary>
        /// Represents a line that provides an extension of the address for bits 4-19 of the address.
        /// </summary>
        ExtendedSegmentAddress,

        /// <summary>
        /// Represents a starting address field.
        /// </summary>
        StartSegmentAddress,

        /// <summary>
        /// Represents a line that provides an extension of the address for bits 16-31 of the address.
        /// </summary>
        ExtendedLinearAddress,

        /// <summary>
        /// Represents a starting address field.
        /// </summary>
        StartLinearAddress,
    };

}
