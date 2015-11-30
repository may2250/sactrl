// SocketManager.cpp: implementation of the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlconv.h>
//#include "WBCaptuer.h"
#include "SocketManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
const UINT EVT_CONSUCCESS = 0x0000;	// Connection established
const UINT EVT_CONFAILURE = 0x0001;	// General failure - Wait Connection failed
const UINT EVT_CONDROP	  = 0x0002;	// Connection dropped
const UINT EVT_ZEROLENGTH = 0x0003;	// Zero length message
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketManager::CSocketManager()
: m_pMsgCtrl(NULL)
{
	m_nMode = MODE_EDT;
	//m_szData[0] = '\0';
	m_szData = _T("");
	m_DataArrived = FALSE;
	m_pObject = NULL;
}

CSocketManager::~CSocketManager()
{

}


void CSocketManager::DisplayData(const LPBYTE lpData, DWORD dwCount, const SockAddrIn& sfrom)
{
	CString strData;
	//memcpy(strData.GetBuffer(dwCount), A2CT((LPSTR)lpData), dwCount);
	memcpy(strData.GetBuffer(dwCount), (LPCTSTR)lpData, dwCount);

//#ifndef _UNICODE
//	char cData[5000];
//	memcpy(cData, (LPSTR)lpData, dwCount );
//	cData[dwCount] = '\0';
//	strData.Format(_T("%s"), cData);
//#else
//	lpData[dwCount] = '\0';
//	strData = lpData;
//#endif

	strData.ReleaseBuffer();
	if (!sfrom.IsNull())
	{
		LONG  uAddr = sfrom.GetIPAddr();
		BYTE* sAddr = (BYTE*) &uAddr;
		short nPort = ntohs( sfrom.GetPort() );	// show port in host format...
		CString strAddr;
		// Address is stored in network format...
		strAddr.Format(_T("%u.%u.%u.%u (%d)>"),
					(UINT)(sAddr[0]), (UINT)(sAddr[1]),
					(UINT)(sAddr[2]), (UINT)(sAddr[3]), nPort);

		strData = strAddr + strData;
	}

	AppendMessage( strData );
}


void CSocketManager::AppendMessage(LPCTSTR strText )
{
	if (NULL == m_pMsgCtrl)
		return;
/*
	if (::IsWindow( m_pMsgCtrl->GetSafeHwnd() ))
	{
		int nLen = m_pMsgCtrl->GetWindowTextLength();
		m_pMsgCtrl->SetSel(nLen, nLen);
		m_pMsgCtrl->ReplaceSel( strText );
	}
*/
	HWND hWnd = m_pMsgCtrl->GetSafeHwnd();
	DWORD dwResult = 0;
	if (SendMessageTimeout(hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_NORMAL, 1000L, &dwResult) != 0)
	{
		int nLen = (int) dwResult;
		if (SendMessageTimeout(hWnd, EM_SETSEL, nLen, nLen, SMTO_NORMAL, 1000L, &dwResult) != 0)
		{
			if (SendMessageTimeout(hWnd, EM_REPLACESEL, FALSE, (LPARAM)strText, SMTO_NORMAL, 1000L, &dwResult) != 0)
			{
			}
		}
	}
}


void CSocketManager::SetMessageWindow(CEdit* pMsgCtrl)
{
	m_pMsgCtrl = pMsgCtrl;
}


void CSocketManager::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	LPBYTE lpData = lpBuffer;
	SockAddrIn origAddr;
	stMessageProxy1 msgProxy;

	if (IsSmartAddressing())
	{
		dwCount = __min(sizeof(msgProxy), dwCount);
		memcpy(&msgProxy, lpBuffer, dwCount);
		origAddr = msgProxy.address;
		if (IsServer())
		{
			// broadcast message to all
			msgProxy.address.sin_addr.s_addr = htonl(INADDR_BROADCAST);
			WriteComm((const LPBYTE)&msgProxy, dwCount, 0L);
		}
	//	m_SockAddr = msgProxy.address;
		dwCount -= sizeof(msgProxy.address);
		lpData = msgProxy.byData;
	}

	if ( m_nMode == MODE_EDT )
	{
		// Display data to message list
		DisplayData( lpData, dwCount, origAddr );
	}
	else if ( m_nMode == MODE_MSG)
	{
#ifndef _UNICODE
		char cData[5000];
		memcpy(cData, (LPSTR)lpData, dwCount );
		cData[dwCount] = '\0';
		m_szData = cData;
		//MultiByteToWideChar(CP_ACP, 0, (LPCSTR)cData, -1, m_szData, strlen(cData));
#else
		
		lpData[dwCount] = '\0';
		//memcpy( m_szData, lpData, dwCount );
		m_szData = lpData;
		//strcpy( m_szData, (LPCSTR)lpData );
#endif
		m_DataArrived = TRUE;
		//::PostThreadMessage( m_hParentWnd, WM_DATA_ARRIVED, NULL, NULL );
	}
	else if (m_nMode == MODE_OBS) {
		//m_ObsData(lpBuffer, dwCount, this);
	}

	// Display data to message list
	//DisplayData( lpData, dwCount, origAddr );
}

///////////////////////////////////////////////////////////////////////////////
// OnEvent
// Send message to parent window to indicate connection status
void CSocketManager::OnEvent(UINT uEvent)
{
	CWnd* pParent = NULL;
	if ( m_nMode == MODE_EDT )
	{
		if (NULL == m_pMsgCtrl)
			return;

		pParent = m_pMsgCtrl->GetParent();
		if (!::IsWindow( pParent->GetSafeHwnd()))
			return;
	}

	switch( uEvent )
	{
		case EVT_CONSUCCESS:
			AppendMessage( _T("Connection Established\r\n") );
			break;
		case EVT_CONFAILURE:
			AppendMessage( _T("Connection Failed\r\n") );
			break;
		case EVT_CONDROP:
			AppendMessage( _T("Connection Abandonned\r\n") );
			break;
		case EVT_ZEROLENGTH:
			AppendMessage( _T("Zero Length Message\r\n") );
			break;
		default:
			TRACE("Unknown Socket event\n");
			break;
	}

	//pParent->PostMessage( WM_UPDATE_CONNECTION, uEvent, (LPARAM) this);
	if ( m_nMode == MODE_EDT )
	{
		pParent->PostMessage( WM_UPDATE_CONNECTION, uEvent, (LPARAM) this);
	}
	else if ( m_nMode == MODE_MSG )
	{
		::PostMessage(m_hParentWnd, WM_UPDATE_CONNECTION, uEvent, (LPARAM) this );
	}
	else if (m_nMode == MODE_OBS)
	{
		//m_ObsEvent(uEvent, this);
	}

}

void CSocketManager::SetParentHwnd(HWND hWnd)
{
	m_hParentWnd = hWnd;
}

void CSocketManager::SetDisplayMode( int nMode )
{
	m_nMode = nMode;
}

// 
void CSocketManager::ResetDataArrived()
{
	m_DataArrived = FALSE;
	//m_szData[0] = '\0';
	m_szData = _T("");
}

// 返回消息数据
CString CSocketManager::GetMsgData()
{
	/*if ( IsBadStringPtr( m_szData, 100 ) )
	{
		m_szData = _T("");
	}*/
	return m_szData;
}

BOOL CSocketManager::IsDataArrived()
{
	return m_DataArrived;
}

/*QLib::Event<void, UINT, CSocketManager*>* CSocketManager::GetObsEvent()
{
	return &m_ObsEvent;
}

QLib::Event<void, LPBYTE, DWORD, CSocketManager*>* CSocketManager::GetObsData()
{
	return &m_ObsData;
}
*/
void* CSocketManager::GetObjectPoint()
{
	return m_pObject;
}

void CSocketManager::SetObjectPoint( void* pObj )
{
	m_pObject = pObj;
}


