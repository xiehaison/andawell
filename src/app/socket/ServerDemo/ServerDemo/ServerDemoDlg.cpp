
// ServerDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerDemo.h"
#include "ServerDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDemoDlg 对话框

CServerDemoDlg::CServerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDemoDlg::IDD, pParent)
    , m_code(0)
    , m_content(_T(""))
    , m_ip(_T(""))
    , m_port(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDRECVPAK, m_ctrlLog);
    DDX_Text(pDX, IDC_EDCODE, m_code);
    DDX_Text(pDX, IDC_EDCONTENT, m_content);
	DDV_MinMaxInt(pDX, m_port, 0, 65535);
}

BEGIN_MESSAGE_MAP(CServerDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CServerDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CServerDemoDlg 消息处理程序
CServerDemoDlg *gpMainDlg;

BOOL CServerDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    gpMainDlg = this;
    SetHook(TcpSockMsg, TcpSockNotify);
    StartSrv(1232, 600);
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDemoDlg::OnBnClickedButton1()
{
    // TODO:  在此添加控件通知处理程序代码
    SendPacket(m_code, m_content.GetBuffer(), m_content.GetLength());
}


void CServerDemoDlg::SetCounter(DWORD count)
{
    CString s;
    s.Format("%d", count);
    GetDlgItem(IDC_Count)->SetWindowText(s);
}


void CServerDemoDlg::AddLog(const char *line, ...)
{
    char buf[1024];
    memset(buf, 0, 1024);

    va_list args;
    va_start(args, line);
    _vsnprintf_s(buf, sizeof(buf), line, args);
    va_end(args);

    sprintf_s(buf, "%s\r\n",buf);

    SYSTEMTIME tt;
    GetLocalTime(&tt);

    CTime t = CTime::GetCurrentTime();
    CString dline;
    dline.Format("%s(%3u)=>%s", t.Format("%H:%M:%S").GetBuffer(), tt.wMilliseconds , buf);

    //	UpdateData(TRUE);
    CString buf1;///char buf[2048]="";
    m_ctrlLog.GetWindowText(buf1);
    buf1 = buf1 + dline;
    int linecnt = m_ctrlLog.GetLineCount();
    if (linecnt>100)
    {
        int pos = buf1.Find("\r\n");
        buf1.Delete(0, pos + 2);
    }
    m_ctrlLog.SetWindowText(buf1);
    //	UpdateData(FALSE);
    m_ctrlLog.SetSel(buf1.GetLength(), buf1.GetLength());
}



DWORD TcpSockMsg(int node, char *msg, int len)
{
    static long count,lostcount;
    int sentlen = SendPacket(node, msg, len);
    if (sentlen != len){
        gpMainDlg->AddLog("丢包了");
        lostcount++;
        return 0;
    }
    else{
        count++;
    }
    gpMainDlg->SetCounter(count);
    return 0;
}


DWORD TcpSockNotify(int node, int notify, char *msg)
{
    if (notify>0)
        gpMainDlg->AddLog("节点%d已连接", node);
    else
        gpMainDlg->AddLog("节点%d已断开", node);

    return 0;
}

