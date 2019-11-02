using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using DarkUI.Forms;
using System.Runtime.InteropServices;

namespace BUGAV {
    public partial class Form_FilterFile : DarkForm {
        FilterFileConfig __FileConfigInst;
        FilterFileWrap __FilterFileWrapInst;
        public Form_FilterFile() {
            InitializeComponent();
            __FileConfigInst = new FilterFileConfig(FilterFiler_checkedListBox_Files);
            try {
                __FilterFileWrapInst = new FilterFileWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }
        private void FilterFile_Button_Add_Click(object sender, EventArgs e) {
            var fileContent = string.Empty;
            var filePath = string.Empty;
            var realfilePath = string.Empty;
            var fileName = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
                openFileDialog.InitialDirectory = "e:\\";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK) {
                    filePath = openFileDialog.FileName;
                    realfilePath = GetRealPath(filePath);
                    fileName = Path.GetFileName(filePath);
                    FilterFiler_checkedListBox_Files.Items.Insert(0, new FilesListBoxItem { Name = fileName, Value = realfilePath });
                    __FileConfigInst.UpdateConfig();
                    __FilterFileWrapInst.WRAP_FilterFileDrv_UpdateConfig();
                }
            }
        }
        private void FilterFile_Button_Delete_Click(object sender, EventArgs e) {
            foreach (var item in FilterFiler_checkedListBox_Files.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                FilterFiler_checkedListBox_Files.Items.Remove(item);
            }
            __FileConfigInst.UpdateConfig();
            __FilterFileWrapInst.WRAP_FilterFileDrv_UpdateConfig();
        }

        private void FilterFile_Button_Activate_Click(object sender, EventArgs e) {
            //if(FilterFile_Button_Activate.Text == "Activate") {
            //    __FilterFileWrapInst.WRAP_FilterFileDrv_LoadDriver();
            //    if(__FilterFileWrapInst.Get_loaded() == true) {
            //        FilterFile_Button_Activate.Text = "Deactivate";
            //    }
            //
            //} else {
            //    __FilterFileWrapInst.WRAP_FilterFileDrv_UnloadDriver();
            //    if (__FilterFileWrapInst.Get_loaded() == false) {
            //        FilterFile_Button_Activate.Text = "Activate";
            //    }
            //}
            
            __FilterFileWrapInst.WRAP_FilterFileDrv_ConnectCommunicationPort();
        }

        private static string GetRealPath(string path) {
        
            string realPath = path;
            StringBuilder pathInformation = new StringBuilder(250);
            string driveLetter = Path.GetPathRoot(realPath).Replace("\\", "");
            QueryDosDevice(driveLetter, pathInformation, 250);

            string realRoot = pathInformation.ToString();

            realPath = Path.Combine(realRoot, realPath.Replace(Path.GetPathRoot(realPath), ""));
        
            return realPath;
        }
        
        
        [DllImport("kernel32.dll")]
        static extern uint QueryDosDevice(string lpDeviceName, StringBuilder lpTargetPath, int ucchMax);
    }
    public class FilesListBoxItem {
        public string Name { get; set; }
        public string Value { get; set; }
        public override string ToString() { return Name; }
    }
    public class FilterFileConfig {
        System.Windows.Forms.CheckedListBox FileList;
        string ConfigPath { get; set; }
        public FilterFileConfig(System.Windows.Forms.CheckedListBox _FileList) {
            ConfigPath = @"E:\bugav_filefilter.txt";
            using (var stream = File.Open(ConfigPath, FileMode.Create)) { }
            FileList = _FileList;
        }
        public void UpdateConfig() {
            File.WriteAllText(ConfigPath, string.Empty);
            using (StreamWriter file = new StreamWriter(ConfigPath)) {
                foreach (var item in FileList.Items.OfType<FilesListBoxItem>().ToList()) {
                    file.WriteLine(item.Value);
                }
            }
            
        }

    }


}
