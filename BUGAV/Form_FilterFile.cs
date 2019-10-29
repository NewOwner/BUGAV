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

namespace BUGAV {
    public partial class Form_FilterFile : DarkForm {
        public Form_FilterFile() {
            InitializeComponent();
        }

        //private void Filter_Button_AddFile_Click(object sender, EventArgs e) {
        //    var fileContent = string.Empty;
        //    var filePath = string.Empty;
        //
        //    using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
        //        openFileDialog.InitialDirectory = "c:\\";
        //        openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
        //        openFileDialog.FilterIndex = 2;
        //        openFileDialog.RestoreDirectory = true;
        //
        //        if (openFileDialog.ShowDialog() == DialogResult.OK) {
        //            filePath = openFileDialog.FileName;
        //            var fileStream = openFileDialog.OpenFile();
        //            using (StreamReader reader = new StreamReader(fileStream)) {
        //                fileContent = reader.ReadToEnd();
        //            }
        //        }
        //    }
        //
        //    MessageBox.Show(fileContent, "File Content at path: " + filePath, MessageBoxButtons.OK);
        //}

    }
}
