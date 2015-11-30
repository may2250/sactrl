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

const int MODE_EDT = 0;		// ��Edit����ʾ
const int MODE_MSG = 1;		// ����Ϣ��֪ͨ
const int MODE_OBS = 2;		// �й�ģʽ

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
	void ResetDataArrived();				// �����ձ�־��λ
	CString GetMsgData();					// �õ����յ�������
	BOOL IsDataArrived();					// �����Ƿ񵽴�

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
	HWND   m_hParentWnd;		// ��������
	int    m_nMode;			// ��ʾ��ʽ
	//TCHAR  m_szData[5000];
	CString m_szData;
	BOOL   m_DataArrived;		// ���ݵ���

	void*  m_pObject;			

	//QLib::Event<void, UINT,CSocketManager*> m_ObsEvent;
	//QLib::Event<void, LPBYTE, DWORD, CSocketManager*> m_ObsData;

public:
	SockAddrIn m_SockAddr;
};

#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
