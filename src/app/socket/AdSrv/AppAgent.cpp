// AppAgent.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBAgent.h"
#include "AppAgent.h"
#include "afxdialogex.h"


// CAppAgent �Ի���

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


// CAppAgent ��Ϣ�������


BOOL CAppAgent::OnInitDialog()
{
    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    CDialogEx::OnInitDialog();
    char szTabHead[][21] = { "�ڵ�", "��Ϣ"};
    for (int i = 0; i<sizeof(szTabHead) / 21; ++i)
        m_tab.InsertItem(i, szTabHead[i], i);

    if (true)
    {
        //����״̬
        char szHead[][21] = { "�ڵ���", "��ǰ״̬", "ע��״̬","������Ϣ��", "������Ϣ��" };
        int w[] = { 60, 100, 100, 100, 100, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
        for (int i = 0; i<sizeof(szHead) / 21; ++i)
            m_nodelist.InsertColumn(i, szHead[i], LVCFMT_LEFT, w[i]);
    }

    if (true)
    {
        //����״̬
        char szHead[][21] = { "���", "Ŀ��ڵ�", "Դ�ڵ�", "��Ϣ����","��Ϣ" };
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
        m_nodelist.SetItemText(i, 1, "δ����");
    }
    m_msglist.EnsureVisible(m_msglist.GetItemCount(), false);
    //Adjust();
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
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
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    
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
