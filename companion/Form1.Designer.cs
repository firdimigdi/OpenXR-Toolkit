﻿
namespace companion
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle8 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.layerActive = new System.Windows.Forms.Label();
            this.tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.reportIssuesLink = new System.Windows.Forms.LinkLabel();
            this.screenshotCheckbox = new System.Windows.Forms.CheckBox();
            this.checkUpdatesLink = new System.Windows.Forms.LinkLabel();
            this.disableCheckbox = new System.Windows.Forms.CheckBox();
            this.safemodeCheckbox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.openLog = new System.Windows.Forms.Button();
            this.openScreenshots = new System.Windows.Forms.Button();
            this.leftKey = new System.Windows.Forms.ComboBox();
            this.nextKey = new System.Windows.Forms.ComboBox();
            this.rightKey = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.ctrlModifierCheckbox = new System.Windows.Forms.CheckBox();
            this.altModifierCheckbox = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label10 = new System.Windows.Forms.Label();
            this.screenshotKey = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.previousKey = new System.Windows.Forms.ComboBox();
            this.menuVisibility = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.licences = new System.Windows.Forms.LinkLabel();
            this.screenshotFormat = new System.Windows.Forms.ComboBox();
            this.traceButton = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.screenshotEye = new System.Windows.Forms.ComboBox();
            this.appGrid = new System.Windows.Forms.DataGridView();
            this.bypass = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.disable_interceptor = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.module = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.app = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.reset = new System.Windows.Forms.DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.appGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // layerActive
            // 
            this.layerActive.Location = new System.Drawing.Point(23, 99);
            this.layerActive.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.layerActive.Name = "layerActive";
            this.layerActive.Size = new System.Drawing.Size(365, 13);
            this.layerActive.TabIndex = 0;
            this.layerActive.Text = "Layer status is not known";
            this.layerActive.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // reportIssuesLink
            // 
            this.reportIssuesLink.AutoSize = true;
            this.reportIssuesLink.Location = new System.Drawing.Point(7, 697);
            this.reportIssuesLink.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.reportIssuesLink.Name = "reportIssuesLink";
            this.reportIssuesLink.Size = new System.Drawing.Size(71, 13);
            this.reportIssuesLink.TabIndex = 31;
            this.reportIssuesLink.TabStop = true;
            this.reportIssuesLink.Text = "Report issues";
            this.reportIssuesLink.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.reportIssuesLink_LinkClicked);
            // 
            // screenshotCheckbox
            // 
            this.screenshotCheckbox.AutoSize = true;
            this.screenshotCheckbox.Location = new System.Drawing.Point(25, 274);
            this.screenshotCheckbox.Name = "screenshotCheckbox";
            this.screenshotCheckbox.Size = new System.Drawing.Size(114, 17);
            this.screenshotCheckbox.TabIndex = 7;
            this.screenshotCheckbox.Text = "Enable screenshot";
            this.screenshotCheckbox.UseVisualStyleBackColor = true;
            this.screenshotCheckbox.CheckedChanged += new System.EventHandler(this.sceenshotCheckbox_CheckedChanged);
            // 
            // checkUpdatesLink
            // 
            this.checkUpdatesLink.AutoSize = true;
            this.checkUpdatesLink.Location = new System.Drawing.Point(274, 697);
            this.checkUpdatesLink.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.checkUpdatesLink.Name = "checkUpdatesLink";
            this.checkUpdatesLink.Size = new System.Drawing.Size(131, 13);
            this.checkUpdatesLink.TabIndex = 33;
            this.checkUpdatesLink.TabStop = true;
            this.checkUpdatesLink.Text = "Check for a newer version";
            this.checkUpdatesLink.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.checkUpdatesLink_LinkClicked);
            // 
            // disableCheckbox
            // 
            this.disableCheckbox.AutoSize = true;
            this.disableCheckbox.Location = new System.Drawing.Point(25, 156);
            this.disableCheckbox.Margin = new System.Windows.Forms.Padding(2);
            this.disableCheckbox.Name = "disableCheckbox";
            this.disableCheckbox.Size = new System.Drawing.Size(158, 17);
            this.disableCheckbox.TabIndex = 1;
            this.disableCheckbox.Text = "Disable the OpenXR Toolkit";
            this.disableCheckbox.UseVisualStyleBackColor = true;
            this.disableCheckbox.CheckedChanged += new System.EventHandler(this.disableCheckbox_CheckedChanged);
            // 
            // safemodeCheckbox
            // 
            this.safemodeCheckbox.AutoSize = true;
            this.safemodeCheckbox.Location = new System.Drawing.Point(25, 209);
            this.safemodeCheckbox.Margin = new System.Windows.Forms.Padding(2);
            this.safemodeCheckbox.Name = "safemodeCheckbox";
            this.safemodeCheckbox.Size = new System.Drawing.Size(111, 17);
            this.safemodeCheckbox.TabIndex = 3;
            this.safemodeCheckbox.Text = "Enable safe mode";
            this.safemodeCheckbox.UseVisualStyleBackColor = true;
            this.safemodeCheckbox.CheckedChanged += new System.EventHandler(this.safemodeCheckbox_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(41, 181);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(297, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Completely disable the software without needing to uninstall it.";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(41, 234);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(348, 26);
            this.label2.TabIndex = 4;
            this.label2.Text = "Recover an application by ignoring all its settings upon next startup. When in sa" +
    "fe mode, press Ctrl+F1+F2+F3 to delete all settings.";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(41, 300);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(360, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Screenshots are stored in %LocalAppData%\\OpenXR-Toolkit\\screenshots.";
            // 
            // openLog
            // 
            this.openLog.Location = new System.Drawing.Point(18, 613);
            this.openLog.Margin = new System.Windows.Forms.Padding(2);
            this.openLog.Name = "openLog";
            this.openLog.Size = new System.Drawing.Size(150, 31);
            this.openLog.TabIndex = 28;
            this.openLog.Text = "Open log file";
            this.openLog.UseVisualStyleBackColor = true;
            this.openLog.Click += new System.EventHandler(this.openLog_Click);
            // 
            // openScreenshots
            // 
            this.openScreenshots.Location = new System.Drawing.Point(187, 613);
            this.openScreenshots.Margin = new System.Windows.Forms.Padding(2);
            this.openScreenshots.Name = "openScreenshots";
            this.openScreenshots.Size = new System.Drawing.Size(150, 31);
            this.openScreenshots.TabIndex = 29;
            this.openScreenshots.Text = "Open screenshots folder";
            this.openScreenshots.UseVisualStyleBackColor = true;
            this.openScreenshots.Click += new System.EventHandler(this.openScreenshots_Click);
            // 
            // leftKey
            // 
            this.leftKey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.leftKey.FormattingEnabled = true;
            this.leftKey.Location = new System.Drawing.Point(154, 411);
            this.leftKey.Name = "leftKey";
            this.leftKey.Size = new System.Drawing.Size(75, 21);
            this.leftKey.TabIndex = 14;
            this.leftKey.SelectedIndexChanged += new System.EventHandler(this.leftKey_SelectedIndexChanged);
            // 
            // nextKey
            // 
            this.nextKey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.nextKey.FormattingEnabled = true;
            this.nextKey.Location = new System.Drawing.Point(234, 411);
            this.nextKey.Name = "nextKey";
            this.nextKey.Size = new System.Drawing.Size(75, 21);
            this.nextKey.TabIndex = 18;
            this.nextKey.SelectedIndexChanged += new System.EventHandler(this.nextKey_SelectedIndexChanged);
            // 
            // rightKey
            // 
            this.rightKey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rightKey.FormattingEnabled = true;
            this.rightKey.Location = new System.Drawing.Point(314, 411);
            this.rightKey.Name = "rightKey";
            this.rightKey.Size = new System.Drawing.Size(75, 21);
            this.rightKey.TabIndex = 20;
            this.rightKey.SelectedIndexChanged += new System.EventHandler(this.rightKey_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 413);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(125, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "On-screen menu hotkeys";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(93, 468);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(49, 13);
            this.label6.TabIndex = 23;
            this.label6.Text = "Modifiers";
            // 
            // ctrlModifierCheckbox
            // 
            this.ctrlModifierCheckbox.AutoSize = true;
            this.ctrlModifierCheckbox.Location = new System.Drawing.Point(156, 468);
            this.ctrlModifierCheckbox.Name = "ctrlModifierCheckbox";
            this.ctrlModifierCheckbox.Size = new System.Drawing.Size(41, 17);
            this.ctrlModifierCheckbox.TabIndex = 24;
            this.ctrlModifierCheckbox.Text = "Ctrl";
            this.ctrlModifierCheckbox.UseVisualStyleBackColor = true;
            this.ctrlModifierCheckbox.CheckedChanged += new System.EventHandler(this.ctrlModifierCheckbox_CheckedChanged);
            // 
            // altModifierCheckbox
            // 
            this.altModifierCheckbox.AutoSize = true;
            this.altModifierCheckbox.Location = new System.Drawing.Point(207, 468);
            this.altModifierCheckbox.Name = "altModifierCheckbox";
            this.altModifierCheckbox.Size = new System.Drawing.Size(38, 17);
            this.altModifierCheckbox.TabIndex = 25;
            this.altModifierCheckbox.Text = "Alt";
            this.altModifierCheckbox.UseVisualStyleBackColor = true;
            this.altModifierCheckbox.CheckedChanged += new System.EventHandler(this.altModifierCheckbox_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(179, 395);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(21, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "left";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(254, 395);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(33, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "down";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(339, 395);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(27, 13);
            this.label9.TabIndex = 19;
            this.label9.Text = "right";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::companion.Properties.Resources.banner;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(413, 85);
            this.pictureBox1.TabIndex = 36;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(60, 441);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(87, 13);
            this.label10.TabIndex = 21;
            this.label10.Text = "Take screenshot";
            // 
            // screenshotKey
            // 
            this.screenshotKey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.screenshotKey.FormattingEnabled = true;
            this.screenshotKey.Location = new System.Drawing.Point(154, 437);
            this.screenshotKey.Name = "screenshotKey";
            this.screenshotKey.Size = new System.Drawing.Size(75, 21);
            this.screenshotKey.TabIndex = 22;
            this.screenshotKey.SelectedIndexChanged += new System.EventHandler(this.screenshotKey_SelectedIndexChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(259, 357);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(19, 13);
            this.label11.TabIndex = 15;
            this.label11.Text = "up";
            // 
            // previousKey
            // 
            this.previousKey.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.previousKey.FormattingEnabled = true;
            this.previousKey.Location = new System.Drawing.Point(234, 372);
            this.previousKey.Name = "previousKey";
            this.previousKey.Size = new System.Drawing.Size(75, 21);
            this.previousKey.TabIndex = 16;
            this.previousKey.SelectedIndexChanged += new System.EventHandler(this.previousKey_SelectedIndexChanged);
            // 
            // menuVisibility
            // 
            this.menuVisibility.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.menuVisibility.FormattingEnabled = true;
            this.menuVisibility.Items.AddRange(new object[] {
            "Both eyes",
            "Left eye only",
            "Right eye only"});
            this.menuVisibility.Location = new System.Drawing.Point(154, 324);
            this.menuVisibility.Margin = new System.Windows.Forms.Padding(2);
            this.menuVisibility.Name = "menuVisibility";
            this.menuVisibility.Size = new System.Drawing.Size(119, 21);
            this.menuVisibility.TabIndex = 11;
            this.menuVisibility.SelectedIndexChanged += new System.EventHandler(this.menuVisibility_SelectedIndexChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(23, 326);
            this.label12.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(124, 13);
            this.label12.TabIndex = 10;
            this.label12.Text = "In-headset menu visibility";
            // 
            // licences
            // 
            this.licences.AutoSize = true;
            this.licences.Location = new System.Drawing.Point(311, 676);
            this.licences.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.licences.Name = "licences";
            this.licences.Size = new System.Drawing.Size(94, 13);
            this.licences.TabIndex = 32;
            this.licences.TabStop = true;
            this.licences.Text = "3rd Party Licenses";
            this.licences.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.licences_LinkClicked);
            // 
            // screenshotFormat
            // 
            this.screenshotFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.screenshotFormat.FormattingEnabled = true;
            this.screenshotFormat.Items.AddRange(new object[] {
            "DDS",
            "PNG",
            "JPG",
            "BMP"});
            this.screenshotFormat.Location = new System.Drawing.Point(143, 272);
            this.screenshotFormat.Name = "screenshotFormat";
            this.screenshotFormat.Size = new System.Drawing.Size(75, 21);
            this.screenshotFormat.TabIndex = 8;
            this.screenshotFormat.SelectedIndexChanged += new System.EventHandler(this.screenshotFormat_SelectedIndexChanged);
            // 
            // traceButton
            // 
            this.traceButton.Location = new System.Drawing.Point(18, 649);
            this.traceButton.Name = "traceButton";
            this.traceButton.Size = new System.Drawing.Size(150, 31);
            this.traceButton.TabIndex = 30;
            this.traceButton.Text = "Capture trace";
            this.traceButton.UseVisualStyleBackColor = true;
            this.traceButton.Click += new System.EventHandler(this.traceButton_Click);
            // 
            // label13
            // 
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(23, 120);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(365, 13);
            this.label13.TabIndex = 0;
            this.label13.Text = "You do not need to keep this window open";
            this.label13.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(13, 491);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(352, 13);
            this.label14.TabIndex = 26;
            this.label14.Text = "Enable OpenXR Toolkit for each application selectively or reset its profile.";
            // 
            // screenshotEye
            // 
            this.screenshotEye.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.screenshotEye.FormattingEnabled = true;
            this.screenshotEye.Items.AddRange(new object[] {
            "Both eyes",
            "Left eye only",
            "Right eye only"});
            this.screenshotEye.Location = new System.Drawing.Point(234, 272);
            this.screenshotEye.Margin = new System.Windows.Forms.Padding(2);
            this.screenshotEye.Name = "screenshotEye";
            this.screenshotEye.Size = new System.Drawing.Size(119, 21);
            this.screenshotEye.TabIndex = 9;
            this.screenshotEye.SelectedIndexChanged += new System.EventHandler(this.screenshotEye_SelectedIndexChanged);
            // 
            // appGrid
            // 
            this.appGrid.AllowUserToAddRows = false;
            this.appGrid.AllowUserToDeleteRows = false;
            this.appGrid.AllowUserToOrderColumns = true;
            this.appGrid.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.appGrid.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.appGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.appGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.bypass,
            this.disable_interceptor,
            this.module,
            this.app,
            this.reset});
            dataGridViewCellStyle7.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle7.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle7.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle7.SelectionBackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle7.SelectionForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle7.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.appGrid.DefaultCellStyle = dataGridViewCellStyle7;
            this.appGrid.Location = new System.Drawing.Point(10, 507);
            this.appGrid.MultiSelect = false;
            this.appGrid.Name = "appGrid";
            dataGridViewCellStyle8.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle8.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle8.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle8.SelectionBackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle8.SelectionForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle8.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.appGrid.RowHeadersDefaultCellStyle = dataGridViewCellStyle8;
            this.appGrid.RowHeadersVisible = false;
            this.appGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.appGrid.Size = new System.Drawing.Size(395, 101);
            this.appGrid.TabIndex = 37;
            this.appGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.appGrid_CellContentClick);
            this.appGrid.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.appGrid_CellEndEdit);
            this.appGrid.CellMouseUp += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.appGrid_CellMouseUp);
            // 
            // bypass
            // 
            this.bypass.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle2.NullValue = false;
            this.bypass.DefaultCellStyle = dataGridViewCellStyle2;
            this.bypass.FillWeight = 20F;
            this.bypass.HeaderText = "Enable";
            this.bypass.MinimumWidth = 25;
            this.bypass.Name = "bypass";
            this.bypass.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.bypass.ToolTipText = "Enable OpenXR Toolkit for the specific application";
            this.bypass.Width = 50;
            // 
            // disable_interceptor
            // 
            this.disable_interceptor.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle3.NullValue = false;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.disable_interceptor.DefaultCellStyle = dataGridViewCellStyle3;
            this.disable_interceptor.FillWeight = 18.27411F;
            this.disable_interceptor.HeaderText = "Intercept";
            this.disable_interceptor.MinimumWidth = 50;
            this.disable_interceptor.Name = "disable_interceptor";
            this.disable_interceptor.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.disable_interceptor.ToolTipText = "Toggle the graphics API interceptor required for foveated rendering (might cause " +
    "issues with some apps)";
            // 
            // module
            // 
            this.module.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.module.DefaultCellStyle = dataGridViewCellStyle4;
            this.module.FillWeight = 50F;
            this.module.HeaderText = "Executable";
            this.module.MinimumWidth = 50;
            this.module.Name = "module";
            // 
            // app
            // 
            this.app.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.app.DefaultCellStyle = dataGridViewCellStyle5;
            this.app.FillWeight = 50F;
            this.app.HeaderText = "Application";
            this.app.MinimumWidth = 100;
            this.app.Name = "app";
            this.app.ReadOnly = true;
            // 
            // reset
            // 
            this.reset.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(161)));
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.Color.Black;
            this.reset.DefaultCellStyle = dataGridViewCellStyle6;
            this.reset.HeaderText = "";
            this.reset.MinimumWidth = 20;
            this.reset.Name = "reset";
            this.reset.ReadOnly = true;
            this.reset.Text = "X";
            this.reset.ToolTipText = "Reset profile to default values on next run";
            this.reset.UseColumnTextForButtonValue = true;
            this.reset.Width = 20;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(413, 714);
            this.Controls.Add(this.appGrid);
            this.Controls.Add(this.screenshotEye);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.traceButton);
            this.Controls.Add(this.screenshotFormat);
            this.Controls.Add(this.licences);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.menuVisibility);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.previousKey);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.screenshotKey);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.altModifierCheckbox);
            this.Controls.Add(this.ctrlModifierCheckbox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.rightKey);
            this.Controls.Add(this.nextKey);
            this.Controls.Add(this.leftKey);
            this.Controls.Add(this.openScreenshots);
            this.Controls.Add(this.openLog);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.safemodeCheckbox);
            this.Controls.Add(this.disableCheckbox);
            this.Controls.Add(this.checkUpdatesLink);
            this.Controls.Add(this.screenshotCheckbox);
            this.Controls.Add(this.reportIssuesLink);
            this.Controls.Add(this.layerActive);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "OpenXR Toolkit Companion app";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.appGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label layerActive;
        private System.Windows.Forms.ToolTip tooltip;
        private System.Windows.Forms.LinkLabel reportIssuesLink;
        private System.Windows.Forms.CheckBox screenshotCheckbox;
        private System.Windows.Forms.LinkLabel checkUpdatesLink;
        private System.Windows.Forms.CheckBox disableCheckbox;
        private System.Windows.Forms.CheckBox safemodeCheckbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button openLog;
        private System.Windows.Forms.Button openScreenshots;
        private System.Windows.Forms.ComboBox leftKey;
        private System.Windows.Forms.ComboBox rightKey;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox ctrlModifierCheckbox;
        private System.Windows.Forms.CheckBox altModifierCheckbox;
        private System.Windows.Forms.ComboBox nextKey;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox screenshotKey;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox previousKey;
        private System.Windows.Forms.ComboBox menuVisibility;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.LinkLabel licences;
        private System.Windows.Forms.ComboBox screenshotFormat;
        private System.Windows.Forms.Button traceButton;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.ComboBox screenshotEye;
        private System.Windows.Forms.DataGridView appGrid;
        private System.Windows.Forms.DataGridViewCheckBoxColumn bypass;
        private System.Windows.Forms.DataGridViewCheckBoxColumn disable_interceptor;
        private System.Windows.Forms.DataGridViewTextBoxColumn module;
        private System.Windows.Forms.DataGridViewTextBoxColumn app;
        private System.Windows.Forms.DataGridViewButtonColumn reset;
    }
}

