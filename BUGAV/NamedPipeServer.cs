using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Win32.SafeHandles;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;

using DynamicAnalyzeCtrl;
using StaticAnalyzeManager;

namespace BUGAV {

    public class NamedPipeServer {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern SafeFileHandle CreateNamedPipe(
           String pipeName,
           uint dwOpenMode,
           uint dwPipeMode,
           uint nMaxInstances,
           uint nOutBufferSize,
           uint nInBufferSize,
           uint nDefaultTimeOut,
           IntPtr lpSecurityAttributes);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern int ConnectNamedPipe(
           SafeFileHandle hNamedPipe,
           IntPtr lpOverlapped);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern int DisconnectNamedPipe(
           SafeFileHandle hNamedPipe);

        public const uint DUPLEX = (0x00000003);
        public const uint FILE_FLAG_OVERLAPPED = (0x40000000);
        public string method;
        public string processname;
        public class Client {
            public SafeFileHandle handle;
            public FileStream stream;
        }

        public const int BUFFER_SIZE = 500;
        public Client clientse = null;

        public string pipeName;
        Thread listenThread;
        SafeFileHandle clientHandle;
        public int ClientType;

        System.Windows.Forms.NotifyIcon notIcon;

        public NamedPipeServer(string PName, int Mode, System.Windows.Forms.NotifyIcon _notIcon, string _method, string _processname) {
            pipeName = PName;
            ClientType = Mode;//0 Reading Pipe, 1 Writing Pipe
            notIcon = _notIcon;
            method = _method;
            processname = _processname;
        }

        public void Start() {
            Console.WriteLine("C# pipe server");
            this.listenThread = new Thread(new ThreadStart(ListenForClients));
            this.listenThread.Start();
        }
        private void ListenForClients() {
            Console.WriteLine("C# pipe server ListenForClients");
            while (true) {

                clientHandle = CreateNamedPipe(this.pipeName, DUPLEX | FILE_FLAG_OVERLAPPED, 0, 255, BUFFER_SIZE, BUFFER_SIZE, 0, IntPtr.Zero);

                //could not create named pipe
                if (clientHandle.IsInvalid) {
                    Console.WriteLine("C# could not create named pipe");
                    return; 
                }

                int success = ConnectNamedPipe(clientHandle, IntPtr.Zero);

                //could not connect client
                if (success == 0) {
                    Console.WriteLine("C# could not connect client");
                    return;
                }

                clientse = new Client();
                clientse.handle = clientHandle;
                clientse.stream = new FileStream(clientse.handle, FileAccess.ReadWrite, BUFFER_SIZE, true);

                if (ClientType == 0) {
                    Console.WriteLine("C# Read thread");
                    Thread readThread = new Thread(new ThreadStart(Read));
                    readThread.Start();
                }
                Console.WriteLine("C# NOT Read thread");
            }
        }

        public static string ByteArrayToString(byte[] ba) {
            return BitConverter.ToString(ba).Replace("-", "");
        }

        public static byte[] removeTrailingNulls(byte[] ba) {
            return ba.TakeWhile((v, index) => ba.Skip(index).Any(w => w != 0x00)).ToArray();
        }

        private void Read() {
            Console.WriteLine("C# pipe server Read");
            //Client client = (Client)clientObj;
            //clientse.stream = new FileStream(clientse.handle, FileAccess.ReadWrite, BUFFER_SIZE, true);
            byte[] buffer = null;
            ASCIIEncoding encoder = new ASCIIEncoding();

            while (true) {

                int bytesRead = 0;

                try {
                    buffer = new byte[BUFFER_SIZE];
                    bytesRead = clientse.stream.Read(buffer, 0, BUFFER_SIZE);
                } catch {
                    //read error has occurred
                    break;
                }

                //client has disconnected
                if (bytesRead == 0)
                    break;

                //fire message received event
                //if (this.MessageReceived != null)
                //    this.MessageReceived(clientse, encoder.GetString(buffer, 0, bytesRead));

                int ReadLength = 0;
                for (int i = 0; i < BUFFER_SIZE; i++) {
                    if (buffer[i].ToString("x2") != "cc") {
                        ReadLength++;
                    } else
                        break;
                }
                if (ReadLength > 0) {
                    byte[] Rc = new byte[ReadLength];
                    Buffer.BlockCopy(buffer, 0, Rc, 0, ReadLength);
                    //Console.WriteLine("C# App: Received " + ReadLength + " Bytes: " + retstr);
                    //Console.WriteLine("C# App: Received " + ReadLength + " Bytes: " + ByteArrayToString(Rc));
                    byte[] RcTrail = removeTrailingNulls(Rc);
                    string retstr = encoder.GetString(RcTrail, 0, RcTrail.Length);
                    Console.WriteLine("C# App: Received " + ReadLength + " Bytes: " + retstr);
                    buffer.Initialize();

                    if (method == "console") {
                        string _target = "console.txt";
                        string _consoleIOCS = "consoleIOCS.txt";
                        System.IO.File.WriteAllText(_target, retstr);

                        string _toolpath = @"java";
                        string _argflags = 
                            "-jar similarity-uniform-fuzzy-hash-1.8.4.jar -cfh "
                            + _target +" "+ _consoleIOCS+" -f 3 -x";
                        string _fext = "res.console.txt";

                        Console.WriteLine("CONSOOOLE "+ _argflags);
                        IToolResParse resParser = new ToolResParse_ConsoleMon(_fext);
                        SAManager.RunToolOutCapture("", _toolpath, _argflags, _fext);

                        ResContainer res = resParser.ParseResVerbose();
                        notIcon.Visible = true;
                        if (res.isMalware) {
                            notIcon.ShowBalloonTip(5000, "Malware App", "Malware App: "+processname, System.Windows.Forms.ToolTipIcon.Error);
                        }else if (res.isSuspicious) {
                            notIcon.ShowBalloonTip(5000, "Suspitious App", "Suspicious App: " + processname, System.Windows.Forms.ToolTipIcon.Warning);
                        }

                    }else if(method== "apimon") {
                        string _target = "apimon.txt";
                        System.IO.File.WriteAllText(_target, retstr);
                        IToolResParse resParser = new ToolResParse_ApiMon(_target);
                        ResContainer res = resParser.ParseResVerbose();
                        notIcon.Visible = true;
                        if (res.isMalware) {
                            notIcon.ShowBalloonTip(5000, "Malware App", "Malware App: " + processname, System.Windows.Forms.ToolTipIcon.Error);
                        } else if (res.isSuspicious) {
                            notIcon.ShowBalloonTip(5000, "Suspitious App", "Suspicious App: " + processname, System.Windows.Forms.ToolTipIcon.Warning);
                        }
                    }

                }

            }

            //clean up resources
            clientse.stream.Close();
            clientse.handle.Close();

        }
        public void SendMessage(string message, Client client) {

            ASCIIEncoding encoder = new ASCIIEncoding();
            byte[] messageBuffer = encoder.GetBytes(message);

            if (client.stream.CanWrite) {
                client.stream.Write(messageBuffer, 0, messageBuffer.Length);
                client.stream.Flush();
            }


        }
        public void StopServer() {
            //clean up resources

            DisconnectNamedPipe(this.clientHandle);


            this.listenThread.Abort();
        }

    }
}
