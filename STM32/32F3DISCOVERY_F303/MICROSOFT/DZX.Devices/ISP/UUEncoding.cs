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
    /// Provides methods for encoding and decoding data using the UUEncoding standard.
    /// <seealso href="https://en.wikipedia.org/wiki/Uuencoding">https://en.wikipedia.org/wiki/Uuencoding</seealso>
    /// </summary>
    public static class UUEncoding
    {
        /// <summary>
        /// Encodes the specified data.
        /// </summary>
        /// <param name="data">The data to be encoded.</param>
        /// <returns>The encoded string representation of the given data.</returns>
        public static string GetString(byte[] data)
        {
            return GetString(data, 0, data.Length);
        }

        /// <summary>
        /// Encodes the specified data.
        /// </summary>
        /// <param name="data">The data to be encoded.</param>
        /// <param name="offset">An offset into the data to begin encoding.</param>
        /// <param name="length">The total number of bytes to be encoded.</param>
        /// <returns>The encoded string representation of the given data.</returns>
        public static string GetString(byte[] data, int offset, int length)
        {
            StringBuilder sb = new StringBuilder();

            sb.Append(EncodeCharacter((byte)length));

            int total = 0;

            while (total < length)
            {
                int idx = offset + total;

                byte b1 = data[idx + 0];
                byte b2 = ((idx + 1) < data.Length) ? data[idx + 1] : (byte)0;
                byte b3 = ((idx + 2) < data.Length) ? data[idx + 2] : (byte)0;

                sb.Append(EncodeCharacter((byte)((b1 & 0xFC) >> 2)));
                sb.Append(EncodeCharacter((byte)(((b1 & 0x03) << 4) | ((b2 & 0xF0) >> 4))));
                sb.Append(EncodeCharacter((byte)(((b2 & 0x0F) << 2) | ((b3 & 0xC0) >> 6))));
                sb.Append(EncodeCharacter((byte)(b3 & 0x3F)));

                total += 3;
            }

            return sb.ToString();
        }

        /// <summary>
        /// Encodes a single character.
        /// </summary>
        /// <param name="value">The character value to be encoded.</param>
        /// <returns>The encoded character that represents the given value.</returns>
        private static char EncodeCharacter(byte value)
        {
            if (value == 0)
                return Convert.ToChar((byte)0x60);

            return Convert.ToChar((byte)(value + 0x20));
        }

        /// <summary>
        /// Decodes all of the specified characters into a sequence of bytes.
        /// </summary>
        /// <param name="s">The string to be decoded into a sequence of bytes.</param>
        /// <returns>The decoded data bytes from the specified string.</returns>
        public static byte[] GetBytes(string s)
        {
            return GetBytes(s, 0, s.Length);
        }

        /// <summary>
        /// Decodes the specified characters into a sequence of bytes.
        /// </summary>
        /// <param name="s">The string representation to be decoded.</param>
        /// <param name="offset">An offset into the data to begin decoding.</param>
        /// <param name="length">The total number of characters to be decoded.</param>
        /// <returns>The decoded data bytes from the specified string.</returns>
        public static byte[] GetBytes(string s, int offset, int length)
        {
            List<byte> data = new List<byte>();

            int len = DecodeCharacter(s[offset]);

            int total = 1;

            while (total < length)
            {
                int idx = offset + total;

                byte b1 = DecodeCharacter(s[idx + 0]);
                byte b2 = DecodeCharacter(s[idx + 1]);
                byte b3 = DecodeCharacter(s[idx + 2]);
                byte b4 = DecodeCharacter(s[idx + 3]);

                data.Add((byte)((b1 << 2) | ((b2 & 0x30) >> 4)));

                if (data.Count < len)
                    data.Add((byte)(((b2 & 0x0F) << 4) | ((b3 & 0x3C) >> 2)));

                if (data.Count < len)
                    data.Add((byte)(((b3 & 0x03) << 6) | b4));

                total += 4;
            }

            return data.ToArray();
        }

        /// <summary>
        /// Decodes a single character.
        /// </summary>
        /// <param name="ch">The character to be decoded.</param>
        /// <returns>The decoded value for the specified character.</returns>
        private static byte DecodeCharacter(char ch)
        {
            byte value = Convert.ToByte(ch);
            if (value == 0x60)
                return 0;

            return (byte)(value - 0x20);
        }
    }
}
