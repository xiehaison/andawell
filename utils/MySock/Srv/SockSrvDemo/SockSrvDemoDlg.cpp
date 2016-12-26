// SockSrvDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SockSrvDemo.h"
#include "SockSrvDemoDlg.h"
#include "..\\socksrv\\srvintf.h"
#include <sys/timeb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockSrvDemoDlg dialog
CSockSrvDemoDlg* pdlg;

CSockSrvDemoDlg::CSockSrvDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockSrvDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSockSrvDemoDlg)
	m_code = 0;
	m_content = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pdlg=this;
}

void CSockSrvDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockSrvDemoDlg)
	DDX_Control(pDX, IDC_EDRECVPAK, m_ctrlLog);
	DDX_Text(pDX, IDC_EDCODE, m_code);
	DDX_Text(pDX, IDC_EDCONTENT, m_content);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockSrvDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSockSrvDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockSrvDemoDlg message handlers
void OnRecvPak(int code,const char* pak)
{
//	pdlg->AddLog("From[%d]%s",code,pak);
	SendPak(code,pak,20);
}

void OnSysMsg(int status,const char* msg)
{
	pdlg->AddLog("Status=%d;msg=%s",status,msg);
}

BOOL CSockSrvDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	StartUpSrv(1234,600);
	HookRecvPakFunc(OnRecvPak);
	HookSysMsgFunc(OnSysMsg);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSockSrvDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSockSrvDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSockSrvDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSockSrvDemoDlg::AddLog(const char *line, ...)
{
	char buf[1024];
	memset(buf,0,1024);
	
	va_list args;
	va_start(args, line);
	_vsnprintf (buf, sizeof(buf), line, args);
    va_end(args);
	
	strcat(buf, "\r\n");
	
	struct _timeb tstruct;
	_ftime( &tstruct );
	
	CTime t=CTime::GetCurrentTime();
	CString dline;
	dline.Format("%s(%3u)=>%s",t.Format("%H:%M:%S"),tstruct.millitm,buf);
	//	UpdateData(TRUE);
	CString buf1;///char buf[2048]="";
	m_ctrlLog.GetWindowText(buf1);
	buf1=buf1+dline;
	int linecnt=m_ctrlLog.GetLineCount();
	if (linecnt>100)
	{
		int pos=buf1.Find("\r\n");
		buf1.Delete(0,pos+2);
	}
	m_ctrlLog.SetWindowText(buf1);
	//	UpdateData(FALSE);
	m_ctrlLog.SetSel(buf1.GetLength(),buf1.GetLength());
}

void CSockSrvDemoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	char buf[600]="";
	strcpy(buf,m_content);
	SendPak(m_code,buf,600);
}
