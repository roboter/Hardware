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
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace DZX.DataFiles
{
    /// <summary>
    /// Provides methods for generating security keys.
    /// </summary>
    public static class Security
    {
        /// <summary>
        /// Generates and returns a key for the specified passphrase.
        /// </summary>
        /// <param name="keySize">Size of the key in bits. Valid values are 128, 192 or 256.</param>
        /// <param name="passphrase">The passphrase.</param>
        /// <returns>The generated key.</returns>
        public static byte[] GenerateKey(int keySize, string passphrase)
        {
            using (Rfc2898DeriveBytes db = new Rfc2898DeriveBytes(passphrase, new byte[8]))
            {
                return db.GetBytes(keySize / 8);
            }
        }

        /// <summary>
        /// Generates and returns a key for the specified passphrase.
        /// </summary>
        /// <param name="keySize">Size of the key in bits. Valid values are 128, 192 or 256.</param>
        /// <param name="passphrase">The passphrase.</param>
        /// <param name="salt">A salt value.</param>
        /// <returns>The generated key.</returns>
        /// <exception cref="System.ArgumentException">
        /// Value cannot be null or empty;salt
        /// or
        /// Value must contain 16 characters;salt
        /// </exception>
        public static byte[] GenerateKey(int keySize, string passphrase, string salt)
        {
            if (string.IsNullOrEmpty(salt))
                throw new ArgumentException("Value cannot be null or empty", "salt");

            if (salt.Length != 16)
                throw new ArgumentException("Value must contain 16 characters", "salt");


            // Convert the salt string into byte values
            byte[] values = new byte[8];

            for (int i = 0; i < values.Length; i++)
            {
                values[i] = byte.Parse(salt.Substring(i * 2, 2), System.Globalization.NumberStyles.HexNumber);
            }

            return GenerateKey(keySize, passphrase, values);
        }

        /// <summary>
        /// Generates and returns a key for the specified passphrase.
        /// </summary>
        /// <param name="keySize">Size of the key in bits. Valid values are 128, 192 or 256.</param>
        /// <param name="passphrase">The passphrase.</param>
        /// <param name="salt">A salt value.</param>
        /// <returns>The generated key.</returns>
        public static byte[] GenerateKey(int keySize, string passphrase, byte[] salt)
        {
            using (Rfc2898DeriveBytes db = new Rfc2898DeriveBytes(passphrase, salt))
            {
                return db.GetBytes(keySize / 8);
            }
        }
    }
}
