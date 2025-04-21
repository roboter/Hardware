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
using System.ComponentModel;
using System.Linq;
using System.IO.Ports;
using System.Text;

namespace DZX.Devices.FTDI
{
    /// <summary>
    /// Represents an FTDI device.
    /// </summary>
    public class FTDIDevice
    {
        private FTD2XX_NET.FTDI _ftdi = new FTD2XX_NET.FTDI();
        private int _baud = 9600;
        private StopBits _stopbits = StopBits.One;
        private byte _databits = 8;
        private Parity _parity = Parity.None;
        private Handshake _handshake = Handshake.None;

        /// <summary>
        /// The class unique identifier for FTDI devices.
        /// </summary>
        public static readonly Guid ClassGuid = new Guid("219D0508-57A8-4FF5-97A1-BD86587C6C7E");

        /// <summary>
        /// Gets the serial number of this device.
        /// </summary>
        public string SerialNumber { get; private set; }

        /// <summary>
        /// Gets the description for this device.
        /// </summary>
        /// <remarks>Only valid if the device is connected.</remarks>
        public string Description
        {
            get
            {
                if (_ftdi.IsOpen)
                {
                    string description = "";

                    FTD2XX_NET.FTDI.FT_STATUS status = _ftdi.GetDescription(out description);
                    if (status == FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
                        return description;
                }

                return "";
            }
        }

        /// <summary>
        /// Gets or sets the baud rate, in bits per second, for this device. 9600 by default.
        /// </summary>
        public int Baud { get { return _baud; } set { _baud = value; ApplyBaudRate(); } }

        /// <summary>
        /// Gets or sets the number of stop bits for this device.
        /// </summary>
        public StopBits StopBits { get { return _stopbits; } set { _stopbits = value; ApplyCharacteristics(); } }

        /// <summary>
        /// Gets or sets the parity for this device.
        /// </summary>
        public Parity Parity { get { return _parity; } set { _parity = value; ApplyCharacteristics(); } }

        /// <summary>
        /// Gets or sets the number of data bits for this device.
        /// </summary>
        public byte DataBits { get { return _databits; } set { _databits = value; ApplyCharacteristics(); } }

        /// <summary>
        /// Gets or sets the handshake settings for this device.
        /// </summary>
        public Handshake Handshake { get { return _handshake; } set { _handshake = value; ApplyFlowControl(); } }

        /// <summary>
        /// Gets an indication of whether this device is currently considered to be connected and open for communications.
        /// </summary>
        public bool Connected { get { return _ftdi.IsOpen; } }

        /// <summary>
        /// Gets the current write timeout value, in milliseconds, for this device.
        /// </summary>
        public uint WriteTimeout { get; private set; }

        /// <summary>
        /// Gets the current read timeout value, in milliseconds, for this device.
        /// </summary>
        public uint ReadTimeout { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="FTDIDevice"/> class.
        /// </summary>
        public FTDIDevice()
        {
            ReadTimeout = 1000;
            WriteTimeout = 0;
        }

        /// <summary>
        /// Applies the configured baud rate to the underlying FTDI driver.
        /// </summary>
        private void ApplyBaudRate()
        {
            if (_ftdi.IsOpen)
            {
                _ftdi.SetBaudRate((uint)_baud);
            }
        }

        /// <summary>
        /// Applies the flow control settings to the underlying FTDI driver.
        /// </summary>
        private void ApplyFlowControl()
        {
            if (_ftdi.IsOpen)
            {
                switch (_handshake)
                {
                    case Handshake.None:
                        _ftdi.SetFlowControl(FTD2XX_NET.FTDI.FT_FLOW_CONTROL.FT_FLOW_NONE, 0, 0);
                        break;
                    case Handshake.RequestToSend:
                        _ftdi.SetFlowControl(FTD2XX_NET.FTDI.FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, 0, 0);
                        break;
                    case Handshake.XOnXOff:
                        _ftdi.SetFlowControl(FTD2XX_NET.FTDI.FT_FLOW_CONTROL.FT_FLOW_XON_XOFF, 0, 0);
                        break;
                }
            }
        }

        /// <summary>
        /// Applies the port's parity, stop bits and data bits settings to the underlying FTDI driver.
        /// </summary>
        private void ApplyCharacteristics()
        {
            if (_ftdi.IsOpen)
            {
                byte parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_NONE;

                switch (_parity)
                {
                    case Parity.None:
                    default:
                        parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_NONE;
                        break;
                    case Parity.Even:
                        parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_EVEN;
                        break;
                    case Parity.Odd:
                        parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_ODD;
                        break;
                    case Parity.Mark:
                        parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_MARK;
                        break;
                    case Parity.Space:
                        parity = FTD2XX_NET.FTDI.FT_PARITY.FT_PARITY_SPACE;
                        break;
                }

                byte stopbits = FTD2XX_NET.FTDI.FT_STOP_BITS.FT_STOP_BITS_1;

                switch (_stopbits)
                {
                    case System.IO.Ports.StopBits.One:
                    case System.IO.Ports.StopBits.OnePointFive:
                    default:
                        stopbits = FTD2XX_NET.FTDI.FT_STOP_BITS.FT_STOP_BITS_1;
                        break;
                    case System.IO.Ports.StopBits.Two:
                        stopbits = FTD2XX_NET.FTDI.FT_STOP_BITS.FT_STOP_BITS_2;
                        break;
                }

                _ftdi.SetDataCharacteristics(_databits, stopbits, parity);
            }
        }

        /// <summary>
        /// Gets an array of nodes that represent each currently attached FTDI device.
        /// </summary>
        /// <returns>An array of nodes that represent each attached FTDI device.</returns>
        /// <exception cref="FTD2XX_NET.FTDI.FT_EXCEPTION">An error occurred within the FTDI driver.</exception>
        public static FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[] GetAttached()
        {
            FTD2XX_NET.FTDI ftdi = new FTD2XX_NET.FTDI();

            uint devcount = 0;

            FTD2XX_NET.FTDI.FT_STATUS status = ftdi.GetNumberOfDevices(ref devcount);
            if (status == FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
            {
                FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[] nodes = new FTD2XX_NET.FTDI.FT_DEVICE_INFO_NODE[devcount];

                if (nodes.Length > 0)
                {
                    status = ftdi.GetDeviceList(nodes);
                    if (status != FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
                    {
                        throw new FTD2XX_NET.FTDI.FT_EXCEPTION(status.ToString());
                    }
                }

                return nodes;
            }

            throw new FTD2XX_NET.FTDI.FT_EXCEPTION(status.ToString());
        }

        /// <summary>
        /// Opens a connection to the FTDI device with the specified serial number.
        /// </summary>
        /// <param name="serialNumber">The serial number of the device to be connected.</param>
        /// <exception cref="FTD2XX_NET.FTDI.FT_EXCEPTION">An error occurred within the FTDI driver.</exception>
        public void Connect(string serialNumber)
        {
            FTD2XX_NET.FTDI.FT_STATUS status = _ftdi.OpenBySerialNumber(serialNumber);

            if (status != FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
                throw new FTD2XX_NET.FTDI.FT_EXCEPTION(status.ToString());

            // Apply timeout intervals
            _ftdi.SetTimeouts(ReadTimeout, WriteTimeout);
            
            // Apply the port settings
            ApplyBaudRate();
            ApplyCharacteristics();
            ApplyFlowControl();

            SerialNumber = serialNumber;
            PurgeRx();
        }

        /// <summary>
        /// Closes the connection with the device.
        /// </summary>
        public void Disconnect()
        {
            if (_ftdi.IsOpen)
                _ftdi.Close();
        }

        /// <summary>
        /// Purges and removes all data from the receive buffer of the underlying FTDI driver.
        /// </summary>
        public void PurgeRx()
        {
            if (_ftdi.IsOpen)
                _ftdi.Purge(FTD2XX_NET.FTDI.FT_PURGE.FT_PURGE_RX);
        }

        /// <summary>
        /// Purges and removes all data from the transmit buffer of the underlying FTDI driver.
        /// </summary>
        public void PurgeTx()
        {
            if (_ftdi.IsOpen)
                _ftdi.Purge(FTD2XX_NET.FTDI.FT_PURGE.FT_PURGE_TX);
        }

        /// <summary>
        /// Sets the RTS signal.
        /// </summary>
        /// <param name="enable">Set <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        public void SetRTS(bool enable)
        {
            if (_ftdi.IsOpen)
                _ftdi.SetRTS(enable);
        }

        /// <summary>
        /// Sets the DTR signal.
        /// </summary>
        /// <param name="enable">Set <c>true</c> to assert the signal; otherwise <c>false</c>.</param>
        public void SetDTR(bool enable)
        {
            if (_ftdi.IsOpen)
                _ftdi.SetDTR(enable);
        }

        /// <summary>
        /// Processes a status code returned by the FTDI driver. Throws an FTDIException
        /// with the appropriate message if the status indicates a failure.
        /// </summary>
        /// <param name="status">The status code to be processed.</param>
        /// <exception cref="DZX.Devices.FTDI.FTDIException">The status code represented an failure.</exception>
        private void Error(FTD2XX_NET.FTDI.FT_STATUS status)
        {
            if (status != FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
            {
                // Check FT_STATUS values returned from FTD2XX DLL calls
                switch (status)
                {
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_DEVICE_NOT_FOUND:
                        {
                            throw new FTDIException("FTDI device not found.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_DEVICE_NOT_OPENED:
                        {
                            throw new FTDIException("FTDI device not opened.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_DEVICE_NOT_OPENED_FOR_ERASE:
                        {
                            throw new FTDIException("FTDI device not opened for erase.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_DEVICE_NOT_OPENED_FOR_WRITE:
                        {
                            throw new FTDIException("FTDI device not opened for write.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_EEPROM_ERASE_FAILED:
                        {
                            throw new FTDIException("Failed to erase FTDI device EEPROM.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_EEPROM_NOT_PRESENT:
                        {
                            throw new FTDIException("No EEPROM fitted to FTDI device.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_EEPROM_NOT_PROGRAMMED:
                        {
                            throw new FTDIException("FTDI device EEPROM not programmed.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_EEPROM_READ_FAILED:
                        {
                            throw new FTDIException("Failed to read FTDI device EEPROM.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_EEPROM_WRITE_FAILED:
                        {
                            throw new FTDIException("Failed to write FTDI device EEPROM.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_FAILED_TO_WRITE_DEVICE:
                        {
                            throw new FTDIException("Failed to write to FTDI device.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_INSUFFICIENT_RESOURCES:
                        {
                            throw new FTDIException("Insufficient resources.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_INVALID_ARGS:
                        {
                            throw new FTDIException("Invalid arguments for FTD2XX function call.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_INVALID_BAUD_RATE:
                        {
                            throw new FTDIException("Invalid Baud rate for FTDI device.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_INVALID_HANDLE:
                        {
                            throw new FTDIException("Invalid handle for FTDI device.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_INVALID_PARAMETER:
                        {
                            throw new FTDIException("Invalid parameter for FTD2XX function call.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_IO_ERROR:
                        {
                            throw new FTDIException("FTDI device IO error.");
                        }
                    case FTD2XX_NET.FTDI.FT_STATUS.FT_OTHER_ERROR:
                        {
                            throw new FTDIException("An unexpected error has occurred when trying to communicate with the FTDI device.");
                        }
                    default:
                        break;
                }
            }
        }

        /// <summary>
        /// Returns the data any data that has been received and is immediately available.
        /// </summary>
        /// <returns>Any received data that available.</returns>
        public byte[] ReadAvailable()
        {
            if (_ftdi.IsOpen)
            {
                uint num = 0;

                FTD2XX_NET.FTDI.FT_STATUS status = _ftdi.GetRxBytesAvailable(ref num);
                if (status == FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
                {
                    if (num > 0)
                    {
                        byte[] buffer = new byte[num];

                        uint nread = 0;
                        _ftdi.Read(buffer, num, ref nread);

                        if (nread == num)
                            return buffer;

                        if (nread > 0)
                        {
                            byte[] data = new byte[nread];
                            Buffer.BlockCopy(buffer, 0, data, 0, (int)nread);
                            return data;
                        }
                    }
                }
            }

            return new byte[0];
        }

        /// <summary>
        /// Receives and returns the specified amount of data.
        /// </summary>
        /// <param name="nbytes">The number of data bytes to be received.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for the data to be received.</param>
        /// <returns>The data that has been received. Could be less than the requested amount.</returns>
        public byte[] Read(int nbytes, int timeout)
        {
            if (_ftdi.IsOpen)
            {
                byte[] buffer = new byte[nbytes];

                uint nread = 0;

                SetTimeouts((uint)timeout, WriteTimeout);
                FTD2XX_NET.FTDI.FT_STATUS status = _ftdi.Read(buffer, (uint)nbytes, ref nread);
                if (status == FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
                {
                    if (nread == nbytes)
                        return buffer;

                    if (nread > 0)
                    {
                        byte[] result = new byte[nread];
                        Buffer.BlockCopy(buffer, 0, result, 0, (int)nread);
                        return result;
                    }
                }
            }

            return new byte[0];
        }

        /// <summary>
        /// Writes the specified data.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        /// <exception cref="DZX.Devices.FTDI.FTDIException">A failure occurred.</exception>
        public void Write(byte[] data)
        {
            uint nwritten = 0;
            FTD2XX_NET.FTDI.FT_STATUS status = _ftdi.Write(data, data.Length, ref nwritten);
            if (status != FTD2XX_NET.FTDI.FT_STATUS.FT_OK)
            {
                Error(status);
            }

            if (nwritten != data.Length)
            {
                Error(FTD2XX_NET.FTDI.FT_STATUS.FT_IO_ERROR);
            }
        }

        /// <summary>
        /// Writes the specified data.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for the transfer to complete.</param>
        /// <exception cref="DZX.Devices.FTDI.FTDIException">A failure occurred.</exception>
        public void Write(byte[] data, int timeout)
        {
            if (timeout != WriteTimeout)
            {
                WriteTimeout = (uint)timeout;
                _ftdi.SetTimeouts(ReadTimeout, WriteTimeout);
            }

            Write(data);
        }

        /// <summary>
        /// Sets the communication timeouts for the device.
        /// </summary>
        /// <param name="readTimeout">The read timeout, in milliseconds.</param>
        /// <param name="writeTimeout">The write timeout, in milliseconds.</param>
        public void SetTimeouts(uint readTimeout, uint writeTimeout)
        {
            if (readTimeout != this.ReadTimeout)
            {
                this.ReadTimeout = readTimeout;
                _ftdi.SetTimeouts(ReadTimeout, WriteTimeout);
            }

            if (writeTimeout != this.WriteTimeout)
            {
                this.WriteTimeout = writeTimeout;
                _ftdi.SetTimeouts(ReadTimeout, WriteTimeout);
            }
        }
    }

    /// <summary>
    /// Represents an exception that occurred during communications with an FTDI device.
    /// </summary>
    public class FTDIException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FTDIException"/> class.
        /// </summary>
        public FTDIException() :
            base() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="FTDIException"/> class.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public FTDIException(string message) :
            base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="FTDIException"/> class.
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception.</param>
        /// <param name="innerException">The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public FTDIException(string message, Exception innerException) :
            base(message, innerException) { }
    }
}
