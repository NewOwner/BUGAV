using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BUGAV {
    public class AVContext : ApplicationContext {
        NotifyIcon notifyIcon = new NotifyIcon();
        Form_DynamicAnalyze form_dynamicanalyze = new Form_DynamicAnalyze();
        Form_StaticAnalyze form_staticanalyze = new Form_StaticAnalyze();
        Form_RTProtectionManual form_rtprotection = new Form_RTProtectionManual();
        Form_RTProtectionAuto form_rtprotectionAuto = new Form_RTProtectionAuto();
        Form_FilterFile form_filterfile = new Form_FilterFile();
        Form_FilterRegistry form_filterregistry = new Form_FilterRegistry();
        Form_FilterNetwork form_filternetwork = new Form_FilterNetwork();
        Form_Info form_info = new Form_Info();

        public AVContext() {
            MenuItem DynamicAnalyze_MenuItem = new MenuItem("Dynamic Analyze", new EventHandler(show_DynamicAnalyze));
            MenuItem StaticAnalyze_MenuItem = new MenuItem("Static Analyze", new EventHandler(show_StaticAnalyze));
            MenuItem RTProtection_MenuItem = new MenuItem("Manual RT Protection", new EventHandler(show_RTProtection));
            MenuItem RTAProtection_MenuItem = new MenuItem("Auto RT Protection", new EventHandler(show_RTAProtection));
            MenuItem FilterFile_MenuItem = new MenuItem("File Filtering", new EventHandler(show_FilterFile));
            MenuItem FilterRegistry_MenuItem = new MenuItem("Registry Filtering", new EventHandler(show_FilterRegistry));
            MenuItem FilterNetwork_MenuItem = new MenuItem("Network Filtering", new EventHandler(show_FilterNetwork));
            MenuItem Info_MenuItem = new MenuItem("Info", new EventHandler(show_Info));
            MenuItem exitMenuItem = new MenuItem("Exit", new EventHandler(Exit));

            notifyIcon.Icon = BUGAV.Properties.Resources.Flat_Halloween_Bug;
            notifyIcon.ContextMenu = new ContextMenu(new MenuItem[] { 
                DynamicAnalyze_MenuItem, 
                StaticAnalyze_MenuItem, 
                RTProtection_MenuItem,
                RTAProtection_MenuItem,
                FilterFile_MenuItem,
                FilterRegistry_MenuItem,
                FilterNetwork_MenuItem,
                Info_MenuItem,
                exitMenuItem });
            notifyIcon.Visible = true;
        }

        void show_DynamicAnalyze(object sender, EventArgs e) {
            if (form_dynamicanalyze.Visible) {
                form_dynamicanalyze.Focus();
            } else {
                form_dynamicanalyze.ShowDialog();
            }
        }
        void show_StaticAnalyze(object sender, EventArgs e) {
            if (form_staticanalyze.Visible) {
                form_staticanalyze.Focus();
            } else {
                form_staticanalyze.ShowDialog();
            }
        }
        void show_RTProtection(object sender, EventArgs e) {
            if (form_rtprotection.Visible) {
                form_rtprotection.Focus();
            } else {
                form_rtprotection.ShowDialog();
            }
        }
        void show_RTAProtection(object sender, EventArgs e) {
            if (form_rtprotectionAuto.Visible) {
                form_rtprotectionAuto.Focus();
            } else {
                form_rtprotectionAuto.ShowDialog();
            }
        }
        void show_FilterFile(object sender, EventArgs e) {
            if (form_filterfile.Visible) {
                form_filterfile.Focus();
            } else {
                form_filterfile.ShowDialog();
            }
        }
        void show_FilterRegistry(object sender, EventArgs e) {
            if (form_filterregistry.Visible) {
                form_filterregistry.Focus();
            } else {
                form_filterregistry.ShowDialog();
            }
        }
        void show_FilterNetwork(object sender, EventArgs e) {
            if (form_filternetwork.Visible) {
                form_filternetwork.Focus();
            } else {
                form_filternetwork.ShowDialog();
            }
        }
        void show_Info(object sender, EventArgs e) {
            if (form_info.Visible) {
                form_info.Focus();
            } else {
                form_info.ShowDialog();
            }
        }
        void Exit(object sender, EventArgs e) {
            notifyIcon.Visible = false;
            Application.Exit();
        }
    }
}
