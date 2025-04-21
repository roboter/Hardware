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
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

namespace DZX
{
    internal static class Kernel32
    {
        public const Int32 FILE_FLAG_OVERLAPPED = 0X40000000;
        public const Int32 FILE_SHARE_READ = 1;
        public const Int32 FILE_SHARE_WRITE = 2;

        public const UInt32 GENERIC_READ = 0X80000000;
        public const Int32 GENERIC_WRITE = 0X40000000;
        public const Int32 INVALID_HANDLE_VALUE = -1;
        public const Int32 OPEN_EXISTING = 3;
        public const Int32 WAIT_TIMEOUT = 0X102;
        public const Int32 WAIT_OBJECT_0 = 0;
        public const Int32 WAIT_OBJECT_1 = 1;
        public const Int32 ERROR_IO_PENDING = 0x000003E5;
        public const Int32 DEVICE_NOT_CONNECTED = 0x0000048F;
        public const Int32 INFINITE = -1;

        [StructLayout(LayoutKind.Sequential)]
        public class SECURITY_ATTRIBUTES
        {
            public Int32 nLength;
            public Int32 lpSecurityDescriptor;
            public Int32 bInheritHandle;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct COMMTIMEOUTS
        {
            public int ReadIntervalTimeout;
            public int ReadTotalTimeoutMultiplier;
            public int ReadTotalTimeoutConstant;
            public int WriteTotalTimeoutMultiplier;
            public int WriteTotalTimeoutConstant;
        }

        /// <summary>
        /// Wrapper for the Win32 API 'CancelIO' in kernel32.dll.
        /// Cancels all pending I/O operations that are issued by the calling thread for the 
        /// specified file.
        /// </summary>
        /// <param name="hFile">A handle to the file</param>
        /// <returns>True upon success</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool CancelIo(SafeFileHandle hFile);

        /// <summary>
        /// Wrapper for the Win32 API 'GetLastError' in kernel32.dll
        /// Retreives the calling thread's last error code value.
        /// </summary>
        /// <returns>The error code</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern Int32 GetLastError();

        /// <summary>
        /// Wrapper for the Win32 API 'CreateEvent' in kernel32.dll.
        /// Creates or opens a named or unnamed event object.
        /// </summary>
        /// <param name="SecurityAttributes">A pointer to a SECURITY_ATTRIBUTES structure</param>
        /// <param name="bManualReset">True creates a manual reset event. False creates an auto reset event</param>
        /// <param name="bInitialState">True the initial state is signaled. False the initial state is nonsignaled</param>
        /// <param name="lpName">The name of the event object</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern IntPtr CreateEvent(IntPtr SecurityAttributes, Boolean bManualReset, Boolean bInitialState, String lpName);

        /// <summary>
        /// Wrapper for the Win32 API 'ResetEvent' in kernel32.dll.
        /// Sets the specified event object to the nonsignaled state.
        /// </summary>
        /// <param name="eventHandle">A handle to the event object</param>
        /// <returns>True upon success, otherwise false.</returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool ResetEvent(IntPtr eventHandle);

        /// <summary>
        /// Wrapper for the Win32 API 'SetEvent' in kernel32.dll.
        /// Sets the specified event object to the signaled state.
        /// </summary>
        /// <param name="eventHandle">The handle to the event object.</param>
        /// <returns>True upon success, otherwise false.</returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool SetEvent(IntPtr eventHandle);

        /// <summary>
        /// Wrapper for the Win32 API 'CreateFile' in kernel32.dll.
        /// Creates or opens a file or I/O device.
        /// </summary>
        /// <param name="lpFileName">The name of the file or device to be created or opened</param>
        /// <param name="dwDesiredAccess">The requested access to the file or device</param>
        /// <param name="dwShareMode">The requested sharing mode of the file or device</param>
        /// <param name="lpSecurityAttributes">A pointer to a SECURITY_ATTRIBUTES structure</param>
        /// <param name="dwCreationDisposition">An action to take on a file or device that exists or does not exist</param>
        /// <param name="dwFlagsAndAttributes">The file or device attributes and flags</param>
        /// <param name="hTemplateFile">A valid handle to a template file with the GENERIC_READ access right</param>
        /// <returns>An open handle upon success or an invalid handle upon an error</returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern SafeFileHandle CreateFile(String lpFileName, UInt32 dwDesiredAccess, Int32 dwShareMode,
                                                                IntPtr lpSecurityAttributes, Int32 dwCreationDisposition, Int32 dwFlagsAndAttributes, IntPtr hTemplateFile);

        /// <summary>
        /// Wrapper for the Win32 API 'GetOverlappedResult' in kernel32.dll.
        /// Retrieves the results of an overlapped operation on the specified file, named pipe,
        /// or communications device.
        /// </summary>
        /// <param name="hFile">_handle to the file, named pipe, or communications device</param>
        /// <param name="lpOverlapped">A pointer to the overlapped structure</param>
        /// <param name="lpNumberOfBytesTransferred">A pointer to a variable that receives the actual bytes transferred</param>
        /// <param name="bWait">If true, does not return until complete before returning</param>
        /// <returns>True upon a completed transfer</returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern Boolean GetOverlappedResult(SafeFileHandle hFile, IntPtr lpOverlapped, ref Int32 lpNumberOfBytesTransferred, Boolean bWait);

        /// <summary>
        /// Wrapper for the Win32 API 'ReadFile' in kernel32.dll.
        /// Reads data from the specified file or I/O device.
        /// </summary>
        /// <param name="hFile">_handle to the file or I/O device</param>
        /// <param name="lpBuffer">Data buffer that receives the data read from a file or device</param>
        /// <param name="nNumberOfBytesToRead">The maximum number of bytes to read</param>
        /// <param name="lpNumberOfBytesRead">The number of bytes actually read</param>
        /// <param name="lpOverlapped">A pointer to an overlapped structure when using overlapped I/O</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern Boolean ReadFile(SafeFileHandle hFile, IntPtr lpBuffer, Int32 nNumberOfBytesToRead, ref Int32 lpNumberOfBytesRead, ref System.Threading.NativeOverlapped lpOverlapped);

        /// <summary>
        /// Wrapper for the Win32 API 'WaitForSingleObject' in kernel32.dll.
        /// Waits until the specified object is in the signaled state or the timeout
        /// interval elapses.
        /// </summary>
        /// <param name="hHandle">A handle to the object to be signaled.</param>
        /// <param name="dwMilliseconds">The timeout interval in milliseconds.</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern Int32 WaitForSingleObject(IntPtr hHandle, Int32 dwMilliseconds);

        /// <summary>
        /// Wrapper for the Win32 API 'WaitForMultipleObjects' in kernel32.dll.
        /// Waits until one or all of the specified objects are in the signaled state or the timeout
        /// interval elapses.
        /// </summary>
        /// <param name="nCount">The number of object handles in the array pointed by lpHandles.</param>
        /// <param name="lpHandles">An array of object handles.</param>
        /// <param name="waitAll">When true, waits until all handles are signaled, otherwise waits until one is signaled.</param>
        /// <param name="dwMilliseconds">The timeout interval in milliseconds.</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern Int32 WaitForMultipleObjects(int nCount, IntPtr[] lpHandles, bool waitAll, Int32 dwMilliseconds);

        /// <summary>
        /// Wrapper for the Win32 API 'WriteFile' in kernel32.dll.
        /// Writes data to the specified file or I/O device.
        /// </summary>
        /// <param name="hFile">_handle to file or I/O device</param>
        /// <param name="lpBuffer">Data buffer to be written to the file or device</param>
        /// <param name="nNumberOfBytesToWrite">The number of bytes to be written to the file or device</param>
        /// <param name="lpNumberOfBytesWritten">The number of bytes actually written</param>
        /// <param name="lpOverlapped">A pointer to an overlapped structure when using overlapped I/O</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern Boolean WriteFile(SafeFileHandle hFile, IntPtr lpBuffer, Int32 nNumberOfBytesToWrite, ref Int32 lpNumberOfBytesWritten, ref System.Threading.NativeOverlapped lpOverlapped);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool GetCommTimeouts(SafeFileHandle hFile, ref COMMTIMEOUTS lpCommTimeouts);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool SetCommTimeouts(SafeFileHandle hFile, ref COMMTIMEOUTS lpCommTimeouts);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr GetProcessHeap();

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool HeapValidate();
    }

    /// <summary>
    /// Provides access to the Win32 API within the hid.dll
    /// </summary>
    internal static class HID
    {
        /// <summary>
        /// Wrapper for the Win32 API 'HIDD_ATTRIBUTES' structure in hid.dll
        /// </summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct HIDD_ATTRIBUTES
        {
            public Int32 Size;
            public Int16 VendorID;
            public Int16 ProductID;
            public Int16 VersionNumber;
        }

        /// <summary>
        /// Wrapper for the Win32 API 'HIDP_CAPS' structure in hid.dll
        /// </summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct HIDP_CAPS
        {
            public Int16 Usage;
            public Int16 UsagePage;
            public Int16 InputReportByteLength;
            public Int16 OutputReportByteLength;
            public Int16 FeatureReportByteLength;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 17)]
            public Int16[] Reserved;
            public Int16 NumberLinkCollectionNodes;
            public Int16 NumberInputButtonCaps;
            public Int16 NumberInputValueCaps;
            public Int16 NumberInputDataIndices;
            public Int16 NumberOutputButtonCaps;
            public Int16 NumberOutputValueCaps;
            public Int16 NumberOutputDataIndices;
            public Int16 NumberFeatureButtonCaps;
            public Int16 NumberFeatureValueCaps;
            public Int16 NumberFeatureDataIndices;
        }

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_FlushQueue' in hid.dll.
        /// Deletes all pending input reports in a top-level collection's input queue.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to the top-level collection
        /// whose input queue is flushed</param>
        /// <returns>True upon success</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_FlushQueue(SafeFileHandle HidDeviceObject);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetHidGuid' in hid.dll.
        /// Returns the device interface GUID for the HIDClass devices.
        /// </summary>
        /// <param name="HidGuid">Pointer to a caller allocated GUID buffer</param>
        [DllImport("hid.dll", SetLastError = true)]
        public static extern void HidD_GetHidGuid(ref System.Guid HidGuid);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetPhysicalDescriptor' in hid.dll
        /// Returns the embedded string of a top-level collection that identifies the
        /// collection's physical device.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection.</param>
        /// <param name="buffer">Pointer to a call-allocated buffer.</param>
        /// <param name="bufferLength">Specifies the length in bytes of the buffer.</param>
        /// <returns>True upon success, otherwise false.</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetPhysicalDescriptor(SafeFileHandle HidDeviceObject, byte[] buffer, int bufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetManufacturerString' in hid.dll.
        /// Returns a top-level collection's embedded string that identifies
        /// the manufacturer.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="buffer">Pointer to a user allocated buffer to return the string</param>
        /// <param name="bufferLength">Specifies the length, in bytes, of a caller allocated buffer</param>
        /// <returns>True if it returns the entire NULL-terminated embedded string</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetManufacturerString(SafeFileHandle HidDeviceObject, byte[] buffer, int bufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetSerialNumberString' in hid.dll
        /// Returns the embedded string of a top-level collection that identifies the
        /// serial number of the collection's physical device.
        /// </summary>
        /// <param name="HidDeviceObject"></param>
        /// <param name="buffer"></param>
        /// <param name="bufferLength"></param>
        /// <returns></returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetSerialNumberString(SafeFileHandle HidDeviceObject, byte[] buffer, int bufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetProductString' in hid.dll.
        /// Returns a top-level collection's embedded string that identifies
        /// the product.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="buffer">Pointer to a user allocated buffer to return the string</param>
        /// <param name="bufferLength">Specifies the length, in bytes, of a caller allocated buffer</param>
        /// <returns>True if it returns the entire NULL-terminated embedded string</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetProductString(SafeFileHandle HidDeviceObject, byte[] buffer, int bufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetAttributes' in hid.dll.
        /// Returns the attributes of a specified top-level collection
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="Attributes">Pointer to a caller allocated HIDD_ATTRIBUTES structure</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetAttributes(SafeFileHandle HidDeviceObject, ref HIDD_ATTRIBUTES Attributes);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetPreparsedData' in hid.dll.
        /// Returns a top-level collection's preparsed data.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="PreparsedData">A pointer to routine allocated HIDP_PREPARSED_DATA structure</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetPreparsedData(SafeFileHandle HidDeviceObject, ref IntPtr PreparsedData);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_FreePreparsedData' in hid.dll.
        /// Releases teh resources that the HID class driver allocated to hold a top-level
        /// collection's preparsed data.
        /// </summary>
        /// <param name="PreparsedData">Pointer to the buffer returned by HidD_GetPreparsedData</param>
        /// <returns>True if succeeds, False if the buffer was not a preparsed data buffer</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_FreePreparsedData(IntPtr PreparsedData);

        /// <summary>
        /// Wrapper for the Win32 API 'HidP_GetCaps' in hid.dll.
        /// Returns a top-level collection's HIDP_CAPS structure.
        /// </summary>
        /// <param name="PreparsedData">Pointer to a top-level collection's preparsed data</param>
        /// <param name="Capabilities">Pointer to a call allocated buffer that returns a collection's
        /// HIDP_CAPS structure</param>
        /// <returns>HIDP_STATUS_SUCCESS if succeeds, and HIDP_STATUS_INVALID_PREPARSED_DATA if the preparsed
        /// data is not valid</returns>
        [DllImport("hid.dll", SetLastError = true)]
        public static extern Int32 HidP_GetCaps(IntPtr PreparsedData, ref HIDP_CAPS Capabilities);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetNumInputBuffers' in hid.dll.
        /// Returns the current size, in number of reports, of the ring buffer that the HID class driver
        /// uses to queue input reports from a specified top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="NumberBuffers">Pointer to a caller allocated variable that the routine uses
        /// to return the maximum number of input reports the ring buffer can hold</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetNumInputBuffers(SafeFileHandle HidDeviceObject, ref int NumberBuffers);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_SetNumInputBuffers' in hid.dll.
        /// Sets the maximum number of input reports that the HID class driver ring buffer can hold
        /// for a specified top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="NumberBuffers">Specifies the maximum number of buffers the HID class driver
        /// should maintain for the input reports generated by the HidDeviceObject collection</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_SetNumInputBuffers(SafeFileHandle HidDeviceObject, int NumberBuffers);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetInputReport' in hid.dll.
        /// Returns an input report from a specified top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="reportBuffer">Pointer to a user allocated buffer to return the input report</param>
        /// <param name="reportBufferLength">Specifies the length, in bytes, of a caller allocated buffer</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetInputReport(SafeFileHandle HidDeviceObject, byte[] reportBuffer, int reportBufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_SetOutputReport' in hid.dll.
        /// The HidD_SetOutputReport routine sends an output report to a top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection.</param>
        /// <param name="reportBuffer">Pointer to a caller-allocated output report buffer that the caller uses to specify a report ID.</param>
        /// <param name="reportBufferLength">Specifies the size, in bytes, of the report buffer.</param>
        /// <returns>If HidD_SetOutputReport succeeds, it returns TRUE; otherwise, it returns FALSE.</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_SetOutputReport(SafeFileHandle HidDeviceObject, byte[] reportBuffer, int reportBufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_GetFeature' in hid.dll.
        /// Returns a feature report from a specified top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="reportBuffer">Pointer to a user allocated buffer to return the feature report</param>
        /// <param name="reportBufferLength">Specifies the length, in bytes, of a caller allocated buffer</param>
        /// <returns>True if succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_GetFeature(SafeFileHandle HidDeviceObject, byte[] reportBuffer, int reportBufferLength);

        /// <summary>
        /// Wrapper for the Win32 API 'HidD_SetFeature' in hid.dll
        /// Sends a feature report to a top-level collection.
        /// </summary>
        /// <param name="HidDeviceObject">Specifies an open handle to a top-level collection</param>
        /// <param name="reportBuffer">Pointer to a caller allocated feature report buffer to specify a HID report ID.</param>
        /// <param name="reportBufferLength">Specifies the size, in bytes, of the report buffer</param>
        /// <returns>True if it succeeds</returns>
        [DllImport("hid.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool HidD_SetFeature(SafeFileHandle HidDeviceObject, byte[] reportBuffer, int reportBufferLength);
    }

    /// <summary>
    /// Provides access to the Win32 API within the user32.dll
    /// </summary>
    internal static class User32
    {
        /// <summary>
        /// Registers the device or type of device for which a window will receive notifications.
        /// </summary>
        /// <param name="hRecipient">A handle to the window or service that will receive device events for the devices specified in the 
        /// NotificationFilter parameter.</param>
        /// <param name="NotificationFilter">A pointer to a block of data that specifies the type of device for which notifications should be sent. 
        /// This block always begins with the DEV_BROADCAST_HDR structure.</param>
        /// <param name="Flags">Indication whether the hRecipient is a window handle or a service handle.</param>
        /// <returns>If the function succeeds, the return value is a device notification handle; otherwise IntPtr.Zero</returns>
        [DllImport("user32.dll", SetLastError = true)]
        public static extern IntPtr RegisterDeviceNotification(IntPtr hRecipient, IntPtr NotificationFilter, int Flags);

        /// <summary>
        /// Closes the specified device notification handle.
        /// </summary>
        /// <param name="_handle">Device notification handle returned by the RegisterDeviceNotification function.</param>
        /// <returns>If the function succeeds, the return value is true.</returns>
        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool UnregisterDeviceNotification(IntPtr Handle);
    }

    /// <summary>
    /// Provides access to the Win32 API within the SetupAPI.dll
    /// </summary>
    internal static class SetupAPI
    {
        public const int DBT_DEVICEARRIVAL = 0X8000;
        public const int DBT_DEVICEREMOVEPENDING = 0x8003;         // about to remove, still available
        public const int DBT_DEVICEREMOVECOMPLETE = 0X8004;
        public const int DBT_DEVNODES_CHANGED = 0x0007;				// a device has been added to or removed from the system
        public const int DBT_DEVTYP_DEVICEINTERFACE = 5;
        public const int DBT_DEVTYP_HANDLE = 6;
        public const int DEVICE_NOTIFY_ALL_INTERFACE_CLASSES = 4;
        public const int DEVICE_NOTIFY_SERVICE_HANDLE = 1;
        public const int DEVICE_NOTIFY_WINDOW_HANDLE = 0;
        public const int WM_DEVICECHANGE = 0X219;

        public static readonly Guid GUID_DEVINTERFACE_HID = new Guid("4D1E55B2-F16F-11CF-88CB-001111000030");
        public static readonly Guid GUID_DEVINTERFACE_USB_DEVICE = new Guid("A5DCBF10-6530-11D2-901F-00C04FB951ED");

        // from setupapi.h

        public const Int32 DIGCF_PRESENT = 2;
        public const Int32 DIGCF_DEVICEINTERFACE = 0X10;

        // Two declarations for the DEV_BROADCAST_DEVICEINTERFACE structure.

        // Use this one in the call to RegisterDeviceNotification() and
        // in checking dbch_devicetype in a DEV_BROADCAST_HDR structure:

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct DEV_BROADCAST_DEVICEINTERFACE
        {
            public int dbcc_size;
            public int dbcc_devicetype;
            public int dbcc_reserved;
            public Guid dbcc_classguid;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 255)]
            public string dbcc_name;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct DEV_BROADCAST_HDR
        {
            public int dbch_size;
            public int dbch_devicetype;
            public int dbch_reserved;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct SP_DEVICE_INTERFACE_DATA
        {
            public Int32 cbSize;
            public Guid InterfaceClassGuid;
            public Int32 Flags;
            public IntPtr Reserved;
        }

        /// <summary>
        /// Wrapper for the Win32 'SetupDiGetClassDevs' within setupapi.dll. Returns a handle to a device information
        /// set that contains requested device information elements for a local computer.
        /// </summary>
        /// <param name="ClassGuid">A pointer to the guid for a device setup class or a device interface class.</param>
        /// <param name="Enumerator">A pointer to a NULL terminated string taht specifies an identifier for a plug and play device.</param>
        /// <param name="hwndParent">A handle to the top-level window to be used for a user interface that is associated with installing a device instance in
        /// the device information set.</param>
        /// <param name="Flags">Specifies control options that filter the device information elements that are added to the device information set.</param>
        /// <returns>A handle to a device information set upon success.</returns>
        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr SetupDiGetClassDevs(ref System.Guid ClassGuid, IntPtr Enumerator, IntPtr hwndParent, int Flags);

        /// <summary>
        /// Wrapper for the Win32 'SetupDiEnumDeviceInterfaces' within the setupapi.dll. Enumerates the device interfaces that are contained in
        /// a device information set.
        /// </summary>
        /// <param name="DeviceInfoSet">A pointer to a device information set taht contains the device interfaces for which to
        /// return information.</param>
        /// <param name="DeviceInfoData">A pointer to a SP_DEVINFO_DATA structure that specifies a device information element
        /// in DeviceInfoSet.</param>
        /// <param name="InterfaceClassGuid">A pointer to a guid that specifies a device interface class for the requested interface.</param>
        /// <param name="MemberIndex">A zero-based index into the list of interfaces in the device information set.</param>
        /// <param name="DeviceInterfaceData">A pointer to a caller allocated buffer that contains, on successful return, a completed
        /// SP_DEVICE_INTERFACE_DATA structure that identifies an interface that meets the search parameters.</param>
        /// <returns>True if the function completed without error, otherwise false. The error code for the failure can be retrieved by calling GetLastError.</returns>
        [DllImport("setupapi.dll", SetLastError = true)]
        public static extern bool SetupDiEnumDeviceInterfaces(IntPtr DeviceInfoSet, IntPtr DeviceInfoData, ref System.Guid InterfaceClassGuid, int MemberIndex, ref SP_DEVICE_INTERFACE_DATA DeviceInterfaceData);

        /// <summary>
        /// Wrapper for the Win32 'SetupDiGetDeviceInterfaceDetail' within the setupapi.dll. Returns details about a device interface.
        /// </summary>
        /// <param name="DeviceInfoSet">A pointer to the device information set that contains the interface for which
        /// to retrieve details.</param>
        /// <param name="DeviceInterfaceData">A pointer to a SP_DEVICE_INTERFACE_DATA structure that specifies the interface
        /// in DeviceInfoSet for which to retrieve details.</param>
        /// <param name="DeviceInterfaceDetailData">A pointer to a SP_DEVICE_INTERFACE_DETAIL_DATA structure to receive information about the specified
        /// interface.</param>
        /// <param name="DeviceInterfaceDetailDataSize">The size of the DeviceInterfaceDetailData buffer.</param>
        /// <param name="RequiredSize">A pointer to a variable DWORD that receives the required size of the DeviceInterfaceDetailData buffer.</param>
        /// <param name="DeviceInfoData">A pointer to a buffer that receives information about the device that supports the requested interface.</param>
        /// <returns>True if completed with no errors, otherwise false. The error code for the failure can be retrieved by calling GetLastError.</returns>
        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool SetupDiGetDeviceInterfaceDetail(IntPtr DeviceInfoSet, ref SP_DEVICE_INTERFACE_DATA DeviceInterfaceData, IntPtr DeviceInterfaceDetailData, Int32 DeviceInterfaceDetailDataSize, ref Int32 RequiredSize, IntPtr DeviceInfoData);

        /// <summary>
        /// Wrapper for the Win32 'SetupDiDestroyDeviceInfoList' within the setupapi.dll. Deletes a device information set and frees all associated
        /// memory.
        /// </summary>
        /// <param name="DeviceInfoSet">A handle to the device information set to delete.</param>
        /// <returns>True if completed with no errors, otherwise false. The error code for the failure can be retrieved by calling GetLastError.</returns>
        [DllImport("setupapi.dll", SetLastError = true)]
        public static extern int SetupDiDestroyDeviceInfoList(IntPtr DeviceInfoSet);
    }

    internal static class WinUSB
    {
        internal const UInt32 DEVICE_SPEED = 1;
        internal const Byte USB_ENDPOINT_DIRECTION_MASK = 0X80;

        internal const byte USB_DEVICE_DESCRIPTOR_TYPE = 1;

        internal enum POLICY_TYPE
        {
            SHORT_PACKET_TERMINATE = 1,
            AUTO_CLEAR_STALL,
            PIPE_TRANSFER_TIMEOUT,
            IGNORE_SHORT_PACKETS,
            ALLOW_PARTIAL_READS,
            AUTO_FLUSH,
            RAW_IO,
        }

        internal enum USBPIPETYPE : int
        {
            Control,
            Isochronous,
            Bulk,
            Interrupt,
        }

        internal enum USBDEVICESPEED
        {
            Low = 1,
            Full,
            High,
        }

        public static class USB
        {
            public const byte DESTYPEDEVICE = 1;
            public const byte DESTYPECONFIGURATION = 2;
            public const byte DESTYPESTRING = 3;
            public const byte DESTYPEINTERFACE = 4;
            public const byte DESTYPEENDPOINT = 5;
            public const byte DESTYPEDEVICEQUALIFIER = 6;
            public const byte DESTYPEOTHERSPEED = 7;
            public const byte DESTYPEDFUFUNCTIONAL = 0x21;
        }



        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct UsbSetupPacket
        {
            internal byte RequestType;
            internal byte Request;
            internal ushort Value;
            internal ushort Index;
            internal ushort Length;
        }



        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        internal struct WINUSB_PIPE_INFORMATION
        {
            internal USBPIPETYPE PipeType;
            internal byte PipeId;
            internal ushort MaximumPacketSize;
            internal byte Interval;
        }


        [DllImport("winusb.dll", SetLastError = true)]
        internal static extern bool WinUsb_ControlTransfer(IntPtr InterfaceHandle, UsbSetupPacket SetupPacket, IntPtr Buffer, UInt32 BufferLength, ref UInt32 LengthTransferred, IntPtr Overlapped);

        [DllImport("winusb.dll", SetLastError = true)]
        internal static extern bool WinUsb_Free(IntPtr InterfaceHandle);

        [DllImport("winusb.dll", SetLastError = true)]
        internal static extern bool WinUsb_Initialize(SafeFileHandle DeviceHandle, ref IntPtr InterfaceHandle);

        [DllImport("winusb.dll", SetLastError = true)]
        internal static extern bool WinUsb_GetDescriptor(IntPtr InterfaceHandle, byte DescriptorType, byte Index, ushort LangaugeID, IntPtr Buffer, uint BufferLength, ref uint LengthTransferred);

        //  Use this declaration to retrieve DEVICE_SPEED (the only currently defined InformationType).

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_QueryDeviceInformation(IntPtr InterfaceHandle, UInt32 InformationType, ref UInt32 BufferLength, ref Byte Buffer);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_QueryInterfaceSettings(IntPtr InterfaceHandle, Byte AlternateInterfaceNumber, ref DZX.Devices.USB.USBInterfaceDescriptor UsbAltInterfaceDescriptor);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_QueryPipe(IntPtr InterfaceHandle, Byte AlternateInterfaceNumber, Byte PipeIndex, ref WINUSB_PIPE_INFORMATION PipeInformation);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_ReadPipe(IntPtr InterfaceHandle, Byte PipeID, IntPtr Buffer, UInt32 BufferLength, ref UInt32 LengthTransferred, IntPtr Overlapped);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_AbortPipe(IntPtr InterfaceHandle, Byte PipeID);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_GetOverlappedResult(IntPtr InterfaceHandle, IntPtr Overlapped, ref UInt32 LengthTransferred, bool Wait);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_SetPipePolicy(IntPtr InterfaceHandle, Byte PipeID, UInt32 PolicyType, UInt32 ValueLength, ref byte Value);

        [DllImport("winusb.dll", SetLastError = true, EntryPoint = "WinUsb_SetPipePolicy")]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_SetPipePolicy(IntPtr InterfaceHandle, Byte PipeID, UInt32 PolicyType, UInt32 ValueLength, ref UInt32 Value);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_GetPipePolicy(IntPtr InterfaceHandle, Byte PipeID, UInt32 PolicyType, ref UInt32 ValueLength, out byte Value);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_GetPipePolicy(IntPtr InterfaceHandle, Byte PipeID, UInt32 PolicyType, ref UInt32 ValueLength, out UInt32 Value);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_GetCurrentAlternateSetting(IntPtr InterfaceHandle, ref byte Value);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_GetAssociatedInterface(IntPtr InterfaceHandle, byte AssociatedInterfaceIndex, ref IntPtr AssociatedInterfaceHandle);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_WritePipe(IntPtr InterfaceHandle, Byte PipeID, IntPtr Buffer, UInt32 BufferLength, ref UInt32 LengthTransferred, IntPtr Overlapped);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_FlushPipe(IntPtr InterfaceHandle, Byte PipeID);

        [DllImport("winusb.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinUsb_ResetPipe(IntPtr InterfaceHandle, Byte PipeID);
    }

    
}
