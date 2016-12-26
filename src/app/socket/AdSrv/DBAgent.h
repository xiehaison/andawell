// DBGate.h : main header file for the DBGATE application
//

#if !defined(AFX_DBGATE_H__74939907_E615_4416_85D5_83D80B8A9860__INCLUDED_)
#define AFX_DBGATE_H__74939907_E615_4416_85D5_83D80B8A9860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDBGateApp:
// See DBGate.cpp for the implementation of this class
//

class CDBGateApp : public CWinApp
{
public:
	CDBGateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDBGateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGATE_H__74939907_E615_4416_85D5_83D80B8A9860__INCLUDED_)
