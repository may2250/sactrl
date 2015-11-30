#include "StdAfx.h"
#include "SocketSA.h"

CSocketSA::CSocketSA(void)
{
}

CSocketSA::~CSocketSA(void)
{
}

BOOL CSocketSA::ReceiveBinary( const char* strCmd, BYTE* pBuffer, UINT& nRecv, DWORD dwTimeout, UINT RecvSize )
{
	const UINT RECV_BUF = RecvSize;
	DWORD dwRecv = 0;
	BYTE* bySend = (BYTE*)strCmd;
	BYTE* byRecv = new BYTE[RECV_BUF];
	ZeroMemory(byRecv, RECV_BUF);
	BYTE byPackage[10] = {0};
	UINT nBit = 0, nPackage = 0, nCount = 0;

	if (pBuffer == NULL) {
		goto exception;
		//return FALSE;
	}

	// 先收走不需要的数据
	/*this->ReadComm( byRecv, RECV_BUF, 1 );
	ZeroMemory(byRecv, RECV_BUF);*/

	DWORD dwWrite = this->WriteComm( bySend,  strlen(strCmd), dwTimeout );		// 开始传输
	if (dwWrite == (DWORD)(-1)) {
		goto exception;
	}

	dwRecv = this->ReadComm( byRecv, RECV_BUF, dwTimeout );
	if (dwRecv == (DWORD)(-1)) {
		goto exception;
	}
	nCount = dwRecv;

	// 对于开回传的处理
	char* pdest = strstr( (char*)byRecv, strCmd );
	// 有回传数据
	if (pdest != NULL)
	{
		nCount = nCount - strlen(strCmd) - 2;	// 重新计算数据区长度
		memmove(byRecv, byRecv+strlen(strCmd)+2, nCount);
		ZeroMemory(byRecv + nCount, RECV_BUF-nCount);
	}

	if (byRecv[0] == '#') {
		nBit = byRecv[1] - '0';
		memcpy(byPackage, byRecv+2, nBit);
		nPackage = atoi((char*)byPackage);

		while(nCount < nPackage) {
			dwRecv = this->ReadComm( byRecv+nCount, RECV_BUF, dwTimeout );
			if (dwRecv == (DWORD)(-1)) {
				goto exception;
			}
			nCount += dwRecv;
		}

		memcpy(pBuffer,byRecv+2+nBit, nPackage);
		nRecv = nPackage;
	}
	else{
		//return FALSE;
		goto exception;
	}

	delete [] byRecv;
	return TRUE;

exception:
	delete [] byRecv;
	return FALSE;
}

/* 
注意： 函数声明的地方还挖了一个坑，const char* src说明这个src指向一个常量字符串，居然要求对常量
       字符串进行子串替换！这个坑挖的不小，所以一进入函数，就要在堆上new一块和src串内容相同的串。  
*/       
char* CSocketSA::strrep(const char* src, const char* from, const char* to)
{
  // 前面注释已经说明了，因为挖了个坑，所以这里要在堆上重建src指向的字符串
  char *pSrc;
  if (src != NULL)
  {
      pSrc = new char[strlen(src)+1];
      pSrc[strlen(src)] = '\0';
      strcpy(pSrc, src);
  }

  // 如果src，或from, 或to为空指针，或者src的内容为空('\0'),或者from的内容为空('\0')，直接返回src
  if ((src == NULL) || (from == NULL) || (to == NULL) || (*src == '\0') || (*from == '\0'))
  {
	return pSrc;
  }

  /* 
  下面所有代码的逻辑功能注释：

  WHILE pSrc指向的串包含from指向的串   
      在堆上新生成一个串，
	  赋值这个新串的内容为pSrc替换掉from为to的串:
	     拷贝from左边内容到新串
		 拷贝to的内容到新串
		 拷贝from右边内容到新串
	  删除替换前老的pSrc串
	  令pSrc指向替换后新生成的串
  ENDWHIEL
  */

  char* pPos;
  // 在pSrc串中查找from串的位置，返回结果为from串第一次出现位置的指针
  pPos = strstr(pSrc, from);
  while (pPos != NULL) // 找到了一个from串
  {
      // 将这个from串替换掉
	  // 替换后的串长度为：strlen(pSrc) - strlen(from) + strlen(to)
	  int iAfterReplace = strlen(pSrc) - strlen(from) + strlen(to);

	  // 在堆上new出一块空间，用来存放替换后的内容
	  char* pSrcNew = new char[iAfterReplace + 1];
	  pSrcNew[iAfterReplace] = '\0';

	  if (pSrc < pPos)  
	  {
	      memcpy(pSrcNew, pSrc, pPos-pSrc);    // 拷贝from左边内容到新串
	      int iFront = pPos-pSrc;
	      memcpy(pSrcNew+iFront, to, strlen(to)); // 替换from为to
	  }
	  else
	  {
	      memcpy(pSrcNew, to, strlen(to));	// 替换from为to
	  }
	  if (strlen(pPos) - strlen(from) > 0) // 如果from后面还有内容，要拷贝到新串
	  {
	      strcpy(pSrcNew + (pPos-pSrc) + strlen(to), pPos+strlen(from));
	  }

	  // 上次在堆上临时生成的新串要释放掉
	  delete[] pSrc;	

	  pSrc = pSrcNew; // 令pSrc指向本次在堆上生成的替换掉from为to后的新串
      pPos = strstr(pSrc, from);
  }
  return pSrc;
}

// socket收发数据
BOOL CSocketSA::RSCmd ( LPCTSTR szCmd, DWORD dwTimeout, BYTE send[], BYTE recv[], DWORD& recs )
{
	int nCount = 0; 
	
	if ( !this->IsOpen() )
	{
		return false;
	}

	do 
	{	
		CString sz = szCmd;
		memcpy( send, szCmd, strlen(szCmd) );
		this->WriteComm( send, (DWORD)(sz.GetLength()), dwTimeout );
		recs = this->ReadComm( recv, RECV_BUF, dwTimeout );

		nCount++;
		if ( nCount == 10 )
		{
			return false;
		}

	} while( recs > 500 );		// 接收的数据过大，可能接收成波形了

	char* pdest = strstr( (char*)recv, szCmd );

	if (pdest != NULL)
	{
		int nSend = (strlen(szCmd) + 2);
		int nNeed = recs - nSend;
		if (nNeed <= 0)
		{
			return false;
		}

		memmove(recv, recv + nSend, nNeed);
		memset(recv + nNeed, 0, RECV_BUF-nNeed);
		recs = recs - nSend;
	}

	//Sleep(10);
	return true;
}


// 通过socket读取状态，读取double型数据
BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, double &dVal )
{
	BYTE send[SEND_BUF] = {0};
	BYTE recv[RECV_BUF] = {0};
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;
	try
	{
		if ( !RSCmd (szCmd,  dwTimeout,  send,  recv,  recs ) )
			return false;

		if(recs > RECV_BUF || recs <= 0)
			return false;
		recv[recs]='\0';
		szParam = recv;
		dVal = atof( szParam );
	}
	catch (CException* e)
	{
		TCHAR sz[1024];
		e->GetErrorMessage(sz, 1024);
		e->Delete();
		return FALSE;
	}

	return true;
}

// 通过socket读取数据，读取long类型数据
BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, long &lVal )
{
	BYTE send[SEND_BUF] = {0};
	BYTE recv[RECV_BUF] = {0};
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd (szCmd, dwTimeout, send, recv, recs) )
		return false;

	if(recs >= RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;
	lVal = atol( szParam );
	return true;
}

BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, INT64 &dVal )
{
	BYTE send[SEND_BUF] = {0};
	BYTE recv[RECV_BUF] = {0};
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd(szCmd, dwTimeout, send, recv, recs))
		return false;

	if(recs >= RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;
	dVal = _ttoi64( szParam );
	return true;
}

BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, int &nVal )
{
	BYTE send[SEND_BUF] = {0};
	BYTE recv[RECV_BUF] = {0};
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd (szCmd, dwTimeout, send, recv, recs))
		return false;

	if(recs >= RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;
	nVal = _ttoi( szParam );
	return true;
}

// 通过socket读取数据，读取CString类型的数据
BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, CString &szVal )
{
	BYTE send[SEND_BUF] = {0};
	BYTE recv[RECV_BUF] = {0};
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd(szCmd, dwTimeout, send, recv, recs))
		return false;

	if(recs > RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;
	szVal =  szParam;
	return true;
}

BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, int &iVal, CString szRet[], int iRet  )
{
	BYTE send[SEND_BUF];
	BYTE recv[RECV_BUF];
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd(szCmd,  dwTimeout,  send,  recv,  recs ) )
		return false;

	if(recs >= RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;

	szParam = szParam.TrimRight(_T("\r\n"));
	// 判断是否是在某个数组范围内
	if( iRet != 0 )
	{
		for( int i=0; i<iRet; i++ ) 
		{
			if( strcmp( szParam, szRet[i] ) == 0 ) 
			{
				iVal = i;
				break;
			}
		}
	}
	else {
		iVal = atoi( szParam );
	}
	return true;
}

BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, bool &bVal, CString szRet[], int iRet  )
{
	BYTE send[SEND_BUF];
	BYTE recv[RECV_BUF];
	DWORD recs;
	CString szParam;

	if ( !this->IsOpen() )
		return false;

	if ( !RSCmd(szCmd, dwTimeout, send, recv, recs))
		return false;

	if(recs >= RECV_BUF || recs <= 0)
		return false;
	recv[recs]='\0';
	szParam = recv;

	szParam = szParam.TrimRight(_T("\r\n"));
	// 判断是否是在某个数组范围内
	if( iRet <= 3 )
	{
		for( int i=0; i<iRet; i++ ) 
		{
			if( strcmp( szParam, szRet[i] ) == 0 ) 
			{
				bVal = i;
				break;
			}
		}
	}
	else {
		bVal = atoi( szParam );
	}
	return true;
}

// 通过socket设置，不需要收数的
BOOL CSocketSA::LanSendCmd(LPCTSTR szCmd, DWORD dwTimeout, bool IsEcho )
{
	DWORD dwSend = 0;
	DWORD dwRecv = 0;
	BYTE send[SEND_BUF*100] = {0};
	BYTE recv[RECV_BUF] = {0};

	if ( !this->IsOpen() )
		return false;

	CString sz = szCmd;
	memcpy( send, szCmd, strlen(szCmd) );

	WriteComm( send, (DWORD)(sz.GetLength()), dwTimeout );
	if (IsEcho) {
		//Sleep(30);
		dwRecv = ReadComm(recv, RECV_BUF, dwTimeout);
		if (dwRecv == 0 || dwRecv == (DWORD)-1) 
		{
			return false;
		}
		recv[dwRecv] = 0;
		if (sz.Compare(CString(recv).TrimRight(_T("\r\n"))) == 0) {
			return true;
		}
	}
	return true;
}
