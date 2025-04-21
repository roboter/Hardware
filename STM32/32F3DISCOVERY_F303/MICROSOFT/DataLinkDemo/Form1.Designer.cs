namespace DataLinkDemo
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
        /// <param name="disposing">true if managed resources should be _disposed; otherwise, false.</param>
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
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.comboBoxDevices = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxReadLen = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxReadAddress = new System.Windows.Forms.TextBox();
            this.buttonReadMemory = new System.Windows.Forms.Button();
            this.textBoxWriteAddress = new System.Windows.Forms.TextBox();
            this.textBoxWriteData = new System.Windows.Forms.TextBox();
            this.buttonWriteMemory = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonDisableStream = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.labelKernelUtilization = new System.Windows.Forms.Label();
            this.labelKernelTicks = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.buttonEnableStream = new System.Windows.Forms.Button();
            this.buttonClearLog = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tableLayoutPanel2);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(2, 2);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox2.Size = new System.Drawing.Size(523, 96);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "DEVICE CONNECTION";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.buttonRefresh, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.comboBoxDevices, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.label2, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.buttonConnect, 2, 1);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(2, 15);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(2);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.Padding = new System.Windows.Forms.Padding(10);
            this.tableLayoutPanel2.RowCount = 3;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(519, 79);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(328, 43);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(73, 23);
            this.buttonRefresh.TabIndex = 5;
            this.buttonRefresh.Text = "Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // comboBoxDevices
            // 
            this.comboBoxDevices.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.comboBoxDevices.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDevices.FormattingEnabled = true;
            this.comboBoxDevices.Location = new System.Drawing.Point(13, 44);
            this.comboBoxDevices.Name = "comboBoxDevices";
            this.comboBoxDevices.Size = new System.Drawing.Size(309, 21);
            this.comboBoxDevices.TabIndex = 4;
            // 
            // label2
            // 
            this.tableLayoutPanel2.SetColumnSpan(this.label2, 3);
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(13, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(493, 30);
            this.label2.TabIndex = 6;
            this.label2.Text = "The attached devices are displayed below. Click \'Refresh\' to search for any new d" +
    "evices. Click \'Connect\' to establish a connection and transfer other messages.";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(407, 43);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(99, 23);
            this.buttonConnect.TabIndex = 7;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.textBoxLog, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.groupBox2, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.groupBox3, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.buttonClearLog, 0, 4);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(10, 10);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 120F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 173F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(527, 599);
            this.tableLayoutPanel1.TabIndex = 5;
            // 
            // textBoxLog
            // 
            this.textBoxLog.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBoxLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBoxLog.Location = new System.Drawing.Point(3, 396);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.ReadOnly = true;
            this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxLog.Size = new System.Drawing.Size(521, 171);
            this.textBoxLog.TabIndex = 6;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tableLayoutPanel3);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 230);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 10, 3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(521, 160);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "DEVICE SCRATCH-PAD MEMORY";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 3;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 97F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 294F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Controls.Add(this.label3, 1, 1);
            this.tableLayoutPanel3.Controls.Add(this.label1, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.textBoxReadAddress, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.buttonReadMemory, 2, 2);
            this.tableLayoutPanel3.Controls.Add(this.textBoxWriteAddress, 0, 4);
            this.tableLayoutPanel3.Controls.Add(this.textBoxWriteData, 1, 4);
            this.tableLayoutPanel3.Controls.Add(this.buttonWriteMemory, 2, 4);
            this.tableLayoutPanel3.Controls.Add(this.label6, 0, 3);
            this.tableLayoutPanel3.Controls.Add(this.label7, 1, 3);
            this.tableLayoutPanel3.Controls.Add(this.label8, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.textBoxReadLen, 1, 2);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(2);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.Padding = new System.Windows.Forms.Padding(7, 6, 7, 6);
            this.tableLayoutPanel3.RowCount = 6;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 46F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(515, 141);
            this.tableLayoutPanel3.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(106, 52);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Length (in bytes)";
            // 
            // textBoxReadLen
            // 
            this.textBoxReadLen.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.textBoxReadLen.Location = new System.Drawing.Point(106, 68);
            this.textBoxReadLen.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxReadLen.Name = "textBoxReadLen";
            this.textBoxReadLen.Size = new System.Drawing.Size(69, 20);
            this.textBoxReadLen.TabIndex = 4;
            this.textBoxReadLen.Text = "8";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 52);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Address";
            // 
            // textBoxReadAddress
            // 
            this.textBoxReadAddress.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.textBoxReadAddress.Location = new System.Drawing.Point(9, 68);
            this.textBoxReadAddress.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxReadAddress.Name = "textBoxReadAddress";
            this.textBoxReadAddress.Size = new System.Drawing.Size(93, 20);
            this.textBoxReadAddress.TabIndex = 0;
            this.textBoxReadAddress.Text = "0x00000000";
            // 
            // buttonReadMemory
            // 
            this.buttonReadMemory.Enabled = false;
            this.buttonReadMemory.Location = new System.Drawing.Point(400, 67);
            this.buttonReadMemory.Margin = new System.Windows.Forms.Padding(2);
            this.buttonReadMemory.Name = "buttonReadMemory";
            this.buttonReadMemory.Size = new System.Drawing.Size(104, 23);
            this.buttonReadMemory.TabIndex = 2;
            this.buttonReadMemory.Text = "Read Memory";
            this.buttonReadMemory.UseVisualStyleBackColor = true;
            this.buttonReadMemory.Click += new System.EventHandler(this.buttonReadMemory_Click);
            // 
            // textBoxWriteAddress
            // 
            this.textBoxWriteAddress.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.textBoxWriteAddress.Location = new System.Drawing.Point(9, 108);
            this.textBoxWriteAddress.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxWriteAddress.Name = "textBoxWriteAddress";
            this.textBoxWriteAddress.Size = new System.Drawing.Size(93, 20);
            this.textBoxWriteAddress.TabIndex = 6;
            this.textBoxWriteAddress.Text = "0x00000000";
            // 
            // textBoxWriteData
            // 
            this.textBoxWriteData.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.textBoxWriteData.Location = new System.Drawing.Point(106, 108);
            this.textBoxWriteData.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxWriteData.Name = "textBoxWriteData";
            this.textBoxWriteData.Size = new System.Drawing.Size(290, 20);
            this.textBoxWriteData.TabIndex = 7;
            this.textBoxWriteData.Text = "00 01 02 03 04 05 06 07";
            // 
            // buttonWriteMemory
            // 
            this.buttonWriteMemory.Enabled = false;
            this.buttonWriteMemory.Location = new System.Drawing.Point(400, 107);
            this.buttonWriteMemory.Margin = new System.Windows.Forms.Padding(2);
            this.buttonWriteMemory.Name = "buttonWriteMemory";
            this.buttonWriteMemory.Size = new System.Drawing.Size(104, 23);
            this.buttonWriteMemory.TabIndex = 8;
            this.buttonWriteMemory.Text = "Write Memory";
            this.buttonWriteMemory.UseVisualStyleBackColor = true;
            this.buttonWriteMemory.Click += new System.EventHandler(this.buttonWriteMemory_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 92);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(45, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "Address";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(106, 92);
            this.label7.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 13);
            this.label7.TabIndex = 10;
            this.label7.Text = "Data (in hex bytes)";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.tableLayoutPanel4);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(3, 110);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 10, 3, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(10);
            this.groupBox3.Size = new System.Drawing.Size(521, 107);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "STATUS STREAM";
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.ColumnCount = 5;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel4.Controls.Add(this.label9, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.buttonDisableStream, 0, 2);
            this.tableLayoutPanel4.Controls.Add(this.label4, 3, 1);
            this.tableLayoutPanel4.Controls.Add(this.labelKernelUtilization, 4, 2);
            this.tableLayoutPanel4.Controls.Add(this.labelKernelTicks, 3, 2);
            this.tableLayoutPanel4.Controls.Add(this.label5, 4, 1);
            this.tableLayoutPanel4.Controls.Add(this.buttonEnableStream, 0, 2);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(10, 23);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 3;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(501, 74);
            this.tableLayoutPanel4.TabIndex = 9;
            // 
            // buttonDisableStream
            // 
            this.buttonDisableStream.Enabled = false;
            this.buttonDisableStream.Location = new System.Drawing.Point(89, 45);
            this.buttonDisableStream.Margin = new System.Windows.Forms.Padding(2);
            this.buttonDisableStream.Name = "buttonDisableStream";
            this.buttonDisableStream.Size = new System.Drawing.Size(83, 23);
            this.buttonDisableStream.TabIndex = 13;
            this.buttonDisableStream.Text = "Disable";
            this.buttonDisableStream.UseVisualStyleBackColor = true;
            this.buttonDisableStream.Click += new System.EventHandler(this.buttonDisableStream_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(345, 30);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Kernel Ticks";
            // 
            // labelKernelUtilization
            // 
            this.labelKernelUtilization.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.labelKernelUtilization.AutoSize = true;
            this.labelKernelUtilization.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelKernelUtilization.Location = new System.Drawing.Point(416, 43);
            this.labelKernelUtilization.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelKernelUtilization.Name = "labelKernelUtilization";
            this.labelKernelUtilization.Padding = new System.Windows.Forms.Padding(7, 0, 0, 0);
            this.labelKernelUtilization.Size = new System.Drawing.Size(81, 26);
            this.labelKernelUtilization.TabIndex = 10;
            this.labelKernelUtilization.Text = "0.00%";
            // 
            // labelKernelTicks
            // 
            this.labelKernelTicks.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.labelKernelTicks.AutoSize = true;
            this.labelKernelTicks.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelKernelTicks.Location = new System.Drawing.Point(366, 43);
            this.labelKernelTicks.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelKernelTicks.Name = "labelKernelTicks";
            this.labelKernelTicks.Size = new System.Drawing.Size(24, 26);
            this.labelKernelTicks.TabIndex = 9;
            this.labelKernelTicks.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(415, 30);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Padding = new System.Windows.Forms.Padding(7, 0, 0, 0);
            this.label5.Size = new System.Drawing.Size(84, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "CPU Utilization";
            // 
            // buttonEnableStream
            // 
            this.buttonEnableStream.Enabled = false;
            this.buttonEnableStream.Location = new System.Drawing.Point(2, 45);
            this.buttonEnableStream.Margin = new System.Windows.Forms.Padding(2);
            this.buttonEnableStream.Name = "buttonEnableStream";
            this.buttonEnableStream.Size = new System.Drawing.Size(83, 23);
            this.buttonEnableStream.TabIndex = 8;
            this.buttonEnableStream.Text = "Enable";
            this.buttonEnableStream.UseVisualStyleBackColor = true;
            this.buttonEnableStream.Click += new System.EventHandler(this.buttonEnableStream_Click);
            // 
            // buttonClearLog
            // 
            this.buttonClearLog.Location = new System.Drawing.Point(3, 573);
            this.buttonClearLog.Name = "buttonClearLog";
            this.buttonClearLog.Size = new System.Drawing.Size(105, 23);
            this.buttonClearLog.TabIndex = 8;
            this.buttonClearLog.Text = "Clear Log";
            this.buttonClearLog.UseVisualStyleBackColor = true;
            this.buttonClearLog.Click += new System.EventHandler(this.buttonClearLog_Click);
            // 
            // label8
            // 
            this.tableLayoutPanel3.SetColumnSpan(this.label8, 2);
            this.label8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label8.Location = new System.Drawing.Point(10, 6);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(385, 46);
            this.label8.TabIndex = 11;
            this.label8.Text = "Read and write an area of memory that is provided by the device to demonstrate th" +
    "e use of request-response messages.";
            // 
            // label9
            // 
            this.tableLayoutPanel4.SetColumnSpan(this.label9, 3);
            this.label9.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label9.Location = new System.Drawing.Point(3, 0);
            this.label9.Name = "label9";
            this.tableLayoutPanel4.SetRowSpan(this.label9, 2);
            this.label9.Size = new System.Drawing.Size(337, 43);
            this.label9.TabIndex = 14;
            this.label9.Text = "Control a status stream from the device that demonstrates the use of unsolicited " +
    "messages.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(547, 619);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Padding = new System.Windows.Forms.Padding(10);
            this.Text = "DZX Data Link Demo";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.ComboBox comboBoxDevices;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxReadLen;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxReadAddress;
        private System.Windows.Forms.Button buttonEnableStream;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.TextBox textBoxWriteAddress;
        private System.Windows.Forms.TextBox textBoxWriteData;
        private System.Windows.Forms.Label labelKernelUtilization;
        private System.Windows.Forms.Label labelKernelTicks;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button buttonDisableStream;
        private System.Windows.Forms.Button buttonReadMemory;
        private System.Windows.Forms.Button buttonWriteMemory;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonClearLog;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
    }
}

