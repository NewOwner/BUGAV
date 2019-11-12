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
                    PinToolManager.RunTool(tool.Value, file.Value);
                }
                foreach (var proc in DynamicAnalyze_checkedListBox_Processes.CheckedItems.OfType<ProcListBoxItem>().ToList()) {
                    PinToolManager.RunTool(tool.Value, proc.ProcessId);
                }

            }

        }


    }
}
