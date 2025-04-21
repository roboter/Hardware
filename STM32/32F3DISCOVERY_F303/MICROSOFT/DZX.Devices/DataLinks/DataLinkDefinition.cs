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
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace DZX.Devices.DataLinks
{
    /// <summary>
    /// Provides a definition of the messaging protocol for a data link.
    /// </summary>
    [DataContract]
    public class DataLinkDefinition
    {
        /// <summary>
        /// Gets the display name for the definition.
        /// </summary>
        public string Name
        {
            get
            {
                if (!string.IsNullOrEmpty(FileName))
                    return Path.GetFileName(FileName);

                return "untitled.xml";
            }   
        }

        /// <summary>
        /// Gets the file name for the definition.
        /// </summary>
        public string FileName { get; private set; }

        /// <summary>
        /// Gets a value indicating whether this <see cref="DataLinkDefinition"/> exists within
        /// the file system.
        /// </summary>
        /// <value>
        ///   <c>true</c> if the definition already exists within the file system; otherwise, <c>false</c>.
        /// </value>
        public bool Exists { get { return File.Exists(FileName); } }

        /// <summary>
        /// Gets or sets the protocol version for the definition.
        /// </summary>
        [DataMember]
        public int Version { get; set; }

        /// <summary>
        /// Gets or sets the name of the link when generating code for the definition.
        /// </summary>
        [DataMember]
        public string LinkName { get; set; }

        /// <summary>
        /// Gets or sets the last code generation date.
        /// </summary>
        [DataMember]
        public DateTime LastGenDate { get; set; }

        /// <summary>
        /// Gets or sets options for code generation for the definition.
        /// </summary>
        [DataMember]
        public CodeGenerationOptions CodeGenerationOptions { get; set; }

        /// <summary>
        /// Gets or sets the enumerations for the definition.
        /// </summary>
        [DataMember]
        public List<EnumerationDefinition> Enumerations { get; set; }

        /// <summary>
        /// Gets or sets the structures for the definition.
        /// </summary>
        [DataMember]
        public List<StructureDefinition> Structures { get; set; }

        /// <summary>
        /// Gets or sets the messages for the definition.
        /// </summary>
        [DataMember]
        public List<MessageDefinition> Messages { get; set; }

        /// <summary>
        /// Gets or sets the size, in bytes, of the boolean type as defined within the device.
        /// </summary>
        [DataMember]
        public int BooleanSize { get; set; }

        /// <summary>
        /// Gets or sets the device type for the definition.
        /// </summary>
        [DataMember]
        public DeviceType Device { get; set; }

        /// <summary>
        /// Gets or sets the host type for the definition.
        /// </summary>
        [DataMember]
        public HostType Host { get; set; }

        /// <summary>
        /// Gets or sets the log items for the definition.
        /// </summary>
        [DataMember]
        public List<LogItem> LogItems { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the link uses a CRC value to validate messages.
        /// </summary>
        /// <value>
        ///   <c>true</c> if the link uses a CRC for validation; otherwise, <c>false</c>.
        /// </value>
        [DataMember]
        public bool UseCRC { get; set; }

        /// <summary>
        /// Gets the default device code directory.
        /// </summary>
        public string DefaultDeviceDirectory
        {
            get { return Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "DZX Designs", "Data Link", Path.GetFileNameWithoutExtension(Name), "Device"); }
        }

        /// <summary>
        /// Gets the default host code directory.
        /// </summary>
        public string DefaultHostDirectory
        {
            get { return Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "DZX Designs", "Data Link", Path.GetFileNameWithoutExtension(Name), "Host"); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkDefinition"/> class.
        /// </summary>
        public DataLinkDefinition()
        {
            // Assign defaults
            LinkName = "App";
            Enumerations = new List<EnumerationDefinition>();
            Structures = new List<StructureDefinition>();
            Messages = new List<MessageDefinition>();
            BooleanSize = 4;
            Version = 0;
            CodeGenerationOptions = new CodeGenerationOptions();
            LogItems = new List<LogItem>();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkDefinition"/> class from the
        /// specified file.
        /// </summary>
        /// <param name="path">The path of the file used to initialize the definition.</param>
        /// <returns>A definition that represents the given file.</returns>
        public static DataLinkDefinition FromFile(string path)
        {
            using (FileStream stream = new FileStream(path, FileMode.Open))
            {
                DataLinkDefinition def = FromStream(stream);
                def.FileName = path;
                return def;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DataLinkDefinition"/> class from the
        /// specified stream.
        /// </summary>
        /// <param name="stream">The stream used to initialize the definition.</param>
        /// <returns>A definition that represents the given stream.</returns>
        public static DataLinkDefinition FromStream(Stream stream)
        {
            DataContractSerializer serializer = new DataContractSerializer(typeof(DataLinkDefinition));
            return serializer.ReadObject(stream) as DataLinkDefinition;
        }

        /// <summary>
        /// Finds and returns the structure with the following name.
        /// </summary>
        /// <param name="name">The name of the structure to be returned.</param>
        /// <returns>The structure with the given name, if found; otherwise null.</returns>
        public StructureDefinition FindStructure(string name)
        {
            return Structures.FirstOrDefault(s => s.Name == name);
        }

        /// <summary>
        /// Finds and returns the enumeration with the following name.
        /// </summary>
        /// <param name="name">The name of the enumeration to be returned.</param>
        /// <returns>The enumeration with the given name, if found; otherwise null.</returns>
        public EnumerationDefinition FindEnumeration(string name)
        {
            return Enumerations.FirstOrDefault(s => s.Name == name);
        }

        /// <summary>
        /// Saves this definition to the specified file.
        /// </summary>
        /// <param name="path">The full path of the file to save the definition.</param>
        public void Save(string path)
        {
            using (FileStream stream = new FileStream(path, FileMode.Create))
            {
                Save(stream);
                FileName = path;
            }
        }

        /// <summary>
        /// Saves this definition to the specified stream.
        /// </summary>
        /// <param name="stream">The stream to save the definition.</param>
        public void Save(Stream stream)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;

            DataContractSerializer serializer = new DataContractSerializer(typeof(DataLinkDefinition));
            using (XmlWriter writer = XmlWriter.Create(stream, settings))
            {
                serializer.WriteObject(writer, this);
            }
        }

        /// <summary>
        /// Gets and returns information about the largest messages within this definition.
        /// </summary>
        /// <returns>Information about the largest messages.</returns>
        public MaxMessageSizes GetMaxSizes()
        {
            MaxMessageSizes sizes = new MaxMessageSizes();

            sizes.MaxRequestSize = GetMaxSize(Messages.Where(m => m.Type == MessageType.RequestResponse), true, false);
            sizes.MaxResponseSize = GetMaxSize(Messages.Where(m => m.Type == MessageType.RequestResponse), false, true);
            sizes.MaxSize = Math.Max(sizes.MaxRequestSize, sizes.MaxResponseSize);

            sizes.MaxUnsolicitedDeviceSize = GetMaxSize(Messages.Where(m => m.Type == MessageType.Unsolicited && 
                (m.Recipient == Recipient.Device || m.Recipient == Recipient.HostAndDevice)), true, false);

            sizes.MaxUnsolicitedHostSize = GetMaxSize(Messages.Where(m => m.Type == MessageType.Unsolicited &&
                (m.Recipient == Recipient.Host || m.Recipient == Recipient.HostAndDevice)), true, false);

            sizes.MaxUnsolicitedSize = Math.Max(sizes.MaxUnsolicitedDeviceSize, sizes.MaxUnsolicitedHostSize);

            sizes.MaxDeviceSize = Math.Max(sizes.MaxRequestSize, sizes.MaxUnsolicitedDeviceSize);
            sizes.MaxHostSize = Math.Max(sizes.MaxResponseSize, sizes.MaxUnsolicitedHostSize);

            return sizes;
        }

        /// <summary>
        /// Gets the maximum total size, in bytes, of the largest message.
        /// </summary>
        /// <param name="messages">The collection of messages to be checked for maximum sizes.</param>
        /// <param name="requests">Use <c>true</c> to include request parameters in the size calculations.</param>
        /// <param name="responses">Use <c>true</c> to include response parameters in the size calculations.</param>
        /// <returns>The maximum total size of the largest message.</returns>
        private int GetMaxSize(IEnumerable<MessageDefinition> messages, bool requests, bool responses)
        {
            int maxSize = 0;

            foreach (MessageDefinition message in messages)
            {
                int msgSize = 0;

                if (requests)
                    msgSize += GetMaxSize(message.RequestParameters);

                if (responses)
                    msgSize += GetMaxSize(message.ResponseParameters);

                if (msgSize > maxSize)
                    maxSize = msgSize;
            }

            // Add in message overhead
            maxSize += 4;

            // Round up to force 32-bit alignment
            if ((maxSize % 4) != 0)
            {
                maxSize += (4 - (maxSize % 4));
            }

            // Account for the default 'ReadInfo' response
            if (responses) 
            {
                if (maxSize < 8)
                    maxSize = 8;
            }

            if (UseCRC)
                maxSize += 4;

            return maxSize;
        }

        /// <summary>
        /// Gets the maximum total size, in bytes, of all of the specified parameter values.
        /// </summary>
        /// <param name="parameters">The parameters.</param>
        /// <returns>The maximum total size of the given parameters.</returns>
        private int GetMaxSize(List<ParameterDefinition> parameters)
        {
            int size = 0;

            foreach (ParameterDefinition parameter in parameters)
            {
                int itemSize = 0;

                switch (parameter.Type)
                {
                    case ParameterType.U8:
                    case ParameterType.S8:
                    case ParameterType.Enumeration:
                    case ParameterType.String:
                        itemSize = 1;
                        break;
                    case ParameterType.U16:
                    case ParameterType.S16:
                        itemSize = 2;
                        break;
                    case ParameterType.U32:
                    case ParameterType.S32:
                    case ParameterType.F32:
                        itemSize = 4;
                        break;
                    case ParameterType.U64:
                    case ParameterType.S64:
                    case ParameterType.F64:
                        itemSize = 8;
                        break;

                    case ParameterType.Boolean:
                        itemSize = BooleanSize;
                        break;

                    case ParameterType.Structure:
                        StructureDefinition structure = FindStructure(parameter.StructureName);
                        if (structure != null)
                        {
                            itemSize += GetMaxSize(structure.Parameters);
                        }
                        break;
                }

                if (parameter.IsArray)
                {
                    itemSize *= parameter.ArrayLength;
                }

                size += itemSize;
            }

            return size;
        }
    }

    /// <summary>
    /// Represents a recipient of a data link message.
    /// </summary>
    [DataContract]
    public enum Recipient
    {
        /// <summary>
        /// Indicates only the host will receive the message.
        /// </summary>
        [EnumMember]
        Host,

        /// <summary>
        /// Indicates only the device will receive the message.
        /// </summary>
        [EnumMember]
        Device,

        /// <summary>
        /// Indicates that both the host and device will receive the message.
        /// </summary>
        [EnumMember]
        HostAndDevice,
    }

    /// <summary>
    /// Represents a type of message transferred over a data link.
    /// </summary>
    [DataContract]
    public enum MessageType
    {
        /// <summary>
        /// Indicates the message is unsolicited and sent without a request.
        /// </summary>
        [EnumMember]
        Unsolicited,

        /// <summary>
        /// Indicates the message is transferred as a request with a subsequent response.
        /// </summary>
        [EnumMember]
        RequestResponse,
    }

    /// <summary>
    /// Provides a definition for a message that is transferred over a data link.
    /// </summary>
    [DataContract(Name="Message")]
    public class MessageDefinition
    {
        /// <summary>
        /// Gets or sets the recipient of the message.
        /// </summary>
        [DataMember]
        public Recipient Recipient { get; set; }

        /// <summary>
        /// Gets or sets the message type for the message.
        /// </summary>
        [DataMember]
        public MessageType Type { get; set; }

        /// <summary>
        /// Gets or sets the name for the message.
        /// </summary>
        [DataMember]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the identifier for the message.
        /// </summary>
        [DataMember]
        public int ID { get; set; }

        /// <summary>
        /// Gets or sets the request parameters for the message.
        /// </summary>
        [DataMember]
        public List<ParameterDefinition> RequestParameters { get; set; }

        /// <summary>
        /// Gets or sets the response parameters for the message.
        /// </summary>
        [DataMember]
        public List<ParameterDefinition> ResponseParameters { get; set; }

        /// <summary>
        /// Gets a value indicating whether this message has request parameters.
        /// </summary>
        public bool HasRequest { get { return (RequestParameters.Count > 0); } }

        /// <summary>
        /// Gets a value indicating whether this instance has response parameters.
        /// </summary>
        public bool HasResponse
        {
            get
            {
                if (Type == MessageType.RequestResponse)
                    return (ResponseParameters.Count > 0);

                return false;
            }
        }

        /// <summary>
        /// Gets a value indicating whether the message is receivable by the host.
        /// </summary>
        public bool HostReceivable
        {
            get 
            {
                if (Type == MessageType.RequestResponse)
                    return true;

                if (Recipient == Devices.DataLinks.Recipient.Host)
                    return true;

                if (Recipient == Devices.DataLinks.Recipient.HostAndDevice)
                    return true;

                return false;
            }
        }

        /// <summary>
        /// Gets a value indicating whether the message is receivable by the device.
        /// </summary>
        public bool DeviceReceivable
        {
            get
            {
                if (Type == MessageType.RequestResponse)
                    return true;

                if (Recipient == Devices.DataLinks.Recipient.Device)
                    return true;

                if (Recipient == Devices.DataLinks.Recipient.HostAndDevice)
                    return true;

                return false;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MessageDefinition"/> class.
        /// </summary>
        public MessageDefinition()
        {
            RequestParameters = new List<ParameterDefinition>();
            ResponseParameters = new List<ParameterDefinition>();
        }
    }

    /// <summary>
    /// Represents a type of parameter within a data link definition.
    /// </summary>
    [DataContract]
    public enum ParameterType
    {
        /// <summary>
        /// Represents an unsigned 8-bit integer parameter type.
        /// </summary>
        [EnumMember]
        U8,
        /// <summary>
        /// Represents a signed 8-bit integer parameter type.
        /// </summary>
        [EnumMember]
        S8,
        /// <summary>
        /// Represents an unsigned 16-bit integer parameter type.
        /// </summary>
        [EnumMember]
        U16,
        /// <summary>
        /// Represents a signed 16-bit integer parameter type.
        /// </summary>
        [EnumMember]
        S16,
        /// <summary>
        /// Represents an unsigned 32-bit integer parameter type.
        /// </summary>
        [EnumMember]
        U32,
        /// <summary>
        /// Represents a signed 32-bit integer parameter type.
        /// </summary>
        [EnumMember]
        S32,
        /// <summary>
        /// Represents an unsigned 64-bit integer parameter type.
        /// </summary>
        [EnumMember]
        U64,
        /// <summary>
        /// Represents a signed 64-bit integer parameter type.
        /// </summary>
        [EnumMember]
        S64,
        /// <summary>
        /// Represents a single (32-bit) precision floating point value parameter type.
        /// </summary>
        [EnumMember]
        F32,
        /// <summary>
        /// Represents a double (64-bit) precision floating point value parameter type.
        /// </summary>
        [EnumMember]
        F64,
        /// <summary>
        /// Represents a boolean parameter type.
        /// </summary>
        [EnumMember]
        Boolean,
        /// <summary>
        /// Represents a string parameter type.
        /// </summary>
        [EnumMember]
        String,
        /// <summary>
        /// Represents an enumeration parameter type.
        /// </summary>
        [EnumMember]
        Enumeration,
        /// <summary>
        /// Represents a structure parameter type.
        /// </summary>
        [EnumMember]
        Structure,
    }

    /// <summary>
    /// Represents a display option for a value within a data link.
    /// </summary>
    [DataContract]
    public enum DisplayType
    {
        [EnumMember]
        Default,
        [EnumMember]
        Decimal,
        [EnumMember]
        ScaledDecimal,
        [EnumMember]
        Hexadecimal,
    }

    /// <summary>
    /// Provides a definition of a parameter type within a data link definition.
    /// </summary>
    [DataContract(Name="Parameter")]
    public class ParameterDefinition
    {
        /// <summary>
        /// Gets or sets the type of the parameter.
        /// </summary>
        [DataMember]
        public ParameterType Type { get; set; }

        /// <summary>
        /// Gets or sets the name of the parameter.
        /// </summary>
        [DataMember]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the description for the parameter.
        /// </summary>
        [DataMember]
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the length of the array for the parameter, if the parameter is an array.
        /// </summary>
        [DataMember]
        public int ArrayLength { get; set; }

        /// <summary>
        /// Gets or sets the name of the enumeration for the parameter, if the parameter is an enumeration type.
        /// </summary>
        [DataMember(Name = "Enumeration")]
        public string EnumerationName { get; set; }

        /// <summary>
        /// Gets or sets the name of the structure for the parameter, if the parameter is a structure type.
        /// </summary>
        [DataMember(Name="Structure")]
        public string StructureName { get; set; }

        /// <summary>
        /// Gets or sets the display type for the parameter.
        /// </summary>
        [DataMember]
        public DisplayType DisplayType { get; set; }

        /// <summary>
        /// Gets or sets the multiplication factor for the display value for the parameter.
        /// </summary>
        [DataMember]
        public decimal Factor { get; set; }

        /// <summary>
        /// Gets or sets the offset for the display value for the parameter.
        /// </summary>
        [DataMember]
        public decimal Offset { get; set; }

        /// <summary>
        /// Gets or sets the unit for the display value for the parameter.
        /// </summary>
        [DataMember]
        public string Unit { get; set; }

        /// <summary>
        /// Gets a value indicating whether this instance is an array.
        /// </summary>
        /// <value>
        ///   <c>true</c> if this instance is an array; otherwise, <c>false</c>.
        /// </value>
        public bool IsArray { get { return (ArrayLength > 1); } }

        /// <summary>
        /// Initializes a new instance of the <see cref="ParameterDefinition"/> class.
        /// </summary>
        public ParameterDefinition()
        {
            ArrayLength = 1;
        }
    }

    /// <summary>
    /// Represents options regarding the generation of code for a data link definition.
    /// </summary>
    [DataContract]
    public class CodeGenerationOptions
    {
        /// <summary>
        /// Gets or sets a value indicating whether to use the default directory for the host code.
        /// </summary>
        [DataMember]
        public bool UseDefaultHostDirectory { get; set; }

        /// <summary>
        /// Gets or sets the custom directory for the host code.
        /// </summary>
        [DataMember]
        public string HostDirectory { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether to use the default directory for the device code.
        /// </summary>
        [DataMember]
        public bool UseDefaultDeviceDirectory { get; set; }

        /// <summary>
        /// Gets or sets the custom directory for the device code.
        /// </summary>
        [DataMember]
        public string DeviceDirectory { get; set; }

        /// <summary>
        /// Gets or sets the memory type to use for the buffer for unsolicited sending messages.
        /// </summary>
        public MemoryType UnsolicitedBufferMemory { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="CodeGenerationOptions"/> class.
        /// </summary>
        public CodeGenerationOptions()
        {
            // Defaults
            UseDefaultHostDirectory = true;
            UseDefaultDeviceDirectory = true;

            UnsolicitedBufferMemory = MemoryType.LocalStack;
        }
    }

    /// <summary>
    /// Represents a definition of an enumeration parameter type within a data link definition.
    /// </summary>
    [DataContract(Name="Enumeration")]
    public class EnumerationDefinition
    {
        /// <summary>
        /// Gets or sets the name of the enumeration.
        /// </summary>
        [DataMember]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the description for the enumeration.
        /// </summary>
        [DataMember]
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the members for the enumeration.
        /// </summary>
        [DataMember]
        public List<EnumerationDefinitionMember> Members { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="EnumerationDefinition"/> class.
        /// </summary>
        public EnumerationDefinition()
        {
            Members = new List<EnumerationDefinitionMember>();
        }
    }

    /// <summary>
    /// Represents a definition of a member within an enumeration.
    /// </summary>
    [DataContract(Name="EnumerationMember")]
    public class EnumerationDefinitionMember
    {
        /// <summary>
        /// Gets or sets the name of the member.
        /// </summary>
        [DataMember]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the description for the member.
        /// </summary>
        [DataMember]
        public string Description { get; set; }
    }

    /// <summary>
    /// Represents a definition of a data structure within a data link definition.
    /// </summary>
    [DataContract(Name="Structure")]
    public class StructureDefinition
    {
        /// <summary>
        /// Gets or sets the name for the structure.
        /// </summary>
        [DataMember]
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the description for the structure.
        /// </summary>
        [DataMember]
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the parameters for the structure.
        /// </summary>
        [DataMember]
        public List<ParameterDefinition> Parameters { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="StructureDefinition"/> class.
        /// </summary>
        public StructureDefinition()
        {
            Parameters = new List<ParameterDefinition>();
        }
    }

    /// <summary>
    /// Represents the type of host for a data link.
    /// </summary>
    [DataContract]
    public enum HostType
    {
        /// <summary>
        /// Indicates the host code is in .NET C#.
        /// </summary>
        [EnumMember]
        NET_CS,
    }

    /// <summary>
    /// Represents the type of device for a data link.
    /// </summary>
    [DataContract]
    public enum DeviceType
    {
        /// <summary>
        /// Indicates the device code is in embedded 'C'.
        /// </summary>
        [EnumMember]
        EmbeddedC,
    }

    /// <summary>
    /// Represents a type of memory used when implementing a data link.
    /// </summary>
    [DataContract]
    public enum MemoryType
    {
        /// <summary>
        /// Indicates static (global) memory.
        /// </summary>
        [EnumMember]
        Static,

        /// <summary>
        /// Indicates thread local stack memory.
        /// </summary>
        [EnumMember]
        LocalStack,
    }

    /// <summary>
    /// Represents a type of log item for a definition.
    /// </summary>
    [DataContract]
    public enum LogItemType
    {
        /// <summary>
        /// Indicates a default log item.
        /// </summary>
        [EnumMember]
        Default,

        /// <summary>
        /// Indicates a success log item.
        /// </summary>
        [EnumMember]
        Success,

        /// <summary>
        /// Indicates a warning log item.
        /// </summary>
        [EnumMember]
        Warning,

        /// <summary>
        /// Indicates an error log item.
        /// </summary>
        [EnumMember]
        Error
    }

    /// <summary>
    /// Represents a log item for a definition.
    /// </summary>
    [DataContract]
    public class LogItem
    {
        /// <summary>
        /// Gets or sets the type for the item.
        /// </summary>
        [DataMember]
        public LogItemType Type { get; set; }

        /// <summary>
        /// Gets or sets the text for item.
        /// </summary>
        [DataMember]
        public string Text { get; set; }
    }

    /// <summary>
    /// Represents information about the maximum sizes of messages within a data link definition.
    /// </summary>
    public class MaxMessageSizes
    {
        /// <summary>
        /// Represents the size, in bytes, of the largest message within the definition.
        /// </summary>
        public int MaxSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest message received by a device within the definition.
        /// </summary>
        public int MaxDeviceSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest message received by a device within the definition.
        /// </summary>
        public int MaxHostSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest request message within the definition.
        /// </summary>
        public int MaxRequestSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest response message within the definition.
        /// </summary>
        public int MaxResponseSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest unsolicited message within the definition.
        /// </summary>
        public int MaxUnsolicitedSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest unsolicited message received by a device within the definition.
        /// </summary>
        public int MaxUnsolicitedDeviceSize { get; set; }

        /// <summary>
        /// Represents the size, in bytes, of the largest unsolicited message received by a host within the definition.
        /// </summary>
        public int MaxUnsolicitedHostSize { get; set; }
    }
}
