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
    internal static class LPC15xx
    {
        public static void ConfigureTarget(ISPTarget target)
        {
            target.RAMBufferAddress = 0x02000300;
            target.RAMBufferSize = 4096;
            target.MaxReadLength = 4096;
            target.UUEncode = false;
            target.EchoByDefault = false;

            switch (target.DeviceType)
            {
                case ISPDeviceType.LPC1517:
                case ISPDeviceType.LPC1547:
                    // 64 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x1000, 16));
                    break;

                case ISPDeviceType.LPC1518:
                case ISPDeviceType.LPC1548:
                    // 128 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x1000, 32));
                    break;

                case ISPDeviceType.LPC1519:
                case ISPDeviceType.LPC1549:
                    // 256 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x1000, 64));
                    break;
            }
        }
    }
}
