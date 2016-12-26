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
    , m_node(0)
    , m_type(0)
{

}

CAPPTest::~CAPPTest()
{
}

void CAPPTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_node);
    DDV_MinMaxByte(pDX, m_node, 0, 100);
    DDX_CBIndex(pDX, IDC_COMBO1, m_type);
}


BEGIN_MESSAGE_MAP(CAPPTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CAPPTest::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAPPTest ��Ϣ�������


void CAPPTest::OnBnClickedButton1()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    tag_IA_Packet pak;
    memset(&pak, 0, sizeof(pak));
    pak.SerialNo = GetTickCount();
    pak.DesCode = m_node;
    pak.HeadTag = 0xeffffffe;
    pak.PackType = m_type+IA_START;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}
