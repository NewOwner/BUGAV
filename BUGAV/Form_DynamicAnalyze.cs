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
using DynamicAnalyzeCtrl;
using System.Threading;

namespace BUGAV {
    public partial class Form_DynamicAnalyze : DarkForm {
        public Form_DynamicAnalyze() {
            InitializeComponent();
        }

        private void DynamicAnalyze_Button_AddFile_Click(object sender, EventArgs e) {
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
                    DynamicAnalyze_checkedListBox_Files.Items.Insert(0, new FilesListBoxItem { Name = fileName, Value = filePath });
                }
            }
        }

        private void DynamicAnalyze_Button_DeleteFile_Click(object sender, EventArgs e) {
            foreach (var item in DynamicAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                DynamicAnalyze_checkedListBox_Files.Items.Remove(item);
            }
        }

        private void DynamicAnalyze_Button_UpdateProc_Click(object sender, EventArgs e) {

            DynamicAnalyze_checkedListBox_Processes.Items.Clear();

            Process[] processlist = Process.GetProcesses();

            foreach (Process proc in processlist) {
                Console.WriteLine("Process: {0} ID: {1}", proc.ProcessName, proc.Id);

                ProcListBoxItem newListItem = new ProcListBoxItem {
                    Name = proc.ProcessName,
                    ParentId = 0,
                    ProcessId = proc.Id,
                    procHandler = proc
                };

                DynamicAnalyze_checkedListBox_Processes.Items.Insert(0, newListItem);
            }
        }

        private void DynamicAnalyze_Button_LoadTools_Click(object sender, EventArgs e) {
            string toolDirectory = @"tools";
            try {
                var toolFiles = Directory.EnumerateFiles(toolDirectory, "*.dll", SearchOption.AllDirectories);
                foreach (string toolPath in toolFiles) {
                    string fileName = Path.GetFileName(toolPath);
                    DynamicAnalyze_checkedListBox_Tools.Items.Insert(0, new FilesListBoxItem { Name = fileName, Value = toolPath });
                }
            } catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }

        private void DynamicAnalyze_Button_StartPin_Click(object sender, EventArgs e) {
            foreach (var tool in DynamicAnalyze_checkedListBox_Tools.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                foreach (var file in DynamicAnalyze_checkedListBox_Files.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                    Thread pinThread = StartTheThread("file", tool.Value, file.Value, DynamicAnalyze_notifyIcon);
                }
                foreach (var proc in DynamicAnalyze_checkedListBox_Processes.CheckedItems.OfType<ProcListBoxItem>().ToList()) {
                    Thread pinThread = StartTheThread("process", tool.Value, proc.ProcessId.ToString(), DynamicAnalyze_notifyIcon);
                }
            }
        }

        public Thread StartTheThread(string _method, string _tool, string _target, System.Windows.Forms.NotifyIcon _notifyIcon) {
            var t = new Thread(() => PinThreadFunc(_method, _tool, _target, _notifyIcon));
            t.Start();
            return t;
        }

        private static void PinThreadFunc(string _method, string _tool, string _target, System.Windows.Forms.NotifyIcon _notifyIcon) {
            IToolResParse resParser = GetTool(_tool);
            if (_method == "file") {
                PinToolManager.RunToolFile(_tool, _target);
            } else if (_method == "process") {
                PinToolManager.RunToolProcess(_tool, _target);
            }
            bool res = resParser.ParseRes();
            _notifyIcon.Visible = true;
            _notifyIcon.ShowBalloonTip(5000, "Suspitious App", "Suspitious Activity in App: " + _target, System.Windows.Forms.ToolTipIcon.Warning);
            if (res) {
                
            }
        }

        public static IToolResParse GetTool(string _tool) {
            string toolname = Path.GetFileName(_tool);
            if (toolname == "Tool_FuncArgs.dll") {
                return new ToolResParse_FuncArgs("tool_funcargs.txt");
            }else if (toolname == "Tool_ImageLoad.dll") {
                return new ToolResParse_ImageLoad("tool_imageload.txt");
            } else if (toolname == "Tool_RopDetect.dll") {
                return new ToolResParse_RopDetect("tool_ropdetect.txt");
            } else if (toolname == "Tool_ThreadStart.dll") {
                return new ToolResParse_ThreadStart("tool_threadstart.txt");
            } else {
                return null;
            }
        }

        
        private void DynamicAnalyze_notifyIcon_MouseClick(object sender, MouseEventArgs e) {
            DynamicAnalyze_notifyIcon.Visible = false;
        }
    }
}
