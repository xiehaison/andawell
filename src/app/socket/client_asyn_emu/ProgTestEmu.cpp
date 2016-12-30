// ProgTestEmu.cpp : 实现文件
//

#include "stdafx.h"
#include "ProgTestEmu.h"
#include "afxdialogex.h"


// CProgTestEmu 对话框

IMPLEMENT_DYNAMIC(CProgTestEmu, CDialogEx)

CProgTestEmu::CProgTestEmu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgTestEmu::IDD, pParent)
    , m_plan_name(_T(""))
    , m_progress_num(0)
{

}

CProgTestEmu::~CProgTestEmu()
{
}

void CProgTestEmu::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROGRESS1, m_progress);
    DDX_Text(pDX, IDC_PLANNAME, m_plan_name);
    DDX_Text(pDX, IDC_PRJNAME, m_project_name);
    DDX_Text(pDX, IDC_EDIT4, m_progress_num);
	DDV_MinMaxInt(pDX, m_progress_num, 0, 100);
}


BEGIN_MESSAGE_MAP(CProgTestEmu, CDialogEx)
    ON_BN_CLICKED(IDC_Start, &CProgTestEmu::OnBnClickedStart)
    ON_BN_CLICKED(IDC_PAUSE, &CProgTestEmu::OnBnClickedPause)
    ON_BN_CLICKED(IDC_SUSPEND, &CProgTestEmu::OnBnClickedSuspend)
    ON_BN_CLICKED(IDC_CONTINUE, &CProgTestEmu::OnBnClickedContinue)
    ON_BN_CLICKED(IDC_CLOSE, &CProgTestEmu::OnBnClickedClose)
    ON_BN_CLICKED(IDC_SendProgress, &CProgTestEmu::OnBnClickedSendprogress)
END_MESSAGE_MAP()


// CProgTestEmu 消息处理程序
void PlanStart(int sn)
{
    tag_ID_Packet pak;
    pak.PackType = ID_StartTestPlan;
    pak.StartTestPlan.sn = sn;
    pak.StartTestPlan.start_time = CTime::GetCurrentTime().GetTime();
    pak.StartTestPlan.start_user = 0;
    pak.StartTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}

void CProgTestEmu::OnBnClickedStart()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    tag_ID_Packet pak;
    pak.PackType = ID_StartTestPlan;
    strncpy(pak.StartTestPlan.planname, m_plan_name, sizeof(pak.StartTestPlan.planname));
    strncpy(pak.StartTestPlan.projname, m_project_name, sizeof(pak.StartTestPlan.projname));
    pak.StartTestPlan.sn = rand();
    pak.StartTestPlan.start_time = CTime::GetCurrentTime().GetTime();
    pak.StartTestPlan.start_user = 0;    
    pak.StartTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void PlanPause(int sn)
{
    tag_ID_Packet pak;
    pak.PackType = ID_PauseTestPlan;
    pak.PauseTestPlan.sn = sn;
    pak.PauseTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.PauseTestPlan.user = 0;
    pak.PauseTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void CProgTestEmu::OnBnClickedPause()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    PlanPause(rand());
}

void SuspendTestPlan(int sn)
{
    tag_ID_Packet pak;
    pak.PackType = ID_SuspendTestPlan;
    pak.SuspendTestPlan.sn = sn;
    pak.SuspendTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.SuspendTestPlan.user = 0;
    pak.SuspendTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}

void CProgTestEmu::OnBnClickedSuspend()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    tag_ID_Packet pak;
    pak.PackType = ID_SuspendTestPlan;
    pak.SuspendTestPlan.sn = rand();
    pak.SuspendTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.SuspendTestPlan.user = 0;
    pak.SuspendTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));

}

void ContinueTestPlan(int sn)
{
    tag_ID_Packet pak;
    pak.PackType = ID_ContinueTestPlan;
    pak.ContinueTestPlan.sn = sn;
    pak.ContinueTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.ContinueTestPlan.user = 0;
    pak.ContinueTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void CProgTestEmu::OnBnClickedContinue()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    tag_ID_Packet pak;
    pak.PackType = ID_ContinueTestPlan;
    pak.ContinueTestPlan.sn = rand();
    pak.ContinueTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.ContinueTestPlan.user = 0;
    pak.ContinueTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void StopTestPlan(int sn)
{
    tag_ID_Packet pak;
    pak.PackType = ID_StopTestPlan;
    pak.StopTestPlan.sn = sn;
    pak.StopTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.StopTestPlan.user = 0;
    pak.StopTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void CProgTestEmu::OnBnClickedClose()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData();
    tag_ID_Packet pak;
    pak.PackType = ID_StopTestPlan;
    strncpy(pak.StopTestPlan.planname, m_plan_name, sizeof(pak.StopTestPlan.planname));
    strncpy(pak.StopTestPlan.projname, m_project_name, sizeof(pak.StopTestPlan.projname));
    pak.StopTestPlan.sn = rand();
    pak.StopTestPlan.time = CTime::GetCurrentTime().GetTime();
    pak.StopTestPlan.user = 0;
    pak.StopTestPlan.node = atoi(g_Dlg->m_node);
    pak.SrcCode = atoi(g_Dlg->m_node);
    TcpSockSend((void *)&pak, sizeof(pak));
}


void CProgTestEmu::OnBnClickedSendprogress()
{
    UpdateData();
    tag_ID_Packet pak;
    pak.PackType = ID_ProgressPlan;
    pak.ProgressPlan.sn = rand();
    pak.ProgressPlan.time = CTime::GetCurrentTime().GetTime();
    pak.ProgressPlan.progress = m_progress_num;
    pak.SrcCode = atoi(g_Dlg->m_node);

    TcpSockSend((void *)&pak, sizeof(pak));
}

