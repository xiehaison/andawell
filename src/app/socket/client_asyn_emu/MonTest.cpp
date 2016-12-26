// MonTest.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "MonTest.h"
#include "afxdialogex.h"


// CMonTest 对话框

IMPLEMENT_DYNAMIC(CMonTest, CDialogEx)

CMonTest::CMonTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonTest::IDD, pParent)
    , m_accept_monitor(FALSE)
    , m_teststring(_T(""))
    , m_node(0)
    , m_testspeed(50)
    , m_gained(_T("采集数据数:"))
    , m_databuf(_T("数据缓冲区:"))
    , m_SentCount(_T("发送数:"))
    , m_lostcount(_T("丢失数:"))
    , m_rnode(0)
{

}

CMonTest::~CMonTest()
{
}

void CMonTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK1, m_accept_monitor);
    DDX_Text(pDX, IDC_EDIT1, m_teststring);
    DDV_MaxChars(pDX, m_teststring, 100);
    DDX_Text(pDX, IDC_EDIT2, m_node);
    DDX_Slider(pDX, IDC_SLIDER1, m_testspeed);
    DDV_MinMaxInt(pDX, m_testspeed, 0, 100);
    DDX_Text(pDX, IDC_Gained, m_gained);
    DDX_Text(pDX, IDC_BufCount, m_databuf);
    DDX_Text(pDX, IDC_SentCount, m_SentCount);
    DDX_Text(pDX, IDC_LostCount, m_lostcount);
    DDX_Text(pDX, IDC_EDIT6, m_rnode);
}


BEGIN_MESSAGE_MAP(CMonTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CMonTest::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_CHECK1, &CMonTest::OnBnClickedCheck1)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_SendSampling, &CMonTest::OnBnClickedSendsampling)
END_MESSAGE_MAP()

BOOL CMonTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CMonTest::OnBnClickedButton1()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    tag_IA_Packet pak;
    int mynode = atoi(g_Dlg->m_node);
    pak.PackType = IA_TestString;
    sprintf((char *)&pak.TestString.str, m_teststring);
    pak.DesCode = m_node;
    pak.SrcCode = mynode;
    TcpSockSend((char*)&pak, sizeof(pak));
}


void CMonTest::OnBnClickedCheck1()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    if (m_accept_monitor){
        SetTimer(0, 100, NULL);
    }
    else
        KillTimer(0);

}


//模拟产生count个采集数据
//返回实际产生的采集数据个数
int CreateTestData_Sin(double data[10],int &count)
{
    //当前采集的数
    static DWORD curcnt = 0;
    return 0;
}


void CMonTest::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    switch (nIDEvent)
    {
    case 0:
        break;
    default:
        break;
    }
    CDialogEx::OnTimer(nIDEvent);
}


//发送一组采样数据
void CMonTest::OnBnClickedSendsampling()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();

    static DWORD curcnt = 0;
    tag_ID_Packet pak;
    int mynode = atoi(g_Dlg->m_node);
    pak.PackType = ID_ReqMonitorDataResult;
    pak.DesCode = m_rnode;
    pak.SrcCode = mynode;
    pak.ReqMonitorDataResult.count = 10;
    pak.ReqMonitorDataResult.type = E_Emulate_Data_Type1;

    for (int i = 0; i < 10; i++){
        pak.ReqMonitorDataResult.Emulate_Data.emu_data_type1.time[i] = curcnt % 1000;
        pak.ReqMonitorDataResult.Emulate_Data.emu_data_type1.msec[i] = GetTickCount() % 1000 + i * 10;
        pak.ReqMonitorDataResult.Emulate_Data.emu_data_type1.value[i] = 10 * sin(curcnt * 2 * 3.14159265 / 360.0);
        curcnt++;
    }

	TcpSockSend((char*)&pak, sizeof(pak));
}

