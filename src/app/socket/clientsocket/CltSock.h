#if !defined(AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_)
#define AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CltSock.h : header file
//



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
	virtual void OnReceive(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	//virtual int Recv(void );
	int Recv(void* lpBuf, int nBufLen, int nFlags = 0)
	{
		if (!SetTimeOut())
			return -1;
		int len = Receive(lpBuf, nBufLen, nFlags);
		KillTimeOut();
		return len;
	}

	int send(const void* lpBuf, int nBufLen, int nFlags = 0)
	{
        if (m_hSocket == INVALID_SOCKET)
            return -1;
		if (!SetTimeOut())
			return -1;
		int len = Send(lpBuf, nBufLen, nFlags);
		KillTimeOut();
		return len;
	}

	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCltSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	private:
		BOOL SetTimeOut(UINT uTimeOut = 1000)
		{
			m_nTimerID = SetTimer(NULL,0,uTimeOut,NULL);
			return m_nTimerID;
		}
		
		BOOL KillTimeOut()
		{
			return KillTimer(NULL,m_nTimerID);
		}
	protected:
		virtual BOOL OnMessagePending();
	private:
		int m_nTimerID;

// Implementation
	protected:
};


#define MAX_QUEUE 2048

template <class T>
class CMyFifo{
public:
    T queue[MAX_QUEUE];
    int	 m_pHead;
    int  m_pTail;
    bool m_seizure;
public:
    CMyFifo()
    {
        m_pHead = 0;
        m_pTail = 0; 
        memset(queue, 0, sizeof(T)*MAX_QUEUE);
    }

    void RemoveHead(T &msg)
    {
        memcpy(&msg, &queue[m_pHead], sizeof(T));
        m_pHead++;
        if (m_pHead >= MAX_QUEUE)
            m_pHead = 0;
    }

    void GetHead(T &msg)
    {
        memcpy(&msg, &queue[m_pHead], sizeof(T));
    }

    void RemoveAll()
    {
        m_pHead = 0;
        m_pTail = 0;
        memset(queue, 0, sizeof(T)*MAX_QUEUE);
    }

    int AddTail(T f1)
    {
        if (GetCount() == MAX_QUEUE - 1){
            return -1;
        }
        memcpy(&queue[m_pTail], &f1, sizeof(T));
        m_pTail++;
        if (m_pTail >= MAX_QUEUE)
            m_pTail = 0;

        return m_pTail;
    }
};


class CClientComm:public  CObject
{
public:
    CCltSock m_Sock;
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
            //m_Sock.Close();
        }
    }
protected:;
private:;
        
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLTSOCK_H__AD6A6430_37CE_4173_BDDC_B7602182EE4A__INCLUDED_)
