namespace BUGAV {
    partial class Form_StaticAnalyze {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_StaticAnalyze));
            this.StaticAnalyze_TextBox_Info = new DarkUI.Controls.DarkTextBox();
            this.StaticAnalyze_Button_ScanCs = new DarkUI.Controls.DarkButton();
            this.StaticAnalyze_Button_DeleteFile = new DarkUI.Controls.DarkButton();
            this.StaticAnalyze_Button_AddFile = new DarkUI.Controls.DarkButton();
            this.darkLabel5 = new DarkUI.Controls.DarkLabel();
            this.StaticAnalyze_checkedListBox_Files = new System.Windows.Forms.CheckedListBox();
            this.StaticAnalyze_Button_ScanCpp = new DarkUI.Controls.DarkButton();
            this.StaticAnalyze_notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.SuspendLayout();
            // 
            // StaticAnalyze_TextBox_Info
            // 
            this.StaticAnalyze_TextBox_Info.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.StaticAnalyze_TextBox_Info.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.StaticAnalyze_TextBox_Info.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.StaticAnalyze_TextBox_Info.Location = new System.Drawing.Point(12, 215);
            this.StaticAnalyze_TextBox_Info.Multiline = true;
            this.StaticAnalyze_TextBox_Info.Name = "StaticAnalyze_TextBox_Info";
            this.StaticAnalyze_TextBox_Info.Size = new System.Drawing.Size(644, 153);
            this.StaticAnalyze_TextBox_Info.TabIndex = 22;
            // 
            // StaticAnalyze_Button_ScanCs
            // 
            this.StaticAnalyze_Button_ScanCs.Location = new System.Drawing.Point(500, 14);
            this.StaticAnalyze_Button_ScanCs.Name = "StaticAnalyze_Button_ScanCs";
            this.StaticAnalyze_Button_ScanCs.Padding = new System.Windows.Forms.Padding(5);
            this.StaticAnalyze_Button_ScanCs.Size = new System.Drawing.Size(75, 23);
            this.StaticAnalyze_Button_ScanCs.TabIndex = 20;
            this.StaticAnalyze_Button_ScanCs.Text = "Scan .Net";
            this.StaticAnalyze_Button_ScanCs.Click += new System.EventHandler(this.StaticAnalyze_Button_ScanCs_Click);
            // 
            // StaticAnalyze_Button_DeleteFile
            // 
            this.StaticAnalyze_Button_DeleteFile.Location = new System.Drawing.Point(419, 14);
            this.StaticAnalyze_Button_DeleteFile.Name = "StaticAnalyze_Button_DeleteFile";
            this.StaticAnalyze_Button_DeleteFile.Padding = new System.Windows.Forms.Padding(5);
            this.StaticAnalyze_Button_DeleteFile.Size = new System.Drawing.Size(75, 23);
            this.StaticAnalyze_Button_DeleteFile.TabIndex = 15;
            this.StaticAnalyze_Button_DeleteFile.Text = "Delete";
            this.StaticAnalyze_Button_DeleteFile.Click += new System.EventHandler(this.StaticAnalyze_Button_DeleteFile_Click);
            // 
            // StaticAnalyze_Button_AddFile
            // 
            this.StaticAnalyze_Button_AddFile.Location = new System.Drawing.Point(338, 14);
            this.StaticAnalyze_Button_AddFile.Name = "StaticAnalyze_Button_AddFile";
            this.StaticAnalyze_Button_AddFile.Padding = new System.Windows.Forms.Padding(5);
            this.StaticAnalyze_Button_AddFile.Size = new System.Drawing.Size(75, 23);
            this.StaticAnalyze_Button_AddFile.TabIndex = 14;
            this.StaticAnalyze_Button_AddFile.Text = "Add";
            this.StaticAnalyze_Button_AddFile.Click += new System.EventHandler(this.StaticAnalyze_Button_AddFile_Click);
            // 
            // darkLabel5
            // 
            this.darkLabel5.AutoSize = true;
            this.darkLabel5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel5.Location = new System.Drawing.Point(9, 19);
            this.darkLabel5.Name = "darkLabel5";
            this.darkLabel5.Size = new System.Drawing.Size(56, 13);
            this.darkLabel5.TabIndex = 13;
            this.darkLabel5.Text = "Select File";
            // 
            // StaticAnalyze_checkedListBox_Files
            // 
            this.StaticAnalyze_checkedListBox_Files.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.StaticAnalyze_checkedListBox_Files.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.StaticAnalyze_checkedListBox_Files.FormattingEnabled = true;
            this.StaticAnalyze_checkedListBox_Files.Location = new System.Drawing.Point(12, 40);
            this.StaticAnalyze_checkedListBox_Files.Name = "StaticAnalyze_checkedListBox_Files";
            this.StaticAnalyze_checkedListBox_Files.Size = new System.Drawing.Size(644, 169);
            this.StaticAnalyze_checkedListBox_Files.TabIndex = 12;
            this.StaticAnalyze_checkedListBox_Files.SelectedIndexChanged += new System.EventHandler(this.StaticAnalyze_checkedListBox_Files_SelectedIndexChanged);
            // 
            // StaticAnalyze_Button_ScanCpp
            // 
            this.StaticAnalyze_Button_ScanCpp.Location = new System.Drawing.Point(581, 14);
            this.StaticAnalyze_Button_ScanCpp.Name = "StaticAnalyze_Button_ScanCpp";
            this.StaticAnalyze_Button_ScanCpp.Padding = new System.Windows.Forms.Padding(5);
            this.StaticAnalyze_Button_ScanCpp.Size = new System.Drawing.Size(75, 23);
            this.StaticAnalyze_Button_ScanCpp.TabIndex = 23;
            this.StaticAnalyze_Button_ScanCpp.Text = "Scan C++";
            this.StaticAnalyze_Button_ScanCpp.Click += new System.EventHandler(this.StaticAnalyze_Button_ScanCpp_Click);
            // 
            // StaticAnalyze_notifyIcon
            // 
            this.StaticAnalyze_notifyIcon.Text = "notifyIcon1";
            // 
            // Form_StaticAnalyze
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(677, 397);
            this.Controls.Add(this.StaticAnalyze_Button_ScanCpp);
            this.Controls.Add(this.StaticAnalyze_TextBox_Info);
            this.Controls.Add(this.StaticAnalyze_Button_ScanCs);
            this.Controls.Add(this.StaticAnalyze_Button_DeleteFile);
            this.Controls.Add(this.StaticAnalyze_Button_AddFile);
            this.Controls.Add(this.darkLabel5);
            this.Controls.Add(this.StaticAnalyze_checkedListBox_Files);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_StaticAnalyze";
            this.Text = "Form_StaticAnalyze";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkTextBox StaticAnalyze_TextBox_Info;
        private DarkUI.Controls.DarkButton StaticAnalyze_Button_ScanCs;
        private DarkUI.Controls.DarkButton StaticAnalyze_Button_DeleteFile;
        private DarkUI.Controls.DarkButton StaticAnalyze_Button_AddFile;
        private DarkUI.Controls.DarkLabel darkLabel5;
        private System.Windows.Forms.CheckedListBox StaticAnalyze_checkedListBox_Files;
        private DarkUI.Controls.DarkButton StaticAnalyze_Button_ScanCpp;
        private System.Windows.Forms.NotifyIcon StaticAnalyze_notifyIcon;
    }
}