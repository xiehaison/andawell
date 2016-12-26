// AppAgent.cpp : 实现文件
//

#include "stdafx.h"
#include "DBAgent.h"
#include "AppAgent.h"
#include "afxdialogex.h"


// CAppAgent 对话框

IMPLEMENT_DYNAMIC(CAppAgent, CDialogEx)

CAppAgent::CAppAgent(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppAgent::IDD, pParent)
{

}

CAppAgent::~CAppAgent()
{
}

void CAppAgent::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NodeList, m_nodelist);
    DDX_Control(pDX, IDC_MsgList, m_msglist);
    DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CAppAgent, CDialogEx)
    ON_WM_SIZE()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CAppAgent::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CAppAgent 消息处理程序


BOOL CAppAgent::OnInitDialog()
{
    // TODO:  在此添加额外的初始化
    CDialogEx::OnInitDialog();
    char szTabHead[][21] = { "节点", "消息"};
    for (int i = 0; i<sizeof(szTabHead) / 21; ++i)
        m_tab.InsertItem(i, szTabHead[i], i);

    if (true)
    {
        //命令状态
        char szHead[][21] = { "节点编号", "当前状态", "注册状态","接收消息数", "发送消息数" };
        int w[] = { 60, 100, 100, 100, 100, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
        for (int i = 0; i<sizeof(szHead) / 21; ++i)
            m_nodelist.InsertColumn(i, szHead[i], LVCFMT_LEFT, w[i]);
    }

    if (true)
    {
        //命令状态
        char szHead[][21] = { "编号", "目标节点", "源节点", "消息类型","消息" };
        int w[] = { 60, 100, 100, 100, 100, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
        for (int i = 0; i<sizeof(szHead) / 21; ++i)
            m_msglist.InsertColumn(i, szHead[i], LVCFMT_LEFT, w[i]);
    }
    m_nodelist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_msglist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    char szBuf[255];
    int iSize = GetPrivateProfileInt("Node", "total_cnt", 0, CONFIG_FILE);
    for (int i = 0; i<iSize; ++i)
    {
        m_nodelist.InsertItem(i, itoa(i, szBuf, 10), 0);
        m_nodelist.SetItemText(i, 1, "未连接");
    }
    m_msglist.EnsureVisible(m_msglist.GetItemCount(), false);
    //Adjust();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CAppAgent::Adjust()
{
    CRect rect;
    GetClientRect(rect);
    //rect.DeflateRect(1, -30, 1, 1);
    m_tab.MoveWindow(rect);

    rect.DeflateRect(0, 22, 0, 0);
    m_nodelist.MoveWindow(rect);
    m_msglist.MoveWindow(rect);

    //m_listCommand.MoveWindow(rect);
    //m_channel.MoveWindow(rect);
    //m_commandserial.MoveWindow(rect);
    //m_sendserial.MoveWindow(rect);
    //m_buf.MoveWindow(rect);
    //m_appagent.MoveWindow(rect);

}

void CAppAgent::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (m_tab.m_hWnd == NULL) 
        return;
    Adjust();
}

void CAppAgent::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    
    CWnd * p[] = { &m_nodelist, &m_msglist };
    int iCur = m_tab.GetCurSel();
    int size = sizeof(p) / sizeof(CWnd*);
    for (int i = 0; i<size; ++i)
    {
        if (i == iCur)
            p[i]->ShowWindow(SW_SHOW);
        else
            p[i]->ShowWindow(SW_HIDE);
    }
    
    *pResult = 0;
    *pResult = 0;
}
