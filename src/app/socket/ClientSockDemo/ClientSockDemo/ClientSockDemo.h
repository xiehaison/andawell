
// ClientSockDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClientSockDemoApp: 
// �йش����ʵ�֣������ ClientSockDemo.cpp
//

class CClientSockDemoApp : public CWinApp
{
public:
	CClientSockDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClientSockDemoApp theApp;