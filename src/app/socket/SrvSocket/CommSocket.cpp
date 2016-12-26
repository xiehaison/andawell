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

SOCKET gSocket;

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
    CTime now = CTime::GetCurrentTime();
    CString ss, s = now.Format("%c");
    ss.Format("%s(%3u)=>%s\n", s, GetTickCount() % 1000, buf);

	OutputDebugString(ss);
}


CCommSocket::CCommSocket()
{
	m_node = -1;
	m_name = "";
}


CCommSocket::~CCommSocket()
{
    if (m_hSocket != INVALID_SOCKET)
    {
        //ShutDown(2);
        //Close();
    }
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
    int node = m_node;
    if (m_hSocket == INVALID_SOCKET)
        return;
    if (gpCallBackNotify)
    {
        gSocket = m_hSocket;
        gpCallBackNotify(m_node, 0, (char *)&gSocket);
    }
    Close();
    OutputLog("node %d, socket closed", m_node);
    CSocket::OnClose(nErrorCode);
}

#define MAX_MSU_LEN  2048
#define MAX_BUFFER_SIZE MAX_MSU_LEN*10
void CCommSocket::OnReceive(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    static DWORD count;
    char *msu = NULL;
    WORD head,msulen;

    static WORD tail;
    static BYTE buf[MAX_BUFFER_SIZE];
    int len = 0;
    bool continue_flag = false;
//    do{
        len = Recv(&buf[tail], MAX_BUFFER_SIZE - tail);

        if (len < 0){
            OutputLog("读取包错误!");
            memset(buf, 0, sizeof(buf));
            tail = 0;
            gLsnSocket.release(m_node);
            return;
        }
        //#define self_test 0
#ifdef self_test
        //自环测试
        send(buf, len);  
        continue_flag = (len == MAX_BUFFER_SIZE);
#else   
        continue_flag = (len == MAX_BUFFER_SIZE - tail);
        tail += len;
        while (tail > 4){
            head = *(WORD*)&buf[0];
            if (head != PACKET_HEAD){
                OutputLog("包头错误!请重新连接");
                memset(buf, 0, sizeof(buf));
                tail = 0;
                gLsnSocket.release(m_node);
                return;
            }
            msulen = *(WORD*)&buf[2];

            if (tail < msulen + 4)
                break;

            msu = (char*)&buf[4];
            if (gpCallBackMsg)
                gpCallBackMsg(m_node, msu, msulen);
            tail -= (msulen + 4);
            memmove(buf, &buf[msulen + 4], tail);
        }
#endif //self_test
//    }while (continue_flag);
	CSocket::OnReceive(nErrorCode);
}


void CCommSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	OutputLog("Server OnOutOfBandData");
	CancelBlockingCall();
	CSocket::OnOutOfBandData(nErrorCode);
}


int SetHook(OnMsg msg,OnNotify notify)
{
	gpCallBackMsg = msg;
	gpCallBackNotify = notify;
	return 0;
}

