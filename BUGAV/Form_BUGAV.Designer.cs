namespace BUGAV
{
    partial class Form_BUGAV
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_BUGAV));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.controlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.filterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.staticAnalyzisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.realtimeProtectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cloudScanToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.networkProtectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.infoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox_Control = new System.Windows.Forms.GroupBox();
            this.groupBox_Info = new System.Windows.Forms.GroupBox();
            this.darkLabel3 = new DarkUI.Controls.DarkLabel();
            this.darkButton1 = new DarkUI.Controls.DarkButton();
            this.darkLabel2 = new DarkUI.Controls.DarkLabel();
            this.info_label_version = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.darkLabel1 = new DarkUI.Controls.DarkLabel();
            this.groupBox_Filter = new System.Windows.Forms.GroupBox();
            this.Filter_Button_AddRegKey = new DarkUI.Controls.DarkButton();
            this.Filter_Button_AddFile = new DarkUI.Controls.DarkButton();
            this.groupBox_StaticAnalysis = new System.Windows.Forms.GroupBox();
            this.groupBox_RealtimeProtection = new System.Windows.Forms.GroupBox();
            this.groupBox_CloudScan = new System.Windows.Forms.GroupBox();
            this.groupBox_NetworkProtection = new System.Windows.Forms.GroupBox();
            this.Filter_checkedListBox_Files = new System.Windows.Forms.CheckedListBox();
            this.darkLabel4 = new DarkUI.Controls.DarkLabel();
            this.Filter_Button_DeleteFile = new DarkUI.Controls.DarkButton();
            this.label1 = new System.Windows.Forms.Label();
            this.Filter_TextBox_RegKey = new DarkUI.Controls.DarkTextBox();
            this.Filter_Button_DeleteRegKey = new DarkUI.Controls.DarkButton();
            this.Filter_checkedListBox_RegKeys = new System.Windows.Forms.CheckedListBox();
            this.menuStrip1.SuspendLayout();
            this.groupBox_Info.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox_Filter.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.controlToolStripMenuItem,
            this.filterToolStripMenuItem,
            this.staticAnalyzisToolStripMenuItem,
            this.realtimeProtectionToolStripMenuItem,
            this.cloudScanToolStripMenuItem,
            this.networkProtectionToolStripMenuItem,
            this.infoToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(2328, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // controlToolStripMenuItem
            // 
            this.controlToolStripMenuItem.Name = "controlToolStripMenuItem";
            this.controlToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.controlToolStripMenuItem.Text = "control";
            this.controlToolStripMenuItem.Click += new System.EventHandler(this.controlToolStripMenuItem_Click);
            // 
            // filterToolStripMenuItem
            // 
            this.filterToolStripMenuItem.Name = "filterToolStripMenuItem";
            this.filterToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.filterToolStripMenuItem.Text = "filter";
            this.filterToolStripMenuItem.Click += new System.EventHandler(this.filterToolStripMenuItem_Click);
            // 
            // staticAnalyzisToolStripMenuItem
            // 
            this.staticAnalyzisToolStripMenuItem.Name = "staticAnalyzisToolStripMenuItem";
            this.staticAnalyzisToolStripMenuItem.Size = new System.Drawing.Size(94, 20);
            this.staticAnalyzisToolStripMenuItem.Text = "static analysys";
            this.staticAnalyzisToolStripMenuItem.Click += new System.EventHandler(this.staticAnalyzisToolStripMenuItem_Click);
            // 
            // realtimeProtectionToolStripMenuItem
            // 
            this.realtimeProtectionToolStripMenuItem.Name = "realtimeProtectionToolStripMenuItem";
            this.realtimeProtectionToolStripMenuItem.Size = new System.Drawing.Size(120, 20);
            this.realtimeProtectionToolStripMenuItem.Text = "realtime protection";
            this.realtimeProtectionToolStripMenuItem.Click += new System.EventHandler(this.realtimeProtectionToolStripMenuItem_Click);
            // 
            // cloudScanToolStripMenuItem
            // 
            this.cloudScanToolStripMenuItem.Name = "cloudScanToolStripMenuItem";
            this.cloudScanToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.cloudScanToolStripMenuItem.Text = "cloud scan";
            this.cloudScanToolStripMenuItem.Click += new System.EventHandler(this.cloudScanToolStripMenuItem_Click);
            // 
            // networkProtectionToolStripMenuItem
            // 
            this.networkProtectionToolStripMenuItem.Name = "networkProtectionToolStripMenuItem";
            this.networkProtectionToolStripMenuItem.Size = new System.Drawing.Size(120, 20);
            this.networkProtectionToolStripMenuItem.Text = "network protection";
            this.networkProtectionToolStripMenuItem.Click += new System.EventHandler(this.networkProtectionToolStripMenuItem_Click);
            // 
            // infoToolStripMenuItem
            // 
            this.infoToolStripMenuItem.Name = "infoToolStripMenuItem";
            this.infoToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.infoToolStripMenuItem.Text = "info";
            this.infoToolStripMenuItem.Click += new System.EventHandler(this.infoToolStripMenuItem_Click);
            // 
            // groupBox_Control
            // 
            this.groupBox_Control.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_Control.Location = new System.Drawing.Point(1010, 807);
            this.groupBox_Control.Name = "groupBox_Control";
            this.groupBox_Control.Size = new System.Drawing.Size(247, 201);
            this.groupBox_Control.TabIndex = 1;
            this.groupBox_Control.TabStop = false;
            this.groupBox_Control.Text = "Control";
            this.groupBox_Control.Visible = false;
            // 
            // groupBox_Info
            // 
            this.groupBox_Info.Controls.Add(this.darkLabel3);
            this.groupBox_Info.Controls.Add(this.darkButton1);
            this.groupBox_Info.Controls.Add(this.darkLabel2);
            this.groupBox_Info.Controls.Add(this.info_label_version);
            this.groupBox_Info.Controls.Add(this.pictureBox1);
            this.groupBox_Info.Controls.Add(this.darkLabel1);
            this.groupBox_Info.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_Info.Location = new System.Drawing.Point(339, 929);
            this.groupBox_Info.Name = "groupBox_Info";
            this.groupBox_Info.Size = new System.Drawing.Size(259, 135);
            this.groupBox_Info.TabIndex = 2;
            this.groupBox_Info.TabStop = false;
            this.groupBox_Info.Text = "Info";
            // 
            // darkLabel3
            // 
            this.darkLabel3.AutoSize = true;
            this.darkLabel3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel3.Location = new System.Drawing.Point(548, 262);
            this.darkLabel3.Name = "darkLabel3";
            this.darkLabel3.Size = new System.Drawing.Size(50, 13);
            this.darkLabel3.TabIndex = 5;
            this.darkLabel3.Text = "STATUS";
            // 
            // darkButton1
            // 
            this.darkButton1.Location = new System.Drawing.Point(540, 523);
            this.darkButton1.Name = "darkButton1";
            this.darkButton1.Padding = new System.Windows.Forms.Padding(5);
            this.darkButton1.Size = new System.Drawing.Size(88, 23);
            this.darkButton1.TabIndex = 4;
            this.darkButton1.Text = "Check Update";
            // 
            // darkLabel2
            // 
            this.darkLabel2.AutoSize = true;
            this.darkLabel2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel2.Location = new System.Drawing.Point(537, 30);
            this.darkLabel2.Name = "darkLabel2";
            this.darkLabel2.Size = new System.Drawing.Size(62, 13);
            this.darkLabel2.TabIndex = 3;
            this.darkLabel2.Text = "MAIN INFO";
            // 
            // info_label_version
            // 
            this.info_label_version.AutoSize = true;
            this.info_label_version.Location = new System.Drawing.Point(537, 495);
            this.info_label_version.Name = "info_label_version";
            this.info_label_version.Size = new System.Drawing.Size(69, 13);
            this.info_label_version.TabIndex = 2;
            this.info_label_version.Text = "Version 0.0.1";
            // 
            // pictureBox1
            // 
            this.pictureBox1.ImageLocation = "F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\31-5122.png";
            this.pictureBox1.Location = new System.Drawing.Point(20, 30);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(510, 515);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // darkLabel1
            // 
            this.darkLabel1.AutoSize = true;
            this.darkLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel1.Location = new System.Drawing.Point(445, 44);
            this.darkLabel1.Name = "darkLabel1";
            this.darkLabel1.Size = new System.Drawing.Size(60, 13);
            this.darkLabel1.TabIndex = 0;
            this.darkLabel1.Text = "darkLabel1";
            // 
            // groupBox_Filter
            // 
            this.groupBox_Filter.Controls.Add(this.Filter_checkedListBox_RegKeys);
            this.groupBox_Filter.Controls.Add(this.Filter_Button_DeleteRegKey);
            this.groupBox_Filter.Controls.Add(this.Filter_TextBox_RegKey);
            this.groupBox_Filter.Controls.Add(this.label1);
            this.groupBox_Filter.Controls.Add(this.Filter_Button_DeleteFile);
            this.groupBox_Filter.Controls.Add(this.darkLabel4);
            this.groupBox_Filter.Controls.Add(this.Filter_checkedListBox_Files);
            this.groupBox_Filter.Controls.Add(this.Filter_Button_AddRegKey);
            this.groupBox_Filter.Controls.Add(this.Filter_Button_AddFile);
            this.groupBox_Filter.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_Filter.Location = new System.Drawing.Point(12, 36);
            this.groupBox_Filter.Name = "groupBox_Filter";
            this.groupBox_Filter.Size = new System.Drawing.Size(1553, 682);
            this.groupBox_Filter.TabIndex = 3;
            this.groupBox_Filter.TabStop = false;
            this.groupBox_Filter.Text = "Filter";
            this.groupBox_Filter.Visible = false;
            // 
            // Filter_Button_AddRegKey
            // 
            this.Filter_Button_AddRegKey.Location = new System.Drawing.Point(309, 44);
            this.Filter_Button_AddRegKey.Name = "Filter_Button_AddRegKey";
            this.Filter_Button_AddRegKey.Padding = new System.Windows.Forms.Padding(5);
            this.Filter_Button_AddRegKey.Size = new System.Drawing.Size(78, 23);
            this.Filter_Button_AddRegKey.TabIndex = 1;
            this.Filter_Button_AddRegKey.Text = "Add";
            this.Filter_Button_AddRegKey.Click += new System.EventHandler(this.Filter_Button_AddRegKey_Click);
            // 
            // Filter_Button_AddFile
            // 
            this.Filter_Button_AddFile.Location = new System.Drawing.Point(61, 41);
            this.Filter_Button_AddFile.Name = "Filter_Button_AddFile";
            this.Filter_Button_AddFile.Padding = new System.Windows.Forms.Padding(5);
            this.Filter_Button_AddFile.Size = new System.Drawing.Size(65, 23);
            this.Filter_Button_AddFile.TabIndex = 0;
            this.Filter_Button_AddFile.Text = "Add";
            this.Filter_Button_AddFile.Click += new System.EventHandler(this.Filter_Button_AddFile_Click);
            // 
            // groupBox_StaticAnalysis
            // 
            this.groupBox_StaticAnalysis.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_StaticAnalysis.Location = new System.Drawing.Point(91, 807);
            this.groupBox_StaticAnalysis.Name = "groupBox_StaticAnalysis";
            this.groupBox_StaticAnalysis.Size = new System.Drawing.Size(200, 100);
            this.groupBox_StaticAnalysis.TabIndex = 4;
            this.groupBox_StaticAnalysis.TabStop = false;
            this.groupBox_StaticAnalysis.Text = "StaticAnalysis";
            this.groupBox_StaticAnalysis.Visible = false;
            // 
            // groupBox_RealtimeProtection
            // 
            this.groupBox_RealtimeProtection.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_RealtimeProtection.Location = new System.Drawing.Point(317, 807);
            this.groupBox_RealtimeProtection.Name = "groupBox_RealtimeProtection";
            this.groupBox_RealtimeProtection.Size = new System.Drawing.Size(200, 100);
            this.groupBox_RealtimeProtection.TabIndex = 5;
            this.groupBox_RealtimeProtection.TabStop = false;
            this.groupBox_RealtimeProtection.Text = "RealtimeProtection";
            this.groupBox_RealtimeProtection.Visible = false;
            // 
            // groupBox_CloudScan
            // 
            this.groupBox_CloudScan.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_CloudScan.Location = new System.Drawing.Point(560, 807);
            this.groupBox_CloudScan.Name = "groupBox_CloudScan";
            this.groupBox_CloudScan.Size = new System.Drawing.Size(200, 100);
            this.groupBox_CloudScan.TabIndex = 6;
            this.groupBox_CloudScan.TabStop = false;
            this.groupBox_CloudScan.Text = "CloudScan";
            this.groupBox_CloudScan.Visible = false;
            // 
            // groupBox_NetworkProtection
            // 
            this.groupBox_NetworkProtection.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox_NetworkProtection.Location = new System.Drawing.Point(789, 807);
            this.groupBox_NetworkProtection.Name = "groupBox_NetworkProtection";
            this.groupBox_NetworkProtection.Size = new System.Drawing.Size(200, 100);
            this.groupBox_NetworkProtection.TabIndex = 7;
            this.groupBox_NetworkProtection.TabStop = false;
            this.groupBox_NetworkProtection.Text = "NetworkProtection";
            this.groupBox_NetworkProtection.Visible = false;
            // 
            // Filter_checkedListBox_Files
            // 
            this.Filter_checkedListBox_Files.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.Filter_checkedListBox_Files.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.Filter_checkedListBox_Files.FormattingEnabled = true;
            this.Filter_checkedListBox_Files.Location = new System.Drawing.Point(26, 70);
            this.Filter_checkedListBox_Files.Name = "Filter_checkedListBox_Files";
            this.Filter_checkedListBox_Files.Size = new System.Drawing.Size(181, 229);
            this.Filter_checkedListBox_Files.TabIndex = 2;
            // 
            // darkLabel4
            // 
            this.darkLabel4.AutoSize = true;
            this.darkLabel4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel4.Location = new System.Drawing.Point(26, 46);
            this.darkLabel4.Name = "darkLabel4";
            this.darkLabel4.Size = new System.Drawing.Size(28, 13);
            this.darkLabel4.TabIndex = 3;
            this.darkLabel4.Text = "Files";
            // 
            // Filter_Button_DeleteFile
            // 
            this.Filter_Button_DeleteFile.Location = new System.Drawing.Point(132, 41);
            this.Filter_Button_DeleteFile.Name = "Filter_Button_DeleteFile";
            this.Filter_Button_DeleteFile.Padding = new System.Windows.Forms.Padding(5);
            this.Filter_Button_DeleteFile.Size = new System.Drawing.Size(75, 23);
            this.Filter_Button_DeleteFile.TabIndex = 4;
            this.Filter_Button_DeleteFile.Text = "Delete";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(232, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Registry Keys";
            // 
            // Filter_TextBox_RegKey
            // 
            this.Filter_TextBox_RegKey.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.Filter_TextBox_RegKey.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Filter_TextBox_RegKey.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.Filter_TextBox_RegKey.Location = new System.Drawing.Point(235, 73);
            this.Filter_TextBox_RegKey.Name = "Filter_TextBox_RegKey";
            this.Filter_TextBox_RegKey.Size = new System.Drawing.Size(233, 20);
            this.Filter_TextBox_RegKey.TabIndex = 6;
            // 
            // Filter_Button_DeleteRegKey
            // 
            this.Filter_Button_DeleteRegKey.Location = new System.Drawing.Point(393, 44);
            this.Filter_Button_DeleteRegKey.Name = "Filter_Button_DeleteRegKey";
            this.Filter_Button_DeleteRegKey.Padding = new System.Windows.Forms.Padding(5);
            this.Filter_Button_DeleteRegKey.Size = new System.Drawing.Size(75, 23);
            this.Filter_Button_DeleteRegKey.TabIndex = 7;
            this.Filter_Button_DeleteRegKey.Text = "Delete";
            // 
            // Filter_checkedListBox_RegKeys
            // 
            this.Filter_checkedListBox_RegKeys.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.Filter_checkedListBox_RegKeys.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.Filter_checkedListBox_RegKeys.FormattingEnabled = true;
            this.Filter_checkedListBox_RegKeys.Location = new System.Drawing.Point(235, 100);
            this.Filter_checkedListBox_RegKeys.Name = "Filter_checkedListBox_RegKeys";
            this.Filter_checkedListBox_RegKeys.Size = new System.Drawing.Size(233, 199);
            this.Filter_checkedListBox_RegKeys.TabIndex = 8;
            // 
            // Form_BUGAV
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2328, 1121);
            this.Controls.Add(this.groupBox_RealtimeProtection);
            this.Controls.Add(this.groupBox_NetworkProtection);
            this.Controls.Add(this.groupBox_CloudScan);
            this.Controls.Add(this.groupBox_StaticAnalysis);
            this.Controls.Add(this.groupBox_Filter);
            this.Controls.Add(this.groupBox_Info);
            this.Controls.Add(this.groupBox_Control);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form_BUGAV";
            this.Text = "BUGAV";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox_Info.ResumeLayout(false);
            this.groupBox_Info.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox_Filter.ResumeLayout(false);
            this.groupBox_Filter.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem controlToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem filterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem staticAnalyzisToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem realtimeProtectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cloudScanToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem networkProtectionToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox_Control;
        private System.Windows.Forms.GroupBox groupBox_Info;
        private System.Windows.Forms.GroupBox groupBox_Filter;
        private System.Windows.Forms.GroupBox groupBox_StaticAnalysis;
        private System.Windows.Forms.GroupBox groupBox_RealtimeProtection;
        private System.Windows.Forms.GroupBox groupBox_CloudScan;
        private System.Windows.Forms.GroupBox groupBox_NetworkProtection;
        private System.Windows.Forms.ToolStripMenuItem infoToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private DarkUI.Controls.DarkLabel darkLabel1;
        private DarkUI.Controls.DarkButton darkButton1;
        private DarkUI.Controls.DarkLabel darkLabel2;
        private System.Windows.Forms.Label info_label_version;
        private DarkUI.Controls.DarkLabel darkLabel3;
        private DarkUI.Controls.DarkButton Filter_Button_AddRegKey;
        private DarkUI.Controls.DarkButton Filter_Button_AddFile;
        private System.Windows.Forms.CheckedListBox Filter_checkedListBox_Files;
        private System.Windows.Forms.CheckedListBox Filter_checkedListBox_RegKeys;
        private DarkUI.Controls.DarkButton Filter_Button_DeleteRegKey;
        private DarkUI.Controls.DarkTextBox Filter_TextBox_RegKey;
        private System.Windows.Forms.Label label1;
        private DarkUI.Controls.DarkButton Filter_Button_DeleteFile;
        private DarkUI.Controls.DarkLabel darkLabel4;
    }
}

