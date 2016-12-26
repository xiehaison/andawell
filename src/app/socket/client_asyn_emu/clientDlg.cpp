// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "../clientsocket_asyn/clientsock_asyn.h"

#include "../include/packet.h"
//#pragma comment (lib,"D:/work8/andawell/bin/clientsocket_asyn.dll"); 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SockRecv WM_USER+1
#define WM_SockStatus WM_USER+2 


/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_strLog = _T("");
	m_rip = _T("127.0.0.1");
	m_rport = _T("1232");
	m_node = _T("10");
    bconn = 0;
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
    DDX_Text(pDX, IDC_NODE, m_node);
    DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_WM_CLOSE()

	//}}AFX_MSG_MAP
    ON_WM_TIMER()

    //ON_MESSAGE(WM_SockRecv, OnSockRecv)
    //ON_MESSAGE(WM_SockStatus, OnSockStatus)

    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CClientDlg::OnSelchangeTab1)
    ON_BN_CLICKED(IDC_Clear, &CClientDlg::OnBnClickedClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers
CClientDlg *g_Dlg = NULL;
BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    

    g_Dlg = this;
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
		ar >> m_node; 

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
	
    m_montest.Create(IDD_MON_TEST, &m_tab);
    m_manager.Create(IDD_MANAGER, &m_tab);
    m_ProgTest.Create(IDD_PROJ_TEST, &m_tab);

    //m_montest.Create(IDD_MON_TEST, this);
    //m_manager.Create(IDD_MANAGER, this);
    //m_ProgTest.Create(IDD_PROJ_TEST, this);

    char szTabHead[][21] = { "管理部分", "检测项目", "监控部分" };
    CDialog *pWnd[] = { &m_manager, &m_ProgTest, &m_montest };
    for (int i = 0; i < sizeof(szTabHead) / 21; i++){
        m_tab.InsertItem(i, szTabHead[i], i);
    }
    Adjust();
	UpdateData(0);
    SetTimer(0, 1000, NULL);
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
    T_MsgNotify *m_msg = (T_MsgNotify *)msg;

    ::SendMessage(g_Dlg->m_hWnd, WM_SockStatus, (WPARAM)m_msg, (LPARAM)&code);
}


LPTSTR ConvertErrorCodeToStr(DWORD ErrorCode)
{
    HLOCAL LocalAddress = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, ErrorCode, 0, (LPTSTR)&LocalAddress, 0, NULL);
    return (LPTSTR)LocalAddress;
}


//status =0 不显示所有
//status =1 显示tab选择
//status =2 显示所有
void CClientDlg::ShowConnectStatus(int status )
{
    CWnd * p[] = { &m_manager, &m_ProgTest, &m_montest };
    int size = sizeof(p) / sizeof(CWnd*);
    if (status == 1){
        int iCur = m_tab.GetCurSel();

        for (int i = 0; i<size; i++)
        {
            if (i == iCur)
                p[i]->ShowWindow(SW_SHOW);
            else
                p[i]->ShowWindow(SW_HIDE);
        }
    }
    else if (status == 0)
        for (int i = 0; i<size; i++)
            p[i]->ShowWindow(SW_HIDE);
    else if (status == 2)
        for (int i = 0; i<size; i++)
            p[i]->ShowWindow(SW_SHOW);
}

void CClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
    if (bconn==2){
        CloseAll();
        ShowConnectStatus(0);
        bconn = -1;
    }
    else if ( bconn == 0 ){
        //SetHook(RecvMsg, Notify);
        SetTimer(1, 1000, NULL);
        DWORD ret = StartClient(m_rip, atoi(m_rport), atoi(m_node));
        if (ret){
            Output("启动客户端失败!error=%d,strerr=%s", ret, ConvertErrorCodeToStr(ret));
            return;
        }
        GetDlgItem(IDC_RIP)->EnableWindow(0);
        GetDlgItem(IDC_RPORT)->EnableWindow(0);
        GetDlgItem(IDC_NODE)->EnableWindow(0);

        ShowConnectStatus(1);
        GetDlgItem(IDC_CONNECT)->SetWindowText("正在连接...");
        bconn = -1;
    }
}


void CClientDlg::OnClose() 
{
	CDialog::OnClose();
}


BOOL CClientDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CloseAll();
	return CDialog::DestroyWindow();
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    char szS[][21] = { "连接", "正在连接...", "断开" };
    switch (nIDEvent)
    {
    case 0:
        break;
    case 1:
        {
            T_MsgNotify *pmsg = NULL;
            while ((pmsg=GetNotify())!=NULL )
            {
                T_MsgNotify msg = *pmsg;
                OnSockStatus_Asyn(msg);
            }
        }
        break;
    case 2:
        {
            T_Msg *pmsg = NULL;
            while ((pmsg = GetRecvMsg()) != NULL)
            {
                //Output("收到数据包,类型:%s", GetMsgTypeStr(GetMsgType(pmsg->msg)));
                OnSockRecv_Asyn(pmsg);
            }
        }

        break;
    default:;

    }
    CDialog::OnTimer(nIDEvent);
}


int PackMsg_ReqMonitorResult(DWORD dst,DWORD src,bool result)
{
    tag_ID_Packet pak;
    pak.PackType = IA_ReqMonitorResult;
    pak.DesCode = dst;
    pak.SrcCode = src;
    pak.ReqMonitorResult.result = result;


    TcpSockSend((void*)&pak, sizeof(pak));
    return 0;
}


int CClientDlg::OnSockRecv_Asyn(T_Msg *pmsg)
{
    int len = pmsg->len;
    DWORD type = GetMsgType(pmsg->msg);
	UpdateData(0);
	Output("收到消息,%s", GetMsgTypeStr(type));
    switch (type)
    {
    case IA_ReqMonitor:
        PackMsg_ReqMonitorResult(GetMsgSrc(pmsg->msg), GetMsgDst(pmsg->msg), m_montest.m_accept_monitor);

        break;
    case ID_ReqMonitor:
        PackMsg_ReqMonitorResult(GetMsgSrc(pmsg->msg), GetMsgDst(pmsg->msg), m_montest.m_accept_monitor);
        break;
    default:
        break;
    }
    return 0;
}


int CClientDlg::OnSockStatus_Asyn(T_MsgNotify msg)
{
    int notify = msg.notify;
    if (notify >0 ){
        SetTimer(2, 100, NULL);  //启动接收线程
        bconn = 2;
    }
    else if (notify < 0) {
        GetDlgItem(IDC_RIP)->EnableWindow(1);
        GetDlgItem(IDC_RPORT)->EnableWindow(1);
        GetDlgItem(IDC_NODE)->EnableWindow(1);
        ShowConnectStatus(0);
        bconn = 0;
        KillTimer(2); //socket连接中断,停止接收线程
    }
    Output("收到通知消息[%s,node=%d,dir=%d]", msg.msg, msg.node, msg.dir);

    char szS[][21] = { "连接", "正在连接...", "断开" };
    GetDlgItem(IDC_CONNECT)->SetWindowText(szS[bconn]);

    return 0;
}



void CClientDlg::OnDestroy()
{
    UpdateData();
    CFile file("settings_client.tmp", CFile::modeReadWrite | CFile::modeCreate);
    CArchive ar(&file, CArchive::store);
    try
    {
        ar << m_rip;
        ar << m_rport;
        ar << m_node;

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
    CDialog::OnDestroy();

    // TODO:  在此处添加消息处理程序代码
}


void CClientDlg::Adjust()
{
    CRect rect;
    m_tab.GetClientRect(rect);
    rect.DeflateRect(1, 30, 1, 1);
//    m_tab.MoveWindow(rect);
    rect.DeflateRect(15, 30, 0, 0);

    CWnd *p[] = { &m_manager, &m_ProgTest, &m_montest };
    int size = sizeof(p) / sizeof(CWnd*);
    for (int i = 0; i < size; ++i){
        p[i]->MoveWindow(rect);
        p[i]->ShowWindow(SW_HIDE);
    }
}


void CClientDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO:  在此处添加消息处理程序代码
    if (m_tab.m_hWnd == NULL) return;
    Adjust();

}


void CClientDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    if (bconn==2)
        ShowConnectStatus(1);
    *pResult = 0;
}


void CClientDlg::OnBnClickedClear()
{
    // TODO:  在此添加控件通知处理程序代码
    m_strLog = "";
    UpdateData(0);
}
