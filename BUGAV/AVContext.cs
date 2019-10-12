using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BUGAV {
    public class AVContext : ApplicationContext {
        NotifyIcon notifyIcon = new NotifyIcon();
        Form_BUGAV bugav_window = new Form_BUGAV();
        
        public AVContext() {
            MenuItem configMenuItem = new MenuItem("Configuration", new EventHandler(showConfig));
            MenuItem exitMenuItem = new MenuItem("Exit", new EventHandler(Exit));

            notifyIcon.Icon = BUGAV.Properties.Resources.Flat_Halloween_Bug;
            notifyIcon.ContextMenu = new ContextMenu(new MenuItem[] { configMenuItem, exitMenuItem });
            notifyIcon.Visible = true;
        }

        void showConfig(object sender, EventArgs e) {
            if (bugav_window.Visible) {
                bugav_window.Focus();
            } else {
                bugav_window.ShowDialog();
            }
        }
        void Exit(object sender, EventArgs e) {
            notifyIcon.Visible = false;
            Application.Exit();
        }

    }
}
