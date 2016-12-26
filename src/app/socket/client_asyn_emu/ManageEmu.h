#pragma once


// CManageEmu 对话框

class CManageEmu : public CDialogEx
{
	DECLARE_DYNAMIC(CManageEmu)

public:
	CManageEmu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageEmu();

// 对话框数据
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedConfig();
    afx_msg void OnBnClickedRegister();
};
