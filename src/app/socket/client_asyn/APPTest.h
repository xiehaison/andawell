#pragma once


// CAPPTest 对话框

class CAPPTest : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPTest)

public:
	CAPPTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAPPTest();

// 对话框数据
	enum { IDD = IDD_APP_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    // 目标节点
    BYTE m_node;
    // 消息类型
    int m_type;
};
