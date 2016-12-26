#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CProgTestEmu 对话框

class CProgTestEmu : public CDialogEx
{
	DECLARE_DYNAMIC(CProgTestEmu)

public:
	CProgTestEmu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgTestEmu();

// 对话框数据
	enum { IDD = IDD_PROJ_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    // 测试进度
    CProgressCtrl m_progress;
    CString m_plan_name;
    // 项目名
    CString m_project_name;
    // 进度数值
    int m_progress_num;
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedPause();
    afx_msg void OnBnClickedSuspend();
    afx_msg void OnBnClickedContinue();
    afx_msg void OnBnClickedClose();
    afx_msg void OnBnClickedSendprogress();
};
