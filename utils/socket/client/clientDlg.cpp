// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "../clientsocket/clientsock.h"

#include "../include/packet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_strLog = _T("");
	m_rip = _T("192.168.1.193");
	m_rport = _T("9900");
	m_sendbuf = _T("");
	m_node = _T("10");
	m_cin_caller = _T("123456");
	m_cin_called = _T("123456789");
	m_cin_channel = _T("10");
	m_msgtype = _T("");
	m_msgchan = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_Output, m_ctrlLog);
	DDX_Text(pDX, IDC_Output, m_strLog);
	DDX_Text(pDX, IDC_RIP, m_rip);
	DDX_Text(pDX, IDC_RPORT, m_rport);
	DDX_Text(pDX, IDC_SENDBUF, m_sendbuf);
	DDX_Text(pDX, IDC_NODE, m_node);
	DDX_Text(pDX, IDC_CIN_CALLER, m_cin_caller);
	DDX_Text(pDX, IDC_CIN_CALLED, m_cin_called);
	DDX_Text(pDX, IDC_CIN_CHANNEL, m_cin_channel);
	DDX_CBString(pDX, IDC_MSGTYPE, m_msgtype);
	DDX_Text(pDX, IDC_EDIT2, m_msgchan);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SENDPACK, OnSendpack)
	ON_BN_CLICKED(IDC_CALLOUT, OnCallout)
	ON_BN_CLICKED(IDC_HungUP, OnHungUP)
	ON_BN_CLICKED(IDC_SendMSG, OnSendMSG)
	ON_BN_CLICKED(IDC_BREAK, OnBreak)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers
CClientDlg *g_Dlg = NULL;
BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	g_Dlg=this;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CFile file("settings_client.tmp",CFile::modeReadWrite);
	
	CArchive ar(&file, CArchive::load);
	try
	{
		ar >> m_rip;  
		ar >> m_rport;  
		ar >> m_sendbuf; 
		ar >> m_node; 
		ar >> m_cin_caller; 
		ar >> m_cin_called ;
		ar >> m_cin_channel;
		ar.Close();
	}
	catch (CMemoryException* e)
	{		
		e->ReportError();
		ar.Close();
	}
	catch (CFileException* e)
	{
		e->ReportError();
		ar.Close();
	}
	catch (CException* e)
	{
		e->ReportError();
		ar.Close();
	}
	
	
	UpdateData(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void Notify(char *msg,int code)
{
	g_Dlg->Output("RecvNotify msg:%s,code:%04X",msg,code);
}


void RecvMsg(char *msg,int len)
{
	((CClientDlg*)AfxGetMainWnd())->Output("RecvMsg msgtype:%s,len:%04X",((S_MessagePacket*)msg)->OutputTypeString(),len);	
	S_MessagePacket *p_msg = (S_MessagePacket *)msg;
	if( p_msg->m_msgtype == T_AC_TEST_PACKET )
	{
		((CClientDlg*)AfxGetMainWnd())->Output("msg=%s",p_msg->m_Msg.m_AC_TEST_PACKET.m_testdata);
	}
}


void CClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
    UpdateData(1);
	SetHook(RecvMsg,Notify);
	StartClient(m_rip,atoi(m_rport),atoi(m_node));
}


void CClientDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData();
	CFile file("settings_client.tmp",CFile::modeReadWrite |CFile::modeCreate);
	CArchive ar(&file, CArchive::store);
	try
	{
		ar << m_rip;  
		ar << m_rport;  
		ar << m_sendbuf; 
		ar << m_node; 
		ar << m_cin_caller; 
		ar << m_cin_called ;
		ar << m_cin_channel;

		ar.Close();	
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		ar.Close();	
	}
	catch (CFileException* e)
	{
		e->ReportError();
		ar.Close();	
	}
	catch (CException* e)
	{
		e->ReportError();
		ar.Close();	
	}
    CloseAll();	
	CDialog::OnClose();
}


void CClientDlg::OnSendpack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	S_MessagePacket testpack;
    int len = testpack.Init(T_AC_TEST_PACKET);
	strcpy(testpack.m_Msg.m_AC_TEST_PACKET.m_testdata, m_sendbuf);
	testpack.m_msglen = strlen(testpack.m_Msg.m_AC_TEST_PACKET.m_testdata);
	
	SendPacket((const char*)&testpack,len);
}


void CClientDlg::OnCallout() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	S_MessagePacket msg;
    int len = msg.Init(T_ACWaitCall);
	msg.m_Msg.m_ACWaitCall.lch = atoi(m_cin_channel);
	strcpy(msg.m_Msg.m_ACWaitCall.called, m_cin_called);
	strcpy(msg.m_Msg.m_ACWaitCall.caller,m_cin_caller);
	SendPacket((const char *)&msg,len);
}


void CClientDlg::OnHungUP() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	S_MessagePacket msg;
	int len = msg.Init(T_ACRelease);
	msg.m_Msg.m_ACRelease.lch = atoi(m_cin_channel);
	SendPacket((const char *)&msg,len);	
}


void CClientDlg::OnSendMSG() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	S_MessagePacket msg;
	int len = 0;
	if (m_msgtype == "摘机")
	{
        len = msg.Init(T_ACAnswerCall);
        msg.m_Msg.m_ACRelease.lch = atoi(m_cin_channel);
	}
    else if (m_msgtype == "挂机")
    {
        len = msg.Init(T_ACRelease);
        msg.m_Msg.m_ACRelease.lch = atoi(m_cin_channel);
    }
    else if (m_msgtype == "振铃")
    {
        len = msg.Init(T_ACAcceptCall);
        msg.m_Msg.m_ACAcceptCall.lch = atoi(m_cin_channel);
    }
    else if(m_msgtype == "")
        return;

	SendPacket((const char *)&msg,len);	
}


void CClientDlg::OnBreak() 
{
	// TODO: Add your control notification handler code here

	CloseAll();
}


BOOL CClientDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CloseAll();
	return CDialog::DestroyWindow();
}




void CClientDlg::OnBnClickedButton1()
{
    // TODO:  在此添加控件通知处理程序代码
}
