// DemoSACtrl.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "DemoSACtrl.h"
#include "DemoSACtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WSA_VERSION  MAKEWORD(2,2)
#define MAX_HOSTNAME 256
#define MAX_HOSTADDR 40
// CDemoSACtrlApp

BEGIN_MESSAGE_MAP(CDemoSACtrlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDemoSACtrlApp ����

CDemoSACtrlApp::CDemoSACtrlApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDemoSACtrlApp ����

CDemoSACtrlApp theApp;


// CDemoSACtrlApp ��ʼ��

BOOL CDemoSACtrlApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��ʼ������
	WSADATA	WSAData = { 0 };
	if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
	{
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
			HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
			::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

		WSACleanup();
	}


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDemoSACtrlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
