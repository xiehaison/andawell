// APPTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "APPTest.h"
#include "afxdialogex.h"


// CAPPTest �Ի���

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


// CAPPTest ��Ϣ�������
