// CtrlTest.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "CtrlTest.h"
#include "afxdialogex.h"


// CCtrlTest 对话框

IMPLEMENT_DYNAMIC(CCtrlTest, CDialogEx)

CCtrlTest::CCtrlTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtrlTest::IDD, pParent)
{

}

CCtrlTest::~CCtrlTest()
{
}

void CCtrlTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCtrlTest, CDialogEx)
    ON_BN_CLICKED(IDC_Login, &CCtrlTest::OnBnClickedLogin)
END_MESSAGE_MAP()


// CCtrlTest 消息处理程序

//主控端登录
void CCtrlTest::OnBnClickedLogin()
{
    // TODO:  在此添加控件通知处理程序代码
}
