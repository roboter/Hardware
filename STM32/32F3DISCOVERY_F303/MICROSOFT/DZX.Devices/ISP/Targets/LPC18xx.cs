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

namespace DZX.Devices.ISP
{
    internal static class LPC18xx
    {
        public static void ConfigureTarget(ISPTarget target)
        {
            target.RAMBufferAddress = 0x10000000;
            target.RAMBufferSize = 4096;
            target.UUEncode = true;
            target.EchoByDefault = false;

            switch (target.DeviceType)
            {
                case ISPDeviceType.LPC1812:
                case ISPDeviceType.LPC1822:
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A010000, 8, 0x10000, 7));
                    break;

                case ISPDeviceType.LPC1813:
                case ISPDeviceType.LPC1823:
                case ISPDeviceType.LPC1833:
                case ISPDeviceType.LPC1853:
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A010000, 8, 0x10000, 3));

                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B010000, 8, 0x10000, 3));
                    break;

                case ISPDeviceType.LPC1815:
                case ISPDeviceType.LPC1825:
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A010000, 8, 0x10000, 5));

                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B010000, 8, 0x10000, 5));
                    break;

                case ISPDeviceType.LPC1837:
                case ISPDeviceType.LPC1857:
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0, 0x1A010000, 8, 0x10000, 7));

                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B000000, 0, 0x2000, 8));
                    target.MemoryMap.Sections.Add(new MemoryMapSection(1, 0x1B010000, 8, 0x10000, 7));
                    break;
            }
        }
    }
}
