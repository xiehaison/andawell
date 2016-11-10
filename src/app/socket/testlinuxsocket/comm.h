#if !defined(AFX_COMM_H__CA834F5F_68FE_4AF4_8324_B0D82FD23746__INCLUDED_)
#define AFX_COMM_H__CA834F5F_68FE_4AF4_8324_B0D82FD23746__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// comm.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// comm command target


class comm : public CSocket
{
// Attributes
public:
	CString m_name;

// Operations
public:
	comm();
	virtual ~comm();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(comm)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual BOOL OnMessagePending();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(comm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMM_H__CA834F5F_68FE_4AF4_8324_B0D82FD23746__INCLUDED_)
