#pragma once


// CCtrlTest 对话框

class CCtrlTest : public CDialogEx
{
	DECLARE_DYNAMIC(CCtrlTest)

public:
	CCtrlTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCtrlTest();

// 对话框数据
	enum { IDD = IDD_CTRL_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
