// CommSend.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CommSend.h"

#include "CommSocket.h"
#include "../include/packet.h"
#include "LsnSocket.h"

#include "Srvcomm.h"

extern CLsnSocket gLsnSocket;
extern OnNotify gpCallBackNotify ; 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommSend

CCommSend::CCommSend()
{
}

CCommSend::~CCommSend()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCommSend, CSocket)
	//{{AFX_MSG_MAP(CCommSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0


/////////////////////////////////////////////////////////////////////////////
// CCommSend member functions

void CCommSend::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

    OutputLog("node %d, socket %04X closed",m_node,m_dir);
    if (gpCallBackNotify)
    {
        char s[256];
        sprintf(s,"%s socket closed!",m_name);
        gpCallBackNotify(m_node,m_dir);
    }  
    Close();
	CSocket::OnClose(nErrorCode);
}

void CCommSend::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnConnect(nErrorCode);
}
