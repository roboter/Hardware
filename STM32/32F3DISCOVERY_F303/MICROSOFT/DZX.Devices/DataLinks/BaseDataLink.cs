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
using System.ComponentModel.Design;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using DZX.Devices.FTDI;
using DZX.Devices.USB;

namespace DZX.Devices.DataLinks
{
    /// <summary>
    /// Provides the base implementation for a data link.
    /// </summary>
    public abstract partial class BaseDataLink : Component
    {
        /// <summary>
        /// A collection of receivers for receiving responses to requests.
        /// </summary>
        private List<Receiver> _receivers = new List<Receiver>();

        /// <summary>
        /// The decoder for receiving SLIP encoded data.
        /// </summary>
        private SLIP.Decoder _decoder = new SLIP.Decoder();

        /// <summary>
        /// An underlying object to synchronize access to the underlying device.
        /// </summary>
        private object _sync = new object();

        /// <summary>
        /// A value used to limit the number of timer threads reading the underlying device.
        /// </summary>
        private int _reading;

        /// <summary>
        /// A timer used to poll the underlying device for received data.
        /// </summary>
        private System.Threading.Timer _timer;

        /// <summary>
        /// The underlying native USB device.
        /// </summary>
        private USBDevice _usbDevice;

        /// <summary>
        /// The underlying FTDI device.
        /// </summary>
        private FTDIDevice _ftdiDevice;

        /// <summary>
        /// The underlying serial port.
        /// </summary>
        private SerialPort _serialPort;

        /// <summary>
        /// Gets and sets the parent control for the port.
        /// </summary>
        [Browsable(false)]
        public ContainerControl ContainerControl { get; set; }

        /// <summary>
        /// Gets or sets the identifier for the pipe to be used for transmitting data over the data link.
        /// </summary>
        public Nullable<byte> TxPipe { get; set; }

        /// <summary>
        /// Gets or sets the identifier for the pipe to be used for receiving data over the data link.
        /// </summary>
        public Nullable<byte> RxPipe { get; set; }

        /// <summary>
        /// Gets or sets the native USB device to be used by the data link.
        /// </summary>
        public USBDevice USBDevice
        {
            get { return _usbDevice; }
            set
            {
                lock (_sync)
                {
                    _usbDevice = value;
                }
            }
        }

        /// <summary>
        /// Gets or sets the FTDI device to be used by the data link.
        /// </summary>
        public FTDIDevice FTDIDevice
        {
            get { return _ftdiDevice; }
            set
            {
                lock (_sync)
                {
                    _ftdiDevice = value;
                }
            }
        }

        /// <summary>
        /// Gets or sets the serial port to be used by the data link.
        /// </summary>
        public SerialPort SerialPort
        {
            get { return _serialPort; }
            set
            {
                lock (_sync)
                {
                    _serialPort = value;
                }
            }
        }

        /// <summary>
        /// Gets or sets the maximum amount of time, in milliseconds, to wait for a write transfer complete. Default
        /// is 2000.
        /// </summary>
        public int WriteTimeout { get; set; }

        /// <summary>
        /// Gets the protocol version for the data link.
        /// </summary>
        public int Version { get; protected set; }

        /// <summary>
        /// Gets a value indicating whether the link uses a CRC for validation of messages.
        /// </summary>
        /// <value>
        ///   <c>true</c> if the link uses CRC validation; otherwise, <c>false</c>.
        /// </value>
        public bool UseCRC { get; protected set; }

        /// <summary>
        /// Gets or sets the <see cref="T:System.ComponentModel.ISite" /> of the <see cref="T:System.ComponentModel.Component" />.
        /// </summary>
        public override ISite Site
        {
            get { return base.Site; }
            set
            {
                base.Site = value;

                if (base.Site == null)
                    return;

                IDesignerHost host = base.Site.GetService(typeof(IDesignerHost)) as IDesignerHost;
                if (host == null)
                    return;
                    
                IComponent componentHost = host.RootComponent;
                if (componentHost is ContainerControl)
                    ContainerControl = componentHost as ContainerControl;
            }
        }
           
        /// <summary>
        /// Occurs when any message has been received.
        /// </summary>
        public event EventHandler<DataLinkMessageEventArgs> MessageReceived;

        /// <summary>
        /// Initializes a new instance of the <see cref="BaseDataLink"/> class.
        /// </summary>
        public BaseDataLink()
        {
            _decoder.DataDecoded += decoder_DataDecoded;
            _timer = new System.Threading.Timer(OnTimer, null, 1, 1);

            // Defaults
            WriteTimeout = 2000;
        }

        /// <summary>
        /// Raises an event that is synchronized to the <see cref="ContainerControl" /> for the link.
        /// </summary>
        /// <typeparam name="T">The type of arguments for the event to be raised.</typeparam>
        /// <param name="handler">The handler of the event to be raised.</param>
        /// <param name="e">The arguments for the event to be raised.</param>
        protected void OnEvent<T>(EventHandler<T> handler, T e) where T : EventArgs
        {
            // Can't raise event without any handlers
            if (handler == null)
                return;

            // Invoke to synchronize with the container if needed

            if (ContainerControl != null && ContainerControl.InvokeRequired)
                ContainerControl.BeginInvoke((ThreadStart)delegate { OnEvent<T>(handler, e); });
            else
                handler(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:MessageReceived" /> event.
        /// </summary>
        /// <param name="e">The <see cref="DataLinkMessageEventArgs"/> instance containing the event data.</param>
        protected virtual void OnMessageReceived(DataLinkMessageEventArgs e)
        {
            OnEvent<DataLinkMessageEventArgs>(MessageReceived, e);
        }

        /// <summary>
        /// Called when the underlying timer expires.
        /// </summary>
        /// <param name="state">The state for the timer (not used here).</param>
        private void OnTimer(object state)
        {
            // Return if another thread is already reading the device
            int result = Interlocked.CompareExchange(ref _reading, 1, 0);
            if (result > 0)
                return;

            // Read from all associated devices
            lock (_sync)
            {
                ReadUSB();
                ReadFTDI();
                ReadSerial();
            }

            // Release busy reading indicator
            Interlocked.Decrement(ref _reading);
        }

        /// <summary>
        /// Reads and processes all data that has been received from the native USB device.
        /// </summary>
        private void ReadUSB()
        {
            if (_usbDevice == null)
                return;

            // Get any received messages
            USBMessage[] messages = (RxPipe.HasValue) ? _usbDevice.ReadAvailable(RxPipe.Value) : _usbDevice.ReadAvailable();
            if (messages == null)
                return;

            // Process each of the received messages
            foreach (USBMessage message in messages)
            {
                if (message.Size > 0)
                    ReceivedMessage(message.Data);
            }
        }

        /// <summary>
        /// Reads and processes all data that has been received from the FTDI device.
        /// </summary>
        private void ReadFTDI()
        {
            if (_ftdiDevice == null)
                return;

            // Get any received data
            byte[] data = _ftdiDevice.ReadAvailable();
            if (data == null || data.Length == 0)
                return;

            // Process the received data
            ProcessBytes(data);
        }

        /// <summary>
        /// Reads and processes all data that has been received from the serial port.
        /// </summary>
        private void ReadSerial()
        {
            if (_serialPort == null)
                return;

            if (!_serialPort.IsOpen)
                return;

            // Get any received data
            if (_serialPort.BytesToRead == 0)
                return;

            byte[] data = new byte[_serialPort.BytesToRead];
            _serialPort.Read(data, 0, data.Length);

            // Process the received data
            ProcessBytes(data);
        }

        /// <summary>
        /// Processes a received encapsulated message.
        /// </summary>
        /// <param name="data">The received message data.</param>
        public void ReceivedMessage(byte[] data)
        {
            if (data == null)
                return;

            if (data.Length < 4)
                return;

            if (UseCRC)
            {
                uint crc = CRC32.Calculate(0, data, 0, data.Length - 4);
                uint check = BitConverter.ToUInt32(data, data.Length - 4);

                if (crc != check)
                {
                    return;
                }
            }

            DataLinkMessage message = new DataLinkMessage();
            message.ID = BitConverter.ToUInt32(data, 0);

            if (UseCRC)
            {
                if (data.Length > 8)
                {
                    message.Data = new byte[data.Length - 8];
                    Buffer.BlockCopy(data, 4, message.Data, 0, message.Data.Length);
                }
            }
            else
            {
                if (data.Length > 4)
                {
                    message.Data = new byte[data.Length - 4];
                    Buffer.BlockCopy(data, 4, message.Data, 0, message.Data.Length);
                }
            }
            

            lock (_receivers)
            {
                foreach (Receiver receiver in _receivers)
                {
                    receiver.Process(message);
                }
            }

            // Notify a message has been received
            OnMessageReceived(new DataLinkMessageEventArgs(message));  
        }

        /// <summary>
        /// Processes non-encapsulated data.
        /// </summary>
        /// <param name="data">The data to be processed.</param>
        public void ProcessBytes(byte[] data)
        {
            _decoder.Decode(data);
        }

        /// <summary>
        /// Handles the DataDecoded event of the SLIP decoder control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="SLIP.DataEventArgs"/> instance containing the event data.</param>
        void decoder_DataDecoded(object sender, SLIP.DataEventArgs e)
        {
            ReceivedMessage(e.Data);
        }

        /// <summary>
        /// Writes a message over the link.
        /// </summary>
        /// <param name="message">The message to be written.</param>
        protected void Write(DataLinkMessage message)
        {
            // Calculate the total length of the message with overhead
            int len = message.DataLength + 4;

            if (UseCRC)
                len += 4;

            byte[] buffer = new byte[len];
            BitConverter.GetBytes(message.ID).CopyTo(buffer, 0);

            if (message.DataLength > 0)
                Buffer.BlockCopy(message.Data, 0, buffer, 4, message.Data.Length);

            if (UseCRC)
            {
                uint crc = CRC32.Calculate(0, buffer, 0, message.DataLength + 4);
                BitConverter.GetBytes(crc).CopyTo(buffer, message.DataLength + 4);
            }

            Write(buffer);
        }

        /// <summary>
        /// Writes the specified data over the link.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        /// <exception cref="System.NotSupportedException">No device specified to write data link message</exception>
        private void Write(byte[] data)
        {
            lock (_sync)
            {
                if (_usbDevice == null && _ftdiDevice == null && _serialPort == null)
                    throw new NotSupportedException("No device specified to write data link message");

                WriteUSB(data);
                WriteFTDI(data);
                WriteSerial(data);
            }
        }

        /// <summary>
        /// Writes the specified data over the native USB device.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        private void WriteUSB(byte[] data)
        {
            if (_usbDevice == null)
                return;

            if (TxPipe.HasValue)
                _usbDevice.Write(TxPipe.Value, data, WriteTimeout);
            else
                _usbDevice.Write(data, WriteTimeout);
        }

        /// <summary>
        /// Writes the specified data over the FTDI device.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        private void WriteFTDI(byte[] data)
        {
            if (_ftdiDevice == null)
                return;

            _ftdiDevice.Write(SLIP.Encode(data));
        }

        /// <summary>
        /// Writes the specified data over the serial port.
        /// </summary>
        /// <param name="data">The data to be written.</param>
        private void WriteSerial(byte[] data)
        {
            if (_serialPort == null)
                return;

            if (!_serialPort.IsOpen)
                return;

            data = SLIP.Encode(data);
            _serialPort.Write(data, 0, data.Length);
        }

        /// <summary>
        /// Reads information from the device about the link.
        /// </summary>
        /// <returns>The information as received from the device. Null on error.</returns>
        public DataLinkInfo ReadInfo(int timeout)
        {
            DataLinkMessage response = Request(Serialize(0, null), timeout);
            if (response == null)
                return null;

            return Deserialize<DataLinkInfo>(response.Data);
        }

        /// <summary>
        /// Gets the maximum allowable length of an array.
        /// </summary>
        /// <param name="obj">The object that contains the array.</param>
        /// <param name="field">The name of the array field.</param>
        /// <returns>The maximum length of the specified array field.</returns>
        public int GetArrayMaxLength(object obj, string field)
        {
            FieldInfo info = obj.GetType().GetField(field);
            if (info == null)
                return 0;

            return GetArrayMaxLength(info);
        }

        /// <summary>
        /// Gets the maximum length of an array within a data link.
        /// </summary>
        /// <param name="info">The information about the target array field.</param>
        /// <returns>The maximum length of the specified array field.</returns>
        protected int GetArrayMaxLength(FieldInfo info)
        {
            IEnumerable<Attribute> attributes = info.GetCustomAttributes(typeof(DataLinkArrayAttribute));
            if (attributes.Count() > 0)
                return (attributes.First() as DataLinkArrayAttribute).MaxLength;

            return 0;
        }

        /// <summary>
        /// Gets the maximum allowable length of a string.
        /// </summary>
        /// <param name="obj">The object that contains the string.</param>
        /// <param name="field">The name of the string field.</param>
        /// <returns>The maximum length of the specified string field.</returns>
        public int GetStringMaxLength(object obj, string field)
        {
            FieldInfo info = obj.GetType().GetField(field);
            if (info == null)
                return 0;

            return GetStringMaxLength(info);
        }

        /// <summary>
        /// Gets the maximum length of a string within a data link.
        /// </summary>
        /// <param name="info">The information about the target string field.</param>
        /// <returns>The maximum length of the specified string field.</returns>
        protected int GetStringMaxLength(FieldInfo info)
        {
            IEnumerable<Attribute> attributes = info.GetCustomAttributes(typeof(DataLinkStringAttribute));
            if (attributes.Count() > 0)
                return (attributes.First() as DataLinkStringAttribute).MaxLength;

            return 0;
        }

        /// <summary>
        /// Serializes the specified identifier and data values into a data link message.
        /// </summary>
        /// <param name="id">The identifier value for the message.</param>
        /// <param name="values">The values to be serialized into the message.</param>
        /// <returns>A message that contains the serialized values.</returns>
        protected DataLinkMessage Serialize(uint id, object values)
        {
            DataLinkMessage message = new DataLinkMessage();
            message.ID = id;

            if (values == null)
                return message;

            using (MemoryStream stream = new MemoryStream())
            {
                FieldInfo[] infos = values.GetType().GetFields(BindingFlags.Public | BindingFlags.Instance);
                foreach (FieldInfo info in infos)
                {
                    SerializeValue(stream, info, info.GetValue(values));
                }

                message.Data = stream.ToArray();
            }

            return message;
        }

        /// <summary>
        /// Serializes a field value into a memory stream.
        /// </summary>
        /// <param name="stream">The stream to receive the serialization data.</param>
        /// <param name="info">The information about the field to be serialized.</param>
        /// <param name="value">The instance value to be serialized.</param>
        protected void SerializeValue(MemoryStream stream, FieldInfo info, object value)
        {
            if (info.FieldType.IsArray)
            {
                Array array = value as Array;

                int len = (array != null) ? array.Length : 0;
                int maxLen = GetArrayMaxLength(info);

                if (maxLen <= Byte.MaxValue)
                    SerializeValue(stream, TypeCode.Byte, (byte)len);
                else if (maxLen <= UInt16.MaxValue)
                    SerializeValue(stream, TypeCode.UInt16, (UInt16)len);
                else
                    SerializeValue(stream, TypeCode.UInt32, (UInt32)len);

                for (int k = 0; k < len; k++)
                {
                    switch (Type.GetTypeCode(info.FieldType.GetElementType()))
                    {
                        case TypeCode.Byte:
                        case TypeCode.SByte:
                        case TypeCode.UInt16:
                        case TypeCode.Int16:
                        case TypeCode.UInt32:
                        case TypeCode.Int32:
                        case TypeCode.UInt64:
                        case TypeCode.Int64:
                        case TypeCode.Single:
                        case TypeCode.Double:
                        case TypeCode.Boolean:
                            SerializeValue(stream, Type.GetTypeCode(info.FieldType.GetElementType()), array.GetValue(k));
                            break;

                        default:
                            object item = array.GetValue(k);
                            FieldInfo[] infos = info.FieldType.GetElementType().GetFields(BindingFlags.Public | BindingFlags.Instance);
                            foreach (FieldInfo fi in infos)
                            {
                                SerializeValue(stream, fi, fi.GetValue(item));
                            }
                            break;
                    }
                }
            }
            else if (value is string)
            {
                int len = (value as string).Length;

                int maxLen = GetStringMaxLength(info);

                if (maxLen <= Byte.MaxValue)
                    SerializeValue(stream, TypeCode.Byte, (byte)(value as string).Length);
                else if (maxLen <= UInt16.MaxValue)
                    SerializeValue(stream, TypeCode.UInt16, (UInt16)(value as string).Length);
                else
                    SerializeValue(stream, TypeCode.UInt32, (UInt32)(value as string).Length);

                stream.Write(Encoding.ASCII.GetBytes(value as string), 0, len);
            }
            else if (value.GetType().IsClass)
            {
                 FieldInfo[] infos = value.GetType().GetFields(BindingFlags.Public | BindingFlags.Instance);
                 foreach (FieldInfo fi in infos)
                 {
                     SerializeValue(stream, fi, fi.GetValue(value));
                 }
            }
            else if (info.FieldType.IsEnum)
            {
                stream.WriteByte((byte)value);
            }
            else
            {
                SerializeValue(stream, Type.GetTypeCode(info.FieldType), value);
            }
        }

        /// <summary>
        /// Serializes a base value into a memory stream.
        /// </summary>
        /// <param name="stream">The stream to receive the serialization data.</param>
        /// <param name="typeCode">The type code of the value to be serialized.</param>
        /// <param name="value">The value instance to be serialized.</param>
        protected void SerializeValue(MemoryStream stream, TypeCode typeCode, object value)
        {
            switch (typeCode)
            {
                case TypeCode.Byte:
                    stream.WriteByte((byte)value);
                    break;
                case TypeCode.SByte:
                    stream.Write(BitConverter.GetBytes((sbyte)value), 0, sizeof(sbyte));
                    break;
                case TypeCode.UInt16:
                    stream.Write(BitConverter.GetBytes((ushort)value), 0, sizeof(ushort));
                    break;
                case TypeCode.Int16:
                    stream.Write(BitConverter.GetBytes((short)value), 0, sizeof(short));
                    break;
                case TypeCode.UInt32:
                    stream.Write(BitConverter.GetBytes((uint)value), 0, sizeof(uint));
                    break;
                case TypeCode.Int32:
                    stream.Write(BitConverter.GetBytes((int)value), 0, sizeof(int));
                    break;
                case TypeCode.UInt64:
                    stream.Write(BitConverter.GetBytes((ulong)value), 0, sizeof(ulong));
                    break;
                case TypeCode.Int64:
                    stream.Write(BitConverter.GetBytes((long)value), 0, sizeof(long));
                    break;
                case TypeCode.Single:
                    stream.Write(BitConverter.GetBytes((float)value), 0, sizeof(float));
                    break;
                case TypeCode.Double:
                    stream.Write(BitConverter.GetBytes((double)value), 0, sizeof(double));
                    break;
                case TypeCode.Boolean:
                    stream.WriteByte((byte)((bool)value ? 1 : 0));
                    break;
            }
        }

        /// <summary>
        /// Creates and returns an object that represents serialization data.
        /// </summary>
        /// <typeparam name="T">The type of object to be returned.</typeparam>
        /// <param name="data">The serialized data used to initialize the returned object.</param>
        /// <returns>An object that represents the serialized data.</returns>
        protected T Deserialize<T>(byte[] data) where T : new()
        {
            object response = new T();
            Deserialize(response, data, 0);
            return (T)response;
        }

        /// <summary>
        /// Initializes an object from an array of serialized data.
        /// </summary>
        /// <param name="obj">The object to be initialized.</param>
        /// <param name="data">The serialized data.</param>
        /// <param name="offset">A zero-based offset into the data.</param>
        /// <returns>The total number of bytes that have been deserialized.</returns>
        private int Deserialize(object obj, byte[] data, int offset)
        {
            int idx = offset;

            FieldInfo[] fi = obj.GetType().GetFields(BindingFlags.Public | BindingFlags.Instance);
            foreach (FieldInfo info in fi)
            {
                int size = Deserialize(obj, info, data, idx);
                idx += size;
            }

            return idx;
        }

        /// <summary>
        /// Initializes an object from an array of serialized data.
        /// </summary>
        /// <param name="obj">The object to be initialized.</param>
        /// <param name="info">Information about the field to be initialized.</param>
        /// <param name="data">The serialized data.</param>
        /// <param name="offset">A zero-based offset into the data.</param>
        /// <returns>The total number of bytes that have been deserialized.</returns>
        private int Deserialize(object obj, FieldInfo info, byte[] data, int offset)
        {
            if (info.FieldType.IsArray)
            {
                int maxLen = GetArrayMaxLength(info);
                int len = 0;
                int size = 0;

                if (maxLen <= Byte.MaxValue)
                {
                    len = (int)data[offset];
                    size = 1;
                }
                else if (maxLen <= UInt16.MaxValue)
                {
                    len = (int)BitConverter.ToInt16(data, offset);
                    size = 2;
                }
                else
                {
                    len = BitConverter.ToInt32(data, offset);
                    size = 4;
                }

                if (len < 0)
                    throw new DataLinkException("Invalid negative array count");

                object array = Activator.CreateInstance(info.FieldType, len);
                info.SetValue(obj, array);

                for (int k = 0; k < len; k++)
                {
                    int sz;

                    switch (Type.GetTypeCode(info.FieldType.GetElementType()))
                    {
                        case TypeCode.Byte:
                        case TypeCode.SByte:
                        case TypeCode.UInt16:
                        case TypeCode.Int16:
                        case TypeCode.UInt32:
                        case TypeCode.Int32:
                        case TypeCode.UInt64:
                        case TypeCode.Int64:
                        case TypeCode.Single:
                        case TypeCode.Double:
                        case TypeCode.Boolean:

                            object value = DeserializeValue(Type.GetTypeCode(info.FieldType.GetElementType()), data, offset + size, out sz);
                            
                            if (info.FieldType.GetElementType().IsEnum)
                            {
                                Array tarray = Enum.GetValues(info.FieldType.GetElementType());
                                object eobj = tarray.GetValue(Convert.ToInt32(value));
                                (array as Array).SetValue(eobj, k);
                            }
                            else
                            {
                                (array as Array).SetValue(value, k);
                            }
                            size += sz;
                            break;

                        default:
                            object item = Activator.CreateInstance(info.FieldType.GetElementType());
                            (array as Array).SetValue(item, k);
                            size = Deserialize(item, data, offset + size);
                            break;
                    }
                }

                return size;
            }
            else if (info.FieldType == typeof(string))
            {
                int maxLen = GetStringMaxLength(info);

                if (maxLen <= Byte.MaxValue)
                {
                    int len = (int)data[offset];
                    info.SetValue(obj, Encoding.ASCII.GetString(data, offset + 1, len));
                    return len + 1;
                }
                else if (maxLen <= UInt16.MaxValue)
                {
                    int len = (int)BitConverter.ToInt16(data, offset);
                    info.SetValue(obj, Encoding.ASCII.GetString(data, offset + 2, len));
                    return len + 2;
                }
                else
                {
                    int len = BitConverter.ToInt32(data, offset);
                    info.SetValue(obj, Encoding.ASCII.GetString(data, offset + 4, len));
                    return len + 4;
                }
            }
            else if (info.FieldType.IsClass)
            {
                object cls = Activator.CreateInstance(info.FieldType);

                info.SetValue(obj, cls);

                int idx = offset;

                FieldInfo[] fi = info.FieldType.GetFields(BindingFlags.Public | BindingFlags.Instance);
                foreach (FieldInfo childInfo in fi)
                {
                    idx += Deserialize(cls, childInfo, data, idx);
                }

                return idx;
            }
            else
            {
                int size;

                object value = DeserializeValue(Type.GetTypeCode(info.FieldType), data, offset, out size);
                info.SetValue(obj, value);
                return size;
            }
        }

        /// <summary>
        /// Deserializes data into a value.
        /// </summary>
        /// <param name="typeCode">The type code for object to be returned.</param>
        /// <param name="data">The serialized data.</param>
        /// <param name="offset">The zero-based offset into the data.</param>
        /// <param name="size">The size, in bytes, of the object that was returned.</param>
        /// <returns>The deserialized object.</returns>
        private object DeserializeValue(TypeCode typeCode, byte[] data, int offset, out int size)
        {
            switch (typeCode)
            {
                case TypeCode.Boolean:
                    size = sizeof(byte);
                    return Convert.ToBoolean(data[offset]);
                case TypeCode.Byte:
                    size = sizeof(byte);
                    return data[offset];
                case TypeCode.SByte:
                    size = sizeof(sbyte);
                    return Convert.ToSByte(data[offset]);
                case TypeCode.UInt16:
                    size = sizeof(UInt16);
                    return BitConverter.ToUInt16(data, offset);
                case TypeCode.Int16:
                    size = sizeof(Int16);
                    return BitConverter.ToInt16(data, offset);
                case TypeCode.UInt32:
                    size = sizeof(UInt32);
                    return BitConverter.ToUInt32(data, offset);
                case TypeCode.Int32:
                    size = sizeof(Int32);
                    return BitConverter.ToInt32(data, offset);
                case TypeCode.UInt64:
                    size = sizeof(UInt64);
                    return BitConverter.ToUInt64(data, offset);
                case TypeCode.Int64:
                    size = sizeof(Int64);
                    return BitConverter.ToInt64(data, offset);
                case TypeCode.Single:
                    size = sizeof(Single);
                    return BitConverter.ToSingle(data, offset);
                case TypeCode.Double:
                    size = sizeof(Double);
                    return BitConverter.ToDouble(data, offset); 
            }

            size = 0;
            return null;
        }

        /// <summary>
        /// Transmits a request message and waits to receive the response.
        /// </summary>
        /// <param name="request">The request message to be transmitted.</param>
        /// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a response
        /// message to be received.</param>
        /// <returns></returns>
        protected virtual DataLinkMessage Request(DataLinkMessage request, int timeout)
        {
            // Add a receiver to capture the response message
            Receiver receiver = CreateReceiver(request.ID);

            try
            {
                // Transmit the request message
                Write(request);

                // Wait to receive the response message
                return receiver.Wait(timeout);
            }
            finally
            {
                ReleaseReceiver(receiver);
            }
        }

        /// <summary>
        /// Creates and adds a receiver to the link.
        /// </summary>
        /// <param name="id">The identifier of the messages to be received by the receiver.</param>
        /// <returns>The receiver that has been created.</returns>
        private Receiver CreateReceiver(uint id)
        {
            Receiver receiver = new Receiver(0x0000FFFF, id);

            // Add the receiver to enable processing of received messages
            lock (_receivers)
            {
                _receivers.Add(receiver);
            }

            return receiver;
        }

        /// <summary>
        /// Releases a receiver from the link.
        /// </summary>
        /// <param name="receiver">The receiver to be released.</param>
        private void ReleaseReceiver(Receiver receiver)
        {
            lock (_receivers)
            {
                _receivers.Remove(receiver);
            }
        }
    }

    /// <summary>
    /// Represents a message that is transferred over a data link.
    /// </summary>
    public class DataLinkMessage
    {
        /// <summary>
        /// Gets or sets the identifier for the message.
        /// </summary>
        public uint ID { get; set; }

        /// <summary>
        /// Gets or sets the data for the message.
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// Gets the length, in bytes, of the data for the message.
        /// </summary>
        public int DataLength
        {
            get
            {
                if (Data == null)
                    return 0;

                return Data.Length;
            }
        }

        /// <summary>
        /// Gets or sets the <see cref="System.Byte"/> at the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="System.Byte"/> at the specified index</returns>
        public byte this[int index]
        {
            get { return Data[index]; }
            set { Data[index] = value; }
        }
    }

    /// <summary>
    /// Represents errors that occur within a Data Link.
    /// </summary>
    [Serializable]
    public class DataLinkException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkException"/> class.
        /// </summary>
        public DataLinkException() :
            base() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkException"/> class.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public DataLinkException(string message) :
            base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkException"/> class.
        /// </summary>
        /// <param name="message">The error message that explains the reason for the exception.</param>
        /// <param name="innerException">The exception that is the cause of the current exception, or a null reference (Nothing in Visual Basic) if no inner exception is specified.</param>
        public DataLinkException(string message, Exception innerException) :
            base(message, innerException) { }
    }

    /// <summary>
    /// Represents arguments for an event that contains a data link message.
    /// </summary>
    public class DataLinkMessageEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the message for the event.
        /// </summary>
        public DataLinkMessage Message { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkMessageEventArgs"/> class.
        /// </summary>
        /// <param name="message">The message for the event.</param>
        public DataLinkMessageEventArgs(DataLinkMessage message)
        {
            Message = message;
        }
    }

    /// <summary>
    /// Represents an attribute to specify characteristics of an array within a data link.
    /// </summary>
    public class DataLinkArrayAttribute : Attribute
    {
        /// <summary>
        /// Gets or sets the maximum length of the array.
        /// </summary>
        public int MaxLength { get; set; }
    }

    /// <summary>
    /// Represents an attribute to specify characteristics of a string within a data link.
    /// </summary>
    public class DataLinkStringAttribute : Attribute
    {
        /// <summary>
        /// Gets or sets the maximum length of the string.
        /// </summary>
        public int MaxLength { get; set; }
    }

    /// <summary>
    /// Represents information about a data link.
    /// </summary>
    public class DataLinkInfo
    {
        /// <summary>
        /// Gets or sets the protocol version for the data link.
        /// </summary>
        public int Version;
    }
}
