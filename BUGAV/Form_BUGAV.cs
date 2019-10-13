using System;
using System.IO;
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
    public partial class Form_BUGAV : DarkForm {
        public Form_BUGAV() {
            InitializeComponent();
        }

        // GENERAL

        private void filterToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_Filter.Visible = true;
        }

        private void staticAnalyzisToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_StaticAnalysis.Visible = true;
        }

        private void realtimeProtectionToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_RealtimeProtection.Visible = true;
        }

        private void cloudScanToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_CloudScan.Visible = true;
        }

        private void networkProtectionToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_NetworkProtection.Visible = true;
        }

        private void infoToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_Info.Visible = true;
        }

        private void groupBoxInvisibleAll() {
            groupBox_Filter.Visible = false;
            groupBox_StaticAnalysis.Visible = false;
            groupBox_RealtimeProtection.Visible = false;
            groupBox_CloudScan.Visible = false;
            groupBox_NetworkProtection.Visible = false;
            groupBox_Info.Visible = false;
        }


        //FILTER

        private void Filter_Button_AddFile_Click(object sender, EventArgs e) {
            var fileContent = string.Empty;
            var filePath = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog()) {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK) {
                    filePath = openFileDialog.FileName;
                    var fileStream = openFileDialog.OpenFile();
                    using (StreamReader reader = new StreamReader(fileStream)) {
                        fileContent = reader.ReadToEnd();
                    }
                }
            }

            MessageBox.Show(fileContent, "File Content at path: " + filePath, MessageBoxButtons.OK);
        }

        private void Filter_Button_AddRegKey_Click(object sender, EventArgs e) {

        }
    }
}
