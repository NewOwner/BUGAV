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
            var fileName = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
                openFileDialog.InitialDirectory = "f:\\";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK) {
                    filePath = openFileDialog.FileName;
                    fileName = Path.GetFileName(filePath);
                    FilterFiler_checkedListBox_Files.Items.Insert(0, new FilesListBoxItem { Name = fileName, Value = filePath });
                    __FileConfigInst.UpdateConfig();
                }
            }
        }
        private void FilterFile_Button_Delete_Click(object sender, EventArgs e) {
            foreach (var item in FilterFiler_checkedListBox_Files.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                FilterFiler_checkedListBox_Files.Items.Remove(item);
            }
            __FileConfigInst.UpdateConfig();
        }
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
