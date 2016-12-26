// Manager.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "afxdialogex.h"
#include "resource.h"


// CManager 对话框

IMPLEMENT_DYNAMIC(CManager, CDialogEx)

CManager::CManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManager::IDD, pParent)
{

}

CManager::~CManager()
{
}

void CManager::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NodeList, m_nodelist);
    DDX_Control(pDX, IDC_USERLIST, m_userlist);
    DDX_Control(pDX, IDC_TAB1, m_tab);
}

    
BEGIN_MESSAGE_MAP(CManager, CDialogEx)
END_MESSAGE_MAP()


// CManager 消息处理程序


BOOL CManager::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
