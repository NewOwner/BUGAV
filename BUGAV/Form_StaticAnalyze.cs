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
using System.Threading;
using DynamicAnalyzeCtrl;
using StaticAnalyzeManager;

namespace BUGAV {
    public partial class Form_StaticAnalyze : DarkForm {
        StaticAnalyzeCppWrap __StaticAnalyzeCppWrapInst;
        public Form_StaticAnalyze() {
            InitializeComponent();
            try {
                __StaticAnalyzeCppWrapInst = new StaticAnalyzeCppWrap();
            } catch (Exception e) {
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        private void StaticAnalyze_Button_AddFile_Click(object sender, EventArgs e) {
            var filePath = string.Empty;
            var fileName = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
                openFileDialog.InitialDirectory = "e:\\";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK) {
                    filePath = openFileDialog.FileName;
                    fileName = Path.GetFileName(filePath);
                    StaticAnalyze_checkedListBox_Files.Items.Insert(0, new FilesStaticAnalyzeListBoxItem { Name = fileName, Value = filePath, Info = "not scanned" });
                }
            }
        }

        private void StaticAnalyze_checkedListBox_Files_SelectedIndexChanged(object sender, EventArgs e) {
            //  MessageBox.Show(sender.ToString());
        }

        private void StaticAnalyze_Button_DeleteFile_Click(object sender, EventArgs e) {
            foreach (var item in StaticAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesStaticAnalyzeListBoxItem>().ToList()) {
                StaticAnalyze_checkedListBox_Files.Items.Remove(item);
            }
        }

        private void StaticAnalyze_Button_ScanCs_Click(object sender, EventArgs e) {
            foreach (var item in StaticAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesStaticAnalyzeListBoxItem>().ToList()) {
                StartStaticAnalyzeThread("csharp", item.Value, __StaticAnalyzeCppWrapInst, StaticAnalyze_notifyIcon);
            }
        }

        private void StaticAnalyze_Button_ScanCpp_Click(object sender, EventArgs e) {
            foreach (var item in StaticAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesStaticAnalyzeListBoxItem>().ToList()) {
                StartStaticAnalyzeThread("cpp", item.Value, __StaticAnalyzeCppWrapInst, StaticAnalyze_notifyIcon);
            }
        }

        private void StaticAnalyze_Button_Yara_Click(object sender, EventArgs e) {
            foreach (var item in StaticAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesStaticAnalyzeListBoxItem>().ToList()) {
                StartStaticAnalyzeThread("yara", item.Value, __StaticAnalyzeCppWrapInst, StaticAnalyze_notifyIcon);
            }
        }

        public Thread StartStaticAnalyzeThread(string _method, string _target, StaticAnalyzeCppWrap _StaticAnalyzeCppWrapInst, System.Windows.Forms.NotifyIcon _notifyIcon) {
            var t = new Thread(() => StaticAnalyzeThreadFunc(_method, _target, _StaticAnalyzeCppWrapInst, _notifyIcon));
            t.Start();
            return t;
        }

        private static void StaticAnalyzeThreadFunc(string _method, string _target, StaticAnalyzeCppWrap _StaticAnalyzeCppWrapInst, System.Windows.Forms.NotifyIcon _notifyIcon) {
            IToolResParse resParser = GetTool(_method, _target);
            if (_method == "csharp") {
                string[] args_arr = new string[] { _target };
                de4dot.cui.Program.Main(args_arr);
            } else if (_method == "cpp") {
                string _toolpath = @"..\..\..\__LIBS\Manalyze\bin\manalyze.exe";
                string _argflags = "--output=json --hashes --plugins=all";
                string _fext = ".cpp.res.txt";
                SAManager.RunToolOutCapture(_target, _toolpath, _argflags, _fext);
            } else if (_method == "yara") {
                string _toolpath = @"..\..\..\__LIBS\YARA\yara64.exe";
                string _argflags = @"..\..\..\__LIBS\YARA\rules\index.yar -w";
                string _fext = ".yara.res.txt";
                SAManager.RunToolOutCapture(_target, _toolpath, _argflags, _fext);
            }
            bool res = resParser.ParseRes();
            _notifyIcon.Visible = true;
            if (res) {
                _notifyIcon.ShowBalloonTip(5000, "Suspitious App", "Suspitious Activity in App: " + _target, System.Windows.Forms.ToolTipIcon.Warning);
            }
        }

        public static IToolResParse GetTool(string _method, string _target) {
            string targetname = Path.GetFileName(_target);
            if (_method == "csharp") { 
                return new ToolResParse_StaticCsharp(targetname + ".cs.res.txt"); 
            } 
            else if (_method == "cpp") { 
                return new ToolResParse_StaticCpp(targetname + ".cpp.res.txt"); 
            }
            else if (_method == "yara") {
                return new ToolResParse_StaticYara(targetname + ".yara.res.txt");
            } else { return null; }
        }


    }

    public class FilesStaticAnalyzeListBoxItem {
        public string Name { get; set; }
        public string Value { get; set; }
        public string Info { get; set; }
        public override string ToString() { return Name; }
    }
}
