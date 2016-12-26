#if !defined(AFX_COMMSOCKET_H__9983AADD_E747_48D4_A7DF_D4148469BEBA__INCLUDED_)
#define AFX_COMMSOCKET_H__9983AADD_E747_48D4_A7DF_D4148469BEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCommSocket command target

class CCommSocket : public CSocket
{
// Attributes
public:
	CString m_name;
	int m_node;
    int m_dir;
// Operations
public:
	CCommSocket();
	virtual ~CCommSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual BOOL OnMessagePending();
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCommSocket)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	public:
		BOOL SetTimeOut(UINT uTimeOut=1000);
		BOOL KillTimeOut();
	private:
		int m_nTimerID;

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSOCKET_H__9983AADD_E747_48D4_A7DF_D4148469BEBA__INCLUDED_)

