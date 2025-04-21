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
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Microsoft.Win32.SafeHandles;

namespace DZX.Devices.Watchers
{
    /// <summary>
    /// Provides the ability to receive events when a device is attached or detached from the system.
    /// </summary>
    public class DeviceWatcher : IDisposable
    {
        /// <summary>
        /// Underlying list of interfaces being watched
        /// </summary>
        private Dictionary<Guid, InterfaceWatcher> _watchers = new Dictionary<Guid, InterfaceWatcher>();

        /// <summary>
        /// Indication of being _disposed.
        /// </summary>
        private bool _disposed = false;

        /// <summary>
        /// Gets the interface guids that are being watched.
        /// </summary>
        public Guid[] InterfaceGuids { get { return _watchers.Keys.ToArray(); } }

        /// <summary>
        /// Occurs when a device has been attached and added to the system.
        /// </summary>
        public event DeviceAttachedEventHandler DeviceAttached;

        /// <summary>
        /// Occurs when a device has been detached and removed from the system.
        /// </summary>
        public event DeviceDetachedEventHandler DeviceDetached;

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceWatcher"/> class.
        /// </summary>
        public DeviceWatcher()
        {

        }

        /// <summary>
        /// Finalizes an instance of the <see cref="DeviceWatcher"/> class.
        /// </summary>
        ~DeviceWatcher()
        {
            Dispose(false);
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
        /// Releases unmanaged and - optionally - managed resources.
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    foreach (InterfaceWatcher watcher in _watchers.Values)
                    {
                        watcher.Dispose();
                    }

                    _watchers.Clear();
                }

                _disposed = true;
            }
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceAttached" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DeviceAttachedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceAttached(DeviceAttachedEventArgs e)
        {
            DeviceAttachedEventHandler handler = DeviceAttached;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceDetached" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceDetached(DeviceDetachedEventArgs e)
        {
            DeviceDetachedEventHandler handler = DeviceDetached;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Handles the DeviceAttached event of the _watcher control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="DeviceAttachedEventArgs"/> instance containing the event data.</param>
        private void watcher_DeviceAttached(object sender, DeviceAttachedEventArgs e)
        {
            OnDeviceAttached(e);
        }

        /// <summary>
        /// Handles the DeviceDetached event of the _watcher control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
        private void watcher_DeviceDetached(object sender, DeviceDetachedEventArgs e)
        {
            OnDeviceDetached(e);
        }

        /// <summary>
        /// Adds the specified interface to be watched and raise events when a device is either attached or
        /// detached from the system.
        /// </summary>
        /// <param name="interfaceGuid">The guid for the interface to be watched.</param>
        public void AddInterface(Guid interfaceGuid)
        {
            RemoveInterface(interfaceGuid);

            // Create a single interface _watcher
            InterfaceWatcher watcher = new InterfaceWatcher(interfaceGuid);

            // Hook events
            watcher.DeviceAttached += watcher_DeviceAttached;
            watcher.DeviceDetached += watcher_DeviceDetached;

            // Keep underlying list
            _watchers.Add(interfaceGuid, watcher);
        }

        /// <summary>
        /// Removes the specified interface from being watched.
        /// </summary>
        /// <param name="interfaceGuid">The guid for the interface to be removed.</param>
        public void RemoveInterface(Guid interfaceGuid)
        {
            InterfaceWatcher watcher;

            // Try to find in underlying list
            if (_watchers.TryGetValue(interfaceGuid, out watcher))
            {
                // Found it; remove it.
                watcher.Dispose();
                _watchers.Remove(interfaceGuid);
            }
        }
    }

    /// <summary>
    /// Represents a control that registers with the user32.dll to receive events when
    /// devices have been connected or removed.
    /// </summary>
    [DisplayName("Interface Watcher")]
    [Description("Provides handlers for attached/detached events for device interfaces.")]
    public class InterfaceWatcher : System.Windows.Forms.Control
    {
        private IntPtr handle; 
        IntPtr mem = IntPtr.Zero;
        SetupAPI.DEV_BROADCAST_DEVICEINTERFACE bi = new SetupAPI.DEV_BROADCAST_DEVICEINTERFACE();

        /// <summary>
        /// Occurs when a device has been attached.
        /// </summary>
        public event DeviceAttachedEventHandler DeviceAttached;

        /// <summary>
        /// Occurs when a device has been detached.
        /// </summary>
        public event DeviceDetachedEventHandler DeviceDetached;

        /// <summary>
        /// Initializes a new instance of the <see cref="InterfaceWatcher" /> class.
        /// </summary>
        public InterfaceWatcher(Guid interfaceGuid)
        {
            mem = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SetupAPI.DEV_BROADCAST_DEVICEINTERFACE)));

            bi.dbcc_devicetype = SetupAPI.DBT_DEVTYP_DEVICEINTERFACE;
            bi.dbcc_classguid = interfaceGuid;
            bi.dbcc_size = Marshal.SizeOf(typeof(SetupAPI.DEV_BROADCAST_DEVICEINTERFACE));
            Marshal.StructureToPtr(bi, mem, false);

            handle = User32.RegisterDeviceNotification(Handle, mem, SetupAPI.DEVICE_NOTIFY_WINDOW_HANDLE);
        }

        /// <summary>
        /// Releases the unmanaged resources used by the <see cref="T:System.Windows.Forms.Control" /> and its child controls and optionally releases the managed resources.
        /// </summary>
        /// <param name="disposing">true to release both managed and unmanaged resources; false to release only unmanaged resources.</param>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);

            if (disposing)
            {
                if (handle != IntPtr.Zero)
                {
                    User32.UnregisterDeviceNotification(handle);
                    handle = IntPtr.Zero;
                }

                if (mem != IntPtr.Zero)
                {
                    Marshal.FreeHGlobal(mem);
                    mem = IntPtr.Zero;
                }
            }
        }

        /// <summary>
        /// Gets the device broadcast header structure for the specified parameter.
        /// </summary>
        /// <param name="lparam">The parameter as received from a windows message about a device connection change.</param>
        /// <returns>The device broadcast header for the given parameter.</returns>
        private static SetupAPI.DEV_BROADCAST_HDR GetDevBroadcastHdr(IntPtr lparam)
        {
            return (SetupAPI.DEV_BROADCAST_HDR)Marshal.PtrToStructure(lparam, typeof(SetupAPI.DEV_BROADCAST_HDR));
        }

        /// <summary>
        /// Gets the device broadcast device interface structure for the specified parameter.
        /// </summary>
        /// <param name="lparam">The parameter as received from a windows message about a device connection change.</param>
        /// <returns>The device broadcast device interface structure for the given parameter.</returns>
        private static SetupAPI.DEV_BROADCAST_DEVICEINTERFACE GetDevBroadcastDevIntf(IntPtr lparam)
        {
            return (SetupAPI.DEV_BROADCAST_DEVICEINTERFACE)Marshal.PtrToStructure(lparam, typeof(SetupAPI.DEV_BROADCAST_DEVICEINTERFACE));
        }

        /// <summary>
        /// Gets the interface guid for the specified message parameter.
        /// </summary>
        /// <param name="lparam">The message parameter.</param>
        /// <returns>The interface guid represented by the given parameter.</returns>
        public Guid GetInterfaceGuid(IntPtr lparam)
        {
            // Retrieve the global standard information about the event
            SetupAPI.DEV_BROADCAST_HDR hdr = GetDevBroadcastHdr(lparam);

            // Only concerned with device interface changes
            if (hdr.dbch_devicetype == SetupAPI.DBT_DEVTYP_DEVICEINTERFACE)
            {
                SetupAPI.DEV_BROADCAST_DEVICEINTERFACE intf = GetDevBroadcastDevIntf(lparam);
                return intf.dbcc_classguid;
            }

            return default(Guid);
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceAttached" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DeviceAttachedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceAttached(DeviceAttachedEventArgs e)
        {
            DeviceAttachedEventHandler handler = DeviceAttached;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:DeviceDetached" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
        protected virtual void OnDeviceDetached(DeviceDetachedEventArgs e)
        {
            DeviceDetachedEventHandler handler = DeviceDetached;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        internal static string GetDevicePath(IntPtr lparam, Guid classguid)
        {
            // Retreive the global standard information about the event
            SetupAPI.DEV_BROADCAST_HDR hdr = GetDevBroadcastHdr(lparam);

            // Only concerned with device interface changes
            if (hdr.dbch_devicetype == SetupAPI.DBT_DEVTYP_DEVICEINTERFACE)
            {
                SetupAPI.DEV_BROADCAST_DEVICEINTERFACE intf = GetDevBroadcastDevIntf(lparam);

                // Only concerned with the specified guid interface devices
                if (intf.dbcc_classguid == classguid)
                {
                    if (!string.IsNullOrEmpty(intf.dbcc_name))
                    {
                        return intf.dbcc_name.ToLower();
                    }
                }
            }

            return "";
        }

        /// <summary>
        /// Processes the received messages for this form.
        /// </summary>
        /// <param name="m">The Windows <see cref="T:System.Windows.Forms.Message" /> to process.</param>
        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            if (m.Msg == SetupAPI.WM_DEVICECHANGE)
            {

                switch ((int)m.WParam)
                {
                    case SetupAPI.DBT_DEVICEARRIVAL:
                        {
                            Guid guid = GetInterfaceGuid(m.LParam);
                            string path = GetDevicePath(m.LParam, guid);
                            BeginInvoke((ThreadStart)delegate { OnDeviceAttached(new DeviceAttachedEventArgs(path, guid)); });
                        }
                        break;
                    case SetupAPI.DBT_DEVICEREMOVECOMPLETE:
                        {
                            Guid guid = GetInterfaceGuid(m.LParam);
                            string path = GetDevicePath(m.LParam, guid);
                            BeginInvoke((ThreadStart)delegate { OnDeviceDetached(new DeviceDetachedEventArgs(path, guid)); });
                        }
                        break;
                }
            }

            base.WndProc(ref m);
        }
    }

    /// <summary>
    /// Represents a handler that will receive an event when a device has been attached to the system.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="DeviceAttachedEventArgs"/> instance containing the event data.</param>
    public delegate void DeviceAttachedEventHandler(object sender, DeviceAttachedEventArgs e);

    /// <summary>
    /// Contains data for an event that is raised when a device has been attached the system.
    /// </summary>
    public class DeviceAttachedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the connection path for the device that has been attached.
        /// </summary>
        public string Path { get; private set; }

        /// <summary>
        /// Gets the interface guid for the device that has been attached.
        /// </summary>
        public Guid InterfaceGuid { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceAttachedEventArgs"/> class.
        /// </summary>
        /// <param name="path">The connection path for the event.</param>
        /// <param name="interfaceGuid">The interface guid for the event.</param>
        public DeviceAttachedEventArgs(string path, Guid interfaceGuid)
        {
            Path = path;
            InterfaceGuid = interfaceGuid;
        }
    }

    /// <summary>
    /// Represents a handler that will receive an event when a device has been detached from the system.
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="e">The <see cref="DeviceDetachedEventArgs"/> instance containing the event data.</param>
    public delegate void DeviceDetachedEventHandler(object sender, DeviceDetachedEventArgs e);

    /// <summary>
    /// Contains data for an event that is raised when a device has been detached from the system.
    /// </summary>
    public class DeviceDetachedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the connection path for the device that has been detached.
        /// </summary>
        public string Path { get; private set; }

        /// <summary>
        /// Gets the interface guid for the device that has been detached.
        /// </summary>
        public Guid InterfaceGuid { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceDetachedEventArgs"/> class.
        /// </summary>
        /// <param name="path">The connection path for the event.</param>
        /// <param name="interfaceGuid">The interface guid for the event.</param>
        public DeviceDetachedEventArgs(string path, Guid interfaceGuid)
        {
            Path = path;
            InterfaceGuid = interfaceGuid;
        }
    }
}
