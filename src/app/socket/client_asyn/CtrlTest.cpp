// CtrlTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "CtrlTest.h"
#include "afxdialogex.h"


// CCtrlTest �Ի���

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
END_MESSAGE_MAP()


// CCtrlTest ��Ϣ�������
