#if !defined(AFX_COMMSEND_H__1C668C74_153A_4764_97C4_DDEFEE046927__INCLUDED_)
#define AFX_COMMSEND_H__1C668C74_153A_4764_97C4_DDEFEE046927__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSend.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCommSend command target

class CCommSend : public CSocket
{
// Attributes
public:
    CString m_name;
    int m_node;
    int m_dir;

// Operations
public:
	CCommSend();
	virtual ~CCommSend();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSend)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCommSend)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSEND_H__1C668C74_153A_4764_97C4_DDEFEE046927__INCLUDED_)
