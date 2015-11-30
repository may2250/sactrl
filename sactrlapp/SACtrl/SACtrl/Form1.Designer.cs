namespace SACtrl
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.btn_connect = new System.Windows.Forms.Button();
            this.txt_ip = new System.Windows.Forms.MaskedTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.txt_center = new System.Windows.Forms.TextBox();
            this.btn_setcenter = new System.Windows.Forms.Button();
            this.btn_catv = new System.Windows.Forms.Button();
            this.txt_ch = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_cnn = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txt_video = new System.Windows.Forms.TextBox();
            this.txt_ctb = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txt_cso = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_connect
            // 
            this.btn_connect.Location = new System.Drawing.Point(264, 12);
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.Size = new System.Drawing.Size(75, 29);
            this.btn_connect.TabIndex = 0;
            this.btn_connect.Text = "链接";
            this.btn_connect.UseVisualStyleBackColor = true;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // txt_ip
            // 
            this.txt_ip.Location = new System.Drawing.Point(66, 12);
            this.txt_ip.Name = "txt_ip";
            this.txt_ip.Size = new System.Drawing.Size(192, 25);
            this.txt_ip.TabIndex = 1;
            this.txt_ip.Text = "192.168.1.234";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "IP:";
            // 
            // chart1
            // 
            this.chart1.BackSecondaryColor = System.Drawing.Color.WhiteSmoke;
            chartArea2.AxisX.Interval = 50D;
            chartArea2.AxisX.IsLabelAutoFit = false;
            chartArea2.AxisX.LabelStyle.Enabled = false;
            chartArea2.AxisY.LabelStyle.Format = "N3";
            chartArea2.BackColor = System.Drawing.Color.DarkGray;
            chartArea2.Name = "ChartArea1";
            chartArea2.Position.Auto = false;
            chartArea2.Position.Height = 100F;
            chartArea2.Position.Width = 100F;
            this.chart1.ChartAreas.Add(chartArea2);
            this.chart1.Location = new System.Drawing.Point(31, 270);
            this.chart1.Name = "chart1";
            this.chart1.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Bright;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.LabelBackColor = System.Drawing.Color.White;
            series2.LabelBorderColor = System.Drawing.Color.White;
            series2.MarkerColor = System.Drawing.Color.Lime;
            series2.Name = "Series1";
            series2.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            this.chart1.Series.Add(series2);
            this.chart1.Size = new System.Drawing.Size(1066, 450);
            this.chart1.TabIndex = 4;
            this.chart1.Text = "chart1";
            // 
            // txt_center
            // 
            this.txt_center.Location = new System.Drawing.Point(395, 15);
            this.txt_center.Name = "txt_center";
            this.txt_center.Size = new System.Drawing.Size(100, 25);
            this.txt_center.TabIndex = 5;
            // 
            // btn_setcenter
            // 
            this.btn_setcenter.AutoSize = true;
            this.btn_setcenter.Location = new System.Drawing.Point(514, 15);
            this.btn_setcenter.Name = "btn_setcenter";
            this.btn_setcenter.Size = new System.Drawing.Size(107, 26);
            this.btn_setcenter.TabIndex = 6;
            this.btn_setcenter.Text = "设置中心频率";
            this.btn_setcenter.UseVisualStyleBackColor = true;
            this.btn_setcenter.Click += new System.EventHandler(this.btn_setcenter_Click);
            // 
            // btn_catv
            // 
            this.btn_catv.Location = new System.Drawing.Point(772, 15);
            this.btn_catv.Name = "btn_catv";
            this.btn_catv.Size = new System.Drawing.Size(102, 26);
            this.btn_catv.TabIndex = 7;
            this.btn_catv.Text = "开始测试";
            this.btn_catv.UseVisualStyleBackColor = true;
            this.btn_catv.Click += new System.EventHandler(this.btn_catv_Click);
            // 
            // txt_ch
            // 
            this.txt_ch.Location = new System.Drawing.Point(666, 15);
            this.txt_ch.Name = "txt_ch";
            this.txt_ch.Size = new System.Drawing.Size(100, 25);
            this.txt_ch.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(900, 21);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 15);
            this.label2.TabIndex = 9;
            this.label2.Text = "载噪比CNN：";
            // 
            // txt_cnn
            // 
            this.txt_cnn.Location = new System.Drawing.Point(997, 16);
            this.txt_cnn.Name = "txt_cnn";
            this.txt_cnn.Size = new System.Drawing.Size(100, 25);
            this.txt_cnn.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(900, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 15);
            this.label3.TabIndex = 11;
            this.label3.Text = "载波幅度：";
            // 
            // txt_video
            // 
            this.txt_video.Location = new System.Drawing.Point(997, 55);
            this.txt_video.Name = "txt_video";
            this.txt_video.Size = new System.Drawing.Size(100, 25);
            this.txt_video.TabIndex = 12;
            // 
            // txt_ctb
            // 
            this.txt_ctb.Location = new System.Drawing.Point(997, 98);
            this.txt_ctb.Name = "txt_ctb";
            this.txt_ctb.Size = new System.Drawing.Size(100, 25);
            this.txt_ctb.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(900, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(76, 15);
            this.label4.TabIndex = 13;
            this.label4.Text = "CTB数值：";
            // 
            // txt_cso
            // 
            this.txt_cso.Location = new System.Drawing.Point(997, 141);
            this.txt_cso.Name = "txt_cso";
            this.txt_cso.Size = new System.Drawing.Size(100, 25);
            this.txt_cso.TabIndex = 16;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(900, 144);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(76, 15);
            this.label5.TabIndex = 15;
            this.label5.Text = "CSO数值：";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1123, 732);
            this.Controls.Add(this.txt_cso);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txt_ctb);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txt_video);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txt_cnn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txt_ch);
            this.Controls.Add(this.btn_catv);
            this.Controls.Add(this.btn_setcenter);
            this.Controls.Add(this.txt_center);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_ip);
            this.Controls.Add(this.btn_connect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.MaskedTextBox txt_ip;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.TextBox txt_center;
        private System.Windows.Forms.Button btn_setcenter;
        private System.Windows.Forms.Button btn_catv;
        private System.Windows.Forms.TextBox txt_ch;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_cnn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txt_video;
        private System.Windows.Forms.TextBox txt_ctb;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txt_cso;
        private System.Windows.Forms.Label label5;
    }
}

