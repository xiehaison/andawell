#pragma once
#include "afxcmn.h"
#include "resource.h"


// CManager 对话框

class CManager : public CDialogEx
{
	DECLARE_DYNAMIC(CManager)

public:
	CManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManager();

// 对话框数据
	enum { IDD = IDD_Manager };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_nodelist;
    CListCtrl m_userlist;
    CTabCtrl m_tab;
    virtual BOOL OnInitDialog();
};
