// CommSocket.cpp : implementation file
//

#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>

#include "resource.h"
#include "CommSocket.h"
#include "../include/packet.h"

#include "Srvcomm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MSG_RECV_TIMER_HANDLE 43211
#define ON_RECV_TIMEOUT 5
/////////////////////////////////////////////////////////////////////////////
// CCommSocket


OnMsg gpCallBackMsg = NULL; 
OnNotify gpCallBackNotify = NULL; 

void OutputLog(LPCTSTR DbgMessage,...)
{
	char buf[1024];
	memset(buf,0,1024);
	
	va_list args;
	va_start(args, DbgMessage);
	_vsnprintf (buf, sizeof(buf), DbgMessage, args);
	va_end(args);
	
	strcat(buf, "\n");
	char str[512];
	memset(str, 0, sizeof(str));
	strcat(str, buf);
	
	struct timeb tstruct;
	ftime( &tstruct );
	
	char abuf[1024];
	memset(abuf,0,1024);
	sprintf(abuf,"%s(%3u)=>%s",ctime(&tstruct.time),tstruct.millitm,buf);

	ofstream out("SrvSocket.Tmp");
	out << abuf << endl;
	out.flush();
	out.close();
	OutputDebugString(abuf);
}


CCommSocket::CCommSocket()
{
	m_node = -1;
    m_dir = -1;
	m_name = "";
}


CCommSocket::~CCommSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCommSocket, CSocket)
	//{{AFX_MSG_MAP(CCommSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCommSocket member functions

#include "LsnSocket.h"

extern CLsnSocket gLsnSocket;

void CCommSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    CSocket::OnClose(nErrorCode);
    OutputLog("node %d, socket %04X closed", m_node, m_dir);
    if (gpCallBackNotify)
    {
        char s[256];
        sprintf(s,"%s socket closed!",m_name);
        gpCallBackNotify(m_node,m_dir);
    }  
    Close();
    if (gLsnSocket.m_pSockRecv[m_node] == this)
    {
        gLsnSocket.m_pSockRecv[m_node] = NULL;
    }
    if (gLsnSocket.m_pSockSend[m_node] == this)
    {
        gLsnSocket.m_pSockSend[m_node] = NULL;
    }
    delete this;

}


void CCommSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (m_dir == RECV)
    {
        unsigned short int head;
        unsigned short int msulen;
        char msu[1500];
        memset(msu,0,1500);
        
        if (!SetTimeOut()){
            CloseAll();
            return;
        };
        
        Receive(&head,2);
        if(head!= PACKET_HEAD)
            Close();
        Receive(&msulen,2);
        if( msulen > 1500 )
            Close();
        Receive(msu,msulen);
        if(gpCallBackMsg) 
        {
            gpCallBackMsg(m_node,msu,msulen);
        }
        OutputLog("recv msg:%s,handle:%d",((S_MessagePacket*)msu)->OutputTypeString(),m_hSocket);
        KillTimeOut();
    }
	
	CSocket::OnReceive(nErrorCode);
}


BOOL CCommSocket::OnMessagePending() 
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
			return FALSE;  
			// No need for idle time processing.
		}
	}	
	return CSocket::OnMessagePending();
}


void CCommSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	OutputLog("OnMessagePending");
	CancelBlockingCall();
	ShutDown(0);
	Close();
	CSocket::OnOutOfBandData(nErrorCode);
}


BOOL CCommSocket::SetTimeOut(UINT uTimeOut)
{
	m_nTimerID = SetTimer(NULL,0,uTimeOut,NULL);
	return m_nTimerID;
}


BOOL CCommSocket::KillTimeOut()
{
	return KillTimer(NULL,m_nTimerID);
}


int SetHook(OnMsg msg,OnNotify notify)
{
	gpCallBackMsg = msg;
	gpCallBackNotify = notify;
	return 0;
}


void CCommSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (gpCallBackNotify)
    {
        gpCallBackNotify(m_node, m_dir | COMM_CONNECTED);
    }
	CSocket::OnConnect(nErrorCode);
}
