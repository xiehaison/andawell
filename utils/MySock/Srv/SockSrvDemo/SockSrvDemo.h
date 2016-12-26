// SockSrvDemo.h : main header file for the SOCKSRVDEMO application
//

#if !defined(AFX_SOCKSRVDEMO_H__FAC47DE2_33A6_4F0D_8C85_F5BDFC53A66B__INCLUDED_)
#define AFX_SOCKSRVDEMO_H__FAC47DE2_33A6_4F0D_8C85_F5BDFC53A66B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSockSrvDemoApp:
// See SockSrvDemo.cpp for the implementation of this class
//

class CSockSrvDemoApp : public CWinApp
{
public:
	CSockSrvDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockSrvDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSockSrvDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKSRVDEMO_H__FAC47DE2_33A6_4F0D_8C85_F5BDFC53A66B__INCLUDED_)
