namespace BUGAV {
    partial class Form_FilterNetwork {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_FilterNetwork));
            this.FilterNetwork_Button_ClearEvents = new DarkUI.Controls.DarkButton();
            this.FilterNetwork_Button_DeleteRule = new DarkUI.Controls.DarkButton();
            this.FilterNetwork_Button_CreateRule = new DarkUI.Controls.DarkButton();
            this.FilterNetwork_TextBox_Events = new DarkUI.Controls.DarkTextBox();
            this.FilterNetwork_checkedListBox_Rules = new System.Windows.Forms.CheckedListBox();
            this.darkLabel12 = new DarkUI.Controls.DarkLabel();
            this.darkLabel11 = new DarkUI.Controls.DarkLabel();
            this.darkLabel10 = new DarkUI.Controls.DarkLabel();
            this.FilterNetwork_checkedListBox_Interfaces = new System.Windows.Forms.CheckedListBox();
            this.SuspendLayout();
            // 
            // FilterNetwork_Button_ClearEvents
            // 
            this.FilterNetwork_Button_ClearEvents.Location = new System.Drawing.Point(70, 226);
            this.FilterNetwork_Button_ClearEvents.Name = "FilterNetwork_Button_ClearEvents";
            this.FilterNetwork_Button_ClearEvents.Padding = new System.Windows.Forms.Padding(5);
            this.FilterNetwork_Button_ClearEvents.Size = new System.Drawing.Size(75, 23);
            this.FilterNetwork_Button_ClearEvents.TabIndex = 17;
            this.FilterNetwork_Button_ClearEvents.Text = "Clear";
            // 
            // FilterNetwork_Button_DeleteRule
            // 
            this.FilterNetwork_Button_DeleteRule.Location = new System.Drawing.Point(687, 12);
            this.FilterNetwork_Button_DeleteRule.Name = "FilterNetwork_Button_DeleteRule";
            this.FilterNetwork_Button_DeleteRule.Padding = new System.Windows.Forms.Padding(5);
            this.FilterNetwork_Button_DeleteRule.Size = new System.Drawing.Size(75, 23);
            this.FilterNetwork_Button_DeleteRule.TabIndex = 16;
            this.FilterNetwork_Button_DeleteRule.Text = "Delete";
            // 
            // FilterNetwork_Button_CreateRule
            // 
            this.FilterNetwork_Button_CreateRule.Location = new System.Drawing.Point(606, 12);
            this.FilterNetwork_Button_CreateRule.Name = "FilterNetwork_Button_CreateRule";
            this.FilterNetwork_Button_CreateRule.Padding = new System.Windows.Forms.Padding(5);
            this.FilterNetwork_Button_CreateRule.Size = new System.Drawing.Size(75, 23);
            this.FilterNetwork_Button_CreateRule.TabIndex = 15;
            this.FilterNetwork_Button_CreateRule.Text = "Create";
            this.FilterNetwork_Button_CreateRule.Click += new System.EventHandler(this.FilterNetwork_Button_CreateRule_Click);
            // 
            // FilterNetwork_TextBox_Events
            // 
            this.FilterNetwork_TextBox_Events.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.FilterNetwork_TextBox_Events.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FilterNetwork_TextBox_Events.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.FilterNetwork_TextBox_Events.Location = new System.Drawing.Point(24, 255);
            this.FilterNetwork_TextBox_Events.Multiline = true;
            this.FilterNetwork_TextBox_Events.Name = "FilterNetwork_TextBox_Events";
            this.FilterNetwork_TextBox_Events.Size = new System.Drawing.Size(738, 112);
            this.FilterNetwork_TextBox_Events.TabIndex = 14;
            // 
            // FilterNetwork_checkedListBox_Rules
            // 
            this.FilterNetwork_checkedListBox_Rules.FormattingEnabled = true;
            this.FilterNetwork_checkedListBox_Rules.Location = new System.Drawing.Point(305, 45);
            this.FilterNetwork_checkedListBox_Rules.Name = "FilterNetwork_checkedListBox_Rules";
            this.FilterNetwork_checkedListBox_Rules.Size = new System.Drawing.Size(457, 169);
            this.FilterNetwork_checkedListBox_Rules.TabIndex = 13;
            // 
            // darkLabel12
            // 
            this.darkLabel12.AutoSize = true;
            this.darkLabel12.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel12.Location = new System.Drawing.Point(24, 231);
            this.darkLabel12.Name = "darkLabel12";
            this.darkLabel12.Size = new System.Drawing.Size(40, 13);
            this.darkLabel12.TabIndex = 12;
            this.darkLabel12.Text = "Events";
            // 
            // darkLabel11
            // 
            this.darkLabel11.AutoSize = true;
            this.darkLabel11.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel11.Location = new System.Drawing.Point(302, 26);
            this.darkLabel11.Name = "darkLabel11";
            this.darkLabel11.Size = new System.Drawing.Size(34, 13);
            this.darkLabel11.TabIndex = 11;
            this.darkLabel11.Text = "Rules";
            // 
            // darkLabel10
            // 
            this.darkLabel10.AutoSize = true;
            this.darkLabel10.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel10.Location = new System.Drawing.Point(21, 26);
            this.darkLabel10.Name = "darkLabel10";
            this.darkLabel10.Size = new System.Drawing.Size(54, 13);
            this.darkLabel10.TabIndex = 10;
            this.darkLabel10.Text = "Interfaces";
            // 
            // FilterNetwork_checkedListBox_Interfaces
            // 
            this.FilterNetwork_checkedListBox_Interfaces.FormattingEnabled = true;
            this.FilterNetwork_checkedListBox_Interfaces.Location = new System.Drawing.Point(24, 45);
            this.FilterNetwork_checkedListBox_Interfaces.Name = "FilterNetwork_checkedListBox_Interfaces";
            this.FilterNetwork_checkedListBox_Interfaces.Size = new System.Drawing.Size(230, 169);
            this.FilterNetwork_checkedListBox_Interfaces.TabIndex = 9;
            // 
            // Form_FilterNetwork
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.FilterNetwork_Button_ClearEvents);
            this.Controls.Add(this.FilterNetwork_Button_DeleteRule);
            this.Controls.Add(this.FilterNetwork_Button_CreateRule);
            this.Controls.Add(this.FilterNetwork_TextBox_Events);
            this.Controls.Add(this.FilterNetwork_checkedListBox_Rules);
            this.Controls.Add(this.darkLabel12);
            this.Controls.Add(this.darkLabel11);
            this.Controls.Add(this.darkLabel10);
            this.Controls.Add(this.FilterNetwork_checkedListBox_Interfaces);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_FilterNetwork";
            this.Text = "Form_FilterNetwork";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DarkUI.Controls.DarkButton FilterNetwork_Button_ClearEvents;
        private DarkUI.Controls.DarkButton FilterNetwork_Button_DeleteRule;
        private DarkUI.Controls.DarkButton FilterNetwork_Button_CreateRule;
        private DarkUI.Controls.DarkTextBox FilterNetwork_TextBox_Events;
        private System.Windows.Forms.CheckedListBox FilterNetwork_checkedListBox_Rules;
        private DarkUI.Controls.DarkLabel darkLabel12;
        private DarkUI.Controls.DarkLabel darkLabel11;
        private DarkUI.Controls.DarkLabel darkLabel10;
        private System.Windows.Forms.CheckedListBox FilterNetwork_checkedListBox_Interfaces;
    }
}