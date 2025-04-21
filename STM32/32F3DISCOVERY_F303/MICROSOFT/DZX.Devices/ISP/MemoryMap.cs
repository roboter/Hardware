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
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace DZX.Devices.ISP
{
    /// <summary>
    /// Represents a device memory map.
    /// </summary>
    [DataContract]
    public class MemoryMap
    {
        /// <summary>
        /// Represents an invalid sector number.
        /// </summary>
        public const uint InvalidSectorNumber = 0xFFFFFFFF;

        /// <summary>
        /// Represents an invalid bank number.
        /// </summary>
        public const uint InvalidBankNumber = 0xFFFFFFFF;

        /// <summary>
        /// Gets the total size, in bytes, of all the sections contained within this memory map.
        /// </summary>
        public uint Size { get { return (uint)Sections.Sum(s => s.Size); } }

        /// <summary>
        /// Gets the total number of sectors contained within this memory map.
        /// </summary>
        public int SectorCount { get { return (int)Sections.Sum(s => s.SectorCount); } }

        /// <summary>
        /// Gets or sets the sections contained within this memory map.
        /// </summary>
        [DataMember(Name = "Sections")]
        public BindingList<MemoryMapSection> Sections { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryMap"/> class.
        /// </summary>
        public MemoryMap()
        {
            Sections = new BindingList<MemoryMapSection>();
        }

        /// <summary>
        /// Gets the bank number of the specified address.
        /// </summary>
        /// <param name="address">The target address.</param>
        /// <returns>The number of the memory bank that contains the given address.</returns>
        public uint GetBankNumber(uint address)
        {
            MemoryMapSection section = Sections.FirstOrDefault(s => s.Contains(address));
            if (section == null)
                return MemoryMap.InvalidBankNumber;

            return section.Bank.GetValueOrDefault(0);
        }

        /// <summary>
        /// Gets the number of the sector that contains the specified address.
        /// </summary>
        /// <param name="address">The target address.</param>
        /// <returns>The number of the sector that contains the specified address.</returns>
        public uint GetSectorNumber(uint address)
        {
            MemoryMapSection section = Sections.FirstOrDefault(s => s.Contains(address));
            if (section == null)
                return MemoryMap.InvalidSectorNumber;

            if (section.SectorSize == 0)
                return MemoryMap.InvalidSectorNumber;

            return ((address - section.Address) / section.SectorSize) + section.SectorNumber;
        }
    }

    /// <summary>
    /// Represents a section of sectors within a memory map.
    /// </summary>
    [DataContract]
    public class MemoryMapSection
    {
        /// <summary>
        /// Gets or sets the bank number for the section.
        /// </summary>
        [DataMember]
        public Nullable<uint> Bank { get; set; }

        /// <summary>
        /// Gets or sets the starting address for the section.
        /// </summary>
        [DataMember]
        public uint Address { get; set; }

        /// <summary>
        /// Gets or sets the starting sector number for the section.
        /// </summary>
        [DataMember]
        public uint SectorNumber { get; set; }

        /// <summary>
        /// Gets or sets the size, in bytes, for each sector in this section.
        /// </summary>
        [DataMember]
        public uint SectorSize { get; set; }

        /// <summary>
        /// Gets or sets the number of sectors within this section.
        /// </summary>
        [DataMember]
        public uint SectorCount { get; set; }

        /// <summary>
        /// Gets the last address contained by this section.
        /// </summary>
        public uint EndAddress { get { return (Address + (SectorCount * SectorSize) - 1); } }

        /// <summary>
        /// Gets the total size, in bytes, of all the sectors contained within this section.
        /// </summary>
        public uint Size { get { return SectorSize * SectorCount; } }

        /// <summary>
        /// Determines whether the specified address is contained within this section.
        /// </summary>
        /// <param name="address">The target address.</param>
        /// <returns><c>true</c> if the given address is contained within the section; otherwise <c>false</c>.</returns>
        public bool Contains(uint address)
        {
            return (address >= Address && address <= EndAddress);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryMapSection"/> class.
        /// </summary>
        public MemoryMapSection()
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryMapSection"/> class with the
        /// specified parameters.
        /// </summary>
        /// <param name="address">The starting address for the section.</param>
        /// <param name="sectorNumber">The starting sector number for the section.</param>
        /// <param name="sectorSize">The size, in bytes, of each sector within the section.</param>
        /// <param name="sectorCount">The number of sectors within the section.</param>
        public MemoryMapSection(uint address, uint sectorNumber, uint sectorSize, uint sectorCount)
            : this()
        {
            this.Address = address;
            this.SectorNumber = sectorNumber;
            this.SectorSize = sectorSize;
            this.SectorCount = sectorCount;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryMapSection"/> class with the
        /// specified parameters.
        /// </summary>
        /// <param name="bank">The bank number for the section.</param>
        /// <param name="address">The starting address for the section.</param>
        /// <param name="sectorNumber">The starting sector number for the section.</param>
        /// <param name="sectorSize">The size, in bytes, of each sector within the section.</param>
        /// <param name="sectorCount">The number of sectors within the section.</param>
        public MemoryMapSection(uint bank, uint address, uint sectorNumber, uint sectorSize, uint sectorCount)
            : this(address, sectorNumber, sectorSize, sectorCount)
        {
            this.Bank = bank;
        }

        /// <summary>
        /// Returns a <see cref="System.String" /> that represents this instance.
        /// </summary>
        public override string ToString()
        {
            return string.Format("0x{0:X8} - {1}x{2}", Address, SectorSize, SectorCount);
        }
    }
}
