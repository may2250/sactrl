// DemoSACtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DemoSACtrl.h"
#include "DemoSACtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDemoSACtrlDlg �Ի���




CDemoSACtrlDlg::CDemoSACtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoSACtrlDlg::IDD, pParent)
{
	m_pfData = NULL;
	m_pData = NULL;
	m_IsStop = FALSE;
	m_nDBDiv = 10;
	m_dRef = 0.0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoSACtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddr);
}

BEGIN_MESSAGE_MAP(CDemoSACtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_CONNECT, &CDemoSACtrlDlg::OnBnClickedConnect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(BTN_SET_CENTER, &CDemoSACtrlDlg::OnBnClickedSetCenter)
	ON_BN_CLICKED(BTN_SET_SPAN, &CDemoSACtrlDlg::OnBnClickedSetSpan)

	ON_BN_CLICKED(BTN_DISABLE_WAVE, &CDemoSACtrlDlg::OnBnClickedDisableWave)
	ON_BN_CLICKED(BTN_ENABLEWAVE, &CDemoSACtrlDlg::OnBnClickedEnablewave)
	ON_BN_CLICKED(BTN_READ_FROMSHARE, &CDemoSACtrlDlg::OnBnClickedReadFromshare)
END_MESSAGE_MAP()


// CDemoSACtrlDlg ��Ϣ�������

BOOL CDemoSACtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitGDI();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDemoSACtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoSACtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CDemoSACtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDemoSACtrlDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strIPAddr;
	m_IPAddr.GetWindowText(strIPAddr);
	BOOL bSuc =  m_Socket.ConnectTo(strIPAddr, _T("5025"),PF_INET, SOCK_STREAM, true, 5, 1 );

	// �������ݲɼ��߳�
	if (bSuc) {
		m_pThreadData = AfxBeginThread(ThreadData, this);
		m_pThreadDraw = AfxBeginThread(ThreadDraw, this);
	}
}

void CDemoSACtrlDlg::InitGDI() {
	CRect rc;
	GetDlgItem(ST_DRAW)->GetWindowRect(rc);
	
	m_GDI.GDI_Init(rc, GetDlgItem(ST_DRAW)->m_hWnd, UD_BLACK);

	m_GDI.GDI_SetXDepartment(_T("MHz"));
	m_GDI.GDI_SetSpanY(18.8, 98.8);
	m_GDI.GDI_SetGridLineNum(10, DIV_LOG);
	m_GDI.GDI_SetGridStyle( UD_LIGHT_GREY, 1, 1, DEV_GRID_SPECTRUM );
	m_GDI.GDI_SetTextEnable(false, true);
	m_GDI.GDI_SetLine(	UD_GREEN, 1, 
		UD_RED, 1, 
		UD_BLUE, 1,
		UD_ORANGE, 1, 
		UD_LAVENDER, 1, 
		UD_ROYAL_BLUE, 1, 
		UD_MAROON, 1, 
		UD_LIGHT_GREY,1, 
		UD_EQUALIZER, 1, 
		UD_TAN, 1);

	m_GDI.GDI_EnableGrid( true );
	m_GDI.GDI_EnableGridRound ( false );
	m_GDI.GDI_EnableGridPoint ( false );
}

// ���ݲɼ��߳�
UINT CDemoSACtrlDlg::ThreadData( LPVOID lpvoid )
{
	CDemoSACtrlDlg* pDlg = (CDemoSACtrlDlg*)lpvoid;
	
	int nBufSize = 1024*1024*20;
	BYTE* pBuffer = new BYTE [nBufSize];	// ���뻺����
	
	UINT nRecv = 0;	// �յ��˶�������
	int nCount = 0;
	while(true)
	{
		if (pDlg->m_IsStop)
			break;

		pDlg->m_CrCtrl.Lock();
		// �õ��ο�
		pDlg->m_Socket.LanSendCmd(_T("DISPlay:WINDow:TRACe:Y:RLEVel?"), 10000, pDlg->m_dRef);

		Sleep(10);
		// �õ�����
		pDlg->m_Socket.ReceiveBinary("trac?", pBuffer, nRecv, 10000, nBufSize);
		nCount = nRecv/sizeof(float);

		pDlg->m_CrCtrl.Unlock();

		pDlg->m_CrSect.Lock();
		if (pDlg->m_pfData == NULL) {

			pDlg->m_nLen = nCount;
			pDlg->m_pfData = new float[nCount];
			pDlg->m_pData = new double [nCount];
			ZeroMemory(pDlg->m_pfData, nCount*sizeof(float));
			ZeroMemory(pDlg->m_pData, nCount*sizeof(double));
		}
		else if (pDlg->m_nLen != nCount) {
			pDlg->m_nLen = nCount;
			if (pDlg->m_pfData != NULL) {
				delete [] pDlg->m_pfData;
			}
			if (pDlg->m_pData != NULL) {
				delete [] pDlg->m_pData;
			}

			pDlg->m_pfData = new float[nCount];
			pDlg->m_pData = new double [nCount];
			ZeroMemory(pDlg->m_pfData, nCount*sizeof(float));
			ZeroMemory(pDlg->m_pData, nCount*sizeof(double));
		}

		memcpy(pDlg->m_pfData, pBuffer, nRecv);
		for (int i=0; i<nCount; i++) {
			pDlg->m_pData[i] = pDlg->m_pfData[i];
		}

		pDlg->m_CrSect.Unlock();
	}

	delete [] pBuffer;
	return S_OK;
}


UINT CDemoSACtrlDlg::ThreadDraw( LPVOID lpvoid )
{
	CDemoSACtrlDlg* pDlg = (CDemoSACtrlDlg*)lpvoid;

	while(true) {

		if (pDlg->m_IsStop)
			break;
	
		if (pDlg->m_pData == NULL) {
			Sleep(10);
			continue;
		}

		pDlg->m_CrSect.Lock();
		pDlg->m_GDI.GDI_SetSpanY(pDlg->m_dRef - pDlg->m_nDBDiv*8, pDlg->m_dRef);
		pDlg->m_GDI.GDI_Draw(pDlg->m_pData, pDlg->m_nLen);
		pDlg->m_CrSect.Unlock();
		Sleep(30);
	}

	return S_OK;
}

void CDemoSACtrlDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_IsStop = TRUE;
	WaitForSingleObject(m_pThreadData->m_hThread, 50*1000);

	if (m_pfData != NULL) {
		delete [] m_pfData;
	}

	if (m_pData != NULL) {
		delete [] m_pData;
	}

	CDialog::OnClose();
}

void CDemoSACtrlDlg::SendCommand(CString strCmd) {
	m_CrCtrl.Lock();
	m_Socket.LanSendCmd(strCmd, 1000, TRUE);
	m_CrCtrl.Unlock();
}

void CDemoSACtrlDlg::OnBnClickedSetCenter()
{
	CString strCmd = _T("FREQuency:CENTer ");
	CString strVal = _T("");
	GetDlgItem(EDT_CENTER)->GetWindowText(strVal);
	strCmd += strVal;

	SendCommand(strCmd);
}

void CDemoSACtrlDlg::OnBnClickedSetSpan()
{
	CString strCmd = _T("FREQuency:SPAN ");
	CString strVal = _T("");
	GetDlgItem(EDT_SPAN)->GetWindowText(strVal);
	strCmd += strVal;

	SendCommand(strCmd);
}

//void CDemoSACtrlDlg::OnBnClickedConnect2()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString strIPAddr;
//	m_IPAddrSend.GetWindowText(strIPAddr);
//	BOOL bSuc =  m_Socket2.ConnectTo(strIPAddr, _T("1111"),PF_INET, SOCK_STREAM, true, 5, 1 );
//
//	// �������ݲɼ��߳�
//	if (bSuc) {
//		 MessageBox(_T("Connect OK"));
//	}
//}

//void CDemoSACtrlDlg::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	char* pBuf = "abcdefghij";
//	char cBuf[1000] = {0};
//
//	for (int i=0; i<100; i++) {
//		strcat(cBuf, pBuf);
//	}
//
//	m_Socket2.WriteComm((BYTE*)cBuf, strlen(cBuf), 10000);
//}
//
void CDemoSACtrlDlg::OnBnClickedDisableWave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString strCmd = _T("DISPlay:ENABle OFF");
	CString strVal = _T("");
	GetDlgItem(EDT_SPAN)->GetWindowText(strVal);
	strCmd += strVal;

	SendCommand(strCmd);
}

void CDemoSACtrlDlg::OnBnClickedEnablewave()
{
	CString strCmd = _T("DISPlay:ENABle ON");
	CString strVal = _T("");
	GetDlgItem(EDT_SPAN)->GetWindowText(strVal);
	strCmd += strVal;

	SendCommand(strCmd);
}

void CDemoSACtrlDlg::OnBnClickedReadFromshare()
{
	m_hMap = OpenFileMapping(FILE_MAP_READ, FALSE, _T("TestBuff"));
	if (m_hMap == NULL)
		return;

	m_pMemData = (void*)MapViewOfFile(m_hMap, FILE_MAP_READ, 0, 0, 0);
	if (m_pMemData == NULL)
	{
		CloseHandle(m_hMap);
		m_hMap = NULL;
		return;
	}

	m_pThreadData = AfxBeginThread(ThreadDataFromMem, this);
	m_pThreadDraw = AfxBeginThread(ThreadDraw, this);
}

UINT CDemoSACtrlDlg::ThreadDataFromMem( LPVOID lpvoid )
{
	CDemoSACtrlDlg* pDlg = (CDemoSACtrlDlg*)lpvoid;

	int nBufSize = 1024*1024*20;
	BYTE* pBuffer = new BYTE [nBufSize];	// ���뻺����

	UINT nRecv = 0;	// �յ��˶�������
	int nCount = 0;
	sa_frame frame;

	while(true)
	{
		if (pDlg->m_IsStop)
			break;

		pDlg->m_CrCtrl.Lock();
		// �õ��ο�
		//pDlg->m_Socket.LanSendCmd(_T("DISPlay:WINDow:TRACe:Y:RLEVel?"), 10000, pDlg->m_dRef);
		pDlg->m_dRef = 98;

		memcpy(&frame, pDlg->m_pMemData, sizeof(sa_frame));
		nRecv = frame.nDataLen*sizeof(float);
		nCount = frame.nDataLen;
	
		Sleep(10);
		// �õ�����
		//pDlg->m_Socket.ReceiveBinary("trac?", pBuffer, nRecv, 10000, nBufSize);
		//nCount = nRecv/sizeof(float);

		pDlg->m_CrCtrl.Unlock();

		pDlg->m_CrSect.Lock();
		if (pDlg->m_pfData == NULL) {

			pDlg->m_nLen = nCount;
			pDlg->m_pfData = new float[nCount];
			pDlg->m_pData = new double [nCount];
			ZeroMemory(pDlg->m_pfData, nCount*sizeof(float));
			ZeroMemory(pDlg->m_pData, nCount*sizeof(double));
		}
		else if (pDlg->m_nLen != nCount) {	

			pDlg->m_nLen = nCount;
			if (pDlg->m_pfData != NULL) {
				delete [] pDlg->m_pfData;
			}
			if (pDlg->m_pData != NULL) {
				delete [] pDlg->m_pData;
			}

			pDlg->m_pfData = new float[nCount];
			pDlg->m_pData = new double [nCount];
			ZeroMemory(pDlg->m_pfData, nCount*sizeof(float));
			ZeroMemory(pDlg->m_pData, nCount*sizeof(double));
		}

		memcpy(pDlg->m_pfData, frame.fData, nRecv);
		for (int i=0; i<nCount; i++) {
			pDlg->m_pData[i] = pDlg->m_pfData[i];
		}

		pDlg->m_CrSect.Unlock();
	}

	delete [] pBuffer;
	return S_OK;
}
