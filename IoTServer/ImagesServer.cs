using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;

namespace IoTServer
{
    class ImagesServer
    {
        private const long _ServerNotRunning = 0;
        private const long _ServerRunning = 1;

        private long _IsServerRunning;

        private Thread _ConnectionsAccepterThread;
        private List<Thread> _RequestHandlerThreads;

        private Socket _ServerSocket;
        private List<Socket> _RequestHandlerSockets;

        private void Send(Socket socket, byte[] data)
        {
            byte[] signal = new byte[1];
            socket.Send(data);
            socket.Receive(signal);
        }

        private void Receive(Socket socket, byte[] buffer)
        {
            byte[] signal = new byte[1];
            socket.Receive(buffer);
            socket.Send(signal);
        }

        private void SendImage(Socket socket, string filename)
        {
            const int pixelsOffset = 62;
            const int columnsCount = 104;
            const int rowsCount = 212;
            const int bmpRowLength = 128;

            byte[] fileBytes = File.ReadAllBytes(filename);

            for (int i = 0; i < rowsCount; i++)
            {
                byte[] column = new byte[13];

                column = fileBytes.Skip(pixelsOffset + i * bmpRowLength).Take(columnsCount).ToArray();

                Send(socket, column);
            }
        }

        /*
         * Runs a loop for handling incoming requests.
         */
        public void RequestHandler(object socket)
        {
            try
            {
                string[] filePaths = File.ReadAllLines("config.txt");

                MSAccessDBReader iotDBReader = new MSAccessDBReader();

                while (Interlocked.Read(ref _IsServerRunning) == _ServerRunning)
                {
                    byte[] buffer = new byte[1024];

                    Receive(socket as Socket, buffer);

                    int price = iotDBReader.GetPrice(filePaths[0], buffer[0]);

                    if (price == -1)
                    {
                        // the last item in filePaths is the path to an "error" image
                        price = filePaths.Length - 2;
                    }
                    // +1 'cause at position 0 we've got path to DB
                    SendImage(socket as Socket, filePaths[price + 1]);
                }
            }
            catch (Exception exc)
            {
                Console.WriteLine("Request Handler exception:");
                Console.WriteLine(exc.Message);
            }
        }

        /*
         * Binds a server socket to the specified port
         * and Starts listening asynchronously, exiting
         * the function. As soon as an someone connects,
         * creates a thread that begins communicating by
         * receiving incoming requests and handling them
         * with HandleRequest function
         */
        public bool Start(int port)
        {
            if (Interlocked.Read(ref _IsServerRunning) == _ServerRunning)
            {
                return false;
            }

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Any, port);

            _ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _ServerSocket.Bind(serverEndPoint);
            _ServerSocket.Listen(1);

            _ConnectionsAccepterThread = new Thread(delegate ()
                {
                    try
                    {
                        while (Interlocked.Read(ref _IsServerRunning) == _ServerRunning)
                        {
                            Socket newConnectionSocket = _ServerSocket.Accept();
                            Thread newConnectionThread = new Thread(RequestHandler);

                            _RequestHandlerSockets.Add(newConnectionSocket);
                            _RequestHandlerThreads.Add(newConnectionThread);

                            newConnectionThread.Start(newConnectionSocket);
                        }
                    }
                    catch(Exception exc)
                    {
                        Console.WriteLine("Accepter Thread exception:");
                        Console.WriteLine(exc.Message);
                    }
                }
            );

            _IsServerRunning = _ServerRunning;

            _ConnectionsAccepterThread.Start();

            return true;
        }

        public bool Stop(int timeoutBeforeForceTerminationMillisecs = 0)
        {
            if (Interlocked.CompareExchange(ref _IsServerRunning, _ServerNotRunning, _ServerRunning) == _ServerNotRunning)
            {
                return false;
            }

            Thread.Sleep(timeoutBeforeForceTerminationMillisecs);

            _ServerSocket.Close();
            _ConnectionsAccepterThread.Abort();

            for (int i = 0; i < _RequestHandlerSockets.Count; i++)
            {
                _RequestHandlerSockets[i].Close();
                _RequestHandlerThreads[i].Abort();
            }

            return true;
        }

        public ImagesServer()
        {
            _IsServerRunning = _ServerNotRunning;
            _RequestHandlerThreads = new List<Thread>();
            _RequestHandlerSockets = new List<Socket>();
        }
    }
}
