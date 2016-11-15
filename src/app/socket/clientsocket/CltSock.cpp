// CltSock.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CltSock.h"
#include "clientsock.h"
#include "../include/packet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCltSock

extern OnMsg gMsg ;
extern OnNotify gNotify ;
extern CClientComm gComm;

CCltSock::CCltSock()
{
    m_dir = -1;
}

CCltSock::~CCltSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCltSock, CSocket)
	//{{AFX_MSG_MAP(CCltSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCltSock member functions


void CCltSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    char s[256];
    sprintf(s,"node: %d,dir:%d,Á¬½Ó¹Ø±Õ",gComm.m_Node,m_dir);
    F_Notify(s, gComm.m_Node, m_dir,E_ERROR_CLOSE);
    Close();
    delete this;
	CSocket::OnClose(nErrorCode);
}

void CCltSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSocket::OnConnect(nErrorCode);
}

BOOL CCltSock::OnMessagePending() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	MSG msg;
	if(::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
	{
		if (msg.wParam == (UINT) m_nTimerID)
		{
			// Remove the message and call CancelBlockingCall.
            ::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
            CancelBlockingCall();
            ShutDown();
            return FALSE;
			// No need for idle time processing.
		}
	}
	return CSocket::OnMessagePending();
}

void CCltSock::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnOutOfBandData(nErrorCode);
}

void CCltSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (m_dir == RECV)
    {
        unsigned short int head;
        unsigned short int msulen;
        char msu[1500];
        memset(msu,0,1500);
        
        SetTimeOut();
        Receive(&head,2);
        if(head!= 0x7ffe)
            Close();
        Receive(&msulen,2);
        if(msulen > 1500)
            Close();
        Receive(msu,msulen);
        if(gMsg)
        {
            gMsg(msu,msulen);
        }
        Output("recv msg:%s",msu);
        KillTimeOut();
    }
	
	CSocket::OnReceive(nErrorCode);
}
