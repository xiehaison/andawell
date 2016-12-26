#if !defined(AFX_SRVSOCK_H__61B5DB7D_A9D1_4833_AD95_B98ACEBFE246__INCLUDED_)
#define AFX_SRVSOCK_H__61B5DB7D_A9D1_4833_AD95_B98ACEBFE246__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrvSock.h : header file
//
#include "comm.h"



/////////////////////////////////////////////////////////////////////////////
// SrvSock command target

class SrvSock : public CSocket
{
// Attributes
public:

// Operations
public:
	SrvSock();
	virtual ~SrvSock();
    comm *m_pSockRecv ;
    comm *m_pSockSend ;
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SrvSock)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(SrvSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVSOCK_H__61B5DB7D_A9D1_4833_AD95_B98ACEBFE246__INCLUDED_)
