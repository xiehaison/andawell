// DBGateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBAgent.h"
#include "DBAgentDlg.h"

#include "srvcomm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 

#define WM_SockRecv WM_USER+1
#define WM_SockRecvStatus WM_USER+2



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
// CDBGateDlg dialog

CDBGateDlg::CDBGateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBGateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBGateDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);//LoadIcon(IDR_MAINFRAME);
	bIsStart = false;
}

void CDBGateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBGateDlg)
	DDX_Control(pDX, IDC_LIST_BUF, m_buf);
	DDX_Control(pDX, IDC_LIST_COMMANDSERIAL, m_commandserial);
	DDX_Control(pDX, IDC_LIST_SENDSERIAL, m_sendserial);
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_channel);
	DDX_Control(pDX, IDC_LIST_COMMAND, m_listCommand);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDBGateDlg, CDialog)
	//{{AFX_MSG_MAP(CDBGateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_DB, OnButtonDb)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMMANDSERIAL, OnDblclkListCommandserial)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BUF, OnDblclkListBuf)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, OnButtonView)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_DB3, &CDBGateDlg::OnBnClickedButtonDb3)

    ON_MESSAGE(WM_SockRecv, OnSockRecv)
    ON_MESSAGE(WM_SockRecvStatus, OnSockRecvStatus)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBGateDlg message handlers


BOOL CDBGateDlg::OnInitDialog()
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
	COleDateTime m_date = COleDateTime::GetCurrentTime();
	CString str;
	GetWindowText(str);
	SetWindowText(str+" === 启动时间["+m_date.Format("%Y-%m-%d %H:%M:%S")+"]");
	GetDlgItem(IDC_EDIT4)->SetWindowText("-1");


	m_recv.p_ListRecv		= &m_commandserial;
	m_recv.p_ListSend		= &m_sendserial;
	m_recv.p_ListBuf		= &m_buf;
	m_recv.p_ListCommand	= &m_listCommand;

	ListView_SetExtendedListViewStyle(m_listCommand.m_hWnd,LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
//	m_listCommand.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_channel.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_commandserial.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_sendserial.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_buf.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

//	m_imagelist1.Create(16,16,ILC_COLOR,5,0);

	
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
//	m_imagelist1.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

//	m_tab.SetImageList(&m_imagelist1);
//	m_listCommand.SetImageList(&m_imagelist1,LVSIL_SMALL);
//	m_channel.SetImageList(&m_imagelist1,LVSIL_SMALL);
//	m_commandserial.SetImageList(&m_imagelist1,LVSIL_SMALL);
//	m_sendserial.SetImageList(&m_imagelist1,LVSIL_SMALL);
//	m_buf.SetImageList(&m_imagelist1,LVSIL_SMALL);
	


	init_control();	
	adjust();

	//

	SetTimer(1,1000,NULL);
	SetTimer(2,1000,NULL);
	SetTimer(3,10,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDBGateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDBGateDlg::OnPaint() 
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
HCURSOR CDBGateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDBGateDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl * p[]={&m_listCommand,&m_commandserial,&m_buf};
	int iCur = m_tab.GetCurSel();
	for(int i=0;i<sizeof(p)/4;++i)
	{
		if(i == iCur)
			p[i]->ShowWindow(SW_SHOW);
		else
			p[i]->ShowWindow(SW_HIDE);
	}
	
	*pResult = 0;
}

void CDBGateDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_tab.m_hWnd == NULL) return;
	adjust();
}

void CDBGateDlg::adjust()
{
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(1,30,1,1);
	m_tab.MoveWindow(rect);

	rect.DeflateRect(0,24,0,0);
	m_listCommand.MoveWindow(rect);
	m_channel.MoveWindow(rect);
	m_commandserial.MoveWindow(rect);
	m_sendserial.MoveWindow(rect);
	m_buf.MoveWindow(rect);
}

void CDBGateDlg::init_control()
{
	char szTabHead[][21]={"Command状态","命令序列","缓存区状态"};

	for(int i=0;i<sizeof(szTabHead)/21;++i)
		m_tab.InsertItem(i,szTabHead[i],i);

	if(true)
	{
		//命令状态
		char szHead[][21] = {"序号","成功数量","指令类型","状态","记录集","错误描述","参数"};
		int w[]={60,100,100,100,100,150,100,100,100,100,100,100,100,100,100,100,100};
		for(int i=0;i<sizeof(szHead)/21;++i)
			m_listCommand.InsertColumn(i,szHead[i],LVCFMT_LEFT,w[i]);

		//插入列
		char szBuf[255];
		int iSize = GetPrivateProfileInt("chan","cnt",0,"./DBAgent.ini");
		for(int i=0;i<iSize;++i)
		{
			m_listCommand.InsertItem(i,itoa(i,szBuf,10),0);

			m_listCommand.SetItemText(i,3,"关闭");
		}

	}	
	if(true)
	{
		//通道状态
		char szHead[][21] = {"序号","数量","通道命令","指令类型","输入参数","输出参数","更新时间"};
		int w[]={60,100,100,100,100,100,150,100,100,100,100,100,100,100,100,100,100};
		for(int i=0;i<sizeof(szHead)/21;++i)
			m_channel.InsertColumn(i,szHead[i],LVCFMT_LEFT,w[i]);

		//插入列
		char szBuf[255];
		int iSize = GetPrivateProfileInt("chan","cnt",0,"./DbAgent.ini");
		for( int i=0;i<iSize;++i)
			m_channel.InsertItem(i,itoa(i,szBuf,10),0);
	}	
	if(true)
	{
		//接收命令序列
		char szHead[][21] = {"通道","时间","命令字","描述","执行结果"};
		int w[]={60,150,100,100,1000,100,100,100,100,100,100,100,100,100,100,100,100};
		for(int i=0;i<sizeof(szHead)/21;++i)
			m_commandserial.InsertColumn(i,szHead[i],LVCFMT_LEFT,w[i]);
	}	
	if(true)
	{
		//发送命令序列
		char szHead[][21] = {"通道","时间","命令字","描述"};
		int w[]={60,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
		for(int i=0;i<sizeof(szHead)/21;++i)
			m_sendserial.InsertColumn(i,szHead[i],LVCFMT_LEFT,w[i]);
	}	
	if(true)
	{
		//缓存区状态
		char szHead[][21] = {"时间","接收字节","缓存区长度"};
		int w[]={150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
		for(int i=0;i<sizeof(szHead)/21;++i)
			m_buf.InsertColumn(i,szHead[i],LVCFMT_LEFT,w[i]);
	}	
}

void CDBGateDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1://更新Command状态；
		{
			//更新命令状态；
//			m_recv.m_db.UpdateCommand(m_listCommand);

			//更新通道状态；
//			m_recv.m_db.UpdateChannel(m_channel);

			//
			//if(m_link.GetCheck()&&bIsStart)
			//{
			//	//要求自动连接；
			//	
			//	if(m_recv.m_hSocket == INVALID_SOCKET)
			//		m_recv.ConnectServer();
			//	if(m_recv.m_send.m_hSocket == INVALID_SOCKET)
			//		m_recv.m_send.ConnectServer();
			//}

			if(m_commandserial.GetItemCount()>1000)
			{
				for(int j=1000-50;j>0;j--)
				{
					m_commandserial.DeleteItem(j);

				}
				m_commandserial.EnsureVisible(m_commandserial.GetItemCount()-1,0);
			}
			if(m_buf.GetItemCount()>1000)
			{
				for(int j=1000-50;j>0;j--)
				{
					m_buf.DeleteItem(j);

				}
				m_buf.EnsureVisible(m_buf.GetItemCount()-1,0);
			}
				
		}
		break;
	case 2://监控socket连接；
		{
			//更新显示
			int i=0;
			char szBuf[][21]={"","关闭","open...","打开"};
			if(m_recv.m_db._ctp->State == adStateClosed) i=1;
			if(m_recv.m_db._ctp->State == adStateExecuting) i=2;
			if(m_recv.m_db._ctp->State == adStateOpen) i=3;

			GetDlgItem(IDC_EDIT1)->SetWindowText(szBuf[i]);

			//0,关闭 1，正在连接 2，已经连接
			char szS[][21]={"关闭","正在连接...","已经连接"};
//			GetDlgItem(IDC_EDIT2)->SetWindowText(szS[m_recv.status]);
//			GetDlgItem(IDC_EDIT3)->SetWindowText(szS[m_recv.m_send.status]);
		}
		break;
	case 3:
		{
			m_recv.CheckCommandState();
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

LRESULT CDBGateDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_USER+1://
	case WM_USER+2://
		break;
	default:break;
	}
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CDBGateDlg::OnButtonDb() 
{
	// TODO: Add your control notification handler code here
	if(bIsStart)
	{
		//关闭
		bIsStart = false;

		if(m_recv.status == 2)
			m_recv.Close();
		if(m_recv.m_send.status == 2)
			m_recv.m_send.Close();
		m_recv.m_db.CloseDB();
		GetDlgItem(IDC_BUTTON_DB)->SetWindowText("开始");
	}
	else
	{
		//开始
		m_recv.Initialize();
		bIsStart = true;
		GetDlgItem(IDC_BUTTON_DB)->SetWindowText("关闭");
	}

	
}

void CDBGateDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}



void CDBGateDlg::OnKillfocusEdit4() 
{
	// TODO: Add your control notification handler code here
	char szBuf[25];
	GetDlgItem(IDC_EDIT4)->GetWindowText(szBuf,25);
	int i=atol(szBuf);
	sprintf(szBuf,"%d",i);
	GetDlgItem(IDC_EDIT4)->SetWindowText(szBuf);
	m_recv.CurChan=i;
}


void CDBGateDlg::OnDblclkListCommandserial(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	m_commandserial.DeleteAllItems();
	GetDlgItem(IDC_EDIT4)->SetWindowText("999");
	OnKillfocusEdit4();

	int nIndex=m_commandserial.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex!=-1)
	{
		int data=m_commandserial.GetItemData(nIndex);
		for(int i=0;i<m_commandserial.GetItemCount();i++)
		{
			if(data!=m_commandserial.GetItemData(i))
			{
				m_commandserial.DeleteItem(i);
				i--;
			}
		}
	}
	
	*pResult = 0;
}

void CDBGateDlg::OnDblclkListBuf(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_buf.DeleteAllItems();
	
	*pResult = 0;
}

void CDBGateDlg::OnButtonConfig() 
{
	// TODO: Add your control notification handler code here
	WinExec("notepad.exe ./dbagent.ini",SW_SHOW);
}

void CDBGateDlg::OnButtonView() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT4)->SetWindowText("-1");
	OnKillfocusEdit4();
}

void MyOnMsg(int node, char *msg, int len)
{     
    T_MsgServer m_msg;
    m_msg.msg = new char[len];  
    memcpy(m_msg.msg, msg, len);
    m_msg.len = len;
    m_msg.node = node;
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_SockRecv, (WPARAM)&m_msg, NULL);
    delete m_msg.msg;
}



void MyOnNotify(int node, int notify)
{
    T_MsgNotifyServer m_msg;
    m_msg.notify = notify;
    m_msg.node = node;
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_SockRecvStatus, (WPARAM)&m_msg, NULL);
}


LRESULT CDBGateDlg::OnSockRecv(WPARAM wparam, LPARAM lparam)
{
    T_MsgServer *msg = (T_MsgServer *)wparam;
    //char *szBuf = msg->msg;
    //int  len = msg->len;
    m_recv.TakeApartPack(msg);
    return 0;
}


LRESULT CDBGateDlg::OnSockRecvStatus(WPARAM wparam, LPARAM lparam)
{
    T_MsgNotifyServer *msg = (T_MsgNotifyServer *)wparam;
    int  node = msg->node;
    int  notify = msg->notify;
    m_recv.m_node = node;
    return 0;
}


void CDBGateDlg::OnBnClickedButtonDb3()
{
    // TODO:  在此添加控件通知处理程序代码
    static int bopen;
    if (bopen){
        if (m_recv.status == 2)
            m_recv.Close();
        if (m_recv.m_send.status == 2)
            m_recv.m_send.Close();
        m_recv.m_db.CloseDB();
        GetDlgItem(IDC_BUTTON_DB3)->SetWindowText("开始");
    }
    else
    {
        CloseAll();
        StartSrv(1232, 100);
        SetHook(MyOnMsg, MyOnNotify);
        m_recv.Initialize();
        GetDlgItem(IDC_BUTTON_DB3)->SetWindowText("关闭");
    }
    bopen = !bopen;
}
