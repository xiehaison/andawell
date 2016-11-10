
// DbClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DbClient.h"
#include "DbClientDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDbClientDlg 对话框



CDbClientDlg::CDbClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDbClientDlg::IDD, pParent)
    , m_start_flag(0)
    , m_sql(_T(""))
    , m_out(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDbClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SQL, m_sql);
    DDX_Text(pDX, IDC_OUT, m_out);
    DDX_Control(pDX, IDC_OUT, m_ctrl_out);
    DDX_Control(pDX, IDC_SQLRESULT, m_sql_result);
}

BEGIN_MESSAGE_MAP(CDbClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_Config, &CDbClientDlg::OnBnClickedConfig)
    ON_BN_CLICKED(IDC_Start, &CDbClientDlg::OnBnClickedStart)
    ON_BN_CLICKED(IDC_SQLSend, &CDbClientDlg::OnBnClickedSqlsend)
END_MESSAGE_MAP()


// CDbClientDlg 消息处理程序

BOOL CDbClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    m_sql_result.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(10, 30, 10, 1);
    rect.DeflateRect(0, 40, 0, 180);
    m_sql_result.MoveWindow(rect);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDbClientDlg::OnPaint()
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
HCURSOR CDbClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDbClientDlg::OnBnClickedConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    WinExec("notepad.exe .\\Client.ini", SW_SHOW);
}   


void RunLog(const char* line, ...)
{
    char buf[256];
    char buf1[1024] = { 0 };
    struct _timeb tstruct1;
    CTime t1;
    CString dline1;

    //不带时间日志->buf
    memset(buf, 0, 256);
    va_list args;
    va_start(args, line);
    _vsnprintf(buf, sizeof(buf), line, args);
    va_end(args);

    //带时间日志->dline1
    _ftime(&tstruct1);
    t1 = CTime::GetCurrentTime();
    dline1.Format("%s(%3u)=>%s", t1.Format("%H:%M:%S"), tstruct1.millitm, buf);
    CString dline = dline1 + "\n";
    OutputDebugString(dline);
}

void CDbClientDlg::OnBnClickedStart()
{
    // TODO:  在此添加控件通知处理程序代码
    m_start_flag = !m_start_flag;
    if (m_start_flag) {
        UINT nPort = GetPrivateProfileInt("config", "nPort", 0, "./Client.ini");

        //最好不要使用aSocket.Create创建，因为容易会出现10048错误
        //if (!lsnSocket.Socket())
        if (!lsnSocket.Create(nPort)) {
            char szError[256] = { 0 };
            sprintf(szError, "Create Faild: %d", GetLastError());
            RunLog(szError);
            return;
        }
//        lsnSocket.AsyncSelect(FD_ACCEPT);
        //    aSocket.Create(nPort);
        BOOL bOptVal = TRUE;
        int bOptLen = sizeof(BOOL);

        if (!lsnSocket.Listen(10))
        {
            char szError[256] = { 0 };
            sprintf(szError, "Listen Faild: %d", GetLastError());
            RunLog(szError);
            return;
        }

        this->GetDlgItem(IDC_Start)->SetWindowText("停止");
    }
    else{
        lsnSocket.Close();
        this->GetDlgItem(IDC_Start)->SetWindowText("启动");

    }
}


CSocket *CDbClientDlg::findsock()
{
    CSocket *psock;

    return psock;
}


void CDbClientDlg::OnBnClickedSqlsend()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(0);
    CSocket *sock = findsock();

}
