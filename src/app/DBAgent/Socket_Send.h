#if !defined(AFX_SOCKET_SEND_H__2896E047_9D3E_4534_9632_54085E18E216__INCLUDED_)
#define AFX_SOCKET_SEND_H__2896E047_9D3E_4534_9632_54085E18E216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Socket_Send.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSocket_Send command target

class CSocket_Send : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	int status;//0,关闭 1，正在连接 2，已经连接
	CSocket_Send();
	virtual ~CSocket_Send();

// Overrides
public:
	void ConnectServer();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocket_Send)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocket_Send)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKET_SEND_H__2896E047_9D3E_4534_9632_54085E18E216__INCLUDED_)
