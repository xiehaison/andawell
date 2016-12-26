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
	virtual BOOL OnMessagePending();
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCltSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	public:
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
};

class CClientComm:public  CObject
{
public:
    CCltSock *m_pSendSock;
    CCltSock *m_pRecvSock;
    int m_Node;
    CClientComm()
    {
        m_pSendSock = NULL;
        m_pRecvSock = NULL;
        m_Node = -1;
    }
    virtual ~CClientComm(){};
    void Close()
    {
        if (m_pSendSock)
        {
            delete m_pSendSock;
            m_pSendSock = NULL;
        }
        
        if (m_pRecvSock)
        {
            delete m_pRecvSock;
            m_pRecvSock = NULL;
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
