// DemoSACtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDemoSACtrlApp:
// �йش����ʵ�֣������ DemoSACtrl.cpp
//

class CDemoSACtrlApp : public CWinApp
{
public:
	CDemoSACtrlApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDemoSACtrlApp theApp;