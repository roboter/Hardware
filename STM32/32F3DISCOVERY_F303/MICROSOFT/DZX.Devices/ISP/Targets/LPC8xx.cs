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
    internal static class LPC8xx
    {
        public static void ConfigureTarget(ISPTarget target)
        {
            target.RAMBufferAddress = 0x10000300;
            target.RAMBufferSize = 1024;
            target.MaxReadLength = 1024;
            target.UUEncode = false;
            target.EchoByDefault = false;

            switch (target.DeviceType)
            {
                case ISPDeviceType.LPC810:
                    // 4 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x400, 4));
                    break;

                case ISPDeviceType.LPC811:
                    // 8 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x400, 8));
                    break;

                case ISPDeviceType.LPC802:
                case ISPDeviceType.LPC812:
                    // 16 KB parts
                    target.MemoryMap.Sections.Add(new MemoryMapSection(0x00000000, 0, 0x400, 16));
                    break;
            }
        }
    }
}
