// Manager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "afxdialogex.h"
#include "resource.h"


// CManager �Ի���

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


// CManager ��Ϣ�������


BOOL CManager::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
