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
using System.Runtime.Serialization;
using System.Xml;
using System.ComponentModel;

namespace DZX.Devices.ISP
{
    /// <summary>
    /// Represents a family of target ISP devices.
    /// </summary>
    public enum ISPDeviceFamily
    {
        /// <summary>
        /// Represents the NXP LPC8xx familiy of devices.
        /// </summary>
        LPC8xx,

        /// <summary>
        /// Represents the NXP LPC15xx family of devices.
        /// </summary>
        LPC15xx,

        /// <summary>
        /// Represents the NXP LPC175x6x family of devices.
        /// </summary>
        LPC175x6x,

        /// <summary>
        /// Represents the NXP LPC177x8x family of devices.
        /// </summary>
        LPC177x8x,

        /// <summary>
        /// Represents the NXP LPC18xx family of devices.
        /// </summary>
        LPC18xx,
    }

    /// <summary>
    /// Represents an entry within a lookup table to automatically determine additional information about an
    /// ISP device.
    /// </summary>
    internal class ISPLookupEntry
    {
        public ISPDeviceFamily Family;
        public ISPDeviceType DeviceType;
        public uint ID;
        public uint Mask;
        public Nullable<uint> ID2;
        
        public ISPLookupEntry()
        {

        }

        public ISPLookupEntry(uint id, ISPDeviceType deviceType, ISPDeviceFamily family)
            : this(id, null, deviceType, family)
        {

        }

        public ISPLookupEntry(uint id, Nullable<uint> id2, ISPDeviceType deviceType, ISPDeviceFamily family)
            : this()
        {
            this.ID = id;
            this.ID2 = id2;
            this.Mask = 0xFFFFFFFF;
            this.DeviceType = deviceType;
            this.Family = family;
        }

        public ISPLookupEntry(uint id, Nullable<uint> id2, uint mask, ISPDeviceType deviceType, ISPDeviceFamily family)
            : this()
        {
            this.ID = id;
            this.ID2 = id2;
            this.Mask = mask;
            this.DeviceType = deviceType;
            this.Family = family;
        }
    }

    /// <summary>
    /// Represents information that describes a target device that supports the In-System Programming (ISP)
    /// interface.
    /// </summary>
    [DataContract]
    public class ISPTarget
    {
        /// <summary>
        /// A lookup table for determining the device type from a part identifier received from a target device.
        /// </summary>
        internal static readonly ISPLookupEntry[] LookupTable = new ISPLookupEntry[]
        {
            // LPC8xx parts
            new ISPLookupEntry(0x8021, ISPDeviceType.LPC802, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8022, ISPDeviceType.LPC802, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8023, ISPDeviceType.LPC802, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8024, ISPDeviceType.LPC802, ISPDeviceFamily.LPC8xx),

            new ISPLookupEntry(0x8100, ISPDeviceType.LPC810, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8110, ISPDeviceType.LPC811, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8120, ISPDeviceType.LPC812, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8121, ISPDeviceType.LPC812, ISPDeviceFamily.LPC8xx),
            new ISPLookupEntry(0x8122, ISPDeviceType.LPC812, ISPDeviceFamily.LPC8xx),


            // LPC8xx parts
            new ISPLookupEntry(0x1517, ISPDeviceType.LPC1517, ISPDeviceFamily.LPC15xx),
            new ISPLookupEntry(0x1518, ISPDeviceType.LPC1518, ISPDeviceFamily.LPC15xx),
            new ISPLookupEntry(0x1519, ISPDeviceType.LPC1519, ISPDeviceFamily.LPC15xx),
            new ISPLookupEntry(0x1547, ISPDeviceType.LPC1547, ISPDeviceFamily.LPC15xx),
            new ISPLookupEntry(0x1548, ISPDeviceType.LPC1548, ISPDeviceFamily.LPC15xx),
            new ISPLookupEntry(0x1549, ISPDeviceType.LPC1549, ISPDeviceFamily.LPC15xx),
     

            // LPC175x6x parts
            new ISPLookupEntry(0x26113F37, ISPDeviceType.LPC1769, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26013F37, ISPDeviceType.LPC1768, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26012837, ISPDeviceType.LPC1767, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26013F33, ISPDeviceType.LPC1766, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26013733, ISPDeviceType.LPC1765, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26011922, ISPDeviceType.LPC1764, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x26012033, ISPDeviceType.LPC1763, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25113737, ISPDeviceType.LPC1759, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25013F37, ISPDeviceType.LPC1758, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25011723, ISPDeviceType.LPC1756, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25011722, ISPDeviceType.LPC1754, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25001121, ISPDeviceType.LPC1752, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25001118, ISPDeviceType.LPC1751, ISPDeviceFamily.LPC175x6x),
            new ISPLookupEntry(0x25001110, ISPDeviceType.LPC1751_NOCRP, ISPDeviceFamily.LPC175x6x),

            // LPC177x8x parts
            new ISPLookupEntry(0x281D3F47, ISPDeviceType.LPC1788, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x281D3747, ISPDeviceType.LPC1787, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x281D1F43, ISPDeviceType.LPC1786, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x281D1743, ISPDeviceType.LPC1785, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x27193F47, ISPDeviceType.LPC1778, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x27193747, ISPDeviceType.LPC1777, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x27191F43, ISPDeviceType.LPC1776, ISPDeviceFamily.LPC177x8x),
            new ISPLookupEntry(0x27011132, ISPDeviceType.LPC1774, ISPDeviceFamily.LPC177x8x),

            // LPC18xx flashless parts
            new ISPLookupEntry(0xF000D830, 0x00, 0xFF, ISPDeviceType.LPC1850, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF000DA30, 0x00, 0xFF, ISPDeviceType.LPC1830, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00ADB3C, 0x00, 0xFF, ISPDeviceType.LPC1820, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00B5B3F, 0x00, 0xFF, ISPDeviceType.LPC1810, ISPDeviceFamily.LPC18xx),

            // LPC18xx flash parts
            new ISPLookupEntry(0xF001D830, 0x00, 0xFF, ISPDeviceType.LPC1857, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001D830, 0x44, 0xFF, ISPDeviceType.LPC1853, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DA30, 0x00, 0xFF, ISPDeviceType.LPC1837, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DA30, 0x44, 0xFF, ISPDeviceType.LPC1833, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DB3C, 0x00, 0xFF, ISPDeviceType.LPC1827, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DB3C, 0x22, 0xFF, ISPDeviceType.LPC1825, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00BDB3C, 0x44, 0xFF, ISPDeviceType.LPC1823, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00BDB3C, 0x80, 0xFF, ISPDeviceType.LPC1822, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DB3F, 0x00, 0xFF, ISPDeviceType.LPC1817, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF001DB3F, 0x22, 0xFF, ISPDeviceType.LPC1815, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00BDB3F, 0x44, 0xFF, ISPDeviceType.LPC1813, ISPDeviceFamily.LPC18xx),
            new ISPLookupEntry(0xF00BDB3F, 0x80, 0xFF, ISPDeviceType.LPC1812, ISPDeviceFamily.LPC18xx),
        };

        /// <summary>
        /// Gets or sets the type of the device for this target.
        /// </summary>
        [DataMember]
        public ISPDeviceType DeviceType { get; set; }

        /// <summary>
        /// Gets or sets the address of the buffer used within RAM memory.
        /// </summary>
        [DataMember]
        public uint RAMBufferAddress { get; set; }

        /// <summary>
        /// Gets or sets the size, in bytes, of the buffer used within RAM memory.
        /// </summary>
        [DataMember]
        public uint RAMBufferSize { get; set; }

        /// <summary>
        /// Gets or sets whether the program data should be UU encoded.
        /// </summary>
        [DataMember]
        public bool UUEncode { get; set; }

        /// <summary>
        /// Gets or sets whether the target will initially echo transfers.
        /// </summary>
        [DataMember]
        public bool EchoByDefault { get; set; }

        /// <summary>
        /// Gets or sets the maximum number of bytes to read per command from the device.
        /// </summary>
        /// <remarks>Only in effect when UUEncode is <c>false</c>.</remarks>
        [DataMember]
        public int MaxReadLength { get; set; }

        /// <summary>
        /// Provides access to the memory map for this target.
        /// </summary>
        [DataMember]
        public MemoryMap MemoryMap { get; set; }

        /// <summary>
        /// Creates and initializes a target from the specified file path.
        /// </summary>
        /// <param name="path">The file path used to initialize the target.</param>
        /// <returns>An initialized target.</returns>
        public static ISPTarget FromFile(string path)
        {
            using (FileStream stream = new FileStream(path, FileMode.Open))
            {
                return FromStream(stream);
            }
        }

        /// <summary>
        /// Creates and initializes a target from the specified stream.
        /// </summary>
        /// <param name="stream">The stream used to initialize the target.</param>
        /// <returns>An initialized target.</returns>
        public static ISPTarget FromStream(Stream stream)
        {
            DataContractSerializer serializer = new DataContractSerializer(typeof(ISPTarget));
            return serializer.ReadObject(stream) as ISPTarget;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ISPTarget"/> class.
        /// </summary>
        public ISPTarget()
        {
            MemoryMap = new MemoryMap();
        }

        /// <summary>
        /// Saves this target to the specified file path.
        /// </summary>
        /// <param name="path">The target file path.</param>
        public void Save(string path)
        {
            using (FileStream stream = new FileStream(path, FileMode.Create))
            {
                Save(stream);
            }
        }

        /// <summary>
        /// Saves this target to the specified stream.
        /// </summary>
        /// <param name="stream">The target stream.</param>
        public void Save(Stream stream)
        {

            DataContractSerializer serializer = new DataContractSerializer(typeof(ISPTarget));

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            using (System.Xml.XmlWriter writer = System.Xml.XmlWriter.Create(stream, settings))
            {
                serializer.WriteObject(writer, this);
            }
        }

        /// <summary>
        /// Determines whether a device with the specified Part ID contains a secondary
        /// identifier.
        /// </summary>
        /// <param name="id">The device's part identifier value.</param>
        /// <returns><c>true</c> if the device has a secondary identifier; otherwise <c>false</c>.</returns>
        public static bool HasSecondaryIdentifier(uint id)
        {
            ISPLookupEntry entry = LookupTable.FirstOrDefault(t => t.ID == id);
            if (entry == null)
                return false;

            return entry.ID2.HasValue;
        }

        /// <summary>
        /// Finds and returns the <see cref="ISPDeviceType"/> for the specified Part ID value.
        /// </summary>
        /// <param name="id">The part identifier value.</param>
        /// <returns>The <see cref="ISPDeviceType"/> represented by the given part identifier value.</returns>
        public static ISPDeviceType FindDeviceType(uint id)
        {
            ISPLookupEntry entry = LookupTable.FirstOrDefault(t => t.ID == id);
            if (entry == null)
                return ISPDeviceType.Unknown;

            // Only return the type if it doesn't require an additional identifier
            if (entry.ID2.HasValue)
                return ISPDeviceType.Unknown;

            return entry.DeviceType;
        }

        /// <summary>
        /// Finds and returns the <see cref="ISPDeviceType"/> for the specified Part ID values.
        /// </summary>
        /// <param name="id">The part identifier value.</param>
        /// <param name="id2">The secondary part identifier value.</param>
        /// <returns>The <see cref="ISPDeviceType"/> represented by the given part identifier values.</returns>
        public static ISPDeviceType FindDeviceType(uint id, uint id2)
        {
            ISPLookupEntry entry = LookupTable.FirstOrDefault(t => t.ID == id && (t.ID2 & t.Mask) == id2);
            if (entry == null)
                return ISPDeviceType.Unknown;

            return entry.DeviceType;
        }

        /// <summary>
        /// Creates and initializes a <see cref="ISPTarget"/> for the specified type of device.
        /// </summary>
        /// <param name="type">The target device type.</param>
        /// <returns></returns>
        public static ISPTarget FromDeviceType(ISPDeviceType type)
        {
            ISPTarget target = new ISPTarget();

            target.DeviceType = type;

            ISPLookupEntry entry = LookupTable.FirstOrDefault(t => t.DeviceType == type);
            if (entry == null)
                return target;

            switch (entry.Family)
            {
                case ISPDeviceFamily.LPC8xx:
                    LPC8xx.ConfigureTarget(target);
                    break;
                case ISPDeviceFamily.LPC15xx:
                    LPC15xx.ConfigureTarget(target);
                    break;
                case ISPDeviceFamily.LPC175x6x:
                    LPC175x6x.ConfigureTarget(target);
                    break;
                case ISPDeviceFamily.LPC177x8x:
                    LPC17x8x.ConfigureTarget(target);
                    break;
                case ISPDeviceFamily.LPC18xx:
                    LPC18xx.ConfigureTarget(target);
                    break;
            }

            return target;
        }
    }

    /// <summary>
    /// Represents the supported device types.
    /// </summary>
    public enum ISPDeviceType : uint
    {
        Unknown = 0,

        LPC802,
        LPC810,
        LPC811,
        LPC812,

        LPC1517,
        LPC1518,
        LPC1519,
        LPC1547,
        LPC1548,
        LPC1549,

        [Description("LPC1751 (no CRP)")]
        LPC1751_NOCRP,
        LPC1751,
        LPC1752,
        LPC1754,
        LPC1756,
        LPC1758,
        LPC1759,
        LPC1763,
        LPC1764,
        LPC1765,
        LPC1766,
        LPC1767,
        LPC1768,
        LPC1769,

        LPC1774,
        LPC1776,
        LPC1777,
        LPC1778,
        LPC1785,
        LPC1786,
        LPC1787,
        LPC1788,

        LPC1810,
        LPC1820,
        LPC1830,
        LPC1850,

        LPC1812,
        LPC1813,
        LPC1815,
        LPC1817,
        LPC1822,
        LPC1823,
        LPC1825,
        LPC1827,
        LPC1833,
        LPC1837,
        LPC1853,
        LPC1857,
    }
}
