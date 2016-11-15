#pragma once
#include "resource.h"

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
};
