
// DbClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DbClient.h"
#include "DbClientDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDbClientDlg �Ի���



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


// CDbClientDlg ��Ϣ�������

BOOL CDbClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
    m_sql_result.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    CRect rect;
    GetClientRect(rect);
    rect.DeflateRect(10, 30, 10, 1);
    rect.DeflateRect(0, 40, 0, 180);
    m_sql_result.MoveWindow(rect);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDbClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDbClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDbClientDlg::OnBnClickedConfig()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    WinExec("notepad.exe .\\Client.ini", SW_SHOW);
}   


void RunLog(const char* line, ...)
{
    char buf[256];
    char buf1[1024] = { 0 };
    struct _timeb tstruct1;
    CTime t1;
    CString dline1;

    //����ʱ����־->buf
    memset(buf, 0, 256);
    va_list args;
    va_start(args, line);
    _vsnprintf(buf, sizeof(buf), line, args);
    va_end(args);

    //��ʱ����־->dline1
    _ftime(&tstruct1);
    t1 = CTime::GetCurrentTime();
    dline1.Format("%s(%3u)=>%s", t1.Format("%H:%M:%S"), tstruct1.millitm, buf);
    CString dline = dline1 + "\n";
    OutputDebugString(dline);
}

void CDbClientDlg::OnBnClickedStart()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    m_start_flag = !m_start_flag;
    if (m_start_flag) {
        UINT nPort = GetPrivateProfileInt("config", "nPort", 0, "./Client.ini");

        //��ò�Ҫʹ��aSocket.Create��������Ϊ���׻����10048����
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

        this->GetDlgItem(IDC_Start)->SetWindowText("ֹͣ");
    }
    else{
        lsnSocket.Close();
        this->GetDlgItem(IDC_Start)->SetWindowText("����");

    }
}


CSocket *CDbClientDlg::findsock()
{
    CSocket *psock;

    return psock;
}


void CDbClientDlg::OnBnClickedSqlsend()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(0);
    CSocket *sock = findsock();

}
