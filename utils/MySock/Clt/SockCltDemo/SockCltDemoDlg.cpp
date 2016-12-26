// SockCltDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SockCltDemo.h"
#include "SockCltDemoDlg.h"
#include "..\\sockclt\\cltintf.h"
#include <sys/timeb.h>
#include <process.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
int gRecvCnt=0;
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
// CSockCltDemoDlg dialog
CSockCltDemoDlg* pdlg;
CSockCltDemoDlg::CSockCltDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockCltDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSockCltDemoDlg)
	m_sendtext = _T("");
	m_sendcnt = 0;
	m_interval = 0;
	m_cenip = _T("");
	m_cenport = 0;
	m_paksize = 0;
	m_code = 0;
	m_log = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pdlg=this;
}

void CSockCltDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockCltDemoDlg)
	DDX_Control(pDX, IDC_EDRECVTEXT, m_ctrlLog);
	DDX_Control(pDX, IDC_STARTUP, m_startup);
	DDX_Control(pDX, IDC_RECVCNT, m_recvcnt);
	DDX_Text(pDX, IDC_EDSENDTEXT, m_sendtext);
	DDX_Text(pDX, IDC_SENDCNT, m_sendcnt);
	DDX_Text(pDX, IDC_INTERVAL, m_interval);
	DDX_Text(pDX, IDC_CENIP, m_cenip);
	DDX_Text(pDX, IDC_CENPORT, m_cenport);
	DDX_Text(pDX, IDC_PAKSIZE, m_paksize);
	DDX_Text(pDX, IDC_CODE, m_code);
	DDX_Text(pDX, IDC_EDRECVTEXT, m_log);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockCltDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSockCltDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_STARTUP, OnStartup)
	ON_BN_CLICKED(IDC_CONSEND, OnConsend)
	ON_BN_CLICKED(IDC_ZERO, OnZero)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockCltDemoDlg message handlers
void OnRecvPak(const char* pak)
{
	pdlg->AddRecvLine("recv %s",pak);
	gRecvCnt++;
	CString t;
	t.Format("%d",gRecvCnt);
	pdlg->m_recvcnt.SetWindowText(t);
}

void OnStatus(int status)
{
	if(pdlg!=NULL)
	{
		if(status==MSG_CLT_DISCONNECT)
			pdlg->AddRecvLine("disconnect");
		else if(status==MSG_CLT_SEND_CONNECT)
			pdlg->AddRecvLine("send sock connected");
		else if(status==MSG_CLT_RECV_CONNECT)
			pdlg->AddRecvLine("recv sock connected");
		else if(status==MSG_CLT_BUF_OVERFLOW)
			pdlg->AddRecvLine("buf over flow,cleared");
	}
}

BOOL CSockCltDemoDlg::OnInitDialog()
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
	m_cenip="192.168.2.188";
	m_cenport=1234;
	m_code=1;
	m_paksize=600;
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSockCltDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSockCltDemoDlg::OnPaint() 
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
HCURSOR CSockCltDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSockCltDemoDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	char buf[25]="";
	UpdateData(TRUE);
	strcpy(buf,m_sendtext);
	SendPacket(buf);
}

void CSockCltDemoDlg::OnStartup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetPara(m_cenip,m_cenport,m_code,m_paksize);
	if(StartUpClt())
	{
		HookCltRecvPak(OnRecvPak);
		HookCltSysMsg(OnStatus);
		m_startup.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CSockCltDemoDlg::AddRecvLine(const char *line, ...)
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

int sendcnt;
int interval;
void Thread_Send(LPVOID param)
{
	int cnt;
	int intval;
	cnt=sendcnt;
	intval=interval;

	char pak[800]="";
	strcpy(pak,"kjkjkjkjkj");
	int i;
	for(i=0;i<cnt;i++)
	{
		SendPacket(pak);
		Sleep(intval);
	}
}

void CSockCltDemoDlg::OnConsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	sendcnt=m_sendcnt;
	interval=m_interval;
	_beginthread(Thread_Send,0,NULL);
	
	UpdateData(FALSE);
}


void CSockCltDemoDlg::OnZero() 
{
	// TODO: Add your control notification handler code here
	gRecvCnt=0;
	m_recvcnt.SetWindowText("0");
}
