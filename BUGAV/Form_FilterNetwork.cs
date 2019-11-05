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
            newRuleForm.ptrParentForm = this;
            newRuleForm.Show();
        }

        private void FilterNetwork_Button_Activate_Click(object sender, EventArgs e) {
            __NetworkWrapInst.WRAP_FilterNetworkDrv_OpenDevice();
        }

        private void FilterNetwork_Button_DeleteRule_Click(object sender, EventArgs e) {
            foreach (var item in FilterNetwork_checkedListBox_Rules.CheckedItems.OfType<RulesListBoxItem>().ToList()) {
                FilterNetwork_checkedListBox_Rules.Items.Remove(item);
            }
            __NetworkConfigInst.UpdateConfig();
            __NetworkWrapInst.WRAP_FilterNetworkDrv_UpdateConfig();
        }

        public void InsertNetRule(NetRule _newRule) {
            FilterNetwork_checkedListBox_Rules.Items.Insert(0, new RulesListBoxItem { Name = _newRule.ruleName, Value = _newRule.ruleBytes });
            __NetworkConfigInst.UpdateConfig();
            //__NetworkWrapInst.WRAP_FilterNetworkDrv_UpdateConfig();
        }
    }

    public class RulesListBoxItem {
        public string Name { get; set; }
        public IEnumerable<byte> Value { get; set; }
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
            List<byte> res_bytes = new List<byte>();
            foreach (var item in RuleList.Items.OfType<RulesListBoxItem>().ToList()) {
                res_bytes.AddRange(item.Value);
            }
            res_bytes.Add((byte)0xff);
            Console.WriteLine(BitConverter.ToString(res_bytes.ToArray()));
            byte[] arr = res_bytes.ToArray();
            File.WriteAllBytes(ConfigPath, arr);
        }

    }

}
