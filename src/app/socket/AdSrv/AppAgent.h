#pragma once
#include "afxcmn.h"


// CAppAgent 对话框

class CAppAgent : public CDialogEx
{
	DECLARE_DYNAMIC(CAppAgent)

public:
	CAppAgent(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppAgent();
    void Adjust();

// 对话框数据
	enum { IDD = IDD_APPAGENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    // 节点列表
    CListCtrl m_nodelist;
    // 消息列表
    CListCtrl m_msglist;
    CTabCtrl m_tab;
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
