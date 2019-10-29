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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_RTProtection));
            this.RTProtection_Button_EnableRTP = new DarkUI.Controls.DarkButton();
            this.RTProtection_TextBox_ProcessInfo = new DarkUI.Controls.DarkTextBox();
            this.RTProtection_Button_TerminateProcess = new DarkUI.Controls.DarkButton();
            this.RTProtection_checkedListBox_Processes = new System.Windows.Forms.CheckedListBox();
            this.darkLabel1 = new DarkUI.Controls.DarkLabel();
            this.SuspendLayout();
            // 
            // RTProtection_Button_EnableRTP
            // 
            this.RTProtection_Button_EnableRTP.Location = new System.Drawing.Point(10, 64);
            this.RTProtection_Button_EnableRTP.Name = "RTProtection_Button_EnableRTP";
            this.RTProtection_Button_EnableRTP.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_EnableRTP.Size = new System.Drawing.Size(75, 23);
            this.RTProtection_Button_EnableRTP.TabIndex = 6;
            this.RTProtection_Button_EnableRTP.Text = "Enable RTP";
            // 
            // RTProtection_TextBox_ProcessInfo
            // 
            this.RTProtection_TextBox_ProcessInfo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.RTProtection_TextBox_ProcessInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RTProtection_TextBox_ProcessInfo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.RTProtection_TextBox_ProcessInfo.Location = new System.Drawing.Point(266, 12);
            this.RTProtection_TextBox_ProcessInfo.Multiline = true;
            this.RTProtection_TextBox_ProcessInfo.Name = "RTProtection_TextBox_ProcessInfo";
            this.RTProtection_TextBox_ProcessInfo.Size = new System.Drawing.Size(281, 267);
            this.RTProtection_TextBox_ProcessInfo.TabIndex = 5;
            // 
            // RTProtection_Button_TerminateProcess
            // 
            this.RTProtection_Button_TerminateProcess.Location = new System.Drawing.Point(10, 35);
            this.RTProtection_Button_TerminateProcess.Name = "RTProtection_Button_TerminateProcess";
            this.RTProtection_Button_TerminateProcess.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_TerminateProcess.Size = new System.Drawing.Size(75, 23);
            this.RTProtection_Button_TerminateProcess.TabIndex = 4;
            this.RTProtection_Button_TerminateProcess.Text = "Terminate";
            // 
            // RTProtection_checkedListBox_Processes
            // 
            this.RTProtection_checkedListBox_Processes.FormattingEnabled = true;
            this.RTProtection_checkedListBox_Processes.Location = new System.Drawing.Point(91, 16);
            this.RTProtection_checkedListBox_Processes.Name = "RTProtection_checkedListBox_Processes";
            this.RTProtection_checkedListBox_Processes.Size = new System.Drawing.Size(160, 259);
            this.RTProtection_checkedListBox_Processes.TabIndex = 8;
            // 
            // darkLabel1
            // 
            this.darkLabel1.AutoSize = true;
            this.darkLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel1.Location = new System.Drawing.Point(12, 16);
            this.darkLabel1.Name = "darkLabel1";
            this.darkLabel1.Size = new System.Drawing.Size(41, 13);
            this.darkLabel1.TabIndex = 9;
            this.darkLabel1.Text = "Started";
            // 
            // Form_RTProtection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.darkLabel1);
            this.Controls.Add(this.RTProtection_checkedListBox_Processes);
            this.Controls.Add(this.RTProtection_Button_EnableRTP);
            this.Controls.Add(this.RTProtection_TextBox_ProcessInfo);
            this.Controls.Add(this.RTProtection_Button_TerminateProcess);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_RTProtection";
            this.Text = "Form_RTProtection";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkButton RTProtection_Button_EnableRTP;
        private DarkUI.Controls.DarkTextBox RTProtection_TextBox_ProcessInfo;
        private DarkUI.Controls.DarkButton RTProtection_Button_TerminateProcess;
        private System.Windows.Forms.CheckedListBox RTProtection_checkedListBox_Processes;
        private DarkUI.Controls.DarkLabel darkLabel1;
    }
}