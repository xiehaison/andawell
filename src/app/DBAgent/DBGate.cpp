// DBGate.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "DBGate.h"
#include "DBGateDlg.h"
#include "inifile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBGateApp
typedef bool (WINAPI *fabc4)(char* mcode);

BEGIN_MESSAGE_MAP(CDBGateApp, CWinApp)
	//{{AFX_MSG_MAP(CDBGateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBGateApp construction

CDBGateApp::CDBGateApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDBGateApp object
CDBGateApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDBGateApp initialization
CString gProgDir;

BOOL CDBGateApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
/*
	char temp[200]="";
	GetCurrentDirectory(199,temp);
	gProgDir=CString(temp);

	char mcode[33]="";
	fabc4 abc4;
	HINSTANCE hdll=LoadLibrary(gProgDir+"\\yten.dll");
	if (hdll==NULL)
	{
		AfxMessageBox("缺少yten.dll动态连接库!");
		exit(0);
	}
	abc4=(fabc4)GetProcAddress(hdll,"abc4");
	if(abc4==NULL)
	{
		AfxMessageBox("yten.dll动态连接库版本错误!");
		exit(0);
	}
	if (!abc4(mcode))
	{
		AfxMessageBox("本程序需要网络支持!");
		exit(0);
	}
	char yzm[17]="";
	calyzm(mcode,yzm);
	CIniFile ini(gProgDir+"\\license.ini");
	ini.SetStringValue("license","magic",CString(mcode));
	CString syzm=ini.GetStringValue("license","code","");
	if (syzm!=CString(yzm))
	{
		CString msg;
		msg=syzm+"序列号错误!请检查license.ini文件中的密码!";
		AfxMessageBox(msg);
		exit(0);
	}
*/
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDBGateDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
