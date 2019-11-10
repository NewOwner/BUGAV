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

namespace BUGAV {
    public partial class Form_StaticAnalyze : DarkForm {
        public Form_StaticAnalyze() {
            InitializeComponent();
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
                    StaticAnalyze_checkedListBox_Files.Items.Insert(0, new FilesStaticAnalyzeListBoxItem { Name = fileName, Value = filePath, Info="not scanned" });
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
                string[] args_arr = new string[] { item.Value };
                de4dot.cui.Program.Main(args_arr);
            }
        }

        private void StaticAnalyze_Button_ScanCpp_Click(object sender, EventArgs e) {

        }

        //static int Main(string[] args) => de4dot.cui.Program.Main(args);
    }


    public class FilesStaticAnalyzeListBoxItem {
        public string Name { get; set; }
        public string Value { get; set; }
        public string Info { get; set; }
        public override string ToString() { return Name; }
    }
}
