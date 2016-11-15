// Socket_Send.cpp : implementation file
//

#include "stdafx.h"
#include "DBAgent.h"
#include "Socket_Send.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocket_Send

CSocket_Send::CSocket_Send()
{
	status = 0;
}

CSocket_Send::~CSocket_Send()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocket_Send, CAsyncSocket)
	//{{AFX_MSG_MAP(CSocket_Send)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocket_Send member functions

void CSocket_Send::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	Close();
	status = 0;
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CSocket_Send::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	status = 2;
	if(nErrorCode)
	{
		status = 0;
		Close();
	}
	else
	{
		DBPacket pak;
		pak.HeadFlag=0xeffffffe;
		pak.PackType=PAK_PROXYINFO;
		pak.proxyinfo.socktype=1;
		pak.proxyinfo.proxyno=0;
		Send((char*)(&pak),sizeof(pak),0);
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CSocket_Send::ConnectServer()
{
	Close();
	Create();
	//与服务器连接
	char szIP[255]="192.168.3.120";
	UINT nPort = GetPrivateProfileInt("tcp","port",0,"./DBAgent.ini");
	GetPrivateProfileString("tcp", "ip","", szIP, sizeof(szIP),"./DBAgent.ini");

	BOOL ok = Connect(szIP,nPort);
	int nError = WSAGetLastError();
	status = 1;
}
