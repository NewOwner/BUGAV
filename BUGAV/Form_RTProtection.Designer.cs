namespace BUGAV {
    partial class Form_RTProtection {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_RTProtection));
            this.RTProtection_Button_HookBasic = new DarkUI.Controls.DarkButton();
            this.RTProtection_TextBox_ProcessInfo = new DarkUI.Controls.DarkTextBox();
            this.RTProtection_Button_Update = new DarkUI.Controls.DarkButton();
            this.RTProtection_checkedListBox_Processes = new System.Windows.Forms.CheckedListBox();
            this.RTProtection_Button_Activate = new DarkUI.Controls.DarkButton();
            this.darkLabel1 = new DarkUI.Controls.DarkLabel();
            this.RTProtection_Button_Auto = new DarkUI.Controls.DarkButton();
            this.RTProtection_notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.RTProtection_Button_HookWinhttp = new DarkUI.Controls.DarkButton();
            this.RTProtection_Button_HookWininet = new DarkUI.Controls.DarkButton();
            this.RTProtection_Button_HookWs2_32 = new DarkUI.Controls.DarkButton();
            this.darkButton1 = new DarkUI.Controls.DarkButton();
            this.RTProtection_Button_HookConsole = new DarkUI.Controls.DarkButton();
            this.RTProtection_TextBox_Filter = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // RTProtection_Button_HookBasic
            // 
            this.RTProtection_Button_HookBasic.Location = new System.Drawing.Point(24, 34);
            this.RTProtection_Button_HookBasic.Name = "RTProtection_Button_HookBasic";
            this.RTProtection_Button_HookBasic.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_HookBasic.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_HookBasic.TabIndex = 6;
            this.RTProtection_Button_HookBasic.Text = "Hook Basic";
            this.RTProtection_Button_HookBasic.Click += new System.EventHandler(this.RTProtection_Button_Hook_Click);
            // 
            // RTProtection_TextBox_ProcessInfo
            // 
            this.RTProtection_TextBox_ProcessInfo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.RTProtection_TextBox_ProcessInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RTProtection_TextBox_ProcessInfo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.RTProtection_TextBox_ProcessInfo.Location = new System.Drawing.Point(455, 11);
            this.RTProtection_TextBox_ProcessInfo.Multiline = true;
            this.RTProtection_TextBox_ProcessInfo.Name = "RTProtection_TextBox_ProcessInfo";
            this.RTProtection_TextBox_ProcessInfo.Size = new System.Drawing.Size(247, 372);
            this.RTProtection_TextBox_ProcessInfo.TabIndex = 5;
            // 
            // RTProtection_Button_Update
            // 
            this.RTProtection_Button_Update.Location = new System.Drawing.Point(24, 302);
            this.RTProtection_Button_Update.Name = "RTProtection_Button_Update";
            this.RTProtection_Button_Update.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_Update.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_Update.TabIndex = 4;
            this.RTProtection_Button_Update.Text = "Update";
            this.RTProtection_Button_Update.Click += new System.EventHandler(this.RTProtection_Button_Update_Click);
            // 
            // RTProtection_checkedListBox_Processes
            // 
            this.RTProtection_checkedListBox_Processes.FormattingEnabled = true;
            this.RTProtection_checkedListBox_Processes.Location = new System.Drawing.Point(116, 34);
            this.RTProtection_checkedListBox_Processes.Name = "RTProtection_checkedListBox_Processes";
            this.RTProtection_checkedListBox_Processes.Size = new System.Drawing.Size(333, 349);
            this.RTProtection_checkedListBox_Processes.TabIndex = 8;
            // 
            // RTProtection_Button_Activate
            // 
            this.RTProtection_Button_Activate.Location = new System.Drawing.Point(24, 360);
            this.RTProtection_Button_Activate.Name = "RTProtection_Button_Activate";
            this.RTProtection_Button_Activate.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_Activate.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_Activate.TabIndex = 9;
            this.RTProtection_Button_Activate.Text = "Activate";
            this.RTProtection_Button_Activate.Click += new System.EventHandler(this.RTProtection_Button_Activate_Click);
            // 
            // darkLabel1
            // 
            this.darkLabel1.AutoSize = true;
            this.darkLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel1.Location = new System.Drawing.Point(32, 13);
            this.darkLabel1.Name = "darkLabel1";
            this.darkLabel1.Size = new System.Drawing.Size(81, 13);
            this.darkLabel1.TabIndex = 10;
            this.darkLabel1.Text = "New Processes";
            // 
            // RTProtection_Button_Auto
            // 
            this.RTProtection_Button_Auto.Location = new System.Drawing.Point(24, 331);
            this.RTProtection_Button_Auto.Name = "RTProtection_Button_Auto";
            this.RTProtection_Button_Auto.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_Auto.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_Auto.TabIndex = 11;
            this.RTProtection_Button_Auto.Text = "Auto";
            // 
            // RTProtection_notifyIcon
            // 
            this.RTProtection_notifyIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.RTProtection_notifyIcon.BalloonTipText = "sdf";
            this.RTProtection_notifyIcon.BalloonTipTitle = "adsfsf";
            this.RTProtection_notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("RTProtection_notifyIcon.Icon")));
            this.RTProtection_notifyIcon.Text = "notifyIcon1";
            this.RTProtection_notifyIcon.MouseClick += new System.Windows.Forms.MouseEventHandler(this.RTProtection_notifyIcon_MouseClick);
            // 
            // RTProtection_Button_HookWinhttp
            // 
            this.RTProtection_Button_HookWinhttp.Location = new System.Drawing.Point(24, 63);
            this.RTProtection_Button_HookWinhttp.Name = "RTProtection_Button_HookWinhttp";
            this.RTProtection_Button_HookWinhttp.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_HookWinhttp.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_HookWinhttp.TabIndex = 12;
            this.RTProtection_Button_HookWinhttp.Text = "Hook Winhttp";
            this.RTProtection_Button_HookWinhttp.Click += new System.EventHandler(this.RTProtection_Button_HookWinhttp_Click);
            // 
            // RTProtection_Button_HookWininet
            // 
            this.RTProtection_Button_HookWininet.Location = new System.Drawing.Point(24, 92);
            this.RTProtection_Button_HookWininet.Name = "RTProtection_Button_HookWininet";
            this.RTProtection_Button_HookWininet.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_HookWininet.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_HookWininet.TabIndex = 13;
            this.RTProtection_Button_HookWininet.Text = "Hook Wininet";
            this.RTProtection_Button_HookWininet.Click += new System.EventHandler(this.RTProtection_Button_HookWininet_Click);
            // 
            // RTProtection_Button_HookWs2_32
            // 
            this.RTProtection_Button_HookWs2_32.Location = new System.Drawing.Point(24, 121);
            this.RTProtection_Button_HookWs2_32.Name = "RTProtection_Button_HookWs2_32";
            this.RTProtection_Button_HookWs2_32.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_HookWs2_32.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_HookWs2_32.TabIndex = 14;
            this.RTProtection_Button_HookWs2_32.Text = "Hook Ws2_32";
            this.RTProtection_Button_HookWs2_32.Click += new System.EventHandler(this.RTProtection_Button_HookWs2_32_Click);
            // 
            // darkButton1
            // 
            this.darkButton1.Location = new System.Drawing.Point(24, 273);
            this.darkButton1.Name = "darkButton1";
            this.darkButton1.Padding = new System.Windows.Forms.Padding(5);
            this.darkButton1.Size = new System.Drawing.Size(86, 23);
            this.darkButton1.TabIndex = 15;
            this.darkButton1.Text = "Terminate";
            // 
            // RTProtection_Button_HookConsole
            // 
            this.RTProtection_Button_HookConsole.Location = new System.Drawing.Point(24, 150);
            this.RTProtection_Button_HookConsole.Name = "RTProtection_Button_HookConsole";
            this.RTProtection_Button_HookConsole.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_HookConsole.Size = new System.Drawing.Size(86, 23);
            this.RTProtection_Button_HookConsole.TabIndex = 16;
            this.RTProtection_Button_HookConsole.Text = "Hook Console";
            this.RTProtection_Button_HookConsole.Click += new System.EventHandler(this.RTProtection_Button_HookConsole_Click);
            // 
            // RTProtection_TextBox_Filter
            // 
            this.RTProtection_TextBox_Filter.Location = new System.Drawing.Point(116, 13);
            this.RTProtection_TextBox_Filter.Name = "RTProtection_TextBox_Filter";
            this.RTProtection_TextBox_Filter.Size = new System.Drawing.Size(333, 20);
            this.RTProtection_TextBox_Filter.TabIndex = 17;
            this.RTProtection_TextBox_Filter.Text = "powershell";
            // 
            // Form_RTProtection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(723, 397);
            this.Controls.Add(this.RTProtection_TextBox_Filter);
            this.Controls.Add(this.RTProtection_Button_HookConsole);
            this.Controls.Add(this.darkButton1);
            this.Controls.Add(this.RTProtection_Button_HookWs2_32);
            this.Controls.Add(this.RTProtection_Button_HookWininet);
            this.Controls.Add(this.RTProtection_Button_HookWinhttp);
            this.Controls.Add(this.RTProtection_Button_Auto);
            this.Controls.Add(this.darkLabel1);
            this.Controls.Add(this.RTProtection_Button_Activate);
            this.Controls.Add(this.RTProtection_checkedListBox_Processes);
            this.Controls.Add(this.RTProtection_Button_HookBasic);
            this.Controls.Add(this.RTProtection_TextBox_ProcessInfo);
            this.Controls.Add(this.RTProtection_Button_Update);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_RTProtection";
            this.Text = "Form_RTProtection";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkButton RTProtection_Button_HookBasic;
        private DarkUI.Controls.DarkTextBox RTProtection_TextBox_ProcessInfo;
        private DarkUI.Controls.DarkButton RTProtection_Button_Update;
        private System.Windows.Forms.CheckedListBox RTProtection_checkedListBox_Processes;
        private DarkUI.Controls.DarkButton RTProtection_Button_Activate;
        private DarkUI.Controls.DarkLabel darkLabel1;
        private DarkUI.Controls.DarkButton RTProtection_Button_Auto;
        public System.Windows.Forms.NotifyIcon RTProtection_notifyIcon;
        private DarkUI.Controls.DarkButton RTProtection_Button_HookWinhttp;
        private DarkUI.Controls.DarkButton RTProtection_Button_HookWininet;
        private DarkUI.Controls.DarkButton RTProtection_Button_HookWs2_32;
        private DarkUI.Controls.DarkButton darkButton1;
        private DarkUI.Controls.DarkButton RTProtection_Button_HookConsole;
        private System.Windows.Forms.TextBox RTProtection_TextBox_Filter;
    }
}