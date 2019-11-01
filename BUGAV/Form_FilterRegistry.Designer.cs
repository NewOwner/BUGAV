namespace BUGAV {
    partial class Form_FilterRegistry {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_FilterRegistry));
            this.FilterRegistry_checkedListBox_RegKeys = new System.Windows.Forms.CheckedListBox();
            this.FilterRegistry_Button_DeleteRegKey = new DarkUI.Controls.DarkButton();
            this.FilterRegistry_TextBox_RegKey = new DarkUI.Controls.DarkTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.FilterRegistry_Button_AddRegKey = new DarkUI.Controls.DarkButton();
            this.FilterRegistry_Button_Activate = new DarkUI.Controls.DarkButton();
            this.SuspendLayout();
            // 
            // FilterRegistry_checkedListBox_RegKeys
            // 
            this.FilterRegistry_checkedListBox_RegKeys.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.FilterRegistry_checkedListBox_RegKeys.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.FilterRegistry_checkedListBox_RegKeys.FormattingEnabled = true;
            this.FilterRegistry_checkedListBox_RegKeys.Location = new System.Drawing.Point(29, 79);
            this.FilterRegistry_checkedListBox_RegKeys.Name = "FilterRegistry_checkedListBox_RegKeys";
            this.FilterRegistry_checkedListBox_RegKeys.Size = new System.Drawing.Size(233, 199);
            this.FilterRegistry_checkedListBox_RegKeys.TabIndex = 13;
            // 
            // FilterRegistry_Button_DeleteRegKey
            // 
            this.FilterRegistry_Button_DeleteRegKey.Location = new System.Drawing.Point(187, 23);
            this.FilterRegistry_Button_DeleteRegKey.Name = "FilterRegistry_Button_DeleteRegKey";
            this.FilterRegistry_Button_DeleteRegKey.Padding = new System.Windows.Forms.Padding(5);
            this.FilterRegistry_Button_DeleteRegKey.Size = new System.Drawing.Size(75, 23);
            this.FilterRegistry_Button_DeleteRegKey.TabIndex = 12;
            this.FilterRegistry_Button_DeleteRegKey.Text = "Delete";
            this.FilterRegistry_Button_DeleteRegKey.Click += new System.EventHandler(this.FilterRegistry_Button_DeleteRegKey_Click);
            // 
            // FilterRegistry_TextBox_RegKey
            // 
            this.FilterRegistry_TextBox_RegKey.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(74)))));
            this.FilterRegistry_TextBox_RegKey.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FilterRegistry_TextBox_RegKey.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.FilterRegistry_TextBox_RegKey.Location = new System.Drawing.Point(29, 52);
            this.FilterRegistry_TextBox_RegKey.Name = "FilterRegistry_TextBox_RegKey";
            this.FilterRegistry_TextBox_RegKey.Size = new System.Drawing.Size(233, 20);
            this.FilterRegistry_TextBox_RegKey.TabIndex = 11;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ControlLight;
            this.label1.Location = new System.Drawing.Point(26, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Registry Keys";
            // 
            // FilterRegistry_Button_AddRegKey
            // 
            this.FilterRegistry_Button_AddRegKey.Location = new System.Drawing.Point(103, 23);
            this.FilterRegistry_Button_AddRegKey.Name = "FilterRegistry_Button_AddRegKey";
            this.FilterRegistry_Button_AddRegKey.Padding = new System.Windows.Forms.Padding(5);
            this.FilterRegistry_Button_AddRegKey.Size = new System.Drawing.Size(78, 23);
            this.FilterRegistry_Button_AddRegKey.TabIndex = 9;
            this.FilterRegistry_Button_AddRegKey.Text = "Add";
            this.FilterRegistry_Button_AddRegKey.Click += new System.EventHandler(this.FilterRegistry_Button_AddRegKey_Click);
            // 
            // FilterRegistry_Button_Activate
            // 
            this.FilterRegistry_Button_Activate.Location = new System.Drawing.Point(187, 284);
            this.FilterRegistry_Button_Activate.Name = "FilterRegistry_Button_Activate";
            this.FilterRegistry_Button_Activate.Padding = new System.Windows.Forms.Padding(5);
            this.FilterRegistry_Button_Activate.Size = new System.Drawing.Size(75, 23);
            this.FilterRegistry_Button_Activate.TabIndex = 14;
            this.FilterRegistry_Button_Activate.Text = "Activate";
            this.FilterRegistry_Button_Activate.Click += new System.EventHandler(this.FilterRegistry_Button_Activate_Click);
            // 
            // Form_FilterRegistry
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.FilterRegistry_Button_Activate);
            this.Controls.Add(this.FilterRegistry_checkedListBox_RegKeys);
            this.Controls.Add(this.FilterRegistry_Button_DeleteRegKey);
            this.Controls.Add(this.FilterRegistry_TextBox_RegKey);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.FilterRegistry_Button_AddRegKey);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_FilterRegistry";
            this.Text = "Form_FilterRegistry";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckedListBox FilterRegistry_checkedListBox_RegKeys;
        private DarkUI.Controls.DarkButton FilterRegistry_Button_DeleteRegKey;
        private DarkUI.Controls.DarkTextBox FilterRegistry_TextBox_RegKey;
        private System.Windows.Forms.Label label1;
        private DarkUI.Controls.DarkButton FilterRegistry_Button_AddRegKey;
        private DarkUI.Controls.DarkButton FilterRegistry_Button_Activate;
    }
}