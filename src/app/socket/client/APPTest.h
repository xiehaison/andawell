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
};
