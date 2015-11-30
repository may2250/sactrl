// DemoSACtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxmt.h"
#include "DevGDI.h"
#include "SocketSA.h"


// CDemoSACtrlDlg �Ի���
class CDemoSACtrlDlg : public CDialog
{
// ����
public:
	CDemoSACtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMOSACTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CDevGDI m_GDI;		// ��ͼ����
	CSocketSA m_Socket; // �������
	CSocketSA m_Socket2; // �������

public:
	float* m_pfData;		// ���ݻ�����
	double* m_pData;		// ��ͼ������
	int m_nLen;				// ���ݻ���������

	double m_dRef;			// �ο���ƽ
	int m_nDBDiv;			// dB/

	CWinThread* m_pThreadData;
	CWinThread* m_pThreadDraw;

	BOOL m_IsStop;

	CCriticalSection m_CrSect;	// �ٽ���, �������ݻ�������
	CCriticalSection m_CrCtrl;	// �ٽ���, ��ֹ����ָ��Ͳ���ָ���ͻ

	HANDLE m_hMap;
	void* m_pMemData;

public:
	static UINT ThreadData(LPVOID lpvoid);
	static UINT ThreadDataFromMem(LPVOID lpvoid);
	static UINT ThreadDraw(LPVOID lpvoid);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
