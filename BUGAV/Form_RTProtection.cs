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

using System.Threading;

namespace BUGAV {
    public partial class Form_RTProtection : DarkForm {
        RtProtectionWrap __RtProtectionInst;
        Thread __procMonThread;
        public Form_RTProtection() {
            InitializeComponent();
            try {
                __RtProtectionInst = new RtProtectionWrap();
            } catch (Exception e) {
                MessageBox.Show(e.ToString());
                Console.WriteLine("{0} Exception caught.", e.ToString());
            }
        }
        private void RTProtection_Button_Activate_Click(object sender, EventArgs e) {
            if(RTProtection_Button_Activate.Text == "Activate") {
                __RtProtectionInst.WRAP_RtProtectionDrv_LoadDriver();
                if(__RtProtectionInst.Get_loaded() == true) {
                    RTProtection_Button_Activate.Text = "Deactivate";
                    //__procMonThread = new Thread(new ThreadStart(ProcMonThreadFunc));
                    //__procMonThread.Start();
                }
            
            } else {
                __RtProtectionInst.WRAP_RtProtectionDrv_UnloadDriver();
                if (__RtProtectionInst.Get_loaded() == false) {
                    RTProtection_Button_Activate.Text = "Activate";
                    //__procMonThread.Abort();
                }
            }
        }
        public void ProcMonThreadFunc() {
            while (true) {
                __RtProtectionInst.WRAP_RtProtectionDrv_NewProcMon();
            }
        }

    }
}
