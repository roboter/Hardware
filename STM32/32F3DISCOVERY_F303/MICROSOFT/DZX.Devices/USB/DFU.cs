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
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace DZX.Devices.USB
{
    partial class USBDevice
    {
        /// <summary>
        /// Gets the current mode of the device if it supports DFU.
        /// </summary>
        public DFUMode Mode
        {
            get
            {
                // Is there an active DFU interface?
                if (DFUInterface != null)
                    return DFUInterface.Mode;

                // No selected DFU interface, assume runtime mode.
                return DFUMode.Runtime;
            }
        }

        /// <summary>
        /// Gets an indication of whether this <see cref="USBDevice"/> is programmable over a DFU interface.
        /// </summary>
        public bool Programmable { get { return _dfuInterfaces.Count > 0; } }

        /// <summary>
        /// Gets or sets a value indicating whether to perform verification of data that has been downloaded
        /// by uploading the image and validating it's contents.
        /// </summary>
        public bool Verify { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to automatically request a detach after successfully 
        /// performing an upload or download.
        /// </summary>
        public bool AutoDetachRuntime { get; set; }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for the device to complete
        /// a DFU detach operation.
        /// </summary>
        public int DetachTimeout { get; set; }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for the device to complete
        /// an individual DFU block transfer.
        /// </summary>
        public int TransferTimeout { get; set; }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for the device to manifest the
        /// downloaded firmware.
        /// </summary>
        public int ManifestTimeout { get; set; }

        /// <summary>
        /// The currently selected DFU interface, if any.
        /// </summary>
        private DFUInterface DFUInterface;

        /// <summary>
        /// Occurs when a DFU detach has been requested.
        /// </summary>
        public event DFUDetachEventHandler DetachRequested;

        /// <summary>
        /// Occurs when a DFU detach has completed and the device has re-connected in the other mode.
        /// </summary>
        public event DFUDetachEventHandler DetachCompleted;

        /// <summary>
        /// Occurs when each block of data has been downloaded to a device.
        /// </summary>
        public event BlockDownloadedEventHandler Downloading;

        /// <summary>
        /// Occurs when each block of data has been uploaded from a device.
        /// </summary>
        public event BlockUploadedEventHandler Uploading;

        /// <summary>
        /// Occurs when each block of data has been verified.
        /// </summary>
        public event BlockVerifiedEventHandler Verifying;

        /// <summary>
        /// Selects the DFU interface to be used for all DFU operations.
        /// </summary>
        /// <param name="intf">The number of the interface to be selected.</param>
        /// <returns>True upon success; otherwise false.</returns>
        public bool SelectDFUInterface(byte intf)
        {
            if (intf < _dfuInterfaces.Count)
            {
                DFUInterface = _dfuInterfaces[intf];
                return true;
            }

            return false;
        }


        /// <summary>
        /// Reads and returns the current status of the device DFU interface.
        /// </summary>
        /// <returns>The current status of the device DFU interface</returns>
        /// <exception cref="USBException">Insufficient response length for GetStatus()</exception>
        internal DFUStatus GetDFUStatus()
        {
            byte[] data = ControlTransfer(DFUInterface.Handle, 0xA1, 0x3, 0, 0, 6);
            if (data.Length >= 6)
            {
                DFUStatus status = new DFUStatus();

                status.Status = data[0];
                status.PollTimeout = (uint)((data[3] << 24) | (data[2] << 16) | data[1]);
                status.State = (DFUState)data[4];
                status.StringIdx = data[5];

                return status;
            }

            throw new USBException("Insufficient response length for GetStatus()");
        }

        /// <summary>
        /// Reads and returns the current state of the device DFU interface.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="DZX.Devices.USB.DFUException">Invalid response for Read DFU State</exception>
        internal DFUState GetDfuState()
        {
            byte[] data = ControlTransfer(DFUInterface.Handle, 0xA1, 0x5, 0, 0, 1);
            if (data != null && data.Length == 1)
            {
                return (DFUState)data[0];
            }

            throw new DFUException("Invalid response for Read DFU State");
        }

        /// <summary>
        /// Requests the device to perform a DETACH and switch it's mode.
        /// </summary>
        /// <returns>True upon success; otherwise false.</returns>
        public bool Detach()
        {
            return Detach(DetachTimeout);
        }

        /// <summary>
        /// Requests the device to perform a DETACH and switch it's mode.
        /// </summary>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for the device to switch modes.</param>
        /// <returns>True upon success; otherwise false.</returns>
        public bool Detach(int timeout)
        {
            // Get the desired mode after the detach
            DFUMode mode = (Mode == DFUMode.Runtime) ? DFUMode.Bootloader : DFUMode.Runtime;

            // Raise event that a DETACH is being requested
            OnDetachRequested(new DFUDetachEventArgs(Mode));

            // Request the detach
            ControlTransfer(DFUInterface.Handle, 0x21, 0, 0, 0);

            // Wait for the device to return in the new mode
            return CompleteDetach(mode, timeout);
        }

        /// <summary>
        /// Sends a DFU_ABORT request to the device.
        /// </summary>
        /// <exception cref="DZX.Devices.USB.DFUException">Device failed to enter dfuIDLE state</exception>
        public void DfuAbort()
        {
            // Send the request
            ControlTransfer(DFUInterface.Handle, 0x21, 0x6, 0, 0);

            // Read back the current state
            DFUState state = GetDfuState();

            // Ensure the device is now in the idle state
            if (state != DFUState.dfuIDLE)
                throw new DFUException("Device failed to enter dfuIDLE state");
        }


        /// <summary>
        /// Wait until the device is in the dfuDNLOADIDLE state.
        /// </summary>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the device to be
        /// in the dfuDNLOADIDLE state.</param>
        /// <returns>True if the device successfully entered the dfuDNLOADIDLE state; otherwise false.</returns>
        private bool WaitDownloadBusy(int timeout)
        {
            DateTime start = DateTime.Now;

            // Get the status to retrieve the poll interval from the device
            DFUStatus s = GetDFUStatus();

            // Initial state...
            DFUState state = s.State;

            // Wait while the device is busy with the downloaded data
            while (state == DFUState.dfuDNBUSY && (DateTime.Now - start).TotalMilliseconds < timeout)
            {
                // Only hit the device as often as it requested
                System.Threading.Thread.Sleep((int)s.PollTimeout);

                // Poll the state again
                state = GetDfuState();
            }

            // Did the device return to idle as expected?
            return (state == DFUState.dfuDNLOADIDLE);
        }

        /// <summary>
        /// Wait until the device completes the manifest stage and is in the dfuIDLE state.
        /// </summary>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the device to be
        /// in the dfuIDLE state.</param>
        /// <returns>True if the device successfully entered the dfuDNLOADIDLE state; otherwise false.</returns>
        private bool WaitManifest(int timeout)
        {
            DateTime start = DateTime.Now;

            // Get the status to retrieve the poll interval from the device
            DFUStatus s = GetDFUStatus();

            // Initial state...
            DFUState state = s.State;

            // Wait while the device is busy with the downloaded data
            while (state != DFUState.dfuIDLE && (DateTime.Now - start).TotalMilliseconds < timeout)
            {
                // Only hit the device as often as it requested
                System.Threading.Thread.Sleep((int)s.PollTimeout);

                // Poll the state again
                state = GetDfuState();
            }

            // Did the device return to idle as expected?
            return (state == DFUState.dfuIDLE);
        }

        /// <summary>
        /// Downloads the specified data to the device.
        /// </summary>
        /// <param name="data">The data to be downloaded to the device.</param>
        /// <exception cref="System.NotSupportedException">This device not support any DFU operations</exception>
        /// <exception cref="DZX.Devices.USB.DFUException">
        /// Failed to switch to bootloader mode
        /// or
        /// Device reported TransferSize = '0'
        /// or
        /// Download failed
        /// or
        /// Error downloading
        /// or
        /// Failed to switch to runtime mode
        /// </exception>
        public void Download(byte[] data)
        {
            if (DFUInterface == null)
                throw new NotSupportedException("This device not support any DFU operations");
            
            int total = 0;
            ushort lba = 0;

            if (Mode != DFUMode.Bootloader)
            {
                // Device isn't in boot mode, command mode switch
                if (!Detach())
                    throw new DFUException("Failed to switch to bootloader mode");
            }

            // Check current state of the device
            DFUState state = GetDfuState();
            if (state != DFUState.dfuIDLE)
            {
                // Send abort command to force device to dfuIDLE state
                DfuAbort();
            }

            ushort transfersize = DFUInterface.FunctionalDescriptor.wTransferSize;
            if (transfersize == 0)
                throw new DFUException("Device reported TransferSize = '0'");

            OnDownloading(new BlockDownloadedEventArgs(0, data.Length));

            while (total < data.Length)
            {
                int len = data.Length - total;
                if (len > transfersize)
                    len = transfersize;

                byte[] buf = new byte[len];
                Buffer.BlockCopy(data, total, buf, 0, len);

                ControlTransfer(DFUInterface.Handle, 0x21, 0x1, lba, 0, buf);

                if (!WaitDownloadBusy(TransferTimeout))
                    throw new DFUException("Download failed");


                total += (int)len;
                lba++;

                OnDownloading(new BlockDownloadedEventArgs(total, data.Length));
            }

            // Transfer a download of block size zero to indicate the end of downloading
            ControlTransfer(DFUInterface.Handle, 0x21, 0x1, 0, 0, new byte[0]);

            // Wait for the device to complete the manifest stage
            if (!WaitManifest(ManifestTimeout))
            {
                throw new DFUException("Device failed to return to idle state");
            }

            if (Verify)
            {
                VerifyData(data);
            }

            if (AutoDetachRuntime)
            {
                if (!Detach())
                    throw new DFUException("Failed to switch to runtime mode");
            }
        }

        /// <summary>
        /// Verifies the data that has been downloaded to a device.
        /// </summary>
        /// <param name="data">The data that has been downloaded.</param>
        /// <exception cref="DZX.Devices.USB.DFUException">
        /// No response from device
        /// or
        /// Upload terminated by device
        /// or
        /// </exception>
        private void VerifyData(byte[] data)
        {
            ushort transfersize = DFUInterface.FunctionalDescriptor.wTransferSize;

            int total = 0;
            ushort lba = 0;

            OnVerifying(new BlockVerifiedEventArgs(0, data.Length));

            while (total < data.Length)
            {
                int len = data.Length - total;
                if (len > transfersize)
                    len = transfersize;

                byte[] buf = ControlTransfer(DFUInterface.Handle, 0xA1, 0x2, lba, 0, (ushort)len);
                if (buf == null)
                    throw new DFUException("No response from device");

                if (buf.Length < len)
                    throw new DFUException("Upload terminated by device");

                for (int i = 0; i < len; i++)
                {
                    if (buf[i] != data[total + i])
                        throw new DFUException(string.Format("Failed verification at byte index {0}", total + i));
                }

                total += len;
                lba++;

                OnVerifying(new BlockVerifiedEventArgs(total, data.Length));
            }
        }

        /// <summary>
        /// Uploads the specified amount of data from the device.
        /// </summary>
        /// <param name="length">The total amount, in bytes, of data to be uploaded from the device.</param>
        /// <returns>The data that has been received from the device.</returns>
        /// <exception cref="System.NotSupportedException">This device not support any DFU operations</exception>
        /// <exception cref="DZX.Devices.USB.DFUException">
        /// Failed to switch to bootloader mode
        /// or
        /// No response from device
        /// or
        /// Device terminated upload unexpectedly
        /// or
        /// Failed to switch to runtime mode
        /// </exception>
        public byte[] Upload(int length)
        {
            if (DFUInterface == null)
                throw new NotSupportedException("This device not support any DFU operations");

            if (Mode != DFUMode.Bootloader)
            {
                if (!Detach())
                    throw new DFUException("Failed to switch to bootloader mode");
            }

            DFUState state = GetDfuState();
            if (state != DFUState.dfuIDLE)
            {
                DfuAbort();
            }

            ushort transfersize = _dfuInterfaces[0].FunctionalDescriptor.wTransferSize;

            byte[] data = new byte[length];

            int total = 0;
            ushort lba = 0;

            OnUploading(new BlockUploadedEventArgs(0, length));

            while (total < length)
            {
                int len = length - total;
                if (len > transfersize)
                    len = transfersize;

                byte[] buf = ControlTransfer(DFUInterface.Handle, 0xA1, 0x2, lba, 0, (ushort)len);
                if (buf == null)
                    throw new DFUException("No response from device");

                if (buf.Length < len)
                    throw new DFUException("Device response shorter than expected");
                

                Buffer.BlockCopy(buf, 0, data, total, len);

                if (buf.Length < len)
                {
                    if (total < length)
                        throw new DFUException("Device terminated upload unexpectedly");
                }

                total += len;
                lba++;

                OnUploading(new BlockUploadedEventArgs(total, length));
            }

            if (AutoDetachRuntime)
            {
                if (!Detach())
                    throw new DFUException("Failed to switch to runtime mode");
            }

            return data;
        }

        /// <summary>
        /// Completes the DETACH request by waiting for the specified mode to become available.
        /// </summary>
        /// <param name="mode">The mode to wait for.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for the mode to arrive.</param>
        /// <returns>True upon success; otherwise false.</returns>
        private bool CompleteDetach(DFUMode mode, int timeout)
        {
            System.Windows.Forms.Application.DoEvents();
            System.Threading.Thread.Sleep(50);
            System.Windows.Forms.Application.DoEvents();

            DateTime start = DateTime.Now;

            while ((DateTime.Now - start).TotalMilliseconds < timeout)
            {
                System.Windows.Forms.Application.DoEvents();

                if (Connected)
                {
                    if (Mode == mode)
                    {
                        OnDetachCompleted(new DFUDetachEventArgs(mode));
                        return true;
                    }
                }

                System.Threading.Thread.Sleep(10);
            }

            return false;
        }

        /// <summary>
        /// Raises the <see cref="E:DetachRequested" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DFUDetachEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDetachRequested(DFUDetachEventArgs e)
        {
            DFUDetachEventHandler handler = DetachRequested;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:DetachCompleted" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DFUDetachEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDetachCompleted(DFUDetachEventArgs e)
        {
            DFUDetachEventHandler handler = DetachCompleted;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Downloading" /> event.
        /// </summary>
        /// <param name="e">The <see cref="BlockDownloadedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDownloading(BlockDownloadedEventArgs e)
        {
            BlockDownloadedEventHandler handler = Downloading;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Uploading" /> event.
        /// </summary>
        /// <param name="e">The <see cref="BlockUploadedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnUploading(BlockUploadedEventArgs e)
        {
            BlockUploadedEventHandler handler = Uploading;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:Verifying" /> event.
        /// </summary>
        /// <param name="e">The <see cref="BlockVerifiedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnVerifying(BlockVerifiedEventArgs e)
        {
            BlockVerifiedEventHandler handler = Verifying;
            if (handler != null)
            {
                handler(this, e);
            }
        }
    }

    /// <summary>
    /// Represents a device firmware update (DFU) interface provided by a device.
    /// </summary>
    public class DFUInterface
    {
        /// <summary>
        /// Gets the current mode of the interface.
        /// </summary>
        public DFUMode Mode { get; private set; }

        /// <summary>
        /// Gets the alternate setting value for the interface.
        /// </summary>
        public byte AlternateSetting { get; private set; }

        /// <summary>
        /// Gets the handle to be used for communications with the interface.
        /// </summary>
        public IntPtr Handle { get; private set; }

        /// <summary>
        /// Gets or sets the description of the interface.
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the functional descriptor for the interface.
        /// </summary>
        public DFUFunctionalDescriptor FunctionalDescriptor { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DFUInterface"/> class.
        /// </summary>
        /// <param name="alternateSetting">The alternate setting for the interface.</param>
        /// <param name="handle">The handle for the interface.</param>
        /// <param name="mode">The current mode of the interface.</param>
        public DFUInterface(byte alternateSetting, IntPtr handle, DFUMode mode)
        {
            this.AlternateSetting = alternateSetting;
            this.Handle = handle;
            this.Mode = mode;
        }
    }

    /// <summary>
    /// Represents a possible state of a device firmware update (DFU) interface.
    /// </summary>
    internal enum DFUState : byte
    {
        appIDLE = 0,
        appDETACH,
        dfuIDLE,
        dfuDNLOADSYNC,
        dfuDNBUSY,
        dfuDNLOADIDLE,
        dfuMANIFESTSYNC,
        dfuMANIFEST,
        dfuMANIFESTWAITRESET,
        dfuUPLOADIDLE,
        dfuERROR,
    }

    /// <summary>
    /// Represents the status of a DFU interface.
    /// </summary>
    internal class DFUStatus
    {
        /// <summary>
        /// Gets or sets the status code value for the interface.
        /// </summary>
        public byte Status { get; set; }

        /// <summary>
        /// Gets or sets the poll timeout, in milliseconds, for the interface.
        /// </summary>
        public uint PollTimeout { get; set; }

        /// <summary>
        /// Gets or sets the state code value for the interface.
        /// </summary>
        public DFUState State { get; set; }

        /// <summary>
        /// Gets or sets the index of the string that represents the vendor specific status.
        /// </summary>
        public byte StringIdx { get; set; }
    }

    /// <summary>
    /// Represents a mode of a DFU interface.
    /// </summary>
    public enum DFUMode
    {
        /// <summary>
        /// The interface is in the DFU mode.
        /// </summary>
        Bootloader = 0,

        /// <summary>
        /// The interface is in the runtime mode.
        /// </summary>
        Runtime,
    }

    /// <summary>
    /// Represents an exception caused from the DFU layer.
    /// </summary>
    [Serializable]
    public class DFUException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DFUException"/> class.
        /// </summary>
        public DFUException() :
            base() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="DFUException"/> class.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public DFUException(string message) :
            base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="DFUException"/> class.
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception.</param>
        /// <param name="innerException">The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public DFUException(string message, Exception innerException) :
            base(message, innerException) { }
    }

    /// <summary>
    /// An application-defined function that handles an event raised when a device has performed a detach event.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
    public delegate void DFUDetachEventHandler(object sender, DFUDetachEventArgs e);

    /// <summary>
    /// Represents the arguments for a DFU Detach event.
    /// </summary>
    public class DFUDetachEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the mode of the device when the event occurred.
        /// </summary>
        public DFUMode Mode { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DFUDetachEventArgs"/> class.
        /// </summary>
        /// <param name="mode">The mode.</param>
        public DFUDetachEventArgs(DFUMode mode)
        {
            this.Mode = mode;
        }
    }
}
