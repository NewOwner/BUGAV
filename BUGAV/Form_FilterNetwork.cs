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
    public partial class Form_FilterNetwork : DarkForm {
        FilterNetworkConfig __NetworkConfigInst;
        FilterNetworkWrap __NetworkWrapInst;
        public Form_FilterNetwork() {
            InitializeComponent();
            __NetworkConfigInst = new FilterNetworkConfig(FilterNetwork_checkedListBox_Rules);
            try {
                __NetworkWrapInst = new FilterNetworkWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        private void FilterNetwork_Button_CreateRule_Click(object sender, EventArgs e) {
            Form_FilterNetworkRule newRuleForm = new Form_FilterNetworkRule();
            newRuleForm.Show();
        }
    }

    public class RulesListBoxItem {
        public string Name { get; set; }
        IEnumerable<byte> Value { get; set; }
        public override string ToString() { return Name; }
    }
    public class FilterNetworkConfig {
        System.Windows.Forms.CheckedListBox RuleList;
        string ConfigPath { get; set; }
        public FilterNetworkConfig(System.Windows.Forms.CheckedListBox _RuleList) {
            ConfigPath = @"E:\bugav_networkfilter.txt";
            using (var stream = File.Open(ConfigPath, FileMode.Create)) { }
            RuleList = _RuleList;
        }
        public void UpdateConfig() {
            File.WriteAllText(ConfigPath, string.Empty);
            using (StreamWriter file = new StreamWriter(ConfigPath)) {
                foreach (var item in RuleList.Items.OfType<FilesListBoxItem>().ToList()) {
                    file.WriteLine(item.Value);
                }
            }

        }

    }

}
