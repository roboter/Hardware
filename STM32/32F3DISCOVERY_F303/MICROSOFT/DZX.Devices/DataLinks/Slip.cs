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
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace DZX.Devices.DataLinks
{
    /// <summary>
    /// Provides methods for encapsulating data using the Serial Line Internet Protocol (SLIP) protocol.
    /// </summary>
    public static class SLIP
    {
        /// <summary>
        /// Represents the END character.
        /// </summary>
        public const byte END = 0xC0;

        /// <summary>
        /// Represents the ESC (escape) character.
        /// </summary>
        public const byte ESC = 0xDB;

        /// <summary>
        /// Represents the escaped END character.
        /// </summary>
        public const byte ESCEND = 0xDC;

        /// <summary>
        /// Represents the escaped ESC (escape) character.
        /// </summary>
        public const byte ESCESC = 0xDD;

        /// <summary>
        /// Encodes the specified data using the SLIP protocol.
        /// </summary>
        /// <param name="data">The data to be encapsulated.</param>
        /// <returns>The encoded data.</returns>
        public static byte[] Encode(byte[] data)
        {
            using (MemoryStream stream = new MemoryStream())
            {
                for (int k = 0; k < data.Length; k++)
                {
                    switch (data[k])
                    {
                        case ESC:
                            stream.WriteByte(ESC);
                            stream.WriteByte(ESCESC);
                            break;
                        case END:
                            stream.WriteByte(ESC);
                            stream.WriteByte(ESCEND);
                            break;
                        default:
                            stream.WriteByte(data[k]);
                            break;
                    }
                }

                stream.WriteByte(END);
                return stream.ToArray();
            }
        }

        /// <summary>
        /// Provides methods for decoding Serial Line Internet Protocol (SLIP) encapsulated data.
        /// </summary>
        public class Decoder
        {
            /// <summary>
            /// An indication of whether the previously decoded byte was an escape character.
            /// </summary>
            private bool _escaped = false;

            /// <summary>
            /// An underlying stream used for temporarily holding the decoded data.
            /// </summary>
            private MemoryStream _decoded = new MemoryStream();

            /// <summary>
            /// An underlying stream used for temporarily holding the raw data.
            /// </summary>
            private MemoryStream _raw = new MemoryStream();

            /// <summary>
            /// Occurs when encapsulated data has been decoded.
            /// </summary>
            public event EventHandler<DataEventArgs> DataDecoded;

            /// <summary>
            /// Occurs when an invalid escape character has been decoded.
            /// </summary>
            public event EventHandler<DataEventArgs> InvalidEscapeCharacter;

            /// <summary>
            /// Raises the <see cref="E:DataDecoded" /> event.
            /// </summary>
            /// <param name="e">The <see cref="DataEventArgs"/> instance containing the event data.</param>
            protected virtual void OnDataDecoded(DataEventArgs e)
            {
                EventHandler<DataEventArgs> handler = DataDecoded;
                if (handler == null)
                    return;

                handler(this, e);
            }

            /// <summary>
            /// Raises the <see cref="E:InvalidEscapeCharacter" /> event.
            /// </summary>
            /// <param name="e">The <see cref="DataEventArgs"/> instance containing the event data.</param>
            protected virtual void OnInvalidEscapeCharacter(DataEventArgs e)
            {
                EventHandler<DataEventArgs> handler = InvalidEscapeCharacter;
                if (handler == null)
                    return;

                handler(this, e);
            }

            /// <summary>
            /// Decodes the specified data. The <see cref="E:DataDecoded" /> event will be raised upon completion
            /// of encapsulated data.
            /// </summary>
            /// <param name="data">The data to be decoded.</param>
            public void Decode(byte[] data)
            {
                for (int k = 0; k < data.Length; k++)
                {
                    _raw.WriteByte(data[k]);

                    // Determine current escape state
                    if (_escaped)
                    {
                        // Previously received an ESC character
                        // Should only receive an ESCESC or ESCEND character at this location

                        switch (data[k])
                        {
                            case ESCESC:
                                _decoded.WriteByte(ESC);
                                break;
                            case ESCEND:
                                _decoded.WriteByte(END);
                                break;

                            default:
                                // Received an invalid escaped character
                                OnInvalidEscapeCharacter(new DataEventArgs(_raw.ToArray(), _decoded.ToArray()));
                                break;
                        }

                        _escaped = false;
                    }
                    else
                    {
                        // No previous escape character, decode as normal

                        switch (data[k])
                        {
                            case ESC:
                                // Escape, wait for next character
                                _escaped = true;
                                break;

                            case END:
                                // Decode complete
                                OnDataDecoded(new DataEventArgs(_raw.ToArray(), _decoded.ToArray()));

                                // Reset
                                _raw.SetLength(0);
                                _decoded.SetLength(0);
                                break;

                            default:
                                // Normal value that didn't require being escaped
                                _decoded.WriteByte(data[k]);
                                break;
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Represents the arguments for a SLIP event.
        /// </summary>
        public class DataEventArgs : EventArgs
        {
            /// <summary>
            /// Gets the raw data for the event.
            /// </summary>
            public byte[] RawData { get; private set; }

            /// <summary>
            /// Gets the data for the event.
            /// </summary>
            public byte[] Data { get; private set; }

            /// <summary>
            /// Initializes a new instance of the <see cref="DataEventArgs"/> class.
            /// </summary>
            /// <param name="raw">The raw data for the event.</param>
            /// <param name="data">The data for the event.</param>
            public DataEventArgs(byte[] raw, byte[] data)
            {
                RawData = raw;
                Data = data;
            }
        }
    }
}
