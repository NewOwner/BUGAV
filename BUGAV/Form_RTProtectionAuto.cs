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
    public partial class Form_RTProtectionAuto : DarkForm {
        RTNewFilesWrap __RTNewFilesWrapInst;
        Thread __NewFilesThread;
        bool __NewFilesThread_working;
        public Form_RTProtectionAuto() {
            InitializeComponent();
            try {
                __RTNewFilesWrapInst = new RTNewFilesWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

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
                
            }
        }


    }
}
