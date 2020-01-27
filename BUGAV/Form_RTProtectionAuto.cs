using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using DarkUI.Forms;

using System.IO;
using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;

using DynamicAnalyzeCtrl;
using StaticAnalyzeManager;

namespace BUGAV {
    public partial class Form_RTProtectionAuto : DarkForm {
        RTNewFilesWrap __RTNewFilesWrapInst;
        RtProtectionWrap __RtConsoleMonInst;
        WebApcInjldrWrap __WebApcInjldrInst;

        Thread __NewFilesThread;
        Thread __ConsoleMonThread;
        Thread __WebApcInjldrThread;

        bool __NewFilesThread_working;
        bool __ConsoleMonThread_working;
        bool __WebApcInjldrThread_working;
        public Form_RTProtectionAuto() {
            InitializeComponent();
            try {
                __RTNewFilesWrapInst = new RTNewFilesWrap();
                __RtConsoleMonInst = new RtProtectionWrap();
                __WebApcInjldrInst = new WebApcInjldrWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }


        #region newFilesFilter
        private void darkButton1_Click(object sender, EventArgs e) {
            if (RTAuto_NMF_Button.Text == "New Malware Files OFF") {
                RTAuto_NMF_Button.Text = "New Malware Files ON";
                __NewFilesThread = new Thread(new ThreadStart(NewFilesThreadFunc));
                __NewFilesThread_working = true;
                __NewFilesThread.Start();
            } else {
                RTAuto_NMF_Button.Text = "New Malware Files OFF";
                __NewFilesThread_working = false;
            }
        }

        public void NewFilesThreadFunc() {
            while (__NewFilesThread_working) {
                Console.WriteLine("WRAP_ConnectPort");
                bool res = __RTNewFilesWrapInst.WRAP_ConnectPort();
                if (!res) { return; }
                res = __RTNewFilesWrapInst.WRAP_GetFileMessage();
                if (!res) { return; }
                string fname;
                System.IO.StreamReader file = new System.IO.StreamReader(@"new_files.txt");
                fname = file.ReadLine();
                file.Close();

                System.Console.WriteLine(fname);

                //StaticAnalyzeThreadFunc("csharp", fname, RTAuto_notifyIcon);
                //StaticAnalyzeThreadFunc("cpp", fname, RTAuto_notifyIcon);
                StaticAnalyzeThreadFunc("yara", fname, RTAuto_notifyIcon);
            }
        }


        public Thread StartStaticAnalyzeThread(string _method, string _target, System.Windows.Forms.NotifyIcon _notifyIcon) {
            var t = new Thread(() => StaticAnalyzeThreadFunc(_method, _target, _notifyIcon));
            t.Start();
            return t;
        }

        private static void StaticAnalyzeThreadFunc(string _method, string _target, System.Windows.Forms.NotifyIcon _notifyIcon) {
            if (_target == null) { return; }
            IToolResParse resParser = GetTool(_method, _target);
            if (resParser == null) { return; }

            System.Console.WriteLine(_method);
            System.Console.WriteLine(_target);
            System.Console.WriteLine(_notifyIcon.ToString());

            if (!File.Exists(_target)) { return; }

            if (_method == "csharp") {
                Console.WriteLine("csharp analyze.");
                string[] args_arr = new string[] { _target };
                de4dot.cui.Program.Main(args_arr);
                Console.WriteLine("csharp done.");
            } else if (_method == "cpp") {
                string _toolpath = @"Manalyze\bin\manalyze.exe";
                string _argflags = "--output=json --hashes --plugins=all";
                string _fext = ".cpp.res.txt";
                SAManager.RunToolOutCapture(_target, _toolpath, _argflags, _fext);
            } else if (_method == "yara") {
                string _toolpath = @"YARA\yara64.exe";
                string _argflags = @"YARA\rules\index.yar -w";
                string _fext = ".yara.res.txt";
                SAManager.RunToolOutCapture(_target, _toolpath, _argflags, _fext);
            }
            Console.WriteLine("resParser.ParseResVerbose +.");
            ResContainer res = resParser.ParseResVerbose();
            Console.WriteLine("resParser.ParseResVerbose -.");
            if (res == null) { return; }
            _notifyIcon.Visible = true;
            string appInfo = string.Empty;
            if (res.isMalware) {
                _notifyIcon.ShowBalloonTip(5000, "Malware App", "Malware App: " + _target, System.Windows.Forms.ToolTipIcon.Error);
                appInfo = String.Join("\n", res.suspiciousAttr.ToArray());
            }
            if (res.isSuspicious) {
                _notifyIcon.ShowBalloonTip(5000, "Suspitious App", "Suspicious App: " + _target, System.Windows.Forms.ToolTipIcon.Warning);
                appInfo = String.Join("\n", res.suspiciousAttr.ToArray());
            } else {
                _notifyIcon.ShowBalloonTip(5000, "Nothing Suspitious in App", "App: " + _target, System.Windows.Forms.ToolTipIcon.Info);
            }
        }

        public static IToolResParse GetTool(string _method, string _target) {
            try {
                string targetname = Path.GetFileName(_target);
                if (_method == "csharp") {
                    return new ToolResParse_StaticCsharp(targetname + ".cs.res.txt");
                } else if (_method == "cpp") {
                    return new ToolResParse_StaticCpp(targetname + ".cpp.res.txt");
                } else if (_method == "yara") {
                    return new ToolResParse_StaticYara(targetname + ".yara.res.txt");
                } else { return null; }
            } catch (Exception e) {
                Console.WriteLine("Exception caught.");
                return null;
            }
        }

        #endregion

        #region consoleMon
        private void ConsoleMonButton_Click(object sender, EventArgs e) {
            if (ConsoleMonButton.Text == "ConsoleMonButton OFF") {
                __RtConsoleMonInst.WRAP_RtProtectionDrv_LoadDriver();
                if (__RtConsoleMonInst.Get_loaded() == true) {
                    ConsoleMonButton.Text = "ConsoleMonButton ON";
                    __ConsoleMonThread = new Thread(new ThreadStart(ConsoleMonThreadFunc));
                    __ConsoleMonThread_working = true;
                    __ConsoleMonThread.Start();
                }

            } else {
                __ConsoleMonThread_working = false;
            }
        }


        public void ConsoleMonThreadFunc() {
            while (__ConsoleMonThread_working) {
                Console.WriteLine("WRAP_RtProtectionDrv_NewProcMon");
                bool res = __RtConsoleMonInst.WRAP_RtProtectionDrv_NewProcMon();
                Console.WriteLine(res.ToString());
                if (res) {
                    int _ParentId = __RtConsoleMonInst.Get_ParentId();
                    int _ProcessId = __RtConsoleMonInst.Get_ProcessId();
                    int _Create = __RtConsoleMonInst.Get_Create();
                    if (_Create == 1) {
                        Process newproc = Process.GetProcessById(_ProcessId);
                        Console.WriteLine(newproc.ProcessName);
                        Console.WriteLine(_ParentId);
                        Console.WriteLine(_ProcessId);

                        if(newproc.ProcessName=="cmd" ||
                            newproc.ProcessName == "powershell") {
                            NamedPipeServer PServer1 = 
                                new NamedPipeServer(
                                    @"\\.\pipe\myNamedPipe" + _ProcessId.ToString(), 
                                    0, 
                                    RTAutoConsole_notifyIcon,
                                    "console"
                                    );
                            PServer1.Start();
                            __RtConsoleMonInst.WRAP_InjectConsoleLib(_ProcessId);
                        }
                    }
                }
            }
            __RtConsoleMonInst.WRAP_RtProtectionDrv_UnloadDriver();
            if (__RtConsoleMonInst.Get_loaded() == false) {
                ConsoleMonButton.Text = "ConsoleMonButton OFF";
            }
        }

        #endregion

        #region WebApcHook

        private void WebApcMonButton_Click(object sender, EventArgs e) {
            if (WebApcMonButton.Text == "WebApcMonButton OFF") {
                __WebApcInjldrInst.WRAP_Load();
                if (__WebApcInjldrInst.Get_loaded() == true) {
                    WebApcMonButton.Text = "WebApcMonButton ON";
                    __WebApcInjldrThread = new Thread(new ThreadStart(WebApcInjldrThreadFunc));
                    __WebApcInjldrThread_working = true;
                    __WebApcInjldrThread.Start();
                }

            } else {
                __WebApcInjldrThread_working = false;
                __WebApcInjldrInst.WRAP_StopSession();
                WebApcMonButton.Text = "WebApcMonButton OFF";
            }
        }

        public void WebApcInjldrThreadFunc() {
            while (__WebApcInjldrThread_working) {
                Console.WriteLine("WebApcInjldrThreadFunc");
                __WebApcInjldrInst.WRAP_StartSession();
                //bool res = __RtConsoleMonInst.WRAP_RtProtectionDrv_NewProcMon();
                //Console.WriteLine(res.ToString());
                //if (res) {
                //    int _ParentId = __RtConsoleMonInst.Get_ParentId();
                //    int _ProcessId = __RtConsoleMonInst.Get_ProcessId();
                //    int _Create = __RtConsoleMonInst.Get_Create();
                //    if (_Create == 1) {
                //        Process newproc = Process.GetProcessById(_ProcessId);
                //        Console.WriteLine(newproc.ProcessName);
                //        Console.WriteLine(_ParentId);
                //        Console.WriteLine(_ProcessId);
                //
                //        if (newproc.ProcessName == "cmd" ||
                //            newproc.ProcessName == "powershell") {
                //            NamedPipeServer PServer1 =
                //                new NamedPipeServer(
                //                    @"\\.\pipe\myNamedPipe" + _ProcessId.ToString(),
                //                    0,
                //                    RTAutoConsole_notifyIcon,
                //                    "console"
                //                    );
                //            PServer1.Start();
                //            __RtConsoleMonInst.WRAP_InjectConsoleLib(_ProcessId);
                //        }
                //    }
                //}
            }
        }

        #endregion

    }
}
