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
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using DZX.DataFiles.Hex;
using DZX.DataFiles.SRecord;

namespace DZX.DataFiles
{
    /// <summary>
    /// Represents a generic data file.
    /// </summary>
    public class DataFile
    {
        private MemoryStream _stream = new MemoryStream();

        /// <summary>
        /// The individual sections of data for this file.
        /// </summary>
        private List<DataFileSection> _sections = new List<DataFileSection>();

        /// <summary>
        /// Gets or sets the number of bytes per line that is used when saving a file in either the
        /// s-record or hex format.
        /// </summary>
        public int BytesPerLine { get; set; }

        /// <summary>
        /// Gets or sets the reset vector address for the data file.
        /// </summary>
        public int ResetVector { get; set; }

        /// <summary>
        /// Gets the base (starting) address of data for this file.
        /// </summary>
        public int Address
        {
            get
            {
                if (_sections.Count > 0)
                    return _sections[0].Address;

                return 0;
            }
        }

        /// <summary>
        /// Gets the length, in bytes, for the data represented by this file.
        /// </summary>
        public int Length
        {
            get
            {
                if (_sections.Count == 0)
                    return 0;

                return _sections.Sum(s => s.Length);
            }
        }

        /// <summary>
        /// Gets the last address of data for this file.
        /// </summary>
        public int EndAddress
        {
            get
            {
                if (_sections.Count == 0)
                    return 0;

                return _sections.Max(s => s.EndAddress);
            }
        }

        /// <summary>
        /// Gets or sets the DFU suffix for the file.
        /// </summary>
        public DFUSuffix DFUInfo { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataFile"/> class.
        /// </summary>
        public DataFile()
        {
            BytesPerLine = 16;
        }

        /// <summary>
        /// Finds and returns a section that contains the specified address.
        /// </summary>
        /// <param name="address">The target address.</param>
        /// <returns>A data file section that contains the specified address if it exists; otherwise null.</returns>
        private DataFileSection Find(int address)
        {
            return _sections.FirstOrDefault(s => s.Contains(address));
        }

        /// <summary>
        /// Finds and returns a section that contains the specified address range.
        /// </summary>
        /// <param name="address">The starting address of the range.</param>
        /// <param name="length">The total number of bytes of the range.</param>
        /// <returns>A data file section that contains the specified address range if it exists; otherwise null.</returns>
        private DataFileSection Find(int address, int length)
        {
            return _sections.FirstOrDefault(s => s.Contains(address, length));
        }

        /// <summary>
        /// Finds and returns the section that contains the specified address. If none exists, it returns
        /// the section that follows the specified address if one exists.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <returns>
        /// The section that contains the specified address, if any; otherwise the section that follows the
        /// specified address, if any; otherwise null.
        /// </returns>
        private DataFileSection FindOrNext(int address)
        {
            for (int i = 0; i < _sections.Count; i++)
                if (_sections[i].Address >= address)
                    return _sections[i];

            return null;
        }

        /// <summary>
        /// Gets the inferred format from a file extension.
        /// </summary>
        /// <param name="path">The path that contains the file extension to be used to infer the format.</param>
        /// <returns>The format that should be used for the specified file extension.</returns>
        public static DataFileFormat GetFormatFromExtension(string path)
        {
            string ext = Path.GetExtension(path);
            if (!string.IsNullOrEmpty(ext))
            {
                switch (ext.ToLower())
                {
                    case ".bin":
                        return DataFileFormat.Binary;
                    case ".srec":
                    case ".s19":
                    case ".s28":
                    case ".s37":
                        return DataFileFormat.SRecord;
                    case ".hex":
                        return DataFileFormat.Hex;
                    case ".dfu":
                        return DataFileFormat.DFU;
                }
            }

            return DataFileFormat.Unknown;
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified file.
        /// </summary>
        /// <param name="path">The file system path to be opened.</param>
        /// <returns>A data file that has been initialized from the specified file.</returns>
        /// <remarks>
        /// Automatically determines the format of the specified file based upon
        /// the file's extension.
        /// </remarks>
        public static DataFile FromFile(string path)
        {
            return FromFile(GetFormatFromExtension(path), path);
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified file.
        /// </summary>
        /// <param name="format">The format to be used when reading the specified file.</param>
        /// <param name="path">The file system path to be opened.</param>
        /// <returns>A data file that has been initialized from the specified file.</returns>
        /// <exception cref="System.InvalidOperationException">The specified format is unknown.</exception>
        /// <exception cref="System.NotSupportedException">The specified format is not supported.</exception>
        public static DataFile FromFile(DataFileFormat format, string path)
        {
            switch (format)
            {
                case DataFileFormat.Unknown:
                    throw new InvalidOperationException("The specified format is unknown");

                case DataFileFormat.Binary:
                    return FromBinary(path);

                case DataFileFormat.SRecord:
                    return FromSRecord(path);

                case DataFileFormat.Hex:
                    return FromHex(path);

                case DataFileFormat.DFU:
                    return FromDFU(path);
                    
            }

            throw new NotSupportedException("The specified format is not supported");
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified binary file.
        /// </summary>
        /// <param name="path">The path of the binary file used to initialize the data file.</param>
        /// <returns>A data file initialized from the specified file.</returns>
        private static DataFile FromBinary(string path)
        {
            DataFile file = new DataFile();
            DataFileSection section = new DataFileSection(0, File.ReadAllBytes(path));
            file._sections.Add(section);
            return file;
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified S-Record file.
        /// </summary>
        /// <param name="path">The path of the S-Record file used to initialize the data file.</param>
        /// <returns>A data file initialized from the specified file.</returns>
        private static DataFile FromSRecord(string path)
        {
            DataFile file = new DataFile();

            // Open the specified file
            using (StreamReader reader = new StreamReader(path))
            {
                while (!reader.EndOfStream)
                {
                    // Read each line...
                    string text = reader.ReadLine();
                    if (!string.IsNullOrEmpty(text))
                    {
                        // Access the line as an S-Record
                        SRecordLine line = new SRecordLine(text);

                        switch (line.Type)
                        {
                            case SRecord.LineType.DataSequence:
                                file.Write(line.Address, line.Data);
                                break;

                            case SRecord.LineType.EndOfBlock:
                                file.ResetVector = line.Address;
                                break;
                        }

                    }
                }
            }

            return file;
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified hex file.
        /// </summary>
        /// <param name="path">The path of the hex file used to initialize the data file.</param>
        /// <returns>A data file initialized from the specified file.</returns>
        private static DataFile FromHex(string path)
        {
            DataFile file = new DataFile();

            short upperAddress = 0;

            HexStreamState state = HexStreamState.Normal;

            // Open the specified file
            using (StreamReader reader = new StreamReader(path))
            {
                while (!reader.EndOfStream)
                {
                    // Read each line...
                    string text = reader.ReadLine();
                    if (!string.IsNullOrEmpty(text))
                    {
                        // Access the line as hex format
                        HexLine line = new HexLine(text);

                        switch (line.Type)
                        {
                            case HexLineType.ExtendedSegmentAddress:
                                // The data represents bits 16-31 of the address field.
                                if (line.DataLength == 2)
                                {
                                    // Endian swap since the address is now coming from data bytes rather than the input text
                                    upperAddress = BitConverter.ToInt16(line.Data.Reverse().ToArray(), 0);
                                    state = HexStreamState.ExtendedSegmentAddressing;
                                }
                                break;

                            case HexLineType.ExtendedLinearAddress:
                                // The data represents bits 16-31 of the address field.
                                if (line.DataLength == 2)
                                {
                                    // Endian swap since the address is now coming from data bytes rather than the input text
                                    upperAddress = BitConverter.ToInt16(line.Data.Reverse().ToArray(), 0);
                                    state = HexStreamState.ExtendedLinearAddressing;
                                }
                                break;

                            case HexLineType.DataRecord:
                                switch (state)
                                {
                                    case HexStreamState.ExtendedLinearAddressing:
                                        line.Address = (upperAddress << 16) | line.Address;
                                        break;
                                    case HexStreamState.ExtendedSegmentAddressing:
                                        line.Address = (upperAddress << 4) + line.Address;
                                        break;
                                }

                                file.Write(line.Address, line.Data);
                                break;
                            case HexLineType.StartLinearAddress:
                                if (line.DataLength >= 4)
                                    file.ResetVector = BitConverter.ToInt32(line.Data.Reverse().ToArray(), 0);
                                break;
                        }
                    }
                }
            }

            return file;
        }

        internal enum HexStreamState
        {
            /// <summary>
            /// Normal state.
            /// </summary>
            Normal,

            /// <summary>
            /// Indicates stream is using extended linear addressing.
            /// </summary>
            ExtendedLinearAddressing,

            /// <summary>
            /// Indicates stream is using extended segment address.
            /// </summary>
            ExtendedSegmentAddressing,

            /// <summary>
            /// Indicates stream is using linear addressing.
            /// </summary>
            LinearAddressing,
        }

        /// <summary>
        /// Creates and returns a data file initialized from the specified device firmware update (DFU) file.
        /// </summary>
        /// <param name="path">The path of the DFU file used to initialize the data file.</param>
        /// <returns>A data file initialized from the specified file.</returns>
        private static DataFile FromDFU(string path)
        {
            DataFile file = new DataFile();

            // Read as a standard binary file
            DataFileSection section = new DataFileSection(0, File.ReadAllBytes(path));

            if (section.Length > DFUSuffix.BinarySize)
            {
                // Attempt to read the DFU suffix
                byte[] suffix = section.Read(section.Length - DFUSuffix.BinarySize, DFUSuffix.BinarySize);

                // Attempt to parse the suffix
                file.DFUInfo = DFU.FromBuffer(suffix);
                if (file.DFUInfo != null)
                {
                    // Parse successfully, remove suffix from the actual image
                    section.Resize(section.Length - DFUSuffix.BinarySize);
                }
            }
            

            file._sections.Add(section);
            return file;
        }

        /// <summary>
        /// Saves this instance data file to the specified file path.
        /// </summary>
        /// <param name="path">The file path to save this data file to.</param>
        /// <remarks>
        /// Automatically determines the format of the specified file based upon
        /// the file path's extension.
        /// </remarks>
        public void Save(string path)
        {
            Save(GetFormatFromExtension(path), path);
        }

        /// <summary>
        /// Saves this instance data file to the specified file path.
        /// </summary>
        /// <param name="format">The format used to save the data file.</param>
        /// <param name="path">The file path to save this data file to.</param>
        /// <exception cref="System.InvalidOperationException">The specified format is unknown</exception>
        /// <exception cref="System.NotSupportedException">The specified format is not supported</exception>
        public void Save(DataFileFormat format, string path)
        {
            switch (format)
            {
                case DataFileFormat.Unknown:
                    throw new InvalidOperationException("The specified format is unknown");

                case DataFileFormat.Binary:
                    File.WriteAllBytes(path, GetBytes());
                    break;

                case DataFileFormat.SRecord:
                    SaveSRecord(path);
                    break;

                case DataFileFormat.Hex:
                    SaveHex(path);
                    break;

                case DataFileFormat.DFU:
                    SaveDFU(path);
                    break;

                default:
                    throw new NotSupportedException("The specified format is not supported");
            } 
        }

        /// <summary>
        /// Saves this instance data file to the specified file path in an S-Record format.
        /// </summary>
        /// <param name="path">The path to save this file.</param>
        private void SaveSRecord(string path)
        {
            SRecordLine line = new SRecordLine();

            using (StreamWriter writer = new StreamWriter(path))
            {
                line.Type = LineType.Header;
                line.Address = 0;
                line.AddressSize = AddressSize.As16bit;
                line.Data = Encoding.ASCII.GetBytes(Path.GetFileName(path));

                writer.WriteLine(line.ToString());

                foreach (DataFileSection section in _sections)
                {
                    int total = 0;

                    while (total < section.Length)
                    {
                        int len = section.Length - total;
                        if (len > BytesPerLine)
                            len = BytesPerLine;

                        line.Address = section.Address + total;

                        // Calc the number of bits required for the address
                        line.AddressSize = AddressSize.As16bit;

                        if (line.Address > 65535)
                            line.AddressSize = AddressSize.As24bit;

                        if (line.Address > 16777215)
                            line.AddressSize = AddressSize.As32bit;

                        // Get the data for the line
                        line.Data = section.Read(total, len);
                        line.Type = LineType.DataSequence;

                        writer.WriteLine(line.ToString());

                        total += len;
                    }
                }

                line.Type = LineType.EndOfBlock;
                line.Address = ResetVector;
                line.Data = null;

                writer.WriteLine(line.ToString());
            }
        }

        /// <summary>
        /// Saves this instance data file to the specified file path in a hex format.
        /// </summary>
        /// <param name="path">The path to save this file.</param>
        private void SaveHex(string path)
        {
            HexStreamState state = HexStreamState.Normal;
            short upperAddress = 0;

            HexLine line = new HexLine();

            using (StreamWriter writer = new StreamWriter(path))
            {
                foreach (DataFileSection section in _sections)
                {
                    int total = 0;

                    while (total < section.Length)
                    {
                        int len = section.Length - total;
                        if (len > BytesPerLine)
                            len = BytesPerLine;

                        line.Address = section.Address + total;

                        if (line.Address > 0xFFFF)
                        {
                            // Check if the upper address needs to be placed into the file
                            if (upperAddress != (line.Address >> 16))
                            {
                                upperAddress = (short)(line.Address >> 16);

                                // Write a line to go to extended addressing
                                HexLine extendedLine = new HexLine();

                                extendedLine.Address = 0;
                                extendedLine.Type = HexLineType.ExtendedLinearAddress;
                                extendedLine.Data = BitConverter.GetBytes(upperAddress).Reverse().ToArray();

                                writer.WriteLine(extendedLine.ToString());

                                // Indicate that the stream is now in extended addressing mode
                                state = HexStreamState.ExtendedLinearAddressing;
                            }
                        }

                        if (state == HexStreamState.ExtendedLinearAddressing)
                        {
                            // Only supply lower portion of the address
                            line.Address = line.Address & 0x0000FFFF;
                        }

                        line.Data = section.Read(total, len);
                        line.Type = HexLineType.DataRecord;

                       // Buffer.BlockCopy(section.Data, total, line.Data, 0, len);

                        writer.WriteLine(line.ToString());

                        total += len;
                    }
                }

                line.Type = HexLineType.StartLinearAddress;
                line.Address = 0;
                line.Data = BitConverter.GetBytes(ResetVector).Reverse().ToArray();
                writer.WriteLine(line.ToString());

                line.Type = HexLineType.EndOfFile;
                line.Address = 0;
                line.Data = null;
                writer.WriteLine(line.ToString());
            }
        }

        /// <summary>
        /// Saves this instance data file to the specified file path in a DFU format.
        /// </summary>
        /// <param name="path">The path to save this file.</param>
        private void SaveDFU(string path)
        {
            byte[] original = GetBytes();

            byte[] data = new byte[original.Length + 16];
            Buffer.BlockCopy(original, 0, data, 0, original.Length);

            DFU.AppendSuffix(data, original.Length, DFUInfo);
            File.WriteAllBytes(path, data);   
        }

        /// <summary>
        /// Gets the bytes that represent this file.
        /// </summary>
        /// <returns>An array of the bytes that represent this file.</returns>
        public byte[] GetBytes()
        {
            return Read(Address, EndAddress - Address + 1);
        }

        /// <summary>
        /// Reads and returns data from the specified address.
        /// </summary>
        /// <param name="address">The starting address to be read.</param>
        /// <param name="length">The length in bytes to be read.</param>
        /// <returns>An array of the data that has been read.</returns>
        public byte[] Read(int address, int length)
        {
            return Read(address, length, 0xFF);
        }

        /// <summary>
        /// Reads and returns data from the specified address.
        /// </summary>
        /// <param name="address">The starting address to be read.</param>
        /// <param name="length">The length in bytes to be read.</param>
        /// <param name="fillValue">The value used if there is no definition for a particular address.</param>
        /// <returns>An array of the data that has been read.</returns>
        public byte[] Read(int address, int length, byte fillValue)
        {
            byte[] data = new byte[length];

            // Perform default fill if specified
            if (fillValue != 0)
                for (int k = 0; k < length; k++)
                    data[k] = fillValue;


            int total = 0;

            foreach (DataFileSection section in _sections)
            {
                int len = 0;

                // Attempt to read from this section
                section.Read(address, data, length, out len);

                // Keep track of total read
                total += len;

                // Exit if done
                if (total == length)
                    return data;
            }
                
            return data;
        }

        /// <summary>
        /// Writes data to this file at the specified address.
        /// </summary>
        /// <param name="address">The starting address to be written.</param>
        /// <param name="data">The data to be written to the file.</param>
        public void Write(int address, params byte[] data)
        {
            DataFileSection section = _sections.FirstOrDefault(s => address >= s.Address && address <= (s.Address + s.Length));
            if (section == null)
            {
                // No section contains the specified address
                // Create a new section and write the contiguous data to it

                section = new DataFileSection();

                section.Address = address;
                section.Write(address, data);


                // Add the new section and sort in order of addressing
                _sections.Add(section);

                
            }
            else
            {
                // Found a section that contains the address, write to it
                section.Write(address, data);
            }

            // Find the section that follows (in address space) the current section
            DataFileSection next = _sections.FirstOrDefault(s => s.Address > section.Address && s.Address <= section.EndAddress);

            while (next != null)
            {
                if (section.EndAddress < next.EndAddress)
                {
                    // Need to merge data from the next section

                    // Get the bytes that overlap
                    byte[] overlap = next.Read(section.EndAddress, next.EndAddress - section.EndAddress);

                    // Merge the overlapped bytes into the latest section
                    section.Write(section.EndAddress + 1, overlap);
                }

                // Can remove the next section, since data has been redefined or merged into
                // the previous section
                _sections.Remove(next);

                // Get the next section that follows in address space
                next = _sections.FirstOrDefault(s => s.Address > next.Address && s.Address <= next.EndAddress);
            }

            _sections.Sort();
        }

        /// <summary>
        /// Fills data at an address with the specified value.
        /// </summary>
        /// <param name="address">The address to begin the fill operation.</param>
        /// <param name="value">The value to be written.</param>
        /// <param name="count">The total number of bytes to be filled.</param>
        public void Fill(int address, byte value, int count)
        {
            byte[] buffer = new byte[count];

            for (int i = 0; i < count; i++)
                buffer[i] = value;

            Write(address, buffer);
        }

        /// <summary>
        /// Pads all sections to meet the specified size.
        /// </summary>
        /// <param name="size">The size in bytes to pad against.</param>
        public void Pad(int size)
        {
            Pad(size, 0xFF);
        }

        /// <summary>
        /// Pads all sections to meet the specified size.
        /// </summary>
        /// <param name="size">The size in bytes to pad against.</param>
        /// <param name="value">The value used to pad.</param>
        public void Pad(int size, byte value)
        {
            DataFileSection section = _sections.FirstOrDefault(s => (s.Length % size) != 0);

            while (section != null)
            {
                Fill(section.Address + section.Length, value, size - (section.Length % size));
                section = _sections.FirstOrDefault(s => (s.Length % size) != 0);
            }
        }

        /// <summary>
        /// Encrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="passphrase">The passphrase used to generate a key.</param>
        public void Encrypt(int keySize, string passphrase)
        {
            Encrypt(keySize, passphrase, new byte[16]);
        }

        /// <summary>
        /// Encrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="passphrase">The passphrase used to generate a key.</param>
        /// <param name="iv">The initialization vector to be used.</param>
        public void Encrypt(int keySize, string passphrase, byte[] iv)
        {
            Encrypt(keySize, Security.GenerateKey(keySize, passphrase), iv);
        }

        /// <summary>
        /// Encrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="key">The key values.</param>
        public void Encrypt(int keySize, byte[] key)
        {
            Encrypt(keySize, key, new byte[16]);
        }

        /// <summary>
        /// Encrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="key">The key values.</param>
        /// <param name="iv">The initialization vector to be used.</param>
        public void Encrypt(int keySize, byte[] key, byte[] iv)
        {
            // Must pad to at 16-byte blocks for AES
            Pad(16);

            using (AesManaged aes = new AesManaged())
            {
                aes.Mode = CipherMode.CBC;
                aes.Padding = PaddingMode.None;

                aes.KeySize = keySize;
                aes.Key = key;
                aes.IV = iv;

                using (ICryptoTransform crypto = aes.CreateEncryptor())
                {
                    foreach (DataFileSection section in _sections)
                    {
                        section.SetData(crypto.TransformFinalBlock(section.ToArray(), 0, section.Length));
                        //section.Data = crypto.TransformFinalBlock(section.Data, 0, section.Length);
                    }
                }
            }
        }

        /// <summary>
        /// Decrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="passphrase">The passphrase used to generate the key.</param>
        public void Decrypt(int keySize, string passphrase)
        {
            Decrypt(keySize, passphrase, new byte[16]);
        }

        /// <summary>
        /// Decrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="passphrase">The passphrase used to generate the key.</param>
        /// <param name="iv">The initialization vector to be used.</param>
        public void Decrypt(int keySize, string passphrase, byte[] iv)
        {
            Decrypt(keySize, Security.GenerateKey(keySize, passphrase), iv);
        }

        /// <summary>
        /// Decrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="key">The key values.</param>
        public void Decrypt(int keySize, byte[] key)
        {
            Decrypt(keySize, key, new byte[16]);
        }

        /// <summary>
        /// Decrypts this file.
        /// </summary>
        /// <param name="keySize">The size of the key, in bits, to be used. Valid values are 128, 196, or 256.</param>
        /// <param name="key">The key values.</param>
        /// <param name="iv">The initialization vector to be used.</param>
        public void Decrypt(int keySize, byte[] key, byte[] iv)
        {
            using (AesManaged aes = new AesManaged())
            {
                aes.Mode = CipherMode.CBC;
                aes.Padding = PaddingMode.None;

                aes.KeySize = keySize;
                aes.Key = key;
                aes.IV = iv;

                using (ICryptoTransform crypto = aes.CreateDecryptor())
                {
                    foreach (DataFileSection section in _sections)
                    {
                        section.SetData(crypto.TransformFinalBlock(section.ToArray(), 0, section.Length));
                        //section.Data = crypto.TransformFinalBlock(section.Data, 0, section.Length);
                    }
                }
            }
        }

        /// <summary>
        /// Returns a <see cref="System.String" /> that represents this instance.
        /// </summary>
        /// <returns>A <see cref="System.String" /> that represents this instance.</returns>
        public override string ToString()
        {
            return string.Format("Address=0x{0:X8} Length={1}", Address, Length);
        }
    }

    /// <summary>
    /// Represents a contiguous section of data within a data file.
    /// </summary>
    public class DataFileSection : IComparable<DataFileSection>
    {
        private MemoryStream _stream = new MemoryStream();

        /// <summary>
        /// Gets or sets the address for the section.
        /// </summary>
        public int Address { get; set; }

        /// <summary>
        /// Gets the end (or last) address for the section.
        /// </summary>
        public int EndAddress { get { return Address + Length - 1; } }

        /// <summary>
        /// Gets the length in bytes for the section.
        /// </summary>
        public int Length { get { return (int)_stream.Length; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataFileSection"/> class.
        /// </summary>
        public DataFileSection()
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataFileSection"/> class with the specified
        /// address and data.
        /// </summary>
        /// <param name="address">The address for the section.</param>
        /// <param name="data">The data for the section.</param>
        public DataFileSection(int address, byte[] data)
        {
            Address = address;

            SetData(data);
        }

        public void SetData(byte[] data)
        {
            _stream.SetLength(0);
            _stream.Write(data, 0, data.Length);
        }

        /// <summary>
        /// Compares this instance to the specified section by comparing their respective addresses.
        /// </summary>
        /// <param name="section">The section to be compared.</param>
        /// <returns>A signed number indicating the relative values of this instance and the specified section.</returns>
        public int CompareTo(DataFileSection section)
        {
            if (section == null)
                return 1;
            else
                return this.Address.CompareTo(section.Address);
        }

        /// <summary>
        /// Determines whether this section contains the specified address.
        /// </summary>
        /// <param name="address">The address to be checked.</param>
        /// <returns>True if this section contains the specified address; otherwise false.</returns>
        public bool Contains(int address)
        {
            return (address >= Address && address < (Address + Length));
        }

        /// <summary>
        /// Determines whether this section contains the specified address range.
        /// </summary>
        /// <param name="address">The staring address to be checked.</param>
        /// <param name="length">The length in bytes of the entire range to be checked.</param>
        /// <returns>True if this section contains the entire range of specified addresses; otherwise false.</returns>
        public bool Contains(int address, int length)
        {
            if (address >= Address && address < (Address + Length))
                return ((address + length - 1) < (Address + Length));

            return false;
        }

        /// <summary>
        /// Determines whether this section touches the specified address.
        /// </summary>
        /// <param name="address">The address to be checked.</param>
        /// <returns>True if this section just touches the specified address; otherwise false.</returns>
        public bool Touches(int address)
        {
            if (address == Address - 1)
                return true;

            if (address == Address + Length)
                return true;

            return false;
        }

        /// <summary>
        /// Resizes this section while maintaining it's data values.
        /// </summary>
        /// <param name="newSize">The new size for the section.</param>
        public void Resize(int newSize)
        {
            _stream.SetLength(newSize);
        }

        /// <summary>
        /// Reads and returns data from this section at the specified offset.
        /// </summary>
        /// <param name="offset">The offset to begin reading.</param>
        /// <param name="length">The total length, in bytes, to read.</param>
        /// <returns>The data that has been read. May be less than requested if the section doesn't
        /// contain the requested amount.</returns>
        public byte[] Read(int offset, int length)
        {
            // Calc the number of bytes that can be read from this section
            int len = (int)(_stream.Length - offset);

            if (len < 0)
                return new byte[0];

            // Limit to the amount requested
            if (len > length)
                len = length;

            byte[] data = new byte[len];

            _stream.Seek(offset, SeekOrigin.Begin);
            _stream.Read(data, 0, len);
            
            return data;
        }

        /// <summary>
        /// Reads data from this section into the specified buffer.
        /// </summary>
        /// <param name="address">The address to begin reading.</param>
        /// <param name="buffer">The buffer to receive the data from the section.</param>
        /// <param name="nbytes">The total number of bytes to read.</param>
        /// <param name="bytesread">The number of bytes that have been read.</param>
        public void Read(int address, byte[] buffer, int nbytes, out int bytesread)
        {
            int start = address;

            if (Address > address)
                start = Address;

            int end = address + nbytes;

            if (end > (EndAddress + 1))
                end = (EndAddress + 1);

            if (end <= start)
            {
                bytesread = 0;
                return;
            }

            int len = end - start;
            if (len > Length)
                len = Length;

            int offs = Address - address;

            _stream.Seek(start - Address, SeekOrigin.Begin);
            _stream.Read(buffer, offs, len);

            bytesread = len;
        }

        /// <summary>
        /// Writes data into this section.
        /// </summary>
        /// <param name="address">The address to begin writing.</param>
        /// <param name="data">The data to be written.</param>
        /// <remarks>This section will increase in length if necessary.</remarks>
        public void Write(int address, byte[] data)
        {
            int len = (address - Address) + data.Length;
            if (len > _stream.Length)
                _stream.SetLength(len);

            _stream.Seek(address - Address, SeekOrigin.Begin);
            _stream.Write(data, 0, data.Length);
        }

        /// <summary>
        /// Returns the data contained within this section.
        /// </summary>
        /// <returns>An array of the data bytes within this section.</returns>
        public byte[] ToArray()
        {
            return _stream.ToArray();
        }

        /// <summary>
        /// Returns a <see cref="System.String" /> that represents this instance.
        /// </summary>
        /// <returns>A <see cref="System.String" /> that represents this instance.</returns>
        public override string ToString()
        {
            return string.Format("Address: 0x{0:X8} Size: {1}", Address, Length);
        }
    }

    /// <summary>
    /// Represents a formatting for reading and writing a data file.
    /// </summary>
    public enum DataFileFormat
    {
        /// <summary>
        /// An unknown file format.
        /// </summary>
        Unknown = 0,

        /// <summary>
        /// A raw binary format.
        /// </summary>
        Binary,

        /// <summary>
        /// The extended intel hex format.
        /// </summary>
        Hex,

        /// <summary>
        /// The motorola s-record format.
        /// </summary>
        SRecord,

        /// <summary>
        /// The device firmware update format (binary with a DFU suffix).
        /// </summary>
        DFU,
    }
}
