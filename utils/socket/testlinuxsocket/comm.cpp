// comm.cpp : implementation file
//

#include "stdafx.h"
#include "testlinuxsocket.h"
#include "comm.h"
#include "testlinuxsocketDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// comm

extern CTestlinuxsocketDlg *g_Dlg ;

comm::comm()
{
}

comm::~comm()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(comm, CSocket)
	//{{AFX_MSG_MAP(comm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// comm member functions
#define ON_RECV_TIMEOUT 1
#define MSG_RECV_TIMEOUT 999

void comm::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	unsigned short int head;
	unsigned short int msulen;
	int msu[1500];
	memset(msu,0,1500);

	g_Dlg->SetTimer(MSG_RECV_TIMEOUT,ON_RECV_TIMEOUT,NULL);
	
	Receive(&head,2);
	if(head!= 0x7ffe)
		Close();
	Receive(&msulen,2);
	if(msulen > 1500)
		Close();
	Receive(msu,msulen);
    g_Dlg->Output("recv msg:%s",msu);
	g_Dlg->KillTimer(MSG_RECV_TIMEOUT);
	CSocket::OnReceive(nErrorCode);
}


void comm::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    g_Dlg->Output("socket %s closed",m_name);
        
	CSocket::OnClose(nErrorCode);
}


void comm::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	g_Dlg->KillTimer(ON_RECV_TIMEOUT);
	g_Dlg->Output("OnMessagePending");
	CancelBlockingCall();
	ShutDown(0);
	Close();

	CSocket::OnOutOfBandData(nErrorCode);
}


BOOL comm::OnMessagePending() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	g_Dlg->KillTimer(ON_RECV_TIMEOUT);
	g_Dlg->Output("OnMessagePending");
	CancelBlockingCall();
	ShutDown(0);
	Close();
	return CSocket::OnMessagePending();
}


