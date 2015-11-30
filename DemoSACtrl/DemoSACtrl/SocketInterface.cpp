#include "StdAfx.h"
#include "SocketInterface.h"

//#define WSA_VERSION  MAKEWORD(2,0)
//#define MAX_HOSTNAME 256
//#define MAX_HOSTADDR 40

CSocketInterface::CSocketInterface(void)
{
	//WSADATA		WSAData = { 0 };
	//if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
	//{
	//	// Tell the user that we could not find a usable
	//	// WinSock DLL.
	//	if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
	//		 HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
	//		 ::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

	//	WSACleanup( );
	//}
	m_nCurrPort = 5025;
}

CSocketInterface::~CSocketInterface(void)
{
}

//void CSocketInterface::fileSend( TCHAR* fpath )
//{
//	BYTE bfilename[50];
//	BYTE bfilelen[10];
//	BYTE rec[32];
//	TCHAR tcfilesize[10];
//
//	long filelen;
//
//	int j = 0;
//	int filename_len = 0;
//
//	int i = static_cast<int>(wcslen( fpath ));
//	for( ;i>0;i-- )
//		if( fpath[i-1] == '\\' )
//			break;
//	for(;i<=(int)wcslen(fpath);i++)
//		bfilename[j++] = static_cast<BYTE>(fpath[i]);
//
//	filename_len = j;
//
//	FILE* fd = _wfopen( fpath, _T("r+b") );
//	// 得到文件大小
//	fseek(fd, 0L, SEEK_END);
//	filelen = ftell(fd);
//
//	long filemove = 0-filelen;
//	fseek(fd, filemove, SEEK_END);
//
//	_itow( filelen, tcfilesize, 10);
//	WideCharToMultiByte(CP_ACP, 0, tcfilesize, -1, (LPSTR)bfilelen, sizeof(bfilelen), NULL, NULL );
//
//	// 数据发送
//
//	// 文件名
//	CSocketManager::WriteComm( bfilename, filename_len, SOCKET_TIME_OUT );
//	CSocketManager::ReadComm( rec, 32, SOCKET_TIME_OUT );
//	// 文件长度
//	CSocketManager::WriteComm( bfilelen, static_cast<DWORD>(wcslen( tcfilesize )), SOCKET_TIME_OUT );
//	CSocketManager::ReadComm( rec, 32, SOCKET_TIME_OUT );
//
//	while(filelen > 0)
//	{
//		BYTE buffer[PACKAGE_BUF_SIZE];
//
//		if(filelen >= PACKAGE_SIZE)
//		{
//			fread(buffer, PACKAGE_SIZE, 1, fd);
//
//			CSocketManager::WriteComm( buffer, PACKAGE_SIZE, SOCKET_TIME_OUT );
//			CSocketManager::ReadComm( rec, 32, SOCKET_TIME_OUT );
//		}
//		else
//		{
//			fread(buffer, filelen, 1, fd);
//			buffer[filelen]='\0';
//
//			CSocketManager::WriteComm( buffer, filelen, SOCKET_TIME_OUT );
//			CSocketManager::ReadComm( rec, 32, SOCKET_TIME_OUT );
//		}
//		filelen -= PACKAGE_SIZE;
//
//	}
//
//	fclose(fd);
//}
//
//void CSocketInterface::fileReceive( TCHAR* filename )
//{
//	BYTE rec[32] ;
//	BYTE send[32];
//	TCHAR filelen[32];
//
//	CSocketManager::WriteComm( send,  static_cast<DWORD>(wcslen(_T("OK"))), SOCKET_TIME_OUT );
//
//	FILE *fd = _wfopen(filename, _T("wb"));
//
//	DWORD recs = CSocketManager::ReadComm( rec, 32, SOCKET_TIME_OUT );
//	CSocketManager::WriteComm( send,  static_cast<DWORD>(wcslen(_T("OK"))), SOCKET_TIME_OUT );
//	rec[recs]='\0';
//
//	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)rec, -1, filelen, 32);
//	long size = _wtol(filelen);
//	
//	while(size > 0)
//	{
//		BYTE buffer[PACKAGE_BUF_SIZE];
//
//		if(size >= PACKAGE_SIZE)
//		{
//			CSocketManager::ReadComm( buffer, PACKAGE_SIZE, SOCKET_TIME_OUT );
//			CSocketManager::WriteComm( send,  static_cast<DWORD>(wcslen(_T("OK"))), SOCKET_TIME_OUT );
//
//			fwrite(buffer, PACKAGE_SIZE, 1, fd);
//		}
//		else
//		{
//			CSocketManager::ReadComm( buffer, size, SOCKET_TIME_OUT );
//			CSocketManager::WriteComm( send,  static_cast<DWORD>(wcslen(_T("OK"))), SOCKET_TIME_OUT );
//
//			buffer[size]='\0';
//			fwrite( buffer, size, 1, fd );
//		}
//		size -= PACKAGE_SIZE;
//	}
//	fclose(fd);
//}

DWORD CSocketInterface::WriteComm( const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout, bool cover )
{
	BYTE *pBuffer = NULL;

	if( cover )
	{
		BYTE pBuffer[150];
		memcpy( pBuffer, lpBuffer, dwCount);
		pBuffer[dwCount] = 0x0d;
		pBuffer[dwCount+1] = 0x0a;
		pBuffer[dwCount+2] = 0;

		return CSocketManager::WriteComm( pBuffer, dwCount+2, dwTimeout );
	}
	else
	{
		return CSocketManager::WriteComm( lpBuffer, dwCount, dwTimeout );
	}
}

//void CSocketInterface::SaveWave( const TCHAR* ptcFileDir, const TCHAR* ptcCmd /*= _T("trac? TRACE1")*/ ,
//									DWORD dwWait/* = 200 */)
//{
//	SYSTEMTIME systime;
//	GetSystemTime(&systime);
//
//	DWORD recs;
//	TCHAR tcFileName[50];
//	TCHAR tcFilePath[255];
//	BYTE send[SEND_BUF];
//	BYTE recv[RECV_BUF];
//	TCHAR tcWave[10000];
//
//	// 得到文件名
//	wsprintf(tcFileName, _T("%u_%u_%u_%u_%u_%u_%u.txt"), 
//		systime.wYear, systime.wMonth, systime.wDay,
//		systime.wHour+8, systime.wMinute, systime.wSecond, systime.wMilliseconds);
//
//	WideCharToMultiByte(CP_ACP, 0, ptcCmd, -1, (LPSTR)send, SEND_BUF, NULL, NULL );
//
//	this->WriteComm( send,  static_cast<DWORD>(wcslen(ptcCmd)), SOCKET_TIME_OUT/*, falsetrue*/ );		// 开始传输
//	Sleep(dwWait);
//	recs = this->ReadComm( recv, RECV_BUF, SOCKET_TIME_OUT );
//	Sleep(20);
//	recv[recs]='\0';
//
//	MultiByteToWideChar( CP_ACP, 0, (LPCSTR)recv, -1, tcWave, RECV_BUF );
//	tcWave[recs] = _T('\0');
//
//	CString strWave = tcWave;
//	strWave.Replace( _T(","), _T("\r\n") );
//	
//	// 写入波形文件
//	wsprintf(tcFilePath, _T("%s%s"), ptcFileDir,tcFileName);
//
//	FILE* fp = _wfopen( tcFilePath, _T("w+"));
//	fwprintf( fp, _T("%s"), strWave );
//	Sleep(10);
//	fclose(fp);
//}

void  CSocketInterface::SetSocketID( int ID )
{
	m_ID = ID;
}

int	  CSocketInterface::GetSocketID()
{
	return m_ID;
}

void  CSocketInterface::SetServerID( int ID )
{
	m_ServerID = ID;
}

int	  CSocketInterface::GetServerID()
{
	return m_ServerID;
}