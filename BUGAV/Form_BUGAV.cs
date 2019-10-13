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
    public partial class Form_BUGAV : DarkForm {
        public Form_BUGAV() {
            InitializeComponent();
        }

        private void controlToolStripMenuItem_Click(object sender, EventArgs e) {
            groupBoxInvisibleAll();
            groupBox_Control.Visible = true;
        }

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
            groupBox_Control.Visible = false;
            groupBox_Filter.Visible = false;
            groupBox_StaticAnalysis.Visible = false;
            groupBox_RealtimeProtection.Visible = false;
            groupBox_CloudScan.Visible = false;
            groupBox_NetworkProtection.Visible = false;
            groupBox_Info.Visible = false;
        }
    }
}
