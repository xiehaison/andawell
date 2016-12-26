// MonTest.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "MonTest.h"
#include "afxdialogex.h"

#include "ChartLineSerie.h"
#include "ChartPointsSerie.h"
#include "ChartSurfaceSerie.h"
#include "ChartGrid.h"

//#include "SeriesPropDlg.h"
//#include "LinePropDialog.h"
//#include "SurfacePropDialog.h"
//#include "PointsPropDialog.h"

#include "ChartBarSerie.h"
#include "ChartLabel.h"

#include "ChartAxisLabel.h"
#include "ChartStandardAxis.h"
#include "ChartDateTimeAxis.h"

#include "ChartCrossHairCursor.h"
#include "ChartDragLineCursor.h"

#include "chartctrl.h"


// CMonTest 对话框

IMPLEMENT_DYNAMIC(CMonTest, CDialogEx)

CMonTest::CMonTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonTest::IDD, pParent)
    , m_dstnode(_T(""))
{

}

CMonTest::~CMonTest()
{
}

void CMonTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ChartCtrl, m_ChartCtrl);

    DDX_Text(pDX, IDC_DstNode, m_dstnode);
}


BEGIN_MESSAGE_MAP(CMonTest, CDialogEx)
    ON_BN_CLICKED(IDC_Start, &CMonTest::OnBnClickedStart)
    ON_BN_CLICKED(IDC_TestChart, &CMonTest::OnBnClickedTestchart)
    ON_BN_CLICKED(IDC_TestChart2, &CMonTest::OnBnClickedTestchart2)
END_MESSAGE_MAP()


// CMonTest 消息处理程序
void CMonTest::OnBnClickedStart()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    //tag_ID_Packet IDPacket;
    //
    //IDPacket.PackType = ID_ReqMonitor;
    //IDPacket.SerialNo = 0;
    //IDPacket.ReqMonitor.type = 0;

}


BOOL CMonTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    CChartStandardAxis* pBottomAxis =  m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
    pBottomAxis->SetMinMax(0, 100);
    CChartStandardAxis* pLeftAxis   =  m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
    pLeftAxis->SetMinMax(-10, 10);
    //OnLeftAxisRadio();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CMonTest::OnBnClickedTestchart()
{
     //TODO:  在此添加控件通知处理程序代码
    int Type = 1;
    TChartString Name = "1";

    CChartXYSerie* pSeries = NULL;
    CChartLineSerie* pLineSeries = m_ChartCtrl.CreateLineSerie(false,false );
    pSeries = pLineSeries;

    pLineSeries->SetWidth(2);
    pLineSeries->SetPenStyle(1);


    pSeries->SetName(Name);
    pSeries->SetColor(0x00dd0000);

    int NumberPoints = 100;
    double* XValues = new double[NumberPoints];
    double* YValues = new double[NumberPoints];
    float Step = 1;
    float XStart = 0;
    float Amplitude = 10;
    float Period = 1;

    for (int i = 0; i < NumberPoints; i++)
    {
        XValues[i] = XStart + i * Step;
        //YValues[i] = Amplitude * (float)sin(2 * 3.141592 * XValues[i] / Period);
        YValues[i] = rand()%10*1.0;
    }
    pSeries->SetPoints(XValues, YValues, NumberPoints);

    delete[] XValues;
    delete[] YValues;
    m_ChartCtrl.RefreshCtrl();
}


void CMonTest::OnBnClickedTestchart2()
{
    // TODO:  在此添加控件通知处理程序代码
    int Type = 1;
    TChartString Name = "2";

    CChartXYSerie* pSeries = NULL;
    CChartSurfaceSerie* pSurfSeries = m_ChartCtrl.CreateSurfaceSerie(false, false);

    pSeries = pSurfSeries;

    pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsSolid);

    pSeries->SetName(Name);
    pSeries->SetColor(0x00dd00ff);

    int NumberPoints = 100;
    double* XValues = new double[NumberPoints];
    double* YValues = new double[NumberPoints];
    float Step = 1;
    float XStart = 0;
    float Amplitude = 10;
    float Period = 1;

    for (int i = 0; i < NumberPoints; i++)
    {
        XValues[i] = XStart + i * Step;
        //YValues[i] = Amplitude * (float)sin(2 * 3.141592 * XValues[i] / Period);
        YValues[i] = rand() % 10 * -1.0;
    }
    pSeries->SetPoints(XValues, YValues, NumberPoints);

    delete[] XValues;
    delete[] YValues;
    m_ChartCtrl.RefreshCtrl();

}
