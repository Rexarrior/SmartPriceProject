using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace IoTServer
{
    class Program
    {
        static void Send(Socket socket, byte[] data)
        {
            byte[] signal = new byte[1];
            socket.Send(data);
            socket.Receive(signal);
        }

        static void Receive(Socket socket, byte[] buffer)
        {
            byte[] signal = new byte[1];
            socket.Receive(buffer);
            socket.Send(signal);
        }

        static void Main(string[] args)
        {
            ImagesServer server = new ImagesServer();

            server.Start(3033);

            
            Thread.Sleep(100);

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect(IPAddress.Parse("127.0.0.1"), 3033);

            byte[] data = new byte[1];
            data[0] = 1;
            Send(socket, data);

            for (int i = 0; i < 212; i++)
            {
                byte[] buffer = new byte[13];
                Receive(socket, buffer);
            }
            

            Console.ReadLine();

            server.Stop();
        }
    }
}
