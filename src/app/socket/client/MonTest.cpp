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
    , m_rnode(0)
    , m_userid(0)
    , m_teststring(_T(""))
    , m_width(1)
    , m_height(1)
    , m_penstyle(0)
    , m_Type(0)
	, m_reqtype(0)
{
}

CMonTest::~CMonTest()
{
}

void CMonTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rnode);
	DDV_MinMaxInt(pDX, m_rnode, 0, 999);
	DDX_Text(pDX, IDC_EDIT3, m_userid);
	DDV_MinMaxInt(pDX, m_userid, 0, 10000);
	DDX_Control(pDX, IDC_ChartCtrl, m_ChartCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_teststring);
	DDV_MaxChars(pDX, m_teststring, 100);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON1, m_Color);
	DDX_Text(pDX, IDC_EDIT4, m_width);
	DDX_Text(pDX, IDC_EDIT5, m_height);
	DDX_CBIndex(pDX, IDC_COMBO2, m_penstyle);
	DDX_CBIndex(pDX, IDC_COMBO1, m_Type);
	DDX_Text(pDX, IDC_EDIT6, m_reqtype);
}


BEGIN_MESSAGE_MAP(CMonTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CMonTest::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMonTest::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_TestChart, &CMonTest::OnBnClickedTestchart)
    ON_BN_CLICKED(IDC_ClearChart, &CMonTest::OnBnClickedClearchart)
	ON_BN_CLICKED(IDC_Start, &CMonTest::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Pause, &CMonTest::OnBnClickedPause)
END_MESSAGE_MAP()



int SendStartTestPlan()
{
	tag_ID_Packet pak;
	pak.PackType = ID_StartTestPlan;
	pak.DesCode = g_Dlg->req_monitor.rnode;
	pak.SrcCode = atoi(g_Dlg->m_node);
	pak.ReqMonitorData.type = g_Dlg->req_monitor.data_type;
	pak.SerialNo = g_Dlg->req_monitor.SerialNo;
	return SendPacket((char*)&pak, sizeof(pak));
}

// CMonTest 消息处理程序
void CMonTest::OnBnClickedButton1()
{
	UpdateData();
	if (m_bstart == false)
	{
		tag_IA_Packet pak;
		int mynode = atoi(g_Dlg->m_node);
		pak.PackType = IA_ReqMonitor;
		pak.ReqMonitor.rnode = m_rnode;
		pak.ReqMonitor.userid = m_userid;
		pak.ReqMonitor.time = CTime::GetCurrentTime().GetSecond();
		pak.ReqMonitor.type = E_START_MONITOR;
		pak.ReqMonitor.datatype = m_reqtype;
		pak.ReqMonitor.node = mynode;
		pak.DesCode = m_rnode;
		pak.SrcCode = mynode;
		SendPacket((char*)&pak, sizeof(pak));
	}
	else{
		tag_IA_Packet pak;
		int mynode = atoi(g_Dlg->m_node);
		pak.PackType = IA_ReqMonitor;
		pak.ReqMonitor.rnode = m_rnode;
		pak.ReqMonitor.userid = m_userid;
		pak.ReqMonitor.time = CTime::GetCurrentTime().GetSecond();
		pak.ReqMonitor.type = E_STOP_MONITOR;
		pak.ReqMonitor.datatype = m_reqtype;
		pak.ReqMonitor.node = mynode;
		pak.DesCode = m_rnode;
		pak.SrcCode = mynode;
		SendPacket((char*)&pak, sizeof(pak));
	}
}


BOOL CMonTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CChartStandardAxis* pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
    pBottomAxis->SetMinMax(0, 1000);
    CChartStandardAxis* pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
    pLeftAxis->SetMinMax(-10, 10);
	GetDlgItem(IDC_Pause)->EnableWindow(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CMonTest::OnAddseries(int Type, COLORREF Color, int width, int height, int penstyle, int count, double *XValues, double *YValues)
{

    CChartXYSerie* pSeries = NULL;

    switch (Type)
    {
    // Line series
    case 0:
    {
        //bool bSecondHorizAxis = (PropertiesDlg.m_iHorizAxis == 1);
        //bool bSecondVertAxis = (PropertiesDlg.m_iVertAxis == 1);
        CChartLineSerie* pLineSeries = m_ChartCtrl.CreateLineSerie(0, 0);
        pSeries = pLineSeries;
        pLineSeries->SetWidth(width);
        pLineSeries->SetPenStyle(penstyle);
    }
    break;

    // Points series
    case 1:
    {
        CChartPointsSerie* pPointsSeries = m_ChartCtrl.CreatePointsSerie(0, 0);
        pSeries = pPointsSeries;

        switch (penstyle)
        {
        case 0:
            pPointsSeries->SetPointType(CChartPointsSerie::ptEllipse);
            break;

        case 1:
            pPointsSeries->SetPointType(CChartPointsSerie::ptRectangle);
            break;

        case 2:
            pPointsSeries->SetPointType(CChartPointsSerie::ptTriangle);
            break;
        }

        pPointsSeries->SetPointSize(width, height);
    }
    break;

    // Surface series
    case 2:
    {
        CChartSurfaceSerie* pSurfSeries = m_ChartCtrl.CreateSurfaceSerie(0,0 );
        pSeries = pSurfSeries;

        int style = 2;
        switch (style)
        {
        case 0:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsSolid);
            break;
        case 1:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDownDiag);
            break;
        case 2:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchUpDiag);
            break;
        case 3:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchCross);
            break;
        case 4:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDiagCross);
            break;
        case 5:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchHorizontal);
            break;
        case 6:
            pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchVertical);
            break;
        }

    }
    break;
    }

    pSeries->SetColor(Color);

    pSeries->SetPoints(XValues, YValues, count);
    m_ChartCtrl.RefreshCtrl();
}



void CMonTest::OnBnClickedButton2()
{
    UpdateData();
    tag_IA_Packet pak;
    int mynode = atoi(g_Dlg->m_node);
    pak.PackType = IA_TestString;
    sprintf((char *)&pak.TestString.str, m_teststring);
    pak.DesCode = m_rnode;
    pak.SrcCode = mynode;
    SendPacket((char*)&pak, sizeof(pak));
}


void CMonTest::StartMonitor()
{
	int wndid[] = { IDC_EDIT1, IDC_EDIT3, IDC_EDIT6};
	for (int i = 0; i < sizeof(wndid) / sizeof(int); i++){
		GetDlgItem(wndid[i])->EnableWindow(false);
	}
	GetDlgItem(IDC_Start)->EnableWindow(true);

	GetDlgItem(IDC_Start)->SetWindowText("停止");
	GetDlgItem(IDC_Pause)->SetWindowText("暂停");
	GetDlgItem(IDC_BUTTON1)->SetWindowText("关闭监控");
	
	start_stat = true;
	pause_stat = false;
}


void CMonTest::StopMonitor()
{
	int wndid[] = { IDC_EDIT1, IDC_EDIT3, IDC_EDIT6, IDC_BUTTON1 };
	for (int i = 0; i < sizeof(wndid) / sizeof(int); i++){
		GetDlgItem(wndid[i])->EnableWindow(true);
	}
	GetDlgItem(IDC_Start)->EnableWindow(false);
	GetDlgItem(IDC_Pause)->EnableWindow(false);

	GetDlgItem(IDC_Start)->SetWindowText("启动");

	//start_stat = false;
	//pause_stat = false;
}


void CMonTest::OnRecvData(S_Emulate_Data data,DWORD count,DWORD type)
{
    UpdateData();
    int data_cnt = count;
    DWORD NumberPoints = data_cnt;
    double* XValues = new double[NumberPoints];
    double* YValues = new double[NumberPoints];

    switch (type)
    {
    case E_Emulate_Data_Type1:
    {
        for (int i = 0; i<NumberPoints; i++)
        {
            XValues[i] = data.emu_data_type1.time[i]%1000;
            YValues[i] = data.emu_data_type1.value[i];
        }
        OnAddseries(m_Type, m_Color, m_width, m_height, m_penstyle, NumberPoints, XValues, YValues);
    }
    break;
    default:
        break;
    }
}


void CMonTest::OnBnClickedTestchart()
{
    // TODO:  在此添加控件通知处理程序代码
    static DWORD XStart = 0;

    UpdateData();
    int m_datatype = E_Emulate_Data_Type1;
    S_Emulate_Data data;
    int data_cnt = 10;
    for (int i = 0; i < data_cnt; i++){
        data.emu_data_type1.time[i] = CTime::GetCurrentTime().GetSecond();
        data.emu_data_type1.msec[i] = GetTickCount();
        data.emu_data_type1.value[i] = 10*sin(3.14159265 * (XStart+i) / 180);
    }
    
    DWORD NumberPoints = data_cnt;
    double* XValues = new double[NumberPoints];
    double* YValues = new double[NumberPoints];

    switch (m_datatype)
    {
    case E_Emulate_Data_Type1:
        {
            float Amplitude = 10;
            float Period = 1;
            for (int i = 0; i<NumberPoints; i++)
            {
                XValues[i] = XStart++;
                YValues[i] = data.emu_data_type1.value[i]  ;
            }
        }
        break;
    default:
        break;
    }

    OnAddseries(m_Type, m_Color, m_width, m_height, m_penstyle, NumberPoints, XValues, YValues);
    
    delete[] XValues;
    delete[] YValues;
}


void CMonTest::OnBnClickedClearchart()
{
    m_ChartCtrl.RemoveAllSeries();
}


void CMonTest::OnBnClickedStart()
{
	CString str[2] = { "启动", "停止" };
	if (start_stat)
	{
		GetDlgItem(IDC_Pause)->EnableWindow(0);

	}
	else
	{
		pause_stat = false;
		GetDlgItem(IDC_Pause)->EnableWindow(1);
		GetDlgItem(IDC_Pause)->SetWindowText("暂停");
	}
	start_stat = !start_stat;
	GetDlgItem(IDC_Start)->SetWindowText(str[start_stat]);
}


void CMonTest::OnBnClickedPause()
{
	CString str[2] = {"暂停","继续"};
	pause_stat = !pause_stat;
	GetDlgItem(IDC_Pause)->SetWindowText(str[pause_stat]);
}

