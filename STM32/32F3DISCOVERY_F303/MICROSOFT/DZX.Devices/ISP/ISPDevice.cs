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
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FTD2XX_NET;
using DZX.Devices.FTDI;

namespace DZX.Devices.ISP
{
    /// <summary>
    /// Represents a device that supports the NXP In-System Programming (ISP) interface.
    /// </summary>
    public class ISPDevice : IDisposable
    {
        private bool _echo = false;
        private bool disposed = false;
        private FTDIDevice _ftdi;
        private SerialPort _port;
        private int _baud = 9600;
        private int _databits = 8;
        private StopBits _stopbits = StopBits.One;
        private Parity _parity = Parity.None;
        private Handshake _handshake = Handshake.None;
        private Queue<byte> _rx = new Queue<byte>();

        /// <summary>
        /// Gets or sets the target device to be used when performing a Download or Upload operation.
        /// </summary>
        public ISPTarget Target { get; set; }

        /// <summary>
        /// Gets the part identifier value that was received when the device type was queried.
        /// </summary>
        public uint PartID { get; private set; }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for a response
        /// from the device when executing a command. 1000 by default.
        /// </summary>
        public int ResponseTimeout { get; set; }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for a response
        /// from the device when executing a programming memory command. 5000 by default.
        /// </summary>
        public int ProgrammingTimeout { get; set; }

        /// <summary>
        /// Gets or sets the width, in milliseconds, of the reset pulse. 50 by default.
        /// </summary>
        public int ResetPulseWidth { get; set; }

        /// <summary>
        /// Gets or sets the time, in milliseconds, that the ISP Enable signal remains active after
        /// the Reset pulse. 50 by default.
        /// </summary>
        public int ISPEnableDelay { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to erase all sectors within the chip when downloading data.
        /// </summary>
        public bool EraseChip { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to verify each sector after it has been programmed within the device.
        /// </summary>
        public bool Verify { get; set; }

        /// <summary>
        /// Gets a value indicating whether this device is currently open for communications.
        /// </summary>
        public bool Connected
        {
            get
            {
                if (_ftdi != null)
                    return _ftdi.Connected;

                if (_port != null)
                    return _port.IsOpen;

                return false;
            }
        }

        /// <summary>
        /// Gets or sets the baud rate, in bits per second, for the device.
        /// </summary>
        public int Baud 
        {
            get { return _baud; } 
            set 
            { 
                _baud = value;

                if (_ftdi != null)
                    _ftdi.Baud = value;

                if (_port != null)
                    _port.BaudRate = value;
            } 
        }

        /// <summary>
        /// Gets or sets the number of data bits for the device. Default is 8.
        /// </summary>
        public int DataBits
        {
            get { return _databits; }
            set
            {
                _databits = value;

                if (_ftdi != null)
                    _ftdi.DataBits = (byte)value;

                if (_port != null)
                    _port.DataBits = value;
            }
        }

        /// <summary>
        /// Gets or sets the stop bits for the device. Default is one.
        /// </summary>
        public StopBits StopBits
        {
            get { return _stopbits; }
            set
            {
                _stopbits = value;

                if (_ftdi != null)
                    _ftdi.StopBits = value;

                if (_port != null)
                    _port.StopBits = value;
            }
        }

        /// <summary>
        /// Gets or sets the parity for the device. Default is none.
        /// </summary>
        public Parity Parity
        {
            get { return _parity; }
            set
            {
                _parity = value;

                if (_ftdi != null)
                    _ftdi.Parity = value;

                if (_port != null)
                    _port.Parity = value;
            }
        }

        /// <summary>
        /// Gets or sets the handshake for the device. Default is none.
        /// </summary>
        public Handshake Handshake
        {
            get { return _handshake; }
            set
            {
                _handshake = value;

                if (_ftdi != null)
                    _ftdi.Handshake = value;

                if (_port != null)
                    _port.Handshake = value;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether to use DTR and RTS as signals to control
        /// the device's Reset and ISP Enable signals. <c>true</c> by default.
        /// </summary>
        public bool UseSignals { get; set; }

        /// <summary>
        /// Gets or sets the function of the RTS signal. ISP Enable function by default.
        /// </summary>
        public ISPSignalFunction RTSFunction { get; set; }

        /// <summary>
        /// Gets or sets the function of the DTR signal. Reset function by default.
        /// </summary>
        public ISPSignalFunction DTRFunction { get; set; }

        /// <summary>
        /// Occurs when a sector has been requested to be erased within the device.
        /// </summary>
        public event SectorEventHandler SectorErasing;

        /// <summary>
        /// Occurs when a sector has been erased within the device.
        /// </summary>
        public event SectorEventHandler SectorErased;

        /// <summary>
        /// Occurs when a sector has begun a programming operation.
        /// </summary>
        public event SectorEventHandler SectorProgramming;

        /// <summary>
        /// Occurs when a sector has completed programming.
        /// </summary>
        public event SectorEventHandler SectorProgrammed;

        /// <summary>
        /// Occurs when a sector has started being verified.
        /// </summary>
        public event SectorEventHandler SectorVerifying;

        /// <summary>
        /// Occurs when a sector has completed being verified.
        /// </summary>
        public event SectorEventHandler SectorVerified;

        /// <summary>
        /// Occurs when data is being downloaded to the device.
        /// </summary>
        public event SectorProgressEventHandler Downloading;

        /// <summary>
        /// Occurs when data is being uploaded from a device.
        /// </summary>
        public event DataProgressEventHandler Uploading;


        /// <summary>
        /// Initializes a new instance of the <see cref="ISPDevice"/> class.
        /// </summary>
        public ISPDevice()
        {
            // Default DTR and RTS signals
            UseSignals = true;
            DTRFunction = ISPSignalFunction.ResetActiveLow;
            RTSFunction = ISPSignalFunction.ISPEnableActiveLow;

            // Default communication timeouts
            ResponseTimeout = 1000;
            ProgrammingTimeout = 5000;

            // Default signal timings
            ResetPulseWidth = 50;
            ISPEnableDelay = 50;

            EraseChip = false;
            Verify = false;
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="ISPDevice"/> class.
        /// </summary>
        ~ISPDevice()
        {
            Dispose(false);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources.
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    Disconnect();
                }

                disposed = true;
            }
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Returns all of the currently attached FTDI devices.
        /// </summary>
        /// <returns>An array of nodes that each represent an attached FTDI device.</returns>
        public static FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[] GetAttachedAsFTDI()
        {
            return FTDIDevice.GetAttached();
        }

        /// <summary>
        /// Gets the attached as COM.
        /// </summary>
        /// <returns></returns>
        public static string[] GetAttachedAsCOM()
        {
            return SerialPort.GetPortNames();
        }

        /// <summary>
        /// Opens a connection with the device using a standard COM port.
        /// </summary>
        /// <param name="com">The COM port to be opened.</param>
        public void Connect(string com)
        {
            // Close any existing connections
            Disconnect();

            // Open a standard com port
            _port = new SerialPort(com);
            _port.Open();

            // Assign port settings
            _port.BaudRate = _baud;
            _port.DataBits = _databits;
            _port.Parity = _parity;
            _port.StopBits = _stopbits;
            _port.Handshake = _handshake;
        }

        /// <summary>
        /// Opens a connection with the device using the FTDI D2XX driver.
        /// </summary>
        /// <param name="node">The node of the device to be opened.</param>
        public void Connect(FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE node)
        {
            // Close any existing connections
            Disconnect();

            // Open an FTDI device
            _ftdi = new FTDIDevice();
            _ftdi.Connect(node.SerialNumber);

            // Assign port settings
            _ftdi.Baud = _baud;
            _ftdi.DataBits = (byte)_databits;
            _ftdi.Parity = _parity;
            _ftdi.StopBits = _stopbits;
            _ftdi.Handshake = _handshake;
        }

        /// <summary>
        /// Closes any existing connection with the device.
        /// </summary>
        public void Disconnect()
        {
            if (_port != null)
            {
                _port.Close();
                _port.Dispose();
                _port = null;
            }

            if (_ftdi != null)
            {
                _ftdi.Disconnect();
                _ftdi = null;
            }
        }

        /// <summary>
        /// Invokes ISP mode within the device. If <see cref="UseSignals"/> is set to <c>true</c>, the DTR and RTS signals
        /// will be used to enter ISP mode. The auto baud sequence will be performed with the device.
        /// </summary>
        /// <exception cref="DZX.Devices.ISP.ISPException">A command failed with the device.</exception>
        public void InvokeISP()
        {
            // Enter ISP mode using DTR/RTS if configured
            if (UseSignals)
                Reset(true);

            // By default, assume no echo from the target
            _echo = false;

            // If a target has already been specified, determine whether the echo is On/Off by default
            if (Target != null)
                _echo = Target.EchoByDefault;

            // Perform auto baud sequence
            AutoBaud();

            // Turn the echo OFF
            string ack = Command("A 0\r\n", ResponseTimeout, true);
            if (ack != "0")
                ISPReturnCodeError(ack);

            // Don't process request echo
            _echo = false;

            Unlock(23130);

            if (Target == null)
            {
                ISPDeviceType type = ReadDeviceType();

                if (type != ISPDeviceType.Unknown)
                    Target = ISPTarget.FromDeviceType(type);
            }
        }

        /// <summary>
        /// Exits ISP mode within the device by using the DTR and RTS signals to reset
        /// the device.
        /// </summary>
        public void ExitISP()
        {
            if (UseSignals)
            {
                Reset(false);
            }
        }

        /// <summary>
        /// Sets the target configuration for the device from the specified device type.
        /// </summary>
        /// <param name="deviceType">Type of the device.</param>
        public void SetTarget(ISPDeviceType deviceType)
        {
            Target = ISPTarget.FromDeviceType(deviceType);
        }

        /// <summary>
        /// Performs a reset of the device using DTR and RTS signals.
        /// </summary>
        /// <param name="isp">Use <c>true</c> to have the device enter ISP mode; otherwise <c>false</c>.</param>
        public void Reset(bool isp)
        {
            // Assert ISP
            SetISP(isp);

            // Pulse the RESET signal
            SetReset(true);
            System.Threading.Thread.Sleep(ResetPulseWidth);
            SetReset(false);

            if (isp)
            {
                // Keep the ISP active for a bit before releasing to ensure
                // the device properly enters ISP mode
                System.Threading.Thread.Sleep(ISPEnableDelay);

                // Deassert ISP (to allow for manual reset)
                SetISP(false);
            }
        }

        /// <summary>
        /// Executes an Unlock command with the device.
        /// </summary>
        /// <param name="code">The unlock code.</param>
        public void Unlock(uint code)
        {
            string ack = Command(string.Format("U {0}\r\n", code), ResponseTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);
        }

        /// <summary>
        /// Executes a Go command with the device.
        /// </summary>
        /// <param name="address">The address sent to the device.</param>
        /// <param name="arm">Use <c>true</c> to specify ARM mode; otherwise <c>false</c> for thumb mode.</param>
        public void Go(uint address, bool arm)
        {
            string ack = Command(string.Format("G {0} {1}\r\n", address, arm ? "A" : "T"), ResponseTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);
        }

        /// <summary>
        /// Executes the Read Device Serial Number command with the device.
        /// </summary>
        /// <returns>The serial number as received from the device.</returns>
        /// <exception cref="DZX.Devices.ISP.ISPException">No response</exception>
        public byte[] ReadSerialNumber()
        {
            byte[] sn = new byte[16];

            string ack = Command("N\r\n", ResponseTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);

            for (int k = 0; k < 4; k++)
            {
                string response = Read(ResponseTimeout);
                if (string.IsNullOrEmpty(response))
                    throw new ISPException("No response");

                BitConverter.GetBytes(uint.Parse(response)).CopyTo(sn, k * 4);
            }

            return sn;
        }

        /// <summary>
        /// Reads the type of the device using the Read Part Identification Number command.
        /// </summary>
        /// <returns>The target device type.</returns>
        /// <exception cref="DZX.Devices.ISP.ISPException">No response</exception>
        public ISPDeviceType ReadDeviceType()
        {
            string ack = Command("J\r\n", ResponseTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);

            string response = Read(ResponseTimeout);
            if (string.IsNullOrEmpty(response))
                throw new ISPException("No response");

            PartID = uint.Parse(response);

            if (ISPTarget.HasSecondaryIdentifier(PartID))
            {
                response = Read(ResponseTimeout);
                if (string.IsNullOrEmpty(response))
                    return ISPDeviceType.Unknown;

                uint id2 = uint.Parse(response);
                return ISPTarget.FindDeviceType(PartID, id2);
            }

            return ISPTarget.FindDeviceType(PartID);
        }


        private byte[] GetProgramData(uint programAddress, byte[] programData, uint sectorAddress, uint sectorSize, out uint offset)
        {
            if (sectorAddress <= programAddress)
            {
                uint sectorEndAddress = (uint)(sectorAddress + sectorSize - 1);

                if (programAddress <= sectorEndAddress)
                {
                    // The sector overlaps onto the program space
                    uint overlap = sectorSize - (programAddress - sectorAddress);

                    // Cannot overlap beyond the program data
                    if (overlap > (uint)programData.Length)
                        overlap = (uint)programData.Length;

                    byte[] data = new byte[overlap];

                    offset = 0;
                    Buffer.BlockCopy(programData, 0, data, (int)(programAddress - sectorAddress), (int)(overlap - (programAddress - sectorAddress)));
                    return data;
                }
            }
            else
            {
                uint programEndAddress = (uint)(programAddress + programData.Length - 1);
                
                if (sectorAddress <= programEndAddress)
                {
                    uint sectorEndAddress = (uint)(sectorAddress + sectorSize - 1);

                    // The sector overlaps onto the program space
                    uint overlap = sectorSize - (sectorEndAddress - programEndAddress);
                    if (overlap > sectorSize)
                        overlap = sectorSize;

                    byte[] data = new byte[overlap];

                    offset = (sectorAddress - programAddress);
                    Buffer.BlockCopy(programData, (int)offset, data, 0, (int)overlap);
                    return data;
                }
                
            }

            offset = 0;
            return new byte[0];
        }

        /// <summary>
        /// Gets the sectors that contain data or require being erased given the specified data to
        /// be written.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="data">The data.</param>
        /// <returns>An array of the sectors to be erased or programmed.</returns>
        private DataSector[] GetDataSectors(uint address, byte[] data)
        {
            List<DataSector> sectors = new List<DataSector>();

            // Process each memory section for the target
            foreach (MemoryMapSection section in Target.MemoryMap.Sections)
            {
                // Process each sector within the section
                for (uint idx = 0; idx < section.SectorCount; idx++)
                {
                    uint offset = 0;

                    byte[] sectorData = GetProgramData(address, data, section.Address + (idx * section.SectorSize), section.SectorSize, out offset);
                    if (EraseChip || sectorData.Length > 0)
                    {
                        DataSector sector = new DataSector();

                        sector.Bank = section.Bank;
                        sector.Number = section.SectorNumber + idx;
                        sector.Data = sectorData;
                        sector.Offset = offset;

                        sectors.Add(sector);
                    }
                }
            }

            return sectors.ToArray();
        }

        private bool IsBufferBlank(byte[] buffer, int offset, int length)
        {
            for (int k = 0; k < length; k++)
            {
                if (buffer[k + offset] != 0xFF)
                    return false;
            }

            return true;
        }

        /// <summary>
        /// Downloads a block of data to a device at the specified address.
        /// </summary>
        /// <param name="address">The starting destination address within the device.</param>
        /// <param name="data">The data to be downloaded.</param>
        /// <exception cref="DZX.Devices.ISP.ISPException">
        /// No target specified
        /// or
        /// No memory map found
        /// or
        /// The target memory map is empty.
        /// </exception>
        public void Download(uint address, byte[] data)
        {
            if (Target == null)
                throw new ISPException("No target specified");

            if (Target.MemoryMap == null)
                throw new ISPException("No memory map found");

            if (Target.MemoryMap.Sections.Count == 0)
                throw new ISPException("The target memory map is empty");

            byte[] buffer = new byte[Target.RAMBufferSize];

            int programmed = 0;

            // Get all of the sectors that contain data to be programmed
            DataSector[] sectors = GetDataSectors(address, data);
 
            foreach (DataSector sector in sectors)
            {
                OnSectorErasing(new SectorEventArgs(sector.Number));

                // Erase the sector
                PrepareSectors(sector.Number, sector.Number, sector.Bank);
                EraseSectors(sector.Number, sector.Number, sector.Bank);

                OnSectorErased(new SectorEventArgs(sector.Number));

                
                if (sector.Length > 0)
                {
                    OnSectorProgramming(new SectorEventArgs(sector.Number));

                    // Program the sector
                    int total = 0;

                    while (total < sector.Data.Length)
                    {
                        int len = sector.Data.Length - total;
                        if (len > buffer.Length)
                            len = buffer.Length;

                        Buffer.BlockCopy(sector.Data, total, buffer, 0, len);

                        // Only proceed if the buffer is not blank
                        if (!IsBufferBlank(buffer, 0, len))
                        {
                            if (len < buffer.Length)
                            {
                                // Pad the remaining space within the buffer
                                for (int k = len; k < buffer.Length; k++)
                                {
                                    buffer[k] = 0xFF;
                                }
                            }

                            WriteRAM(Target.RAMBufferAddress, buffer, Target.UUEncode);
                            PrepareSectors(sector.Number, sector.Number, sector.Bank);
                            CopyRAMToFlash((uint)(address + sector.Offset + total), Target.RAMBufferAddress, (uint)buffer.Length);
                        }

                        total += len;
                    }

                    OnSectorProgrammed(new SectorEventArgs(sector.Number));

                    if (Verify)
                    {
                        OnSectorVerifying(new SectorEventArgs(sector.Number));

                        byte[] devmem = Upload(address + sector.Offset, sector.Length, false, Target.UUEncode);
                        if (!devmem.SequenceEqual(sector.Data))
                        {
                            throw new ISPException(string.Format("Failed verification of sector {0}.", sector.Number));
                        }

                        OnSectorVerified(new SectorEventArgs(sector.Number));
                    }
                }

                programmed++;

                OnDownloading(new SectorProgressEventArgs((uint)programmed, (uint)sectors.Length));
            }
        }

        /// <summary>
        /// Executes the Write to RAM command with the device.
        /// </summary>
        /// <param name="address">The starting address to be written.</param>
        /// <param name="data">The data to be written.</param>
        private void WriteRAM(uint address, byte[] data, bool uuencode)
        {
            string ack = Command(string.Format("W {0} {1}\r\n", address, data.Length), ResponseTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);

            int total = 0;
            int lines = 0;
            int sumidx = 0;
            int sumtotal = 0;

            while (total < data.Length)
            {
                int len = data.Length - total;

                if (uuencode)
                {
                    // Bound to maximum UU line length
                    if (len > 45)
                        len = 45;

                    // Encode and transfer the data
                    Write(UUEncoding.GetString(data, total, len) + "\r\n");
                }
                else
                {
                    byte[] b = new byte[len];
                    Buffer.BlockCopy(data, total, b, 0, len);
                    Write(b);
                    //Write(BinaryEncoding.GetString(data, total, len) + "\r\n");
                }

                if (uuencode)
                {
                    sumtotal += len;
                    lines++;

                    if (lines == 20)
                    {
                        TransmitChecksum(data, sumidx, sumtotal);
                        lines = 0;
                        sumidx += sumtotal;
                        sumtotal = 0;
                    }
                }

                total += len;
            }

            if (uuencode && lines > 0)
                TransmitChecksum(data, sumidx, sumtotal);
        }

        /// <summary>
        /// Performs a PrepareSector command with the ISP device.
        /// </summary>
        /// <param name="startSector">The start sector.</param>
        /// <param name="endSector">The end sector.</param>
        private void PrepareSectors(uint startSector, uint endSector)
        {
            PrepareSectors(startSector, endSector, null);
        }

        /// <summary>
        /// Performs a PrepareSector command with the ISP device.
        /// </summary>
        /// <param name="startSector">The start sector.</param>
        /// <param name="endSector">The end sector.</param>
        /// <param name="bank">The bank number.</param>
        private void PrepareSectors(uint startSector, uint endSector, Nullable<uint> bank)
        {
            if (bank.HasValue)
            {
                string ack = Command(string.Format("P {0} {1} {2}\r\n", startSector, endSector, bank), ResponseTimeout);

                if (ack != "0")
                    ISPReturnCodeError(ack);
            }
            else
            {
                string ack = Command(string.Format("P {0} {1}\r\n", startSector, endSector), ResponseTimeout);

                if (ack != "0")
                    ISPReturnCodeError(ack);
            }
        }

        /// <summary>
        /// Performs an EraseSectors command with the ISP device.
        /// </summary>
        /// <param name="startSector">The start sector.</param>
        /// <param name="endSector">The end sector.</param>
        private void EraseSectors(uint startSector, uint endSector)
        {
            EraseSectors(startSector, endSector, null);
        }

        /// <summary>
        /// Performs an EraseSectors command with the ISP device.
        /// </summary>
        /// <param name="startSector">The start sector.</param>
        /// <param name="endSector">The end sector.</param>
        /// <param name="bank">The bank number.</param>
        private void EraseSectors(uint startSector, uint endSector, Nullable<uint> bank)
        {
            if (bank.HasValue)
            {
                string ack = Command(string.Format("E {0} {1} {2}\r\n", startSector, endSector, bank), ResponseTimeout);

                if (ack != "0")
                    ISPReturnCodeError(ack);
            }
            else
            {
                string ack = Command(string.Format("E {0} {1}\r\n", startSector, endSector), ResponseTimeout);

                if (ack != "0")
                    ISPReturnCodeError(ack);
            }
        }

        /// <summary>
        /// Performs a CopyRAMToFlash command with an ISP device.
        /// </summary>
        /// <param name="dst">The destination address.</param>
        /// <param name="src">The source address.</param>
        /// <param name="nbytes">The number of bytes to be copied.</param>
        private void CopyRAMToFlash(uint dst, uint src, uint nbytes)
        {
            string ack = Command(string.Format("C {0} {1} {2}\r\n", dst, src, nbytes), ProgrammingTimeout);

            if (ack != "0")
                ISPReturnCodeError(ack);
        }

        /// <summary>
        /// Reads the memory.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="nbytes">The nbytes.</param>
        /// <returns></returns>
        /// <exception cref="DZX.Devices.ISP.ISPException">
        /// Received invalid checksum
        /// </exception>
        public byte[] Upload(uint address, int nbytes)
        {
            return Upload(address, nbytes, true, Target.UUEncode);
        }

        /// <summary>
        /// Reads the memory.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="nbytes">The nbytes.</param>
        /// <returns></returns>
        /// <exception cref="DZX.Devices.ISP.ISPException">
        /// Received invalid checksum
        /// </exception>
        private byte[] Upload(uint address, int nbytes, bool events, bool uuencode)
        {
            int nread = nbytes;

            if ((nread % 4) != 0)
            {
                nread += (4 - (nread % 4));
            }

            byte[] data = new byte[nread];

            if (uuencode)
            {
                // Request a read memory command
                string ack = Command(string.Format("R {0} {1}\r\n", address, nread), ResponseTimeout);
                if (ack != "0")
                    ISPReturnCodeError(ack);

                if (events)
                    OnUploading(new DataProgressEventArgs((uint)0, (uint)nread));

                int total = 0;
                int lines = 0;
                int sumidx = 0;
                int sumtotal = 0;
                int proglines = 0;

                while (total < nbytes)
                {
                    // Receive the next line
                    string line = Read(ResponseTimeout);

                    // Decode the line
                    byte[] buf = UUEncoding.GetBytes(line);

                    // Store the raw data
                    buf.CopyTo(data, total);


                    // Keep track of amount completed
                    total += buf.Length;
                    lines++;
                    proglines++;

                    sumtotal += buf.Length;

                    if (lines == 20)
                    {
                        // Process a checksum every 20 UU lines
                        ReceiveChecksum(data, sumidx, sumtotal);

                        lines = 0;
                        sumidx += sumtotal;
                        sumtotal = 0;
                    }

                    // Provide an upload event every 100 lines (4500 bytes)
                    if (proglines >= 100)
                    {
                        proglines = 0;
                        if (events)
                            OnUploading(new DataProgressEventArgs((uint)total, (uint)nread));
                    }
                }

                if (lines > 0)
                {
                    // Process a checksum
                    ReceiveChecksum(data, sumidx, sumtotal);
                }

                if (proglines > 0)
                {
                    if (events)
                        OnUploading(new DataProgressEventArgs((uint)total, (uint)nread));
                }
            }
            else
            {
                int total = 0;

                while (total < nread)
                {
                    int len = nread - total;
                    if (len > Target.MaxReadLength)
                        len = Target.MaxReadLength;

                    // Request a read memory command
                    string ack = Command(string.Format("R {0} {1}\r\n", address + total, len), ResponseTimeout);
                    if (ack != "0")
                        ISPReturnCodeError(ack);

                    if (events)
                        OnUploading(new DataProgressEventArgs((uint)total, (uint)nread));

                    byte[] buf = ReadBinary(len, ResponseTimeout);
                    if (buf.Length != len)
                        throw new ISPException(string.Format("Incorrect response length, received '{0}' of expected '{1}' bytes", buf.Length, len));

                    Buffer.BlockCopy(buf, 0, data, total, len);
                    total += len;
                }
            }

            if (nread == nbytes)
                return data;

            byte[] retval = new byte[nbytes];
            Buffer.BlockCopy(data, 0, retval, 0, nbytes);
            return retval;
        }

        /// <summary>
        /// Transmits a checksum for the specified data and awaits a proper
        /// response from the device.
        /// </summary>
        /// <param name="data">The data used to calculate the checksum.</param>
        /// <param name="offset">An offset into the data to start the checksum calculation.</param>
        /// <param name="length">The length, in bytes, of data to be accumulated within the checksum.</param>
        /// <exception cref="DZX.Devices.ISP.ISPException">Device did not accept checksum.</exception>
        private void TransmitChecksum(byte[] data, int offset, int length)
        {
            // Calculate own checksum value
            int sum = 0;

            for (int i = 0; i < length; i++)
                sum += data[offset + i];

            string ack = Command(string.Format("{0}\r\n", sum), ResponseTimeout);
            if (ack != "OK")
                throw new ISPException("Device did not accept checksum");
        }

        /// <summary>
        /// Receives and verifies a checksum for the specified data.
        /// </summary>
        /// <param name="data">The data used to verify the checksum.</param>
        /// <param name="offset">An offset into the data to begin verifying the checksum.</param>
        /// <param name="length">The length of data, in bytes, to be verified.</param>
        /// <exception cref="DZX.Devices.ISP.ISPException">
        /// Received invalid checksum
        /// </exception>
        private void ReceiveChecksum(byte[] data, int offset, int length)
        {
            // Receive the checksum from the device
            int rxcheck = 0;
            if (int.TryParse(Read(ResponseTimeout), out rxcheck))
            {
                // Calculate own checksum value
                int sum = 0;

                for (int i = 0; i < length; i++)
                    sum += data[offset + i];

                if (rxcheck == sum)
                    Write("OK\r\n");
                else
                    throw new ISPException(string.Format("Invalid checksum. Expected '{0}', received '{1}'", sum, rxcheck));
            }
            else
            {
                throw new ISPException("Received invalid checksum");
            }
        }

        /// <summary>
        /// Performs the auto baud sequence with the device.
        /// </summary>
        /// <exception cref="DZX.Devices.ISP.ISPException">
        /// No device response from auto baud character
        /// or
        /// Invalid response from auto baud character
        /// or
        /// No device response from auto baud confirmation
        /// or
        /// Invalid response from auto baud confirmation
        /// or
        /// No device response from auto baud confirmation
        /// or
        /// Invalid response from auto baud confirmation
        /// </exception>
        private void AutoBaud()
        {
            string response = Command("?", ResponseTimeout, false);

            if (string.IsNullOrEmpty(response))
                throw new ISPException("No device response from auto baud character");

            if (response != "Synchronized")
                throw new ISPException("Invalid response from auto baud character");

            response = Command("Synchronized\r\n", ResponseTimeout, true);
            if (string.IsNullOrEmpty(response))
                throw new ISPException("No device response from auto baud confirmation");

            if (response != "OK")
                throw new ISPException("Invalid response from auto baud confirmation");

            response = Command("0\r\n", ResponseTimeout, true);

            if (string.IsNullOrEmpty(response))
                throw new ISPException("No device response from auto baud confirmation");

            if (response != "OK")
                throw new ISPException("Invalid response from auto baud confirmation");
        }

        /// <summary>
        /// Sets the DTR signal.
        /// </summary>
        /// <param name="enable">Use <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        private void SetDTR(bool enable)
        {
            if (_ftdi != null)
            {
                _ftdi.SetDTR(enable);
            }
            else if (_port != null)
            {
                _port.DtrEnable = enable;
            }
        }

        /// <summary>
        /// Sets the RTS signal.
        /// </summary>
        /// <param name="enable">Use <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        private void SetRTS(bool enable)
        {
            if (_ftdi != null)
            {
                _ftdi.SetRTS(enable);
            }
            else if (_port != null)
            {
                _port.RtsEnable = enable;
            }
        }

        /// <summary>
        /// Sets the Reset signal.
        /// </summary>
        /// <param name="active">Use <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        public void SetReset(bool active)
        {
            switch (DTRFunction)
            {
                case ISPSignalFunction.ResetActiveHigh:
                    SetDTR(!active);
                    break;
                case ISPSignalFunction.ResetActiveLow:
                    SetDTR(active);
                    break;
            }

            switch (RTSFunction)
            {
                case ISPSignalFunction.ResetActiveHigh:
                    SetRTS(!active);
                    break;
                case ISPSignalFunction.ResetActiveLow:
                    SetRTS(active);
                    break;
            }
        }

        /// <summary>
        /// Sets the ISP Enable signal.
        /// </summary>
        /// <param name="active">Use <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        public void SetISP(bool active)
        {
            switch (DTRFunction)
            {
                case ISPSignalFunction.ISPEnableActiveHigh:
                    SetDTR(!active);
                    break;
                case ISPSignalFunction.ISPEnableActiveLow:
                    SetDTR(active);
                    break;
            }

            switch (RTSFunction)
            {
                case ISPSignalFunction.ISPEnableActiveHigh:
                    SetRTS(!active);
                    break;
                case ISPSignalFunction.ISPEnableActiveLow:
                    SetRTS(active);
                    break;
            }
        }


        /// <summary>
        /// Performs a command transfer with the device.
        /// </summary>
        /// <param name="request">The request message.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a response.</param>
        /// <returns>The response message that was received from the device; if any.</returns>
        private string Command(string request, int timeout)
        {
            return Command(request, timeout, _echo);
        }

        /// <summary>
        /// Performs a command transfer with the device.
        /// </summary>
        /// <param name="request">The request message.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a response.</param>
        /// <param name="echo">Use <c>true</c> if the device is configured to echo the request; otherwise <c>false</c>.</param>
        /// <returns>The response message that was received from the device; if any.</returns>
        private string Command(string request, int timeout, bool echo)
        {
            //mSB.Clear();
            _rx.Clear();

            // Send the request message
            Write(request);

            if (echo)
            {
                // Read the echo'd request
                Read(timeout);
            }

            // Attempt to read the response
            return Read(timeout);
        }

        /// <summary>
        /// Writes the specified message to the device.
        /// </summary>
        /// <param name="message">The message to be sent to the device.</param>
        private void Write(string msg)
        {
            Write(Encoding.ASCII.GetBytes(msg));
        }

        /// <summary>
        /// Writes the specified data to the device.
        /// </summary>
        /// <param name="data">The data to be sent to the device.</param>
        private void Write(byte[] data)
        {
            if (_ftdi != null)
            {
                _ftdi.Write(data);
            }
            else if (_port != null)
            {
                _port.Write(data, 0, data.Length);
            }
        }

        /// <summary>
        /// Reads data from the interface port into the underlying receive stream.
        /// </summary>
        private void ReadPort()
        {
            byte[] data = null;

            if (_ftdi != null)
            {
                // Read from the FTDI device
                data = _ftdi.ReadAvailable();
            }
            else if (_port != null)
            {
                // Read from the COM device
                int avail = _port.BytesToRead;
                if (avail > 0)
                {
                    data = new byte[avail];
                    _port.Read(data, 0, avail);
                }
            }

            // Any data received?
            if (data != null && data.Length > 0)
            {
                // Store the received data for processing later
                foreach (byte b in data)
                    _rx.Enqueue(b);
            }
        }

        /// <summary>
        /// Reads and returns the next received message from the device.
        /// </summary>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a message to arrive.</param>
        /// <returns>The message that has been received, if any; otherwise an empty string.</returns>
        private string Read(int timeout)
        {
            // Return an existing message if one is available
            //if (mRxQueue.Count > 0)
           //     return mRxQueue.Dequeue();

            System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
            watch.Start();

            StringBuilder sb = new StringBuilder();

            while (watch.ElapsedMilliseconds < timeout)
            {
                // Read the available data
                ReadPort();

                while (_rx.Count > 0)
                {
                    byte b = _rx.Dequeue();

                    sb.Append(Convert.ToChar(b));

                    if (_echo && sb.Length >= 1)
                    {
                        if (sb[sb.Length - 1] == '\r')
                        {
                            return sb.ToString().Substring(0, sb.Length - 1);
                        }
                    }
                    else if (sb.Length >= 2)
                    {
                        // Check if an end-of-line has been received
                        if (sb[sb.Length - 2] == '\r' && sb[sb.Length - 1] == '\n')
                        {
                            return sb.ToString().Substring(0, sb.Length - 2);
                        }
                    }
                }

                System.Threading.Thread.Sleep(1);
            }

            return "";
        }

        /// <summary>
        /// Reads and returns the received binary data.
        /// </summary>
        /// <param name="nbytes">The number of bytes to receive and return.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for the specified number of bytes to arrive.</param>
        /// <returns>The data bytes that have been received, if any; otherwise an empty array.</returns>
        private byte[] ReadBinary(int nbytes, int timeout)
        {
            System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
            watch.Start();

            System.IO.MemoryStream mem = new System.IO.MemoryStream();

            while (watch.ElapsedMilliseconds < timeout)
            {
                ReadPort();

                while (_rx.Count > 0)
                {
                    byte b = _rx.Dequeue();
                    mem.Write(new byte[] { b }, 0, 1);

                    if (mem.Length >= nbytes)
                        return mem.ToArray();
                }

                System.Threading.Thread.Sleep(1);
            }

            // No message has been received
            return mem.ToArray();
        }

        /// <summary>
        /// Gets a description for the specified device return code.
        /// </summary>
        /// <param name="code">The code.</param>
        /// <returns>A text description for the given return code.</returns>
        private string GetReturnCodeDescription(uint code)
        {
            switch (code)
            {
                case 0:
                    return "CMD_SUCCESS";
                case 1:
                    return "INVALID_COMMAND";
                case 2:
                    return "SRC_ADDR_ERROR";
                case 3:
                    return "DST_ADDR_ERROR";
                case 4:
                    return "SRC_ADDR_NOT_MAPPED";
                case 5:
                    return "DST_ADDR_NOT_MAPPED";
                case 6:
                    return "COUNT_ERROR";
                case 7:
                    return "INVALID_SECTOR";
                case 8:
                    return "SECTOR_NOT_BLANK";
                case 9:
                    return "SECTOR_NOT_PREPARED";
                case 10:
                    return "COMPARE_ERROR";
                case 11:
                    return "BUSY";
                case 12:
                    return "PARAM_ERROR";
                case 13:
                    return "ADDR_ERROR";
                case 14:
                    return "ADDR_NOT_MAPPED";
                case 15:
                    return "CMD_LOCKED";
                case 16:
                    return "INVALID_CODE";
                case 17:
                    return "INVALID_BAUD_RATE";
                case 18:
                    return "INVALID_STOP_BIT";
                case 19:
                    return "CODE_READ_PROTECTION_ENABLED";
                case 20:
                    return "INVALID_FLASH_UNIT";
                case 21:
                    return "USER_CODE_CHECKSUM";
                case 22:
                    return "ERROR_SETTING_ACTIVE_PARTION";
                default:
                    return "Unknown";
            }
        }


        /// <summary>
        /// Processes a return code response from the device.
        /// </summary>
        /// <param name="code">The response message received by the device.</param>
        /// <exception cref="DZX.Devices.ISP.ISPException">The return code from the device.</exception>
        private void ISPReturnCodeError(string code)
        {
            if (string.IsNullOrEmpty(code))
                throw new ISPException("No return code from device");

            uint number = 0;

            // Attempt to convert the return code into an integer
            if (!uint.TryParse(code, out number))
                throw new ISPException(string.Format("Unrecognized return code from device: {0}", code));

            // Throw an exception with the appropriate description
            throw new ISPException(string.Format("Return code from device: {0}", GetReturnCodeDescription(number)));
        }


        /// <summary>
        /// Raises the <see cref="E:SectorErased" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorErased(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorErased;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:SectorErasing" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorErasing(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorErasing;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:SectorProgramming" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorProgramming(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorProgramming;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:SectorProgrammed" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorProgrammed(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorProgrammed;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:SectorVerifying" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorVerifying(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorVerifying;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:SectorVerified" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorEventArgs"/> instance containing the event data.</param>
        protected virtual void OnSectorVerified(SectorEventArgs e)
        {
            SectorEventHandler handler = SectorVerified;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Downloading" /> event.
        /// </summary>
        /// <param name="e">The <see cref="SectorProgressEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDownloading(SectorProgressEventArgs e)
        {
            SectorProgressEventHandler handler = Downloading;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Uploading" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DataProgressEventArgs"/> instance containing the event data.</param>
        protected virtual void OnUploading(DataProgressEventArgs e)
        {
            DataProgressEventHandler handler = Uploading;
            if (handler != null)
            {
                handler(this, e);
            }
        }
    }

    /// <summary>
    /// Represents a data sector within a device.
    /// </summary>
    internal class DataSector
    {
        /// <summary>
        /// Gets or sets the bank of the sector.
        /// </summary>
        public Nullable<uint> Bank { get; set; }

        /// <summary>
        /// Gets or sets the number of the sector.
        /// </summary>
        public uint Number { get; set; }

        /// <summary>
        /// Gets or sets the offset of the data of the sector.
        /// </summary>
        public uint Offset { get; set; }

        /// <summary>
        /// Gets or sets the data of the sector.
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// Gets the length, in bytes, of the data within this sector.
        /// </summary>
        public int Length
        {
            get
            {
                if (Data != null)
                    return Data.Length;

                return 0;
            }
        }
    }

    /// <summary>
    /// Represents a function for a signal that controls an ISP device.
    /// </summary>
    public enum ISPSignalFunction
    {
        /// <summary>
        /// Indicates the signal functions as the device reset signal and is active LOW.
        /// </summary>
        ResetActiveLow = 0,

        /// <summary>
        /// Indicates the signal functions as the device reset signal and is active HIGH.
        /// </summary>
        ResetActiveHigh,

        /// <summary>
        /// Indicates the signal functions as the device ISP enable signal and is active LOW.
        /// </summary>
        ISPEnableActiveLow,

        /// <summary>
        /// Indicates the signal functions as the device ISP enable signal and is active HIGH.
        /// </summary>
        ISPEnableActiveHigh
    }

    /// <summary>
    /// Represents an exception that occurred with communications with an ISP device.
    /// </summary>
    public class ISPException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ISPException"/> class.
        /// </summary>
        public ISPException() :
            base() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ISPException"/> class.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public ISPException(string message) :
            base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ISPException"/> class.
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception.</param>
        /// <param name="innerException">The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public ISPException(string message, Exception innerException) :
            base(message, innerException) { }
    }
}
