#if !defined(AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_)
#define AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CltSock.h : header file
//

#include "clientsock_asyn.h"
#include <list>


/////////////////////////////////////////////////////////////////////////////
// CCltSock command target

class CCltSock : public CSocket
{
// Attributes
public:
    int m_dir;

// Operations
public:
	CCltSock();
	virtual ~CCltSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCltSock)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	int Recv(void* lpBuf, int nBufLen, int nFlags = 0)
	{
		if (!SetTimeOut())
            return E_ERROR_Timeout;
		int len = Receive(lpBuf, nBufLen, nFlags);
		KillTimeOut();
		return len;
	}
    int Send(const void* lpBuf, int nBufLen, int nFlags = 0)
    {
        if (!SetTimeOut())
            return E_ERROR_Timeout;
        int len = CSocket::Send(lpBuf, nBufLen, nFlags);
        KillTimeOut();
        return len;
    }

	int send(const void* lpBuf, int nBufLen, int nFlags = 0)
	{
		if (!SetTimeOut())
            return E_ERROR_Timeout;
        int len = CSocket::Send(lpBuf, nBufLen, nFlags);
		KillTimeOut();
		return len;
	}

	// Generated message map functions
	//{{AFX_MSG(CCltSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	private:
		BOOL SetTimeOut(UINT uTimeOut=1000)
		{
			m_nTimerID = SetTimer(NULL,0,uTimeOut,NULL);
			return m_nTimerID;
		}
		
		
		BOOL KillTimeOut()
		{
			return KillTimer(NULL,m_nTimerID);
		}
	private:
		int m_nTimerID;


// Implementation
	protected:
		virtual BOOL CCltSock::OnMessagePending()
		{
			// TODO: Add your specialized code here and/or call the base class

			MSG msg;
			if (::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
			{
				if (msg.wParam == (UINT)m_nTimerID)
				{
					// Remove the message and call CancelBlockingCall.
					::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
                    OutputLog("Client--OnMessagePending--CancelBlockingCall");

                    CancelBlockingCall();
//					ShutDown();
					return FALSE;
					// No need for idle time processing.
				}
			}
			return CSocket::OnMessagePending();
		}

};

typedef struct {
    WORD len;
    BYTE  * buf;
}S_Buf;


class CClientComm:public  CObject
{
public:
    CCltSock m_Sock;
    list < T_Msg > m_SendQueue;
    list < T_Msg > m_RecvQueue;
    list <T_MsgNotify> m_listnotify;

    int m_Node;
    CClientComm()
    {
        m_Sock.m_hSocket = INVALID_SOCKET;
        m_Node = -1;
    }

    void Init()
    {
        m_Sock.m_hSocket = INVALID_SOCKET;
        m_Node = -1;

    }
    virtual ~CClientComm(){};
    void Close()
    {
        if (m_Sock.m_hSocket != INVALID_SOCKET){
            m_Sock.ShutDown(2);
            m_SendQueue.clear();
            m_RecvQueue.clear();
            m_listnotify.clear();
        }
        m_Node = -1;
        return;
    }
protected:;
private:;
        
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_)
