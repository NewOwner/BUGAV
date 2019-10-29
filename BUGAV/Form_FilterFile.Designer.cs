namespace BUGAV {
    partial class Form_FilterFile {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_FilterFile));
            this.FilterFile_Button_Delete = new DarkUI.Controls.DarkButton();
            this.darkLabel4 = new DarkUI.Controls.DarkLabel();
            this.FilterFiler_checkedListBox_Files = new System.Windows.Forms.CheckedListBox();
            this.FilterFile_Button_Add = new DarkUI.Controls.DarkButton();
            this.FilterFile_Button_Activate = new DarkUI.Controls.DarkButton();
            this.SuspendLayout();
            // 
            // FilterFile_Button_Delete
            // 
            this.FilterFile_Button_Delete.Location = new System.Drawing.Point(137, 21);
            this.FilterFile_Button_Delete.Name = "FilterFile_Button_Delete";
            this.FilterFile_Button_Delete.Padding = new System.Windows.Forms.Padding(5);
            this.FilterFile_Button_Delete.Size = new System.Drawing.Size(75, 23);
            this.FilterFile_Button_Delete.TabIndex = 8;
            this.FilterFile_Button_Delete.Text = "Delete";
            // 
            // darkLabel4
            // 
            this.darkLabel4.AutoSize = true;
            this.darkLabel4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel4.Location = new System.Drawing.Point(31, 26);
            this.darkLabel4.Name = "darkLabel4";
            this.darkLabel4.Size = new System.Drawing.Size(28, 13);
            this.darkLabel4.TabIndex = 7;
            this.darkLabel4.Text = "Files";
            // 
            // FilterFiler_checkedListBox_Files
            // 
            this.FilterFiler_checkedListBox_Files.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(63)))), ((int)(((byte)(65)))));
            this.FilterFiler_checkedListBox_Files.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.FilterFiler_checkedListBox_Files.FormattingEnabled = true;
            this.FilterFiler_checkedListBox_Files.Location = new System.Drawing.Point(31, 50);
            this.FilterFiler_checkedListBox_Files.Name = "FilterFiler_checkedListBox_Files";
            this.FilterFiler_checkedListBox_Files.Size = new System.Drawing.Size(181, 229);
            this.FilterFiler_checkedListBox_Files.TabIndex = 6;
            // 
            // FilterFile_Button_Add
            // 
            this.FilterFile_Button_Add.Location = new System.Drawing.Point(66, 21);
            this.FilterFile_Button_Add.Name = "FilterFile_Button_Add";
            this.FilterFile_Button_Add.Padding = new System.Windows.Forms.Padding(5);
            this.FilterFile_Button_Add.Size = new System.Drawing.Size(65, 23);
            this.FilterFile_Button_Add.TabIndex = 5;
            this.FilterFile_Button_Add.Text = "Add";
            // 
            // FilterFile_Button_Activate
            // 
            this.FilterFile_Button_Activate.Location = new System.Drawing.Point(34, 285);
            this.FilterFile_Button_Activate.Name = "FilterFile_Button_Activate";
            this.FilterFile_Button_Activate.Padding = new System.Windows.Forms.Padding(5);
            this.FilterFile_Button_Activate.Size = new System.Drawing.Size(75, 23);
            this.FilterFile_Button_Activate.TabIndex = 9;
            this.FilterFile_Button_Activate.Text = "Activate";
            // 
            // Form_FilterFile
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.FilterFile_Button_Activate);
            this.Controls.Add(this.FilterFile_Button_Delete);
            this.Controls.Add(this.darkLabel4);
            this.Controls.Add(this.FilterFiler_checkedListBox_Files);
            this.Controls.Add(this.FilterFile_Button_Add);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_FilterFile";
            this.Text = "Form_FilterFile";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DarkUI.Controls.DarkButton FilterFile_Button_Delete;
        private DarkUI.Controls.DarkLabel darkLabel4;
        private System.Windows.Forms.CheckedListBox FilterFiler_checkedListBox_Files;
        private DarkUI.Controls.DarkButton FilterFile_Button_Add;
        private DarkUI.Controls.DarkButton FilterFile_Button_Activate;
    }
}