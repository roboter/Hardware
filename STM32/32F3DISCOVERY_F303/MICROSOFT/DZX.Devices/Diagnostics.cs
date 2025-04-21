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

namespace DZX.Devices
{
    /// <summary>
    /// Provides diagnostic information for devices.
    /// </summary>
    public static class Diagnostics
    {
        /// <summary>
        /// An underlying stopwatch for measuring timestamps.
        /// </summary>
        private static System.Diagnostics.Stopwatch _watch;

        /// <summary>
        /// Initializes the <see cref="Diagnostics"/> class.
        /// </summary>
        static Diagnostics()
        {
            _watch = new System.Diagnostics.Stopwatch();
            _watch.Start();
        }

        /// <summary>
        /// Gets a current timestamp, in ticks.
        /// </summary>
        /// <remarks>The frequency of ticks is defined by <see cref="System.Diagnostics.Stopwatch.Frequency" />.</remarks>
        public static long Timestamp
        {
            get { return _watch.ElapsedTicks; }
        }

        /// <summary>
        /// Gets a current timestamp in a <see cref="System.TimeSpan"/> unit.
        /// </summary>
        public static TimeSpan TimestampSpan
        {
            get { return TimeSpan.FromTicks((TimeSpan.TicksPerSecond * _watch.ElapsedTicks) / System.Diagnostics.Stopwatch.Frequency); }
        }
    }
}
