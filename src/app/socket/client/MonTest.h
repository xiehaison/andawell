#pragma once
#include "resource.h"
#include "ChartCtrl.h"
#include "packet.h"

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
    // 被控端编号
    int m_rnode;
	bool m_bstart;
    afx_msg void OnBnClickedButton1();
    // 用户id
    int m_userid;
    // chart图表
    CChartCtrl m_ChartCtrl;
    virtual BOOL OnInitDialog();
    void OnAddseries(int Type, COLORREF Color, int width, int height, int penstyle, int count, double *XValues, double *YValues);
    void OnRecvData(S_Emulate_Data data,DWORD count,DWORD type);
	void StartMonitor();
	void StopMonitor();
	// 测试字符串
    CString m_teststring;
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedTestchart();
    COLORREF m_Color;
    int  m_width;
    int  m_height;
    int m_penstyle;
    int m_Type;
	bool pause_stat;
	bool start_stat;

    afx_msg void OnBnClickedClearchart();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPause();
	// 请求监控的数据类型
	DWORD m_reqtype;
};
