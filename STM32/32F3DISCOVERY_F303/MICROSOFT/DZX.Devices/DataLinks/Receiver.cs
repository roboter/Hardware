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
using System.Threading;
using System.Threading.Tasks;

namespace DZX.Devices.DataLinks
{
    /// <summary>
    /// Provides methods for receiving particular messages from a hardware device.
    /// </summary>
    internal sealed class Receiver
    {
        /// <summary>
        /// Provides the mechanism for signaling the blocked calling thread when the
        /// appropriate message is received.
        /// </summary>
        private ManualResetEvent resetEvent;

        /// <summary>
        /// The message identifier the receiver is waiting to receive.
        /// </summary>
        private uint id;

        /// <summary>
        /// The mask used to target specific bits of the id field.
        /// </summary>
        private uint mask;

        /// <summary>
        /// The message that has been received and captured by this receiver.
        /// </summary>
        private DataLinkMessage message;

        /// <summary>
        /// Initializes a new instance of the <see cref="Receiver"/> class for the
        /// specified message identifier.
        /// </summary>
        /// <param name="mask">A mask of the bits to be checked within the identifier field.</param>
        /// <param name="id">The message identifier the receiver will wait for to be received.</param>
        public Receiver(uint mask, uint id)
        {
            // Init the underlying event
            resetEvent = new ManualResetEvent(false);

            // Capture the IDs to listen for
            this.mask = mask;
            this.id = id;
        }

        /// <summary>
        /// Resets the receiver so that it can allow another Wait call and 
        /// block the caller.
        /// </summary>
        public void Reset()
        {
            resetEvent.Reset();
        }

        /// <summary>
        /// Blocks until a message with the specified ID is received or until the specified
        /// timeout interval elapses.
        /// </summary>
        /// <param name="timeout">The maximum amount of time in milliseconds to wait for the message to be received.</param>
        /// <returns>The message that was received upon success; otherwise default.</returns>
        public DataLinkMessage Wait(int timeout)
        {
            if (resetEvent.WaitOne(timeout))
            {
                // Didn't timeout, return the captured message
                return message;
            }

            // Timed out...
            return null;
        }

        /// <summary>
        /// Processes the specified message by checking if the message
        /// should be captured.
        /// </summary>
        /// <param name="message">The message for the receiver to process.</param>
        public void Process(DataLinkMessage message)
        {
            // Check if the message matches the identifier of interest
            if (((this.mask & this.id) ^ message.ID) == 0)
            {
                // Capture the message
                this.message = message;

                // Signal any waiting thread
                resetEvent.Set();
            }
        }
    }
}
