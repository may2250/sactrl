#pragma once
#include "socketinterface.h"

class CSocketSA :
	public CSocketInterface
{
public:
	CSocketSA(void);
	virtual ~CSocketSA(void);

public:
	// 封装的网络活动 用来读取某一项数据
	BOOL RSCmd ( LPCTSTR szCmd, DWORD dwTimeout, BYTE send[], BYTE recv[], DWORD& recs );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, double &dVal );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, long &lVal );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, CString &szVal );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, INT64 &dVal );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, bool IsEcho );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, int &iVal, CString szRet[], int iRet );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, bool &bVal, CString szRet[], int iRet );
	BOOL LanSendCmd( LPCTSTR szCmd, DWORD dwTimeout, int &nVal );
	char* strrep(const char* src, const char* from, const char* to);
	BOOL ReceiveBinary( const char* strCmd, BYTE* pBuffer, UINT& nRecv, DWORD dwTimeout = 10000, UINT RecvSize = 10000 );
};
