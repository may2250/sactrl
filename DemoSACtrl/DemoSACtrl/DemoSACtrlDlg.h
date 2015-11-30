// DemoSACtrlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxmt.h"
#include "DevGDI.h"
#include "SocketSA.h"


// CDemoSACtrlDlg 对话框
class CDemoSACtrlDlg : public CDialog
{
// 构造
public:
	CDemoSACtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEMOSACTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CDevGDI m_GDI;		// 绘图对象
	CSocketSA m_Socket; // 网络对象
	CSocketSA m_Socket2; // 网络对象

public:
	float* m_pfData;		// 数据缓冲区
	double* m_pData;		// 绘图缓冲区
	int m_nLen;				// 数据缓冲区长度

	double m_dRef;			// 参考电平
	int m_nDBDiv;			// dB/

	CWinThread* m_pThreadData;
	CWinThread* m_pThreadDraw;

	BOOL m_IsStop;

	CCriticalSection m_CrSect;	// 临界区, 保护数据缓冲区用
	CCriticalSection m_CrCtrl;	// 临界区, 防止控制指令和采数指令冲突

	HANDLE m_hMap;
	void* m_pMemData;

public:
	static UINT ThreadData(LPVOID lpvoid);
	static UINT ThreadDataFromMem(LPVOID lpvoid);
	static UINT ThreadDraw(LPVOID lpvoid);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAddr;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnClose();
	void InitGDI();
	afx_msg void OnBnClickedSetCenter();
	afx_msg void OnBnClickedSetSpan();
	void SendCommand(CString strCmd);
	CIPAddressCtrl m_IPAddrSend;
	/*afx_msg void OnBnClickedConnect2();
	afx_msg void OnBnClickedButton1();*/
	afx_msg void OnBnClickedDisableWave();
	afx_msg void OnBnClickedEnablewave();
	afx_msg void OnBnClickedReadFromshare();
};
