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
            this.RTProtection_Button_Hook = new DarkUI.Controls.DarkButton();
            this.RTProtection_TextBox_ProcessInfo = new DarkUI.Controls.DarkTextBox();
            this.RTProtection_Button_TerminateProcess = new DarkUI.Controls.DarkButton();
            this.RTProtection_checkedListBox_Processes = new System.Windows.Forms.CheckedListBox();
            this.RTProtection_Button_Activate = new DarkUI.Controls.DarkButton();
            this.SuspendLayout();
            // 
            // RTProtection_Button_Hook
            // 
            this.RTProtection_Button_Hook.Location = new System.Drawing.Point(10, 96);
            this.RTProtection_Button_Hook.Name = "RTProtection_Button_Hook";
            this.RTProtection_Button_Hook.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_Hook.Size = new System.Drawing.Size(75, 23);
            this.RTProtection_Button_Hook.TabIndex = 6;
            this.RTProtection_Button_Hook.Text = "Hook";
            this.RTProtection_Button_Hook.Click += new System.EventHandler(this.RTProtection_Button_Hook_Click);
            // 
            // RTProtection_TextBox_ProcessInfo
            // 
            this.RTProtection_TextBox_ProcessInfo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.RTProtection_TextBox_ProcessInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RTProtection_TextBox_ProcessInfo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.RTProtection_TextBox_ProcessInfo.Location = new System.Drawing.Point(433, 16);
            this.RTProtection_TextBox_ProcessInfo.Multiline = true;
            this.RTProtection_TextBox_ProcessInfo.Name = "RTProtection_TextBox_ProcessInfo";
            this.RTProtection_TextBox_ProcessInfo.Size = new System.Drawing.Size(336, 274);
            this.RTProtection_TextBox_ProcessInfo.TabIndex = 5;
            // 
            // RTProtection_Button_TerminateProcess
            // 
            this.RTProtection_Button_TerminateProcess.Location = new System.Drawing.Point(10, 55);
            this.RTProtection_Button_TerminateProcess.Name = "RTProtection_Button_TerminateProcess";
            this.RTProtection_Button_TerminateProcess.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_TerminateProcess.Size = new System.Drawing.Size(75, 23);
            this.RTProtection_Button_TerminateProcess.TabIndex = 4;
            this.RTProtection_Button_TerminateProcess.Text = "Terminate";
            this.RTProtection_Button_TerminateProcess.Click += new System.EventHandler(this.RTProtection_Button_TerminateProcess_Click);
            // 
            // RTProtection_checkedListBox_Processes
            // 
            this.RTProtection_checkedListBox_Processes.FormattingEnabled = true;
            this.RTProtection_checkedListBox_Processes.Location = new System.Drawing.Point(91, 16);
            this.RTProtection_checkedListBox_Processes.Name = "RTProtection_checkedListBox_Processes";
            this.RTProtection_checkedListBox_Processes.Size = new System.Drawing.Size(319, 274);
            this.RTProtection_checkedListBox_Processes.TabIndex = 8;
            // 
            // RTProtection_Button_Activate
            // 
            this.RTProtection_Button_Activate.Location = new System.Drawing.Point(10, 16);
            this.RTProtection_Button_Activate.Name = "RTProtection_Button_Activate";
            this.RTProtection_Button_Activate.Padding = new System.Windows.Forms.Padding(5);
            this.RTProtection_Button_Activate.Size = new System.Drawing.Size(75, 23);
            this.RTProtection_Button_Activate.TabIndex = 9;
            this.RTProtection_Button_Activate.Text = "Activate";
            this.RTProtection_Button_Activate.Click += new System.EventHandler(this.RTProtection_Button_Activate_Click);
            // 
            // Form_RTProtection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.RTProtection_Button_Activate);
            this.Controls.Add(this.RTProtection_checkedListBox_Processes);
            this.Controls.Add(this.RTProtection_Button_Hook);
            this.Controls.Add(this.RTProtection_TextBox_ProcessInfo);
            this.Controls.Add(this.RTProtection_Button_TerminateProcess);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_RTProtection";
            this.Text = "Form_RTProtection";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private DarkUI.Controls.DarkButton RTProtection_Button_Hook;
        private DarkUI.Controls.DarkTextBox RTProtection_TextBox_ProcessInfo;
        private DarkUI.Controls.DarkButton RTProtection_Button_TerminateProcess;
        private System.Windows.Forms.CheckedListBox RTProtection_checkedListBox_Processes;
        private DarkUI.Controls.DarkButton RTProtection_Button_Activate;
    }
}