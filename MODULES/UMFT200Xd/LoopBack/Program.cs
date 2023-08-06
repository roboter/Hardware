using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

using FTD2XX_NET;

namespace LoopBack
{
    class Program
    {
        static void Main(string[] args)
        {
            UInt32 ftdiDeviceCount = 0;
            FTDI.FT_STATUS ftStatus = FTDI.FT_STATUS.FT_OK;

            // Create new instance of the FTDI device class
            FTDI myFtdiDevice = new FTDI();
            
            // Determine the number of FTDI devices connected to the machine
            ftStatus = myFtdiDevice.GetNumberOfDevices(ref ftdiDeviceCount);
            // Check status
            if (ftStatus == FTDI.FT_STATUS.FT_OK)
            {
                Console.WriteLine("Number of FTDI devices: " + ftdiDeviceCount.ToString());
                Console.WriteLine("");
            }
            else
            {
                // Wait for a key press
                Console.WriteLine("Failed to get number of devices (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // If no devices available, return
            if (ftdiDeviceCount == 0)
            {
                // Wait for a key press
                Console.WriteLine("Failed to get number of devices (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Allocate storage for device info list
            FTDI.FT_DEVICE_INFO_NODE[] ftdiDeviceList = new FTDI.FT_DEVICE_INFO_NODE[ftdiDeviceCount];

            // Populate our device list
            ftStatus = myFtdiDevice.GetDeviceList(ftdiDeviceList);

            if (ftStatus == FTDI.FT_STATUS.FT_OK)
            {
                for (UInt32 i = 0; i < ftdiDeviceCount; i++)
                {
                    Console.WriteLine("Device Index: " + i.ToString());
                    Console.WriteLine("Flags: " + String.Format("{0:x}", ftdiDeviceList[i].Flags));
                    Console.WriteLine("Type: " + ftdiDeviceList[i].Type.ToString());
                    Console.WriteLine("ID: " + String.Format("{0:x}", ftdiDeviceList[i].ID));
                    Console.WriteLine("Location ID: " + String.Format("{0:x}", ftdiDeviceList[i].LocId));
                    Console.WriteLine("Serial Number: " + ftdiDeviceList[i].SerialNumber.ToString());
                    Console.WriteLine("Description: " + ftdiDeviceList[i].Description.ToString());
                    Console.WriteLine("");
                }
            }


            // Open first device in our list by serial number
            ftStatus = myFtdiDevice.OpenBySerialNumber(ftdiDeviceList[0].SerialNumber);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to open device (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Set up device data parameters
            // Set Baud rate to 9600
            ftStatus = myFtdiDevice.SetBaudRate(9600);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to set Baud rate (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Set data characteristics - Data bits, Stop bits, Parity
            ftStatus = myFtdiDevice.SetDataCharacteristics(FTDI.FT_DATA_BITS.FT_BITS_8, FTDI.FT_STOP_BITS.FT_STOP_BITS_1, FTDI.FT_PARITY.FT_PARITY_NONE);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to set data characteristics (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Set flow control - set RTS/CTS flow control
            ftStatus = myFtdiDevice.SetFlowControl(FTDI.FT_FLOW_CONTROL.FT_FLOW_RTS_CTS, 0x11, 0x13);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to set flow control (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Set read timeout to 5 seconds, write timeout to infinite
            ftStatus = myFtdiDevice.SetTimeouts(5000, 0);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to set timeouts (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }

            // Perform loop back - make sure loop back connector is fitted to the device
            // Write string data to the device
            string dataToWrite = "Hello world!";
            UInt32 numBytesWritten = 0;
            // Note that the Write method is overloaded, so can write string or byte array data
            ftStatus = myFtdiDevice.Write(dataToWrite, dataToWrite.Length, ref numBytesWritten);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to write to device (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }


            // Check the amount of data available to read
            // In this case we know how much data we are expecting, 
            // so wait until we have all of the bytes we have sent.
            UInt32 numBytesAvailable = 0;
            do
            {
                ftStatus = myFtdiDevice.GetRxBytesAvailable(ref numBytesAvailable);
                if (ftStatus != FTDI.FT_STATUS.FT_OK)
                {
                    // Wait for a key press
                    Console.WriteLine("Failed to get number of bytes available to read (error " + ftStatus.ToString() + ")");
                    Console.ReadKey();
                    return;
                }
                Thread.Sleep(10);
            } while (numBytesAvailable < dataToWrite.Length);

            // Now that we have the amount of data we want available, read it
            string readData;
            UInt32 numBytesRead = 0;
            // Note that the Read method is overloaded, so can read string or byte array data
            ftStatus = myFtdiDevice.Read(out readData, numBytesAvailable, ref numBytesRead);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                // Wait for a key press
                Console.WriteLine("Failed to read data (error " + ftStatus.ToString() + ")");
                Console.ReadKey();
                return;
            }
            Console.WriteLine(readData);

            // Close our device
            ftStatus = myFtdiDevice.Close();

            // Wait for a key press
            Console.WriteLine("Press any key to continue.");
            Console.ReadKey();
            return;
        }
    }
}
