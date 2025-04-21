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
using System.Text;


namespace DZX.Devices.DataLinks
{
	#region Custom Enumerations

	#endregion

	#region Custom Structures

	#endregion

	#region Unsolicited Send Objects

	/// <summary>
	/// Parameters for message 'Enable Status Stream'.
	/// </summary>
	public class EnableStatusStreamArgs
	{
		/// <summary>
		/// The enable/disable state for the status stream.
		/// </summary>
		public bool Enabled;
	}

	#endregion

	#region Request/Response Objects

	/// <summary>
	/// Request parameters for message 'Read Memory'.
	/// </summary>
	public class ReadMemoryRequest
	{
		/// <summary>
		/// The starting address to be read.
		/// </summary>
		public uint Address;

		/// <summary>
		/// The number of data bytes to be read and returned.
		/// </summary>
		public uint Length;
	}

	/// <summary>
	/// Response parameters for message 'Read Memory'.
	/// </summary>
	public class ReadMemoryResponse
	{
		/// <summary>
		/// The memory data values.
		/// </summary>
		[DataLinkArray(MaxLength=256)]
		public byte[] Data;

		/// <summary>
		/// A result code for the operation.
		/// </summary>
		public uint Result;
	}

	/// <summary>
	/// Request parameters for message 'Write Memory'.
	/// </summary>
	public class WriteMemoryRequest
	{
		/// <summary>
		/// The starting address to be written.
		/// </summary>
		public uint Address;

		/// <summary>
		/// The data values to be written to memory.
		/// </summary>
		[DataLinkArray(MaxLength=256)]
		public byte[] Data;
	}

	/// <summary>
	/// Response parameters for message 'Write Memory'.
	/// </summary>
	public class WriteMemoryResponse
	{
		/// <summary>
		/// A result response code.
		/// </summary>
		public uint Result;
	}

	#endregion

	#region Unsolicited Receive Event Objects

	/// <summary>
	/// EventArgs parameters for message 'Device Status'.
	/// </summary>
	public class DeviceStatusEventArgs : EventArgs
	{
		/// <summary>
		/// Definition for the 'Kernel Utilization' parameter.
		/// </summary>
		public uint KernelUtilization;

		/// <summary>
		/// Definition for the 'Kernel Ticks' parameter.
		/// </summary>
		public uint KernelTicks;
	}


	#endregion

	/// <summary>
	/// Implements the custom 'App' data link.
	/// </summary>
	public class DataLinkApp : BaseDataLink
	{
		#region Message Identifiers

		private readonly uint EnableStatusStreamID = 1;
		private readonly uint ReadMemoryID = 2;
		private readonly uint WriteMemoryID = 3;
		private readonly uint DeviceStatusID = 4;

		#endregion

		#region Unsolicited Receive Events

		/// <summary>
		/// Occurs when the 'DeviceStatus' message has been received.
		/// </summary>
		public event EventHandler<DeviceStatusEventArgs> DeviceStatusReceived;

		#endregion

		/// <summary>
		/// Initializes a new instance of the <see cref="DataLinkApp"/> class.
		/// </summary>
		public DataLinkApp()
		{
			Version = 1;
			UseCRC = false;
		}

		#region Unsolicited Send Methods

		/// <summary>
		/// Sends the 'EnableStatusStream' message.
		/// </summary>
		/// <param name="args">Arguments for the message.</param>
		public void EnableStatusStream(EnableStatusStreamArgs args)
		{
			// Create and send the message
			Write(Serialize(EnableStatusStreamID, args));
		}

		#endregion

		#region Request/Response Methods

		/// <summary>
		/// Sends the 'Read Memory' request message and receives and returns the response from the device.
		/// </summary>
		/// <param name="request">The request parameters.</param>
		/// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a response from the device.</param>
		/// <returns>The response as received from the device. Null if no response was received.</returns>
		public ReadMemoryResponse ReadMemory(ReadMemoryRequest request, int timeout)
		{
			// Create a request message
			DataLinkMessage message = Serialize(ReadMemoryID, request);

			// Send the request and wait for a response
			DataLinkMessage response = Request(message, timeout);
			if (response == null)
			{
				return null;
			}

			return Deserialize<ReadMemoryResponse>(response.Data);
		}

		/// <summary>
		/// Sends the 'Write Memory' request message and receives and returns the response from the device.
		/// </summary>
		/// <param name="request">The request parameters.</param>
		/// <param name="timeout">The maximum amount of time, in milliseconds, to wait for a response from the device.</param>
		/// <returns>The response as received from the device. Null if no response was received.</returns>
		public WriteMemoryResponse WriteMemory(WriteMemoryRequest request, int timeout)
		{
			// Create a request message
			DataLinkMessage message = Serialize(WriteMemoryID, request);

			// Send the request and wait for a response
			DataLinkMessage response = Request(message, timeout);
			if (response == null)
			{
				return null;
			}

			return Deserialize<WriteMemoryResponse>(response.Data);
		}

		#endregion

		#region Unsolicited Receive Event Handlers

		/// <summary>
		/// Raises the <see cref="E:DeviceStatusReceived" /> event.
		/// </summary>
		/// <param name="e">The event arguments.</param>
		protected virtual void OnDeviceStatusReceived(DeviceStatusEventArgs e)
		{
			OnEvent<DeviceStatusEventArgs>(DeviceStatusReceived, e);
		}

		#endregion


		/// <summary>
		/// Raises the <see cref="E:MessageReceived" /> event.
		/// </summary>
		/// <param name="e">The event arguments.</param>
		protected override void OnMessageReceived(DataLinkMessageEventArgs e)
		{
			// Call specific receive events based upon message identifier
			switch (e.Message.ID & 0x0000FFFF)
			{
				case 4:
					OnDeviceStatusReceived(Deserialize<DeviceStatusEventArgs>(e.Message.Data));
					break;

			}

			// Provide global message received event
			base.OnMessageReceived(e);
		}

	}
}
