
// ClientSockDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientSockDemo.h"
#include "ClientSockDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DWORD recvcount;
DWORD sentcount;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientSockDemoDlg �Ի���



CClientSockDemoDlg::CClientSockDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientSockDemoDlg::IDD, pParent)
    , m_ip(_T("127.0.0.1"))
    , m_port(1232)
    , m_node(1)
    , m_span(0)
    , m_count(1000)
    , m_size(200)
    , m_content(_T("111111111111111"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientSockDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDRECVTEXT, m_ctrlLog);
    DDX_Text(pDX, IDC_CENIP, m_ip);
    DDX_Text(pDX, IDC_CENPORT, m_port);
    DDX_Text(pDX, IDC_CODE, m_node);
    DDX_Text(pDX, IDC_INTERVAL, m_span);
    DDX_Text(pDX, IDC_SENDCNT, m_count);
    DDX_Text(pDX, IDC_PAKSIZE, m_size);
    DDX_Text(pDX, IDC_EDSENDTEXT, m_content);
}

BEGIN_MESSAGE_MAP(CClientSockDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_STARTUP, &CClientSockDemoDlg::OnBnClickedStartup)
    ON_BN_CLICKED(IDC_ZERO, &CClientSockDemoDlg::OnBnClickedZero)
    ON_BN_CLICKED(IDC_SEND, &CClientSockDemoDlg::OnBnClickedSend)
    ON_BN_CLICKED(IDC_CONSEND, &CClientSockDemoDlg::OnBnClickedConsend)
END_MESSAGE_MAP()

CClientSockDemoDlg *gpMainDlg;

// CClientSockDemoDlg ��Ϣ�������

BOOL CClientSockDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
    gpMainDlg = this;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientSockDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientSockDemoDlg::OnPaint()
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
HCURSOR CClientSockDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void myOnMsg(char *msg, int len);
void myOnNotify(char *msg, int code);

DWORD StartClient(const char *rip, int rport, int note);

int SendPacket(const char *pack, WORD len);


int CloseAll();


void myOnMsg(char *msg, int len)
{
//    gpMainDlg->AddLog(msg);
    gpMainDlg->SetCount();
    recvcount++;
}

int gbConnStat;

void myOnNotify(char *msg, int code)
{

    if (code > 0){
        gpMainDlg->AddLog("������");
        gpMainDlg->GetDlgItem(IDC_STARTUP)->SetWindowText("�Ͽ�");
        gbConnStat = 1;
    }
    else{
        gpMainDlg->AddLog("�ѶϿ�");
        gpMainDlg->GetDlgItem(IDC_STARTUP)->SetWindowText("����");
        gbConnStat = 0;
    }
}


void CClientSockDemoDlg::SetCount()
{
    CString s;
    s.Format("%d", recvcount);
    GetDlgItem(IDC_RECVCNT)->SetWindowText(s);
}


void CClientSockDemoDlg::AddLog(const char *line, ...)
{
    char buf[1024];
    memset(buf, 0, 1024);

    va_list args;
    va_start(args, line);
    _vsnprintf_s(buf, sizeof(buf), line, args);
    va_end(args);

    sprintf_s(buf, "%s\r\n", buf);

    SYSTEMTIME tt;
    GetLocalTime(&tt);

    CTime t = CTime::GetCurrentTime();
    CString dline;
    dline.Format("%s(%3u)=>%s", t.Format("%H:%M:%S").GetBuffer(), tt.wMilliseconds, buf);

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

void CClientSockDemoDlg::OnBnClickedStartup()
{
    if (gbConnStat == 0){
        gbConnStat = 100;
        SetHook(myOnMsg, myOnNotify);
        StartClient(m_ip.GetBuffer(), m_port, m_node);
    }
    else if (gbConnStat == 1){
        CloseAll();
    }
}


void CClientSockDemoDlg::OnBnClickedZero()
{
    recvcount = 0;
    GetDlgItem(IDC_RECVCNT)->SetWindowText("0");

}


void CClientSockDemoDlg::OnBnClickedSend()
{
    SendPacket(m_content.GetBuffer(), m_content.GetLength());
}


void CClientSockDemoDlg::OnBnClickedConsend()
{
    UpdateData();
    for (int i = 0; i < m_count; i++){
        SendPacket(m_content.GetBuffer(), m_content.GetLength());
        Sleep(m_span);
    }
}
