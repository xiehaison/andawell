// MonTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "MonTest.h"
#include "afxdialogex.h"


// CMonTest �Ի���

IMPLEMENT_DYNAMIC(CMonTest, CDialogEx)

CMonTest::CMonTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonTest::IDD, pParent)
{

}

CMonTest::~CMonTest()
{
}

void CMonTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonTest, CDialogEx)
END_MESSAGE_MAP()


// CMonTest ��Ϣ�������
