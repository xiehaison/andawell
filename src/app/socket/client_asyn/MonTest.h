#pragma once
#include "resource.h"
#include "ChartCtrl.h"
//#include "ColourPicker.h"
#include "ChartLineSerie.h"



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
    afx_msg void OnBnClickedStart();
    virtual BOOL OnInitDialog();

//    CChartAxis* GetSelectedAxis();
    CChartCtrl m_ChartCtrl;

    // 单检设备
    afx_msg void OnBnClickedTestchart();
    // //被监控的检测节点
    CString m_dstnode;
    afx_msg void OnBnClickedTestchart2();
};
