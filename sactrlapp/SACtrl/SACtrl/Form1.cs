using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Windows.Forms.DataVisualization.Charting;
using System.Text.RegularExpressions;

namespace SACtrl
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //CheckForIllegalCrossThreadCalls = false;
        }
        public const int BufferSize = 1024 * 1024 * 20;
        public byte[] pBuffer = new byte[BufferSize];
        float[] m_pfData;   // 数据缓冲区
        double[] m_pData;   // 绘图缓冲区
        int m_nLen = 0;				// 数据缓冲区长度
        double m_dRef = 0.0;			// 参考电平
        int m_nDBDiv = 10;			// dB/
        Object locked = new object();  //程序锁
        NetworkStream stream = null;
        TcpClient tcp = null;
        public delegate void MyInvoke();

        private void ConnectCallback() 
        {            
            try 
            {  
                byte[] sendData;
                byte[] byPackage = new byte[] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
                byte[] tmpbyte = new byte[] { 0x00, 0x00, 0x00, 0x00 };
                int nCount = 0;
                int res = 0, nPackage = 0;
                int nBit = 0;
                string strResponse = "";
                while (true)
                {                    
                    nCount = 0;
                    try
                    {
                        lock (locked)
                        {
                            // 得到参考
                            sendData = Encoding.ASCII.GetBytes("DISPlay:WINDow:TRACe:Y:RLEVel?\r\n");
                            stream.Write(sendData, 0, sendData.Length);     // 发往服务器
                            do
                            {
                                pBuffer = new byte[BufferSize];
                                stream.Read(pBuffer, 0, pBuffer.Length);//接受服务器回报的字符串 
                                nCount++;
                                if (nCount == 10)
                                {
                                    return;
                                }
                                strResponse = Encoding.ASCII.GetString(pBuffer).Trim();//从服务器接受到的字符串
                                res = strResponse.IndexOf("\0");
                            } while (res == 0 || strResponse.IndexOf("trac") > -1);
                            strResponse = strResponse.Substring(strResponse.IndexOf("DISPlay:WINDow:TRACe:Y:RLEVel?\r\n"), res);
                            if (strResponse.Length < 500)
                            {
                                int nStart = strResponse.IndexOf("\r\n");
                                int nEnd = strResponse.LastIndexOf("\r\n");
                                strResponse = strResponse.Substring(nStart + 2, nEnd - nStart - 2);
                                m_dRef = double.Parse(strResponse);//参考值
                            }
                            // 得到波形
                            sendData = Encoding.ASCII.GetBytes("trac?\r\n");
                            stream.Write(sendData, 0, sendData.Length);
                            nCount = stream.Read(pBuffer, 0, pBuffer.Length);//接受服务器回报的字符串
                            strResponse = Encoding.ASCII.GetString(pBuffer).Trim();
                            res = strResponse.IndexOf("\0");
                            strResponse = strResponse.Substring(strResponse.IndexOf("trac?\r\n"), res);
                            if (strResponse.Length > 0)
                            {
                                int nStart = strResponse.IndexOf("\r\n") + 2;
                                nCount = nCount - nStart;
                                Array.Copy(pBuffer, nStart, pBuffer, 0, nCount);
                                if (pBuffer[0] == '#')//35
                                {
                                    nBit = pBuffer[1] - '0';//48
                                    Array.Copy(pBuffer, 2, byPackage, 0, nBit);
                                    nPackage = int.Parse(Encoding.ASCII.GetString(byPackage));
                                    /* while (nCount < nPackage)
                                    {
                                        stream.BeginRead(pBuffer, nCount, pBuffer.Length, null, stream);
                                        nCount += dwRecv;
                                    }*/
                                    Array.Copy(pBuffer, 2 + nBit, pBuffer, 0, nPackage);
                                    nCount = nPackage / sizeof(float);
                                    m_nLen = nCount;
                                    m_pfData = new float[nCount];
                                    m_pData = new double[nCount];
                                    //Array.Copy(pBuffer, 0, m_pfData, 0, nPackage);
                                    for (int i = 0; i < nCount; i++)
                                    {
                                        tmpbyte[0] = pBuffer[4 * i];
                                        tmpbyte[1] = pBuffer[4 * i + 1];
                                        tmpbyte[2] = pBuffer[4 * i + 2];
                                        tmpbyte[3] = pBuffer[4 * i + 3];
                                        m_pData[i] = m_pfData[i] = BitConverter.ToSingle(tmpbyte, 0);
                                    }
                                    Method_Draw();
                                }
                            }
                        }                        
                    }
                    catch
                    {
                        //MessageBox.Show("error!");
                    }
                    finally
                    {
                       
                    }
                    Thread.Sleep(20);
               }                    
            
 
            }catch (Exception e) {
                MessageBox.Show("无法链接到设备!!");
            }
        }

        private void Method_Draw()
        {
            //this.Invoke
            this.BeginInvoke(new MyInvoke(chart_Draw));
        }

        private void chart_Draw()
        {
            if (m_nLen > 0)
            {
                try
                {
                    chart1.ChartAreas[0].AxisX.Maximum = m_nLen;
                    //chart1.ChartAreas[0].AxisX.Interval = 50;
                    chart1.ChartAreas[0].AxisY.Interval = 8;
                    chart1.ChartAreas[0].AxisY.Minimum = m_dRef - m_nDBDiv * 8;
                    chart1.ChartAreas[0].AxisY.Maximum = m_dRef;
                    chart1.Series["Series1"].ChartType = SeriesChartType.Spline;//曲线类型 
                    if (chart1.Series["Series1"].Points.Count > 0)
                    {
                        for (int i = 0; i < m_nLen; i++)
                        {
                            chart1.Series["Series1"].Points[i].SetValueY(m_pData[i]);
                        }
                    }
                    else
                    {
                        for (int i = 0; i < m_nLen; i++)
                        {
                            chart1.Series["Series1"].Points.AddY(m_pData[i]);
                        }
                    }         
                        
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message.ToString());
                }
            }          
        }

        private void btn_connect_Click(object sender, EventArgs e)
        {
            if (tcp == null)
            {
                tcp = new TcpClient();
                IPAddress IP;
                try
                {
                    IP = IPAddress.Parse(txt_ip.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("无效的IP地址！");
                    return;
                }
                Thread.CurrentThread.Name = "main";
                try
                {
                    if (this.Ping(txt_ip.Text))
                    {
                        tcp.Connect(IP, 5025);
                        if (tcp.Connected)
                        {
                            stream = tcp.GetStream();
                            Thread worker = new Thread(ConnectCallback);
                            worker.Name = "worker";
                            worker.Start();
                        }
                        else
                        {
                            MessageBox.Show("设备连接失败!");
                        }
                    }
                    else
                    {
                        MessageBox.Show("无法连接设备，请确认设备连接正常!");
                    }
                }
                catch { MessageBox.Show("设备连接失败!"); }       

            }
            
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void btn_setcenter_Click(object sender, EventArgs e)
        {            
            string cmdstr = "FREQuency:CENTer " + txt_center.Text+"\r\n";           
            lock (locked)
            {
                LanSendCmd(cmdstr, true);
            }      
        }

        private bool LanSendCmd(string cmdstr, bool IsEcho)
        {
            byte[] send = new byte[10000];
            byte[] recv = new byte[10000];
            int nCount = 0;
            string strResponse = "";
            send = Encoding.ASCII.GetBytes(cmdstr);
            try
            {
                stream.Write(send, 0, send.Length);     // 发往服务器
                if (IsEcho)
                {
                    nCount = stream.Read(recv, 0, recv.Length);//接受服务器回报的字符串 
                    if (nCount < 1)
                    {
                        return false;
                    }
                    recv[nCount] = 0;
                    strResponse = Encoding.ASCII.GetString(recv).Trim();//从服务器接受到的字符串
                    if (strResponse.LastIndexOf("\r\n") == 0)
                    {
                        return true;
                    }
                }

            }
            catch { }
            return true;
        }

        private void LanSendCmd(string cmdstr, out double result)
        {
            byte[] send = new byte[10000];
            byte[] recv = new byte[10000];
            int nCount = 0;
            string strResponse = "";
            send = Encoding.ASCII.GetBytes(cmdstr);
            try
            {
                stream.Write(send, 0, send.Length);     // 发往服务器
                nCount = stream.Read(recv, 0, recv.Length);//接受服务器回报的字符串 
                strResponse = Encoding.ASCII.GetString(recv).Trim();
                if (nCount > 1)
                {
                    int nStart = strResponse.IndexOf("\r\n");
                    int nEnd = strResponse.LastIndexOf("\r\n");
                    strResponse = strResponse.Substring(nStart + 2, nEnd - nStart - 2);
                    result = double.Parse(strResponse);//参考值
                    return;
                }
            }
            catch { }
            result = 0;
        }

        // 通过socket读取数据，读取CString类型的数据
        private void LanSendCmd(string cmdstr, out string szVal)
        {
            byte[] send = new byte[10000];
            byte[] recv = new byte[10000];
            int nCount = 0;
            string strResponse = "";

            send = Encoding.ASCII.GetBytes(cmdstr);
            try
            {
                stream.Write(send, 0, send.Length);     // 发往服务器
                nCount = stream.Read(recv, 0, recv.Length);//接受服务器回报的字符串 
                strResponse = Encoding.ASCII.GetString(recv).Trim();
                if (nCount > 1)
                {
                    int nStart = strResponse.IndexOf("\r\n");
                    int nEnd = strResponse.LastIndexOf("\r\n");
                    strResponse = strResponse.Substring(nStart + 2, nEnd - nStart - 2);
                    szVal = strResponse;
                    return;
                }
            }
            catch { }
            szVal = "";
            return;
        }

        public static int GetNumber(string str)
        {
            int number = 0;
            string num = null;
            foreach (char item in str)
            {
                if (item >= 48 && item <= 58)
                {
                    num += item;
                }
            }
            number = int.Parse(num);
            return number;
        } 

        private void btn_catv_Click(object sender, EventArgs e)
        {
            int ch = 0;
            double result = 0;
            /*try
            {
                int.TryParse(txt_ch.Text, out ch);
                if (ch > 10 || ch < 1)
                {
                    MessageBox.Show("错误的频道~~");
                    return;
                }
            }
            catch {
                MessageBox.Show("错误的频道~~");
                return;
            }*/
            ch = GetNumber(txt_ch.Text);
            string cmdstr = "CATV:CHANnel:SELect "+ ch +"\r\n";
            lock (locked)
            {
                string mode = "";
                LanSendCmd("INSTrument?\r\n", out mode);
                //设置频谱仪工作模式
                LanSendCmd("INSTrument CATV\r\n", true);
                LanSendCmd("INSTrument?\r\n", out mode);
                //激活频道表
                LanSendCmd("PLAN:ACTIve DS20 china\r\n", true);
                //设置被测频道号
                LanSendCmd(cmdstr, true);
                //设置载噪比开关
                LanSendCmd("ATV:CCN:STATe ON\r\n", true);
                //设置单次扫描与否
                LanSendCmd("ATV:CCN:CONTINUE\r\n", true);
                //读取载噪比数值
                LanSendCmd("ATV:CCN?\r\n", out result);
                txt_cnn.Text = result.ToString();
                LanSendCmd("ATV:CCN:STATe OFF\r\n", true);
                //读取载波幅度
                //LanSendCmd("ATV:CARR:VIDEo?\r\n", out result);
                //txt_video.Text = result.ToString();
                //读取CTB数值
                //LanSendCmd("ATV:CTB?\r\n", out result);
                //txt_ctb.Text = result.ToString();
                //读取CSO数值
                //LanSendCmd("ATV:CSO?\r\n", out result);
                //txt_cso.Text = result.ToString();
            }  
    
        }  

        public bool Ping(string ip)
        {
            System.Net.NetworkInformation.Ping p = new System.Net.NetworkInformation.Ping();
            System.Net.NetworkInformation.PingOptions options = new System.Net.NetworkInformation.PingOptions();
            options.DontFragment = true;
            string data = "Test Data!";
            byte[] buffer = Encoding.ASCII.GetBytes(data);
            int timeout = 1000; // Timeout 时间，单位：毫秒  
            System.Net.NetworkInformation.PingReply reply = p.Send(ip, timeout, buffer, options);
            if (reply.Status == System.Net.NetworkInformation.IPStatus.Success)
                return true;
            else
                return false;
        }

        
    }
}
