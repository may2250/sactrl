#pragma once
#include "socketmanager.h"

const int PACKAGE_SIZE = 1024;
const int PACKAGE_BUF_SIZE = 1030;
const DWORD SOCKET_TIME_OUT = 20000;/*60000*//*5000*/
const DWORD SOCKET_TIME_OUT_DTV = 60000;		// 2s
const DWORD SOCKET_TIME_OUT_CHSCAN = 20000;	// 超时时间

class CSocketInterface :
	public CSocketManager
{
public:
	CSocketInterface(void);
public:
	~CSocketInterface(void);

public:
	int m_nCurrPort;	// 当前连接的端口
	CString m_nCurrServer; // 当前服务器
	const static int RECV_BUF = 10000;
	const static int SEND_BUF = 100;

private:
	int m_ID;		// SOCKET ID号
	int m_ServerID; // 服务器 ID号

public:
	void  SetSocketID( int ID );			// 设置SOCKET ID
	int	  GetSocketID();					// 得到SOCKET ID
	void  SetServerID( int ID );			// 设置服务器 ID
	int	  GetServerID();					// 得到服务器 ID

public:
	//void fileSend( TCHAR* fpath );			// 文件发送
	//void fileReceive( TCHAR* filename );	// 文件接收
	DWORD WriteComm(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout, bool cover = true );	// 覆盖向网口发消息的函数
	//void SaveWave( const TCHAR* ptcFileDir, const TCHAR* ptcCmd = _T("trac? TRACE1"), DWORD dwWait = 200 );			// 保存波形
};
