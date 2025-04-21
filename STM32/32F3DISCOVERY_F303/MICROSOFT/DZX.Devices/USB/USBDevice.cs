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
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;
using DZX.Devices.Watchers;

namespace DZX.Devices.USB
{
    /// <summary>
    /// Represents a generic USB device that utilizes the WinUSB driver for communications.
    /// </summary>
    public partial class USBDevice : IDisposable
    {
        /// <summary>
        /// The default interface unique identifier as provided by DZX.
        /// </summary>
        public static readonly Guid DefaultInterfaceGuid = new Guid("{F1309947-BB1B-4B26-B611-79C234D26BCD}");

        /// <summary>
        /// Provides an indication of whether this device has been previously _disposed.
        /// </summary>
        private bool _disposed = false;

        /// <summary>
        /// An object for synchronizing access to the device.
        /// </summary>
        private object _sync = new object();

        /// <summary>
        /// A collection of _readers that continuously read and queue received data from IN pipes.
        /// </summary>
        private Dictionary<byte, PipeReader> _readers = new Dictionary<byte, PipeReader>();

        /// <summary>
        /// A collection of DFU interfaces supported by the device.
        /// </summary>
        private Dictionary<byte, DFUInterface> _dfuInterfaces = new Dictionary<byte, DFUInterface>();

        /// <summary>
        /// The available pipes for the device.
        /// </summary>
        private Dictionary<byte, PipeInfo> _pipes = new Dictionary<byte, PipeInfo>();

        /// <summary>
        /// The file handle for this device.
        /// </summary>
        private SafeFileHandle _fileHandle;

        /// <summary>
        /// The interface handle for this device.
        /// </summary>
        private IntPtr _handle;

        /// <summary>
        /// An interface _watcher for receiving attach/detach events. 
        /// </summary>
        private InterfaceWatcher _watcher;

        /// <summary>
        /// Gets or sets the unique identifier for the interface implemented by the device.
        /// </summary>
        public Guid InterfaceGuid { get; set; }

        /// <summary>
        /// Gets an indication of whether this device is currently considered to be connected and open for communications.
        /// </summary>
        public bool Connected { get; private set; }

        /// <summary>
        /// Gets the connection path for this device.
        /// </summary>
        public string Path { get; private set; }

        /// <summary>
        /// Gets the identifier for the device.
        /// </summary>
        public DeviceID ID { get; private set; }

        /// <summary>
        /// Gets or sets the alternate interface number.
        /// </summary>
        public byte AlternateInterfaceNumber { get; set; }

        /// <summary>
        /// Gets the vendor identifier number as reported by the device.
        /// </summary>
        public ushort VendorID { get; private set; }

        /// <summary>
        /// Gets the product identifier number as reported by the device.
        /// </summary>
        public ushort ProductID { get; private set; }

        /// <summary>
        /// Gets the name of the manufacturer of the device.
        /// </summary>
        public string ManufacturerName { get; private set; }

        /// <summary>
        /// Gets the name of the product of the device.
        /// </summary>
        public string ProductName { get; private set; }

        /// <summary>
        /// Gets the serial number of the device.
        /// </summary>
        public string SerialNumber { get; private set; }

        /// <summary>
        /// Gets the available transmit pipes.
        /// </summary>
        public PipeInfo[] TxPipes { get; private set; }

        /// <summary>
        /// Gets the available receive pipes.
        /// </summary>
        public PipeInfo[] RxPipes { get; private set; }

        /// <summary>
        /// Gets or sets the default write timeout, in milliseconds.
        /// </summary>
        public int WriteTimeout { get; set; }

        /// <summary>
        /// Gets the last error code.
        /// </summary>
        public int LastErrorCode { get; private set; }

        /// <summary>
        /// Occurs when the connected status has changed.
        /// </summary>
        public event EventHandler ConnectedChanged;


        /// <summary>
        /// Initializes a new instance of the <see cref="USBDevice"/> class.
        /// </summary>
        public USBDevice()
        {
            InterfaceGuid = DefaultInterfaceGuid;
            AlternateInterfaceNumber = 0;

            WriteTimeout = 5000;
            TransferTimeout = 5000;
            DetachTimeout = 5000;
            ManifestTimeout = 5000;

            AutoDetachRuntime = true;
            Verify = false;
        }


        /// <summary>
        /// Finalizes an instance of the <see cref="USBDevice"/> class.
        /// </summary>
        ~USBDevice()
        {
            Dispose(false);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources.
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    Disconnect();
                }

                _disposed = true;
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
        /// Handles the DeviceAttached event of the mNotifer control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="DeviceAttachedEventArgs"/> instance containing the event data.</param>
        void mNotifer_DeviceAttached(object sender, DeviceAttachedEventArgs e)
        {
            // Is the device that just attached the same device as this?
            if (e.Path == Path)
            {
                // Only reconnect if not connected
                if (!Connected)
                {
                    try
                    {
                        // Attempt to reconnect
                        Connect(e.Path);
                    }
                    catch (Exception)
                    {
                        Disconnect();
                    }
                }
            }
        }

        /// <summary>
        /// Handles the DeviceDetached event of the mNotifer control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
        void mNotifer_DeviceDetached(object sender, DeviceDetachedEventArgs e)
        {
            // Did this device just detach?
            if (e.Path == Path)
            {
                // Yes, close this device
                Disconnect(true);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:ConnectedChanged" /> event.
        /// </summary>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        protected virtual void OnConnectedChanged(EventArgs e)
        {
            EventHandler handler = ConnectedChanged;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Filters and returns matches for the specified devices.
        /// </summary>
        /// <param name="paths">The device paths to be filtered.</param>
        /// <param name="id">The device identifier used to find matches.</param>
        /// <returns>An array of device paths that match the given device identifier</returns>
        private static string[] FilterByID(string[] paths, DeviceID id)
        {
            List<string> matches = new List<string>();

            foreach (string path in paths)
            {
                using (USBDevice device = new USBDevice())
                {
                    try
                    {
                        device.Connect(path);

                        if (device.ID.CompareTo(id) == 0)
                            matches.Add(path);
                    }
                    catch (USBException) { }
                }
            }

            return matches.ToArray();
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified id.
        /// </summary>
        /// <param name="id">The id used to filter the attached devices. Formatted as vendorID:productID:serialNumber</param>
        /// <returns>An array of connection paths that match the specified id.</returns>
        public static string[] GetAttached(string id)
        {
            return GetAttached(DefaultInterfaceGuid, id);
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified id.
        /// </summary>
        /// <param name="intfGuid">The interface guid implemented by the devices to be returned.</param>
        /// <param name="id">The text id of the target device (in format of vid:pid or vid:pid:sn).</param>
        /// <returns>An array of connection paths that match the specified ids.</returns>
        public static string[] GetAttached(Guid intfGuid, string id)
        {
            return FilterByID(GetAttached(intfGuid), DeviceID.FromText(id));
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified ids.
        /// </summary>
        /// <param name="vendorID">The vendor ID used to filter the attached devices.</param>
        /// <param name="productID">The product ID used to filter the attached devices.</param>
        /// <returns>An array of connection paths that match the specified ids.</returns>
        public static string[] GetAttached(ushort vendorID, ushort productID)
        {
            return GetAttached(DefaultInterfaceGuid, vendorID, productID);
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified ids.
        /// </summary>
        /// <param name="intfGuid">The interface guid implemented by the devices to be returned.</param>
        /// <param name="vendorID">The vendor ID used to filter the attached devices.</param>
        /// <param name="productID">The product ID used to filter the attached devices.</param>
        /// <returns>An array of connection paths that match the specified ids.</returns>
        public static string[] GetAttached(Guid intfGuid, ushort vendorID, ushort productID)
        {
            return FilterByID(GetAttached(intfGuid), new DeviceID(vendorID, productID));
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified ids.
        /// </summary>
        /// <param name="vendorID">The vendor ID used to filter the attached devices.</param>
        /// <param name="productID">The product ID used to filter the attached devices.</param>
        /// <param name="serialNumber">The serial number used to filter the attached devices.</param>
        /// <returns>An array of connection paths that match the specified ids.</returns>
        public static string[] GetAttached(ushort vendorID, ushort productID, string serialNumber)
        {
            return GetAttached(DefaultInterfaceGuid, vendorID, productID, serialNumber);
        }

        /// <summary>
        /// Gets the connection paths for attached devices that match the specified ids.
        /// </summary>
        /// <param name="intfGuid">The interface guid implemented by the devices to be returned.</param>
        /// <param name="vendorID">The vendor ID used to filter the attached devices.</param>
        /// <param name="productID">The product ID used to filter the attached devices.</param>
        /// <param name="serialNumber">The serial number used to filter the attached devices.</param>
        /// <returns>An array of connection paths that match the specified ids.</returns>
        public static string[] GetAttached(Guid intfGuid, ushort vendorID, ushort productID, string serialNumber)
        {
            return FilterByID(GetAttached(intfGuid), new DeviceID(vendorID, productID, serialNumber));
        }

        /// <summary>
        /// Gets the connection paths for all attached devices that implement the default interface guid.
        /// </summary>
        /// <returns>An array of connection paths.</returns>
        public static string[] GetAttached()
        {
            return GetAttached(DefaultInterfaceGuid);
        }

        /// <summary>
        /// Gets the connection paths for attached devices that implement the specified interface guid.
        /// </summary>
        /// <param name="intfGuid">The interface guid implemented by the devices to be returned.</param>
        /// <returns>An array of connection paths.</returns>
        public static string[] GetAttached(Guid intfGuid)
        {
            List<string> paths = new List<string>();

            IntPtr detailDataBuffer = IntPtr.Zero;
            IntPtr deviceInfoSet = new System.IntPtr();

            try
            {
                // Open a handle to the PNP development node
                deviceInfoSet = SetupAPI.SetupDiGetClassDevs(ref intfGuid, 
                                                            IntPtr.Zero, 
                                                            IntPtr.Zero, 
                                                            SetupAPI.DIGCF_PRESENT | SetupAPI.DIGCF_DEVICEINTERFACE);

                int memberIndex = 0;

                bool success = true;

                do
                {
                    // Get the path for the hid device.
                    string path = ReadDevicePath(intfGuid, deviceInfoSet, memberIndex);

                    if (!string.IsNullOrEmpty(path))
                    {
                        // Force the path to use all lower case. Do this so that when a connect/disconnect
                        // event is raised from windows, the path within it's args matches this one.
                        path = path.ToLower();

                        // Add the device identity for the discovered path
                        paths.Add(path);

                        // Go to the next device
                        memberIndex++;
                    }
                    else
                    {
                        success = false;
                    }
                }
                while (success);
            }
            finally
            {
                if (deviceInfoSet != IntPtr.Zero)
                    SetupAPI.SetupDiDestroyDeviceInfoList(deviceInfoSet);
            }

            return paths.ToArray();
        }

        /// <summary>
        /// Reads the device path for a device from the speecified device index.
        /// </summary>
        /// <param name="guid">The guid for the device interface.</param>
        /// <param name="deviceInfoSet">The information set for the target device.</param>
        /// <param name="deviceIndex">The zero-based index for the target device.</param>
        /// <returns>The target device's path.</returns>
        private static string ReadDevicePath(Guid guid, IntPtr deviceInfoSet, int deviceIndex)
        {
            IntPtr detailDataBuffer = IntPtr.Zero;

            try
            {
                SetupAPI.SP_DEVICE_INTERFACE_DATA MyDeviceInterfaceData = new SetupAPI.SP_DEVICE_INTERFACE_DATA();

                //Initialize the size member...
                //Size is 28 for 32-bit and 32 for 64-bit.
                MyDeviceInterfaceData.cbSize = Marshal.SizeOf(MyDeviceInterfaceData);

                if (SetupAPI.SetupDiEnumDeviceInterfaces(deviceInfoSet, IntPtr.Zero, ref guid, deviceIndex, ref MyDeviceInterfaceData))
                {
                    Int32 bufferSize = 0;

                    SetupAPI.SetupDiGetDeviceInterfaceDetail(deviceInfoSet,
                                                                    ref MyDeviceInterfaceData,
                                                                    IntPtr.Zero,
                                                                    0,
                                                                    ref bufferSize,
                                                                    IntPtr.Zero);

                    // Allocate memory for the SP_DEVICE_INTERFACE_DETAIL_DATA structure using the returned buffer size.
                    detailDataBuffer = Marshal.AllocHGlobal(bufferSize);

                    // Store cbSize in the first bytes of the array. The number of bytes varies with 32- and 64-bit systems.
                    Marshal.WriteInt32(detailDataBuffer, (IntPtr.Size == 4) ? (4 + Marshal.SystemDefaultCharSize) : 8);

                    SetupAPI.SetupDiGetDeviceInterfaceDetail(deviceInfoSet,
                                                            ref MyDeviceInterfaceData,
                                                            detailDataBuffer,
                                                            bufferSize,
                                                            ref bufferSize,
                                                            IntPtr.Zero);


                    // Skip over cbsize (4 bytes) to get the address of the devicePathName.

                    IntPtr pDevicePathName = new IntPtr(detailDataBuffer.ToInt32() + 4);

                    // Get the String containing the devicePathName.
                    return Marshal.PtrToStringAuto(pDevicePathName);

                }

                return "";
            }
            finally
            {
                if (detailDataBuffer != IntPtr.Zero)
                {
                    // Free the memory allocated previously by AllocHGlobal.

                    Marshal.FreeHGlobal(detailDataBuffer);
                }
            }
        }

        /// <summary>
        /// Gets the application mode for the device at the specified path.
        /// </summary>
        /// <param name="path">The path of the target device.</param>
        /// <returns>The current mode of the device at the specified path.</returns>
        public static DFUMode GetMode(string path)
        {
            using (USBDevice device = new USBDevice())
            {
                device.Connect(path);
                return device.Mode;
            }
        }

        /// <summary>
        /// Gets a string representation for the last Win32 error that has occurred.
        /// </summary>
        /// <returns>The string representation of the last Win32 error.</returns>
        private string GetLastError()
        {
            LastErrorCode = Marshal.GetLastWin32Error();
            return new Win32Exception(LastErrorCode).Message;
        }

        /// <summary>
        /// Establishes a connection with the specified device.
        /// </summary>
        /// <param name="path">The connection path to the device to be connected.</param>
        /// <exception cref="DZX.Devices.USB.USBException">CreateFile() Failed</exception>
        /// <exception cref="DZX.Devices.USB.USBException">WinUsb_Initialize() Failed</exception>
        public void Connect(string path)
        {
            Disconnect();

            lock (_sync)
            {

                // Is this a new connection path than a previous connection?
                if (Path != path)
                {
                    // Remove _watcher to re-create for the new connection path
                    if (_watcher != null)
                    {
                        _watcher.Dispose();
                        _watcher = null;
                    }
                }

                Path = path;

                _fileHandle = Kernel32.CreateFile(path,
                                            Kernel32.GENERIC_READ | Kernel32.GENERIC_WRITE,
                                            Kernel32.FILE_SHARE_READ | Kernel32.FILE_SHARE_WRITE,
                                            IntPtr.Zero,
                                            Kernel32.OPEN_EXISTING,
                                            Kernel32.FILE_FLAG_OVERLAPPED,
                                            IntPtr.Zero);

                if (_fileHandle.IsInvalid)
                    throw new USBException(string.Format("CreateFile() Failed. '{0}'", GetLastError()));

                if (!WinUSB.WinUsb_Initialize(_fileHandle, ref _handle))
                    throw new USBException(string.Format("WinUsb_Initialize() Failed. '{0}'", GetLastError()));



                // Fetch the device descriptor
                USBDeviceDescriptor deviceDescriptor = ReadDeviceDescriptor();

                // Parse the device ID's
                VendorID = deviceDescriptor.idVendor;
                ProductID = deviceDescriptor.idProduct;

                // Read and cache the device strings
                if (deviceDescriptor.iManufacturer > 0)
                    ManufacturerName = ReadStringDescriptor(deviceDescriptor.iManufacturer);
                else
                    ManufacturerName = "";

                if (deviceDescriptor.iProduct > 0)
                    ProductName = ReadStringDescriptor(deviceDescriptor.iProduct);
                else
                    ProductName = "";

                if (deviceDescriptor.iSerialNumber > 0)
                    SerialNumber = ReadStringDescriptor(deviceDescriptor.iSerialNumber);
                else
                    SerialNumber = "";

                ID = new DeviceID(VendorID, ProductID, SerialNumber);

                // Query and cache information about the available pipes
                _pipes.Clear();

                List<PipeInfo> txpipes = new List<PipeInfo>();
                List<PipeInfo> rxpipes = new List<PipeInfo>();

                byte alt = 0;
                if (!WinUSB.WinUsb_GetCurrentAlternateSetting(_handle, ref alt))
                    throw new USBException(string.Format("WinUsb_GetCurrentAlternateSetting() Failed. '{0}'", GetLastError()));

                USBInterfaceDescriptor intf = ReadInterfaceDescriptor(_handle, alt);
                if (intf.bInterfaceClass == 0xFE && intf.bInterfaceSubClass == 0x01)
                {
                    DFUInterface dfuInterface = new DFUInterface(alt, _handle, intf.bInterfaceProtocol == 1 ? DFUMode.Runtime : DFUMode.Bootloader);
                    _dfuInterfaces.Add(alt, dfuInterface);

                    // Read the configuration descriptor
                    byte[] cfgdes2 = ReadDescriptor(_handle, 0x2, 0x0);

                    // Parse out the DFU functional descriptor
                    dfuInterface.FunctionalDescriptor = ParseDescriptor<DFUFunctionalDescriptor>(cfgdes2, 0x21);
                }


                if (_dfuInterfaces.Count > 0)
                {
                    // Select the first DFU interface by default
                    DFUInterface = _dfuInterfaces[0];
                }

                for (byte idx = 0; idx < intf.bNumEndpoints; idx++)
                {
                    PipeInfo pi = QueryPipeInformation(idx);
                    _pipes.Add(pi.ID, pi);

                    if ((pi.ID & 0x80) == 0x80)
                        rxpipes.Add(pi);
                    else
                        txpipes.Add(pi);
                }


                TxPipes = txpipes.ToArray();
                RxPipes = rxpipes.ToArray();

                // Initialize all host transmit pipes
                foreach (PipeInfo pipe in TxPipes)
                {
                    // Flush any existing data
                    ResetPipe(pipe.ID);

                    // Configure to auto clear stalls
                    SetPipeAutoClearStall(pipe.ID, 1);

                    // Configure to short packet terminate to signal end-of-message
                    SetPipeShortPacketTerminate(pipe.ID, 1);
                }

                // Initialize all host receive pipes
                foreach (PipeInfo pipe in RxPipes)
                {
                    // Configure to auto clear stalls
                    SetPipeAutoClearStall(pipe.ID, 1);

                    // Flush any existing data
                    ResetPipe(pipe.ID);
                }


                if (_watcher == null)
                {
                    // Create a _watcher to automatically disconnect if the physical device is detached
                    _watcher = new InterfaceWatcher(InterfaceGuid);
                    _watcher.DeviceAttached += mNotifer_DeviceAttached;
                    _watcher.DeviceDetached += mNotifer_DeviceDetached;
                }

                // Kick off threads to read all receive pipes
                StartReaders();

                // Considered to be connected now
                Connected = true;
            }

            OnConnectedChanged(EventArgs.Empty); 
        }

        /// <summary>
        /// Closes the connection to the device.
        /// </summary>
        public void Disconnect()
        {
            Disconnect(false);
        }

        /// <summary>
        /// Closes this device.
        /// </summary>
        /// <param name="detached">True if called from the _watcher; otherwise called by the user.</param>
        private void Disconnect(bool detached)
        {
            bool disconnected = false;

            lock (_sync)
            {
                StopReaders();

                if (!detached)
                {
                    if (_watcher != null)
                    {
                        _watcher.Dispose();
                        _watcher = null;
                    }
                }

                if (Connected)
                    disconnected = true;

                Connected = false;

                foreach (DFUInterface intf in _dfuInterfaces.Values)
                {
                    if (intf.Handle != _handle)
                        WinUSB.WinUsb_Free(intf.Handle);
                }

                _dfuInterfaces.Clear();

                if (_handle != IntPtr.Zero)
                {
                    WinUSB.WinUsb_Free(_handle);
                    _handle = IntPtr.Zero;
                }

                if (_fileHandle != default(SafeFileHandle))
                {
                    if (!_fileHandle.IsClosed)
                        _fileHandle.Close();

                    _fileHandle.Dispose();
                    _fileHandle = default(SafeFileHandle);
                }
            }

            if (disconnected)
            {
                OnConnectedChanged(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Queries and returns information describing the specified pipe.
        /// </summary>
        /// <param name="index">The index of the target pipe.</param>
        /// <returns>Information describing the specified pipe.</returns>
        /// <exception cref="DZX.Devices.USB.USBException">The transfer failed.</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        private PipeInfo QueryPipeInformation(byte index)
        {
            WinUSB.WINUSB_PIPE_INFORMATION natinfo = new WinUSB.WINUSB_PIPE_INFORMATION();

            if (!WinUSB.WinUsb_QueryPipe(_handle, AlternateInterfaceNumber, index, ref natinfo))
                throw new USBException(string.Format("WinUsb_QueryPipe() Failed. '{0}'", GetLastError()));

            PipeInfo info = new PipeInfo();

            info.ID = natinfo.PipeId;
            info.Interval = natinfo.Interval;
            info.MaxPacketSize = natinfo.MaximumPacketSize;
                        
            switch (natinfo.PipeType)
            {
                case WinUSB.USBPIPETYPE.Control:
                    info.TransferType = TransferType.Control;
                    break;
                case WinUSB.USBPIPETYPE.Isochronous:
                    info.TransferType = TransferType.Isochronous;
                    break;
                case WinUSB.USBPIPETYPE.Bulk:
                    info.TransferType = TransferType.Bulk;
                    break;
                case WinUSB.USBPIPETYPE.Interrupt:
                    info.TransferType = TransferType.Interrupt;
                    break;
            }

            return info;
        }

        /// <summary>
        /// Returns information about a specific pipe.
        /// </summary>
        /// <param name="pipeID">The identifier for the target pipe.</param>
        /// <returns>Information describing the specified pipe.</returns>
        /// <exception cref="DZX.Devices.USB.USBException">The specified pipe was not found.</exception>
        public PipeInfo GetPipeInformation(byte pipeID)
        {
            if (_pipes.ContainsKey(pipeID))
            {
                return _pipes[pipeID];
            }

            throw new USBException(string.Format("No pipe found with ID {0:X2}", pipeID));
        }

        /// <summary>
        /// Resets a pipe on the device.
        /// </summary>
        /// <param name="pipeID">The identifier for the pipe to be reset.</param>
        /// <exception cref="DZX.USB.USBException">The call to WinUsb_ResetPipe() failed.</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        public void ResetPipe(byte pipeID)
        {
            if ((pipeID & 0x80) != 0)
            {
                ReadAvailable(pipeID);
            }

            if (!WinUSB.WinUsb_ResetPipe(_handle, pipeID))
            {
                throw new USBException(string.Format("WinUsb_ResetPipe() Failed. '{0}'", GetLastError()));
            }
        }

        /// <summary>
        /// Creates and returns a descriptor with the specified values.
        /// </summary>
        /// <typeparam name="T">The type of descriptor.</typeparam>
        /// <param name="data">The data that represents the data.</param>
        /// <param name="descriptorType">Type of the descriptor.</param>
        /// <returns>The initialized descriptor.</returns>
        private T ParseDescriptor<T>(byte[] data, byte descriptorType)
        {
            int idx = 0;

            while (idx < data.Length)
            {
                int len = data[idx];
                if (data[idx+1] == descriptorType)
                    return (T)Marshal.PtrToStructure(Marshal.UnsafeAddrOfPinnedArrayElement(data, idx), typeof(T));

                idx += len;
            }

            return default(T);
        }

        /// <summary>
        /// Reads and returns the device descriptor from the device.
        /// </summary>
        /// <returns>The device descriptor received by the device.</returns>
        /// <exception cref="DZX.Devices.USB.USBException">The call to WinUsb_GetDescriptor() failed.</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        public USBDeviceDescriptor ReadDeviceDescriptor()
        {
            IntPtr buffer = Marshal.AllocHGlobal(1024);

            try
            {
                uint size = (uint)Marshal.SizeOf(typeof(USBDeviceDescriptor));
                uint transferred = 0;

                if (!WinUSB.WinUsb_GetDescriptor(_handle, 
                                                 (byte)DescriptorType.Device, 
                                                 0, 
                                                 0x0409, 
                                                 buffer, 
                                                 size, 
                                                 ref transferred))
                {
                    throw new USBException(string.Format("WinUsb_GetDescriptor() Failed. '{0}'", GetLastError()));
                }

                USBDeviceDescriptor des;
                
                des = (USBDeviceDescriptor)Marshal.PtrToStructure(buffer, typeof(USBDeviceDescriptor));

                return des;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private USBInterfaceDescriptor ReadInterfaceDescriptor(IntPtr handle, byte alternateSetting)
        {
            USBInterfaceDescriptor descriptor = new USBInterfaceDescriptor();

            if (!WinUSB.WinUsb_QueryInterfaceSettings(handle, alternateSetting, ref descriptor))
                throw new USBException(string.Format("WinUsb_QueryInterfaceSettings() Failed. '{0}'", GetLastError()));

            return descriptor;
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private byte[] ReadDescriptor(IntPtr handle, byte type, byte index)
        {
            IntPtr buffer = Marshal.AllocHGlobal(1024);

            try
            {
                uint transferred = 0;

                if (!WinUSB.WinUsb_GetDescriptor(handle, type, index, 0x0409, buffer, 1024, ref transferred))
                {
                    throw new USBException(string.Format("WinUsb_GetDescriptor() Failed. '{0}'", GetLastError()));
                }

                byte[] des = new byte[transferred];
                Marshal.Copy(buffer, des, 0, (int)transferred);
                return des;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private string ReadStringDescriptor(byte index)
        {
            if (index == 0)
            {
                return "";
            }

            IntPtr buffer = Marshal.AllocHGlobal(256);

            try
            {
                uint transferred = 0;

                if (!WinUSB.WinUsb_GetDescriptor(_handle, 3, index, 0x0409, buffer, 256, ref transferred))
                {
                    throw new USBException(string.Format("WinUsb_GetDescriptor() Failed. '{0}'", GetLastError()));
                }

                USBDescriptor des = (USBDescriptor)Marshal.PtrToStructure(buffer, typeof(USBDescriptor));

                string name = Marshal.PtrToStringAuto(IntPtr.Add(buffer, 2));
                if (!string.IsNullOrEmpty(name))
                {
                    int namelength = (int)((transferred - 2) / 2);
                    if (name.Length > namelength)
                    {
                        name = name.Remove(namelength, name.Length - namelength);
                    }
                }

                return name;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private byte[] ControlTransfer(IntPtr handle, byte requestType, byte request, ushort value, ushort index)
        {
            WinUSB.UsbSetupPacket pkt = new WinUSB.UsbSetupPacket();

            pkt.RequestType = requestType;
            pkt.Request = request;
            pkt.Value = value;
            pkt.Index = index;

            IntPtr buffer = Marshal.AllocHGlobal(4096);

            try
            {
                uint transferred = 0;

                if (!WinUSB.WinUsb_ControlTransfer(handle, pkt, IntPtr.Zero, 0, ref transferred, IntPtr.Zero))
                    throw new USBException(string.Format("WinUsb_ControlTransfer() Failed. '{0}'", GetLastError()));


                byte[] data = new byte[transferred];
                Marshal.Copy(buffer, data, 0, (int)transferred);
                return data;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private byte[] ControlTransfer(IntPtr handle, byte requestType, byte request, ushort value, ushort index, ushort length)
        {
            WinUSB.UsbSetupPacket pkt = new WinUSB.UsbSetupPacket();

            pkt.RequestType = requestType;
            pkt.Request = request;
            pkt.Value = value;
            pkt.Index = index;
            pkt.Length = length;

            IntPtr buffer = Marshal.AllocHGlobal(8192);

            try
            {
                uint transferred = 0;

                if (!WinUSB.WinUsb_ControlTransfer(handle, pkt, buffer, length, ref transferred, IntPtr.Zero))
                    throw new USBException(string.Format("WinUsb_ControlTransfer() Failed. '{0}'", GetLastError()));


                byte[] data = new byte[transferred];
                Marshal.Copy(buffer, data, 0, (int)transferred);
                return data;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        [MethodImpl(MethodImplOptions.NoOptimization)]
        private void ControlTransfer(IntPtr handle, byte requestType, byte request, ushort value, ushort index, byte[] data)
        {
            WinUSB.UsbSetupPacket pkt = new WinUSB.UsbSetupPacket();

            pkt.RequestType = requestType;
            pkt.Request = request;
            pkt.Value = value;
            pkt.Index = index;

            IntPtr buffer = Marshal.AllocHGlobal(data.Length);

            try
            {
                Marshal.Copy(data, 0, buffer, data.Length);

                uint transferred = 0;

                if (!WinUSB.WinUsb_ControlTransfer(handle, pkt, buffer, (uint)data.Length, ref transferred, IntPtr.Zero))
                    throw new USBException(string.Format("WinUsb_ControlTransfer() Failed. '{0}'", GetLastError()));
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        /// <summary>
        /// Sets the transfer timeout for the specified pipe.
        /// </summary>
        /// <param name="pipe">The identifier for the target pipe.</param>
        /// <param name="timeout">The new transfer timeout value for the pipe.</param>
        /// <exception cref="DZX.Devices.USB.USBException">WinUsb_SetPipePolicy() Failed</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        private void SetPipeTimeout(byte pipe, uint timeout)
        {
            if (!WinUSB.WinUsb_SetPipePolicy(_handle, pipe, (uint)WinUSB.POLICY_TYPE.PIPE_TRANSFER_TIMEOUT, 4, ref timeout))
                throw new USBException(string.Format("WinUsb_SetPipePolicy() Failed. '{0}'", GetLastError()));
        }

        /// <summary>
        /// Sets the short packet terminate option for the specified pipe.
        /// </summary>
        /// <param name="pipe">The identifier for the target pipe.</param>
        /// <param name="enabled">'1' to enable short packet termination; otherwise '0'.</param>
        /// <exception cref="DZX.Devices.USB.USBException">WinUsb_SetPipePolicy() Failed</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        private void SetPipeShortPacketTerminate(byte pipe, byte enabled)
        {
            if (!WinUSB.WinUsb_SetPipePolicy(_handle, pipe, (uint)WinUSB.POLICY_TYPE.SHORT_PACKET_TERMINATE, 1, ref enabled))
                throw new USBException(string.Format("WinUsb_SetPipePolicy() Failed. '{0}'", GetLastError()));
        }

        /// <summary>
        /// Sets the auto clear stall option for the specified pipe.
        /// </summary>
        /// <param name="pipe">The identifier for the target pipe.</param>
        /// <param name="enabled">'1' to enable the auto clear stall feature; otherwise '0'.</param>
        /// <exception cref="DZX.Devices.USB.USBException">WinUsb_SetPipePolicy() Failed</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        private void SetPipeAutoClearStall(byte pipe, byte enabled)
        {
            if (!WinUSB.WinUsb_SetPipePolicy(_handle, pipe, (uint)WinUSB.POLICY_TYPE.AUTO_CLEAR_STALL, 1, ref enabled))
                throw new USBException(string.Format("WinUsb_SetPipePolicy() Failed. '{0}'", GetLastError()));
        }


        /// <summary>
        /// Writes data to the default OUT pipe.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        /// <exception cref="DZX.Devices.USB.USBException">The write transfer failed.</exception>
        public void Write(byte[] data)
        {
            Write(data, WriteTimeout);
        }

        /// <summary>
        /// Writes data to the default OUT pipe.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the data to be written. Use '0' to wait indefinitely.</param>
        /// <exception cref="DZX.Devices.USB.USBException">There are no open OUT pipes.</exception>
        /// <exception cref="DZX.Devices.USB.USBException">The write transfer failed.</exception>
        public void Write(byte[] data, int timeout)
        {
            if (TxPipes.Length == 0)
                throw new USBException("There are no open OUT pipes");

            Write(TxPipes[0].ID, data, timeout);
        }

        /// <summary>
        /// Writes data to the specified pipe.
        /// </summary>
        /// <param name="pipe">The pipe to transmit the data.</param>
        /// <param name="data">The data to be written.</param>
        /// <exception cref="DZX.Devices.USB.USBException">The write transfer failed.</exception>
        public void Write(byte pipe, byte[] data)
        {
            Write(pipe, data, WriteTimeout);
        }

        /// <summary>
        /// Writes data to the specified pipe.
        /// </summary>
        /// <param name="pipe">The pipe to transmit the data.</param>
        /// <param name="data">The data to be written.</param>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the data to be written. Use '0' to wait indefinitely.</param>
        /// <exception cref="DZX.Devices.USB.USBException">The write transfer failed.</exception>
        [MethodImpl(MethodImplOptions.NoOptimization)]
        public void Write(byte pipe, byte[] data, int timeout)
        {
            SetPipeTimeout(pipe, (uint)timeout);

            IntPtr buffer = Marshal.AllocHGlobal(4096);

            try
            {
                Marshal.Copy(data, 0, buffer, data.Length);

                uint transferred = 0;
                if (!WinUSB.WinUsb_WritePipe(_handle, pipe, buffer, (uint)data.Length, ref transferred, IntPtr.Zero))
                {
                    throw new USBException(string.Format("WinUsb_WritePipe() Failed. '{0}'", GetLastError()));
                }
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        /// <summary>
        /// Reads and returns data from the default IN pipe.
        /// </summary>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the data to be received.</param>
        /// <returns>The data that has been received upon success; otherwise null on any error.</returns>
        public byte[] Read(int timeout)
        {
            lock (_readers)
            {
                if (RxPipes.Length == 0)
                    throw new USBException("There are no open IN pipes");

                PipeReader reader;

                if (_readers.TryGetValue(RxPipes[0].ID, out reader))
                {
                    USBMessage message = reader.Read(timeout);
                    if (message != null)
                    {
                        return message.Data;
                    }
                }

                return null;
            }
        }

        /// <summary>
        /// Reads and returns data from the specified pipe.
        /// </summary>
        /// <param name="pipe">The pipe to receive the data.</param>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the data to be received.</param>
        /// <returns>The data that has been received upon success; otherwise null on any error.</returns>
        public byte[] Read(byte pipe, int timeout)
        {
            lock (_readers)
            {
                PipeReader reader;

                if (_readers.TryGetValue(pipe, out reader))
                {
                    USBMessage message = reader.Read(timeout);
                    if (message != null)
                    {
                        return message.Data;
                    }
                }

                return null;
            }
        }

        /// <summary>
        /// Starts a reader for each of the receiving pipes.
        /// </summary>
        private void StartReaders()
        {
            lock (_readers)
            {
                StopReaders();

                PipeInfo[] pipes = RxPipes;
                foreach (PipeInfo pipe in pipes)
                {
                    PipeReader reader = new PipeReader(_handle, pipe.ID);
                    _readers.Add(pipe.ID, reader);
                }
            }
        }

        /// <summary>
        /// Stops any pipe _readers that happen to be running.
        /// </summary>
        private void StopReaders()
        {
            lock (_readers)
            {
                foreach (PipeReader reader in _readers.Values)
                {
                    reader.Dispose();
                }

                _readers.Clear();
            }
        }

        /// <summary>
        /// Reads all of the messages that are currently available within the receive queues.
        /// </summary>
        /// <returns>An array of messages that have been received.</returns>
        public USBMessage[] ReadAvailable()
        {
            List<USBMessage> msgs = new List<USBMessage>();

            lock (_readers)
            {
                foreach (KeyValuePair<byte, PipeReader> pair in _readers)
                {
                    msgs.AddRange(pair.Value.ReadAvailable());
                }
            }

            return msgs.ToArray();
        }

        /// <summary>
        /// Reads all of the messages that are currently available within the receive queue for the 
        /// specified pipe.
        /// </summary>
        /// <param name="pipe">The target pipe.</param>
        /// <returns>An array of messages that have been received.</returns>
        public USBMessage[] ReadAvailable(byte pipe)
        {
            lock (_readers)
            {
                PipeReader reader;

                if (_readers.TryGetValue(pipe, out reader))
                {
                    return reader.ReadAvailable();
                }

                return null;
            }
        }

        /// <summary>
        /// Represents a thread that continuously reads and queues data received from a WinUSB pipe.
        /// </summary>
        private class PipeReader : IDisposable
        {
            private bool disposed = false;
            private bool terminate = false;
            private Thread thread;
            private Queue<USBMessage> queue = new Queue<USBMessage>();
            private IntPtr terminateEvent = IntPtr.Zero;
            private ManualResetEvent manualEvent = new ManualResetEvent(false);
            private IntPtr nonManagedBuffer;
            private IntPtr nonManagedOverlapped;
            private NativeOverlapped overlap;

            /// <summary>
            /// Gets the ID for the pipe that is being read.
            /// </summary>
            public byte Pipe { get; private set; }

            /// <summary>
            /// Gets the handle used for communications for the reader.
            /// </summary>
            public IntPtr Handle { get; private set; }

            /// <summary>
            /// Releases unmanaged and - optionally - managed resources.
            /// </summary>
            /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
            protected virtual void Dispose(bool disposing)
            {
                if (!disposed)
                {
                    if (manualEvent != null)
                    {
                        manualEvent.Dispose();
                        manualEvent = null;
                    }

                    if (thread != null)
                    {
                        if (terminateEvent != IntPtr.Zero)
                        {
                            Kernel32.SetEvent(terminateEvent);
                        }

                        try
                        {
                            if (!thread.Join(200))
                            {
                                thread.Abort();
                            }
                        }
                        catch (Exception) {  }

                        thread = null;

                        Marshal.FreeHGlobal(nonManagedBuffer);
                        Marshal.FreeHGlobal(nonManagedOverlapped);
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
            /// Initializes a new instance of the <see cref="PipeReader"/> class.
            /// </summary>
            /// <param name="handle">The handle used to read the pipe.</param>
            /// <param name="pipe">The pipe to be read.</param>
            public PipeReader(IntPtr handle, byte pipe)
            {
                Handle = handle;
                Pipe = pipe;

                terminateEvent = Kernel32.CreateEvent(IntPtr.Zero, true, false, null);

                overlap = new NativeOverlapped();
                overlap.EventHandle = Kernel32.CreateEvent(IntPtr.Zero, true, false, null);
                overlap.OffsetHigh = 0;
                overlap.OffsetLow = 0;

                nonManagedBuffer = Marshal.AllocHGlobal(8192);
                nonManagedOverlapped = Marshal.AllocHGlobal(Marshal.SizeOf(overlap));

                // Create a thread to continuously read from the pipe
                thread = new Thread(ReadThreadProc);
                thread.Start(pipe);
            }

            /// <summary>
            /// Finalizes an instance of the <see cref="PipeReader"/> class.
            /// </summary>
            ~PipeReader()
            {
                Dispose(false);
            }

            /// <summary>
            /// The read thread process function.
            /// </summary>
            /// <param name="arg">An argument that provides the ID for the pipe to be read by the thread.</param>
            [MethodImpl(MethodImplOptions.NoOptimization)]
            private void ReadThreadProc(object arg)
            {
                byte pipeID = (byte)arg;

                try
                {
                    uint bytesRead = 0;
                    IntPtr[] handles = new IntPtr[2] { overlap.EventHandle, terminateEvent };

                    while (!terminate)
                    {
                        Marshal.StructureToPtr(overlap, nonManagedOverlapped, false);

                        bool success = WinUSB.WinUsb_ReadPipe(Handle, pipeID, nonManagedBuffer, 8192, ref bytesRead, nonManagedOverlapped);

                        if (!success)
                        {
                            // Get the reason for the failure to read
                            Int32 lastError = Kernel32.GetLastError();

                            // Check if there is just no data to be read yet?
                            if (lastError == Kernel32.ERROR_IO_PENDING)
                            {
                                // Wait for either overlapped event (data to arrive) or terminate event...
                                Int32 result = Kernel32.WaitForMultipleObjects(2, handles, false, Kernel32.INFINITE);

                                switch (result)
                                {
                                    case Kernel32.WAIT_OBJECT_0: // Overlapped I/O completed
                                        success = WinUSB.WinUsb_GetOverlappedResult(Handle, nonManagedOverlapped, ref bytesRead, false);
                                        break;

                                    case Kernel32.WAIT_OBJECT_1: // Thread was signaled to terminate
                                        terminate = true;
                                        break;

                                    case Kernel32.WAIT_TIMEOUT:
                                    default:
                                        WinUSB.WinUsb_AbortPipe(Handle, pipeID);
                                        break;
                                }
                            }
                            else if (lastError == Kernel32.DEVICE_NOT_CONNECTED)
                            {
                                // The device is no longer connected so terminate thread
                                terminate = true;
                            }
                            else
                            {
                                // Unexpected error code...
                                System.Diagnostics.Trace.WriteLine(string.Format("Unexpected error code '0x{0:X8}' reading WinUSB Pipe", lastError));
                                terminate = true;
                            }
                        }

                        // Check if data has been read?
                        if (success)
                        {
                            byte[] data = new byte[bytesRead];
                            Marshal.Copy(nonManagedBuffer, data, 0, data.Length);

                            USBMessage msg = new USBMessage(data);
                            msg.Pipe = pipeID;

                            lock (queue)
                            {
                                // Queue the received message
                                queue.Enqueue(msg);

                                // Signal that there is a message within the queue
                                manualEvent.Set();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Trace.WriteLine(string.Format("Unexpected exception '{0}' reading WinUSB Pipe", ex.Message));
                }
                finally
                {
                    
                }
            }

            /// <summary>
            /// Reads and returns a received message.
            /// </summary>
            /// <returns>The message that has been received, if any; otherwise null.</returns>
            public USBMessage Read()
            {
                lock (queue)
                {
                    if (queue.Count > 0)
                    {
                        USBMessage message = queue.Dequeue();

                        if (queue.Count == 0)
                            manualEvent.Reset();

                        return message;
                    }
                }

                return null;
            }

            /// <summary>
            /// Reads and returns a received message.
            /// </summary>
            /// <param name="timeout">The maximum amount of time, in milliseconds, to block and wait for a message to be received.</param>
            /// <returns>The message that has been received, if any; otherwise null.</returns>
            public USBMessage Read(int timeout)
            {
                manualEvent.WaitOne(timeout);

                lock (queue)
                {
                    if (queue.Count > 0)
                    {
                        USBMessage message = queue.Dequeue();

                        if (queue.Count == 0)
                            manualEvent.Reset();

                        return message;
                    }
                }

                return null;
            }

            /// <summary>
            /// Returns the messages that are currently available within the underlying receive queue.
            /// </summary>
            /// <returns>An array of the messages that have been received.</returns>
            public USBMessage[] ReadAvailable()
            {
                lock (queue)
                {
                    USBMessage[] msgs = queue.ToArray();
                    queue.Clear();
                    manualEvent.Reset();

                    return msgs;
                }
            }
        }
    }

    /// <summary>
    /// Represents an encapsulated message transferred between a USB device.
    /// </summary>
    public class USBMessage
    {
        /// <summary>
        /// Gets or sets the timestamp for the message.
        /// </summary>
        public long Timestamp { get; set; }

        /// <summary>
        /// Gets or sets the pipe identifier for the message.
        /// </summary>
        public byte Pipe { get; set; }

        /// <summary>
        /// Gets or sets the data payload for the message.
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// Gets or sets the <see cref="System.Byte"/> of the data payload at the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="System.Byte"/> of data at the specified index.</returns>
        public byte this[int index]
        {
            get { return Data[index]; }
            set { Data[index] = value; }
        }

        /// <summary>
        /// Gets the size (in bytes) of the payload of the message.
        /// </summary>
        public int Size
        {
            get
            {
                if (Data != null)
                    return Data.Length;

                return 0;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="USBMessage"/> class.
        /// </summary>
        public USBMessage()
        {
            //Timestamp = DateTime.Now;
            Timestamp = DZX.Devices.Diagnostics.Timestamp;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="USBMessage"/> class with the specified data payload.
        /// </summary>
        /// <param name="data">The initial data payload for the message.</param>
        public USBMessage(byte[] data)
            : this()
        {
            Data = data;
        }
    }

    /// <summary>
    /// Represents errors that occur during I/O operations with a USB device.
    /// </summary>
    [Serializable]
    public class USBException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="USBException"/> class.
        /// </summary>
        public USBException() :
            base() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="USBException"/> class.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public USBException(string message) :
            base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="USBException"/> class.
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception.</param>
        /// <param name="innerException">The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public USBException(string message, Exception innerException) :
            base(message, innerException) { }
    }

    /// <summary>
    /// Represents a type of descriptor.
    /// </summary>
    public enum DescriptorType : byte
    {
        None = 0,
        Device = 1,
        Configuration = 2,
        String = 3,
        Interface = 4,
        Endpoint = 5,
        DeviceQualifier = 6,
        OtherSpeed = 7,
        DFUFunctional = 0x21,
    }
}
