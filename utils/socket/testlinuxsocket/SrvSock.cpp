// SrvSock.cpp : implementation file
//

#include "stdafx.h"
#include "mycomm.h"
#include "testlinuxsocket.h"
#include "SrvSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SrvSock

SrvSock::SrvSock()
{
    m_pSockRecv = NULL;
    m_pSockSend = NULL;
}

SrvSock::~SrvSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(SrvSock, CSocket)
	//{{AFX_MSG_MAP(SrvSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

#include "testlinuxsocketDlg.h"

/////////////////////////////////////////////////////////////////////////////
// SrvSock member functions
extern CTestlinuxsocketDlg *g_Dlg ;

void SrvSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (m_pSockSend == NULL )
    {
        m_pSockSend = new comm;
        Accept(*m_pSockSend);
        m_pSockSend->m_name = "m_pSockSend";
        g_Dlg->Output("Accept m_pSockSend ok");
    }
	else if (m_pSockRecv == NULL)
	{
        m_pSockRecv = new comm;
        Accept(*m_pSockRecv);
        m_pSockRecv->m_name = "m_pSockRecv";
        g_Dlg->Output("Accept m_pSockRecv ok");
	}
	CSocket::OnAccept(nErrorCode);
}


void SrvSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    delete m_pSockRecv;
    delete m_pSockSend;
    m_pSockRecv = NULL;
    m_pSockSend= NULL;
	CSocket::OnClose(nErrorCode);
}

