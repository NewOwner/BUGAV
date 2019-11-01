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
    public partial class Form_FilterRegistry : DarkForm {
        FilterRegConfig __FilterRegConfig;
        public Form_FilterRegistry() {
            InitializeComponent();
        }

        private void FilterRegistry_Button_AddRegKey_Click(object sender, EventArgs e) {

        }

        private void FilterRegistry_Button_DeleteRegKey_Click(object sender, EventArgs e) {

        }

        private void FilterRegistry_Button_Activate_Click(object sender, EventArgs e) {

        }
    }

    public class FilterRegConfig {
        System.Windows.Forms.CheckedListBox KeysList;
        string ConfigPath { get; set; }
        public FilterRegConfig(System.Windows.Forms.CheckedListBox _KeysList) {
            ConfigPath = @"E:\bugav_registryfilter.txt";
            using (var stream = File.Open(ConfigPath, FileMode.Create)) { }
            KeysList = _KeysList;
        }
        public void UpdateConfig() {
            File.WriteAllText(ConfigPath, string.Empty);
            using (StreamWriter file = new StreamWriter(ConfigPath)) {
                foreach (var item in KeysList.Items.OfType<FilesListBoxItem>().ToList()) {
                    file.WriteLine(item.Value);
                }
            }

        }

    }
}
