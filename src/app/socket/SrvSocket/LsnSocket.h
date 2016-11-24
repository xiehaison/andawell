#if !defined(AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_)
#define AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LsnSocket.h : header file
//

#include "CommSocket.h"
//#defined MAX_NODE 10000
void OutputLog(LPCTSTR DbgMessage,...);

/////////////////////////////////////////////////////////////////////////////
// CLsnSocket command target

class CLsnSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CLsnSocket();
	virtual ~CLsnSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLsnSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLsnSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
/*
	public:
		BOOL SetTimeOut(UINT uTimeOut=1000);
		BOOL KillTimeOut();
	private:
		LONGLONG m_llDtStart;
		UINT  m_uTimeOut; 
*/

// Implementation
public:
    CCommSocket *m_pSockRecv[MAX_NODE];
    CCommSocket *m_pSockSend[MAX_NODE];
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_)


