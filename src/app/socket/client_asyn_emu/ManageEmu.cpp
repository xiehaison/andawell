// ManageEmu.cpp : 实现文件
//

#include "stdafx.h"
#include "ManageEmu.h"
#include "afxdialogex.h"


// CManageEmu 对话框

IMPLEMENT_DYNAMIC(CManageEmu, CDialogEx)

CManageEmu::CManageEmu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageEmu::IDD, pParent)
{

}

CManageEmu::~CManageEmu()
{
}

void CManageEmu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManageEmu, CDialogEx)
    ON_BN_CLICKED(IDC_Config, &CManageEmu::OnBnClickedConfig)
    ON_BN_CLICKED(IDC_Register, &CManageEmu::OnBnClickedRegister)
END_MESSAGE_MAP()


// CManageEmu 消息处理程序


void CManageEmu::OnBnClickedConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    WinExec("notepad.exe ./client_emu.ini", SW_SHOW);
}


void CManageEmu::OnBnClickedRegister()
{
    UpdateData(0);
    tag_ID_Packet pak;
    pak.PackType = ID_RegTestMachine;
    //pak.RegTestMachine.node = GetPrivateProfileInt("Server", "my_node", 0, "./test_machine.ini");
    pak.RegTestMachine.node = atoi(g_Dlg->m_node);
    TcpSockSend((void*)&pak, sizeof(pak));
}
