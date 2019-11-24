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

using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;

namespace BUGAV {
    public partial class Form_RTProtection : DarkForm {
        RtProtectionWrap __RtProtectionInst;
        Thread __procMonThread;
        bool __procMonThread_working;
        public Form_RTProtection() {
            InitializeComponent();
            try {
                __RtProtectionInst = new RtProtectionWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
           
        }
        private void RTProtection_Button_Activate_Click(object sender, EventArgs e) {
            if (RTProtection_Button_Activate.Text == "Activate") {
                __RtProtectionInst.WRAP_RtProtectionDrv_LoadDriver();
                if (__RtProtectionInst.Get_loaded() == true) {
                    RTProtection_Button_Activate.Text = "Deactivate";
                    __procMonThread = new Thread(new ThreadStart(ProcMonThreadFunc));
                    __procMonThread_working = true;
                    __procMonThread.Start();
                }

            } else {
                __procMonThread_working = false;
            }
        }

        private void RTProtection_Button_TerminateProcess_Click(object sender, EventArgs e) {
            foreach (var item in RTProtection_checkedListBox_Processes.SelectedItems.OfType<ProcListBoxItem>().ToList()) {
                item.procHandler.Kill();
                RTProtection_checkedListBox_Processes.Items.Remove(item);
            }
        }

        private void RTProtection_Button_Hook_Click(object sender, EventArgs e) {
            foreach (var item in RTProtection_checkedListBox_Processes.SelectedItems.OfType<ProcListBoxItem>().ToList()) {
                Console.WriteLine(@"\\.\pipe\myNamedPipe" + item.ProcessId.ToString());
                NamedPipeServer PServer1 = new NamedPipeServer(@"\\.\pipe\myNamedPipe"+ item.ProcessId.ToString(), 0, RTProtection_notifyIcon);
                PServer1.Start();
                __RtProtectionInst.WRAP_InjectLib(item.ProcessId);
            }
        }

        public void ProcMonThreadFunc() {
            while (__procMonThread_working) {
                Console.WriteLine("WRAP_RtProtectionDrv_NewProcMon");
                bool res = __RtProtectionInst.WRAP_RtProtectionDrv_NewProcMon();
                Console.WriteLine(res.ToString());
                if (res) {
                    int _ParentId = __RtProtectionInst.Get_ParentId();
                    int _ProcessId = __RtProtectionInst.Get_ProcessId();
                    int _Create = __RtProtectionInst.Get_Create();
                    if (_Create == 1) {
                        Process newproc = Process.GetProcessById(_ProcessId);
                        ProcListBoxItem newListItem = new ProcListBoxItem {
                            Name = newproc.ProcessName,
                            ParentId = _ParentId,
                            ProcessId = _ProcessId,
                            procHandler = newproc
                        };
                        RTProtection_checkedListBox_Processes.Items.Insert(0, newListItem);

                    } else {
                        foreach (var item in RTProtection_checkedListBox_Processes.Items.OfType<ProcListBoxItem>().ToList()) {
                            Console.WriteLine(item.ProcessId.ToString() + " " + _ProcessId.ToString());
                            if (item.ProcessId == _ProcessId) {
                                RTProtection_checkedListBox_Processes.Items.Remove(item);
                                break;
                            }
                        }
                    }
                }
            }
            __RtProtectionInst.WRAP_RtProtectionDrv_UnloadDriver();
            if (__RtProtectionInst.Get_loaded() == false) {
                RTProtection_Button_Activate.Text = "Activate";
            }
        }

        
    }
    public class ProcListBoxItem {
        public string Name { get; set; }
        public int ParentId { get; set; }
        public int ProcessId { get; set; }
        public int Create { get; set; }
        public Process procHandler { get; set; }
        public override string ToString() { return Name + " " + ProcessId.ToString(); }
    }
}
