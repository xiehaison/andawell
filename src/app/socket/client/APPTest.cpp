// APPTest.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "APPTest.h"
#include "afxdialogex.h"


// CAPPTest 对话框

IMPLEMENT_DYNAMIC(CAPPTest, CDialogEx)
 
CAPPTest::CAPPTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPTest::IDD, pParent)
{

}

CAPPTest::~CAPPTest()
{
}

void CAPPTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAPPTest, CDialogEx)
END_MESSAGE_MAP()


// CAPPTest 消息处理程序
