// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"


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
    //}}AFX_DATA_MAP
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

    ON_MESSAGE(WM_SockRecv, OnSockRecv)
    ON_MESSAGE(WM_SockStatus, OnSockStatus)

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
	
    char szTabHead[][21] = { "数据库", "测试项目", "管理","监控" };
    CDialog *pWnd[] = { &m_dbtest, &m_apptest, &m_ctrltest, &m_montest };

    m_dbtest.Create(IDD_DB_Test, this);
    m_apptest.Create(IDD_APP_TEST, this);
    m_ctrltest.Create(IDD_CTRL_TEST, this);
    m_montest.Create(IDD_MON_TEST, this);
    for (int i = 0; i < sizeof(szTabHead) / 21; i++){
        m_tab.InsertItem(i, szTabHead[i], i);
    }
    Adjust();
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
    T_MsgNotify *m_msg = (T_MsgNotify *)msg;

    ::SendMessage(g_Dlg->m_hWnd, WM_SockStatus, (WPARAM)m_msg, (LPARAM)&code);
}


void RecvMsg(char *msg,int len)
{

    DBPacket *pak = (DBPacket *)msg;
    ::SendMessage(g_Dlg->m_hWnd, WM_SockRecv, (WPARAM)pak, NULL);
}


LPTSTR ConvertErrorCodeToString(DWORD ErrorCode)
{
    HLOCAL LocalAddress = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, ErrorCode, 0, (LPTSTR)&LocalAddress, 0, NULL);
    return (LPTSTR)LocalAddress;
}


void CClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
    if (bconn){
        CloseAll();
        GetDlgItem(IDC_CONNECT)->SetWindowText("连接");
        bconn = 0;
    }
    else if (bconn==0){
        CloseAll();
        SetHook(RecvMsg, Notify);
        DWORD ret = StartClient(m_rip, atoi(m_rport), atoi(m_node));
        if (ret){
            OutputLog("启动客户端失败!error=%d,strerr=%s", ret, ConvertErrorCodeToString(ret));
            return;
        }
        GetDlgItem(IDC_RIP)->EnableWindow(0);
        GetDlgItem(IDC_RPORT)->EnableWindow(0);
        GetDlgItem(IDC_NODE)->EnableWindow(0);
        //GetDlgItem(IDC_CONNECT)->SetWindowText("正在连接...");
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



int SendReqMonitorData()
{
	tag_ID_Packet pak;
	pak.PackType = ID_ReqMonitorData;
	pak.DesCode = g_Dlg->req_monitor.rnode;
	pak.SrcCode = atoi(g_Dlg->m_node);
	pak.ReqMonitorData.type = g_Dlg->req_monitor.data_type;
	pak.SerialNo = g_Dlg->req_monitor.SerialNo;
	return SendPacket((char*)&pak, sizeof(pak));
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == req_monitor.proj_timer + 1000)
	{
		SendReqMonitorData();
	}
	else if (nIDEvent == 0)
	{
		char szS[][21] = { "连接", "正在连接...", "断开" };
		GetDlgItem(IDC_CONNECT)->SetWindowText(szS[bconn]);
		OutputLog("%s,%d", szS[bconn], bconn);
	}

    CDialog::OnTimer(nIDEvent);
}


//
LRESULT CClientDlg::OnSockRecv(WPARAM wparam, LPARAM lparam)
{
    S_Msg_Header *header = (S_Msg_Header *)wparam;
    DWORD type  = GetMsgType(header);

    switch (type)
    {
    case IA_TestString:
        {
            tag_IA_Packet *pak = (tag_IA_Packet *)wparam;
            OutputLog("收到测试字符串[%s]", pak->TestString.str);
        }
        break;
    case ID_ReqMonitorDataResult:
        {
			if (req_monitor.proj_timer == 0){
				tag_ID_Packet * recvpak = (tag_ID_Packet *)wparam;
				m_montest.OnRecvData(recvpak->ReqMonitorDataResult.Emulate_Data, recvpak->ReqMonitorDataResult.count, recvpak->ReqMonitorDataResult.type);
			}
			else{
				tag_ID_Packet * recvpak = (tag_ID_Packet *)wparam;
				m_montest.OnRecvData(recvpak->ReqMonitorDataResult.Emulate_Data, recvpak->ReqMonitorDataResult.count, recvpak->ReqMonitorDataResult.type);
				req_monitor.SerialNo += recvpak->ReqMonitorDataResult.count;
			}
        }
        break;
	case IA_ReqMonitorResult:
		{
			tag_ID_Packet * recvpak = (tag_ID_Packet *)wparam;
			if (recvpak->ReqMonitorResult.result)
			{
				OutputLog("请求监控已被接受!项目编号:%d,数据类型:%d", recvpak->ReqMonitorResult.projno, recvpak->ReqMonitorResult.data_type);
				g_Dlg->req_monitor.proj_timer = recvpak->ReqMonitorResult.projno;   //项目编号被当做时间中断使用
				g_Dlg->req_monitor.data_type = m_montest.m_reqtype;					//数据格式类型
				g_Dlg->req_monitor.rnode = recvpak->SrcCode;						//被控端节点编号
				g_Dlg->req_monitor.SerialNo = 0;									//数据个数计数开始
				SetTimer(req_monitor.proj_timer + 1000, 100, NULL);					//设置时间中断,发送请求数据
				m_montest.StartMonitor();
				m_montest.m_bstart = true;
			}
			else{
				OutputLog("请求监控被拒绝!");
			}
		}
		break;
    default:
        break;
    }


    DBPacket *pak = (DBPacket *)wparam;

    switch (pak->PackType)
    {
    case IC_PREPARESQL_READY:
        OutputLog("准备sql成功!");
        break;
    case IC_SETPARA_READY:
        OutputLog("参数设置成功!");
        break;
    case IC_SQLEXEC_OK:
        OutputLog("执行成功!");
        break;
    case IC_SQLEXEC_ERR:
        OutputLog("执行失败!");
        break;
    case IC_MOVENEXT_RES:
        OutputLog("移动到下条!");
        break;
    case IC_GETPARAMOUT_VALUE:
        OutputLog("获取输出参数值!");
        break;
    case IC_GETPARAMOUT_ERR:
        OutputLog("设置参数失败!");
        break;
    case IC_UPDATEFIELD_RES:
        OutputLog("更新字段!");
        break;
    case IC_GETFIELD_VALUE:
        {
            int chan = pak->chan;
            switch (pak->ret_GetField.vType)
            {
            case REF_I:
                OutputLog("通道%d=>GetField [I%d=%d]", chan, pak->ret_GetField.FieldInd, pak->ret_GetField.ICon);
                break;
            case REF_F:
                OutputLog("通道%d=>GetField [F%d=%f]", chan, pak->ret_GetField.FieldInd, pak->ret_GetField.FCon);
                break;
            case REF_T:
                OutputLog("通道%d=>GetField [T%d=%s]", chan, pak->ret_GetField.FieldInd, pak->ret_GetField.TCon);
                break;
            case REF_S:
                OutputLog("通道%d=>GetField [S%d=%s]", chan, pak->req_GetField.FieldInd, pak->ret_GetField.SCon);
                break;
            }
        }
        OutputLog("得到字段值!");
        break;
    }
    return 0;
}


LRESULT CClientDlg::OnSockStatus(WPARAM wparam, LPARAM lparam)
{
    T_MsgNotify *msg = (T_MsgNotify *)wparam;
    int notify = msg->notify;

    if (notify > 0 )
        bconn = 2;
    else if (int(msg->notify) < 0) {
        GetDlgItem(IDC_RIP)->EnableWindow(1);
        GetDlgItem(IDC_RPORT)->EnableWindow(1);
        GetDlgItem(IDC_NODE)->EnableWindow(1);

        bconn  = 0;
    }
    OutputLog("收到通知消息[%s,node=%d]", msg->msg, msg->node);


    char szS[][21] = { "连接", "正在连接...", "断开" };
    GetDlgItem(IDC_CONNECT)->SetWindowText(szS[bconn]);
    UpdateData();
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

    CWnd *pWnd[] = { &m_dbtest, &m_apptest, &m_ctrltest, &m_montest };
    for (int i = 0; i < 4; ++i){
        pWnd[i]->MoveWindow(rect);
        pWnd[i]->ShowWindow(SW_HIDE);
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
    CWnd * p[] = { &m_dbtest,&m_apptest, &m_ctrltest, &m_montest };

    int iCur = m_tab.GetCurSel();
    for (int i = 0; i<4; i++)
    {
        if (i == iCur)
            p[i]->ShowWindow(SW_SHOW);
        else
            p[i]->ShowWindow(SW_HIDE);
    }

    *pResult = 0;
}


void CClientDlg::OnBnClickedClear()
{
    // TODO:  在此添加控件通知处理程序代码
    m_strLog = "";
    UpdateData(0);
}
