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

	// �����߲���Ҫ������
	/*this->ReadComm( byRecv, RECV_BUF, 1 );
	ZeroMemory(byRecv, RECV_BUF);*/

	DWORD dwWrite = this->WriteComm( bySend,  strlen(strCmd), dwTimeout );		// ��ʼ����
	if (dwWrite == (DWORD)(-1)) {
		goto exception;
	}

	dwRecv = this->ReadComm( byRecv, RECV_BUF, dwTimeout );
	if (dwRecv == (DWORD)(-1)) {
		goto exception;
	}
	nCount = dwRecv;

	// ���ڿ��ش��Ĵ���
	char* pdest = strstr( (char*)byRecv, strCmd );
	// �лش�����
	if (pdest != NULL)
	{
		nCount = nCount - strlen(strCmd) - 2;	// ���¼�������������
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
ע�⣺ ���������ĵط�������һ���ӣ�const char* src˵�����srcָ��һ�������ַ�������ȻҪ��Գ���
       �ַ��������Ӵ��滻��������ڵĲ�С������һ���뺯������Ҫ�ڶ���newһ���src��������ͬ�Ĵ���  
*/       
char* CSocketSA::strrep(const char* src, const char* from, const char* to)
{
  // ǰ��ע���Ѿ�˵���ˣ���Ϊ���˸��ӣ���������Ҫ�ڶ����ؽ�srcָ����ַ���
  char *pSrc;
  if (src != NULL)
  {
      pSrc = new char[strlen(src)+1];
      pSrc[strlen(src)] = '\0';
      strcpy(pSrc, src);
  }

  // ���src����from, ��toΪ��ָ�룬����src������Ϊ��('\0'),����from������Ϊ��('\0')��ֱ�ӷ���src
  if ((src == NULL) || (from == NULL) || (to == NULL) || (*src == '\0') || (*from == '\0'))
  {
	return pSrc;
  }

  /* 
  �������д�����߼�����ע�ͣ�

  WHILE pSrcָ��Ĵ�����fromָ��Ĵ�   
      �ڶ���������һ������
	  ��ֵ����´�������ΪpSrc�滻��fromΪto�Ĵ�:
	     ����from������ݵ��´�
		 ����to�����ݵ��´�
		 ����from�ұ����ݵ��´�
	  ɾ���滻ǰ�ϵ�pSrc��
	  ��pSrcָ���滻�������ɵĴ�
  ENDWHIEL
  */

  char* pPos;
  // ��pSrc���в���from����λ�ã����ؽ��Ϊfrom����һ�γ���λ�õ�ָ��
  pPos = strstr(pSrc, from);
  while (pPos != NULL) // �ҵ���һ��from��
  {
      // �����from���滻��
	  // �滻��Ĵ�����Ϊ��strlen(pSrc) - strlen(from) + strlen(to)
	  int iAfterReplace = strlen(pSrc) - strlen(from) + strlen(to);

	  // �ڶ���new��һ��ռ䣬��������滻�������
	  char* pSrcNew = new char[iAfterReplace + 1];
	  pSrcNew[iAfterReplace] = '\0';

	  if (pSrc < pPos)  
	  {
	      memcpy(pSrcNew, pSrc, pPos-pSrc);    // ����from������ݵ��´�
	      int iFront = pPos-pSrc;
	      memcpy(pSrcNew+iFront, to, strlen(to)); // �滻fromΪto
	  }
	  else
	  {
	      memcpy(pSrcNew, to, strlen(to));	// �滻fromΪto
	  }
	  if (strlen(pPos) - strlen(from) > 0) // ���from���滹�����ݣ�Ҫ�������´�
	  {
	      strcpy(pSrcNew + (pPos-pSrc) + strlen(to), pPos+strlen(from));
	  }

	  // �ϴ��ڶ�����ʱ���ɵ��´�Ҫ�ͷŵ�
	  delete[] pSrc;	

	  pSrc = pSrcNew; // ��pSrcָ�򱾴��ڶ������ɵ��滻��fromΪto����´�
      pPos = strstr(pSrc, from);
  }
  return pSrc;
}

// socket�շ�����
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

	} while( recs > 500 );		// ���յ����ݹ��󣬿��ܽ��ճɲ�����

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


// ͨ��socket��ȡ״̬����ȡdouble������
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

// ͨ��socket��ȡ���ݣ���ȡlong��������
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

// ͨ��socket��ȡ���ݣ���ȡCString���͵�����
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
	// �ж��Ƿ�����ĳ�����鷶Χ��
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
	// �ж��Ƿ�����ĳ�����鷶Χ��
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

// ͨ��socket���ã�����Ҫ������
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
