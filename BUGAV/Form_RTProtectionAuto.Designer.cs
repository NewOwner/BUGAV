namespace BUGAV {
    partial class Form_RTProtectionAuto {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_RTProtectionAuto));
            this.RTAuto_NMF_Button = new DarkUI.Controls.DarkButton();
            this.RTAuto_notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.SuspendLayout();
            // 
            // RTAuto_NMF_Button
            // 
            this.RTAuto_NMF_Button.Location = new System.Drawing.Point(13, 13);
            this.RTAuto_NMF_Button.Name = "RTAuto_NMF_Button";
            this.RTAuto_NMF_Button.Padding = new System.Windows.Forms.Padding(5);
            this.RTAuto_NMF_Button.Size = new System.Drawing.Size(144, 23);
            this.RTAuto_NMF_Button.TabIndex = 0;
            this.RTAuto_NMF_Button.Text = "New Malware Files OFF";
            this.RTAuto_NMF_Button.Click += new System.EventHandler(this.darkButton1_Click);
            // 
            // RTAuto_notifyIcon
            // 
            this.RTAuto_notifyIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.RTAuto_notifyIcon.BalloonTipText = "sdf";
            this.RTAuto_notifyIcon.BalloonTipTitle = "sdfsd";
            this.RTAuto_notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("RTAuto_notifyIcon.Icon")));
            this.RTAuto_notifyIcon.Text = "RTAuto_notifyIcon";
            // 
            // Form_RTProtectionAuto
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.RTAuto_NMF_Button);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_RTProtectionAuto";
            this.Text = "Form_RTProtectionAuto";
            this.ResumeLayout(false);

        }

        #endregion

        private DarkUI.Controls.DarkButton RTAuto_NMF_Button;
        public System.Windows.Forms.NotifyIcon RTAuto_notifyIcon;
    }
}