#pragma once
#include "resource.h"
#include "afxcmn.h"

// CMonTest 对话框
class CMonTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMonTest)

public:
	CMonTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMonTest();

// 对话框数据
	enum { IDD = IDD_MON_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

    // 接受监控
    BOOL m_accept_monitor;
    // 速度
    // 测试字符串
    CString m_teststring;
    afx_msg void OnBnClickedButton1();
    // 节点号
    int m_testspeed;
    // //采集到的数据总数
    CString m_gained;
    // 缓冲区中的数据数
    CString m_databuf;
    // 已经发送的数据数
    CString m_SentCount;
    // 丢失的数据数量
    CString m_lostcount;
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedSendsampling();
    // 监控的主控端
    DWORD m_rnode;
    // 项目状态:已被监控,等待开始(idle),测量过程中,暂停,挂起,停止
    int m_projstatus;
    // 项目编号
    int m_project_no;
    // 总采集数
    DWORD m_totalcount;
    // 采集速度
    CProgressCtrl m_speedctrl;
};
