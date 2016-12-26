// CltSock.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CltSock.h"
#include "clientsock_asyn.h"
#include "../include/packet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCltSock

//extern OnMsg gMsg ;
//extern OnNotify gNotify ;
extern  CClientComm gComm;
extern  CRITICAL_SECTION gCS;
extern  CRITICAL_SECTION gCSRecv;

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
    sprintf(s,"[node=%d,Á¬½Ó¹Ø±Õ!]", gComm.m_Node);
    F_Notify(s, gComm.m_Node, m_dir,E_ERROR_CLOSE);
	Close();
    CSocket::OnClose(nErrorCode);
}


void CCltSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    CSocket::OnConnect(nErrorCode);
}


void CCltSock::OnOutOfBandData(int nErrorCode) 
{
	CancelBlockingCall();
    OutputLog("Client--OnOutOfBandData--CancelBlockingCall");
    CSocket::OnOutOfBandData(nErrorCode);
}


void CCltSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

    static unsigned count;

    static char msu[MAX_MSG_LEN];
    static char msubuf[MAX_MSG_LEN * 1000];
    static int tail = 0, head = 0;
    WORD packhead, packlen;
    int len;
    len = Recv((char*)&msubuf[tail], MAX_MSG_LEN * 1000);
    if (len < 0)
        return;
    tail += len;
    while (tail>4)
    {
        packhead = *(WORD*)&msubuf[0];
        if (packhead != PACKET_HEAD){
            ShutDown(2);
            return;
        }
        packlen = *(WORD*)&msubuf[2];
        if (packlen >(tail - 4)){
            break;
        }
        static T_Msg msg;
        msg.len = packlen;
        memcpy(msg.msg, &msubuf[4], packlen);
        EnterCriticalSection(&gCSRecv);
        gComm.m_RecvQueue.push_back(msg);
        LeaveCriticalSection(&gCSRecv);

        tail -= (packlen + 4);
        memmove(msubuf, &msubuf[packlen + 4], tail);
    }
    CSocket::OnReceive(nErrorCode);

}
