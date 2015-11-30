#pragma once
#include "socketmanager.h"

const int PACKAGE_SIZE = 1024;
const int PACKAGE_BUF_SIZE = 1030;
const DWORD SOCKET_TIME_OUT = 20000;/*60000*//*5000*/
const DWORD SOCKET_TIME_OUT_DTV = 60000;		// 2s
const DWORD SOCKET_TIME_OUT_CHSCAN = 20000;	// ��ʱʱ��

class CSocketInterface :
	public CSocketManager
{
public:
	CSocketInterface(void);
public:
	~CSocketInterface(void);

public:
	int m_nCurrPort;	// ��ǰ���ӵĶ˿�
	CString m_nCurrServer; // ��ǰ������
	const static int RECV_BUF = 10000;
	const static int SEND_BUF = 100;

private:
	int m_ID;		// SOCKET ID��
	int m_ServerID; // ������ ID��

public:
	void  SetSocketID( int ID );			// ����SOCKET ID
	int	  GetSocketID();					// �õ�SOCKET ID
	void  SetServerID( int ID );			// ���÷����� ID
	int	  GetServerID();					// �õ������� ID

public:
	//void fileSend( TCHAR* fpath );			// �ļ�����
	//void fileReceive( TCHAR* filename );	// �ļ�����
	DWORD WriteComm(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout, bool cover = true );	// ���������ڷ���Ϣ�ĺ���
	//void SaveWave( const TCHAR* ptcFileDir, const TCHAR* ptcCmd = _T("trac? TRACE1"), DWORD dwWait = 200 );			// ���沨��
};
