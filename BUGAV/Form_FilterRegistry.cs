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
using Microsoft.Win32;

namespace BUGAV {
    public partial class Form_FilterRegistry : DarkForm {
        FilterRegConfig __RegConfig;
        FilterRegistryWrap __RegistryWrap;
        public Form_FilterRegistry() {
            InitializeComponent();
            __RegConfig = new FilterRegConfig(FilterRegistry_checkedListBox_RegKeys);
            try {
                __RegistryWrap = new FilterRegistryWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }

        private void FilterRegistry_Button_AddRegKey_Click(object sender, EventArgs e) {
            //HKEY_LOCAL_MACHINE\SOFTWARE\Google\Chrome
            // RegFltr: Use ed nt!Kd_IHVDRIVER_Mask 8 to enable more detailed printouts windbg

            string keystr = string.Empty;
            string rootkey = string.Empty;
            string valstr = string.Empty;

            keystr = FilterRegistry_TextBox_RegKey.Text.ToUpper();
            keystr = FilterRegistry_TextBox_RegKey.Text;
            if (keystr == string.Empty) { return; }
            rootkey = GetUntilOrEmpty(keystr);
            valstr = GetAfterOrEmpty(keystr);
            RegistryKey subkey = null;
            if (rootkey == "HKEY_CLASSES_ROOT") { subkey = Registry.ClassesRoot.OpenSubKey(valstr); } else
            if (rootkey == "HKEY_CURRENT_USER") { subkey = Registry.CurrentUser.OpenSubKey(valstr); } else
            if (rootkey == "HKEY_LOCAL_MACHINE") { subkey = Registry.LocalMachine.OpenSubKey(valstr); } else
            if (rootkey == "HKEY_USERS") { subkey = Registry.Users.OpenSubKey(valstr); } else
            if (rootkey == "HKEY_CURRENT_CONFIG") { subkey = Registry.CurrentConfig.OpenSubKey(valstr); }
            if (subkey == null) { return; }

            FilterRegistry_checkedListBox_RegKeys.Items.Insert(0, new FilesListBoxItem { Name = keystr, Value = keystr });
            __RegConfig.UpdateConfig();
            __RegistryWrap.WRAP_FilterRegistryDrv_UpdateConfig();
        }

        private void FilterRegistry_Button_DeleteRegKey_Click(object sender, EventArgs e) {
            foreach (var item in FilterRegistry_checkedListBox_RegKeys.CheckedItems.OfType<FilesListBoxItem>().ToList()) {
                FilterRegistry_checkedListBox_RegKeys.Items.Remove(item);
            }
            __RegConfig.UpdateConfig();
            __RegistryWrap.WRAP_FilterRegistryDrv_UpdateConfig();
        }

        private void FilterRegistry_Button_Activate_Click(object sender, EventArgs e) {
            if(FilterRegistry_Button_Activate.Text == "Activate") {
                __RegistryWrap.WRAP_FilterRegistryDrv_LoadDriver();
                __RegistryWrap.WRAP_FilterRegistryDrv_RegisterCallback();
                if (__RegistryWrap.Get_loaded() == true) {
                    __RegistryWrap.WRAP_FilterRegistryDrv_TestCallbacks();
                    FilterRegistry_Button_Activate.Text = "Deactivate";
                }
            
            } else {
                __RegistryWrap.WRAP_FilterRegistryDrv_UnregisterCallback();
                __RegistryWrap.WRAP_FilterRegistryDrv_UnloadDriver();
                if (__RegistryWrap.Get_loaded() == false) {
                    FilterRegistry_Button_Activate.Text = "Activate";
                }
            }
        }

        public string GetUntilOrEmpty(string text, string stopAt = @"\") {
            if (!string.IsNullOrWhiteSpace(text)) {
                int charLocation = text.IndexOf(stopAt, StringComparison.Ordinal);
                if (charLocation > 0) { return text.Substring(0, charLocation); }
            }
            return string.Empty;
        }
        public string GetAfterOrEmpty(string text, string stopAt = @"\") {
            if (!string.IsNullOrWhiteSpace(text)) {
                int charLocation = text.IndexOf(stopAt, StringComparison.Ordinal);
                if (charLocation > 0) { return text.Substring(charLocation+1); }
            }
            return string.Empty;
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
