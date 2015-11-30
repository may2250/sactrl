// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SocketComm.h"
#include "qevent.h"

const int MODE_EDT = 0;		// 用Edit来显示
const int MODE_MSG = 1;		// 用消息来通知
const int MODE_OBS = 2;		// 托管模式

#define WM_UPDATE_CONNECTION	WM_APP+0x1234

struct stMessageProxy1
{
  SockAddrIn address;
  BYTE byData[BUFFER_SIZE];
};

class CSocketManager : public CSocketComm  
{
public:
	CSocketManager();
	virtual ~CSocketManager();

	void SetMessageWindow(CEdit* pMsgCtrl);
	void AppendMessage(LPCTSTR strText );
	
	void SetParentHwnd(HWND hWnd);
	void SetDisplayMode( int nMode );
	void ResetDataArrived();				// 将接收标志置位
	CString GetMsgData();					// 得到接收到的数据
	BOOL IsDataArrived();					// 数据是否到达

	void SetObjectPoint(void* pObj);
	void* GetObjectPoint();
	//void BindObs(void* pFunc);

	//QLib::Event<void, UINT, CSocketManager*>* GetObsEvent();
	//QLib::Event<void, LPBYTE, DWORD, CSocketManager*>* GetObsData();

public:
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent);


protected:
	void DisplayData(const LPBYTE lpData, DWORD dwCount, const SockAddrIn& sfrom);
	CEdit* m_pMsgCtrl;

private:
	HWND   m_hParentWnd;		// 父窗体句柄
	int    m_nMode;			// 显示方式
	//TCHAR  m_szData[5000];
	CString m_szData;
	BOOL   m_DataArrived;		// 数据到达

	void*  m_pObject;			

	//QLib::Event<void, UINT,CSocketManager*> m_ObsEvent;
	//QLib::Event<void, LPBYTE, DWORD, CSocketManager*> m_ObsData;

public:
	SockAddrIn m_SockAddr;
};

#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
