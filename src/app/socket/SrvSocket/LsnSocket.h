#if !defined(AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_)
#define AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LsnSocket.h : header file
//

#include "SrvSocket.h"
#include "commsocket.h"
#include "SrvComm.h"
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
    void release(int node)
    {
        if (node < 0)
            return;
        if (m_Sock[node].m_hSocket != INVALID_SOCKET)
        {
            m_Sock[node].ShutDown(2);
        }
    }


	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLsnSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
// Implementation
public:
    CCommSocket m_Sock[MAX_NODE];
    CCommSocket sock;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSNSOCKET_H__424A6DAA_64E4_4B27_93F5_8BA6FB274C5A__INCLUDED_)


