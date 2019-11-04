namespace BUGAV {
    partial class Form_FilterNetworkRule {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_FilterNetworkRule));
            this.darkLabel1 = new DarkUI.Controls.DarkLabel();
            this.darkLabel2 = new DarkUI.Controls.DarkLabel();
            this.darkLabel3 = new DarkUI.Controls.DarkLabel();
            this.darkLabel4 = new DarkUI.Controls.DarkLabel();
            this.darkLabel5 = new DarkUI.Controls.DarkLabel();
            this.darkLabel6 = new DarkUI.Controls.DarkLabel();
            this.darkLabel7 = new DarkUI.Controls.DarkLabel();
            this.FilterNetworkRule_comboBox_Action = new System.Windows.Forms.ComboBox();
            this.FilterNetworkRule_comboBox_EtherType = new System.Windows.Forms.ComboBox();
            this.FilterNetworkRule_comboBox_IpNextProtocol = new System.Windows.Forms.ComboBox();
            this.FilterNetworkRule_Button_AddRule = new DarkUI.Controls.DarkButton();
            this.FilterNetworkRule_Button_Cancel = new DarkUI.Controls.DarkButton();
            this.FilterNetworkRule_textBox_SourceIp = new System.Windows.Forms.TextBox();
            this.FilterNetworkRule_textBox_DestinationIp = new System.Windows.Forms.TextBox();
            this.FilterNetworkRule_textBox_SourcePort = new System.Windows.Forms.TextBox();
            this.FilterNetworkRule_textBox_DestinationPort = new System.Windows.Forms.TextBox();
            this.FilterNetworkRule_comboBox_Direction = new System.Windows.Forms.ComboBox();
            this.darkLabel8 = new DarkUI.Controls.DarkLabel();
            this.SuspendLayout();
            // 
            // darkLabel1
            // 
            this.darkLabel1.AutoSize = true;
            this.darkLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel1.Location = new System.Drawing.Point(18, 27);
            this.darkLabel1.Name = "darkLabel1";
            this.darkLabel1.Size = new System.Drawing.Size(40, 13);
            this.darkLabel1.TabIndex = 0;
            this.darkLabel1.Text = "Action:";
            // 
            // darkLabel2
            // 
            this.darkLabel2.AutoSize = true;
            this.darkLabel2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel2.Location = new System.Drawing.Point(18, 106);
            this.darkLabel2.Name = "darkLabel2";
            this.darkLabel2.Size = new System.Drawing.Size(62, 13);
            this.darkLabel2.TabIndex = 1;
            this.darkLabel2.Text = "Ether Type:";
            // 
            // darkLabel3
            // 
            this.darkLabel3.AutoSize = true;
            this.darkLabel3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel3.Location = new System.Drawing.Point(18, 147);
            this.darkLabel3.Name = "darkLabel3";
            this.darkLabel3.Size = new System.Drawing.Size(81, 13);
            this.darkLabel3.TabIndex = 2;
            this.darkLabel3.Text = "IP next protocol";
            // 
            // darkLabel4
            // 
            this.darkLabel4.AutoSize = true;
            this.darkLabel4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel4.Location = new System.Drawing.Point(18, 188);
            this.darkLabel4.Name = "darkLabel4";
            this.darkLabel4.Size = new System.Drawing.Size(57, 13);
            this.darkLabel4.TabIndex = 3;
            this.darkLabel4.Text = "Source IP:";
            // 
            // darkLabel5
            // 
            this.darkLabel5.AutoSize = true;
            this.darkLabel5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel5.Location = new System.Drawing.Point(18, 226);
            this.darkLabel5.Name = "darkLabel5";
            this.darkLabel5.Size = new System.Drawing.Size(76, 13);
            this.darkLabel5.TabIndex = 4;
            this.darkLabel5.Text = "Destination IP:";
            // 
            // darkLabel6
            // 
            this.darkLabel6.AutoSize = true;
            this.darkLabel6.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel6.Location = new System.Drawing.Point(18, 266);
            this.darkLabel6.Name = "darkLabel6";
            this.darkLabel6.Size = new System.Drawing.Size(66, 13);
            this.darkLabel6.TabIndex = 5;
            this.darkLabel6.Text = "Source Port:";
            // 
            // darkLabel7
            // 
            this.darkLabel7.AutoSize = true;
            this.darkLabel7.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel7.Location = new System.Drawing.Point(18, 305);
            this.darkLabel7.Name = "darkLabel7";
            this.darkLabel7.Size = new System.Drawing.Size(85, 13);
            this.darkLabel7.TabIndex = 6;
            this.darkLabel7.Text = "Destination Port:";
            // 
            // FilterNetworkRule_comboBox_Action
            // 
            this.FilterNetworkRule_comboBox_Action.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FilterNetworkRule_comboBox_Action.FormattingEnabled = true;
            this.FilterNetworkRule_comboBox_Action.Items.AddRange(new object[] {
            "Alert",
            "Drop",
            "Ignore"});
            this.FilterNetworkRule_comboBox_Action.Location = new System.Drawing.Point(112, 24);
            this.FilterNetworkRule_comboBox_Action.Name = "FilterNetworkRule_comboBox_Action";
            this.FilterNetworkRule_comboBox_Action.Size = new System.Drawing.Size(162, 21);
            this.FilterNetworkRule_comboBox_Action.TabIndex = 7;
            // 
            // FilterNetworkRule_comboBox_EtherType
            // 
            this.FilterNetworkRule_comboBox_EtherType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FilterNetworkRule_comboBox_EtherType.FormattingEnabled = true;
            this.FilterNetworkRule_comboBox_EtherType.Items.AddRange(new object[] {
            "IP",
            "ARP",
            "Ignore"});
            this.FilterNetworkRule_comboBox_EtherType.Location = new System.Drawing.Point(112, 103);
            this.FilterNetworkRule_comboBox_EtherType.Name = "FilterNetworkRule_comboBox_EtherType";
            this.FilterNetworkRule_comboBox_EtherType.Size = new System.Drawing.Size(162, 21);
            this.FilterNetworkRule_comboBox_EtherType.TabIndex = 8;
            // 
            // FilterNetworkRule_comboBox_IpNextProtocol
            // 
            this.FilterNetworkRule_comboBox_IpNextProtocol.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FilterNetworkRule_comboBox_IpNextProtocol.FormattingEnabled = true;
            this.FilterNetworkRule_comboBox_IpNextProtocol.Items.AddRange(new object[] {
            "ICMP",
            "IGMP",
            "UDP",
            "TCP",
            "Ignore"});
            this.FilterNetworkRule_comboBox_IpNextProtocol.Location = new System.Drawing.Point(112, 144);
            this.FilterNetworkRule_comboBox_IpNextProtocol.Name = "FilterNetworkRule_comboBox_IpNextProtocol";
            this.FilterNetworkRule_comboBox_IpNextProtocol.Size = new System.Drawing.Size(162, 21);
            this.FilterNetworkRule_comboBox_IpNextProtocol.TabIndex = 9;
            // 
            // FilterNetworkRule_Button_AddRule
            // 
            this.FilterNetworkRule_Button_AddRule.Location = new System.Drawing.Point(112, 340);
            this.FilterNetworkRule_Button_AddRule.Name = "FilterNetworkRule_Button_AddRule";
            this.FilterNetworkRule_Button_AddRule.Padding = new System.Windows.Forms.Padding(5);
            this.FilterNetworkRule_Button_AddRule.Size = new System.Drawing.Size(75, 23);
            this.FilterNetworkRule_Button_AddRule.TabIndex = 14;
            this.FilterNetworkRule_Button_AddRule.Text = "Add";
            this.FilterNetworkRule_Button_AddRule.Click += new System.EventHandler(this.FilterNetworkRule_Button_AddRule_Click);
            // 
            // FilterNetworkRule_Button_Cancel
            // 
            this.FilterNetworkRule_Button_Cancel.Location = new System.Drawing.Point(199, 340);
            this.FilterNetworkRule_Button_Cancel.Name = "FilterNetworkRule_Button_Cancel";
            this.FilterNetworkRule_Button_Cancel.Padding = new System.Windows.Forms.Padding(5);
            this.FilterNetworkRule_Button_Cancel.Size = new System.Drawing.Size(75, 23);
            this.FilterNetworkRule_Button_Cancel.TabIndex = 15;
            this.FilterNetworkRule_Button_Cancel.Text = "Cancel";
            this.FilterNetworkRule_Button_Cancel.Click += new System.EventHandler(this.FilterNetworkRule_Button_Cancel_Click);
            // 
            // FilterNetworkRule_textBox_SourceIp
            // 
            this.FilterNetworkRule_textBox_SourceIp.Location = new System.Drawing.Point(112, 185);
            this.FilterNetworkRule_textBox_SourceIp.Name = "FilterNetworkRule_textBox_SourceIp";
            this.FilterNetworkRule_textBox_SourceIp.Size = new System.Drawing.Size(162, 20);
            this.FilterNetworkRule_textBox_SourceIp.TabIndex = 16;
            this.FilterNetworkRule_textBox_SourceIp.Text = "Ignore";
            // 
            // FilterNetworkRule_textBox_DestinationIp
            // 
            this.FilterNetworkRule_textBox_DestinationIp.Location = new System.Drawing.Point(112, 223);
            this.FilterNetworkRule_textBox_DestinationIp.Name = "FilterNetworkRule_textBox_DestinationIp";
            this.FilterNetworkRule_textBox_DestinationIp.Size = new System.Drawing.Size(162, 20);
            this.FilterNetworkRule_textBox_DestinationIp.TabIndex = 17;
            this.FilterNetworkRule_textBox_DestinationIp.Text = "Ignore";
            // 
            // FilterNetworkRule_textBox_SourcePort
            // 
            this.FilterNetworkRule_textBox_SourcePort.Location = new System.Drawing.Point(112, 263);
            this.FilterNetworkRule_textBox_SourcePort.Name = "FilterNetworkRule_textBox_SourcePort";
            this.FilterNetworkRule_textBox_SourcePort.Size = new System.Drawing.Size(162, 20);
            this.FilterNetworkRule_textBox_SourcePort.TabIndex = 18;
            this.FilterNetworkRule_textBox_SourcePort.Text = "Ignore";
            // 
            // FilterNetworkRule_textBox_DestinationPort
            // 
            this.FilterNetworkRule_textBox_DestinationPort.Location = new System.Drawing.Point(112, 302);
            this.FilterNetworkRule_textBox_DestinationPort.Name = "FilterNetworkRule_textBox_DestinationPort";
            this.FilterNetworkRule_textBox_DestinationPort.Size = new System.Drawing.Size(162, 20);
            this.FilterNetworkRule_textBox_DestinationPort.TabIndex = 19;
            this.FilterNetworkRule_textBox_DestinationPort.Text = "Ignore";
            // 
            // FilterNetworkRule_comboBox_Direction
            // 
            this.FilterNetworkRule_comboBox_Direction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FilterNetworkRule_comboBox_Direction.FormattingEnabled = true;
            this.FilterNetworkRule_comboBox_Direction.Items.AddRange(new object[] {
            "From",
            "To",
            "Ignore"});
            this.FilterNetworkRule_comboBox_Direction.Location = new System.Drawing.Point(112, 63);
            this.FilterNetworkRule_comboBox_Direction.Name = "FilterNetworkRule_comboBox_Direction";
            this.FilterNetworkRule_comboBox_Direction.Size = new System.Drawing.Size(162, 21);
            this.FilterNetworkRule_comboBox_Direction.TabIndex = 21;
            // 
            // darkLabel8
            // 
            this.darkLabel8.AutoSize = true;
            this.darkLabel8.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.darkLabel8.Location = new System.Drawing.Point(18, 66);
            this.darkLabel8.Name = "darkLabel8";
            this.darkLabel8.Size = new System.Drawing.Size(52, 13);
            this.darkLabel8.TabIndex = 20;
            this.darkLabel8.Text = "Direction:";
            // 
            // Form_FilterNetworkRule
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 383);
            this.Controls.Add(this.FilterNetworkRule_comboBox_Direction);
            this.Controls.Add(this.darkLabel8);
            this.Controls.Add(this.FilterNetworkRule_textBox_DestinationPort);
            this.Controls.Add(this.FilterNetworkRule_textBox_SourcePort);
            this.Controls.Add(this.FilterNetworkRule_textBox_DestinationIp);
            this.Controls.Add(this.FilterNetworkRule_textBox_SourceIp);
            this.Controls.Add(this.FilterNetworkRule_Button_Cancel);
            this.Controls.Add(this.FilterNetworkRule_Button_AddRule);
            this.Controls.Add(this.FilterNetworkRule_comboBox_IpNextProtocol);
            this.Controls.Add(this.FilterNetworkRule_comboBox_EtherType);
            this.Controls.Add(this.FilterNetworkRule_comboBox_Action);
            this.Controls.Add(this.darkLabel7);
            this.Controls.Add(this.darkLabel6);
            this.Controls.Add(this.darkLabel5);
            this.Controls.Add(this.darkLabel4);
            this.Controls.Add(this.darkLabel3);
            this.Controls.Add(this.darkLabel2);
            this.Controls.Add(this.darkLabel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form_FilterNetworkRule";
            this.Text = "Form_CreateRule";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DarkUI.Controls.DarkLabel darkLabel1;
        private DarkUI.Controls.DarkLabel darkLabel2;
        private DarkUI.Controls.DarkLabel darkLabel3;
        private DarkUI.Controls.DarkLabel darkLabel4;
        private DarkUI.Controls.DarkLabel darkLabel5;
        private DarkUI.Controls.DarkLabel darkLabel6;
        private DarkUI.Controls.DarkLabel darkLabel7;
        private System.Windows.Forms.ComboBox FilterNetworkRule_comboBox_Action;
        private System.Windows.Forms.ComboBox FilterNetworkRule_comboBox_EtherType;
        private System.Windows.Forms.ComboBox FilterNetworkRule_comboBox_IpNextProtocol;
        private DarkUI.Controls.DarkButton FilterNetworkRule_Button_AddRule;
        private DarkUI.Controls.DarkButton FilterNetworkRule_Button_Cancel;
        private System.Windows.Forms.TextBox FilterNetworkRule_textBox_SourceIp;
        private System.Windows.Forms.TextBox FilterNetworkRule_textBox_DestinationIp;
        private System.Windows.Forms.TextBox FilterNetworkRule_textBox_SourcePort;
        private System.Windows.Forms.TextBox FilterNetworkRule_textBox_DestinationPort;
        private System.Windows.Forms.ComboBox FilterNetworkRule_comboBox_Direction;
        private DarkUI.Controls.DarkLabel darkLabel8;
    }
}