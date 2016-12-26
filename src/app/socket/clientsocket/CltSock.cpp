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
    char s[256]="连接关闭";
    F_Notify(s, gComm.m_Node, E_ERROR_CLOSE);
    Close();
    gComm.m_Node = -1;
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
            OutputLog("Client OnMessagePending--CancelBlockingCall");
            return FALSE;
			// No need for idle time processing.
		}
	}
	return CSocket::OnMessagePending();
}

void CCltSock::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CancelBlockingCall();
    OutputLog("Client OnOutOfBandData--CancelBlockingCall");
	CSocket::OnOutOfBandData(nErrorCode);
}


#define MAX_MSU_LEN  2048
#define MAX_BUFFER_SIZE MAX_MSU_LEN*10

void CCltSock::OnReceive(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    static unsigned count;

    static char msu[MAX_MSU_LEN];
    static char msubuf[MAX_BUFFER_SIZE];
    static int tail = 0;
    bool continue_flag;
    WORD packhead, packlen;
//    do{
        int len = Recv((char*)&msubuf[tail], MAX_BUFFER_SIZE - tail);
        if (len < 0)
            return;
        continue_flag = (len == MAX_BUFFER_SIZE - tail);
        tail += len;
        while (tail >4)
        {
            packhead = *(WORD*)&msubuf[0];
            if (packhead != PACKET_HEAD){
                memset(msubuf, 0, sizeof(msubuf));
                tail = 0;
                ShutDown(2);
                return;
            }
            packlen = *(WORD*)&msubuf[2];
            if (packlen > (tail - 4)){
                break;
            }
            memcpy(msu, &msubuf[4], packlen);
            if (gMsg){
                gMsg((char*)&msu, packlen);
                count++;
                //OutputLog("收到消息!count=%d", count++);
            }
            tail -= (packlen + 4);
            memmove(msubuf, &msubuf[packlen + 4], tail);
        }
 //   } while (continue_flag);
    OutputLog("收到消息!count=%d", count);
    CSocket::OnReceive(nErrorCode);
}
